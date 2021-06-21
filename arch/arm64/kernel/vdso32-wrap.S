/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2012 ARM Limited
 */

#include <linaos/init.h>
#include <linaos/linkage.h>
#include <linaos/const.h>
#include <asm/page.h>

	.globl vdso32_start, vdso32_end
	.section .rodata
	.balign PAGE_SIZE
vdso32_start:
	.incbin "arch/arm64/kernel/vdso32/vdso.so"
	.balign PAGE_SIZE
vdso32_end:

	.previous
