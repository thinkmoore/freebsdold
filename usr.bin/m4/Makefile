#	$OpenBSD: Makefile,v 1.10 2002/04/26 13:13:41 espie Exp $
# $FreeBSD: stable/9/usr.bin/m4/Makefile 201386 2010-01-02 10:27:05Z ed $

# -DEXTENDED 
# 	if you want the paste & spaste macros.

PROG=	m4
CFLAGS+=-DEXTENDED

SRCS=	eval.c expr.c look.c main.c misc.c gnum4.c trace.c

WARNS?=	0

.include <bsd.prog.mk>
