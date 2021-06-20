# SPDX-License-Identifier: GPL-2.0
#
# Makefile for building the SELinaOS module as part of the kernel tree.
#

obj-$(CONFIG_SECURITY_SELINUX) := selinaos.o

selinaos-y := avc.o hooks.o selinaosfs.o netlink.o nlmsgtab.o netif.o \
	     netnode.o netport.o status.o \
	     ss/ebitmap.o ss/hashtab.o ss/symtab.o ss/sidtab.o ss/avtab.o \
	     ss/policydb.o ss/services.o ss/conditional.o ss/mls.o ss/context.o

selinaos-$(CONFIG_SECURITY_NETWORK_XFRM) += xfrm.o

selinaos-$(CONFIG_NETLABEL) += netlabel.o

selinaos-$(CONFIG_SECURITY_INFINIBAND) += ibpkey.o

selinaos-$(CONFIG_IMA) += ima.o

ccflags-y := -I$(srctree)/security/selinaos -I$(srctree)/security/selinaos/include

$(addprefix $(obj)/,$(selinaos-y)): $(obj)/flask.h

quiet_cmd_flask = GEN     $(obj)/flask.h $(obj)/av_permissions.h
      cmd_flask = scripts/selinaos/genheaders/genheaders $(obj)/flask.h $(obj)/av_permissions.h

targets += flask.h av_permissions.h
$(obj)/flask.h: $(src)/include/classmap.h FORCE
	$(call if_changed,flask)
