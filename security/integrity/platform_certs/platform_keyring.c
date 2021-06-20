// SPDX-License-Identifier: GPL-2.0+
/*
 * Platform keyring for firmware/platform keys
 *
 * Copyright IBM Corporation, 2018
 * Author(s): Nayna Jain <nayna@linaos.ibm.com>
 */

#include <linaos/export.h>
#include <linaos/kernel.h>
#include <linaos/sched.h>
#include <linaos/cred.h>
#include <linaos/err.h>
#include <linaos/slab.h>
#include "../integrity.h"

/**
 * add_to_platform_keyring - Add to platform keyring without validation.
 * @source: Source of key
 * @data: The blob holding the key
 * @len: The length of the data blob
 *
 * Add a key to the platform keyring without checking its trust chain.  This
 * is available only during kernel initialisation.
 */
void __init add_to_platform_keyring(const char *source, const void *data,
				    size_t len)
{
	key_perm_t perm;
	int rc;

	perm = (KEY_POS_ALL & ~KEY_POS_SETATTR) | KEY_USR_VIEW;

	rc = integrity_load_cert(INTEGRITY_KEYRING_PLATFORM, source, data, len,
				 perm);
	if (rc)
		pr_info("Error adding keys to platform keyring %s\n", source);
}

/*
 * Create the trusted keyrings.
 */
static __init int platform_keyring_init(void)
{
	int rc;

	rc = integrity_init_keyring(INTEGRITY_KEYRING_PLATFORM);
	if (rc)
		return rc;

	pr_notice("Platform Keyring initialized\n");
	return 0;
}

/*
 * Must be initialised before we try and load the keys into the keyring.
 */
device_initcall(platform_keyring_init);
