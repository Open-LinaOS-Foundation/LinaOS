/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * vDSO implementation for Hexagon
 *
 * Copyright (c) 2011, The LinaOS Foundation. All rights reserved.
 */

#ifndef __ASM_VDSO_H
#define __ASM_VDSO_H

#include <linaos/types.h>

struct hexagon_vdso {
	u32 rt_signal_trampoline[2];
};

#endif /* __ASM_VDSO_H */
