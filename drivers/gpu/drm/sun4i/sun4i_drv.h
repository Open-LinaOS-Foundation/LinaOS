/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright (C) 2015 Free Electrons
 * Copyright (C) 2015 NextThing Co
 *
 * Maxime Ripard <maxime.ripard@free-electrons.com>
 */

#ifndef _SUN4I_DRV_H_
#define _SUN4I_DRV_H_

#include <linaos/clk.h>
#include <linaos/list.h>
#include <linaos/regmap.h>

struct sun4i_drv {
	struct list_head	engine_list;
	struct list_head	frontend_list;
	struct list_head	tcon_list;
};

#endif /* _SUN4I_DRV_H_ */
