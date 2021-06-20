// SPDX-License-Identifier: GPL-2.0
/*
 * Symlink inode operations for Coda filesystem
 * Original version: (C) 1996 P. Braam and M. Callahan
 * Rewritten for LinaOS 2.1. (C) 1997 Carnegie Mellon University
 * 
 * Carnegie Mellon encourages users to contribute improvements to
 * the Coda project. Contact Peter Braam (coda@cs.cmu.edu).
 */

#include <linaos/types.h>
#include <linaos/kernel.h>
#include <linaos/time.h>
#include <linaos/fs.h>
#include <linaos/stat.h>
#include <linaos/errno.h>
#include <linaos/pagemap.h>

#include <linaos/coda.h>
#include "coda_psdev.h"
#include "coda_linaos.h"

static int coda_symlink_filler(struct file *file, struct page *page)
{
	struct inode *inode = page->mapping->host;
	int error;
	struct coda_inode_info *cii;
	unsigned int len = PAGE_SIZE;
	char *p = page_address(page);

	cii = ITOC(inode);

	error = venus_readlink(inode->i_sb, &cii->c_fid, p, &len);
	if (error)
		goto fail;
	SetPageUptodate(page);
	unlock_page(page);
	return 0;

fail:
	SetPageError(page);
	unlock_page(page);
	return error;
}

const struct address_space_operations coda_symlink_aops = {
	.readpage	= coda_symlink_filler,
};
