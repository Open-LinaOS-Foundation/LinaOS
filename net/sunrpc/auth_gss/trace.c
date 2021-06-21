// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2018, 2019 Oracle. All rights reserved.
 */

#include <linaos/sunrpc/clnt.h>
#include <linaos/sunrpc/sched.h>
#include <linaos/sunrpc/svc.h>
#include <linaos/sunrpc/svc_xprt.h>
#include <linaos/sunrpc/auth_gss.h>
#include <linaos/sunrpc/gss_err.h>

#define CREATE_TRACE_POINTS
#include <trace/events/rpcgss.h>
