#	From: @(#)Makefile	8.1 (Berkeley) 5/31/93
# $FreeBSD: stable/9/bin/Makefile 212515 2010-09-13 01:29:51Z imp $

.include <bsd.own.mk>

SUBDIR= cat \
	chflags \
	chio \
	chmod \
	cp \
	date \
	dd \
	df \
	domainname \
	echo \
	ed \
	expr \
	getfacl \
	hostname \
	kenv \
	kill \
	ln \
	ls \
	mkdir \
	mv \
	pax \
	pkill \
	ps \
	pwait \
	pwd \
	realpath \
	rm \
	rmdir \
	setfacl \
	sh \
	sleep \
	stty \
	sync \
	test \
	uuidgen

.if ${MK_RCMDS} != "no"
SUBDIR+=	rcp
.endif

.if ${MK_SENDMAIL} != "no"
SUBDIR+=	rmail
.endif

.if ${MK_TCSH} != "no"
SUBDIR+=	csh
.endif

.include <bsd.arch.inc.mk>

SUBDIR:=	${SUBDIR:O}

.include <bsd.subdir.mk>
