#	@(#)Makefile	8.1 (Berkeley) 6/6/93
# $FreeBSD: stable/9/usr.bin/nfsstat/Makefile 201386 2010-01-02 10:27:05Z ed $

PROG=	nfsstat
CFLAGS+=-DNFS
DPADD=  ${LIBKVM}
LDADD= -lkvm

WARNS?=	3

.include <bsd.prog.mk>
