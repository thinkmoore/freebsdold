# $FreeBSD: stable/9/sys/modules/dtrace/dtrace_test/Makefile 254704 2013-08-23 14:17:45Z avg $

.PATH: ${.CURDIR}/../../../cddl/dev/dtrace

KMOD=		dtrace_test
SRCS=		dtrace_test.c

SRCS+=		vnode_if.h
		
CFLAGS+=	-I${.CURDIR}/../../..

CFLAGS+=	-D_KERNEL

.include <bsd.kmod.mk>

CFLAGS+=	-include ${.CURDIR}/../../../cddl/compat/opensolaris/sys/debug_compat.h
