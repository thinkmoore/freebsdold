# $FreeBSD: stable/9/lib/libftpio/Makefile 201381 2010-01-02 09:58:07Z ed $

.include <bsd.own.mk>

LIB=		ftpio
SHLIB_MAJOR=	8

SRCS=		ftpio.c ftperr.c
INCS=		ftpio.h
CFLAGS+=	-I${.CURDIR} -Wall
MAN=		ftpio.3
CLEANFILES=	ftperr.c

.if ${MK_INET6_SUPPORT} != "no"
CFLAGS+=	-DINET6
.endif

WARNS?=		2

ftperr.c:	ftp.errors
	@echo '#include <stdio.h>' > ${.TARGET}
	@echo '#include "ftpio.h"' >> ${.TARGET}
	@echo "struct ftperr ftpErrList[] = {" \ >>  ${.TARGET}
	@cat ${.ALLSRC} \
	  | grep -v ^# \
	  | sort \
	  | while read NUM STRING; do \
	    echo "  { $${NUM}, \"$${STRING}\" },"; \
	  done >> ${.TARGET}
	@echo "};" >> ${.TARGET}
	@echo -n "int const ftpErrListLength = " >> ${.TARGET}
	@echo "sizeof(ftpErrList) / sizeof(*ftpErrList);" >> ${.TARGET}

.include <bsd.lib.mk>
