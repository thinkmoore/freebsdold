#!/bin/sh
# $FreeBSD: stable/9/tools/regression/lib/libc/stdio/test-open_wmemstream.t 252343 2013-06-28 16:07:20Z jhb $

cd `dirname $0`

executable=`basename $0 .t`

make $executable 2>&1 > /dev/null

exec ./$executable
