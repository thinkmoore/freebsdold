#!/bin/sh
# $FreeBSD: stable/9/tools/regression/pjdfstest/tests/rename/02.t 211178 2010-08-11 16:33:17Z pjd $

desc="rename returns ENAMETOOLONG if an entire length of either path name exceeded {PATH_MAX} characters"

dir=`dirname $0`
. ${dir}/../misc.sh

echo "1..6"

n0=`namegen`
nx=`dirgen_max`
nxx="${nx}x"

mkdir -p "${nx%/*}"

expect 0 create ${n0} 0644
expect 0 rename ${n0} ${nx}
expect 0 rename ${nx} ${n0}
expect ENAMETOOLONG rename ${n0} ${nxx}
expect 0 unlink ${n0}
expect ENAMETOOLONG rename ${nxx} ${n0}

rm -rf "${nx%%/*}"
