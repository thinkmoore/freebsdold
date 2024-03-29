# Common defines for all of /sys/boot/pc98/
#
# $FreeBSD: stable/9/sys/boot/pc98/Makefile.inc 243446 2012-11-23 13:17:18Z nyan $

BINDIR?=	/boot

LOADER_ADDRESS?=0x200000
CFLAGS+=	-march=i386 -ffreestanding -mpreferred-stack-boundary=2 \
		-mno-mmx -mno-3dnow -mno-sse -mno-sse2 -mno-sse3 -msoft-float
CFLAGS+=	-Os -DPC98
LDFLAGS+=	-nostdlib

# BTX components
.if exists(${.OBJDIR}/../btx)
BTXDIR=		${.OBJDIR}/../btx
.else
BTXDIR=		${.CURDIR}/../btx
.endif
BTXLDR=		${BTXDIR}/btxldr/btxldr
BTXKERN=	${BTXDIR}/btx/btx
BTXCRT=		${BTXDIR}/lib/crt0.o

.include "../Makefile.inc"
