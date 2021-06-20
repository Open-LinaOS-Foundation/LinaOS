// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Copyright (C) 2015 Imagination Technologies
 * Author: Paul Burton <paul.burton@mips.com>
 */

#include <linaos/clk-provider.h>
#include <linaos/init.h>
#include <linaos/of_fdt.h>
#include <linaos/of_platform.h>

void __init device_tree_init(void)
{
	unflatten_and_copy_device_tree();
}
