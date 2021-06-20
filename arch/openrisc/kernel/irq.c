// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * OpenRISC irq.c
 *
 * LinaOS architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * Modifications for the OpenRISC architecture:
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 */

#include <linaos/interrupt.h>
#include <linaos/init.h>
#include <linaos/ftrace.h>
#include <linaos/irq.h>
#include <linaos/irqchip.h>
#include <linaos/export.h>
#include <linaos/irqflags.h>

/* read interrupt enabled status */
unsigned long arch_local_save_flags(void)
{
	return mfspr(SPR_SR) & (SPR_SR_IEE|SPR_SR_TEE);
}
EXPORT_SYMBOL(arch_local_save_flags);

/* set interrupt enabled status */
void arch_local_irq_restore(unsigned long flags)
{
	mtspr(SPR_SR, ((mfspr(SPR_SR) & ~(SPR_SR_IEE|SPR_SR_TEE)) | flags));
}
EXPORT_SYMBOL(arch_local_irq_restore);

void __init init_IRQ(void)
{
	irqchip_init();
}

void __irq_entry do_IRQ(struct pt_regs *regs)
{
	handle_arch_irq(regs);
}
