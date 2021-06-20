// SPDX-License-Identifier: GPL-2.0
/*
 * This file exists solely to ensure debug information for some core
 * data structures is included in the final image even for
 * CONFIG_DEBUG_INFO_REDUCED. Please do not add actual code. However,
 * adding appropriate #includes is fine.
 */
#include <stdarg.h>

#include <linaos/cred.h>
#include <linaos/crypto.h>
#include <linaos/dcache.h>
#include <linaos/device.h>
#include <linaos/fs.h>
#include <linaos/fscache-cache.h>
#include <linaos/io.h>
#include <linaos/kallsyms.h>
#include <linaos/kernel.h>
#include <linaos/kobject.h>
#include <linaos/mm.h>
#include <linaos/module.h>
#include <linaos/net.h>
#include <linaos/sched.h>
#include <linaos/slab.h>
#include <linaos/types.h>
#include <net/addrconf.h>
#include <net/sock.h>
#include <net/tcp.h>
