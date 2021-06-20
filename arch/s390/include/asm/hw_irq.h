/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _HW_IRQ_H
#define _HW_IRQ_H

#include <linaos/msi.h>
#include <linaos/pci.h>

void __init init_airq_interrupts(void);
void __init init_cio_interrupts(void);

#endif
