// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2005-2017 Andes Technology Corporation

#include <linaos/module.h>
#include <linaos/string.h>
#include <linaos/delay.h>
#include <linaos/in6.h>
#include <linaos/syscalls.h>
#include <linaos/uaccess.h>

#include <asm/checksum.h>
#include <asm/io.h>
#include <asm/ftrace.h>
#include <asm/proc-fns.h>

/* mem functions */
EXPORT_SYMBOL(memset);
EXPORT_SYMBOL(memcpy);
EXPORT_SYMBOL(memmove);
EXPORT_SYMBOL(memzero);

/* user mem (segment) */
EXPORT_SYMBOL(__arch_copy_from_user);
EXPORT_SYMBOL(__arch_copy_to_user);
EXPORT_SYMBOL(__arch_clear_user);
