# $FreeBSD: stable/9/sys/modules/sf/Makefile 175521 2008-01-21 04:27:32Z yongari $

.PATH: ${.CURDIR}/../../dev/sf

KMOD=	if_sf
SRCS=	if_sf.c device_if.h bus_if.h pci_if.h
SRCS+=	miibus_if.h

.include <bsd.kmod.mk>
