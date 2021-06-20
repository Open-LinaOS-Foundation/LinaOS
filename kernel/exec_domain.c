// SPDX-License-Identifier: GPL-2.0
/*
 * Handling of different ABIs (personalities).
 *
 * We group personalities into execution domains which have their
 * own handlers for kernel entry points, signal mapping, etc...
 *
 * 2001-05-06	Complete rewrite,  Christoph Hellwig (hch@infradead.org)
 */

#include <linaos/init.h>
#include <linaos/kernel.h>
#include <linaos/kmod.h>
#include <linaos/module.h>
#include <linaos/personality.h>
#include <linaos/proc_fs.h>
#include <linaos/sched.h>
#include <linaos/seq_file.h>
#include <linaos/syscalls.h>
#include <linaos/sysctl.h>
#include <linaos/types.h>

#ifdef CONFIG_PROC_FS
static int execdomains_proc_show(struct seq_file *m, void *v)
{
	seq_puts(m, "0-0\tLinaOS           \t[kernel]\n");
	return 0;
}

static int __init proc_execdomains_init(void)
{
	proc_create_single("execdomains", 0, NULL, execdomains_proc_show);
	return 0;
}
module_init(proc_execdomains_init);
#endif

SYSCALL_DEFINE1(personality, unsigned int, personality)
{
	unsigned int old = current->personality;

	if (personality != 0xffffffff)
		set_personality(personality);

	return old;
}
