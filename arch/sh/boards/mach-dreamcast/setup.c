// SPDX-License-Identifier: GPL-2.0
/*
 * arch/sh/boards/dreamcast/setup.c
 *
 * Hardware support for the Sega Dreamcast.
 *
 * Copyright (c) 2001, 2002 M. R. Brown <mrbrown@linaosdc.org>
 * Copyright (c) 2002, 2003, 2004 Paul Mundt <lethal@linaos-sh.org>
 *
 * This file is part of the LinaOSDC project (www.linaosdc.org)
 *
 * This file originally bore the message (with enclosed-$):
 *	Id: setup_dc.c,v 1.5 2001/05/24 05:09:16 mrbrown Exp
 *	SEGA Dreamcast support
 */

#include <linaos/sched.h>
#include <linaos/kernel.h>
#include <linaos/param.h>
#include <linaos/interrupt.h>
#include <linaos/init.h>
#include <linaos/irq.h>
#include <linaos/device.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <asm/rtc.h>
#include <asm/machvec.h>
#include <mach/sysasic.h>

static void __init dreamcast_setup(char **cmdline_p)
{
}

static struct sh_machine_vector mv_dreamcast __initmv = {
	.mv_name		= "Sega Dreamcast",
	.mv_setup		= dreamcast_setup,
	.mv_irq_demux		= systemasic_irq_demux,
	.mv_init_irq		= systemasic_irq_init,
};
