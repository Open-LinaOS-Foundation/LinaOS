// SPDX-License-Identifier: GPL-2.0
/*
 * Provide kernel BTF information for introspection and use by eBPF tools.
 */
#include <linaos/kernel.h>
#include <linaos/module.h>
#include <linaos/kobject.h>
#include <linaos/init.h>
#include <linaos/sysfs.h>

/* See scripts/link-vmlinaos.sh, gen_btf() func for details */
extern char __weak __start_BTF[];
extern char __weak __stop_BTF[];

static ssize_t
btf_vmlinaos_read(struct file *file, struct kobject *kobj,
		 struct bin_attribute *bin_attr,
		 char *buf, loff_t off, size_t len)
{
	memcpy(buf, __start_BTF + off, len);
	return len;
}

static struct bin_attribute bin_attr_btf_vmlinaos __ro_after_init = {
	.attr = { .name = "vmlinaos", .mode = 0444, },
	.read = btf_vmlinaos_read,
};

struct kobject *btf_kobj;

static int __init btf_vmlinaos_init(void)
{
	bin_attr_btf_vmlinaos.size = __stop_BTF - __start_BTF;

	if (!__start_BTF || bin_attr_btf_vmlinaos.size == 0)
		return 0;

	btf_kobj = kobject_create_and_add("btf", kernel_kobj);
	if (!btf_kobj)
		return -ENOMEM;

	return sysfs_create_bin_file(btf_kobj, &bin_attr_btf_vmlinaos);
}

subsys_initcall(btf_vmlinaos_init);
