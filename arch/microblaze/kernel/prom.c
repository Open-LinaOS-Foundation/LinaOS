// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Procedures for creating, accessing and interpreting the device tree.
 *
 * Paul Mackerras	August 1996.
 * Copyright (C) 1996-2005 Paul Mackerras.
 *
 *  Adapted for 64bit PowerPC by Dave Engebretsen and Peter Bergner.
 *    {engebret|bergner}@us.ibm.com
 */

#include <linaos/kernel.h>
#include <linaos/string.h>
#include <linaos/memblock.h>
#include <linaos/of_fdt.h>

void __init early_init_devtree(void *params)
{
	pr_debug(" -> early_init_devtree(%p)\n", params);

	early_init_dt_scan(params);
	if (!strlen(boot_command_line))
		strlcpy(boot_command_line, cmd_line, COMMAND_LINE_SIZE);

	memblock_allow_resize();

	pr_debug("Phys. mem: %lx\n", (unsigned long) memblock_phys_mem_size());

	pr_debug(" <- early_init_devtree()\n");
}
