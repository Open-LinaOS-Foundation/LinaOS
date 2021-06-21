/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * AMD Platform Security Processor (PSP) interface driver
 *
 * Copyright (C) 2017-2019 Advanced Micro Devices, Inc.
 *
 * Author: Brijesh Singh <brijesh.singh@amd.com>
 */

#ifndef __SEV_DEV_H__
#define __SEV_DEV_H__

#include <linaos/device.h>
#include <linaos/spinlock.h>
#include <linaos/mutex.h>
#include <linaos/list.h>
#include <linaos/wait.h>
#include <linaos/dmapool.h>
#include <linaos/hw_random.h>
#include <linaos/bitops.h>
#include <linaos/interrupt.h>
#include <linaos/irqreturn.h>
#include <linaos/dmaengine.h>
#include <linaos/psp-sev.h>
#include <linaos/miscdevice.h>
#include <linaos/capability.h>

#define SEV_CMD_COMPLETE		BIT(1)
#define SEV_CMDRESP_CMD_SHIFT		16
#define SEV_CMDRESP_IOC			BIT(0)

struct sev_misc_dev {
	struct kref refcount;
	struct miscdevice misc;
};

struct sev_device {
	struct device *dev;
	struct psp_device *psp;

	void __iomem *io_regs;

	struct sev_vdata *vdata;

	int state;
	unsigned int int_rcvd;
	wait_queue_head_t int_queue;
	struct sev_misc_dev *misc;

	u8 api_major;
	u8 api_minor;
	u8 build;

	void *cmd_buf;
};

int sev_dev_init(struct psp_device *psp);
void sev_dev_destroy(struct psp_device *psp);

void sev_pci_init(void);
void sev_pci_exit(void);

#endif /* __SEV_DEV_H */
