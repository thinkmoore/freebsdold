# ex:ts=8
#
# $FreeBSD: stable/9/usr.sbin/amd/Makefile.inc 231702 2012-02-14 19:36:35Z dim $
#
# Makefile for amd
# 	This file is under a "BSD" copyright (c) by David O'Brien 1998.
#	Portions derived from
#	$NetBSD: Makefile.inc,v 1.10 1998/08/08 22:33:27 christos Exp $
#	Portions derived from amd/libamu/Makefile
#	$NetBSD: Makefile,v 1.8 1998/08/08 22:33:37 christos Exp $

.include <bsd.own.mk>

CFLAGS+= -I. -I${.CURDIR} 
CFLAGS+= -I${.CURDIR}/../include
.if exists(${.OBJDIR}/../include)
CFLAGS+= -I${.OBJDIR}/../include
.endif
CFLAGS+= -I${.CURDIR}/../../../contrib/amd/include
CFLAGS+= -I${.CURDIR}/../../../contrib/amd
CFLAGS+= -DHAVE_CONFIG_H
.if ${MK_NIS} == "no"
CFLAGS+= -DHAVE_LOCALCONFIG_H
.endif

.if ${MK_HESIOD} != "no"
CFLAGS+= -DYES_HESIOD
.endif

CFLAGS+= -DHOST_CPU=\"${MACHINE_CPUARCH}\" -DHOST_ARCH=\"${MACHINE_ARCH}\"

.if exists(${.OBJDIR}/../libamu)
LIBAMUDIR=	${.OBJDIR}/../libamu
.else
LIBAMUDIR=	${.CURDIR}/../libamu
.endif
LIBAMU=		${LIBAMUDIR}/libamu.a

RPCCOM=		RPCGEN_CPP=${CPP:Q} rpcgen
MOUNT_X=	${DESTDIR}/usr/include/rpcsvc/mount.x
NFS_PROT_X=	${DESTDIR}/usr/include/rpcsvc/nfs_prot.x

WARNS?=	1

.if exists(${.CURDIR}/../../Makefile.inc)
.include "${.CURDIR}/../../Makefile.inc"
.endif
