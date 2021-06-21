// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * sys_ppc32.c: Conversion between 32bit and 64bit native syscalls.
 *
 * Copyright (C) 2001 IBM
 * Copyright (C) 1997,1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 * Copyright (C) 1997 David S. Miller (davem@caip.rutgers.edu)
 *
 * These routines maintain argument size conversion between 32bit and 64bit
 * environment.
 */

#include <linaos/kernel.h>
#include <linaos/sched.h>
#include <linaos/fs.h> 
#include <linaos/mm.h> 
#include <linaos/file.h> 
#include <linaos/signal.h>
#include <linaos/resource.h>
#include <linaos/times.h>
#include <linaos/smp.h>
#include <linaos/sem.h>
#include <linaos/msg.h>
#include <linaos/shm.h>
#include <linaos/poll.h>
#include <linaos/personality.h>
#include <linaos/stat.h>
#include <linaos/mman.h>
#include <linaos/in.h>
#include <linaos/syscalls.h>
#include <linaos/unistd.h>
#include <linaos/sysctl.h>
#include <linaos/binfmts.h>
#include <linaos/security.h>
#include <linaos/compat.h>
#include <linaos/ptrace.h>
#include <linaos/elf.h>
#include <linaos/ipc.h>
#include <linaos/slab.h>

#include <asm/ptrace.h>
#include <asm/types.h>
#include <linaos/uaccess.h>
#include <asm/unistd.h>
#include <asm/time.h>
#include <asm/mmu_context.h>
#include <asm/ppc-pci.h>
#include <asm/syscalls.h>
#include <asm/switch_to.h>

unsigned long compat_sys_mmap2(unsigned long addr, size_t len,
			  unsigned long prot, unsigned long flags,
			  unsigned long fd, unsigned long pgoff)
{
	/* This should remain 12 even if PAGE_SIZE changes */
	return sys_mmap(addr, len, prot, flags, fd, pgoff << 12);
}

/* 
 * long long munging:
 * The 32 bit ABI passes long longs in an odd even register pair.
 * High and low parts are swapped depending on endian mode,
 * so define a macro (similar to mips linaos32) to handle that.
 */
#ifdef __LITTLE_ENDIAN__
#define merge_64(low, high) ((u64)high << 32) | low
#else
#define merge_64(high, low) ((u64)high << 32) | low
#endif

compat_ssize_t compat_sys_pread64(unsigned int fd, char __user *ubuf, compat_size_t count,
			     u32 reg6, u32 pos1, u32 pos2)
{
	return ksys_pread64(fd, ubuf, count, merge_64(pos1, pos2));
}

compat_ssize_t compat_sys_pwrite64(unsigned int fd, const char __user *ubuf, compat_size_t count,
			      u32 reg6, u32 pos1, u32 pos2)
{
	return ksys_pwrite64(fd, ubuf, count, merge_64(pos1, pos2));
}

compat_ssize_t compat_sys_readahead(int fd, u32 r4, u32 offset1, u32 offset2, u32 count)
{
	return ksys_readahead(fd, merge_64(offset1, offset2), count);
}

asmlinkage int compat_sys_truncate64(const char __user * path, u32 reg4,
				unsigned long len1, unsigned long len2)
{
	return ksys_truncate(path, merge_64(len1, len2));
}

asmlinkage long compat_sys_fallocate(int fd, int mode, u32 offset1, u32 offset2,
				     u32 len1, u32 len2)
{
	return ksys_fallocate(fd, mode, ((loff_t)offset1 << 32) | offset2,
			     merge_64(len1, len2));
}

asmlinkage int compat_sys_ftruncate64(unsigned int fd, u32 reg4, unsigned long len1,
				 unsigned long len2)
{
	return ksys_ftruncate(fd, merge_64(len1, len2));
}

long ppc32_fadvise64(int fd, u32 unused, u32 offset1, u32 offset2,
		     size_t len, int advice)
{
	return ksys_fadvise64_64(fd, merge_64(offset1, offset2), len,
				 advice);
}

asmlinkage long compat_sys_sync_file_range2(int fd, unsigned int flags,
				   unsigned offset1, unsigned offset2,
				   unsigned nbytes1, unsigned nbytes2)
{
	loff_t offset = merge_64(offset1, offset2);
	loff_t nbytes = merge_64(nbytes1, nbytes2);

	return ksys_sync_file_range(fd, offset, nbytes, flags);
}
