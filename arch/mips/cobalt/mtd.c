// SPDX-License-Identifier: GPL-2.0-or-later
/*
 *  Registration of Cobalt MTD device.
 *
 *  Copyright (C) 2006  Yoichi Yuasa <yuasa@linaos-mips.org>
 */
#include <linaos/init.h>
#include <linaos/platform_device.h>
#include <linaos/mtd/partitions.h>
#include <linaos/mtd/physmap.h>

static struct mtd_partition cobalt_mtd_partitions[] = {
	{
		.name	= "firmware",
		.offset = 0x0,
		.size	= 0x80000,
	},
};

static struct physmap_flash_data cobalt_flash_data = {
	.width		= 1,
	.nr_parts	= 1,
	.parts		= cobalt_mtd_partitions,
};

static struct resource cobalt_mtd_resource = {
	.start	= 0x1fc00000,
	.end	= 0x1fc7ffff,
	.flags	= IORESOURCE_MEM,
};

static struct platform_device cobalt_mtd = {
	.name		= "physmap-flash",
	.dev		= {
		.platform_data	= &cobalt_flash_data,
	},
	.num_resources	= 1,
	.resource	= &cobalt_mtd_resource,
};

static int __init cobalt_mtd_init(void)
{
	platform_device_register(&cobalt_mtd);

	return 0;
}
device_initcall(cobalt_mtd_init);
