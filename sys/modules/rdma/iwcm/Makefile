# $FreeBSD: stable/9/sys/modules/rdma/iwcm/Makefile 178794 2008-05-05 20:19:33Z kmacy $

RDMA=	${.CURDIR}/../../../contrib/rdma
.PATH: ${RDMA}

KMOD=  rdma_iwcm
SRCS=  device_if.h bus_if.h pci_if.h pcib_if.h opt_sched.h
SRCS+= rdma_iwcm.c 

.include <bsd.kmod.mk>
