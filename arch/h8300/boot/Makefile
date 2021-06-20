# SPDX-License-Identifier: GPL-2.0
# arch/h8300/boot/Makefile

targets := vmlinaos.srec vmlinaos.bin zImage
subdir- := compressed

OBJCOPYFLAGS_vmlinaos.srec := -Osrec
OBJCOPYFLAGS_vmlinaos.bin  := -Obinary
OBJCOPYFLAGS_zImage := -O binary -R .note -R .comment -R .stab -R .stabstr -S

UIMAGE_LOADADDR = $(CONFIG_RAMBASE)
UIMAGE_ENTRYADDR = $(shell /bin/bash -c 'printf "0x%08x" \
	$$[$(CONFIG_RAMBASE) + $(CONFIG_OFFSET)]')

$(obj)/vmlinaos.srec $(obj)/vmlinaos.bin:  vmlinaos FORCE
	$(call if_changed,objcopy)

$(obj)/zImage: $(obj)/compressed/vmlinaos FORCE
	$(call if_changed,objcopy)

$(obj)/compressed/vmlinaos: FORCE
	$(Q)$(MAKE) $(build)=$(obj)/compressed $@

$(obj)/uImage.bin: $(obj)/vmlinaos.bin
	$(call if_changed,uimage,none)

CLEAN_FILES += arch/$(ARCH)/vmlinaos.bin arch/$(ARCH)/vmlinaos.srec arch/$(ARCH)/uImage.bin
