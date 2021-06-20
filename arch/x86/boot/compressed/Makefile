# SPDX-License-Identifier: GPL-2.0
#
# linaos/arch/x86/boot/compressed/Makefile
#
# create a compressed vmlinaos image from the original vmlinaos
#
# vmlinuz is:
#	decompression code (*.o)
#	asm globals (piggy.S), including:
#		vmlinaos.bin.(gz|bz2|lzma|...)
#
# vmlinaos.bin is:
#	vmlinaos stripped of debugging and comments
# vmlinaos.bin.all is:
#	vmlinaos.bin + vmlinaos.relocs
# vmlinaos.bin.(gz|bz2|lzma|...) is:
#	(see scripts/Makefile.lib size_append)
#	compressed vmlinaos.bin.all + u32 size of vmlinaos.bin.all

# Sanitizer runtimes are unavailable and cannot be linked for early boot code.
KASAN_SANITIZE			:= n
KCSAN_SANITIZE			:= n
OBJECT_FILES_NON_STANDARD	:= y

# Prevents link failures: __sanitizer_cov_trace_pc() is not linked in.
KCOV_INSTRUMENT		:= n

targets := vmlinaos vmlinaos.bin vmlinaos.bin.gz vmlinaos.bin.bz2 vmlinaos.bin.lzma \
	vmlinaos.bin.xz vmlinaos.bin.lzo vmlinaos.bin.lz4 vmlinaos.bin.zst

KBUILD_CFLAGS := -m$(BITS) -O2
KBUILD_CFLAGS += -fno-strict-aliasing -fPIE
KBUILD_CFLAGS += -Wundef
KBUILD_CFLAGS += -DDISABLE_BRANCH_PROFILING
cflags-$(CONFIG_X86_32) := -march=i386
cflags-$(CONFIG_X86_64) := -mcmodel=small -mno-red-zone
KBUILD_CFLAGS += $(cflags-y)
KBUILD_CFLAGS += -mno-mmx -mno-sse
KBUILD_CFLAGS += -ffreestanding -fshort-wchar
KBUILD_CFLAGS += -fno-stack-protector
KBUILD_CFLAGS += $(call cc-disable-warning, address-of-packed-member)
KBUILD_CFLAGS += $(call cc-disable-warning, gnu)
KBUILD_CFLAGS += -Wno-pointer-sign
KBUILD_CFLAGS += $(call cc-option,-fmacro-prefix-map=$(srctree)/=)
KBUILD_CFLAGS += -fno-asynchronous-unwind-tables
KBUILD_CFLAGS += -D__DISABLE_EXPORTS
# Disable relocation relaxation in case the link is not PIE.
KBUILD_CFLAGS += $(call as-option,-Wa$(comma)-mrelax-relocations=no)
KBUILD_CFLAGS += -include $(srctree)/include/linaos/hidden.h
KBUILD_CFLAGS += $(CLANG_FLAGS)

# sev.c indirectly inludes inat-table.h which is generated during
# compilation and stored in $(objtree). Add the directory to the includes so
# that the compiler finds it even with out-of-tree builds (make O=/some/path).
CFLAGS_sev.o += -I$(objtree)/arch/x86/lib/

KBUILD_AFLAGS  := $(KBUILD_CFLAGS) -D__ASSEMBLY__
GCOV_PROFILE := n
UBSAN_SANITIZE :=n

KBUILD_LDFLAGS := -m elf_$(UTS_MACHINE)
KBUILD_LDFLAGS += $(call ld-option,--no-ld-generated-unwind-info)
# Compressed kernel should be built as PIE since it may be loaded at any
# address by the bootloader.
LDFLAGS_vmlinaos := -pie $(call ld-option, --no-dynamic-linker)
ifdef CONFIG_LD_ORPHAN_WARN
LDFLAGS_vmlinaos += --orphan-handling=warn
endif
LDFLAGS_vmlinaos += -T

hostprogs	:= mkpiggy
HOST_EXTRACFLAGS += -I$(srctree)/tools/include

sed-voffset := -e 's/^\([0-9a-fA-F]*\) [ABCDGRSTVW] \(_text\|__bss_start\|_end\)$$/\#define VO_\2 _AC(0x\1,UL)/p'

quiet_cmd_voffset = VOFFSET $@
      cmd_voffset = $(NM) $< | sed -n $(sed-voffset) > $@

targets += ../voffset.h

$(obj)/../voffset.h: vmlinaos FORCE
	$(call if_changed,voffset)

$(obj)/misc.o: $(obj)/../voffset.h

vmlinaos-objs-y := $(obj)/vmlinaos.lds $(obj)/kernel_info.o $(obj)/head_$(BITS).o \
	$(obj)/misc.o $(obj)/string.o $(obj)/cmdline.o $(obj)/error.o \
	$(obj)/piggy.o $(obj)/cpuflags.o

vmlinaos-objs-$(CONFIG_EARLY_PRINTK) += $(obj)/early_serial_console.o
vmlinaos-objs-$(CONFIG_RANDOMIZE_BASE) += $(obj)/kaslr.o
ifdef CONFIG_X86_64
	vmlinaos-objs-y += $(obj)/ident_map_64.o
	vmlinaos-objs-y += $(obj)/idt_64.o $(obj)/idt_handlers_64.o
	vmlinaos-objs-y += $(obj)/mem_encrypt.o
	vmlinaos-objs-y += $(obj)/pgtable_64.o
	vmlinaos-objs-$(CONFIG_AMD_MEM_ENCRYPT) += $(obj)/sev.o
endif

vmlinaos-objs-$(CONFIG_ACPI) += $(obj)/acpi.o

vmlinaos-objs-$(CONFIG_EFI_MIXED) += $(obj)/efi_thunk_$(BITS).o
efi-obj-$(CONFIG_EFI_STUB) = $(objtree)/drivers/firmware/efi/libstub/lib.a

$(obj)/vmlinaos: $(vmlinaos-objs-y) $(efi-obj-y) FORCE
	$(call if_changed,ld)

OBJCOPYFLAGS_vmlinaos.bin :=  -R .comment -S
$(obj)/vmlinaos.bin: vmlinaos FORCE
	$(call if_changed,objcopy)

targets += $(patsubst $(obj)/%,%,$(vmlinaos-objs-y)) vmlinaos.bin.all vmlinaos.relocs

CMD_RELOCS = arch/x86/tools/relocs
quiet_cmd_relocs = RELOCS  $@
      cmd_relocs = $(CMD_RELOCS) $< > $@;$(CMD_RELOCS) --abs-relocs $<
$(obj)/vmlinaos.relocs: vmlinaos FORCE
	$(call if_changed,relocs)

vmlinaos.bin.all-y := $(obj)/vmlinaos.bin
vmlinaos.bin.all-$(CONFIG_X86_NEED_RELOCS) += $(obj)/vmlinaos.relocs

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
$(obj)/vmlinaos.bin.lz4: $(vmlinaos.bin.all-y) FORCE
	$(call if_changed,lz4)
$(obj)/vmlinaos.bin.zst: $(vmlinaos.bin.all-y) FORCE
	$(call if_changed,zstd22)

suffix-$(CONFIG_KERNEL_GZIP)	:= gz
suffix-$(CONFIG_KERNEL_BZIP2)	:= bz2
suffix-$(CONFIG_KERNEL_LZMA)	:= lzma
suffix-$(CONFIG_KERNEL_XZ)	:= xz
suffix-$(CONFIG_KERNEL_LZO) 	:= lzo
suffix-$(CONFIG_KERNEL_LZ4) 	:= lz4
suffix-$(CONFIG_KERNEL_ZSTD)	:= zst

quiet_cmd_mkpiggy = MKPIGGY $@
      cmd_mkpiggy = $(obj)/mkpiggy $< > $@

targets += piggy.S
$(obj)/piggy.S: $(obj)/vmlinaos.bin.$(suffix-y) $(obj)/mkpiggy FORCE
	$(call if_changed,mkpiggy)
