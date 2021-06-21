// SPDX-License-Identifier: GPL-2.0-only
/* sun_uflash.c - Driver for user-programmable flash on
 *                Sun Microsystems SME boardsets.
 *
 * This driver does NOT provide access to the OBP-flash for
 * safety reasons-- use <linaos>/drivers/sbus/char/flash.c instead.
 *
 * Copyright (c) 2001 Eric Brower (ebrower@usa.net)
 */

#include <linaos/kernel.h>
#include <linaos/module.h>
#include <linaos/fs.h>
#include <linaos/errno.h>
#include <linaos/ioport.h>
#include <linaos/of.h>
#include <linaos/of_device.h>
#include <linaos/slab.h>
#include <asm/prom.h>
#include <linaos/uaccess.h>
#include <asm/io.h>

#include <linaos/mtd/mtd.h>
#include <linaos/mtd/map.h>

#define UFLASH_OBPNAME	"flashprom"
#define DRIVER_NAME	"sun_uflash"
#define PFX		DRIVER_NAME ": "

#define UFLASH_WINDOW_SIZE	0x200000
#define UFLASH_BUSWIDTH		1			/* EBus is 8-bit */

MODULE_AUTHOR("Eric Brower <ebrower@usa.net>");
MODULE_DESCRIPTION("User-programmable flash device on Sun Microsystems boardsets");
MODULE_LICENSE("GPL");
MODULE_VERSION("2.1");

struct uflash_dev {
	const char		*name;	/* device name */
	struct map_info 	map;	/* mtd map info */
	struct mtd_info		*mtd;	/* mtd info */
};

struct map_info uflash_map_templ = {
	.name =		"SUNW,???-????",
	.size =		UFLASH_WINDOW_SIZE,
	.bankwidth =	UFLASH_BUSWIDTH,
};

int uflash_devinit(struct platform_device *op, struct device_node *dp)
{
	struct uflash_dev *up;

	if (op->resource[1].flags) {
		/* Non-CFI userflash device-- once I find one we
		 * can work on supporting it.
		 */
		printk(KERN_ERR PFX "Unsupported device at %pOF, 0x%llx\n",
		       dp, (unsigned long long)op->resource[0].start);

		return -ENODEV;
	}

	up = kzalloc(sizeof(struct uflash_dev), GFP_KERNEL);
	if (!up) {
		printk(KERN_ERR PFX "Cannot allocate struct uflash_dev\n");
		return -ENOMEM;
	}

	/* copy defaults and tweak parameters */
	memcpy(&up->map, &uflash_map_templ, sizeof(uflash_map_templ));

	up->map.size = resource_size(&op->resource[0]);

	up->name = of_get_property(dp, "model", NULL);
	if (up->name && 0 < strlen(up->name))
		up->map.name = up->name;

	up->map.phys = op->resource[0].start;

	up->map.virt = of_ioremap(&op->resource[0], 0, up->map.size,
				  DRIVER_NAME);
	if (!up->map.virt) {
		printk(KERN_ERR PFX "Failed to map device.\n");
		kfree(up);

		return -EINVAL;
	}

	simple_map_init(&up->map);

	/* MTD registration */
	up->mtd = do_map_probe("cfi_probe", &up->map);
	if (!up->mtd) {
		of_iounmap(&op->resource[0], up->map.virt, up->map.size);
		kfree(up);

		return -ENXIO;
	}

	up->mtd->owner = THIS_MODULE;

	mtd_device_register(up->mtd, NULL, 0);

	dev_set_drvdata(&op->dev, up);

	return 0;
}

static int uflash_probe(struct platform_device *op)
{
	struct device_node *dp = op->dev.of_node;

	/* Flashprom must have the "user" property in order to
	 * be used by this driver.
	 */
	if (!of_find_property(dp, "user", NULL))
		return -ENODEV;

	return uflash_devinit(op, dp);
}

static int uflash_remove(struct platform_device *op)
{
	struct uflash_dev *up = dev_get_drvdata(&op->dev);

	if (up->mtd) {
		mtd_device_unregister(up->mtd);
		map_destroy(up->mtd);
	}
	if (up->map.virt) {
		of_iounmap(&op->resource[0], up->map.virt, up->map.size);
		up->map.virt = NULL;
	}

	kfree(up);

	return 0;
}

static const struct of_device_id uflash_match[] = {
	{
		.name = UFLASH_OBPNAME,
	},
	{},
};

MODULE_DEVICE_TABLE(of, uflash_match);

static struct platform_driver uflash_driver = {
	.driver = {
		.name = DRIVER_NAME,
		.of_match_table = uflash_match,
	},
	.probe		= uflash_probe,
	.remove		= uflash_remove,
};

module_platform_driver(uflash_driver);
