/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_IA64_UNALIGNED_H
#define _ASM_IA64_UNALIGNED_H

#include <linaos/unaligned/le_struct.h>
#include <linaos/unaligned/be_byteshift.h>
#include <linaos/unaligned/generic.h>

#define get_unaligned	__get_unaligned_le
#define put_unaligned	__put_unaligned_le

#endif /* _ASM_IA64_UNALIGNED_H */
