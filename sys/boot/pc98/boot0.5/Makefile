# $FreeBSD: stable/9/sys/boot/pc98/boot0.5/Makefile 208789 2010-06-03 17:42:32Z ed $

PROG=	${BOOT}.out
INTERNALPROG=
FILES=	${BOOT}
NO_MAN=
SRCS=	start.s boot.s boot0.5.s disk.s selector.s support.s syscons.s \
	putssjis.s
CLEANFILES= ${BOOT} ${BOOT}.bin

BOOT=	boot0.5

# The base address that we the boot0 code to to run it.  Don't change this
# unless you are glutton for punishment.
BOOT_BOOT0_ORG?=	0x0000

LDFLAGS=-e start -Ttext ${BOOT_BOOT0_ORG} -Wl,-N,-T,${.CURDIR}/ldscript

# The size of boot0.5 must be 7168 bytes
${BOOT}: ${BOOT}.bin
	cat ${BOOT}.bin /dev/zero | dd of=${BOOT} bs=1 count=7168

${BOOT}.bin: ${BOOT}.out
	objcopy -S -O binary ${BOOT}.out ${.TARGET}

.include <bsd.prog.mk>
