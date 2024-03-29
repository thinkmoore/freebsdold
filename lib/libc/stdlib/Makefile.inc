#	from @(#)Makefile.inc	8.3 (Berkeley) 2/4/95
# $FreeBSD: stable/9/lib/libc/stdlib/Makefile.inc 243405 2012-11-22 15:19:53Z ed $

# machine-independent stdlib sources
.PATH: ${.CURDIR}/${LIBC_ARCH}/stdlib ${.CURDIR}/stdlib

MISRCS+=_Exit.c a64l.c abort.c abs.c atexit.c atof.c atoi.c atol.c atoll.c \
	bsearch.c div.c exit.c getenv.c getopt.c getopt_long.c \
	getsubopt.c hcreate.c heapsort.c imaxabs.c imaxdiv.c \
	insque.c l64a.c labs.c ldiv.c llabs.c lldiv.c lsearch.c malloc.c \
	merge.c ptsname.c qsort.c qsort_r.c quick_exit.c radixsort.c rand.c \
	random.c reallocf.c realpath.c remque.c strfmon.c strtoimax.c \
	strtol.c strtoll.c strtoq.c strtoul.c strtonum.c strtoull.c \
        strtoumax.c strtouq.c system.c tdelete.c tfind.c tsearch.c twalk.c

SYM_MAPS+= ${.CURDIR}/stdlib/Symbol.map

# machine-dependent stdlib sources
.sinclude "${.CURDIR}/${LIBC_ARCH}/stdlib/Makefile.inc"

MAN+=	a64l.3 abort.3 abs.3 aligned_alloc.3 alloca.3 atexit.3 atof.3 \
	atoi.3 atol.3 at_quick_exit.3 bsearch.3 \
	div.3 exit.3 getenv.3 getopt.3 getopt_long.3 getsubopt.3 \
	hcreate.3 imaxabs.3 imaxdiv.3 insque.3 labs.3 ldiv.3 llabs.3 lldiv.3 \
	lsearch.3 malloc.3 memory.3 ptsname.3 qsort.3 \
	quick_exit.3 \
	radixsort.3 rand.3 random.3 \
	realpath.3 strfmon.3 strtod.3 strtol.3 strtonum.3 strtoul.3 system.3 \
	tsearch.3

MLINKS+=a64l.3 l64a.3 a64l.3 l64a_r.3
MLINKS+=aligned_alloc.3 posix_memalign.3
MLINKS+=atol.3 atoll.3
MLINKS+=exit.3 _Exit.3
MLINKS+=getenv.3 putenv.3 getenv.3 setenv.3 getenv.3 unsetenv.3
MLINKS+=getopt_long.3 getopt_long_only.3
MLINKS+=hcreate.3 hdestroy.3 hcreate.3 hsearch.3
MLINKS+=insque.3 remque.3
MLINKS+=lsearch.3 lfind.3
MLINKS+=ptsname.3 grantpt.3 ptsname.3 unlockpt.3
MLINKS+=qsort.3 heapsort.3 qsort.3 mergesort.3 qsort.3 qsort_r.3
MLINKS+=rand.3 rand_r.3 rand.3 srand.3 rand.3 sranddev.3
MLINKS+=random.3 initstate.3 random.3 setstate.3 random.3 srandom.3 \
	random.3 srandomdev.3
MLINKS+=radixsort.3 sradixsort.3
MLINKS+=strfmon.3 strfmon_l.3
MLINKS+=strtod.3 strtof.3 strtod.3 strtold.3
MLINKS+=strtol.3 strtoll.3 strtol.3 strtoq.3 strtol.3 strtoimax.3
MLINKS+=strtoul.3 strtoull.3 strtoul.3 strtouq.3 strtoul.3 strtoumax.3
MLINKS+=malloc.3 calloc.3 malloc.3 free.3 malloc.3 malloc.conf.5 \
	malloc.3 realloc.3 malloc.3 reallocf.3 malloc.3 malloc_usable_size.3
MLINKS+=tsearch.3 tdelete.3 tsearch.3 tfind.3 tsearch.3 twalk.3

.if defined(MALLOC_PRODUCTION)
CFLAGS+=	-DMALLOC_PRODUCTION
.endif

