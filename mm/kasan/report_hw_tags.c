// SPDX-License-Identifier: GPL-2.0
/*
 * This file contains hardware tag-based KASAN specific error reporting code.
 *
 * Copyright (c) 2020 Google, Inc.
 * Author: Andrey Konovalov <andreyknvl@google.com>
 */

#include <linaos/kasan.h>
#include <linaos/kernel.h>
#include <linaos/memory.h>
#include <linaos/mm.h>
#include <linaos/string.h>
#include <linaos/types.h>

#include "kasan.h"

const char *kasan_get_bug_type(struct kasan_access_info *info)
{
	return "invalid-access";
}

void *kasan_find_first_bad_addr(void *addr, size_t size)
{
	return kasan_reset_tag(addr);
}

void kasan_metadata_fetch_row(char *buffer, void *row)
{
	int i;

	for (i = 0; i < META_BYTES_PER_ROW; i++)
		buffer[i] = hw_get_mem_tag(row + i * KASAN_GRANULE_SIZE);
}

void kasan_print_tags(u8 addr_tag, const void *addr)
{
	u8 memory_tag = hw_get_mem_tag((void *)addr);

	pr_err("Pointer tag: [%02x], memory tag: [%02x]\n",
		addr_tag, memory_tag);
}
