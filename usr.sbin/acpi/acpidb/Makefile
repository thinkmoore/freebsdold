# $FreeBSD: stable/9/usr.sbin/acpi/acpidb/Makefile 220663 2011-04-15 18:34:27Z jkim $

PROG=	acpidb
SRCS=	acpidb.c
SRCS+=	osunixxf.c

# debugger
SRCS+=	dbcmds.c dbdisply.c dbexec.c dbfileio.c dbhistry.c	\
	dbinput.c dbmethod.c dbnames.c dbstats.c dbutils.c	\
	dbxface.c

# disassembler
SRCS+=	dmbuffer.c dmnames.c dmobject.c dmopcode.c dmresrc.c	\
	dmresrcl.c dmresrcs.c dmutils.c dmwalk.c

# events
SRCS+=	evevent.c evglock.c evgpe.c evgpeblk.c evgpeinit.c	\
	evgpeutil.c evmisc.c evregion.c evrgnini.c evsci.c	\
	evxface.c evxfevnt.c evxfgpe.c evxfregn.c

# hardware
SRCS+=	hwacpi.c hwgpe.c hwpci.c hwregs.c hwsleep.c hwvalid.c	\
	hwxface.c

# interpreter/dispatcher
SRCS+=	dsargs.c dscontrol.c dsfield.c dsinit.c dsmethod.c	\
	dsmthdat.c dsobject.c dsopcode.c dsutils.c dswexec.c	\
	dswload.c dswload2.c dswscope.c dswstate.c

# interpreter/executer
SRCS+=	exconfig.c exconvrt.c excreate.c exdebug.c exdump.c	\
	exfield.c exfldio.c exmisc.c exmutex.c exnames.c	\
	exoparg1.c exoparg2.c exoparg3.c exoparg6.c exprep.c	\
	exregion.c exresnte.c exresolv.c exresop.c exstore.c	\
	exstoren.c exstorob.c exsystem.c exutils.c

# interpreter/parser
SRCS+=	psargs.c psloop.c psopcode.c psparse.c psscope.c	\
	pstree.c psutils.c pswalk.c psxface.c

# namespace
SRCS+=	nsaccess.c nsalloc.c nsdump.c nseval.c nsinit.c		\
	nsload.c nsnames.c nsobject.c nsparse.c nspredef.c	\
	nsrepair.c nsrepair2.c nssearch.c nsutils.c nswalk.c	\
	nsxfeval.c nsxfname.c nsxfobj.c

# resources
SRCS+=	rsaddr.c rscalc.c rscreate.c rsdump.c rsinfo.c		\
	rsio.c rsirq.c rslist.c rsmemory.c rsmisc.c		\
	rsutils.c rsxface.c

# tables
SRCS+=	tbfadt.c tbfind.c tbinstal.c tbutils.c tbxface.c	\
	tbxfroot.c

# utilities
SRCS+=	utalloc.c utcache.c utcopy.c utdebug.c utdecode.c	\
	utdelete.c uteval.c utglobal.c utids.c utinit.c		\
	utlock.c utmath.c utmisc.c utmutex.c utobject.c utosi.c	\
	utresrc.c utstate.c uttrack.c utxface.c utxferror.c

MAN=	acpidb.8
WARNS?=	2

CFLAGS+= -DACPI_EXEC_APP -fno-strict-aliasing
DPADD=	${LIBPTHREAD}
LDADD=	-lpthread

.include <bsd.prog.mk>
