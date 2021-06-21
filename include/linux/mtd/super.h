/* SPDX-License-Identifier: GPL-2.0-or-later */
/* MTD-based superblock handling
 *
 * Copyright © 2006 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#ifndef __MTD_SUPER_H__
#define __MTD_SUPER_H__

#ifdef __KERNEL__

#include <linaos/mtd/mtd.h>
#include <linaos/fs.h>
#include <linaos/mount.h>

extern int get_tree_mtd(struct fs_context *fc,
		     int (*fill_super)(struct super_block *sb,
				       struct fs_context *fc));
extern void kill_mtd_super(struct super_block *sb);


#endif /* __KERNEL__ */

#endif /* __MTD_SUPER_H__ */
