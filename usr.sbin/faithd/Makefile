# Copyright (c) 1996 WIDE Project. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modifications, are permitted provided that the above copyright notice
# and this paragraph are duplicated in all such forms and that any
# documentation, advertising materials, and other materials related to
# such distribution and use acknowledge that the software was developed
# by the WIDE Project, Japan. The name of the Project may not be used to
# endorse or promote products derived from this software without
# specific prior written permission. THIS SOFTWARE IS PROVIDED ``AS IS''
# AND WITHOUT ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, WITHOUT
# LIMITATION, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE.
#
# $FreeBSD: stable/9/usr.sbin/faithd/Makefile 201390 2010-01-02 11:07:44Z ed $

PROG=	faithd
MAN=	faithd.8
SRCS=	faithd.c tcp.c ftp.c prefix.c

CFLAGS+= -DHAVE_POLL_H

WARNS?=	2

.include <bsd.prog.mk>
