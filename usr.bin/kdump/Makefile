#	@(#)Makefile	8.1 (Berkeley) 6/6/93
# $FreeBSD: stable/9/usr.bin/kdump/Makefile 234444 2012-04-18 20:32:07Z dim $

.if (${MACHINE_ARCH} == "amd64")
SFX=		32
.endif

.PATH: ${.CURDIR}/../ktrace

PROG=		kdump
SRCS=		kdump.c ioctl.c kdump_subr.c subr.c
CFLAGS+=	-I${.CURDIR}/../ktrace -I${.CURDIR} -I${.CURDIR}/../..

.if ${MACHINE_ARCH} == "amd64" || ${MACHINE_ARCH} == "i386"
SRCS+=		linux_syscalls.c
.endif

WARNS?=		0

CLEANFILES=	ioctl.c kdump_subr.c linux_syscalls.c

ioctl.c: mkioctls
	env CPP="${CPP}" \
	   sh ${.CURDIR}/mkioctls ${DESTDIR}/usr/include > ${.TARGET}

kdump_subr.c: mksubr
	sh ${.CURDIR}/mksubr ${DESTDIR}/usr/include > ${.TARGET}

linux_syscalls.c:
	/bin/sh ${.CURDIR}/../../sys/kern/makesyscalls.sh \
	    ${.CURDIR}/../../sys/${MACHINE_ARCH}/linux${SFX}/syscalls.master ${.CURDIR}/linux_syscalls.conf
	echo "int nlinux_syscalls = sizeof(linux_syscallnames) / sizeof(linux_syscallnames[0]);" \
	    >> linux_syscalls.c

.include <bsd.prog.mk>
