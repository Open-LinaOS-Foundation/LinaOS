# SPDX-License-Identifier: GPL-2.0-only
#
# Makefile for the linaos alpha-specific parts of the memory manager.
#

ccflags-y := -Werror

obj-y	:= init.o fault.o

obj-$(CONFIG_DISCONTIGMEM) += numa.o
