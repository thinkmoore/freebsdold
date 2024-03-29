#!/bin/sh
# $FreeBSD: stable/9/tools/regression/pjdfstest/tests/symlink/03.t 211178 2010-08-11 16:33:17Z pjd $

desc="symlink returns ENAMETOOLONG if an entire length of either path name exceeded {PATH_MAX} characters"

dir=`dirname $0`
. ${dir}/../misc.sh

echo "1..6"

n0=`namegen`
nx=`dirgen_max`
nxx="${nx}x"

mkdir -p "${nx%/*}"
expect 0 symlink ${nx} ${n0}
expect 0 unlink ${n0}
expect 0 symlink ${n0} ${nx}
expect 0 unlink ${nx}
expect ENAMETOOLONG symlink ${n0} ${nxx}
expect ENAMETOOLONG symlink ${nxx} ${n0}
rm -rf "${nx%%/*}"
