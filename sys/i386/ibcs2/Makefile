# Makefile for syscall tables
#
# $FreeBSD: stable/9/sys/i386/ibcs2/Makefile 155359 2006-02-05 23:25:19Z rwatson $

all:
	@echo "make sysent, isc_sysent or xenix_sysent only"

sysent:  ibcs2_sysent.c ibcs2_syscall.h ibcs2_proto.h

ibcs2_sysent.c ibcs2_syscall.h ibcs2_proto.h: ../../kern/makesyscalls.sh \
		syscalls.master syscalls.conf
	-mv -f ibcs2_sysent.c ibcs2_sysent.c.bak
	-mv -f ibcs2_syscall.h ibcs2_syscall.h.bak
	-mv -f ibcs2_proto.h ibcs2_proto.h.bak
	sh ../../kern/makesyscalls.sh syscalls.master syscalls.conf

isc_sysent:  ibcs2_isc_sysent.c ibcs2_isc_syscall.h

ibcs2_isc_sysent.c ibcs2_isc_syscall.h : ../../kern/makesyscalls.sh \
		syscalls.isc syscalls.isc.conf
	-mv -f ibcs2_isc_sysent.c ibcs2_isc_sysent.c.bak
	-mv -f ibcs2_isc_syscall.h ibcs2_isc_syscall.h.bak
	sh ../../kern/makesyscalls.sh syscalls.isc syscalls.isc.conf

xenix_sysent:  ibcs2_xenix_sysent.c ibcs2_xenix_syscall.h ibcs2_xenix.h

ibcs2_xenix_sysent.c ibcs2_xenix_syscall.h ibcs2_xenix.h: \
		../../kern/makesyscalls.sh syscalls.xenix syscalls.xenix.conf
	-mv -f ibcs2_xenix_sysent.c ibcs2_xenix_sysent.c.bak
	-mv -f ibcs2_xenix_syscall.h ibcs2_xenix_syscall.h.bak
	-mv -f ibcs2_xenix.h ibcs2_xenix.h.bak
	sh ../../kern/makesyscalls.sh syscalls.xenix syscalls.xenix.conf
