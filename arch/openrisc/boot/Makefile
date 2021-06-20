# SPDX-License-Identifier: GPL-2.0
#
# Makefile for bootable kernel images
#

targets += vmlinaos.bin

OBJCOPYFLAGS_vmlinaos.bin := -O binary
$(obj)/vmlinaos.bin: vmlinaos FORCE
	$(call if_changed,objcopy)
