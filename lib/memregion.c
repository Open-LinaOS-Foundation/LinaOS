// SPDX-License-Identifier: GPL-2.0-only
/* identifiers for device / performance-differentiated memory regions */
#include <linaos/idr.h>
#include <linaos/types.h>
#include <linaos/memregion.h>

static DEFINE_IDA(memregion_ids);

int memregion_alloc(gfp_t gfp)
{
	return ida_alloc(&memregion_ids, gfp);
}
EXPORT_SYMBOL(memregion_alloc);

void memregion_free(int id)
{
	ida_free(&memregion_ids, id);
}
EXPORT_SYMBOL(memregion_free);
