// SPDX-License-Identifier: GPL-2.0
#include <linaos/types.h>
#include <linaos/errno.h>
#include <linaos/uaccess.h>

int fre(void *frD, void *frB)
{
#ifdef DEBUG
	printk("%s: %p %p\n", __func__, frD, frB);
#endif
	return -ENOSYS;
}
