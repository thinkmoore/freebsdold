# $FreeBSD: stable/9/cddl/sbin/zfs/Makefile 249643 2013-04-19 09:19:10Z mm $

.PATH: ${.CURDIR}/../../../cddl/contrib/opensolaris/cmd/zfs

PROG=	zfs
MAN=	zfs.8
SRCS=	zfs_main.c zfs_iter.c

WARNS?=	0
CFLAGS+= -I${.CURDIR}/../../../cddl/contrib/opensolaris/lib/libzpool/common
CFLAGS+= -I${.CURDIR}/../../../cddl/compat/opensolaris/include
CFLAGS+= -I${.CURDIR}/../../../cddl/compat/opensolaris/lib/libumem
CFLAGS+= -I${.CURDIR}/../../../sys/cddl/compat/opensolaris
CFLAGS+= -I${.CURDIR}/../../../cddl/contrib/opensolaris/head
CFLAGS+= -I${.CURDIR}/../../../cddl/contrib/opensolaris/lib/libuutil/common
CFLAGS+= -I${.CURDIR}/../../../cddl/contrib/opensolaris/lib/libzfs/common
CFLAGS+= -I${.CURDIR}/../../../cddl/contrib/opensolaris/lib/libzfs_core/common
CFLAGS+= -I${.CURDIR}/../../../cddl/contrib/opensolaris/lib/libumem/common
CFLAGS+= -I${.CURDIR}/../../../cddl/contrib/opensolaris/lib/libnvpair
CFLAGS+= -I${.CURDIR}/../../../sys/cddl/contrib/opensolaris/uts/common
CFLAGS+= -I${.CURDIR}/../../../sys/cddl/contrib/opensolaris/uts/common/fs/zfs
CFLAGS+= -I${.CURDIR}/../../../sys/cddl/contrib/opensolaris/uts/common/sys
CFLAGS+= -I${.CURDIR}/../../../sys/cddl/contrib/opensolaris/common/zfs

DPADD=	${LIBGEOM} ${LIBJAIL} ${LIBNVPAIR} ${LIBUMEM} \
	${LIBUTIL} ${LIBUUTIL} ${LIBZFS_CORE} ${LIBZFS}
LDADD=	-lgeom -ljail -lnvpair -lumem -lutil -luutil -lzfs_core -lzfs

.include <bsd.prog.mk>
