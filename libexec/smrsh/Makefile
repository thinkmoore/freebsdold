#	@(#)Makefile	8.1 (Berkeley) 7/2/95
# $FreeBSD: stable/9/libexec/smrsh/Makefile 247333 2013-02-26 18:31:03Z dim $

SENDMAIL_DIR=${.CURDIR}/../../contrib/sendmail
.PATH:	${SENDMAIL_DIR}/smrsh

PROG=	smrsh
SRCS=	smrsh.c
MAN=	smrsh.8
CFLAGS+=-I${SENDMAIL_DIR}/src -I${SENDMAIL_DIR}/include -I.

LIBSMDIR=	${.OBJDIR}/../../lib/libsm
LIBSM=		${LIBSMDIR}/libsm.a

DPADD=	${LIBSM}
LDADD=	${LIBSM}

WARNS?=	2

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
