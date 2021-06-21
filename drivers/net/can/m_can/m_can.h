/* SPDX-License-Identifier: GPL-2.0 */
/* CAN bus driver for Bosch M_CAN controller
 * Copyright (C) 2018 Texas Instruments Incorporated - http://www.ti.com/
 */

#ifndef _CAN_M_CAN_H_
#define _CAN_M_CAN_H_

#include <linaos/can/core.h>
#include <linaos/can/led.h>
#include <linaos/can/rx-offload.h>
#include <linaos/completion.h>
#include <linaos/device.h>
#include <linaos/dma-mapping.h>
#include <linaos/freezer.h>
#include <linaos/slab.h>
#include <linaos/uaccess.h>
#include <linaos/clk.h>
#include <linaos/delay.h>
#include <linaos/interrupt.h>
#include <linaos/io.h>
#include <linaos/kernel.h>
#include <linaos/module.h>
#include <linaos/netdevice.h>
#include <linaos/of.h>
#include <linaos/of_device.h>
#include <linaos/pm_runtime.h>
#include <linaos/iopoll.h>
#include <linaos/can/dev.h>
#include <linaos/pinctrl/consumer.h>

/* m_can lec values */
enum m_can_lec_type {
	LEC_NO_ERROR = 0,
	LEC_STUFF_ERROR,
	LEC_FORM_ERROR,
	LEC_ACK_ERROR,
	LEC_BIT1_ERROR,
	LEC_BIT0_ERROR,
	LEC_CRC_ERROR,
	LEC_UNUSED,
};

enum m_can_mram_cfg {
	MRAM_SIDF = 0,
	MRAM_XIDF,
	MRAM_RXF0,
	MRAM_RXF1,
	MRAM_RXB,
	MRAM_TXE,
	MRAM_TXB,
	MRAM_CFG_NUM,
};

/* address offset and element number for each FIFO/Buffer in the Message RAM */
struct mram_cfg {
	u16 off;
	u8  num;
};

struct m_can_classdev;
struct m_can_ops {
	/* Device specific call backs */
	int (*clear_interrupts)(struct m_can_classdev *cdev);
	u32 (*read_reg)(struct m_can_classdev *cdev, int reg);
	int (*write_reg)(struct m_can_classdev *cdev, int reg, int val);
	u32 (*read_fifo)(struct m_can_classdev *cdev, int addr_offset);
	int (*write_fifo)(struct m_can_classdev *cdev, int addr_offset,
			  int val);
	int (*init)(struct m_can_classdev *cdev);
};

struct m_can_classdev {
	struct can_priv can;
	struct can_rx_offload offload;
	struct napi_struct napi;
	struct net_device *net;
	struct device *dev;
	struct clk *hclk;
	struct clk *cclk;

	struct workqueue_struct *tx_wq;
	struct work_struct tx_work;
	struct sk_buff *tx_skb;

	struct can_bittiming_const *bit_timing;
	struct can_bittiming_const *data_timing;

	struct m_can_ops *ops;

	int version;
	u32 irqstatus;

	int pm_clock_support;
	int is_peripheral;

	struct mram_cfg mcfg[MRAM_CFG_NUM];
};

struct m_can_classdev *m_can_class_allocate_dev(struct device *dev, int sizeof_priv);
void m_can_class_free_dev(struct net_device *net);
int m_can_class_register(struct m_can_classdev *cdev);
void m_can_class_unregister(struct m_can_classdev *cdev);
int m_can_class_get_clocks(struct m_can_classdev *cdev);
void m_can_init_ram(struct m_can_classdev *priv);

int m_can_class_suspend(struct device *dev);
int m_can_class_resume(struct device *dev);
#endif	/* _CAN_M_H_ */
