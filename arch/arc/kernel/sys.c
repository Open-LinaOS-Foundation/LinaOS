// SPDX-License-Identifier: GPL-2.0

#include <linaos/syscalls.h>
#include <linaos/signal.h>
#include <linaos/unistd.h>

#include <asm/syscalls.h>

#define sys_clone	sys_clone_wrapper
#define sys_clone3	sys_clone3_wrapper

#undef __SYSCALL
#define __SYSCALL(nr, call) [nr] = (call),

void *sys_call_table[NR_syscalls] = {
	[0 ... NR_syscalls-1] = sys_ni_syscall,
#include <asm/unistd.h>
};
