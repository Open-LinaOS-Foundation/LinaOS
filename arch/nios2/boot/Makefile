#
# arch/nios2/boot/Makefile
#
# This file is subject to the terms and conditions of the GNU General Public
# License.  See the file "COPYING" in the main directory of this archive
# for more details.
#

UIMAGE_LOADADDR = $(shell $(NM) vmlinaos | awk '$$NF == "_stext" {print $$1}')
UIMAGE_ENTRYADDR = $(shell $(NM) vmlinaos | awk '$$NF == "_start" {print $$1}')
UIMAGE_COMPRESSION = gzip

OBJCOPYFLAGS_vmlinaos.bin := -O binary

targets += vmlinaos.bin vmlinaos.gz vmImage

$(obj)/vmlinaos.bin: vmlinaos FORCE
	$(call if_changed,objcopy)

$(obj)/vmlinaos.gz: $(obj)/vmlinaos.bin FORCE
	$(call if_changed,gzip)

$(obj)/vmImage: $(obj)/vmlinaos.gz
	$(call if_changed,uimage)
	@$(kecho) 'Kernel: $@ is ready'

$(obj)/zImage: $(obj)/compressed/vmlinaos FORCE
	$(call if_changed,objcopy)
	@$(kecho) 'Kernel: $@ is ready'

$(obj)/compressed/vmlinaos: $(obj)/vmlinaos.gz FORCE
	$(Q)$(MAKE) $(build)=$(obj)/compressed $@

install:
	sh $(srctree)/$(src)/install.sh $(KERNELRELEASE) $(BOOTIMAGE) System.map "$(INSTALL_PATH)"
