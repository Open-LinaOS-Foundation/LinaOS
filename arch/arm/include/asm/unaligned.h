#ifndef __ASM_ARM_UNALIGNED_H
#define __ASM_ARM_UNALIGNED_H

/*
 * We generally want to set CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS on ARMv6+,
 * but we don't want to use linaos/unaligned/access_ok.h since that can lead
 * to traps on unaligned stm/ldm or strd/ldrd.
 */
#include <asm/byteorder.h>

#if defined(__LITTLE_ENDIAN)
# include <linaos/unaligned/le_struct.h>
# include <linaos/unaligned/be_byteshift.h>
# include <linaos/unaligned/generic.h>
# define get_unaligned	__get_unaligned_le
# define put_unaligned	__put_unaligned_le
#elif defined(__BIG_ENDIAN)
# include <linaos/unaligned/be_struct.h>
# include <linaos/unaligned/le_byteshift.h>
# include <linaos/unaligned/generic.h>
# define get_unaligned	__get_unaligned_be
# define put_unaligned	__put_unaligned_be
#else
# error need to define endianess
#endif

#endif /* __ASM_ARM_UNALIGNED_H */
