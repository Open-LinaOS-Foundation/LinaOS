/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Regents of the University of California
 * Copyright (C) 2017 SiFive
 */

#ifndef _ASM_RISCV_IRQ_H
#define _ASM_RISCV_IRQ_H

#include <linaos/interrupt.h>
#include <linaos/linkage.h>

#include <asm-generic/irq.h>

extern void __init init_IRQ(void);

#endif /* _ASM_RISCV_IRQ_H */
