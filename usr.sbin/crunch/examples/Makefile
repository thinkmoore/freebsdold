# $FreeBSD: stable/9/usr.sbin/crunch/examples/Makefile 139103 2004-12-21 08:47:35Z ru $

CRUNCHED=	fixit

# below is boiler-plate to make $(CRUNCHED) from $(CRUNCHED).conf
# I'd use PROG instead of CRUNCHED, but the system makefiles REALLY want
# to build things in the normal way if you use PROG.

CONF=	$(CRUNCHED).conf

OUTMK=	$(CRUNCHED).mk
OUTPUTS= $(OUTMK) $(CRUNCHED).c $(CRUNCHED).cache

NO_MAN=
CLEANFILES+= $(CRUNCHED) *.o *.lo *.c *.mk *.cache
CLEANDIRFILES+= $(OUTPUTS)

all: $(CRUNCHED)
exe: $(CRUNCHED)

$(OUTPUTS): $(CONF)
	crunchgen ${.CURDIR}/$(CONF)

$(CRUNCHED): $(OUTPUTS) submake

submake:
	make -f $(OUTMK)
objs:
	make -f $(OUTMK) objs
cleandir:
	rm -f $(CLEANDIRFILES)

.include <bsd.prog.mk>
