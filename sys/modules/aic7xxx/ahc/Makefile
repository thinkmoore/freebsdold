
# $FreeBSD: stable/9/sys/modules/aic7xxx/ahc/Makefile 136854 2004-10-24 07:54:44Z ru $

.PATH:	${.CURDIR}/../../../dev/aic7xxx
KMOD=	ahc
SUBDIR=	ahc_eisa ahc_isa ahc_pci

GENSRCS= aic7xxx_seq.h aic7xxx_reg.h
AHC_REG_PRETTY_PRINT=1
REG_PRINT_OPT=
.ifdef AHC_REG_PRETTY_PRINT
GENSRCS+= aic7xxx_reg_print.c
CFLAGS+= -DAHC_REG_PRETTY_PRINT=1
REG_PRINT_OPT= -p aic7xxx_reg_print.c
.endif
BEFORE_DEPEND = ${GENSRCS}

../aicasm/aicasm: ${.CURDIR}/../../../dev/aci7xxx/aicasm/*.[chyl]
	( cd ${.CURDIR}/../aicasm; ${MAKE} aicasm; )

${GENSRCS}:								 \
		${.CURDIR}/../../../dev/aic7xxx/aic7xxx.{reg,seq}	 \
		${.CURDIR}/../../../cam/scsi/scsi_message.h ../aicasm/aicasm
	../aicasm/aicasm ${INCLUDES} -I${.CURDIR}/../../../cam/scsi	 \
			-I${.CURDIR}/../../../dev/aic7xxx		 \
			-o aic7xxx_seq.h -r aic7xxx_reg.h		 \
			${REG_PRINT_OPT}				 \
			-i ${.CURDIR}/../../../dev/aic7xxx/aic7xxx_osm.h \
			${.CURDIR}/../../../dev/aic7xxx/aic7xxx.seq

SRCS= ${GENSRCS}
SRCS+= aic7xxx.c aic7xxx_93cx6.c aic7xxx_osm.c aic7770.c
SRCS+= opt_scsi.h opt_aic7xxx.h opt_cam.h
SRCS+= device_if.h bus_if.h pci_if.h

CLEANFILES= ${GENSRCS}

.include <bsd.kmod.mk>
