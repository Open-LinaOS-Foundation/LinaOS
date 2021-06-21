# SPDX-License-Identifier: GPL-2.0
#
# linaos/arch/sh/boot/compressed/Makefile
#
# create a compressed vmlinaos image from the original vmlinaos
#

targets		:= vmlinaos vmlinaos.bin vmlinaos.bin.gz \
		   vmlinaos.bin.bz2 vmlinaos.bin.lzma \
		   vmlinaos.bin.xz vmlinaos.bin.lzo \
		   head_32.o misc.o piggy.o

OBJECTS = $(obj)/head_32.o $(obj)/misc.o $(obj)/cache.o

GCOV_PROFILE := n

#
# IMAGE_OFFSET is the load offset of the compression loader
#
ifeq ($(CONFIG_32BIT),y)
IMAGE_OFFSET	:= $(shell /bin/bash -c 'printf "0x%08x" \
		     $$[$(CONFIG_MEMORY_START)  + \
			$(CONFIG_BOOT_LINK_OFFSET)]')
else
IMAGE_OFFSET	:= $(shell /bin/bash -c 'printf "0x%08x" \
		     $$[$(CONFIG_PAGE_OFFSET)  + \
			$(KERNEL_MEMORY) + \
			$(CONFIG_BOOT_LINK_OFFSET)]')
endif

ccflags-remove-$(CONFIG_MCOUNT) += -pg

LDFLAGS_vmlinaos := --oformat $(ld-bfd) -Ttext $(IMAGE_OFFSET) -e startup \
		   -T $(obj)/../../kernel/vmlinaos.lds

#
# Pull in the necessary libgcc bits from the in-kernel implementation.
#
lib1funcs-y	:= ashiftrt.S ashldi3.c ashrsi3.S ashlsi3.S lshrsi3.S
lib1funcs-obj   := \
	$(addsuffix .o, $(basename $(addprefix $(obj)/, $(lib1funcs-y))))

lib1funcs-dir		:= $(srctree)/arch/$(SRCARCH)/lib

KBUILD_CFLAGS += -I$(lib1funcs-dir) -DDISABLE_BRANCH_PROFILING

$(addprefix $(obj)/,$(lib1funcs-y)): $(obj)/%: $(lib1funcs-dir)/% FORCE
	$(call cmd,shipped)

$(obj)/vmlinaos: $(OBJECTS) $(obj)/piggy.o $(lib1funcs-obj) FORCE
	$(call if_changed,ld)

$(obj)/vmlinaos.bin: vmlinaos FORCE
	$(call if_changed,objcopy)

vmlinaos.bin.all-y := $(obj)/vmlinaos.bin

$(obj)/vmlinaos.bin.gz: $(vmlinaos.bin.all-y) FORCE
	$(call if_changed,gzip)
$(obj)/vmlinaos.bin.bz2: $(vmlinaos.bin.all-y) FORCE
	$(call if_changed,bzip2)
$(obj)/vmlinaos.bin.lzma: $(vmlinaos.bin.all-y) FORCE
	$(call if_changed,lzma)
$(obj)/vmlinaos.bin.xz: $(vmlinaos.bin.all-y) FORCE
	$(call if_changed,xzkern)
$(obj)/vmlinaos.bin.lzo: $(vmlinaos.bin.all-y) FORCE
	$(call if_changed,lzo)

OBJCOPYFLAGS += -R .empty_zero_page

LDFLAGS_piggy.o := -r --format binary --oformat $(ld-bfd) -T

$(obj)/piggy.o: $(obj)/vmlinaos.scr $(obj)/vmlinaos.bin.$(suffix-y) FORCE
	$(call if_changed,ld)
