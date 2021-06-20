// SPDX-License-Identifier: GPL-2.0
//
// Copyright 2004 Simtec Electronics
//	Ben Dooks <ben@simtec.co.uk>
//
// http://armlinaos.simtec.co.uk/
//
// Power Management helpers for Simtec S3C24XX implementations

#include <linaos/kernel.h>
#include <linaos/types.h>
#include <linaos/interrupt.h>
#include <linaos/list.h>
#include <linaos/timer.h>
#include <linaos/init.h>
#include <linaos/device.h>
#include <linaos/io.h>

#include <asm/mach/arch.h>
#include <asm/mach/map.h>

#include "map.h"
#include "regs-gpio.h"

#include <asm/mach-types.h>

#include "pm.h"

#include "regs-mem-s3c24xx.h"

#define COPYRIGHT ", Copyright 2005 Simtec Electronics"

/* pm_simtec_init
 *
 * enable the power management functions
*/

static __init int pm_simtec_init(void)
{
	unsigned long gstatus4;

	/* check which machine we are running on */

	if (!machine_is_bast() && !machine_is_vr1000() &&
	    !machine_is_anubis() && !machine_is_osiris() &&
	    !machine_is_aml_m5900())
		return 0;

	printk(KERN_INFO "Simtec Board Power Management" COPYRIGHT "\n");

	gstatus4  = (__raw_readl(S3C2410_BANKCON7) & 0x3) << 30;
	gstatus4 |= (__raw_readl(S3C2410_BANKCON6) & 0x3) << 28;
	gstatus4 |= (__raw_readl(S3C2410_BANKSIZE) & S3C2410_BANKSIZE_MASK);

	__raw_writel(gstatus4, S3C2410_GSTATUS4);

	return s3c_pm_init();
}

arch_initcall(pm_simtec_init);
