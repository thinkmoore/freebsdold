#	$NetBSD: Makefile,v 1.3 1995/07/04 01:53:05 cgd Exp $
# $FreeBSD: stable/9/usr.bin/xlint/lint1/Makefile 125503 2004-02-05 22:44:25Z ru $

PROG=	lint1
SRCS=	cgram.y scan.l mem1.c mem.c err.c main1.c decl.c tree.c func.c \
	init.c emit.c emit1.c inittyp.c
MAN=	lint.7
CLEANFILES= lint.7

LDADD=	-ll -lm
DPADD=	${LIBL} ${LIBM}
CFLAGS+= -I. -I${.CURDIR}
LINTFLAGS=-aehpz

BINDIR=	/usr/libexec

.PATH: ${.CURDIR}/../common

lint.7: makeman
	sh ${.CURDIR}/makeman ${DESTDIR}${BINDIR}/${PROG} -m >${.TARGET}

.include <bsd.prog.mk>
