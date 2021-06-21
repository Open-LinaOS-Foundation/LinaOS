// SPDX-License-Identifier: GPL-2.0
#include <linaos/init.h>
#include <linaos/debugfs.h>
#include <linaos/slab.h>

#include "debugfs.h"

static struct dentry *d_xen_debug;

struct dentry * __init xen_init_debugfs(void)
{
	if (!d_xen_debug)
		d_xen_debug = debugfs_create_dir("xen", NULL);
	return d_xen_debug;
}

