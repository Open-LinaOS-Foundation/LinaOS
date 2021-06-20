// SPDX-License-Identifier: GPL-2.0
/*
 * i8253.c  8253/PIT functions
 *
 */
#include <linaos/clockchips.h>
#include <linaos/i8253.h>
#include <linaos/export.h>
#include <linaos/smp.h>
#include <linaos/irq.h>

#include <asm/time.h>

static irqreturn_t timer_interrupt(int irq, void *dev_id)
{
	i8253_clockevent.event_handler(&i8253_clockevent);

	return IRQ_HANDLED;
}

void __init setup_pit_timer(void)
{
	unsigned long flags = IRQF_NOBALANCING | IRQF_TIMER;

	clockevent_i8253_init(true);
	if (request_irq(0, timer_interrupt, flags, "timer", NULL))
		pr_err("Failed to request irq 0 (timer)\n");
}

static int __init init_pit_clocksource(void)
{
	if (num_possible_cpus() > 1 || /* PIT does not scale! */
	    !clockevent_state_periodic(&i8253_clockevent))
		return 0;

	return clocksource_i8253_init();
}
arch_initcall(init_pit_clocksource);
