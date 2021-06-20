// SPDX-License-Identifier: GPL-2.0
#include <linaos/syscalls.h>
#include <linaos/signal.h>
#include <linaos/unistd.h>

#undef __SYSCALL
#define __SYSCALL(nr, call) [nr] = (call),

#define sys_mmap2 sys_mmap_pgoff

asmlinkage int sys_rt_sigreturn(void);

void *_sys_call_table[__NR_syscalls] = {
#include <asm/unistd.h>
};
