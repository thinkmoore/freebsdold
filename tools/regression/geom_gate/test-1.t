#!/bin/sh
# $FreeBSD: stable/9/tools/regression/geom_gate/test-1.t 137587 2004-11-11 19:47:55Z nik $

base=`basename $0`
us=45
work="/dev/md${us}"
src="/dev/md`expr $us + 1`"
conf=`mktemp /tmp/$base.XXXXXX` || exit 1

mdconfig -a -t malloc -s 1M -u $us || exit 1
mdconfig -a -t malloc -s 1M -u `expr $us + 1` || exit 1
dd if=/dev/random of=$work bs=1m count=1 >/dev/null 2>&1
dd if=/dev/random of=$src bs=1m count=1 >/dev/null 2>&1
sum=`cat $src | md5 -q`

echo "127.0.0.1 RW $work" > $conf
ggated $conf
ggatec create -u $us 127.0.0.1 $work

dd if=${src} of=/dev/ggate${us} bs=1m count=1 >/dev/null 2>&1

echo '1..2'

if [ `cat $work | md5 -q` != $sum ]; then
	echo 'not ok 1 - md5 checksum'
else
	echo 'ok 1 - md5 checksum'

	if [ `cat /dev/ggate${us} | md5 -q` != $sum ]; then
		echo 'not ok 2 - md5 checksum'
	else
		echo 'ok 2 - md5 checksum'
	fi
fi

ggatec destroy -u $us
mdconfig -d -u $us
mdconfig -d -u `expr $us + 1`
pkill ggated $conf
rm -f $conf
