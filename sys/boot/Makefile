# $FreeBSD: stable/9/sys/boot/Makefile 223539 2011-06-25 16:01:45Z marius $

.include <bsd.own.mk>
.include <bsd.arch.inc.mk>

.if ${MK_FORTH} != "no"
# Build the add-in FORTH interpreter.
SUBDIR+=		ficl
.endif

# Pick the machine-dependent subdir based on the target architecture.
ADIR=			${MACHINE:S/amd64/i386/:S/powerpc64/powerpc/}
.if exists(${.CURDIR}/${ADIR}/.)
SUBDIR+=		${ADIR}
.endif

.include <bsd.subdir.mk>
