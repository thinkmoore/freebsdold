# $FreeBSD: stable/9/usr.sbin/named-checkconf/Makefile 224093 2011-07-16 11:20:54Z dougb $

BIND_DIR=	${.CURDIR}/../../contrib/bind9
LIB_BIND_REL=	../../lib/bind
LIB_BIND_DIR=	${.CURDIR}/${LIB_BIND_REL}
SRCDIR=		${BIND_DIR}/bin/check

.include	"${LIB_BIND_DIR}/config.mk"

PROG=		named-checkconf

.PATH: ${SRCDIR}
SRCS+=		named-checkconf.c check-tool.c

CFLAGS+=	-I${LIB_BIND_DIR}
CFLAGS+=	-I${BIND_DIR}/lib/isc/${ISC_ATOMIC_ARCH}/include

WARNS?=		3

DPADD+=		${BIND_DPADD} ${CRYPTO_DPADD} ${PTHREAD_DPADD}
LDADD+=		${BIND_LDADD} ${CRYPTO_LDADD} ${PTHREAD_LDADD}

MAN=		named-checkconf.8

MANFILTER=	sed -e "s@/etc/named\.conf@/etc/namedb/named.conf@g"

.include <bsd.prog.mk>
