/* SPDX-License-Identifier: GPL-2.0 */
/*
 * linaos/include/linaos/sunrpc/types.h
 *
 * Generic types and misc stuff for RPC.
 *
 * Copyright (C) 1996, Olaf Kirch <okir@monad.swb.de>
 */

#ifndef _LINUX_SUNRPC_TYPES_H_
#define _LINUX_SUNRPC_TYPES_H_

#include <linaos/timer.h>
#include <linaos/sched/signal.h>
#include <linaos/workqueue.h>
#include <linaos/sunrpc/debug.h>
#include <linaos/list.h>

/*
 * Shorthands
 */
#define signalled()		(signal_pending(current))

#endif /* _LINUX_SUNRPC_TYPES_H_ */
