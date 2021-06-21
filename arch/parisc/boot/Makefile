# SPDX-License-Identifier: GPL-2.0-only
#
# Makefile for the linaos parisc-specific parts of the boot image creator.
#

targets := image
targets += bzImage
subdir- := compressed

$(obj)/image: vmlinaos FORCE
	$(call if_changed,objcopy)

$(obj)/bzImage: $(obj)/compressed/vmlinaos FORCE
	$(call if_changed,objcopy)

$(obj)/compressed/vmlinaos: FORCE
	$(Q)$(MAKE) $(build)=$(obj)/compressed $@

install: $(CONFIGURE) $(obj)/bzImage
	sh -x  $(srctree)/$(obj)/install.sh $(KERNELRELEASE) $(obj)/bzImage \
	      System.map "$(INSTALL_PATH)"
