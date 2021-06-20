/* SPDX-License-Identifier: GPL-2.0-or-later */
#ifndef _ASM_X86_IOMAP_H
#define _ASM_X86_IOMAP_H

/*
 * Copyright © 2008 Ingo Molnar
 */

#include <linaos/fs.h>
#include <linaos/mm.h>
#include <linaos/uaccess.h>
#include <linaos/highmem.h>
#include <asm/cacheflush.h>
#include <asm/tlbflush.h>

void __iomem *__iomap_local_pfn_prot(unsigned long pfn, pgprot_t prot);

int iomap_create_wc(resource_size_t base, unsigned long size, pgprot_t *prot);

void iomap_free(resource_size_t base, unsigned long size);

#endif /* _ASM_X86_IOMAP_H */
