# $FreeBSD: stable/9/sys/modules/patm/Makefile 182668 2008-09-01 23:59:00Z imp $
#
# Author: Harti Brandt <harti@freebsd.org>
#
.PATH: ${.CURDIR}/../../dev/patm

KMOD=	if_patm
SRCS=	if_patm.c if_patm_attach.c if_patm_ioctl.c if_patm_intr.c \
	if_patm_tx.c if_patm_rx.c if_patm_rtables.c \
	device_if.h bus_if.h pci_if.h opt_inet.h opt_natm.h

CFLAGS+= -DENABLE_BPF
# CFLAGS+= -DPATM_DEBUG=0x0 -DINVARIANT_SUPPORT -DINVARIANTS -DDIAGNOSTIC

.if !defined(KERNBUILDDIR)
opt_inet.h:
	echo "#define INET 1" > ${.TARGET}

opt_natm.h:
	echo "#define NATM 1" > ${.TARGET}
.endif

.include <bsd.kmod.mk>
