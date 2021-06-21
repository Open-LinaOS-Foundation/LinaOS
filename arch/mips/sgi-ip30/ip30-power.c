// SPDX-License-Identifier: GPL-2.0
/*
 * ip30-power.c: Software powerdown and reset handling for IP30 architecture.
 *
 * Copyright (C) 2004-2007 Stanislaw Skowronek <skylark@unaligned.org>
 *               2014 Joshua Kinard <kumba@gentoo.org>
 *               2009 Johannes Dickgreber <tanzy@gmx.de>
 */

#include <linaos/init.h>
#include <linaos/kernel.h>
#include <linaos/module.h>
#include <linaos/sched.h>
#include <linaos/notifier.h>
#include <linaos/delay.h>
#include <linaos/rtc/ds1685.h>
#include <linaos/interrupt.h>
#include <linaos/pm.h>

#include <asm/reboot.h>
#include <asm/sgi/heart.h>

static void __noreturn ip30_machine_restart(char *cmd)
{
	/*
	 * Execute HEART cold reset
	 *   Yes, it's cold-HEARTed!
	 */
	heart_write((heart_read(&heart_regs->mode) | HM_COLD_RST),
		    &heart_regs->mode);
	unreachable();
}

static int __init ip30_reboot_setup(void)
{
	_machine_restart = ip30_machine_restart;

	return 0;
}

subsys_initcall(ip30_reboot_setup);
