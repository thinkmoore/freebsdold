# $FreeBSD: stable/9/sys/modules/drm2/i915kms/Makefile 239965 2012-09-01 05:35:48Z kib $

.PATH:	${.CURDIR}/../../../dev/drm2/i915
KMOD	= i915kms
SRCS	= \
	i915_debug.c \
	i915_dma.c \
	i915_drv.c \
	i915_gem.c \
	i915_gem_execbuffer.c \
	i915_gem_evict.c \
	i915_gem_gtt.c \
	i915_gem_tiling.c \
	i915_irq.c \
	i915_suspend.c \
	intel_bios.c \
	intel_crt.c \
	intel_display.c \
	intel_dp.c \
	intel_fb.c \
	intel_hdmi.c \
	intel_iic.c \
	intel_lvds.c \
	intel_modes.c \
	intel_opregion.c \
	intel_overlay.c \
	intel_panel.c \
	intel_ringbuffer.c \
	intel_sdvo.c \
	intel_sprite.c \
	intel_tv.c

.if ${MACHINE_CPUARCH} == "amd64"
SRCS	+= i915_ioc32.c
.endif

SRCS	+= device_if.h bus_if.h pci_if.h iicbus_if.h iicbb_if.h opt_drm.h \
	 opt_compat.h

.include <bsd.kmod.mk>
