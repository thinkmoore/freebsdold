#!/bin/sh
# $FreeBSD: stable/9/tools/regression/pjdfstest/tests/link/02.t 211178 2010-08-11 16:33:17Z pjd $

desc="link returns ENAMETOOLONG if a component of either pathname exceeded {NAME_MAX} characters"

dir=`dirname $0`
. ${dir}/../misc.sh

echo "1..10"

n0=`namegen`
nx=`namegen_max`
nxx="${nx}x"

expect 0 create ${nx} 0644
expect 0 link ${nx} ${n0}
expect 0 unlink ${nx}
expect 0 link ${n0} ${nx}
expect 0 unlink ${n0}
expect 0 unlink ${nx}

expect 0 create ${n0} 0644
expect ENAMETOOLONG link ${n0} ${nxx}
expect 0 unlink ${n0}
expect ENAMETOOLONG link ${nxx} ${n0}
