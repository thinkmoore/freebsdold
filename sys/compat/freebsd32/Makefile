# Makefile for syscall tables
#
# $FreeBSD: stable/9/sys/compat/freebsd32/Makefile 219559 2011-03-12 08:51:43Z avg $

all:
	@echo "make sysent only"

sysent:  freebsd32_sysent.c freebsd32_syscall.h freebsd32_proto.h freebsd32_systrace_args.c

freebsd32_sysent.c freebsd32_syscalls.c freebsd32_syscall.h freebsd32_proto.h freebsd32_systrace_args.c : \
	    ../../kern/makesyscalls.sh syscalls.master syscalls.conf
	-mv -f freebsd32_sysent.c freebsd32_sysent.c.bak
	-mv -f freebsd32_syscalls.c freebsd32_syscalls.c.bak
	-mv -f freebsd32_syscall.h freebsd32_syscall.h.bak
	-mv -f freebsd32_proto.h freebsd32_proto.h.bak
	-mv -f freebsd32_systrace_args.c  freebsd32_systrace_args.c.bak
	sh ../../kern/makesyscalls.sh syscalls.master syscalls.conf

clean:
	rm -f freebsd32_sysent.c freebsd32_syscalls.c freebsd32_syscall.h freebsd32_proto.h
	rm -f freebsd32_systrace_args.c 
