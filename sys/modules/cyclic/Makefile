# $FreeBSD: stable/9/sys/modules/cyclic/Makefile 254704 2013-08-23 14:17:45Z avg $

.PATH: ${.CURDIR}/../../cddl/dev/cyclic

KMOD=		cyclic
SRCS=		cyclic.c

SRCS+=		vnode_if.h

CFLAGS+=	-I${.CURDIR}/../../cddl/compat/opensolaris		\
		-I${.CURDIR}/../../cddl/contrib/opensolaris/uts/common	\
		-I${.CURDIR}/../..					\
		-I${.CURDIR}/../../cddl/dev/cyclic/${MACHINE_CPUARCH:S/amd64/i386/}

IGNORE_PRAGMA=	1

.include <bsd.kmod.mk>

CFLAGS+=	-include ${.CURDIR}/../../cddl/compat/opensolaris/sys/debug_compat.h
