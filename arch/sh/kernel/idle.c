// SPDX-License-Identifier: GPL-2.0
/*
 * The idle loop for all SuperH platforms.
 *
 *  Copyright (C) 2002 - 2009  Paul Mundt
 */
#include <linaos/module.h>
#include <linaos/init.h>
#include <linaos/mm.h>
#include <linaos/pm.h>
#include <linaos/tick.h>
#include <linaos/preempt.h>
#include <linaos/thread_info.h>
#include <linaos/irqflags.h>
#include <linaos/smp.h>
#include <linaos/atomic.h>
#include <asm/smp.h>
#include <asm/bl_bit.h>

static void (*sh_idle)(void);

void default_idle(void)
{
	set_bl_bit();
	raw_local_irq_enable();
	/* Isn't this racy ? */
	cpu_sleep();
	clear_bl_bit();
}

void arch_cpu_idle_dead(void)
{
	play_dead();
}

void arch_cpu_idle(void)
{
	sh_idle();
}

void __init select_idle_routine(void)
{
	/*
	 * If a platform has set its own idle routine, leave it alone.
	 */
	if (!sh_idle)
		sh_idle = default_idle;
}

void stop_this_cpu(void *unused)
{
	local_irq_disable();
	set_cpu_online(smp_processor_id(), false);

	for (;;)
		cpu_sleep();
}
