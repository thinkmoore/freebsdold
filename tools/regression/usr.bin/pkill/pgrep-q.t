#!/bin/sh
# $FreeBSD: stable/9/tools/regression/usr.bin/pkill/pgrep-q.t 203802 2010-02-12 18:52:24Z pjd $

base=`basename $0`

echo "1..4"

name="pgrep -q"
sleep0=`mktemp /tmp/$base.XXXXXX` || exit 1
sleep1=`mktemp /tmp/$base.XXXXXX` || exit 1
ln -sf /bin/sleep $sleep0
$sleep0 5 &
sleep 0.3
pid=$!
out="`pgrep -q -f $sleep0 2>&1`"
if [ $? -eq 0 ]; then
	echo "ok 1 - $name"
else
	echo "not ok 1 - $name"
fi
if [ -z "${out}" ]; then
	echo "ok 2 - $name"
else
	echo "not ok 2 - $name"
fi
out="`pgrep -q -f $sleep1 2>&1`"
if [ $? -ne 0 ]; then
	echo "ok 3 - $name"
else
	echo "not ok 3 - $name"
fi
if [ -z "${out}" ]; then
	echo "ok 4 - $name"
else
	echo "not ok 4 - $name"
fi
kill $pid
rm -f $sleep0 $sleep1
