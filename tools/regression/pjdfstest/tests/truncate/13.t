#!/bin/sh
# $FreeBSD: stable/9/tools/regression/pjdfstest/tests/truncate/13.t 185227 2008-11-23 20:07:00Z pjd $

desc="truncate returns EINVAL if the length argument was less than 0"

dir=`dirname $0`
. ${dir}/../misc.sh

echo "1..4"

n0=`namegen`

expect 0 create ${n0} 0644
expect EINVAL -- truncate ${n0} -1
expect EINVAL -- truncate ${n0} -999999
expect 0 unlink ${n0}
