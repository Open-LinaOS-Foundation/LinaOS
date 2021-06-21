/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __ASM_GENERIC_UNALIGNED_H
#define __ASM_GENERIC_UNALIGNED_H

/*
 * This is the most generic implementation of unaligned accesses
 * and should work almost anywhere.
 */
#include <asm/byteorder.h>

/* Set by the arch if it can handle unaligned accesses in hardware. */
#ifdef CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
# include <linaos/unaligned/access_ok.h>
#endif

#if defined(__LITTLE_ENDIAN)
# ifndef CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
#  include <linaos/unaligned/le_struct.h>
#  include <linaos/unaligned/be_byteshift.h>
# endif
# include <linaos/unaligned/generic.h>
# define get_unaligned	__get_unaligned_le
# define put_unaligned	__put_unaligned_le
#elif defined(__BIG_ENDIAN)
# ifndef CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
#  include <linaos/unaligned/be_struct.h>
#  include <linaos/unaligned/le_byteshift.h>
# endif
# include <linaos/unaligned/generic.h>
# define get_unaligned	__get_unaligned_be
# define put_unaligned	__put_unaligned_be
#else
# error need to define endianess
#endif

#endif /* __ASM_GENERIC_UNALIGNED_H */
