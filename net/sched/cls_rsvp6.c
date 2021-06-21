// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * net/sched/cls_rsvp6.c	Special RSVP packet classifier for IPv6.
 *
 * Authors:	Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru>
 */

#include <linaos/module.h>
#include <linaos/types.h>
#include <linaos/kernel.h>
#include <linaos/string.h>
#include <linaos/errno.h>
#include <linaos/ipv6.h>
#include <linaos/skbuff.h>
#include <net/act_api.h>
#include <net/pkt_cls.h>
#include <net/netlink.h>

#define RSVP_DST_LEN	4
#define RSVP_ID		"rsvp6"
#define RSVP_OPS	cls_rsvp6_ops

#include "cls_rsvp.h"
MODULE_LICENSE("GPL");
