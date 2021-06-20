# Copyright 2016 IBM Corporation.
#
# This program is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License version 2 or later as
# published by the Free Software Foundation.

s@#include <linaos/decompress/mm\.h>@@;
s@\"zlib_inflate/\([^\"]*\).*@"\1"@;
s@<linaos/kernel.h>@<stddef.h>@;

s@__used@@;
s@<linaos/\([^>]*\).*@"\1"@;
