# $FreeBSD: stable/9/sys/modules/coda/Makefile 176233 2008-02-13 13:06:22Z rwatson $

.PATH: ${.CURDIR}/../../fs/coda

KMOD=	coda
SRCS=	vnode_if.h \
	coda_fbsd.c coda_psdev.c coda_subr.c coda_venus.c coda_vfsops.c \
	coda_vnops.c opt_coda.h

.include <bsd.kmod.mk>
