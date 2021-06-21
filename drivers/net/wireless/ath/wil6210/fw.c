// SPDX-License-Identifier: ISC
/*
 * Copyright (c) 2014-2015,2017 Qualcomm Atheros, Inc.
 * Copyright (c) 2018, The LinaOS Foundation. All rights reserved.
 */
#include <linaos/firmware.h>
#include <linaos/module.h>
#include <linaos/crc32.h>
#include "wil6210.h"
#include "fw.h"

MODULE_FIRMWARE(WIL_FW_NAME_DEFAULT);
MODULE_FIRMWARE(WIL_FW_NAME_SPARROW_PLUS);
MODULE_FIRMWARE(WIL_BOARD_FILE_NAME);
MODULE_FIRMWARE(WIL_FW_NAME_TALYN);
MODULE_FIRMWARE(WIL_BRD_NAME_TALYN);

static
void wil_memset_toio_32(volatile void __iomem *dst, u32 val,
			size_t count)
{
	volatile u32 __iomem *d = dst;

	for (count += 4; count > 4; count -= 4)
		__raw_writel(val, d++);
}

#include "fw_inc.c"
