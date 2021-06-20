# SPDX-License-Identifier: GPL-2.0
#
# arch/microblaze/boot/Makefile
#

targets := linaos.bin linaos.bin.gz linaos.bin.ub simpleImage.*

OBJCOPYFLAGS := -R .note -R .comment -R .note.gnu.build-id -O binary

$(obj)/linaos.bin: vmlinaos FORCE
	$(call if_changed,objcopy)

$(obj)/linaos.bin.ub: $(obj)/linaos.bin FORCE
	$(call if_changed,uimage)

$(obj)/linaos.bin.gz: $(obj)/linaos.bin FORCE
	$(call if_changed,gzip)

quiet_cmd_strip = STRIP   $< $@$2
	cmd_strip = $(STRIP) -K microblaze_start -K _end -K __log_buf \
				-K _fdt_start $< -o $@$2

UIMAGE_LOADADDR = $(CONFIG_KERNEL_BASE_ADDR)

$(obj)/simpleImage.$(DTB): vmlinaos FORCE
	$(call if_changed,objcopy)

$(obj)/simpleImage.$(DTB).ub: $(obj)/simpleImage.$(DTB) FORCE
	$(call if_changed,uimage)

$(obj)/simpleImage.$(DTB).unstrip: vmlinaos FORCE
	$(call if_changed,shipped)

$(obj)/simpleImage.$(DTB).strip: vmlinaos FORCE
	$(call if_changed,strip)
