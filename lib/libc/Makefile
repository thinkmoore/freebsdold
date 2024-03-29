#	@(#)Makefile	8.2 (Berkeley) 2/3/94
# $FreeBSD: stable/9/lib/libc/Makefile 219019 2011-02-25 00:04:39Z gabor $

SHLIBDIR?= /lib

.include <bsd.own.mk>

# Pick the current architecture directory for libc. In general, this is
# named MACHINE_CPUARCH, but some ABIs are different enough to require
# their own libc, so allow a directory named MACHINE_ARCH to override this.

.if exists(${.CURDIR}/${MACHINE_ARCH})
LIBC_ARCH=${MACHINE_ARCH}
.else
LIBC_ARCH=${MACHINE_CPUARCH}
.endif

# All library objects contain FreeBSD revision strings by default; they may be
# excluded as a space-saving measure.  To produce a library that does
# not contain these strings, add -DSTRIP_FBSDID (see <sys/cdefs.h>) to CFLAGS
# below.  Note: there are no IDs for syscall stubs whose sources are generated.
# To include legacy CSRG sccsid strings, add -DLIBC_SCCS and -DSYSLIBC_SCCS
# to CFLAGS below.  -DSYSLIBC_SCCS affects just the system call stubs.
LIB=c
SHLIB_MAJOR= 7
WARNS?=	2
CFLAGS+=-I${.CURDIR}/include -I${.CURDIR}/../../include
CFLAGS+=-I${.CURDIR}/${LIBC_ARCH}
CFLAGS+=-DNLS
CLEANFILES+=tags
INSTALL_PIC_ARCHIVE=
PRECIOUSLIB=

.ifndef NO_THREAD_STACK_UNWIND
CANCELPOINTS_CFLAGS=-fexceptions
CFLAGS+=${CANCELPOINTS_CFLAGS}
.endif

#
# Only link with static libgcc.a (no libgcc_eh.a).
#
DPADD+=	${LIBGCC}
LDFLAGS+= -nodefaultlibs
LDADD+= -lgcc -lssp_nonshared

# Define (empty) variables so that make doesn't give substitution
# errors if the included makefiles don't change these:
MDSRCS=
MISRCS=
MDASM=
MIASM=
NOASM=

.include "${.CURDIR}/${LIBC_ARCH}/Makefile.inc"
.include "${.CURDIR}/db/Makefile.inc"
.include "${.CURDIR}/compat-43/Makefile.inc"
.include "${.CURDIR}/gdtoa/Makefile.inc"
.include "${.CURDIR}/gen/Makefile.inc"
.include "${.CURDIR}/gmon/Makefile.inc"
.if ${MK_ICONV} != "no"
.include "${.CURDIR}/iconv/Makefile.inc"
.endif
.include "${.CURDIR}/inet/Makefile.inc"
.include "${.CURDIR}/isc/Makefile.inc"
.include "${.CURDIR}/locale/Makefile.inc"
.include "${.CURDIR}/nameser/Makefile.inc"
.include "${.CURDIR}/net/Makefile.inc"
.include "${.CURDIR}/nls/Makefile.inc"
.include "${.CURDIR}/posix1e/Makefile.inc"
.if ${LIBC_ARCH} != "amd64" && \
    ${LIBC_ARCH} != "ia64" && \
    ${LIBC_ARCH} != "powerpc64" && \
    ${LIBC_ARCH} != "sparc64" && \
    ${MACHINE_ARCH:Mmipsn32*} == "" && \
    ${MACHINE_ARCH:Mmips64*} == ""
.include "${.CURDIR}/quad/Makefile.inc"
.endif
.include "${.CURDIR}/regex/Makefile.inc"
.include "${.CURDIR}/resolv/Makefile.inc"
.include "${.CURDIR}/stdio/Makefile.inc"
.include "${.CURDIR}/stdlib/Makefile.inc"
.include "${.CURDIR}/stdtime/Makefile.inc"
.include "${.CURDIR}/string/Makefile.inc"
.include "${.CURDIR}/sys/Makefile.inc"
.include "${.CURDIR}/rpc/Makefile.inc"
.include "${.CURDIR}/uuid/Makefile.inc"
.include "${.CURDIR}/xdr/Makefile.inc"
.if ${LIBC_ARCH} == "arm" || ${LIBC_ARCH} == "mips"
.include "${.CURDIR}/softfloat/Makefile.inc"
.endif
.if ${MK_NIS} != "no"
CFLAGS+= -DYP
.include "${.CURDIR}/yp/Makefile.inc"
.endif
.if ${MK_HESIOD} != "no"
CFLAGS+= -DHESIOD
.endif
.if ${MK_FP_LIBC} == "no"
CFLAGS+= -DNO_FLOATING_POINT
.endif
.if ${MK_NS_CACHING} != "no"
CFLAGS+= -DNS_CACHING
.endif
.if defined(_FREEFALL_CONFIG)
CFLAGS+=-D_FREEFALL_CONFIG
.endif

VERSION_DEF=${.CURDIR}/Versions.def
SYMBOL_MAPS=${SYM_MAPS}
CFLAGS+= -DSYMBOL_VERSIONING

# If there are no machine dependent sources, append all the
# machine-independent sources:
.if empty(MDSRCS)
SRCS+=	${MISRCS}
.else
# Append machine-dependent sources, then append machine-independent sources
# for which there is no machine-dependent variant.
SRCS+=	${MDSRCS}
.for _src in ${MISRCS}
.if ${MDSRCS:R:M${_src:R}} == ""
SRCS+=	${_src}
.endif
.endfor
.endif

KQSRCS=	adddi3.c anddi3.c ashldi3.c ashrdi3.c cmpdi2.c divdi3.c iordi3.c \
	lshldi3.c lshrdi3.c moddi3.c muldi3.c negdi2.c notdi2.c qdivrem.c \
	subdi3.c ucmpdi2.c udivdi3.c umoddi3.c xordi3.c
KSRCS=	bcmp.c ffs.c ffsl.c fls.c flsl.c index.c mcount.c rindex.c \
	strcat.c strcmp.c strcpy.c strlen.c strncpy.c

libkern: libkern.gen libkern.${LIBC_ARCH}

libkern.gen: ${KQSRCS} ${KSRCS}
	cp -p ${.CURDIR}/quad/quad.h ${.ALLSRC} ${DESTDIR}/sys/libkern

libkern.${LIBC_ARCH}:: ${KMSRCS}
.if defined(KMSRCS) && !empty(KMSRCS)
	cp -p ${.ALLSRC} ${DESTDIR}/sys/libkern/${LIBC_ARCH}
.endif

.include <bsd.lib.mk>

# Disable warnings in contributed sources.
CWARNFLAGS:=	${.IMPSRC:Ngdtoa_*.c:C/^.+$/${CWARNFLAGS}/:C/^$/-w/}
# XXX For now, we don't allow libc to be compiled with
# -fstack-protector-all because it breaks rtld.  We may want to make a librtld
# in the future to circumvent this.
SSP_CFLAGS:=	${SSP_CFLAGS:S/^-fstack-protector-all$/-fstack-protector/}
# Disable stack protection for SSP symbols.
SSP_CFLAGS:=	${.IMPSRC:N*/stack_protector.c:C/^.+$/${SSP_CFLAGS}/}
# Generate stack unwinding tables for cancellation points
CANCELPOINTS_CFLAGS:=	${.IMPSRC:Mcancelpoints_*:C/^.+$/${CANCELPOINTS_CFLAGS}/:C/^$//}
