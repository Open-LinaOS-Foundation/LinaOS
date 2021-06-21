/* SPDX-License-Identifier: GPL-2.0 */
#ifndef EADM_SCH_H
#define EADM_SCH_H

#include <linaos/completion.h>
#include <linaos/device.h>
#include <linaos/timer.h>
#include <linaos/list.h>
#include "orb.h"

struct eadm_private {
	union orb orb;
	enum {EADM_IDLE, EADM_BUSY, EADM_NOT_OPER} state;
	struct completion *completion;
	struct subchannel *sch;
	struct timer_list timer;
	struct list_head head;
} __aligned(8);

#define get_eadm_private(n) ((struct eadm_private *)dev_get_drvdata(&n->dev))
#define set_eadm_private(n, p) (dev_set_drvdata(&n->dev, p))

#endif
