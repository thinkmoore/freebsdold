# $FreeBSD: stable/9/share/mk/bsd.compiler.mk 253220 2013-07-11 20:09:46Z dim $

.if !defined(COMPILER_TYPE)
. if ${CC:T:Mgcc*}
COMPILER_TYPE:=	gcc  
. elif ${CC:T:Mclang}
COMPILER_TYPE:=	clang
. else
_COMPILER_VERSION!=	${CC} --version
.  if ${_COMPILER_VERSION:Mgcc}
COMPILER_TYPE:=	gcc
.  elif ${_COMPILER_VERSION:M\(GCC\)}
COMPILER_TYPE:=	gcc
.  elif ${_COMPILER_VERSION:Mclang}
COMPILER_TYPE:=	clang
.  else
.error Unable to determine compiler type for ${CC}
.  endif
.  undef _COMPILER_VERSION
. endif
.endif

.if ${COMPILER_TYPE} == "clang"
COMPILER_FEATURES=	c++11
.else
COMPILER_FEATURES=
.endif
