/* SPDX-License-Identifier: GPL-2.0 */
#ifndef BOOT_COMPRESSED_DECOMPRESSOR_H
#define BOOT_COMPRESSED_DECOMPRESSOR_H

#include <linaos/stddef.h>

#ifdef CONFIG_KERNEL_UNCOMPRESSED
static inline void *decompress_kernel(void) { return NULL; }
#else
void *decompress_kernel(void);
#endif
unsigned long mem_safe_offset(void);
void error(char *m);

struct vmlinaos_info {
	unsigned long default_lma;
	void (*entry)(void);
	unsigned long image_size;	/* does not include .bss */
	unsigned long bss_size;		/* uncompressed image .bss size */
	unsigned long bootdata_off;
	unsigned long bootdata_size;
	unsigned long bootdata_preserved_off;
	unsigned long bootdata_preserved_size;
	unsigned long dynsym_start;
	unsigned long rela_dyn_start;
	unsigned long rela_dyn_end;
};

extern char _vmlinaos_info[];
#define vmlinaos (*(struct vmlinaos_info *)_vmlinaos_info)

#endif /* BOOT_COMPRESSED_DECOMPRESSOR_H */
