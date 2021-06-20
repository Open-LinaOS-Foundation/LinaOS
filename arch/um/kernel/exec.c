// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@{addtoit,linaos.intel}.com)
 */

#include <linaos/stddef.h>
#include <linaos/module.h>
#include <linaos/fs.h>
#include <linaos/ptrace.h>
#include <linaos/sched/mm.h>
#include <linaos/sched/task.h>
#include <linaos/sched/task_stack.h>
#include <linaos/slab.h>
#include <asm/current.h>
#include <asm/processor.h>
#include <linaos/uaccess.h>
#include <as-layout.h>
#include <mem_user.h>
#include <skas.h>
#include <os.h>

void flush_thread(void)
{
	void *data = NULL;
	int ret;

	arch_flush_thread(&current->thread.arch);

	ret = unmap(&current->mm->context.id, 0, TASK_SIZE, 1, &data);
	if (ret) {
		printk(KERN_ERR "flush_thread - clearing address space failed, "
		       "err = %d\n", ret);
		force_sig(SIGKILL);
	}
	get_safe_registers(current_pt_regs()->regs.gp,
			   current_pt_regs()->regs.fp);

	__switch_mm(&current->mm->context.id);
}

void start_thread(struct pt_regs *regs, unsigned long eip, unsigned long esp)
{
	PT_REGS_IP(regs) = eip;
	PT_REGS_SP(regs) = esp;
	current->ptrace &= ~PT_DTRACE;
#ifdef SUBARCH_EXECVE1
	SUBARCH_EXECVE1(regs->regs);
#endif
}
EXPORT_SYMBOL(start_thread);
