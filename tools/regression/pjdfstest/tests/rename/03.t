#!/bin/sh
# $FreeBSD: stable/9/tools/regression/pjdfstest/tests/rename/03.t 166065 2007-01-17 01:42:12Z pjd $

desc="rename returns ENOENT if a component of the 'from' path does not exist, or a path prefix of 'to' does not exist"

dir=`dirname $0`
. ${dir}/../misc.sh

echo "1..6"

n0=`namegen`
n1=`namegen`
n2=`namegen`

expect 0 mkdir ${n0} 0755
expect ENOENT rename ${n0}/${n1}/test ${n2}
expect 0 create ${n2} 0644
expect ENOENT rename ${n2} ${n0}/${n1}/test
expect 0 unlink ${n2}
expect 0 rmdir ${n0}
