# $FreeBSD: stable/9/sys/boot/powerpc/boot1.chrp/Makefile 232432 2012-03-03 02:20:46Z nwhitehorn $

WITHOUT_SSP=

PROG=           boot1.elf
NEWVERSWHAT=    "Open Firmware boot block" ${MACHINE_ARCH}
BINDIR?=        /boot
INSTALLFLAGS=   -b

FILES=		boot1.hfs
SRCS=		boot1.c ashldi3.c syncicache.c

INTERNALPROG=
NO_MAN=

CFLAGS= -ffreestanding -msoft-float -Os \
	-I${.CURDIR}/../../common -I${.CURDIR}/../../../ \
	-D_STANDALONE
LDFLAGS=-nostdlib -static -N

.include "${.CURDIR}/../Makefile.inc"
.PATH:  ${.CURDIR}/../../../libkern ${.CURDIR}/../../../../lib/libc/powerpc/gen ${.CURDIR}

# The following inserts out objects into a template HFS 
# created by generate-hfs.sh

.include "${.CURDIR}/Makefile.hfs"

boot1.hfs: boot1.elf bootinfo.txt
	echo ${.OBJDIR}
	uudecode ${.CURDIR}/hfs.tmpl.bz2.uu
	mv hfs.tmpl.bz2 ${.TARGET}.bz2
	bzip2 -f -d ${.TARGET}.bz2
	dd if=boot1.elf of=${.TARGET} seek=${BOOT1_OFFSET} conv=notrunc
	dd if=${.CURDIR}/bootinfo.txt of=${.TARGET} seek=${BOOTINFO_OFFSET} \
	    conv=notrunc

CLEANFILES= boot1.hfs

boot1.o: ${.CURDIR}/../../common/ufsread.c

.include <bsd.prog.mk>

