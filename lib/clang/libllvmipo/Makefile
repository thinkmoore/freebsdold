# $FreeBSD: stable/9/lib/clang/libllvmipo/Makefile 245431 2013-01-14 19:51:26Z dim $

.include <bsd.own.mk>

LIB=	llvmipo

SRCDIR=	lib/Transforms/IPO
SRCS=	ArgumentPromotion.cpp \
	BarrierNoopPass.cpp \
	ConstantMerge.cpp \
	DeadArgumentElimination.cpp \
	ExtractGV.cpp \
	FunctionAttrs.cpp \
	GlobalDCE.cpp \
	GlobalOpt.cpp \
	IPConstantPropagation.cpp \
	InlineAlways.cpp \
	InlineSimple.cpp \
	Inliner.cpp \
	Internalize.cpp \
	LoopExtractor.cpp \
	MergeFunctions.cpp \
	PartialInlining.cpp \
	PassManagerBuilder.cpp \
	PruneEH.cpp \
	StripDeadPrototypes.cpp \
	StripSymbols.cpp

.if ${MK_CLANG_EXTRAS} != "no"
SRCS+=	IPO.cpp
.endif

TGHDRS=	Intrinsics

.include "../clang.lib.mk"
