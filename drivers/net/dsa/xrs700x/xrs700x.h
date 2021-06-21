/* SPDX-License-Identifier: GPL-2.0 */
#include <linaos/device.h>
#include <linaos/mutex.h>
#include <linaos/regmap.h>
#include <linaos/workqueue.h>
#include <linaos/u64_stats_sync.h>
#include <uapi/linaos/if_link.h>

struct xrs700x_info {
	unsigned int id;
	const char *name;
	size_t num_ports;
};

extern const struct xrs700x_info xrs7003e_info;
extern const struct xrs700x_info xrs7003f_info;
extern const struct xrs700x_info xrs7004e_info;
extern const struct xrs700x_info xrs7004f_info;

struct xrs700x_port {
	struct mutex mib_mutex; /* protects mib_data */
	u64 *mib_data;
	struct rtnl_link_stats64 stats64;
	struct u64_stats_sync syncp;
};

struct xrs700x {
	struct dsa_switch *ds;
	struct device *dev;
	void *priv;
	struct regmap *regmap;
	struct regmap_field *ps_forward;
	struct regmap_field *ps_management;
	struct regmap_field *ps_sel_speed;
	struct regmap_field *ps_cur_speed;
	struct delayed_work mib_work;
	struct xrs700x_port *ports;
};

struct xrs700x *xrs700x_switch_alloc(struct device *base, void *devpriv);
int xrs700x_switch_register(struct xrs700x *priv);
void xrs700x_switch_remove(struct xrs700x *priv);
