/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * env.c: ARCS environment variable routines.
 *
 * Copyright (C) 1996 David S. Miller (davem@davemloft.net)
 */
#include <linaos/init.h>
#include <linaos/kernel.h>
#include <linaos/string.h>

#include <asm/fw/arc/types.h>
#include <asm/sgialib.h>

PCHAR __init
ArcGetEnvironmentVariable(CHAR *name)
{
	return (CHAR *) ARC_CALL1(get_evar, name);
}
