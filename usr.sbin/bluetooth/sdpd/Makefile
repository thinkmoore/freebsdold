# $Id: Makefile,v 1.1 2004/01/20 21:27:55 max Exp $
# $FreeBSD: stable/9/usr.sbin/bluetooth/sdpd/Makefile 177059 2008-03-11 16:51:07Z emax $

PROG=		sdpd
MAN=		sdpd.8
SRCS=		bgd.c dun.c ftrn.c gn.c irmc.c irmc_command.c lan.c log.c \
		main.c nap.c opush.c panu.c profile.c provider.c sar.c scr.c \
		sd.c server.c sp.c srr.c ssar.c ssr.c sur.c uuid.c

CFLAGS+=	-I${.CURDIR}
WARNS?=		2

.include <bsd.prog.mk>
