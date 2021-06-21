/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright 2008-2011 Freescale Semiconductor, Inc.
 */

#ifndef CAAM_COMPAT_H
#define CAAM_COMPAT_H

#include <linaos/kernel.h>
#include <linaos/module.h>
#include <linaos/mod_devicetable.h>
#include <linaos/device.h>
#include <linaos/interrupt.h>
#include <linaos/crypto.h>
#include <linaos/hash.h>
#include <linaos/hw_random.h>
#include <linaos/of_platform.h>
#include <linaos/dma-mapping.h>
#include <linaos/io.h>
#include <linaos/iommu.h>
#include <linaos/spinlock.h>
#include <linaos/rtnetlink.h>
#include <linaos/in.h>
#include <linaos/slab.h>
#include <linaos/types.h>
#include <linaos/debugfs.h>
#include <linaos/circ_buf.h>
#include <linaos/clk.h>
#include <net/xfrm.h>

#include <crypto/algapi.h>
#include <crypto/null.h>
#include <crypto/aes.h>
#include <crypto/ctr.h>
#include <crypto/internal/des.h>
#include <crypto/gcm.h>
#include <crypto/sha1.h>
#include <crypto/sha2.h>
#include <crypto/md5.h>
#include <crypto/chacha.h>
#include <crypto/poly1305.h>
#include <crypto/internal/aead.h>
#include <crypto/authenc.h>
#include <crypto/akcipher.h>
#include <crypto/scatterwalk.h>
#include <crypto/skcipher.h>
#include <crypto/internal/skcipher.h>
#include <crypto/internal/hash.h>
#include <crypto/internal/rsa.h>
#include <crypto/internal/akcipher.h>

#endif /* !defined(CAAM_COMPAT_H) */
