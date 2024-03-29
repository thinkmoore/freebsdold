#	from: @(#)sys.mk	8.2 (Berkeley) 3/21/94
# $FreeBSD: stable/9/share/mk/sys.mk 252827 2013-07-05 19:35:51Z emaste $

unix		?=	We run FreeBSD, not UNIX.
.FreeBSD	?=	true

.if !defined(%POSIX)
#
# MACHINE_CPUARCH defines a collection of MACHINE_ARCH.  Machines with
# the same MACHINE_ARCH can run each other's binaries, so it necessarily
# has word size and endian swizzled in.  However, support files for
# these machines often are shared amongst all combinations of size
# and/or endian.  This is called MACHINE_CPU in NetBSD, but that's used
# for something different in FreeBSD.
#
MACHINE_CPUARCH=${MACHINE_ARCH:C/mips.*e[lb]/mips/:C/armeb/arm/:C/powerpc64/powerpc/}
.endif

# Set any local definitions first. Place this early, but it needs
# MACHINE_CPUARCH to be defined.
.sinclude <local.sys.mk>

# If the special target .POSIX appears (without prerequisites or
# commands) before the first noncomment line in the makefile, make shall
# process the makefile as specified by the Posix 1003.2 specification.
# make(1) sets the special macro %POSIX in this case (to the actual
# value "1003.2", for what it's worth).
#
# The rules below use this macro to distinguish between Posix-compliant
# and default behaviour.

.if defined(%POSIX)
.SUFFIXES:	.o .c .y .l .a .sh .f
.else
.SUFFIXES:	.out .a .ln .o .c .cc .cpp .cxx .C .m .F .f .e .r .y .l .S .asm .s .cl .p .h .sh
.endif

AR		?=	ar
.if defined(%POSIX)
ARFLAGS		?=	-rv
.else
ARFLAGS		?=	rl
.endif
RANLIB		?=	ranlib

AS		?=	as
AFLAGS		?=
ACFLAGS		?=

.if defined(%POSIX)
CC		?=	c89
CFLAGS		?=	-O
.else
CC		?=	cc
.if ${MACHINE_CPUARCH} == "arm" || ${MACHINE_CPUARCH} == "mips"
CFLAGS		?=	-O -pipe
.else
CFLAGS		?=	-O2 -pipe
.endif
.if defined(NO_STRICT_ALIASING)
CFLAGS		+=	-fno-strict-aliasing
.endif
.endif
PO_CFLAGS	?=	${CFLAGS}

# C Type Format data is required for DTrace
CTFFLAGS	?=	-L VERSION

CTFCONVERT	?=	ctfconvert
CTFMERGE	?=	ctfmerge
DTRACE		?=	dtrace
.if defined(CFLAGS) && (${CFLAGS:M-g} != "")
CTFFLAGS	+=	-g
.else
# XXX: What to do here? Is removing the CFLAGS part completely ok here?
# For now comment it out to not compile with -g unconditionally.
#CFLAGS		+=	-g
.endif

CXX		?=	c++
CXXFLAGS	?=	${CFLAGS:N-std=*:N-Wnested-externs:N-W*-prototypes:N-Wno-pointer-sign:N-Wold-style-definition}
PO_CXXFLAGS	?=	${CXXFLAGS}

CPP		?=	cpp

.if empty(.MAKEFLAGS:M-s)
ECHO		?=	echo
ECHODIR		?=	echo
.else
ECHO		?=	true
.if ${.MAKEFLAGS:M-s} == "-s"
ECHODIR		?=	echo
.else
ECHODIR		?=	true
.endif
.endif

.if !empty(.MAKEFLAGS:M-n) && ${.MAKEFLAGS:M-n} == "-n"
_+_		?=
.else
_+_		?=	+
.endif

.if defined(%POSIX)
FC		?=	fort77
FFLAGS		?=	-O 1
.else
FC		?=	f77
FFLAGS		?=	-O
.endif
EFLAGS		?=

INSTALL		?=	install

LEX		?=	lex
LFLAGS		?=

LD		?=	ld
LDFLAGS		?=

LINT		?=	lint
LINTFLAGS	?=	-cghapbx
LINTKERNFLAGS	?=	${LINTFLAGS}
LINTOBJFLAGS	?=	-cghapbxu -i
LINTOBJKERNFLAGS?=	${LINTOBJFLAGS}
LINTLIBFLAGS	?=	-cghapbxu -C ${LIB}

MAKE		?=	make

OBJC		?=	cc
OBJCFLAGS	?=	${OBJCINCLUDES} ${CFLAGS} -Wno-import

OBJCOPY		?=	objcopy

PC		?=	pc
PFLAGS		?=

RC		?=	f77
RFLAGS		?=

SHELL		?=	sh

YACC		?=	yacc
.if defined(%POSIX)
YFLAGS		?=
.else
YFLAGS		?=	-d
.endif

.if defined(%POSIX)

# Posix 1003.2 mandated rules
#
# Quoted directly from the Posix 1003.2 draft, only the macros
# $@, $< and $* have been replaced by ${.TARGET}, ${.IMPSRC}, and
# ${.PREFIX}, resp.

# SINGLE SUFFIX RULES
.c:
	${CC} ${CFLAGS} ${LDFLAGS} -o ${.TARGET} ${.IMPSRC}
	${CTFCONVERT_CMD}

.f:
	${FC} ${FFLAGS} ${LDFLAGS} -o ${.TARGET} ${.IMPSRC}
	${CTFCONVERT_CMD}

.sh:
	cp -f ${.IMPSRC} ${.TARGET}
	chmod a+x ${.TARGET}

# DOUBLE SUFFIX RULES

.c.o:
	${CC} ${CFLAGS} -c ${.IMPSRC}
	${CTFCONVERT_CMD}

.f.o:
	${FC} ${FFLAGS} -c ${.IMPSRC}
	${CTFCONVERT_CMD}

.y.o:
	${YACC} ${YFLAGS} ${.IMPSRC}
	${CC} ${CFLAGS} -c y.tab.c
	rm -f y.tab.c
	mv y.tab.o ${.TARGET}
	${CTFCONVERT_CMD}

.l.o:
	${LEX} ${LFLAGS} ${.IMPSRC}
	${CC} ${CFLAGS} -c lex.yy.c
	rm -f lex.yy.c
	mv lex.yy.o ${.TARGET}
	${CTFCONVERT_CMD}

.y.c:
	${YACC} ${YFLAGS} ${.IMPSRC}
	mv y.tab.c ${.TARGET}

.l.c:
	${LEX} ${LFLAGS} ${.IMPSRC}
	mv lex.yy.c ${.TARGET}

.c.a:
	${CC} ${CFLAGS} -c ${.IMPSRC}
	${AR} ${ARFLAGS} ${.TARGET} ${.PREFIX}.o
	rm -f ${.PREFIX}.o

.f.a:
	${FC} ${FFLAGS} -c ${.IMPSRC}
	${AR} ${ARFLAGS} ${.TARGET} ${.PREFIX}.o
	rm -f ${.PREFIX}.o

.else

# non-Posix rule set

.sh:
	cp -fp ${.IMPSRC} ${.TARGET}
	chmod a+x ${.TARGET}

.c.ln:
	${LINT} ${LINTOBJFLAGS} ${CFLAGS:M-[DIU]*} ${.IMPSRC} || \
	    touch ${.TARGET}

.cc.ln .C.ln .cpp.ln .cxx.ln:
	${LINT} ${LINTOBJFLAGS} ${CXXFLAGS:M-[DIU]*} ${.IMPSRC} || \
	    touch ${.TARGET}

.c:
	${CC} ${CFLAGS} ${LDFLAGS} ${.IMPSRC} ${LDLIBS} -o ${.TARGET}
	${CTFCONVERT_CMD}

.c.o:
	${CC} ${CFLAGS} -c ${.IMPSRC}
	${CTFCONVERT_CMD}

.cc .cpp .cxx .C:
	${CXX} ${CXXFLAGS} ${LDFLAGS} ${.IMPSRC} ${LDLIBS} -o ${.TARGET}

.cc.o .cpp.o .cxx.o .C.o:
	${CXX} ${CXXFLAGS} -c ${.IMPSRC}

.m.o:
	${OBJC} ${OBJCFLAGS} -c ${.IMPSRC}
	${CTFCONVERT_CMD}

.p.o:
	${PC} ${PFLAGS} -c ${.IMPSRC}
	${CTFCONVERT_CMD}

.e .r .F .f:
	${FC} ${RFLAGS} ${EFLAGS} ${FFLAGS} ${LDFLAGS} ${.IMPSRC} ${LDLIBS} \
	    -o ${.TARGET}

.e.o .r.o .F.o .f.o:
	${FC} ${RFLAGS} ${EFLAGS} ${FFLAGS} -c ${.IMPSRC}

.S.o:
	${CC} ${CFLAGS} ${ACFLAGS} -c ${.IMPSRC}
	${CTFCONVERT_CMD}

.asm.o:
	${CC} -x assembler-with-cpp ${CFLAGS} ${ACFLAGS} -c ${.IMPSRC}
	${CTFCONVERT_CMD}

.s.o:
	${AS} ${AFLAGS} -o ${.TARGET} ${.IMPSRC}
	${CTFCONVERT_CMD}

# XXX not -j safe
.y.o:
	${YACC} ${YFLAGS} ${.IMPSRC}
	${CC} ${CFLAGS} -c y.tab.c -o ${.TARGET}
	rm -f y.tab.c
	${CTFCONVERT_CMD}

.l.o:
	${LEX} -t ${LFLAGS} ${.IMPSRC} > ${.PREFIX}.tmp.c
	${CC} ${CFLAGS} -c ${.PREFIX}.tmp.c -o ${.TARGET}
	rm -f ${.PREFIX}.tmp.c
	${CTFCONVERT_CMD}

# XXX not -j safe
.y.c:
	${YACC} ${YFLAGS} ${.IMPSRC}
	mv y.tab.c ${.TARGET}

.l.c:
	${LEX} -t ${LFLAGS} ${.IMPSRC} > ${.TARGET}

.s.out .c.out .o.out:
	${CC} ${CFLAGS} ${LDFLAGS} ${.IMPSRC} ${LDLIBS} -o ${.TARGET}
	${CTFCONVERT_CMD}

.f.out .F.out .r.out .e.out:
	${FC} ${EFLAGS} ${RFLAGS} ${FFLAGS} ${LDFLAGS} ${.IMPSRC} \
	    ${LDLIBS} -o ${.TARGET}
	rm -f ${.PREFIX}.o
	${CTFCONVERT_CMD}

# XXX not -j safe
.y.out:
	${YACC} ${YFLAGS} ${.IMPSRC}
	${CC} ${CFLAGS} ${LDFLAGS} y.tab.c ${LDLIBS} -ly -o ${.TARGET}
	rm -f y.tab.c
	${CTFCONVERT_CMD}

.l.out:
	${LEX} -t ${LFLAGS} ${.IMPSRC} > ${.PREFIX}.tmp.c
	${CC} ${CFLAGS} ${LDFLAGS} ${.PREFIX}.tmp.c ${LDLIBS} -ll -o ${.TARGET}
	rm -f ${.PREFIX}.tmp.c
	${CTFCONVERT_CMD}

# FreeBSD build pollution.  Hide it in the non-POSIX part of the ifdef.
__MAKE_CONF?=/etc/make.conf
.if exists(${__MAKE_CONF})
.include "${__MAKE_CONF}"
.endif

.if defined(__MAKE_SHELL) && !empty(__MAKE_SHELL)
SHELL=	${__MAKE_SHELL}
.SHELL: path=${__MAKE_SHELL}
.endif

# Default executable format
# XXX hint for bsd.port.mk
OBJFORMAT?=	elf

# Tell bmake to expand -V VAR by default
.MAKE.EXPAND_VARIABLES= yes

# Tell bmake the makefile preference
.MAKE.MAKEFILE_PREFERENCE= BSDmakefile makefile Makefile

.if !defined(.PARSEDIR)
# We are not bmake, which is more aggressive about searching .PATH
# It is sometime necessary to curb its enthusiasm with .NOPATH
# The following allows us to quietly ignore .NOPATH when not using bmake.
.NOTMAIN: .NOPATH
.NOPATH:

# Toggle on warnings
.WARN: dirsyntax
.endif

.endif

.include <bsd.compat.mk>
.include <bsd.cpu.mk>
