# $FreeBSD: stable/9/sys/modules/netmap/Makefile 236519 2012-06-03 17:51:53Z luigi $
#
# Compile netmap as a module, useful if you want a netmap bridge
# or loadable drivers.

.PATH: ${.CURDIR}/../../dev/netmap
.PATH.h: ${.CURDIR}/../../net
KMOD	= netmap
SRCS	= device_if.h bus_if.h opt_netmap.h
SRCS	+= netmap.c netmap.h netmap_kern.h

netmap.o: netmap_mem2.c

.include <bsd.kmod.mk>
