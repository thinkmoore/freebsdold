# $FreeBSD: stable/9/sys/modules/uart/Makefile 221869 2011-05-14 01:53:38Z attilio $

.PATH: ${.CURDIR}/../../dev/uart

.if ${MACHINE_CPUARCH} == "sparc64"
uart_bus_ebus=	uart_bus_ebus.c
ofw_bus_if=	ofw_bus_if.h
.endif

KMOD=	uart
SRCS=	uart_bus_acpi.c ${uart_bus_ebus} uart_bus_isa.c uart_bus_pccard.c \
	uart_bus_pci.c uart_bus_puc.c uart_bus_scc.c \
	uart_core.c uart_dbg.c \
	uart_dev_ns8250.c uart_dev_quicc.c uart_dev_sab82532.c \
	uart_dev_z8530.c \
	uart_if.c uart_if.h uart_subr.c uart_tty.c
.if exists(${.CURDIR}/../../dev/uart/uart_cpu_${MACHINE}.c)
SRCS+=	uart_cpu_${MACHINE}.c
.endif
SRCS+=	bus_if.h card_if.h device_if.h isa_if.h ${ofw_bus_if} pci_if.h \
	power_if.h pccarddevs.h serdev_if.h

MFILES= dev/pccard/card_if.m dev/pccard/power_if.m dev/pci/pci_if.m \
	dev/ofw/ofw_bus_if.m dev/uart/uart_if.m isa/isa_if.m kern/bus_if.m \
	kern/device_if.m kern/serdev_if.m

.include <bsd.kmod.mk>
