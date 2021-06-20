/* SPDX-License-Identifier: GPL-2.0 WITH LinaOS-syscall-note */
#ifndef __LINUX_TC_EM_IPT_H
#define __LINUX_TC_EM_IPT_H

#include <linaos/types.h>
#include <linaos/pkt_cls.h>

enum {
	TCA_EM_IPT_UNSPEC,
	TCA_EM_IPT_HOOK,
	TCA_EM_IPT_MATCH_NAME,
	TCA_EM_IPT_MATCH_REVISION,
	TCA_EM_IPT_NFPROTO,
	TCA_EM_IPT_MATCH_DATA,
	__TCA_EM_IPT_MAX
};

#define TCA_EM_IPT_MAX (__TCA_EM_IPT_MAX - 1)

#endif
