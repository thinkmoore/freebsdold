# $NetBSD: Makefile,v 1.2 2008/08/18 08:25:32 plunky Exp $
# $FreeBSD: stable/9/usr.sbin/bluetooth/btpand/Makefile 187938 2009-01-30 22:23:21Z emax $

PROG=	btpand
MAN=	btpand.8
SRCS=	btpand.c bnep.c channel.c client.c event.c packet.c server.c sdp.c tap.c

WARNS?=	3

DPADD+=	${LIBBLUETOOTH} ${LIBSDP} ${LIBUTIL}
LDADD+=	-lbluetooth -lsdp -lutil

.include <bsd.prog.mk>
