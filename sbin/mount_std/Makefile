#	@(#)Makefile	8.2 (Berkeley) 3/27/94
#	$FreeBSD: stable/9/sbin/mount_std/Makefile 203916 2010-02-15 14:07:40Z uqs $

PROG=	mount_std
SRCS=	mount_std.c getmntopts.c
MAN=	mount_std.8
MLINKS=	mount_std.8 mount_devfs.8 \
	mount_std.8 mount_fdescfs.8 \
	mount_std.8 mount_linprocfs.8 \
	mount_std.8 mount_procfs.8

MOUNT=	${.CURDIR}/../mount
CFLAGS+= -I${MOUNT}
WARNS?=	3

.PATH:	${MOUNT}

LINKS=	${BINDIR}/mount_std ${BINDIR}/mount_devfs \
	${BINDIR}/mount_std ${BINDIR}/mount_fdescfs \
	${BINDIR}/mount_std ${BINDIR}/mount_linprocfs \
	${BINDIR}/mount_std ${BINDIR}/mount_procfs

.include <bsd.prog.mk>
