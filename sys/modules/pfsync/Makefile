# $FreeBSD: stable/9/sys/modules/pfsync/Makefile 229770 2012-01-07 11:01:35Z glebius $

.include <bsd.own.mk>

.PATH: ${.CURDIR}/../../contrib/pf/net

KMOD=	pfsync
SRCS=	if_pfsync.c \
	opt_pf.h opt_inet.h opt_inet6.h

CFLAGS+= -I${.CURDIR}/../../contrib/pf
SRCS+=	bus_if.h device_if.h

.if defined(KERNBUILDDIR)
MKDEP+=		-include ${KERNBUILDDIR}/opt_global.h
.else
.if ${MK_INET_SUPPORT} != "no"
opt_inet.h:
	echo "#define INET 1" > ${.TARGET}
.endif

.if ${MK_INET6_SUPPORT} != "no"
opt_inet6.h:
	echo "#define INET6 1" > ${.TARGET}
.endif

.if defined(VIMAGE)
opt_global.h:
	echo "#define VIMAGE 1" >> ${.TARGET}
CFLAGS+=	-include opt_global.h
MKDEP+=		-include opt_global.h
.endif
.endif

.include <bsd.kmod.mk>
