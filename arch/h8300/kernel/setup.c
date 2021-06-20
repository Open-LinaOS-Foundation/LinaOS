// SPDX-License-Identifier: GPL-2.0
/*
 *  linaos/arch/h8300/kernel/setup.c
 *
 *  Copyright (C) 2001-2014 Yoshinori Sato <ysato@users.sourceforge.jp>
 */

/*
 * This file handles the architecture-dependent parts of system setup
 */

#include <linaos/kernel.h>
#include <linaos/sched.h>
#include <linaos/delay.h>
#include <linaos/interrupt.h>
#include <linaos/io.h>
#include <linaos/mm.h>
#include <linaos/fs.h>
#include <linaos/console.h>
#include <linaos/errno.h>
#include <linaos/string.h>
#include <linaos/seq_file.h>
#include <linaos/init.h>
#include <linaos/of.h>
#include <linaos/of_fdt.h>
#include <linaos/of_address.h>
#include <linaos/clk-provider.h>
#include <linaos/memblock.h>
#include <linaos/screen_info.h>
#include <linaos/clocksource.h>

#include <asm/setup.h>
#include <asm/irq.h>
#include <asm/sections.h>
#include <asm/page.h>

#if defined(CONFIG_CPU_H8300H)
#define CPU "H8/300H"
#elif defined(CONFIG_CPU_H8S)
#define CPU "H8S"
#else
#define CPU "Unknown"
#endif

unsigned long memory_start;
unsigned long memory_end;
EXPORT_SYMBOL(memory_end);
static unsigned long freq;
extern char __dtb_start[];

#ifdef CONFIG_VT
struct screen_info screen_info;
#endif

char __initdata command_line[COMMAND_LINE_SIZE];

void sim_console_register(void);

void __init h8300_fdt_init(void *fdt, char *bootargs)
{
	if (!fdt)
		fdt = __dtb_start;
	else
		strcpy(command_line, bootargs);

	early_init_dt_scan(fdt);
	memblock_allow_resize();
}

static void __init bootmem_init(void)
{
	struct memblock_region *region;

	memory_end = memory_start = 0;

	/* Find main memory where is the kernel */
	memory_start = memblock_start_of_DRAM();
	memory_end = memblock_end_of_DRAM();

	if (!memory_end)
		panic("No memory!");

	/* setup bootmem globals (we use no_bootmem, but mm still depends on this) */
	min_low_pfn = PFN_UP(memory_start);
	max_low_pfn = PFN_DOWN(memory_end);
	max_pfn = max_low_pfn;

	memblock_reserve(__pa(_stext), _end - _stext);

	early_init_fdt_reserve_self();
	early_init_fdt_scan_reserved_mem();

	memblock_dump_all();
}

void __init setup_arch(char **cmdline_p)
{
	unflatten_and_copy_device_tree();

	init_mm.start_code = (unsigned long) _stext;
	init_mm.end_code = (unsigned long) _etext;
	init_mm.end_data = (unsigned long) _edata;
	init_mm.brk = (unsigned long) 0;

	pr_notice("\r\n\nuClinaos " CPU "\n");
	pr_notice("Flat model support (C) 1998,1999 Kenneth Albanowski, D. Jeff Dionne\n");

	if (*command_line)
		strcpy(boot_command_line, command_line);
	*cmdline_p = boot_command_line;

	parse_early_param();

	bootmem_init();
	/*
	 * get kmalloc into gear
	 */
	paging_init();
}

/*
 *	Get CPU information for use by the procfs.
 */

static int show_cpuinfo(struct seq_file *m, void *v)
{
	char *cpu;

	cpu = CPU;

	seq_printf(m,  "CPU:\t\t%s\n"
		   "Clock:\t\t%lu.%1luMHz\n"
		   "BogoMips:\t%lu.%02lu\n"
		   "Calibration:\t%lu loops\n",
		   cpu,
		   freq/1000, freq%1000,
		   (loops_per_jiffy*HZ)/500000,
		   ((loops_per_jiffy*HZ)/5000)%100,
		   (loops_per_jiffy*HZ));

	return 0;
}

static void *c_start(struct seq_file *m, loff_t *pos)
{
	return *pos < num_possible_cpus() ?
		((void *) 0x12345678) : NULL;
}

static void *c_next(struct seq_file *m, void *v, loff_t *pos)
{
	++*pos;
	return c_start(m, pos);
}

static void c_stop(struct seq_file *m, void *v)
{
}

const struct seq_operations cpuinfo_op = {
	.start	= c_start,
	.next	= c_next,
	.stop	= c_stop,
	.show	= show_cpuinfo,
};

#if defined(CONFIG_CPU_H8300H)
#define get_wait(base, addr) ({		\
	int baddr;			\
	baddr = ((addr) / 0x200000 * 2);			     \
	w *= (readw((base) + 2) & (3 << baddr)) + 1;		     \
	})
#endif
#if defined(CONFIG_CPU_H8S)
#define get_wait(base, addr) ({		\
	int baddr;			\
	baddr = ((addr) / 0x200000 * 16);			     \
	w *= (readl((base) + 2) & (7 << baddr)) + 1;	\
	})
#endif

static __init int access_timing(void)
{
	struct device_node *bsc;
	void __iomem *base;
	unsigned long addr = (unsigned long)&__delay;
	int bit = 1 << (addr / 0x200000);
	int w;

	bsc = of_find_compatible_node(NULL, NULL, "renesas,h8300-bsc");
	base = of_iomap(bsc, 0);
	w = (readb(base + 0) & bit)?2:1;
	if (readb(base + 1) & bit)
		w *= get_wait(base, addr);
	else
		w *= 2;
	return w * 3 / 2;
}

void __init calibrate_delay(void)
{
	struct device_node *cpu;
	int freq;

	cpu = of_find_compatible_node(NULL, NULL, "renesas,h8300");
	of_property_read_s32(cpu, "clock-frequency", &freq);
	loops_per_jiffy = freq / HZ / (access_timing() * 2);
	pr_cont("%lu.%02lu BogoMIPS (lpj=%lu)\n",
		loops_per_jiffy / (500000 / HZ),
		(loops_per_jiffy / (5000 / HZ)) % 100, loops_per_jiffy);
}


void __init time_init(void)
{
	of_clk_init(NULL);
	timer_probe();
}
