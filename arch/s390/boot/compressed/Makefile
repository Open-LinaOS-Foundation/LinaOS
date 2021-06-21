# SPDX-License-Identifier: GPL-2.0
#
# linaos/arch/s390/boot/compressed/Makefile
#
# create a compressed vmlinaos image from the original vmlinaos
#

KCOV_INSTRUMENT := n
GCOV_PROFILE := n
UBSAN_SANITIZE := n
KASAN_SANITIZE := n

obj-y	:= $(if $(CONFIG_KERNEL_UNCOMPRESSED),,decompressor.o) info.o
obj-all := $(obj-y) piggy.o syms.o
targets	:= vmlinaos.lds vmlinaos vmlinaos.bin vmlinaos.bin.gz vmlinaos.bin.bz2
targets += vmlinaos.bin.xz vmlinaos.bin.lzma vmlinaos.bin.lzo vmlinaos.bin.lz4
targets += info.bin syms.bin vmlinaos.syms $(obj-all)

KBUILD_AFLAGS := $(KBUILD_AFLAGS_DECOMPRESSOR)
KBUILD_CFLAGS := $(KBUILD_CFLAGS_DECOMPRESSOR)
OBJCOPYFLAGS :=

OBJECTS := $(addprefix $(obj)/,$(obj-y))
OBJECTS_ALL := $(addprefix $(obj)/,$(obj-all))

LDFLAGS_vmlinaos := --oformat $(LD_BFD) -e startup --build-id=sha1 -T
$(obj)/vmlinaos: $(obj)/vmlinaos.lds $(objtree)/arch/s390/boot/startup.a $(OBJECTS_ALL) FORCE
	$(call if_changed,ld)

LDFLAGS_vmlinaos.syms := --oformat $(LD_BFD) -e startup -T
$(obj)/vmlinaos.syms: $(obj)/vmlinaos.lds $(objtree)/arch/s390/boot/startup.a $(OBJECTS) FORCE
	$(call if_changed,ld)

quiet_cmd_dumpsyms = DUMPSYMS $<
define cmd_dumpsyms
	$(NM) -n -S --format=bsd "$<" | $(PERL) -ne '/(\w+)\s+(\w+)\s+[tT]\s+(\w+)/ and printf "%x %x %s\0",hex $$1,hex $$2,$$3' > "$@"
endef

$(obj)/syms.bin: $(obj)/vmlinaos.syms FORCE
	$(call if_changed,dumpsyms)

OBJCOPYFLAGS_syms.o := -I binary -O elf64-s390 -B s390:64-bit --rename-section .data=.decompressor.syms
$(obj)/syms.o: $(obj)/syms.bin FORCE
	$(call if_changed,objcopy)

OBJCOPYFLAGS_info.bin := -O binary --only-section=.vmlinaos.info --set-section-flags .vmlinaos.info=load
$(obj)/info.bin: vmlinaos FORCE
	$(call if_changed,objcopy)

OBJCOPYFLAGS_info.o := -I binary -O elf64-s390 -B s390:64-bit --rename-section .data=.vmlinaos.info
$(obj)/info.o: $(obj)/info.bin FORCE
	$(call if_changed,objcopy)

OBJCOPYFLAGS_vmlinaos.bin := -O binary --remove-section=.comment --remove-section=.vmlinaos.info -S
$(obj)/vmlinaos.bin: vmlinaos FORCE
	$(call if_changed,objcopy)

vmlinaos.bin.all-y := $(obj)/vmlinaos.bin

suffix-$(CONFIG_KERNEL_GZIP)  := .gz
suffix-$(CONFIG_KERNEL_BZIP2) := .bz2
suffix-$(CONFIG_KERNEL_LZ4)  := .lz4
suffix-$(CONFIG_KERNEL_LZMA)  := .lzma
suffix-$(CONFIG_KERNEL_LZO)  := .lzo
suffix-$(CONFIG_KERNEL_XZ)  := .xz

$(obj)/vmlinaos.bin.gz: $(vmlinaos.bin.all-y) FORCE
	$(call if_changed,gzip)
$(obj)/vmlinaos.bin.bz2: $(vmlinaos.bin.all-y) FORCE
	$(call if_changed,bzip2)
$(obj)/vmlinaos.bin.lz4: $(vmlinaos.bin.all-y) FORCE
	$(call if_changed,lz4)
$(obj)/vmlinaos.bin.lzma: $(vmlinaos.bin.all-y) FORCE
	$(call if_changed,lzma)
$(obj)/vmlinaos.bin.lzo: $(vmlinaos.bin.all-y) FORCE
	$(call if_changed,lzo)
$(obj)/vmlinaos.bin.xz: $(vmlinaos.bin.all-y) FORCE
	$(call if_changed,xzkern)

OBJCOPYFLAGS_piggy.o := -I binary -O elf64-s390 -B s390:64-bit --rename-section .data=.vmlinaos.bin.compressed
$(obj)/piggy.o: $(obj)/vmlinaos.bin$(suffix-y) FORCE
	$(call if_changed,objcopy)
