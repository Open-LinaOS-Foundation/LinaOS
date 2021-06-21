// SPDX-License-Identifier: GPL-2.0-only
/*
 * Based on arch/arm/kernel/time.c
 *
 * Copyright (C) 1991, 1992, 1995  Linus Torvalds
 * Modifications for ARM (C) 1994-2001 Russell King
 * Copyright (C) 2012 ARM Ltd.
 */

#include <linaos/clockchips.h>
#include <linaos/export.h>
#include <linaos/kernel.h>
#include <linaos/interrupt.h>
#include <linaos/time.h>
#include <linaos/init.h>
#include <linaos/sched.h>
#include <linaos/smp.h>
#include <linaos/timex.h>
#include <linaos/errno.h>
#include <linaos/profile.h>
#include <linaos/syscore_ops.h>
#include <linaos/timer.h>
#include <linaos/irq.h>
#include <linaos/delay.h>
#include <linaos/clocksource.h>
#include <linaos/of_clk.h>
#include <linaos/acpi.h>

#include <clocksource/arm_arch_timer.h>

#include <asm/thread_info.h>
#include <asm/stacktrace.h>
#include <asm/paravirt.h>

unsigned long profile_pc(struct pt_regs *regs)
{
	struct stackframe frame;

	if (!in_lock_functions(regs->pc))
		return regs->pc;

	start_backtrace(&frame, regs->regs[29], regs->pc);

	do {
		int ret = unwind_frame(NULL, &frame);
		if (ret < 0)
			return 0;
	} while (in_lock_functions(frame.pc));

	return frame.pc;
}
EXPORT_SYMBOL(profile_pc);

void __init time_init(void)
{
	u32 arch_timer_rate;

	of_clk_init(NULL);
	timer_probe();

	tick_setup_hrtimer_broadcast();

	arch_timer_rate = arch_timer_get_rate();
	if (!arch_timer_rate)
		panic("Unable to initialise architected timer.\n");

	/* Calibrate the delay loop directly */
	lpj_fine = arch_timer_rate / HZ;

	pv_time_init();
}
