#!/bin/sh
# $FreeBSD: stable/9/tools/regression/pjdfstest/tests/symlink/01.t 166065 2007-01-17 01:42:12Z pjd $

desc="symlink returns ENOTDIR if a component of the name2 path prefix is not a directory"

dir=`dirname $0`
. ${dir}/../misc.sh

echo "1..5"

n0=`namegen`
n1=`namegen`

expect 0 mkdir ${n0} 0755
expect 0 create ${n0}/${n1} 0644
expect ENOTDIR symlink test ${n0}/${n1}/test
expect 0 unlink ${n0}/${n1}
expect 0 rmdir ${n0}
