#!/bin/sh
# $FreeBSD: stable/9/tools/regression/pjdfstest/tests/open/23.t 210954 2010-08-06 19:19:14Z pjd $

desc="open may return EINVAL when an attempt was made to open a descriptor with an illegal combination of O_RDONLY, O_WRONLY, and O_RDWR"

dir=`dirname $0`
. ${dir}/../misc.sh

echo "1..5"

n0=`namegen`

expect 0 create ${n0} 0644
expect "0|EINVAL" open ${n0} O_RDONLY,O_RDWR
expect "0|EINVAL" open ${n0} O_WRONLY,O_RDWR
expect "0|EINVAL" open ${n0} O_RDONLY,O_WRONLY,O_RDWR
expect 0 unlink ${n0}
