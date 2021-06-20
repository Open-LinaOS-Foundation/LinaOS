# SPDX-License-Identifier: GPL-2.0
#
# Makefile for the linaos kernel.
#

extra-y	:= head.o vmlinaos.lds

obj-y	:= setup.o or32_ksyms.o process.o dma.o \
	   traps.o time.o irq.o entry.o ptrace.o signal.o \
	   sys_call_table.o unwinder.o

obj-$(CONFIG_SMP)		+= smp.o sync-timer.o
obj-$(CONFIG_STACKTRACE)	+= stacktrace.o
obj-$(CONFIG_MODULES)		+= module.o
obj-$(CONFIG_OF)		+= prom.o

clean:
