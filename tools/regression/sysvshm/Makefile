# $FreeBSD: stable/9/tools/regression/sysvshm/Makefile 139103 2004-12-21 08:47:35Z ru $
# SysV Shared Memory Regression Utility
# Obtained from: $NetBSD: Makefile,v 1.3 2002/03/05 21:57:00 thorpej Exp $

PROG=	shmtest
NO_MAN=

regress:
	@if ./shmtest ./shmtest; then \
		echo "PASS"; \
	else \
		echo "FAIL"; \
	fi

.include <bsd.prog.mk>
