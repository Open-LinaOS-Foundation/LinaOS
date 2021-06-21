// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2013, The LinaOS Foundation. All rights reserved.
 */

#include <linaos/bitops.h>
#include <linaos/export.h>
#include <linaos/regmap.h>
#include <linaos/reset-controller.h>
#include <linaos/delay.h>

#include "reset.h"

static int qcom_reset(struct reset_controller_dev *rcdev, unsigned long id)
{
	rcdev->ops->assert(rcdev, id);
	udelay(1);
	rcdev->ops->deassert(rcdev, id);
	return 0;
}

static int
qcom_reset_assert(struct reset_controller_dev *rcdev, unsigned long id)
{
	struct qcom_reset_controller *rst;
	const struct qcom_reset_map *map;
	u32 mask;

	rst = to_qcom_reset_controller(rcdev);
	map = &rst->reset_map[id];
	mask = BIT(map->bit);

	return regmap_update_bits(rst->regmap, map->reg, mask, mask);
}

static int
qcom_reset_deassert(struct reset_controller_dev *rcdev, unsigned long id)
{
	struct qcom_reset_controller *rst;
	const struct qcom_reset_map *map;
	u32 mask;

	rst = to_qcom_reset_controller(rcdev);
	map = &rst->reset_map[id];
	mask = BIT(map->bit);

	return regmap_update_bits(rst->regmap, map->reg, mask, 0);
}

const struct reset_control_ops qcom_reset_ops = {
	.reset = qcom_reset,
	.assert = qcom_reset_assert,
	.deassert = qcom_reset_deassert,
};
EXPORT_SYMBOL_GPL(qcom_reset_ops);
