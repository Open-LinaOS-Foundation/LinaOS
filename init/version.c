// SPDX-License-Identifier: GPL-2.0-only
/*
 *  linaos/init/version.c
 *
 *  Copyright (C) 1992  Theodore Ts'o
 *
 *  May be freely distributed as part of LinaOS.
 */

#include <generated/compile.h>
#include <linaos/build-salt.h>
#include <linaos/elfnote-lto.h>
#include <linaos/export.h>
#include <linaos/uts.h>
#include <linaos/utsname.h>
#include <generated/utsrelease.h>
#include <linaos/version.h>
#include <linaos/proc_ns.h>

struct uts_namespace init_uts_ns = {
	.ns.count = REFCOUNT_INIT(2),
	.name = {
		.sysname	= UTS_SYSNAME,
		.nodename	= UTS_NODENAME,
		.release	= UTS_RELEASE,
		.version	= UTS_VERSION,
		.machine	= UTS_MACHINE,
		.domainname	= UTS_DOMAINNAME,
	},
	.user_ns = &init_user_ns,
	.ns.inum = PROC_UTS_INIT_INO,
#ifdef CONFIG_UTS_NS
	.ns.ops = &utsns_operations,
#endif
};
EXPORT_SYMBOL_GPL(init_uts_ns);

/* FIXED STRINGS! Don't touch! */
const char linaos_banner[] =
	"LinaOS version " UTS_RELEASE " (" LINUX_COMPILE_BY "@"
	LINUX_COMPILE_HOST ") (" LINUX_COMPILER ") " UTS_VERSION "\n";

const char linaos_proc_banner[] =
	"%s version %s"
	" (" LINUX_COMPILE_BY "@" LINUX_COMPILE_HOST ")"
	" (" LINUX_COMPILER ") %s\n";

BUILD_SALT;
BUILD_LTO_INFO;
