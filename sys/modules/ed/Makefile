# $FreeBSD: stable/9/sys/modules/ed/Makefile 150961 2005-10-05 05:26:03Z imp $

.PATH: ${.CURDIR}/../../dev/ed

KMOD=	if_ed
SRCS=	if_ed.c
SRCS+=	if_ed_novell.c if_ed_wd80x3.c if_ed_rtl80x9.c isa_if.h
.if ${MACHINE} == "pc98"
SRCS+=	if_ed_cbus.c
.else
SRCS+=	if_ed_isa.c if_ed_3c503.c if_ed_hpp.c if_ed_sic.c
.endif
SRCS+=	if_ed_pccard.c pccarddevs.h card_if.h
SRCS+=	if_ed_pci.c pci_if.h

SRCS+=	opt_ed.h bus_if.h device_if.h miibus_if.h

.include <bsd.kmod.mk>
