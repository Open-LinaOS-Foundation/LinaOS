#!/bin/sh
# SPDX-License-Identifier: LGPL-2.1

if [ $# -ne 1 ] ; then
	linaos_header_dir=tools/include/uapi/linaos
else
	linaos_header_dir=$1
fi

linaos_mount=${linaos_header_dir}/mount.h

printf "static const char *fsconfig_cmds[] = {\n"
ms='[[:space:]]*'
sed -nr "s/^${ms}FSCONFIG_([[:alnum:]_]+)${ms}=${ms}([[:digit:]]+)${ms},.*/\t[\2] = \"\1\",/p" \
	${linaos_mount}
printf "};\n"
