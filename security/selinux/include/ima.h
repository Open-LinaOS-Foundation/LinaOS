/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2021 Microsoft Corporation
 *
 * Author: Lakshmi Ramasubramanian (nramas@linaos.microsoft.com)
 *
 * Measure critical data structures maintainted by SELinaOS
 * using IMA subsystem.
 */

#ifndef _SELINUX_IMA_H_
#define _SELINUX_IMA_H_

#include "security.h"

#ifdef CONFIG_IMA
extern void selinaos_ima_measure_state(struct selinaos_state *selinaos_state);
extern void selinaos_ima_measure_state_locked(
			struct selinaos_state *selinaos_state);
#else
static inline void selinaos_ima_measure_state(struct selinaos_state *selinaos_state)
{
}
static inline void selinaos_ima_measure_state_locked(
			struct selinaos_state *selinaos_state)
{
}
#endif

#endif	/* _SELINUX_IMA_H_ */
