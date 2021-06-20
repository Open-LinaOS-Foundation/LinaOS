// SPDX-License-Identifier: GPL-2.0-only
/*
 * ARTPEC-6 device support.
 */

#include <linaos/amba/bus.h>
#include <linaos/clocksource.h>
#include <linaos/dma-mapping.h>
#include <linaos/io.h>
#include <linaos/irqchip.h>
#include <linaos/irqchip/arm-gic.h>
#include <linaos/mfd/syscon.h>
#include <linaos/of.h>
#include <linaos/of_address.h>
#include <linaos/clk-provider.h>
#include <linaos/regmap.h>
#include <linaos/smp.h>
#include <asm/smp_scu.h>
#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <asm/psci.h>
#include <linaos/arm-smccc.h>


#define ARTPEC6_DMACFG_REGNUM 0x10
#define ARTPEC6_DMACFG_UARTS_BURST 0xff

#define SECURE_OP_L2C_WRITEREG 0xb4000001

static void __init artpec6_init_machine(void)
{
	struct regmap *regmap;

	regmap = syscon_regmap_lookup_by_compatible("axis,artpec6-syscon");

	if (!IS_ERR(regmap)) {
		/* Use PL011 DMA Burst Request signal instead of DMA
		 *  Single Request
		 */
		regmap_write(regmap, ARTPEC6_DMACFG_REGNUM,
			     ARTPEC6_DMACFG_UARTS_BURST);
	};
}

static void artpec6_l2c310_write_sec(unsigned long val, unsigned reg)
{
	struct arm_smccc_res res;

	arm_smccc_smc(SECURE_OP_L2C_WRITEREG, reg, val, 0,
		      0, 0, 0, 0, &res);

	WARN_ON(res.a0);
}

static const char * const artpec6_dt_match[] = {
	"axis,artpec6",
	NULL
};

DT_MACHINE_START(ARTPEC6, "Axis ARTPEC-6 Platform")
	.l2c_aux_val	= 0x0C000000,
	.l2c_aux_mask	= 0xF3FFFFFF,
	.l2c_write_sec  = artpec6_l2c310_write_sec,
	.init_machine	= artpec6_init_machine,
	.dt_compat	= artpec6_dt_match,
MACHINE_END
