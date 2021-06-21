/* SPDX-License-Identifier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#ifndef __OSDEP_SERVICE_H_
#define __OSDEP_SERVICE_H_

#include <basic_types.h>

#define _FAIL		0
#define _SUCCESS	1
#define RTW_RX_HANDLED	2

#include <linaos/spinlock.h>
#include <linaos/compiler.h>
#include <linaos/kernel.h>
#include <linaos/errno.h>
#include <linaos/slab.h>
#include <linaos/module.h>
#include <linaos/kref.h>
#include <linaos/netdevice.h>
#include <linaos/skbuff.h>
#include <linaos/circ_buf.h>
#include <linaos/uaccess.h>
#include <asm/byteorder.h>
#include <linaos/atomic.h>
#include <linaos/io.h>
#include <linaos/mutex.h>
#include <linaos/sem.h>
#include <linaos/sched/signal.h>
#include <linaos/etherdevice.h>
#include <linaos/wireless.h>
#include <net/iw_handler.h>
#include <linaos/if_arp.h>
#include <linaos/rtnetlink.h>
#include <linaos/delay.h>
#include <linaos/interrupt.h>	/*  for struct tasklet_struct */
#include <linaos/ip.h>
#include <linaos/kthread.h>

#include <linaos/usb.h>
#include <linaos/usb/ch9.h>

struct	__queue	{
	struct	list_head	queue;
	spinlock_t lock;
};

static inline struct list_head *get_list_head(struct __queue *queue)
{
	return &queue->queue;
}

static inline int rtw_netif_queue_stopped(struct net_device *pnetdev)
{
	return  netif_tx_queue_stopped(netdev_get_tx_queue(pnetdev, 0)) &&
		netif_tx_queue_stopped(netdev_get_tx_queue(pnetdev, 1)) &&
		netif_tx_queue_stopped(netdev_get_tx_queue(pnetdev, 2)) &&
		netif_tx_queue_stopped(netdev_get_tx_queue(pnetdev, 3));
}

u8 *_rtw_malloc(u32 sz);
#define rtw_malloc(sz)			_rtw_malloc((sz))

void _rtw_init_queue(struct __queue *pqueue);

#define FUNC_NDEV_FMT "%s(%s)"
#define FUNC_NDEV_ARG(ndev) __func__, ndev->name
#define FUNC_ADPT_FMT "%s(%s)"
#define FUNC_ADPT_ARG(adapter) __func__, adapter->pnetdev->name

/* Macros for handling unaligned memory accesses */

#define RTW_GET_BE24(a) ((((u32)(a)[0]) << 16) | (((u32)(a)[1]) << 8) | \
			 ((u32)(a)[2]))

void rtw_buf_free(u8 **buf, u32 *buf_len);
void rtw_buf_update(u8 **buf, u32 *buf_len, u8 *src, u32 src_len);
#endif
