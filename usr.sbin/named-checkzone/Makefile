# $FreeBSD: stable/9/usr.sbin/named-checkzone/Makefile 201390 2010-01-02 11:07:44Z ed $

BIND_DIR=	${.CURDIR}/../../contrib/bind9
LIB_BIND_REL=	../../lib/bind
LIB_BIND_DIR=	${.CURDIR}/${LIB_BIND_REL}
SRCDIR=		${BIND_DIR}/bin/check

.include	"${LIB_BIND_DIR}/config.mk"

PROG=		named-checkzone

.PATH: ${SRCDIR}
SRCS+=		named-checkzone.c check-tool.c

CFLAGS+=	-I${LIB_BIND_DIR}

WARNS?=		3

DPADD+=		${BIND_DPADD} ${CRYPTO_DPADD} ${PTHREAD_DPADD}
LDADD+=		${BIND_LDADD} ${CRYPTO_LDADD} ${PTHREAD_LDADD}

LINKS=		${BINDIR}/named-checkzone ${BINDIR}/named-compilezone

MAN=		named-checkzone.8

MLINKS=		named-checkzone.8 named-compilezone.8

.include <bsd.prog.mk>
