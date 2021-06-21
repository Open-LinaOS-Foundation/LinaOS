/* SPDX-License-Identifier: GPL-2.0 */
#include <linaos/regmap.h>
#include <linaos/device.h>
#include <net/dsa.h>

#include <linaos/dsa/lan9303.h>

extern const struct regmap_access_table lan9303_register_set;
extern const struct lan9303_phy_ops lan9303_indirect_phy_ops;

int lan9303_probe(struct lan9303 *chip, struct device_node *np);
int lan9303_remove(struct lan9303 *chip);
