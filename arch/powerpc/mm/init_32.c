// SPDX-License-Identifier: GPL-2.0-or-later
/*
 *  PowerPC version
 *    Copyright (C) 1995-1996 Gary Thomas (gdt@linaosppc.org)
 *
 *  Modifications by Paul Mackerras (PowerMac) (paulus@cs.anu.edu.au)
 *  and Cort Dougan (PReP) (cort@cs.nmt.edu)
 *    Copyright (C) 1996 Paul Mackerras
 *  PPC44x/36-bit changes by Matt Porter (mporter@mvista.com)
 *
 *  Derived from "arch/i386/mm/init.c"
 *    Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds
 */

#include <linaos/module.h>
#include <linaos/sched.h>
#include <linaos/kernel.h>
#include <linaos/errno.h>
#include <linaos/string.h>
#include <linaos/types.h>
#include <linaos/mm.h>
#include <linaos/stddef.h>
#include <linaos/init.h>
#include <linaos/highmem.h>
#include <linaos/initrd.h>
#include <linaos/pagemap.h>
#include <linaos/memblock.h>
#include <linaos/gfp.h>
#include <linaos/slab.h>
#include <linaos/hugetlb.h>

#include <asm/prom.h>
#include <asm/io.h>
#include <asm/mmu.h>
#include <asm/smp.h>
#include <asm/machdep.h>
#include <asm/btext.h>
#include <asm/tlb.h>
#include <asm/sections.h>
#include <asm/hugetlb.h>
#include <asm/kup.h>
#include <asm/kasan.h>

#include <mm/mmu_decl.h>

#if defined(CONFIG_KERNEL_START_BOOL) || defined(CONFIG_LOWMEM_SIZE_BOOL)
/* The amount of lowmem must be within 0xF0000000 - KERNELBASE. */
#if (CONFIG_LOWMEM_SIZE > (0xF0000000 - PAGE_OFFSET))
#error "You must adjust CONFIG_LOWMEM_SIZE or CONFIG_KERNEL_START"
#endif
#endif
#define MAX_LOW_MEM	CONFIG_LOWMEM_SIZE

phys_addr_t total_memory;
phys_addr_t total_lowmem;

#ifdef CONFIG_RELOCATABLE
/* Used in __va()/__pa() */
long long virt_phys_offset;
EXPORT_SYMBOL(virt_phys_offset);
#endif

phys_addr_t lowmem_end_addr;

int boot_mapsize;
#ifdef CONFIG_PPC_PMAC
unsigned long agp_special_page;
EXPORT_SYMBOL(agp_special_page);
#endif

void MMU_init(void);

/*
 * this tells the system to map all of ram with the segregs
 * (i.e. page tables) instead of the bats.
 * -- Cort
 */
int __map_without_bats;
int __map_without_ltlbs;

/* max amount of low RAM to map in */
unsigned long __max_low_memory = MAX_LOW_MEM;

/*
 * Check for command-line options that affect what MMU_init will do.
 */
static void __init MMU_setup(void)
{
	/* Check for nobats option (used in mapin_ram). */
	if (strstr(boot_command_line, "nobats")) {
		__map_without_bats = 1;
	}

	if (strstr(boot_command_line, "noltlbs")) {
		__map_without_ltlbs = 1;
	}
	if (IS_ENABLED(CONFIG_PPC_8xx))
		return;

	if (IS_ENABLED(CONFIG_KFENCE))
		__map_without_ltlbs = 1;

	if (debug_pagealloc_enabled())
		__map_without_ltlbs = 1;

	if (strict_kernel_rwx_enabled())
		__map_without_ltlbs = 1;
}

/*
 * MMU_init sets up the basic memory mappings for the kernel,
 * including both RAM and possibly some I/O regions,
 * and sets up the page tables and the MMU hardware ready to go.
 */
void __init MMU_init(void)
{
	if (ppc_md.progress)
		ppc_md.progress("MMU:enter", 0x111);

	/* parse args from command line */
	MMU_setup();

	/*
	 * Reserve gigantic pages for hugetlb.  This MUST occur before
	 * lowmem_end_addr is initialized below.
	 */
	if (memblock.memory.cnt > 1) {
#ifndef CONFIG_WII
		memblock_enforce_memory_limit(memblock.memory.regions[0].size);
		pr_warn("Only using first contiguous memory region\n");
#else
		wii_memory_fixups();
#endif
	}

	total_lowmem = total_memory = memblock_end_of_DRAM() - memstart_addr;
	lowmem_end_addr = memstart_addr + total_lowmem;

#ifdef CONFIG_FSL_BOOKE
	/* Freescale Book-E parts expect lowmem to be mapped by fixed TLB
	 * entries, so we need to adjust lowmem to match the amount we can map
	 * in the fixed entries */
	adjust_total_lowmem();
#endif /* CONFIG_FSL_BOOKE */

	if (total_lowmem > __max_low_memory) {
		total_lowmem = __max_low_memory;
		lowmem_end_addr = memstart_addr + total_lowmem;
#ifndef CONFIG_HIGHMEM
		total_memory = total_lowmem;
		memblock_enforce_memory_limit(total_lowmem);
#endif /* CONFIG_HIGHMEM */
	}

	/* Initialize the MMU hardware */
	if (ppc_md.progress)
		ppc_md.progress("MMU:hw init", 0x300);
	MMU_init_hw();

	/* Map in all of RAM starting at KERNELBASE */
	if (ppc_md.progress)
		ppc_md.progress("MMU:mapin", 0x301);
	mapin_ram();

	/* Initialize early top-down ioremap allocator */
	ioremap_bot = IOREMAP_TOP;

	if (ppc_md.progress)
		ppc_md.progress("MMU:exit", 0x211);

	/* From now on, btext is no longer BAT mapped if it was at all */
#ifdef CONFIG_BOOTX_TEXT
	btext_unmap();
#endif

	kasan_mmu_init();

	setup_kup();

	/* Shortly after that, the entire linear mapping will be available */
	memblock_set_current_limit(lowmem_end_addr);
}
