#!/bin/sh
# $FreeBSD: stable/9/tools/regression/usr.bin/pkill/pkill-_g.t 199141 2009-11-10 14:32:09Z jhb $

base=`basename $0`

echo "1..2"

name="pkill -G <gid>"
rgid=`id -gr`
sleep=`mktemp /tmp/$base.XXXXXX` || exit 1
ln -sf /bin/sleep $sleep
$sleep 5 &
sleep 0.3
pkill -f -G $rgid $sleep
ec=$?
case $ec in
0)
	echo "ok 1 - $name"
	;;
*)
	echo "not ok 1 - $name"
	;;
esac
rm -f $sleep

name="pkill -G <group>"
rgid=`id -grn`
sleep=`mktemp /tmp/$base.XXXXXX` || exit 1
ln -sf /bin/sleep $sleep
$sleep 5 &
sleep 0.3
pkill -f -G $rgid $sleep
ec=$?
case $ec in
0)
	echo "ok 2 - $name"
	;;
*)
	echo "not ok 2 - $name"
	;;
esac
rm -f $sleep
