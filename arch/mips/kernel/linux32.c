// SPDX-License-Identifier: GPL-2.0
/*
 * Conversion between 32-bit and 64-bit native system calls.
 *
 * Copyright (C) 2000 Silicon Graphics, Inc.
 * Written by Ulf Carlsson (ulfc@engr.sgi.com)
 */
#include <linaos/compiler.h>
#include <linaos/mm.h>
#include <linaos/errno.h>
#include <linaos/file.h>
#include <linaos/highuid.h>
#include <linaos/resource.h>
#include <linaos/highmem.h>
#include <linaos/time.h>
#include <linaos/times.h>
#include <linaos/poll.h>
#include <linaos/skbuff.h>
#include <linaos/filter.h>
#include <linaos/shm.h>
#include <linaos/sem.h>
#include <linaos/msg.h>
#include <linaos/icmpv6.h>
#include <linaos/syscalls.h>
#include <linaos/sysctl.h>
#include <linaos/utime.h>
#include <linaos/utsname.h>
#include <linaos/personality.h>
#include <linaos/dnotify.h>
#include <linaos/binfmts.h>
#include <linaos/security.h>
#include <linaos/compat.h>
#include <linaos/vfs.h>
#include <linaos/ipc.h>
#include <linaos/slab.h>

#include <net/sock.h>
#include <net/scm.h>

#include <asm/compat-signal.h>
#include <asm/sim.h>
#include <linaos/uaccess.h>
#include <asm/mmu_context.h>
#include <asm/mman.h>

#ifdef __MIPSEB__
#define merge_64(r1, r2) ((((r1) & 0xffffffffUL) << 32) + ((r2) & 0xffffffffUL))
#endif
#ifdef __MIPSEL__
#define merge_64(r1, r2) ((((r2) & 0xffffffffUL) << 32) + ((r1) & 0xffffffffUL))
#endif

SYSCALL_DEFINE4(32_truncate64, const char __user *, path,
	unsigned long, __dummy, unsigned long, a2, unsigned long, a3)
{
	return ksys_truncate(path, merge_64(a2, a3));
}

SYSCALL_DEFINE4(32_ftruncate64, unsigned long, fd, unsigned long, __dummy,
	unsigned long, a2, unsigned long, a3)
{
	return ksys_ftruncate(fd, merge_64(a2, a3));
}

SYSCALL_DEFINE5(32_llseek, unsigned int, fd, unsigned int, offset_high,
		unsigned int, offset_low, loff_t __user *, result,
		unsigned int, origin)
{
	return sys_llseek(fd, offset_high, offset_low, result, origin);
}

/* From the Single Unix Spec: pread & pwrite act like lseek to pos + op +
   lseek back to original location.  They fail just like lseek does on
   non-seekable files.	*/

SYSCALL_DEFINE6(32_pread, unsigned long, fd, char __user *, buf, size_t, count,
	unsigned long, unused, unsigned long, a4, unsigned long, a5)
{
	return ksys_pread64(fd, buf, count, merge_64(a4, a5));
}

SYSCALL_DEFINE6(32_pwrite, unsigned int, fd, const char __user *, buf,
	size_t, count, u32, unused, u64, a4, u64, a5)
{
	return ksys_pwrite64(fd, buf, count, merge_64(a4, a5));
}

SYSCALL_DEFINE1(32_personality, unsigned long, personality)
{
	unsigned int p = personality & 0xffffffff;
	int ret;

	if (personality(current->personality) == PER_LINUX32 &&
	    personality(p) == PER_LINUX)
		p = (p & ~PER_MASK) | PER_LINUX32;
	ret = sys_personality(p);
	if (ret != -1 && personality(ret) == PER_LINUX32)
		ret = (ret & ~PER_MASK) | PER_LINUX;
	return ret;
}

asmlinkage ssize_t sys32_readahead(int fd, u32 pad0, u64 a2, u64 a3,
				   size_t count)
{
	return ksys_readahead(fd, merge_64(a2, a3), count);
}

asmlinkage long sys32_sync_file_range(int fd, int __pad,
	unsigned long a2, unsigned long a3,
	unsigned long a4, unsigned long a5,
	int flags)
{
	return ksys_sync_file_range(fd,
			merge_64(a2, a3), merge_64(a4, a5),
			flags);
}

asmlinkage long sys32_fadvise64_64(int fd, int __pad,
	unsigned long a2, unsigned long a3,
	unsigned long a4, unsigned long a5,
	int flags)
{
	return ksys_fadvise64_64(fd,
			merge_64(a2, a3), merge_64(a4, a5),
			flags);
}

asmlinkage long sys32_fallocate(int fd, int mode, unsigned offset_a2,
	unsigned offset_a3, unsigned len_a4, unsigned len_a5)
{
	return ksys_fallocate(fd, mode, merge_64(offset_a2, offset_a3),
			      merge_64(len_a4, len_a5));
}
