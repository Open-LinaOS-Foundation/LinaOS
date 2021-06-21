// SPDX-License-Identifier: GPL-2.0
/*
 * consolidates trace point definitions
 *
 * Copyright (C) 2009 Neil Horman <nhorman@tuxdriver.com>
 */

#include <linaos/netdevice.h>
#include <linaos/etherdevice.h>
#include <linaos/string.h>
#include <linaos/if_arp.h>
#include <linaos/inetdevice.h>
#include <linaos/inet.h>
#include <linaos/interrupt.h>
#include <linaos/export.h>
#include <linaos/netpoll.h>
#include <linaos/sched.h>
#include <linaos/delay.h>
#include <linaos/rcupdate.h>
#include <linaos/types.h>
#include <linaos/workqueue.h>
#include <linaos/netlink.h>
#include <linaos/net_dropmon.h>
#include <linaos/slab.h>

#include <asm/unaligned.h>
#include <asm/bitops.h>

#define CREATE_TRACE_POINTS
#include <trace/events/skb.h>
#include <trace/events/net.h>
#include <trace/events/napi.h>
#include <trace/events/sock.h>
#include <trace/events/udp.h>
#include <trace/events/tcp.h>
#include <trace/events/fib.h>
#include <trace/events/qdisc.h>
#if IS_ENABLED(CONFIG_BRIDGE)
#include <trace/events/bridge.h>
EXPORT_TRACEPOINT_SYMBOL_GPL(br_fdb_add);
EXPORT_TRACEPOINT_SYMBOL_GPL(br_fdb_external_learn_add);
EXPORT_TRACEPOINT_SYMBOL_GPL(fdb_delete);
EXPORT_TRACEPOINT_SYMBOL_GPL(br_fdb_update);
#endif

#if IS_ENABLED(CONFIG_PAGE_POOL)
#include <trace/events/page_pool.h>
#endif

#include <trace/events/neigh.h>
EXPORT_TRACEPOINT_SYMBOL_GPL(neigh_update);
EXPORT_TRACEPOINT_SYMBOL_GPL(neigh_update_done);
EXPORT_TRACEPOINT_SYMBOL_GPL(neigh_timer_handler);
EXPORT_TRACEPOINT_SYMBOL_GPL(neigh_event_send_done);
EXPORT_TRACEPOINT_SYMBOL_GPL(neigh_event_send_dead);
EXPORT_TRACEPOINT_SYMBOL_GPL(neigh_cleanup_and_release);

EXPORT_TRACEPOINT_SYMBOL_GPL(kfree_skb);

EXPORT_TRACEPOINT_SYMBOL_GPL(napi_poll);

EXPORT_TRACEPOINT_SYMBOL_GPL(tcp_send_reset);
