/* SPDX-License-Identifier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2013 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#ifndef __OSDEP_LINUX_SERVICE_H_
#define __OSDEP_LINUX_SERVICE_H_

	#include <linaos/spinlock.h>
	#include <linaos/compiler.h>
	#include <linaos/kernel.h>
	#include <linaos/errno.h>
	#include <linaos/init.h>
	#include <linaos/slab.h>
	#include <linaos/module.h>
	#include <linaos/kref.h>
	/* include <linaos/smp_lock.h> */
	#include <linaos/netdevice.h>
	#include <linaos/skbuff.h>
	#include <linaos/uaccess.h>
	#include <asm/byteorder.h>
	#include <linaos/atomic.h>
	#include <linaos/io.h>
	#include <linaos/sem.h>
	#include <linaos/sched.h>
	#include <linaos/etherdevice.h>
	#include <linaos/wireless.h>
	#include <net/iw_handler.h>
	#include <linaos/if_arp.h>
	#include <linaos/rtnetlink.h>
	#include <linaos/delay.h>
	#include <linaos/interrupt.h>	/*  for struct tasklet_struct */
	#include <linaos/ip.h>
	#include <linaos/kthread.h>
	#include <linaos/list.h>
	#include <linaos/vmalloc.h>

/* 	#include <linaos/ieee80211.h> */
        #include <net/ieee80211_radiotap.h>
	#include <net/cfg80211.h>

	struct	__queue	{
		struct	list_head	queue;
		spinlock_t	lock;
	};

	#define thread_exit() complete_and_exit(NULL, 0)

static inline struct list_head *get_next(struct list_head	*list)
{
	return list->next;
}

static inline struct list_head	*get_list_head(struct __queue	*queue)
{
	return (&(queue->queue));
}

static inline void _set_timer(struct timer_list *ptimer, u32 delay_time)
{
	mod_timer(ptimer, (jiffies + (delay_time * HZ / 1000)));
}

static inline void _init_workitem(struct work_struct *pwork, void *pfunc, void *cntx)
{
	INIT_WORK(pwork, pfunc);
}

static inline void _set_workitem(struct work_struct *pwork)
{
	schedule_work(pwork);
}

static inline void _cancel_workitem_sync(struct work_struct *pwork)
{
	cancel_work_sync(pwork);
}

static inline int rtw_netif_queue_stopped(struct net_device *pnetdev)
{
	return (netif_tx_queue_stopped(netdev_get_tx_queue(pnetdev, 0)) &&
		netif_tx_queue_stopped(netdev_get_tx_queue(pnetdev, 1)) &&
		netif_tx_queue_stopped(netdev_get_tx_queue(pnetdev, 2)) &&
		netif_tx_queue_stopped(netdev_get_tx_queue(pnetdev, 3)));
}

static inline void rtw_netif_wake_queue(struct net_device *pnetdev)
{
	netif_tx_wake_all_queues(pnetdev);
}

static inline void rtw_netif_start_queue(struct net_device *pnetdev)
{
	netif_tx_start_all_queues(pnetdev);
}

static inline void rtw_netif_stop_queue(struct net_device *pnetdev)
{
	netif_tx_stop_all_queues(pnetdev);
}

#define rtw_signal_process(pid, sig) kill_pid(find_vpid((pid)), (sig), 1)

#define NDEV_ARG(ndev) ndev->name
#define ADPT_ARG(adapter) adapter->pnetdev->name
#define FUNC_NDEV_FMT "%s(%s)"
#define FUNC_NDEV_ARG(ndev) __func__, ndev->name
#define FUNC_ADPT_FMT "%s(%s)"
#define FUNC_ADPT_ARG(adapter) __func__, adapter->pnetdev->name

struct rtw_netdev_priv_indicator {
	void *priv;
	u32 sizeof_priv;
};

static inline struct adapter *rtw_netdev_priv(struct net_device *netdev)
{
	return ((struct rtw_netdev_priv_indicator *)netdev_priv(netdev))->priv;
}

struct net_device *rtw_alloc_etherdev_with_old_priv(int sizeof_priv, void *old_priv);
extern struct net_device *rtw_alloc_etherdev(int sizeof_priv);

#endif
