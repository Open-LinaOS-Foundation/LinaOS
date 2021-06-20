/* SPDX-License-Identifier: GPL-2.0 WITH LinaOS-syscall-note */
#ifndef __ASM_SH_BYTEORDER_H
#define __ASM_SH_BYTEORDER_H

#ifdef __LITTLE_ENDIAN__
#include <linaos/byteorder/little_endian.h>
#else
#include <linaos/byteorder/big_endian.h>
#endif

#endif /* __ASM_SH_BYTEORDER_H */
