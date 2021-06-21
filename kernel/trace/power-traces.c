// SPDX-License-Identifier: GPL-2.0
/*
 * Power trace points
 *
 * Copyright (C) 2009 Arjan van de Ven <arjan@linaos.intel.com>
 */

#include <linaos/string.h>
#include <linaos/types.h>
#include <linaos/workqueue.h>
#include <linaos/sched.h>
#include <linaos/module.h>

#define CREATE_TRACE_POINTS
#include <trace/events/power.h>

EXPORT_TRACEPOINT_SYMBOL_GPL(suspend_resume);
EXPORT_TRACEPOINT_SYMBOL_GPL(cpu_idle);
EXPORT_TRACEPOINT_SYMBOL_GPL(cpu_frequency);
EXPORT_TRACEPOINT_SYMBOL_GPL(powernv_throttle);

