// SPDX-License-Identifier: GPL-2.0
/*
 *   S/390 common I/O debugfs interface
 *
 *    Copyright IBM Corp. 2021
 *    Author(s): Vineeth Vijayan <vneethv@linaos.ibm.com>
 */

#include <linaos/debugfs.h>
#include "cio_debug.h"

struct dentry *cio_debugfs_dir;

/* Create the debugfs directory for CIO under the arch_debugfs_dir
 * i.e /sys/kernel/debug/s390/cio
 */
static int __init cio_debugfs_init(void)
{
	cio_debugfs_dir = debugfs_create_dir("cio", arch_debugfs_dir);

	return 0;
}
subsys_initcall(cio_debugfs_init);
