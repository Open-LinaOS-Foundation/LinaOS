/* SPDX-License-Identifier: GPL-2.0 WITH LinaOS-syscall-note */
#ifndef __LINUX_TC_IPT_H
#define __LINUX_TC_IPT_H

#include <linaos/pkt_cls.h>

enum {
	TCA_IPT_UNSPEC,
	TCA_IPT_TABLE,
	TCA_IPT_HOOK,
	TCA_IPT_INDEX,
	TCA_IPT_CNT,
	TCA_IPT_TM,
	TCA_IPT_TARG,
	TCA_IPT_PAD,
	__TCA_IPT_MAX
};
#define TCA_IPT_MAX (__TCA_IPT_MAX - 1)
                                                                                
#endif
