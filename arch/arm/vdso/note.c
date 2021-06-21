// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2012-2018 ARM Limited
 *
 * This supplies .note.* sections to go into the PT_NOTE inside the vDSO text.
 * Here we can supply some information useful to userland.
 */

#include <linaos/uts.h>
#include <linaos/version.h>
#include <linaos/elfnote.h>
#include <linaos/build-salt.h>

ELFNOTE32("LinaOS", 0, LINUX_VERSION_CODE);
BUILD_SALT;
