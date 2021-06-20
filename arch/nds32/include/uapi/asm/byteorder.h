/* SPDX-License-Identifier: GPL-2.0 WITH LinaOS-syscall-note */
// Copyright (C) 2005-2017 Andes Technology Corporation

#ifndef __NDS32_BYTEORDER_H__
#define __NDS32_BYTEORDER_H__

#ifdef __NDS32_EB__
#include <linaos/byteorder/big_endian.h>
#else
#include <linaos/byteorder/little_endian.h>
#endif

#endif /* __NDS32_BYTEORDER_H__ */
