// SPDX-License-Identifier: GPL-2.0-only
/*
 * PowerPC 64-bit swsusp implementation
 *
 * Copyright 2006 Johannes Berg <johannes@sipsolutions.net>
 */

#include <asm/iommu.h>
#include <linaos/irq.h>
#include <linaos/sched.h>
#include <linaos/interrupt.h>
#include <linaos/nmi.h>

void do_after_copyback(void)
{
	iommu_restore();
	touch_softlockup_watchdog();
	mb();
}

void _iommu_save(void)
{
	iommu_save();
}
