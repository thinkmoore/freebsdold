
# $FreeBSD: stable/9/sys/modules/aic7xxx/ahc/ahc_isa/Makefile 133912 2004-08-17 02:32:30Z gibbs $

.PATH:	${.CURDIR}/../../../../dev/aic7xxx
KMOD=		ahc_isa

../aic7xxx_reg.h:
	( cd .. ; ${MAKE} aic7xxx_reg.h )

SRCS=	ahc_isa.c ../aic7xxx_reg.h
SRCS+=	device_if.h bus_if.h pci_if.h isa_if.h
SRCS+=	opt_scsi.h opt_cam.h opt_aic7xxx.h

CFLAGS+=	-I${.CURDIR}/../../../../dev/aic7xxx -I..

CLEANFILES=	../aic7xxx_reg.h ../aic7xxx_seq.h

.include <bsd.kmod.mk>
