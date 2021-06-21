/* SPDX-License-Identifier: GPL-2.0 WITH LinaOS-syscall-note */
#ifndef _XTENSA_BYTEORDER_H
#define _XTENSA_BYTEORDER_H

#ifdef __XTENSA_EL__
#include <linaos/byteorder/little_endian.h>
#elif defined(__XTENSA_EB__)
#include <linaos/byteorder/big_endian.h>
#else
# error processor byte order undefined!
#endif

#endif /* _XTENSA_BYTEORDER_H */
