# $FreeBSD: stable/9/usr.sbin/pkg_install/delete/Makefile 222035 2011-05-17 19:11:47Z flz $

PROG=	pkg_delete
SRCS=	main.c perform.c

CFLAGS+= -I${.CURDIR}/../lib

WFORMAT?=	1

DPADD=	${LIBINSTALL} ${LIBMD}
LDADD=	${LIBINSTALL} -lmd

.include <bsd.prog.mk>
