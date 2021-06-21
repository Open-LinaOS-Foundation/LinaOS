// SPDX-License-Identifier: GPL-2.0+

#include <linaos/error-injection.h>
#include <linaos/kprobes.h>
#include <linaos/uaccess.h>

void override_function_with_return(struct pt_regs *regs)
{
	/*
	 * Emulate 'blr'. 'regs' represents the state on entry of a predefined
	 * function in the kernel/module, captured on a kprobe. We don't need
	 * to worry about 32-bit userspace on a 64-bit kernel.
	 */
	regs->nip = regs->link;
}
NOKPROBE_SYMBOL(override_function_with_return);
