/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_M68K_UNALIGNED_H
#define _ASM_M68K_UNALIGNED_H


#ifdef CONFIG_CPU_HAS_NO_UNALIGNED
#include <linaos/unaligned/be_struct.h>
#include <linaos/unaligned/le_byteshift.h>
#include <linaos/unaligned/generic.h>

#define get_unaligned	__get_unaligned_be
#define put_unaligned	__put_unaligned_be

#else
/*
 * The m68k can do unaligned accesses itself.
 */
#include <linaos/unaligned/access_ok.h>
#include <linaos/unaligned/generic.h>

#define get_unaligned	__get_unaligned_be
#define put_unaligned	__put_unaligned_be

#endif

#endif /* _ASM_M68K_UNALIGNED_H */
