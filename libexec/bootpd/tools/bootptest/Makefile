# Makefile
# $FreeBSD: stable/9/libexec/bootpd/tools/bootptest/Makefile 74814 2001-03-26 14:22:12Z ru $

PROG=	bootptest
MAN=	bootptest.8
SRCS=	bootptest.c getether.c getif.c print-bootp.c report.c

SRCDIR=	${.CURDIR}/../..
CFLAGS+=-I${SRCDIR}
.PATH:	${SRCDIR}

.include <bsd.prog.mk>
