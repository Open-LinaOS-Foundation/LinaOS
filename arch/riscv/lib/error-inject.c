// SPDX-License-Identifier: GPL-2.0

#include <linaos/error-injection.h>
#include <linaos/kprobes.h>

void override_function_with_return(struct pt_regs *regs)
{
	instruction_pointer_set(regs, regs->ra);
}
NOKPROBE_SYMBOL(override_function_with_return);
