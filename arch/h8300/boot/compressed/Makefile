# SPDX-License-Identifier: GPL-2.0
#
# linaos/arch/sh/boot/compressed/Makefile
#
# create a compressed vmlinaos image from the original vmlinaos
#

targets		:= vmlinaos vmlinaos.bin vmlinaos.bin.gz head.o misc.o piggy.o

OBJECTS = $(obj)/head.o $(obj)/misc.o

#
# IMAGE_OFFSET is the load offset of the compression loader
# Assign dummy values if these 2 variables are not defined,
# in order to suppress error message.
#
CONFIG_MEMORY_START     ?= 0x00400000
CONFIG_BOOT_LINK_OFFSET ?= 0x00280000
IMAGE_OFFSET := $(shell printf "0x%08x" $$(($(CONFIG_MEMORY_START)+$(CONFIG_BOOT_LINK_OFFSET))))

LIBGCC := $(shell $(CROSS-COMPILE)$(CC) $(KBUILD_CFLAGS) -print-libgcc-file-name 2>/dev/null)
LDFLAGS_vmlinaos := -Ttext $(IMAGE_OFFSET) -estartup -T $(obj)/vmlinaos.lds \
	--defsym output=$(CONFIG_MEMORY_START)

$(obj)/vmlinaos: $(OBJECTS) $(obj)/piggy.o $(LIBGCC) FORCE
	$(call if_changed,ld)

$(obj)/vmlinaos.bin: vmlinaos FORCE
	$(call if_changed,objcopy)

suffix-$(CONFIG_KERNEL_GZIP)    := gzip
suffix-$(CONFIG_KERNEL_LZO)     := lzo

$(obj)/vmlinaos.bin.$(suffix-y): $(obj)/vmlinaos.bin FORCE
	$(call if_changed,$(suffix-y))

LDFLAGS_piggy.o := -r --format binary --oformat elf32-h8300-linaos -T
OBJCOPYFLAGS := -O binary

$(obj)/piggy.o: $(obj)/vmlinaos.scr $(obj)/vmlinaos.bin.$(suffix-y) FORCE
	$(call if_changed,ld)

CFLAGS_misc.o = -O0
