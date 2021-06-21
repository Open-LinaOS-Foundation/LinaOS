# SPDX-License-Identifier: GPL-2.0-only
#
# linaos/arch/parisc/boot/compressed/Makefile
#
# create a compressed self-extracting vmlinaos image from the original vmlinaos
#

KCOV_INSTRUMENT := n
GCOV_PROFILE := n
UBSAN_SANITIZE := n

targets := vmlinaos.lds vmlinaos vmlinaos.bin vmlinaos.bin.gz vmlinaos.bin.bz2
targets += vmlinaos.bin.xz vmlinaos.bin.lzma vmlinaos.bin.lzo vmlinaos.bin.lz4
targets += misc.o piggy.o sizes.h head.o real2.o firmware.o
targets += real2.S firmware.c

KBUILD_CFLAGS := -D__KERNEL__ -O2 -DBOOTLOADER
KBUILD_CFLAGS += -DDISABLE_BRANCH_PROFILING
KBUILD_CFLAGS += -fno-strict-aliasing
KBUILD_CFLAGS += $(cflags-y) -fno-delete-null-pointer-checks -fno-builtin-printf
KBUILD_CFLAGS += -fno-PIE -mno-space-regs -mdisable-fpregs -Os
ifndef CONFIG_64BIT
KBUILD_CFLAGS += -mfast-indirect-calls
endif

OBJECTS += $(obj)/head.o $(obj)/real2.o $(obj)/firmware.o $(obj)/misc.o $(obj)/piggy.o

LDFLAGS_vmlinaos := -X -e startup --as-needed -T
$(obj)/vmlinaos: $(obj)/vmlinaos.lds $(OBJECTS) $(LIBGCC)
	$(call if_changed,ld)

sed-sizes := -e 's/^\([0-9a-fA-F]*\) . \(__bss_start\|_end\|parisc_kernel_start\)$$/\#define SZ\2 0x\1/p'

quiet_cmd_sizes = GEN $@
      cmd_sizes = $(NM) $< | sed -n $(sed-sizes) > $@

$(obj)/sizes.h: vmlinaos
	$(call if_changed,sizes)

AFLAGS_head.o += -I$(objtree)/$(obj) -DBOOTLOADER
$(obj)/head.o: $(obj)/sizes.h

CFLAGS_misc.o += -I$(objtree)/$(obj)
$(obj)/misc.o: $(obj)/sizes.h

$(obj)/firmware.o: $(obj)/firmware.c
$(obj)/firmware.c: $(srctree)/arch/$(SRCARCH)/kernel/firmware.c
	$(call cmd,shipped)

AFLAGS_real2.o += -DBOOTLOADER
$(obj)/real2.o: $(obj)/real2.S
$(obj)/real2.S: $(srctree)/arch/$(SRCARCH)/kernel/real2.S
	$(call cmd,shipped)

$(obj)/misc.o: $(obj)/sizes.h

CPPFLAGS_vmlinaos.lds += -I$(objtree)/$(obj) -DBOOTLOADER
$(obj)/vmlinaos.lds: $(obj)/sizes.h

OBJCOPYFLAGS_vmlinaos.bin := -R .comment -R .note -S
$(obj)/vmlinaos.bin: vmlinaos FORCE
	$(call if_changed,objcopy)

vmlinaos.bin.all-y := $(obj)/vmlinaos.bin

suffix-$(CONFIG_KERNEL_GZIP)  := gz
suffix-$(CONFIG_KERNEL_BZIP2) := bz2
suffix-$(CONFIG_KERNEL_LZ4)  := lz4
suffix-$(CONFIG_KERNEL_LZMA)  := lzma
suffix-$(CONFIG_KERNEL_LZO)  := lzo
suffix-$(CONFIG_KERNEL_XZ)  := xz

$(obj)/vmlinaos.bin.gz: $(vmlinaos.bin.all-y)
	$(call if_changed,gzip)
$(obj)/vmlinaos.bin.bz2: $(vmlinaos.bin.all-y)
	$(call if_changed,bzip2)
$(obj)/vmlinaos.bin.lz4: $(vmlinaos.bin.all-y)
	$(call if_changed,lz4)
$(obj)/vmlinaos.bin.lzma: $(vmlinaos.bin.all-y)
	$(call if_changed,lzma)
$(obj)/vmlinaos.bin.lzo: $(vmlinaos.bin.all-y)
	$(call if_changed,lzo)
$(obj)/vmlinaos.bin.xz: $(vmlinaos.bin.all-y)
	$(call if_changed,xzkern)

LDFLAGS_piggy.o := -r --format binary --oformat $(LD_BFD) -T
$(obj)/piggy.o: $(obj)/vmlinaos.scr $(obj)/vmlinaos.bin.$(suffix-y)
	$(call if_changed,ld)
