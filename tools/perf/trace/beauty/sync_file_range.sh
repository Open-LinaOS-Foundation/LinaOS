#!/bin/sh
# SPDX-License-Identifier: LGPL-2.1

if [ $# -ne 1 ] ; then
	linaos_header_dir=tools/include/uapi/linaos
else
	linaos_header_dir=$1
fi

linaos_fs=${linaos_header_dir}/fs.h

printf "static const char *sync_file_range_flags[] = {\n"
regex='^[[:space:]]*#[[:space:]]*define[[:space:]]+SYNC_FILE_RANGE_([[:alnum:]_]+)[[:space:]]+([[:xdigit:]]+)[[:space:]]*.*'
egrep $regex ${linaos_fs} | \
	sed -r "s/$regex/\2 \1/g"	| \
	xargs printf "\t[ilog2(%s) + 1] = \"%s\",\n"
printf "};\n"
