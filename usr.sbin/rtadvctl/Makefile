# $FreeBSD: stable/9/usr.sbin/rtadvctl/Makefile 224144 2011-07-17 19:24:54Z hrs $
#
.PATH:	${.CURDIR}/../rtadvd

PROG=	rtadvctl
MAN=	rtadvctl.8

SRCS=	rtadvctl.c control.c control_client.c if.c timer_subr.c

CFLAGS+= -I${.CURDIR} -I${.CURDIR}/../rtadvd
WARNS?=	1

.include <bsd.prog.mk>
