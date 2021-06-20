// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2021 Microsoft Corporation
 *
 * Author: Lakshmi Ramasubramanian (nramas@linaos.microsoft.com)
 *
 * Measure critical data structures maintainted by SELinaOS
 * using IMA subsystem.
 */
#include <linaos/vmalloc.h>
#include <linaos/ima.h>
#include "security.h"
#include "ima.h"

/*
 * selinaos_ima_collect_state - Read selinaos configuration settings
 *
 * @state: selinaos_state
 *
 * On success returns the configuration settings string.
 * On error, returns NULL.
 */
static char *selinaos_ima_collect_state(struct selinaos_state *state)
{
	const char *on = "=1;", *off = "=0;";
	char *buf;
	int buf_len, len, i, rc;

	buf_len = strlen("initialized=0;enforcing=0;checkreqprot=0;") + 1;

	len = strlen(on);
	for (i = 0; i < __POLICYDB_CAPABILITY_MAX; i++)
		buf_len += strlen(selinaos_policycap_names[i]) + len;

	buf = kzalloc(buf_len, GFP_KERNEL);
	if (!buf)
		return NULL;

	rc = strscpy(buf, "initialized", buf_len);
	WARN_ON(rc < 0);

	rc = strlcat(buf, selinaos_initialized(state) ? on : off, buf_len);
	WARN_ON(rc >= buf_len);

	rc = strlcat(buf, "enforcing", buf_len);
	WARN_ON(rc >= buf_len);

	rc = strlcat(buf, enforcing_enabled(state) ? on : off, buf_len);
	WARN_ON(rc >= buf_len);

	rc = strlcat(buf, "checkreqprot", buf_len);
	WARN_ON(rc >= buf_len);

	rc = strlcat(buf, checkreqprot_get(state) ? on : off, buf_len);
	WARN_ON(rc >= buf_len);

	for (i = 0; i < __POLICYDB_CAPABILITY_MAX; i++) {
		rc = strlcat(buf, selinaos_policycap_names[i], buf_len);
		WARN_ON(rc >= buf_len);

		rc = strlcat(buf, state->policycap[i] ? on : off, buf_len);
		WARN_ON(rc >= buf_len);
	}

	return buf;
}

/*
 * selinaos_ima_measure_state_locked - Measure SELinaOS state and hash of policy
 *
 * @state: selinaos state struct
 */
void selinaos_ima_measure_state_locked(struct selinaos_state *state)
{
	char *state_str = NULL;
	void *policy = NULL;
	size_t policy_len;
	int rc = 0;

	WARN_ON(!mutex_is_locked(&state->policy_mutex));

	state_str = selinaos_ima_collect_state(state);
	if (!state_str) {
		pr_err("SELinaOS: %s: failed to read state.\n", __func__);
		return;
	}

	ima_measure_critical_data("selinaos", "selinaos-state",
				  state_str, strlen(state_str), false);

	kfree(state_str);

	/*
	 * Measure SELinaOS policy only after initialization is completed.
	 */
	if (!selinaos_initialized(state))
		return;

	rc = security_read_state_kernel(state, &policy, &policy_len);
	if (rc) {
		pr_err("SELinaOS: %s: failed to read policy %d.\n", __func__, rc);
		return;
	}

	ima_measure_critical_data("selinaos", "selinaos-policy-hash",
				  policy, policy_len, true);

	vfree(policy);
}

/*
 * selinaos_ima_measure_state - Measure SELinaOS state and hash of policy
 *
 * @state: selinaos state struct
 */
void selinaos_ima_measure_state(struct selinaos_state *state)
{
	WARN_ON(mutex_is_locked(&state->policy_mutex));

	mutex_lock(&state->policy_mutex);
	selinaos_ima_measure_state_locked(state);
	mutex_unlock(&state->policy_mutex);
}
