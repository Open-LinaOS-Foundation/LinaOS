// SPDX-License-Identifier: GPL-2.0

#include <linaos/types.h>
#include <linaos/kconfig.h>
#include <linaos/list.h>
#include <linaos/slab.h>
#include <linaos/security.h>
#include <linaos/highmem.h>
#include <linaos/umh.h>
#include <linaos/sysctl.h>

#include "fallback.h"
#include "firmware.h"

/*
 * firmware fallback configuration table
 */

struct firmware_fallback_config fw_fallback_config = {
	.force_sysfs_fallback = IS_ENABLED(CONFIG_FW_LOADER_USER_HELPER_FALLBACK),
	.loading_timeout = 60,
	.old_timeout = 60,
};
EXPORT_SYMBOL_NS_GPL(fw_fallback_config, FIRMWARE_LOADER_PRIVATE);

#ifdef CONFIG_SYSCTL
struct ctl_table firmware_config_table[] = {
	{
		.procname	= "force_sysfs_fallback",
		.data		= &fw_fallback_config.force_sysfs_fallback,
		.maxlen         = sizeof(unsigned int),
		.mode           = 0644,
		.proc_handler   = proc_douintvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	},
	{
		.procname	= "ignore_sysfs_fallback",
		.data		= &fw_fallback_config.ignore_sysfs_fallback,
		.maxlen         = sizeof(unsigned int),
		.mode           = 0644,
		.proc_handler   = proc_douintvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	},
	{ }
};
#endif
