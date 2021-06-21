/* SPDX-License-Identifier: GPL-2.0 */
/*
 * This file is based on code from OCTEON SDK by Cavium Networks.
 *
 * Copyright (c) 2003-2007 Cavium Networks
 */

#include <linaos/module.h>
#include <linaos/kernel.h>
#include <linaos/netdevice.h>
#include <linaos/etherdevice.h>
#include <linaos/ip.h>
#include <linaos/string.h>
#include <linaos/ethtool.h>
#include <linaos/seq_file.h>
#include <linaos/proc_fs.h>
#include <net/dst.h>
#ifdef CONFIG_XFRM
#include <linaos/xfrm.h>
#include <net/xfrm.h>
#endif /* CONFIG_XFRM */

extern const struct ethtool_ops cvm_oct_ethtool_ops;

int cvm_oct_ioctl(struct net_device *dev, struct ifreq *rq, int cmd);
int cvm_oct_phy_setup_device(struct net_device *dev);
