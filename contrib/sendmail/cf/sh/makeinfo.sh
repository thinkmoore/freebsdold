#!/bin/sh
#
# Copyright (c) 1998, 1999 Sendmail, Inc. and its suppliers.
#	All rights reserved.
# Copyright (c) 1983 Eric P. Allman.  All rights reserved.
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
#
# By using this file, you agree to the terms and conditions set
# forth in the LICENSE file which can be found at the top level of
# the sendmail distribution.
#
#
#	$Id: makeinfo.sh,v 8.14 1999/02/07 07:26:25 gshapiro Exp $
#
# $FreeBSD: stable/9/contrib/sendmail/cf/sh/makeinfo.sh 195626 2009-07-11 22:30:37Z cperciva $
#

usewhoami=0
usehostname=0
for p in `echo $PATH | sed 's/:/ /g'`
do
	if [ "x$p" = "x" ]
	then
		p="."
	fi
	if [ -f $p/whoami ]
	then
		usewhoami=1
		if [ $usehostname -ne 0 ]
		then
			break;
		fi
	fi
	if [ -f $p/hostname ]
	then
		usehostname=1
		if [ $usewhoami -ne 0 ]
		then
			break;
		fi
	fi
done
if [ $usewhoami -ne 0 ]
then
	user=`whoami`
else
	user=$LOGNAME
fi

if [ $usehostname -ne 0 ]
then
	host=`hostname`
else
	host=`uname -n`
fi
echo '#####' built by $user@$host
echo '#####' in `pwd` | sed 's/\/tmp_mnt//'
echo '#####' using $1 as configuration include directory | sed 's/\/tmp_mnt//'
echo "define(\`__HOST__', $host)dnl"
