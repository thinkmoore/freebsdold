#  $FreeBSD: stable/9/sys/boot/arm/at91/libat91/Makefile 171794 2007-08-09 05:16:55Z imp $

.include "${.CURDIR}/../Makefile.inc"

LIB=		at91
INTERNALLIB=
SRCS=at91rm9200_lowlevel.c delay.c eeprom.c emac.c emac_init.c getc.c \
	putchar.c printf.c reset.c spi_flash.c xmodem.c \
	sd-card.c strcvt.c strlen.c strcmp.c memcpy.c strcpy.c \
	memset.c memcmp.c
SRCS+=ashldi3.c divsi3.S
NO_MAN=

.if ${MK_TAG_LIST} != "no"
CFLAGS += -I${.CURDIR}/.. -DSUPPORT_TAG_LIST
SRCS+=tag_list.c
.endif

.include <bsd.lib.mk>
