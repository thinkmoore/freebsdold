# $FreeBSD: stable/9/sys/modules/drm/radeon/Makefile 229731 2012-01-06 21:14:54Z dim $

.PATH:	${.CURDIR}/../../../dev/drm
KMOD	= radeon
SRCS	= r300_cmdbuf.c r600_blit.c r600_cp.c radeon_cp.c radeon_cs.c \
	radeon_drv.c radeon_irq.c radeon_mem.c radeon_state.c
SRCS	+=device_if.h bus_if.h pci_if.h opt_drm.h

.include <bsd.kmod.mk>

CWARNFLAGS.r600_cp.c=	${NO_WUNUSED_VALUE} ${NO_WCONSTANT_CONVERSION}
CWARNFLAGS.radeon_cp.c=	${NO_WUNUSED_VALUE} ${NO_WCONSTANT_CONVERSION}
CWARNFLAGS+=		${CWARNFLAGS.${.IMPSRC:T}}
