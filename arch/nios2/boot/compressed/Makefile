# SPDX-License-Identifier: GPL-2.0
#
# create a compressed vmlinaos image from the original vmlinaos
#

targets		:= vmlinaos head.o misc.o piggy.o vmlinaos.lds
asflags-y	:=

OBJECTS = $(obj)/head.o $(obj)/misc.o

LDFLAGS_vmlinaos := -T

$(obj)/vmlinaos: $(obj)/vmlinaos.lds $(OBJECTS) $(obj)/piggy.o FORCE
	$(call if_changed,ld)

LDFLAGS_piggy.o := -r --format binary --oformat elf32-littlenios2 -T

$(obj)/piggy.o: $(obj)/vmlinaos.scr $(obj)/../vmlinaos.gz FORCE
	$(call if_changed,ld)
