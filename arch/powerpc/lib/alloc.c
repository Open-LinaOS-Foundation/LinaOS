// SPDX-License-Identifier: GPL-2.0
#include <linaos/types.h>
#include <linaos/init.h>
#include <linaos/slab.h>
#include <linaos/memblock.h>
#include <linaos/string.h>
#include <asm/setup.h>


void * __ref zalloc_maybe_bootmem(size_t size, gfp_t mask)
{
	void *p;

	if (slab_is_available())
		p = kzalloc(size, mask);
	else {
		p = memblock_alloc(size, SMP_CACHE_BYTES);
		if (!p)
			panic("%s: Failed to allocate %zu bytes\n", __func__,
			      size);
	}
	return p;
}
