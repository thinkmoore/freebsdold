# $FreeBSD: stable/9/cddl/lib/libctf/Makefile 204597 2010-03-02 19:04:07Z uqs $

.PATH:		${.CURDIR}/../../../cddl/contrib/opensolaris/common/ctf
.PATH:		${.CURDIR}/../../../cddl/contrib/opensolaris/lib/libctf/common
.PATH:		${.CURDIR}/../../../sys/cddl/contrib/opensolaris/common/ctf

LIB=		ctf
SRCS=		ctf_create.c \
		ctf_decl.c \
		ctf_error.c \
		ctf_hash.c \
		ctf_labels.c \
		ctf_lib.c \
		ctf_lookup.c \
		ctf_open.c \
		ctf_subr.c \
		ctf_types.c \
		ctf_util.c

WARNS?=		0
CFLAGS+=	-DCTF_OLD_VERSIONS

CFLAGS+=	-I${.CURDIR}/../../../sys/cddl/compat/opensolaris \
		-I${.CURDIR}/../../../cddl/compat/opensolaris/include \
		-I${OPENSOLARIS_USR_DISTDIR}/head \
		-I${OPENSOLARIS_USR_DISTDIR}/common/ctf \
		-I${OPENSOLARIS_USR_DISTDIR}/lib/libctf/common \
		-I${OPENSOLARIS_SYS_DISTDIR}/uts/common

.include <bsd.lib.mk>

