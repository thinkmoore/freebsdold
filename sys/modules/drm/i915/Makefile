# $FreeBSD: stable/9/sys/modules/drm/i915/Makefile 182080 2008-08-23 20:59:12Z rnoland $

.PATH:	${.CURDIR}/../../../dev/drm
KMOD	= i915
SRCS	= i915_dma.c i915_drv.c i915_irq.c i915_mem.c i915_suspend.c
SRCS	+=device_if.h bus_if.h pci_if.h opt_drm.h

.include <bsd.kmod.mk>
