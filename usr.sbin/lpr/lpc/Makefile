#	From: @(#)Makefile	8.1 (Berkeley) 6/6/93
# $FreeBSD: stable/9/usr.sbin/lpr/lpc/Makefile 201390 2010-01-02 11:07:44Z ed $

.PATH: ${.CURDIR}/../common_source

PROG=	lpc
MAN=	lpc.8
SRCS=	lpc.c cmds.c cmdtab.c movejobs.c 
BINGRP=	daemon
BINMODE= 2555

CFLAGS+= -I${.CURDIR}/../common_source

WARNS?=	0

DPADD=	${LIBLPR} ${LIBEDIT} ${LIBTERMCAP}
LDADD=	${LIBLPR} -ledit -ltermcap

.include <bsd.prog.mk>
