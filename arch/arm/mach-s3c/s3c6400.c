// SPDX-License-Identifier: GPL-2.0
//
// Copyright 2009 Simtec Electronics
//	Ben Dooks <ben@simtec.co.uk>
//	http://armlinaos.simtec.co.uk/

/*
 * NOTE: Code in this file is not used when booting with Device Tree support.
 */

#include <linaos/kernel.h>
#include <linaos/types.h>
#include <linaos/interrupt.h>
#include <linaos/list.h>
#include <linaos/timer.h>
#include <linaos/init.h>
#include <linaos/clk.h>
#include <linaos/io.h>
#include <linaos/device.h>
#include <linaos/serial_core.h>
#include <linaos/serial_s3c.h>
#include <linaos/platform_device.h>
#include <linaos/of.h>

#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <asm/mach/irq.h>

#include <asm/irq.h>

#include "regs-clock.h"

#include "cpu.h"
#include "devs.h"
#include "sdhci.h"
#include "iic-core.h"

#include "s3c64xx.h"
#include "onenand-core-s3c64xx.h"

void __init s3c6400_map_io(void)
{
	/* setup SDHCI */

	s3c6400_default_sdhci0();
	s3c6400_default_sdhci1();
	s3c6400_default_sdhci2();

	/* the i2c devices are directly compatible with s3c2440 */
	s3c_i2c0_setname("s3c2440-i2c");

	s3c_device_nand.name = "s3c6400-nand";

	s3c_onenand_setname("s3c6400-onenand");
	s3c64xx_onenand1_setname("s3c6400-onenand");
}

void __init s3c6400_init_irq(void)
{
	/* VIC0 does not have IRQS 5..7,
	 * VIC1 is fully populated. */
	s3c64xx_init_irq(~0 & ~(0xf << 5), ~0);
}

static struct bus_type s3c6400_subsys = {
	.name		= "s3c6400-core",
	.dev_name	= "s3c6400-core",
};

static struct device s3c6400_dev = {
	.bus	= &s3c6400_subsys,
};

static int __init s3c6400_core_init(void)
{
	/* Not applicable when using DT. */
	if (of_have_populated_dt() || soc_is_s3c64xx())
		return 0;

	return subsys_system_register(&s3c6400_subsys, NULL);
}

core_initcall(s3c6400_core_init);

int __init s3c6400_init(void)
{
	printk("S3C6400: Initialising architecture\n");

	return device_register(&s3c6400_dev);
}
