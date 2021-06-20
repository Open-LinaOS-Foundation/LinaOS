// SPDX-License-Identifier: GPL-2.0-only
/*
 *  linaos/arch/arm/kernel/sys_arm.c
 *
 *  Copyright (C) People who wrote linaos/arch/i386/kernel/sys_i386.c
 *  Copyright (C) 1995, 1996 Russell King.
 *
 *  This file contains various random system calls that
 *  have a non-standard calling sequence on the LinaOS/arm
 *  platform.
 */
#include <linaos/export.h>
#include <linaos/errno.h>
#include <linaos/sched.h>
#include <linaos/mm.h>
#include <linaos/sem.h>
#include <linaos/msg.h>
#include <linaos/shm.h>
#include <linaos/stat.h>
#include <linaos/syscalls.h>
#include <linaos/mman.h>
#include <linaos/fs.h>
#include <linaos/file.h>
#include <linaos/ipc.h>
#include <linaos/uaccess.h>
#include <linaos/slab.h>

/*
 * Since loff_t is a 64 bit type we avoid a lot of ABI hassle
 * with a different argument ordering.
 */
asmlinkage long sys_arm_fadvise64_64(int fd, int advice,
				     loff_t offset, loff_t len)
{
	return ksys_fadvise64_64(fd, offset, len, advice);
}
