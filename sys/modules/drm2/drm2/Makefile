# $FreeBSD: stable/9/sys/modules/drm2/drm2/Makefile 249082 2013-04-04 05:47:50Z kib $

.PATH:	${.CURDIR}/../../../dev/drm2
KMOD	= drm2
SRCS	= \
	drm_agpsupport.c \
	drm_auth.c \
	drm_bufs.c \
	drm_context.c \
	drm_crtc.c \
	drm_crtc_helper.c \
	drm_dma.c \
	drm_dp_iic_helper.c \
	drm_drawable.c \
	drm_drv.c \
	drm_edid.c \
	drm_fb_helper.c \
	drm_fops.c \
	drm_gem.c \
	drm_gem_names.c \
	drm_global.c \
	drm_hashtab.c \
	drm_ioctl.c \
	drm_irq.c \
	drm_linux_list_sort.c \
	drm_lock.c \
	drm_memory.c \
	drm_mm.c \
	drm_modes.c \
	drm_pci.c \
	drm_scatter.c \
	drm_sman.c \
	drm_stub.c \
	drm_sysctl.c \
	drm_vm.c

.if ${MACHINE_CPUARCH} == "amd64"
SRCS	+= drm_ioc32.c
.endif

SRCS	+=device_if.h bus_if.h pci_if.h device_if.h iicbus_if.h opt_drm.h \
	opt_vm.h opt_compat.h

.include <bsd.kmod.mk>
