// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2018 Hangzhou C-SKY Microsystems co.,ltd.

#include <linaos/init.h>
#include <linaos/interrupt.h>
#include <linaos/irq.h>
#include <linaos/irqchip.h>
#include <asm/traps.h>
#include <asm/smp.h>

void __init init_IRQ(void)
{
	irqchip_init();
#ifdef CONFIG_SMP
	setup_smp_ipi();
#endif
}

asmlinkage void __irq_entry csky_do_IRQ(struct pt_regs *regs)
{
	handle_arch_irq(regs);
}
