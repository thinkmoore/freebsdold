# $FreeBSD: stable/9/lib/libcom_err/Makefile 74870 2001-03-27 17:27:19Z ru $

LIB=	com_err
SRCS=	com_err.c error.c
INCS=	${COM_ERRDIR}/com_err.h ${COM_ERRDIR}/com_right.h
MAN=	com_err.3
COM_ERRDIR=	${.CURDIR}/../../contrib/com_err
CFLAGS+=	-I${COM_ERRDIR}

SUBDIR=	doc

.include <bsd.lib.mk>

.PATH:	${COM_ERRDIR}
