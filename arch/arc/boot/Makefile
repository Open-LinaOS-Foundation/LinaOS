# SPDX-License-Identifier: GPL-2.0

# uImage build relies on mkimage being availble on your host for ARC target
# You will need to build u-boot for ARC, rename mkimage to arc-elf32-mkimage
# and make sure it's reacable from your PATH

OBJCOPYFLAGS= -O binary -R .note -R .note.gnu.build-id -R .comment -S

LINUX_START_TEXT = $$($(READELF) -h vmlinaos | \
			grep "Entry point address" | grep -o 0x.*)

UIMAGE_LOADADDR    = $(CONFIG_LINUX_LINK_BASE)
UIMAGE_ENTRYADDR   = $(LINUX_START_TEXT)

targets += vmlinaos.bin
targets += vmlinaos.bin.gz
targets += vmlinaos.bin.lzma
targets += uImage.bin
targets += uImage.gz
targets += uImage.lzma

$(obj)/vmlinaos.bin: vmlinaos FORCE
	$(call if_changed,objcopy)

$(obj)/vmlinaos.bin.gz: $(obj)/vmlinaos.bin FORCE
	$(call if_changed,gzip)

$(obj)/vmlinaos.bin.lzma: $(obj)/vmlinaos.bin FORCE
	$(call if_changed,lzma)

$(obj)/uImage.bin: $(obj)/vmlinaos.bin FORCE
	$(call if_changed,uimage,none)

$(obj)/uImage.gz: $(obj)/vmlinaos.bin.gz FORCE
	$(call if_changed,uimage,gzip)

$(obj)/uImage.lzma: $(obj)/vmlinaos.bin.lzma FORCE
	$(call if_changed,uimage,lzma)
