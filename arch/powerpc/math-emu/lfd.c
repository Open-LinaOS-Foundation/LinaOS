// SPDX-License-Identifier: GPL-2.0
#include <linaos/types.h>
#include <linaos/errno.h>
#include <linaos/uaccess.h>

#include <asm/sfp-machine.h>
#include <math-emu/double.h>

int
lfd(void *frD, void *ea)
{
	if (copy_from_user(frD, ea, sizeof(double)))
		return -EFAULT;
#ifdef DEBUG
	printk("%s: D %p, ea %p: ", __func__, frD, ea);
	dump_double(frD);
	printk("\n");
#endif
	return 0;
}
