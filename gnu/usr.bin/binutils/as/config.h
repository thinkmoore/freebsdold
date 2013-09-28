/* $FreeBSD: stable/9/gnu/usr.bin/binutils/as/config.h 218822 2011-02-18 20:54:12Z dim $ */

/* config.h.  Generated by configure.  */
/* config.in.  Generated from configure.in by autoheader.  */

/* Define if using AIX 5.2 value for C_WEAKEXT. */
/* #undef AIX_WEAK_SUPPORT */

/* assert broken? */
/* #undef BROKEN_ASSERT */

/* Define to one of `_getb67', `GETB67', `getb67' for Cray-2 and Cray-YMP
   systems. This function is required for `alloca.c' support on those systems.
   */
/* #undef CRAY_STACKSEG_END */

/* Compiling cross-assembler? */
/* #undef CROSS_COMPILE */

/* Define to 1 if using `alloca.c'. */
/* #undef C_ALLOCA */

/* Default architecture. */
/* #define DEFAULT_ARCH "i386" */

/* Default CRIS architecture. */
/* #undef DEFAULT_CRIS_ARCH */

/* Default emulation. */
/* #define DEFAULT_EMULATION "i386elf" */

/* Supported emulations. */
/* #define EMULATIONS &i386elf, */

/* Define if you want run-time sanity checks. */
/* #undef ENABLE_CHECKING */

/* Define to 1 if translation of program messages to the user's native
   language is requested. */
/* #undef ENABLE_NLS */

/* Define to 1 if you have `alloca', as a function or macro. */
#define HAVE_ALLOCA 1

/* Define to 1 if you have <alloca.h> and it should be used (not on Ultrix).
   */
/* #undef HAVE_ALLOCA_H */

/* Is the prototype for getopt in <unistd.h> in the expected format? */
#define HAVE_DECL_GETOPT 1

/* Define to 1 if you have the declaration of `vsnprintf', and to 0 if you
   don't. */
#define HAVE_DECL_VSNPRINTF 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you have the <errno.h> header file. */
#define HAVE_ERRNO_H 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `remove' function. */
/* #undef HAVE_REMOVE */

/* Define to 1 if you have the `sbrk' function. */
#define HAVE_SBRK 1

/* Define to 1 if you have the <stdarg.h> header file. */
#define HAVE_STDARG_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the `unlink' function. */
#define HAVE_UNLINK 1

/* Define to 1 if you have the <varargs.h> header file. */
/* #undef HAVE_VARARGS_H */

/* Using i386 COFF? */
/* #undef I386COFF */

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* Using m68k COFF? */
/* #undef M68KCOFF */

/* Using m88k COFF? */
/* #undef M88KCOFF */

/* Default CPU for MIPS targets. */
/* #undef MIPS_CPU_STRING_DEFAULT */

/* Generate 64-bit code by default on MIPS targets. */
/* #undef MIPS_DEFAULT_64BIT */

/* Choose a default ABI for MIPS targets. */
/* #undef MIPS_DEFAULT_ABI */

/* Define if environ is not declared in system header files. */
#define NEED_DECLARATION_ENVIRON 1

/* Define if errno is not declared in system header files. */
/* #undef NEED_DECLARATION_ERRNO */

/* Define if ffs is not declared in system header files. */
/* #undef NEED_DECLARATION_FFS */

/* Define if free is not declared in system header files. */
/* #undef NEED_DECLARATION_FREE */

/* Define if malloc is not declared in system header files. */
/* #undef NEED_DECLARATION_MALLOC */

/* Define if sbrk is not declared in system header files. */
/* #undef NEED_DECLARATION_SBRK */

/* Define if strstr is not declared in system header files. */
/* #undef NEED_DECLARATION_STRSTR */

/* a.out support? */
/* #undef OBJ_MAYBE_AOUT */

/* b.out support? */
/* #undef OBJ_MAYBE_BOUT */

/* COFF support? */
/* #undef OBJ_MAYBE_COFF */

/* ECOFF support? */
/* #undef OBJ_MAYBE_ECOFF */

/* ELF support? */
/* #undef OBJ_MAYBE_ELF */

/* generic support? */
/* #undef OBJ_MAYBE_GENERIC */

/* SOM support? */
/* #undef OBJ_MAYBE_SOM */

/* Name of package */
#define PACKAGE "gas"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT ""

/* Define to the full name of this package. */
#define PACKAGE_NAME ""

/* Define to the full name and version of this package. */
#define PACKAGE_STRING ""

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME ""

/* Define to the version of this package. */
#define PACKAGE_VERSION ""

/* Define if defaulting to ELF on SCO 5. */
/* #undef SCO_ELF */

/* If using the C implementation of alloca, define if you know the
   direction of stack growth for your system; otherwise it will be
   automatically deduced at run-time.
	STACK_DIRECTION > 0 => grows toward higher addresses
	STACK_DIRECTION < 0 => grows toward lower addresses
	STACK_DIRECTION = 0 => direction of growth unknown */
/* #undef STACK_DIRECTION */

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Using strict COFF? */
/* #undef STRICTCOFF */

/* Target alias. */
/* #define TARGET_ALIAS "i386-unknown-freebsd9.0" */

/* Define as 1 if big endian. */
/* #undef TARGET_BYTES_BIG_ENDIAN */

/* Canonical target. */
/* #define TARGET_CANONICAL "i386-unknown-freebsd9.0" */

/* Target CPU. */
/* #define TARGET_CPU "i386" */

/* Target OS. */
/* #define TARGET_OS "freebsd9.0" */

/* Define if default target is PowerPC Solaris. */
/* #undef TARGET_SOLARIS_COMMENT */

/* Define if target is Symbian OS. */
/* #undef TARGET_SYMBIAN */

/* Target vendor. */
/* #define TARGET_VENDOR "unknown" */

/* Use b modifier when opening binary files? */
/* #undef USE_BINARY_FOPEN */

/* Use emulation support? */
/* #undef USE_EMULATIONS */

/* Allow use of E_MIPS_ABI_O32 on MIPS targets. */
/* #undef USE_E_MIPS_ABI_O32 */

/* Using cgen code? */
/* #undef USING_CGEN */

/* Version number of package */
/* #define VERSION "2.17.50" */

/* Define to 1 if your processor stores words with the most significant byte
   first (like Motorola and SPARC, unlike Intel and VAX). */
/* #undef WORDS_BIGENDIAN */

/* Define to 1 if `lex' declares `yytext' as a `char *' by default, not a
   `char[]'. */
#define YYTEXT_POINTER 1

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
/* #undef inline */
#endif
