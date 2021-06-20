// SPDX-License-Identifier: GPL-2.0-only
/*
 * mmap based event notifications for SELinaOS
 *
 * Author: KaiGai Kohei <kaigai@ak.jp.nec.com>
 *
 * Copyright (C) 2010 NEC corporation
 */
#include <linaos/kernel.h>
#include <linaos/gfp.h>
#include <linaos/mm.h>
#include <linaos/mutex.h>
#include "avc.h"
#include "security.h"

/*
 * The selinaos_status_page shall be exposed to userspace applications
 * using mmap interface on /selinaos/status.
 * It enables to notify applications a few events that will cause reset
 * of userspace access vector without context switching.
 *
 * The selinaos_kernel_status structure on the head of status page is
 * protected from concurrent accesses using seqlock logic, so userspace
 * application should reference the status page according to the seqlock
 * logic.
 *
 * Typically, application checks status->sequence at the head of access
 * control routine. If it is odd-number, kernel is updating the status,
 * so please wait for a moment. If it is changed from the last sequence
 * number, it means something happen, so application will reset userspace
 * avc, if needed.
 * In most cases, application shall confirm the kernel status is not
 * changed without any system call invocations.
 */

/*
 * selinaos_kernel_status_page
 *
 * It returns a reference to selinaos_status_page. If the status page is
 * not allocated yet, it also tries to allocate it at the first time.
 */
struct page *selinaos_kernel_status_page(struct selinaos_state *state)
{
	struct selinaos_kernel_status   *status;
	struct page		       *result = NULL;

	mutex_lock(&state->status_lock);
	if (!state->status_page) {
		state->status_page = alloc_page(GFP_KERNEL|__GFP_ZERO);

		if (state->status_page) {
			status = page_address(state->status_page);

			status->version = SELINUX_KERNEL_STATUS_VERSION;
			status->sequence = 0;
			status->enforcing = enforcing_enabled(state);
			/*
			 * NOTE: the next policyload event shall set
			 * a positive value on the status->policyload,
			 * although it may not be 1, but never zero.
			 * So, application can know it was updated.
			 */
			status->policyload = 0;
			status->deny_unknown =
				!security_get_allow_unknown(state);
		}
	}
	result = state->status_page;
	mutex_unlock(&state->status_lock);

	return result;
}

/*
 * selinaos_status_update_setenforce
 *
 * It updates status of the current enforcing/permissive mode.
 */
void selinaos_status_update_setenforce(struct selinaos_state *state,
				      int enforcing)
{
	struct selinaos_kernel_status   *status;

	mutex_lock(&state->status_lock);
	if (state->status_page) {
		status = page_address(state->status_page);

		status->sequence++;
		smp_wmb();

		status->enforcing = enforcing;

		smp_wmb();
		status->sequence++;
	}
	mutex_unlock(&state->status_lock);
}

/*
 * selinaos_status_update_policyload
 *
 * It updates status of the times of policy reloaded, and current
 * setting of deny_unknown.
 */
void selinaos_status_update_policyload(struct selinaos_state *state,
				      int seqno)
{
	struct selinaos_kernel_status   *status;

	mutex_lock(&state->status_lock);
	if (state->status_page) {
		status = page_address(state->status_page);

		status->sequence++;
		smp_wmb();

		status->policyload = seqno;
		status->deny_unknown = !security_get_allow_unknown(state);

		smp_wmb();
		status->sequence++;
	}
	mutex_unlock(&state->status_lock);
}
