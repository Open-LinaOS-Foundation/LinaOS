// SPDX-License-Identifier: GPL-2.0-only
/*
 * arch/arm/plat-iop/i2c.c
 *
 * Author: Nicolas Pitre <nico@cam.org>
 * Copyright (C) 2001 MontaVista Software, Inc.
 * Copyright (C) 2004 Intel Corporation.
 */

#include <linaos/mm.h>
#include <linaos/init.h>
#include <linaos/major.h>
#include <linaos/fs.h>
#include <linaos/platform_device.h>
#include <linaos/serial.h>
#include <linaos/tty.h>
#include <linaos/serial_core.h>
#include <linaos/io.h>
#include <linaos/gpio/machine.h>
#include <asm/page.h>
#include <asm/mach/map.h>
#include <asm/setup.h>
#include <asm/memory.h>
#include <asm/mach/arch.h>

#include "hardware.h"
#include "iop3xx.h"
#include "irqs.h"

/*
 * Each of the I2C busses have corresponding GPIO lines, and the driver
 * need to access these directly to drive the bus low at times.
 */

struct gpiod_lookup_table iop3xx_i2c0_gpio_lookup = {
	.dev_id = "IOP3xx-I2C.0",
	.table = {
		GPIO_LOOKUP("gpio-iop", 7, "scl", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("gpio-iop", 6, "sda", GPIO_ACTIVE_HIGH),
		{ }
	},
};

struct gpiod_lookup_table iop3xx_i2c1_gpio_lookup = {
	.dev_id = "IOP3xx-I2C.1",
	.table = {
		GPIO_LOOKUP("gpio-iop", 5, "scl", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("gpio-iop", 4, "sda", GPIO_ACTIVE_HIGH),
		{ }
	},
};

static struct resource iop3xx_i2c0_resources[] = {
	[0] = {
		.start	= 0xfffff680,
		.end	= 0xfffff697,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= IRQ_IOP32X_I2C_0,
		.end	= IRQ_IOP32X_I2C_0,
		.flags	= IORESOURCE_IRQ,
	},
};

struct platform_device iop3xx_i2c0_device = {
	.name		= "IOP3xx-I2C",
	.id		= 0,
	.num_resources	= 2,
	.resource	= iop3xx_i2c0_resources,
};


static struct resource iop3xx_i2c1_resources[] = {
	[0] = {
		.start	= 0xfffff6a0,
		.end	= 0xfffff6b7,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= IRQ_IOP32X_I2C_1,
		.end	= IRQ_IOP32X_I2C_1,
		.flags	= IORESOURCE_IRQ,
	}
};

struct platform_device iop3xx_i2c1_device = {
	.name		= "IOP3xx-I2C",
	.id		= 1,
	.num_resources	= 2,
	.resource	= iop3xx_i2c1_resources,
};
