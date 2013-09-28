# $FreeBSD: stable/9/usr.sbin/dnssec-verify/Makefile 254651 2013-08-22 08:15:03Z erwin $

BIND_DIR=	${.CURDIR}/../../contrib/bind9
LIB_BIND_REL=	../../lib/bind
LIB_BIND_DIR=	${.CURDIR}/${LIB_BIND_REL}
SRCDIR=		${BIND_DIR}/bin/dnssec

.include	"${LIB_BIND_DIR}/config.mk"

PROG=		dnssec-verify

.PATH: ${SRCDIR}
SRCS+=		dnssec-verify.c dnssectool.c

CFLAGS+=	-I${SRCDIR}/unix/include -I${SRCDIR}/include
CFLAGS+=	-fsigned-char

DPADD+=		${BIND_DPADD} ${CRYPTO_DPADD} ${PTHREAD_DPADD}
LDADD+=		${BIND_LDADD} ${CRYPTO_LDADD} ${PTHREAD_LDADD}

WARNS?=		3

MAN=		dnssec-verify.8

.include <bsd.prog.mk>
