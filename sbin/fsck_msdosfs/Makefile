#	$NetBSD: Makefile,v 1.6 1997/05/08 21:11:11 gwr Exp $
# $FreeBSD: stable/9/sbin/fsck_msdosfs/Makefile 209364 2010-06-20 09:40:54Z brian $

FSCK=	${.CURDIR}/../fsck
.PATH: ${FSCK}

PROG=	fsck_msdosfs
MAN=	fsck_msdosfs.8
SRCS=	main.c check.c boot.c fat.c dir.c fsutil.c

CFLAGS+= -I${FSCK}
WARNS?=	2

.include <bsd.prog.mk>
