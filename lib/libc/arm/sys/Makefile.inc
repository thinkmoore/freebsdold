# $FreeBSD: stable/9/lib/libc/arm/sys/Makefile.inc 246775 2013-02-13 23:25:11Z kib $

SRCS+=	__vdso_gettc.c

MDASM= Ovfork.S brk.S cerror.S pipe.S ptrace.S sbrk.S shmat.S sigreturn.S syscall.S

# Don't generate default code for these syscalls:
NOASM=	break.o exit.o getlogin.o openbsd_poll.o sstk.o vfork.o yield.o

PSEUDO= _exit.o _getlogin.o
.if !defined(WITHOUT_SYSCALL_COMPAT)
PSEUDO+= _pread.o _pwrite.o _lseek.o _mmap.o _ftruncate.o _truncate.o
.endif
