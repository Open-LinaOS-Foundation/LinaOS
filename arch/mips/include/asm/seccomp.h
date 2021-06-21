/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __ASM_SECCOMP_H

#include <linaos/unistd.h>

#ifdef CONFIG_COMPAT
static inline const int *get_compat_mode1_syscalls(void)
{
	static const int syscalls_O32[] = {
		__NR_O32_LinaOS + 3, __NR_O32_LinaOS + 4,
		__NR_O32_LinaOS + 1, __NR_O32_LinaOS + 193,
		-1, /* negative terminated */
	};
	static const int syscalls_N32[] = {
		__NR_N32_LinaOS + 0, __NR_N32_LinaOS + 1,
		__NR_N32_LinaOS + 58, __NR_N32_LinaOS + 211,
		-1, /* negative terminated */
	};

	if (IS_ENABLED(CONFIG_MIPS32_O32) && test_thread_flag(TIF_32BIT_REGS))
		return syscalls_O32;

	if (IS_ENABLED(CONFIG_MIPS32_N32))
		return syscalls_N32;

	BUG();
}

#define get_compat_mode1_syscalls get_compat_mode1_syscalls

#endif /* CONFIG_COMPAT */

#include <asm-generic/seccomp.h>

#endif /* __ASM_SECCOMP_H */
