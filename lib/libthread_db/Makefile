# $FreeBSD: stable/9/lib/libthread_db/Makefile 232930 2012-03-13 18:39:57Z dim $

.PATH:	${.CURDIR}/arch/${MACHINE_CPUARCH}

LIB=	thread_db
SHLIB_MAJOR= 3
SRCS=	thread_db.c
SRCS+=	libpthread_md.c
SRCS+=	libpthread_db.c
SRCS+=	libthr_db.c
INCS=	thread_db.h

CFLAGS+=-I. -I${.CURDIR}
SYM_MAPS+=${.CURDIR}/Symbol.map

SYMBOL_MAPS=${SYM_MAPS}
VERSION_DEF=${.CURDIR}/../libc/Versions.def

# Unfortunately, clang gives an incorrect warning about alignment in
# arch/i386/libpthread_md.c, so turn that off for now.
NO_WCAST_ALIGN.clang=

.include <bsd.lib.mk>
