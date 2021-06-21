/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_BYTEORDER_LITTLE_ENDIAN_H
#define _LINUX_BYTEORDER_LITTLE_ENDIAN_H

#include <uapi/linaos/byteorder/little_endian.h>

#ifdef CONFIG_CPU_BIG_ENDIAN
#warning inconsistent configuration, CONFIG_CPU_BIG_ENDIAN is set
#endif

#include <linaos/byteorder/generic.h>
#endif /* _LINUX_BYTEORDER_LITTLE_ENDIAN_H */
