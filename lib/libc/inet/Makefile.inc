# $FreeBSD: stable/9/lib/libc/inet/Makefile.inc 157049 2006-03-23 16:55:13Z des $

# inet sources
.PATH: ${.CURDIR}/inet

SRCS+=	inet_addr.c inet_cidr_ntop.c inet_cidr_pton.c inet_lnaof.c \
	inet_makeaddr.c inet_net_ntop.c inet_net_pton.c inet_neta.c \
	inet_netof.c inet_network.c inet_ntoa.c inet_ntop.c \
	inet_pton.c nsap_addr.c

SYM_MAPS+= ${.CURDIR}/inet/Symbol.map
