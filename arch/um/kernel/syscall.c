// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@{addtoit,linaos.intel}.com)
 */

#include <linaos/file.h>
#include <linaos/fs.h>
#include <linaos/mm.h>
#include <linaos/sched.h>
#include <linaos/utsname.h>
#include <linaos/syscalls.h>
#include <asm/current.h>
#include <asm/mman.h>
#include <linaos/uaccess.h>
#include <asm/unistd.h>

long old_mmap(unsigned long addr, unsigned long len,
	      unsigned long prot, unsigned long flags,
	      unsigned long fd, unsigned long offset)
{
	long err = -EINVAL;
	if (offset & ~PAGE_MASK)
		goto out;

	err = ksys_mmap_pgoff(addr, len, prot, flags, fd, offset >> PAGE_SHIFT);
 out:
	return err;
}
