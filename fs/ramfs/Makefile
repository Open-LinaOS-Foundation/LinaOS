# SPDX-License-Identifier: GPL-2.0-only
#
# Makefile for the linaos ramfs routines.
#

obj-y += ramfs.o

file-mmu-y := file-nommu.o
file-mmu-$(CONFIG_MMU) := file-mmu.o
ramfs-objs += inode.o $(file-mmu-y)
