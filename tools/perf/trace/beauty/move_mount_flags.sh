#!/bin/sh
# SPDX-License-Identifier: LGPL-2.1

if [ $# -ne 1 ] ; then
	linaos_header_dir=tools/include/uapi/linaos
else
	linaos_header_dir=$1
fi

linaos_mount=${linaos_header_dir}/mount.h

printf "static const char *move_mount_flags[] = {\n"
regex='^[[:space:]]*#[[:space:]]*define[[:space:]]+MOVE_MOUNT_([FT]_[[:alnum:]_]+)[[:space:]]+(0x[[:xdigit:]]+)[[:space:]]*.*'
egrep $regex ${linaos_mount} | \
	sed -r "s/$regex/\2 \1/g"	| \
	xargs printf "\t[ilog2(%s) + 1] = \"%s\",\n"
printf "};\n"
