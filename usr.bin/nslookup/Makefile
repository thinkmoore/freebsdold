# $FreeBSD: stable/9/usr.bin/nslookup/Makefile 255233 2013-09-05 06:58:49Z erwin $

BIND_DIR=	${.CURDIR}/../../contrib/bind9
LIB_BIND_REL=	../../lib/bind
LIB_BIND_DIR=	${.CURDIR}/${LIB_BIND_REL}
SRCDIR=		${BIND_DIR}/bin/dig

.include	"${LIB_BIND_DIR}/config.mk"

PROG=		nslookup

.PATH: ${SRCDIR}
SRCS+=		dighost.c nslookup.c

CFLAGS+=	-I${SRCDIR}/include -ledit
CFLAGS+=	-I${BIND_DIR}/lib/isc/${ISC_ATOMIC_ARCH}/include

DPADD+=		${BIND_DPADD} ${CRYPTO_DPADD} ${PTHREAD_DPADD} ${LIBEDIT}
LDADD+=		${BIND_LDADD} ${CRYPTO_LDADD} ${PTHREAD_LDADD} ${LIBEDIT}

WARNS?=		0

MANFILTER=	sed -e "s@^host \[server\]@\\\fBhost\\\fR \\\fI[server]\\\fR@"

.include <bsd.prog.mk>
