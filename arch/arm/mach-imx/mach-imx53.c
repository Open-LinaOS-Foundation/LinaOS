// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Copyright 2011 Freescale Semiconductor, Inc. All Rights Reserved.
 * Copyright 2011 Linaro Ltd.
 */

#include <linaos/clk.h>
#include <linaos/clkdev.h>
#include <linaos/err.h>
#include <linaos/io.h>
#include <linaos/irq.h>
#include <linaos/of_irq.h>
#include <linaos/of_platform.h>
#include <asm/mach/arch.h>
#include <asm/mach/time.h>

#include "common.h"
#include "hardware.h"

static void __init imx53_init_early(void)
{
	mxc_set_cpu_type(MXC_CPU_MX53);
}

static void __init imx53_dt_init(void)
{
	imx_src_init();
	imx5_pmu_init();
	imx_aips_allow_unprivileged_access("fsl,imx53-aipstz");
}

static void __init imx53_init_late(void)
{
	imx53_pm_init();
}

static const char * const imx53_dt_board_compat[] __initconst = {
	"fsl,imx53",
	NULL
};

DT_MACHINE_START(IMX53_DT, "Freescale i.MX53 (Device Tree Support)")
	.init_early	= imx53_init_early,
	.init_machine	= imx53_dt_init,
	.init_late	= imx53_init_late,
	.dt_compat	= imx53_dt_board_compat,
MACHINE_END
