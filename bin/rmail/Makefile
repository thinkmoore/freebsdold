#	@(#)Makefile	8.1 (Berkeley) 5/31/93
# $FreeBSD: stable/9/bin/rmail/Makefile 203916 2010-02-15 14:07:40Z uqs $

SENDMAIL_DIR=${.CURDIR}/../../contrib/sendmail
.PATH:	${SENDMAIL_DIR}/rmail

# Not much point this being static. It calls a shared sendmail...
NO_SHARED?= NO

PROG=	rmail
SRCS=	rmail.c
MAN=	rmail.8

WARNS?=	2
CFLAGS+=-I${SENDMAIL_DIR}/include -I.

LIBSMDIR=	${.OBJDIR}/../../lib/libsm
LIBSM=		${LIBSMDIR}/libsm.a

DPADD=	${LIBSM}
LDADD=	${LIBSM}

SRCS+=	sm_os.h
CLEANFILES+=sm_os.h

# User customizations to the sendmail build environment
CFLAGS+=${SENDMAIL_CFLAGS}
DPADD+=${SENDMAIL_DPADD}
LDADD+=${SENDMAIL_LDADD}
LDFLAGS+=${SENDMAIL_LDFLAGS}

# If you want to have your rmail queuing the mail only, uncomment the
# following:
# CFLAGS+= -DQUEUE_ONLY

sm_os.h:
	ln -sf ${SENDMAIL_DIR}/include/sm/os/sm_os_freebsd.h sm_os.h

.include <bsd.prog.mk>
