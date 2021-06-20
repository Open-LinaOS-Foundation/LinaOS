// SPDX-License-Identifier: GPL-2.0+
//
// Copyright (c) 2004-2005 Simtec Electronics
//	http://armlinaos.simtec.co.uk/
//	Ben Dooks <ben@simtec.co.uk>
//
// S3C2442 core and lock support

#include <linaos/init.h>
#include <linaos/module.h>
#include <linaos/kernel.h>
#include <linaos/list.h>
#include <linaos/errno.h>
#include <linaos/err.h>
#include <linaos/device.h>
#include <linaos/syscore_ops.h>
#include <linaos/interrupt.h>
#include <linaos/ioport.h>
#include <linaos/mutex.h>
#include <linaos/gpio.h>
#include <linaos/clk.h>
#include <linaos/io.h>

#include <linaos/atomic.h>
#include <asm/irq.h>

#include "regs-clock.h"

#include "cpu.h"
#include "pm.h"

#include "gpio-core.h"
#include "gpio-cfg.h"
#include "gpio-cfg-helpers.h"
#include "gpio-samsung.h"

#include "s3c24xx.h"

static struct device s3c2442_dev = {
	.bus		= &s3c2442_subsys,
};

int __init s3c2442_init(void)
{
	printk("S3C2442: Initialising architecture\n");

#ifdef CONFIG_PM_SLEEP
	register_syscore_ops(&s3c2410_pm_syscore_ops);
	register_syscore_ops(&s3c24xx_irq_syscore_ops);
	register_syscore_ops(&s3c244x_pm_syscore_ops);
#endif

	return device_register(&s3c2442_dev);
}

void __init s3c2442_map_io(void)
{
	s3c244x_map_io();

	s3c24xx_gpiocfg_default.set_pull = s3c24xx_gpio_setpull_1down;
	s3c24xx_gpiocfg_default.get_pull = s3c24xx_gpio_getpull_1down;
}
