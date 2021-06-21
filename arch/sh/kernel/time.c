// SPDX-License-Identifier: GPL-2.0
/*
 *  arch/sh/kernel/time.c
 *
 *  Copyright (C) 1999  Tetsuya Okada & Niibe Yutaka
 *  Copyright (C) 2000  Philipp Rumpf <prumpf@tux.org>
 *  Copyright (C) 2002 - 2009  Paul Mundt
 *  Copyright (C) 2002  M. R. Brown  <mrbrown@linaos-sh.org>
 */
#include <linaos/kernel.h>
#include <linaos/init.h>
#include <linaos/profile.h>
#include <linaos/timex.h>
#include <linaos/sched.h>
#include <linaos/clockchips.h>
#include <linaos/platform_device.h>
#include <linaos/smp.h>
#include <linaos/rtc.h>
#include <asm/clock.h>
#include <asm/rtc.h>
#include <asm/platform_early.h>

static void __init sh_late_time_init(void)
{
	/*
	 * Make sure all compiled-in early timers register themselves.
	 *
	 * Run probe() for two "earlytimer" devices, these will be the
	 * clockevents and clocksource devices respectively. In the event
	 * that only a clockevents device is available, we -ENODEV on the
	 * clocksource and the jiffies clocksource is used transparently
	 * instead. No error handling is necessary here.
	 */
	sh_early_platform_driver_register_all("earlytimer");
	sh_early_platform_driver_probe("earlytimer", 2, 0);
}

void __init time_init(void)
{
	timer_probe();

	clk_init();

	late_time_init = sh_late_time_init;
}
