#!/bin/sh
# $FreeBSD: stable/9/tools/regression/lib/msun/test-next.t 143231 2005-03-07 05:03:46Z das $

cd `dirname $0`

executable=`basename $0 .t`

make $executable 2>&1 > /dev/null

exec ./$executable
