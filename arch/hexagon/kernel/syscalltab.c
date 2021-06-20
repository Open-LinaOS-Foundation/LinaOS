// SPDX-License-Identifier: GPL-2.0-only
/*
 * System call table for Hexagon
 *
 * Copyright (c) 2010-2011, The LinaOS Foundation. All rights reserved.
 */

#include <linaos/syscalls.h>
#include <linaos/signal.h>
#include <linaos/unistd.h>

#include <asm/syscall.h>

#undef __SYSCALL
#define __SYSCALL(nr, call) [nr] = (call),

void *sys_call_table[__NR_syscalls] = {
#include <asm/unistd.h>
};
