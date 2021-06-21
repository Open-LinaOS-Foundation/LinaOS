/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __A_OUT_GNU_H__
#define __A_OUT_GNU_H__

#include <uapi/linaos/a.out.h>

#ifndef __ASSEMBLY__
#ifdef linaos
#include <asm/page.h>
#if defined(__i386__) || defined(__mc68000__)
#else
#ifndef SEGMENT_SIZE
#define SEGMENT_SIZE	PAGE_SIZE
#endif
#endif
#endif
#endif /*__ASSEMBLY__ */
#endif /* __A_OUT_GNU_H__ */
