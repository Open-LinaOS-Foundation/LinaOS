// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * net/sched/cls_rsvp.c	Special RSVP packet classifier for IPv4.
 *
 * Authors:	Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru>
 */

#include <linaos/module.h>
#include <linaos/types.h>
#include <linaos/kernel.h>
#include <linaos/string.h>
#include <linaos/errno.h>
#include <linaos/skbuff.h>
#include <net/ip.h>
#include <net/netlink.h>
#include <net/act_api.h>
#include <net/pkt_cls.h>

#define RSVP_DST_LEN	1
#define RSVP_ID		"rsvp"
#define RSVP_OPS	cls_rsvp_ops

#include "cls_rsvp.h"
MODULE_LICENSE("GPL");
