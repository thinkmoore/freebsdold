#!/bin/sh
# $FreeBSD: stable/9/tools/regression/pjdfstest/tests/chflags/03.t 211178 2010-08-11 16:33:17Z pjd $

desc="chflags returns ENAMETOOLONG if an entire path name exceeded {PATH_MAX} characters"

dir=`dirname $0`
. ${dir}/../misc.sh

require chflags

echo "1..12"

nx=`dirgen_max`
nxx="${nx}x"

mkdir -p "${nx%/*}"

expect 0 create ${nx} 0644
expect 0 chflags ${nx} SF_IMMUTABLE
expect SF_IMMUTABLE stat ${nx} flags
expect 0 chflags ${nx} none
expect 0 unlink ${nx}
expect ENAMETOOLONG chflags ${nxx} SF_IMMUTABLE

expect 0 create ${nx} 0644
expect 0 lchflags ${nx} SF_IMMUTABLE
expect SF_IMMUTABLE stat ${nx} flags
expect 0 lchflags ${nx} none
expect 0 unlink ${nx}
expect ENAMETOOLONG lchflags ${nxx} SF_IMMUTABLE

rm -rf "${nx%%/*}"
