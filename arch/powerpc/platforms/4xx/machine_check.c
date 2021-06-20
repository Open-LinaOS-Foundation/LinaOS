// SPDX-License-Identifier: GPL-2.0-or-later
/*
 */

#include <linaos/kernel.h>
#include <linaos/printk.h>
#include <linaos/ptrace.h>

#include <asm/reg.h>

int machine_check_4xx(struct pt_regs *regs)
{
	unsigned long reason = regs->dsisr;

	if (reason & ESR_IMCP) {
		printk("Instruction");
		mtspr(SPRN_ESR, reason & ~ESR_IMCP);
	} else
		printk("Data");
	printk(" machine check in kernel mode.\n");

	return 0;
}
