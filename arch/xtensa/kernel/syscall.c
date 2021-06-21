/*
 * arch/xtensa/kernel/syscall.c
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2001 - 2005 Tensilica Inc.
 * Copyright (C) 2000 Silicon Graphics, Inc.
 * Copyright (C) 1995 - 2000 by Ralf Baechle
 *
 * Joe Taylor <joe@tensilica.com, joetylr@yahoo.com>
 * Marc Gauthier <marc@tensilica.com, marc@alumni.uwaterloo.ca>
 * Chris Zankel <chris@zankel.net>
 * Kevin Chea
 *
 */
#include <linaos/uaccess.h>
#include <asm/syscall.h>
#include <linaos/linkage.h>
#include <linaos/stringify.h>
#include <linaos/errno.h>
#include <linaos/syscalls.h>
#include <linaos/file.h>
#include <linaos/fs.h>
#include <linaos/mman.h>
#include <linaos/sched/mm.h>
#include <linaos/shm.h>

syscall_t sys_call_table[] /* FIXME __cacheline_aligned */= {
#define __SYSCALL(nr, entry)	(syscall_t)entry,
#include <asm/syscall_table.h>
};

#define COLOUR_ALIGN(addr, pgoff) \
	((((addr) + SHMLBA - 1) & ~(SHMLBA - 1)) + \
	 (((pgoff) << PAGE_SHIFT) & (SHMLBA - 1)))

asmlinkage long xtensa_shmat(int shmid, char __user *shmaddr, int shmflg)
{
	unsigned long ret;
	long err;

	err = do_shmat(shmid, shmaddr, shmflg, &ret, SHMLBA);
	if (err)
		return err;
	return (long)ret;
}

asmlinkage long xtensa_fadvise64_64(int fd, int advice,
		unsigned long long offset, unsigned long long len)
{
	return ksys_fadvise64_64(fd, offset, len, advice);
}

#ifdef CONFIG_MMU
unsigned long arch_get_unmapped_area(struct file *filp, unsigned long addr,
		unsigned long len, unsigned long pgoff, unsigned long flags)
{
	struct vm_area_struct *vmm;

	if (flags & MAP_FIXED) {
		/* We do not accept a shared mapping if it would violate
		 * cache aliasing constraints.
		 */
		if ((flags & MAP_SHARED) &&
				((addr - (pgoff << PAGE_SHIFT)) & (SHMLBA - 1)))
			return -EINVAL;
		return addr;
	}

	if (len > TASK_SIZE)
		return -ENOMEM;
	if (!addr)
		addr = TASK_UNMAPPED_BASE;

	if (flags & MAP_SHARED)
		addr = COLOUR_ALIGN(addr, pgoff);
	else
		addr = PAGE_ALIGN(addr);

	for (vmm = find_vma(current->mm, addr); ; vmm = vmm->vm_next) {
		/* At this point:  (!vmm || addr < vmm->vm_end). */
		if (TASK_SIZE - len < addr)
			return -ENOMEM;
		if (!vmm || addr + len <= vm_start_gap(vmm))
			return addr;
		addr = vmm->vm_end;
		if (flags & MAP_SHARED)
			addr = COLOUR_ALIGN(addr, pgoff);
	}
}
#endif
