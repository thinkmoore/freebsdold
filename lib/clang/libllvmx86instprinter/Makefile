# $FreeBSD: stable/9/lib/clang/libllvmx86instprinter/Makefile 246637 2013-02-10 21:24:47Z dim $

.include <bsd.own.mk>

LIB=	llvmx86instprinter

SRCDIR=	lib/Target/X86/InstPrinter
INCDIR=	lib/Target/X86
SRCS=	X86ATTInstPrinter.cpp \
	X86InstComments.cpp \
	X86IntelInstPrinter.cpp

TGHDRS=	X86GenAsmWriter \
	X86GenAsmWriter1 \
	X86GenInstrInfo \
	X86GenRegisterInfo \
	X86GenSubtargetInfo

.include "../clang.lib.mk"
