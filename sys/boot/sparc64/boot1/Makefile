# $FreeBSD: stable/9/sys/boot/sparc64/boot1/Makefile 236076 2012-05-26 08:54:26Z marius $

PROG=	boot1.elf
INTERNALPROG=
NO_MAN=
FILES?=	boot1
SRCS=	_start.s boot1.c
CLEANFILES=${FILES} boot1.aout

BOOTBLOCKBASE= 0x4000

CFLAGS+=-mcmodel=medlow -Os -I${.CURDIR}/../../common
LDFLAGS=-Ttext ${BOOTBLOCKBASE} -Wl,-N

# Construct boot1. sunlabel expects it to contain zeroed-out space for the
# label, and to be of the correct size.
${FILES}: boot1.aout
	@set -- `ls -l boot1.aout`; x=$$((7680-$$5)); \
	    echo "$$x bytes available"; test $$x -ge 0
	dd if=/dev/zero of=${.TARGET} bs=512 count=16
	dd if=boot1.aout of=${.TARGET} bs=512 oseek=1 conv=notrunc

boot1.aout: boot1.elf
	elf2aout -o ${.TARGET} ${.ALLSRC}

boot1.o: ${.CURDIR}/../../common/ufsread.c

.include <bsd.prog.mk>
