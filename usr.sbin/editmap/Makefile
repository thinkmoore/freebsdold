# $FreeBSD: stable/9/usr.sbin/editmap/Makefile 201390 2010-01-02 11:07:44Z ed $

SENDMAIL_DIR=${.CURDIR}/../../contrib/sendmail
.PATH: ${SENDMAIL_DIR}/editmap

PROG=	editmap
SRCS=	editmap.c
MAN=	editmap.8

CFLAGS+= -I${SENDMAIL_DIR}/src -I${SENDMAIL_DIR}/include -I.
CFLAGS+= -DNEWDB -DNOT_SENDMAIL

WARNS?=	2

LIBSMDIR=	${.OBJDIR}/../../lib/libsm
LIBSM=		${LIBSMDIR}/libsm.a

LIBSMDBDIR=	${.OBJDIR}/../../lib/libsmdb
LIBSMDB=	${LIBSMDBDIR}/libsmdb.a

LIBSMUTILDIR=	${.OBJDIR}/../../lib/libsmutil
LIBSMUTIL=	${LIBSMUTILDIR}/libsmutil.a

DPADD=	${LIBSMDB} ${LIBSMUTIL} ${LIBSM}
LDADD=	${LIBSMDB} ${LIBSMUTIL} ${LIBSM}

SRCS+=	sm_os.h
CLEANFILES+=sm_os.h

# User customizations to the sendmail build environment
CFLAGS+=${SENDMAIL_CFLAGS}
DPADD+=${SENDMAIL_DPADD}
LDADD+=${SENDMAIL_LDADD}
LDFLAGS+=${SENDMAIL_LDFLAGS}

sm_os.h:
	ln -sf ${SENDMAIL_DIR}/include/sm/os/sm_os_freebsd.h sm_os.h

.include <bsd.prog.mk>
