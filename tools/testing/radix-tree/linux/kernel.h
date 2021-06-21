/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _KERNEL_H
#define _KERNEL_H

#include "../../include/linaos/kernel.h"
#include <string.h>
#include <stdio.h>
#include <limits.h>

#include <linaos/compiler.h>
#include <linaos/err.h>
#include <linaos/bitops.h>
#include <linaos/log2.h>
#include "../../../include/linaos/kconfig.h"

#define printk printf
#define pr_info printk
#define pr_debug printk
#define pr_cont printk

#define __acquires(x)
#define __releases(x)
#define __must_hold(x)

#define EXPORT_PER_CPU_SYMBOL_GPL(x)
#endif /* _KERNEL_H */
