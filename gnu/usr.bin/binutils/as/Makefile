# $FreeBSD: stable/9/gnu/usr.bin/binutils/as/Makefile 235398 2012-05-13 13:57:53Z kib $


# BINDIR
.include "${.CURDIR}/../../Makefile.inc"
.include "${.CURDIR}/../Makefile.inc0"
.include <bsd.own.mk>

.PATH: ${SRCDIR}/gas ${SRCDIR}/gas/config

PROG=	as
SRCS+=	app.c \
	as.c \
	atof-generic.c \
	atof-ieee.c \
	cond.c \
	depend.c \
	dw2gencfi.c \
	dwarf2dbg.c \
	ecoff.c \
	ehopt.c \
	expr.c \
	flonum-copy.c \
	flonum-konst.c \
	flonum-mult.c \
	frags.c \
	hash.c \
	input-file.c \
	input-scrub.c \
	listing.c \
	literal.c \
	macro.c \
	messages.c \
	obj-elf.c \
	output-file.c \
	read.c \
	sb.c \
	stabs.c \
	subsegs.c \
	symbols.c \
	write.c
# DEO: why not used?
#SRCS+=	itbl-ops.c

.if ${TARGET_CPUARCH} == "mips"
SRCS+=	itbl-ops.c itbl-parse.y itbl-lex.l
.endif

.if ${TARGET_ARCH} == "amd64"
SRCS+=	tc-i386.c
.elif ${TARGET_CPUARCH} == "powerpc"
SRCS+=	tc-ppc.c
.elif ${TARGET_ARCH} == "sparc64"
SRCS+=	tc-sparc.c
.else
SRCS+=	tc-${TARGET_CPUARCH}.c
.endif

.if ${TARGET_ARCH} == "sparc64"
CFLAGS+= -DDEFAULT_ARCH=\"v9-64\"
.else
CFLAGS+= -DDEFAULT_ARCH=\"${BINUTILS_ARCH}\"
.endif
.if defined(TARGET_BIG_ENDIAN)
CFLAGS+= -DTARGET_BYTES_BIG_ENDIAN=1
.endif
CFLAGS+= -DTARGET_CPU=\"${BINUTILS_ARCH}\"
CFLAGS+= -DTARGET_OS=\"${TARGET_OS}\"
CFLAGS+= -DTARGET_CANONICAL=\"${TARGET_TUPLE}\"
CFLAGS+= -DTARGET_ALIAS=\"${TARGET_TUPLE}\"
CFLAGS+= -DVERSION=\"${VERSION}\"
CFLAGS+= -D_GNU_SOURCE
CFLAGS+= -I${SRCDIR}/gas -I${SRCDIR}/bfd -I${SRCDIR}/gas/config -I${SRCDIR}
CFLAGS+= -I${.CURDIR} -I${.CURDIR}/${TARGET_CPUARCH}-freebsd

.if ${MK_SHARED_TOOLCHAIN} == "no"
NO_SHARED?=	yes
.endif

DPADD=	${RELTOP}/libbfd/libbfd.a
DPADD+=	${RELTOP}/libiberty/libiberty.a
DPADD+=	${RELTOP}/libopcodes/libopcodes.a
LDADD=	${DPADD}

.include <bsd.prog.mk>
