# $Id: Makefile,v 1.1 2002/11/24 20:40:11 max Exp $
# $FreeBSD: stable/9/sys/modules/netgraph/bluetooth/l2cap/Makefile 124472 2004-01-13 11:28:51Z ru $

.PATH: ${.CURDIR}/../../../../netgraph/bluetooth/l2cap

CFLAGS+=	-I${.CURDIR}/../../../../netgraph/bluetooth/include \
		-I${.CURDIR}/../../../../netgraph/bluetooth/l2cap

KMOD=		ng_l2cap
SRCS=		ng_l2cap_main.c ng_l2cap_cmds.c ng_l2cap_evnt.c \
		ng_l2cap_ulpi.c ng_l2cap_llpi.c ng_l2cap_misc.c

.include <bsd.kmod.mk>
