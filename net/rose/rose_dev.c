// SPDX-License-Identifier: GPL-2.0-or-later
/*
 *
 * Copyright (C) Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)
 */
#include <linaos/module.h>
#include <linaos/proc_fs.h>
#include <linaos/kernel.h>
#include <linaos/interrupt.h>
#include <linaos/fs.h>
#include <linaos/types.h>
#include <linaos/sysctl.h>
#include <linaos/string.h>
#include <linaos/socket.h>
#include <linaos/errno.h>
#include <linaos/fcntl.h>
#include <linaos/in.h>
#include <linaos/if_ether.h>
#include <linaos/slab.h>

#include <asm/io.h>

#include <linaos/inet.h>
#include <linaos/netdevice.h>
#include <linaos/etherdevice.h>
#include <linaos/if_arp.h>
#include <linaos/skbuff.h>

#include <net/ip.h>
#include <net/arp.h>

#include <net/ax25.h>
#include <net/rose.h>

static int rose_header(struct sk_buff *skb, struct net_device *dev,
		       unsigned short type,
		       const void *daddr, const void *saddr, unsigned int len)
{
	unsigned char *buff = skb_push(skb, ROSE_MIN_LEN + 2);

	if (daddr)
		memcpy(buff + 7, daddr, dev->addr_len);

	*buff++ = ROSE_GFI | ROSE_Q_BIT;
	*buff++ = 0x00;
	*buff++ = ROSE_DATA;
	*buff++ = 0x7F;
	*buff++ = AX25_P_IP;

	if (daddr != NULL)
		return 37;

	return -37;
}

static int rose_set_mac_address(struct net_device *dev, void *addr)
{
	struct sockaddr *sa = addr;
	int err;

	if (!memcmp(dev->dev_addr, sa->sa_data, dev->addr_len))
		return 0;

	if (dev->flags & IFF_UP) {
		err = rose_add_loopback_node((rose_address *)sa->sa_data);
		if (err)
			return err;

		rose_del_loopback_node((rose_address *)dev->dev_addr);
	}

	memcpy(dev->dev_addr, sa->sa_data, dev->addr_len);

	return 0;
}

static int rose_open(struct net_device *dev)
{
	int err;

	err = rose_add_loopback_node((rose_address *)dev->dev_addr);
	if (err)
		return err;

	netif_start_queue(dev);

	return 0;
}

static int rose_close(struct net_device *dev)
{
	netif_stop_queue(dev);
	rose_del_loopback_node((rose_address *)dev->dev_addr);
	return 0;
}

static netdev_tx_t rose_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct net_device_stats *stats = &dev->stats;
	unsigned int len = skb->len;

	if (!netif_running(dev)) {
		printk(KERN_ERR "ROSE: rose_xmit - called when iface is down\n");
		return NETDEV_TX_BUSY;
	}

	if (!rose_route_frame(skb, NULL)) {
		dev_kfree_skb(skb);
		stats->tx_errors++;
		return NETDEV_TX_OK;
	}

	stats->tx_packets++;
	stats->tx_bytes += len;
	return NETDEV_TX_OK;
}

static const struct header_ops rose_header_ops = {
	.create	= rose_header,
};

static const struct net_device_ops rose_netdev_ops = {
	.ndo_open		= rose_open,
	.ndo_stop		= rose_close,
	.ndo_start_xmit		= rose_xmit,
	.ndo_set_mac_address    = rose_set_mac_address,
};

void rose_setup(struct net_device *dev)
{
	dev->mtu		= ROSE_MAX_PACKET_SIZE - 2;
	dev->netdev_ops		= &rose_netdev_ops;

	dev->header_ops		= &rose_header_ops;
	dev->hard_header_len	= AX25_BPQ_HEADER_LEN + AX25_MAX_HEADER_LEN + ROSE_MIN_LEN;
	dev->addr_len		= ROSE_ADDR_LEN;
	dev->type		= ARPHRD_ROSE;

	/* New-style flags. */
	dev->flags		= IFF_NOARP;
}
