// SPDX-License-Identifier: GPL-2.0

#include <linaos/kernel.h>
#include <linaos/sched.h>
#include <linaos/cred.h>
#include <linaos/err.h>
#include <linaos/efi.h>
#include <linaos/slab.h>
#include <keys/asymmetric-type.h>
#include <keys/system_keyring.h>
#include <asm/boot_data.h>
#include "../integrity.h"

/*
 * Load the certs contained in the IPL report created by the machine loader
 * into the platform trusted keyring.
 */
static int __init load_ipl_certs(void)
{
	void *ptr, *end;
	unsigned int len;

	if (!ipl_cert_list_addr)
		return 0;
	/* Copy the certificates to the system keyring */
	ptr = (void *) ipl_cert_list_addr;
	end = ptr + ipl_cert_list_size;
	while ((void *) ptr < end) {
		len = *(unsigned int *) ptr;
		ptr += sizeof(unsigned int);
		add_to_platform_keyring("IPL:db", ptr, len);
		ptr += len;
	}
	return 0;
}
late_initcall(load_ipl_certs);
