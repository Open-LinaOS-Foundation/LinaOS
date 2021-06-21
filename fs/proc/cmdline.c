// SPDX-License-Identifier: GPL-2.0
#include <linaos/fs.h>
#include <linaos/init.h>
#include <linaos/proc_fs.h>
#include <linaos/seq_file.h>

static int cmdline_proc_show(struct seq_file *m, void *v)
{
	seq_puts(m, saved_command_line);
	seq_putc(m, '\n');
	return 0;
}

static int __init proc_cmdline_init(void)
{
	proc_create_single("cmdline", 0, NULL, cmdline_proc_show);
	return 0;
}
fs_initcall(proc_cmdline_init);
