#	From: @(#)Makefile	8.1 (Berkeley) 6/6/93
# $FreeBSD: stable/9/usr.sbin/lpr/pac/Makefile 98702 2002-06-23 20:57:18Z gad $

.PATH: ${.CURDIR}/../common_source

PROG=	pac
MAN=	pac.8

CFLAGS+= -I${.CURDIR}/../common_source

DPADD=	${LIBLPR}
LDADD=	${LIBLPR}

.include <bsd.prog.mk>
