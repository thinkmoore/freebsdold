# $FreeBSD: stable/9/sys/modules/dtrace/fasttrap/Makefile 254704 2013-08-23 14:17:45Z avg $

.PATH:	${.CURDIR}/../../../cddl/contrib/opensolaris/uts/common/dtrace

KMOD=		fasttrap
SRCS=		fasttrap.c fasttrap_isa.c opt_compat.h
SRCS+=		vnode_if.h

CFLAGS+=	-I${.CURDIR}/../../../cddl/compat/opensolaris \
		-I${.CURDIR}/../../../cddl/contrib/opensolaris/uts/common \
		-I${.CURDIR}/../../..

.if ${MACHINE_CPUARCH} == "amd64" ||  ${MACHINE_CPUARCH} == "i386"
CFLAGS+=	-I${.CURDIR}/../../../cddl/contrib/opensolaris/uts/intel
.PATH:		${.CURDIR}/../../../cddl/contrib/opensolaris/uts/intel/dtrace
.endif

CFLAGS+=	-DSMP

.include <bsd.kmod.mk>

CFLAGS+=	-include ${.CURDIR}/../../../cddl/compat/opensolaris/sys/debug_compat.h
CWARNFLAGS+=	-Wno-unused
