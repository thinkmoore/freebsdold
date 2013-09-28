# $FreeBSD: stable/9/sys/modules/dtrace/dtio/Makefile 254704 2013-08-23 14:17:45Z avg $

.PATH: ${.CURDIR}/../../../kern

KMOD=		dtio
SRCS=		dtio_kdtrace.c \
		vnode_if.h

CFLAGS+=	-I${.CURDIR}/../../../cddl/compat/opensolaris \
		-I${.CURDIR}/../../../cddl/contrib/opensolaris/uts/common \
		-I${.CURDIR}/../../..

.include <bsd.kmod.mk>

CFLAGS+=	-include ${.CURDIR}/../../../cddl/compat/opensolaris/sys/debug_compat.h
