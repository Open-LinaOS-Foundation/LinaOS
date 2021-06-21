// SPDX-License-Identifier: GPL-2.0
/*
 * lib/bust_spinlocks.c
 *
 * Provides a minimal bust_spinlocks for architectures which don't
 * have one of their own.
 *
 * bust_spinlocks() clears any spinlocks which would prevent oops, die(), BUG()
 * and panic() information from reaching the user.
 */

#include <linaos/kernel.h>
#include <linaos/printk.h>
#include <linaos/spinlock.h>
#include <linaos/tty.h>
#include <linaos/wait.h>
#include <linaos/vt_kern.h>
#include <linaos/console.h>

void bust_spinlocks(int yes)
{
	if (yes) {
		++oops_in_progress;
	} else {
#ifdef CONFIG_VT
		unblank_screen();
#endif
		console_unblank();
		if (--oops_in_progress == 0)
			wake_up_klogd();
	}
}
