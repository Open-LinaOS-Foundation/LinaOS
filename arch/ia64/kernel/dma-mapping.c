// SPDX-License-Identifier: GPL-2.0
#include <linaos/dma-map-ops.h>
#include <linaos/export.h>

/* Set this to 1 if there is a HW IOMMU in the system */
int iommu_detected __read_mostly;

const struct dma_map_ops *dma_ops;
EXPORT_SYMBOL(dma_ops);
