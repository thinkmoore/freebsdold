# $FreeBSD: stable/9/cddl/usr.bin/zstreamdump/Makefile 219089 2011-02-27 19:41:40Z pjd $

.PATH: ${.CURDIR}/../..//contrib/opensolaris/cmd/zstreamdump

PROG=	zstreamdump
MAN=	zstreamdump.1

WARNS?=	0
CFLAGS+= -I${.CURDIR}/../../../sys/cddl/compat/opensolaris
CFLAGS+= -I${.CURDIR}/../../compat/opensolaris/include
CFLAGS+= -I${.CURDIR}/../../compat/opensolaris/lib/libumem
CFLAGS+= -I${.CURDIR}/../../contrib/opensolaris/lib/libzpool/common
CFLAGS+= -I${.CURDIR}/../../contrib/opensolaris/lib/libnvpair
CFLAGS+= -I${.CURDIR}/../../../sys/cddl/contrib/opensolaris/common/zfs
CFLAGS+= -I${.CURDIR}/../../../sys/cddl/contrib/opensolaris/uts/common/fs/zfs
CFLAGS+= -I${.CURDIR}/../../../sys/cddl/contrib/opensolaris/uts/common/sys
CFLAGS+= -I${.CURDIR}/../../../sys/cddl/contrib/opensolaris/uts/common
CFLAGS+= -I${.CURDIR}/../../contrib/opensolaris/head
CFLAGS+= -I${.CURDIR}/../../lib/libumem

DPADD=	${LIBM} ${LIBNVPAIR} ${LIBUMEM} ${LIBZPOOL} \
	${LIBPTHREAD} ${LIBZ} ${LIBAVL}
LDADD=	-lm -lnvpair -lumem -lzpool -lpthread -lz -lavl

CSTD=	c99

.include <bsd.prog.mk>
