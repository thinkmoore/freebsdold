# $FreeBSD: stable/9/lib/libkiconv/Makefile 237698 2012-06-28 09:18:11Z gabor $

SHLIBDIR?=	/lib

.include <bsd.own.mk>

LIB=		kiconv
SRCS=		kiconv_sysctl.c xlat16_iconv.c xlat16_sysctl.c
SRCS+=		quirks.c

SHLIB_MAJOR=	4

MAN=		kiconv.3

MLINKS+=	kiconv.3 kiconv_add_xlat16_cspair.3 \
		kiconv.3 kiconv_add_xlat16_cspairs.3 \
		kiconv.3 kiconv_add_xlat16_table.3

CFLAGS+=	-I${.CURDIR}/../../sys

WARNS?=		1

.if ${MK_ICONV} == "no"
CFLAGS+=	-DICONV_DLOPEN
.endif

.include <bsd.lib.mk>
