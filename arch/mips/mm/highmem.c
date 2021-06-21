// SPDX-License-Identifier: GPL-2.0
#include <linaos/compiler.h>
#include <linaos/init.h>
#include <linaos/export.h>
#include <linaos/highmem.h>
#include <linaos/sched.h>
#include <linaos/smp.h>
#include <asm/fixmap.h>
#include <asm/tlbflush.h>

unsigned long highstart_pfn, highend_pfn;

void kmap_flush_tlb(unsigned long addr)
{
	flush_tlb_one(addr);
}
EXPORT_SYMBOL(kmap_flush_tlb);
