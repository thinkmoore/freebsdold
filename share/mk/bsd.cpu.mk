# $FreeBSD: stable/9/share/mk/bsd.cpu.mk 220863 2011-04-19 18:09:21Z dim $

# Set default CPU compile flags and baseline CPUTYPE for each arch.  The
# compile flags must support the minimum CPU type for each architecture but
# may tune support for more advanced processors.

.if !defined(CPUTYPE) || empty(CPUTYPE)
_CPUCFLAGS =
. if ${MACHINE_CPUARCH} == "i386"
MACHINE_CPU = i486
. elif ${MACHINE_CPUARCH} == "amd64"
MACHINE_CPU = amd64 sse2 sse mmx
. elif ${MACHINE_CPUARCH} == "ia64"
MACHINE_CPU = itanium
. elif ${MACHINE_CPUARCH} == "powerpc"
MACHINE_CPU = aim
. elif ${MACHINE_CPUARCH} == "sparc64"
MACHINE_CPU = ultrasparc
. elif ${MACHINE_CPUARCH} == "arm"
MACHINE_CPU = arm
. elif ${MACHINE_CPUARCH} == "mips"
MACHINE_CPU = mips
. endif
.else

# Handle aliases (not documented in make.conf to avoid user confusion
# between e.g. i586 and pentium)

. if ${MACHINE_CPUARCH} == "i386"
.  if ${CPUTYPE} == "nocona"
CPUTYPE = prescott
.  elif ${CPUTYPE} == "core"
CPUTYPE = prescott
.  elif ${CPUTYPE} == "p4"
CPUTYPE = pentium4
.  elif ${CPUTYPE} == "p4m"
CPUTYPE = pentium4m
.  elif ${CPUTYPE} == "p3"
CPUTYPE = pentium3
.  elif ${CPUTYPE} == "p3m"
CPUTYPE = pentium3m
.  elif ${CPUTYPE} == "p-m"
CPUTYPE = pentium-m
.  elif ${CPUTYPE} == "p2"
CPUTYPE = pentium2
.  elif ${CPUTYPE} == "i686"
CPUTYPE = pentiumpro
.  elif ${CPUTYPE} == "i586/mmx"
CPUTYPE = pentium-mmx
.  elif ${CPUTYPE} == "i586"
CPUTYPE = pentium
.  elif ${CPUTYPE} == "opteron-sse3" || ${CPUTYPE} == "athlon64-sse3" || \
     ${CPUTYPE} == "k8-sse3"
CPUTYPE = prescott
.  elif ${CPUTYPE} == "opteron" || ${CPUTYPE} == "athlon64" || \
     ${CPUTYPE} == "k8"
CPUTYPE = athlon-mp
.  elif ${CPUTYPE} == "k7"
CPUTYPE = athlon
.  endif
. elif ${MACHINE_CPUARCH} == "amd64"
.  if ${CPUTYPE} == "prescott"
CPUTYPE = nocona
.  endif
. elif ${MACHINE_ARCH} == "sparc64"
.  if ${CPUTYPE} == "us"
CPUTYPE = ultrasparc
.  elif ${CPUTYPE} == "us3"
CPUTYPE = ultrasparc3
.  endif
. endif

###############################################################################
# Logic to set up correct gcc optimization flag.  This must be included
# after /etc/make.conf so it can react to the local value of CPUTYPE
# defined therein.  Consult:
#	http://gcc.gnu.org/onlinedocs/gcc/ARM-Options.html
#	http://gcc.gnu.org/onlinedocs/gcc/IA_002d64-Options.html
#	http://gcc.gnu.org/onlinedocs/gcc/RS_002f6000-and-PowerPC-Options.html
#	http://gcc.gnu.org/onlinedocs/gcc/MIPS-Options.html
#	http://gcc.gnu.org/onlinedocs/gcc/SPARC-Options.html
#	http://gcc.gnu.org/onlinedocs/gcc/i386-and-x86_002d64-Options.html

. if ${MACHINE_CPUARCH} == "i386"
.  if ${CPUTYPE} == "crusoe"
_CPUCFLAGS = -march=i686 -falign-functions=0 -falign-jumps=0 -falign-loops=0
.  elif ${CPUTYPE} == "k5"
_CPUCFLAGS = -march=pentium
.  elif ${CPUTYPE} == "core2"
_CPUCFLAGS = -march=prescott
.  else
_CPUCFLAGS = -march=${CPUTYPE}
.  endif # GCC on 'i386'
. elif ${MACHINE_CPUARCH} == "amd64"
_CPUCFLAGS = -march=${CPUTYPE}
. elif ${MACHINE_CPUARCH} == "arm"
.  if ${CPUTYPE} == "xscale"
#XXX: gcc doesn't seem to like -mcpu=xscale, and dies while rebuilding itself
#_CPUCFLAGS = -mcpu=xscale
_CPUCFLAGS = -march=armv5te -D__XSCALE__
.  else
_CPUCFLAGS = -mcpu=${CPUTYPE}
.  endif
. elif ${MACHINE_ARCH} == "powerpc"
.  if ${CPUTYPE} == "e500"
_CPUCFLAGS = -Wa,-me500 -msoft-float
.  else
_CPUCFLAGS = -mcpu=${CPUTYPE} -mno-powerpc64
.  endif
. elif ${MACHINE_ARCH} == "powerpc64"
_CPUCFLAGS = -mcpu=${CPUTYPE}
. elif ${MACHINE_CPUARCH} == "mips"
.  if ${CPUTYPE} == "mips32"
_CPUCFLAGS = -march=mips32
.  elif ${CPUTYPE} == "mips32r2"
_CPUCFLAGS = -march=mips32r2
.  elif ${CPUTYPE} == "mips64"
_CPUCFLAGS = -march=mips64
.  elif ${CPUTYPE} == "mips64r2"
_CPUCFLAGS = -march=mips64r2
.  elif ${CPUTYPE} == "mips4kc"
_CPUCFLAGS = -march=4kc
.  elif ${CPUTYPE} == "mips24kc"
_CPUCFLAGS = -march=24kc
.  endif
. elif ${MACHINE_ARCH} == "sparc64"
.  if ${CPUTYPE} == "v9"
_CPUCFLAGS = -mcpu=v9
.  elif ${CPUTYPE} == "ultrasparc"
_CPUCFLAGS = -mcpu=ultrasparc
.  elif ${CPUTYPE} == "ultrasparc3"
_CPUCFLAGS = -mcpu=ultrasparc3
.  endif
. endif

# Set up the list of CPU features based on the CPU type.  This is an
# unordered list to make it easy for client makefiles to test for the
# presence of a CPU feature.

. if ${MACHINE_CPUARCH} == "i386"
.  if ${CPUTYPE} == "opteron-sse3" || ${CPUTYPE} == "athlon64-sse3"
MACHINE_CPU = athlon-xp athlon k7 3dnow sse3 sse2 sse mmx k6 k5 i586 i486 i386
.  elif ${CPUTYPE} == "opteron" || ${CPUTYPE} == "athlon64"
MACHINE_CPU = athlon-xp athlon k7 3dnow sse2 sse mmx k6 k5 i586 i486 i386
.  elif ${CPUTYPE} == "athlon-mp" || ${CPUTYPE} == "athlon-xp" || \
    ${CPUTYPE} == "athlon-4"
MACHINE_CPU = athlon-xp athlon k7 3dnow sse mmx k6 k5 i586 i486 i386
.  elif ${CPUTYPE} == "athlon" || ${CPUTYPE} == "athlon-tbird"
MACHINE_CPU = athlon k7 3dnow mmx k6 k5 i586 i486 i386
.  elif ${CPUTYPE} == "k6-3" || ${CPUTYPE} == "k6-2" || ${CPUTYPE} == "geode"
MACHINE_CPU = 3dnow mmx k6 k5 i586 i486 i386
.  elif ${CPUTYPE} == "k6"
MACHINE_CPU = mmx k6 k5 i586 i486 i386
.  elif ${CPUTYPE} == "k5"
MACHINE_CPU = k5 i586 i486 i386
.  elif ${CPUTYPE} == "c3"
MACHINE_CPU = 3dnow mmx i586 i486 i386
.  elif ${CPUTYPE} == "c3-2"
MACHINE_CPU = sse mmx i586 i486 i386
.  elif ${CPUTYPE} == "c7"
MACHINE_CPU = sse3 sse2 sse i686 mmx i586 i486 i386
.  elif ${CPUTYPE} == "core2"
MACHINE_CPU = ssse3 sse3 sse2 sse i686 mmx i586 i486 i386
.  elif ${CPUTYPE} == "prescott"
MACHINE_CPU = sse3 sse2 sse i686 mmx i586 i486 i386
.  elif ${CPUTYPE} == "pentium4" || ${CPUTYPE} == "pentium4m" || ${CPUTYPE} == "pentium-m"
MACHINE_CPU = sse2 sse i686 mmx i586 i486 i386
.  elif ${CPUTYPE} == "pentium3" || ${CPUTYPE} == "pentium3m"
MACHINE_CPU = sse i686 mmx i586 i486 i386
.  elif ${CPUTYPE} == "pentium2"
MACHINE_CPU = i686 mmx i586 i486 i386
.  elif ${CPUTYPE} == "pentiumpro"
MACHINE_CPU = i686 i586 i486 i386
.  elif ${CPUTYPE} == "pentium-mmx"
MACHINE_CPU = mmx i586 i486 i386
.  elif ${CPUTYPE} == "pentium"
MACHINE_CPU = i586 i486 i386
.  elif ${CPUTYPE} == "i486"
MACHINE_CPU = i486 i386
.  elif ${CPUTYPE} == "i386"
MACHINE_CPU = i386
.  endif
. elif ${MACHINE_CPUARCH} == "amd64"
.  if ${CPUTYPE} == "opteron-sse3" || ${CPUTYPE} == "athlon64-sse3" || ${CPUTYPE} == "k8-sse3"
MACHINE_CPU = k8 3dnow sse3
.  elif ${CPUTYPE} == "opteron" || ${CPUTYPE} == "athlon64" || ${CPUTYPE} == "k8"
MACHINE_CPU = k8 3dnow
.  elif ${CPUTYPE} == "core2"
MACHINE_CPU = ssse3 sse3
.  elif ${CPUTYPE} == "nocona"
MACHINE_CPU = sse3
.  endif
MACHINE_CPU += amd64 sse2 sse mmx
. elif ${MACHINE_CPUARCH} == "ia64"
.  if ${CPUTYPE} == "itanium"
MACHINE_CPU = itanium
.  endif
. elif ${MACHINE_ARCH} == "powerpc"
.  if ${CPUTYPE} == "e500"
MACHINE_CPU = booke
.  endif
. elif ${MACHINE_ARCH} == "sparc64"
.  if ${CPUTYPE} == "v9"
MACHINE_CPU = v9
.  elif ${CPUTYPE} == "ultrasparc"
MACHINE_CPU = v9 ultrasparc
.  elif ${CPUTYPE} == "ultrasparc3"
MACHINE_CPU = v9 ultrasparc ultrasparc3
.  endif
. endif
.endif

.if ${MACHINE_CPUARCH} == "mips"
CFLAGS += -G0
.endif

# NB: COPTFLAGS is handled in /usr/src/sys/conf/kern.pre.mk

.if !defined(NO_CPU_CFLAGS)
CFLAGS += ${_CPUCFLAGS}
.endif
