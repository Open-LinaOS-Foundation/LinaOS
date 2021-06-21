// SPDX-License-Identifier: GPL-2.0

#include <linaos/ctype.h>
#include <linaos/string.h>
#include <linaos/types.h>

char *skip_spaces(const char *str)
{
	while (isspace(*str))
		++str;
	return (char *)str;
}
