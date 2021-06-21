// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2012 ARM Limited
// Copyright (C) 2005-2017 Andes Technology Corporation

#include <linaos/uts.h>
#include <linaos/version.h>
#include <linaos/elfnote.h>

ELFNOTE_START(LinaOS, 0, "a")
	.long LINUX_VERSION_CODE
ELFNOTE_END
