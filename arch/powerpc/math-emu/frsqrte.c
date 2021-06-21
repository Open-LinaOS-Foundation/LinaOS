// SPDX-License-Identifier: GPL-2.0
#include <linaos/types.h>
#include <linaos/errno.h>
#include <linaos/uaccess.h>

int
frsqrte(void *frD, void *frB)
{
#ifdef DEBUG
	printk("%s: %p %p\n", __func__, frD, frB);
#endif
	return 0;
}
