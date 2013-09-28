# $FreeBSD: stable/9/usr.bin/dig/Makefile 255233 2013-09-05 06:58:49Z erwin $

BIND_DIR=	${.CURDIR}/../../contrib/bind9
LIB_BIND_REL=	../../lib/bind
LIB_BIND_DIR=	${.CURDIR}/${LIB_BIND_REL}
SRCDIR=		${BIND_DIR}/bin/dig

.include	"${LIB_BIND_DIR}/config.mk"

PROG=		dig

.PATH: ${SRCDIR}
SRCS+=		dig.c dighost.c

CFLAGS+=	-I${SRCDIR}/include
CFLAGS+=	-I${BIND_DIR}/lib/isc/${ISC_ATOMIC_ARCH}/include

.if ${MK_BIND_IDN} == "yes"
CFLAGS+=	-DWITH_IDN -I/usr/local/include
CFLAGS+=	-L/usr/local/lib -lidnkit -R/usr/local/lib -liconv
.endif

WARNS?=		0

DPADD+=		${BIND_DPADD} ${CRYPTO_DPADD} ${PTHREAD_DPADD}
LDADD+=		${BIND_LDADD} ${CRYPTO_LDADD} ${PTHREAD_LDADD}

.include <bsd.prog.mk>
