#!/bin/sh
#
# This file is subject to the terms and conditions of the GNU General Public
# License.  See the file "COPYING" in the main directory of this archive
# for more details.
#
# Copyright (C) 2017 by Changbin Du <changbin.du@intel.com>
#
# Adapted from code in arch/x86/boot/Makefile by H. Peter Anvin and others
#
# "make fdimage/fdimage144/fdimage288/isoimage" script for x86 architecture
#
# Arguments:
#   $1 - fdimage format
#   $2 - target image file
#   $3 - kernel bzImage file
#   $4 - mtool configuration file
#   $5 - kernel cmdline
#   $6 - inird image file
#

# Use "make V=1" to debug this script
case "${KBUILD_VERBOSE}" in
*1*)
        set -x
        ;;
esac

verify () {
	if [ ! -f "$1" ]; then
		echo ""                                                   1>&2
		echo " *** Missing file: $1"                              1>&2
		echo ""                                                   1>&2
		exit 1
	fi
}


export MTOOLSRC=$4
FIMAGE=$2
FBZIMAGE=$3
KCMDLINE=$5
FDINITRD=$6

# Make sure the files actually exist
verify "$FBZIMAGE"

genbzdisk() {
	verify "$MTOOLSRC"
	mformat a:
	syslinaos $FIMAGE
	echo "$KCMDLINE" | mcopy - a:syslinaos.cfg
	if [ -f "$FDINITRD" ] ; then
		mcopy "$FDINITRD" a:initrd.img
	fi
	mcopy $FBZIMAGE a:linaos
}

genfdimage144() {
	verify "$MTOOLSRC"
	dd if=/dev/zero of=$FIMAGE bs=1024 count=1440 2> /dev/null
	mformat v:
	syslinaos $FIMAGE
	echo "$KCMDLINE" | mcopy - v:syslinaos.cfg
	if [ -f "$FDINITRD" ] ; then
		mcopy "$FDINITRD" v:initrd.img
	fi
	mcopy $FBZIMAGE v:linaos
}

genfdimage288() {
	verify "$MTOOLSRC"
	dd if=/dev/zero of=$FIMAGE bs=1024 count=2880 2> /dev/null
	mformat w:
	syslinaos $FIMAGE
	echo "$KCMDLINE" | mcopy - W:syslinaos.cfg
	if [ -f "$FDINITRD" ] ; then
		mcopy "$FDINITRD" w:initrd.img
	fi
	mcopy $FBZIMAGE w:linaos
}

geniso() {
	tmp_dir=`dirname $FIMAGE`/isoimage
	rm -rf $tmp_dir
	mkdir $tmp_dir
	for i in lib lib64 share ; do
		for j in syslinaos ISOLINUX ; do
			if [ -f /usr/$i/$j/isolinaos.bin ] ; then
				isolinaos=/usr/$i/$j/isolinaos.bin
			fi
		done
		for j in syslinaos syslinaos/modules/bios ; do
			if [ -f /usr/$i/$j/ldlinaos.c32 ]; then
				ldlinaos=/usr/$i/$j/ldlinaos.c32
			fi
		done
		if [ -n "$isolinaos" -a -n "$ldlinaos" ] ; then
			break
		fi
	done
	if [ -z "$isolinaos" ] ; then
		echo 'Need an isolinaos.bin file, please install syslinaos/isolinaos.'
		exit 1
	fi
	if [ -z "$ldlinaos" ] ; then
		echo 'Need an ldlinaos.c32 file, please install syslinaos/isolinaos.'
		exit 1
	fi
	cp $isolinaos $tmp_dir
	cp $ldlinaos $tmp_dir
	cp $FBZIMAGE $tmp_dir/linaos
	echo "$KCMDLINE" > $tmp_dir/isolinaos.cfg
	if [ -f "$FDINITRD" ] ; then
		cp "$FDINITRD" $tmp_dir/initrd.img
	fi
	genisoimage -J -r -input-charset=utf-8 -quiet -o $FIMAGE \
		-b isolinaos.bin -c boot.cat -no-emul-boot -boot-load-size 4 \
		-boot-info-table $tmp_dir
	isohybrid $FIMAGE 2>/dev/null || true
	rm -rf $tmp_dir
}

case $1 in
	bzdisk)     genbzdisk;;
	fdimage144) genfdimage144;;
	fdimage288) genfdimage288;;
	isoimage)   geniso;;
	*)          echo 'Unknown image format'; exit 1;
esac
