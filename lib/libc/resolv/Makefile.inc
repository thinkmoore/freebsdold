# $FreeBSD: stable/9/lib/libc/resolv/Makefile.inc 158787 2006-05-21 11:19:36Z ume $

# resolv sources
.PATH: ${.CURDIR}/resolv

SRCS+=	herror.c h_errno.c mtctxres.c res_comp.c res_data.c res_debug.c \
	res_findzonecut.c res_init.c res_mkquery.c res_mkupdate.c \
	res_query.c res_send.c res_state.c res_update.c

SYM_MAPS+= ${.CURDIR}/resolv/Symbol.map
