// SPDX-License-Identifier: GPL-2.0
#include <linaos/fs.h>
#include <linaos/init.h>
#include <linaos/kernel.h>
#include <linaos/proc_fs.h>
#include <linaos/seq_file.h>
#include <linaos/utsname.h>

static int version_proc_show(struct seq_file *m, void *v)
{
	seq_printf(m, linaos_proc_banner,
		utsname()->sysname,
		utsname()->release,
		utsname()->version);
	return 0;
}

static int __init proc_version_init(void)
{
	proc_create_single("version", 0, NULL, version_proc_show);
	return 0;
}
fs_initcall(proc_version_init);
