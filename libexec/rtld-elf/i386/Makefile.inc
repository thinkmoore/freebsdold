# $FreeBSD: stable/9/libexec/rtld-elf/i386/Makefile.inc 217026 2011-01-05 21:23:26Z dim $

CFLAGS+=	-mno-mmx -mno-3dnow -mno-sse -mno-sse2 -mno-sse3 -msoft-float
# Uncomment this to build the dynamic linker as an executable instead
# of a shared library:
#LDSCRIPT=	${.CURDIR}/${MACHINE_CPUARCH}/elf_rtld.x
