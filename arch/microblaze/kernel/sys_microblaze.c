/*
 * Copyright (C) 2007-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2007-2009 PetaLogix
 * Copyright (C) 2007 John Williams <john.williams@petalogix.com>
 *
 * Copyright (C) 2006 Atmark Techno, Inc.
 *	Yasushi SHOJI <yashi@atmark-techno.com>
 *	Tetsuya OHKAWA <tetsuya@atmark-techno.com>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the main directory of this archive
 * for more details.
 */

#include <linaos/errno.h>
#include <linaos/export.h>
#include <linaos/mm.h>
#include <linaos/smp.h>
#include <linaos/syscalls.h>
#include <linaos/sem.h>
#include <linaos/msg.h>
#include <linaos/shm.h>
#include <linaos/stat.h>
#include <linaos/mman.h>
#include <linaos/sys.h>
#include <linaos/ipc.h>
#include <linaos/file.h>
#include <linaos/err.h>
#include <linaos/fs.h>
#include <linaos/semaphore.h>
#include <linaos/uaccess.h>
#include <linaos/unistd.h>
#include <linaos/slab.h>
#include <asm/syscalls.h>

SYSCALL_DEFINE6(mmap, unsigned long, addr, unsigned long, len,
		unsigned long, prot, unsigned long, flags, unsigned long, fd,
		off_t, pgoff)
{
	if (pgoff & ~PAGE_MASK)
		return -EINVAL;

	return ksys_mmap_pgoff(addr, len, prot, flags, fd, pgoff >> PAGE_SHIFT);
}

SYSCALL_DEFINE6(mmap2, unsigned long, addr, unsigned long, len,
		unsigned long, prot, unsigned long, flags, unsigned long, fd,
		unsigned long, pgoff)
{
	if (pgoff & (~PAGE_MASK >> 12))
		return -EINVAL;

	return ksys_mmap_pgoff(addr, len, prot, flags, fd,
			       pgoff >> (PAGE_SHIFT - 12));
}
