#!/bin/sh
# $FreeBSD: stable/9/tools/regression/pjdfstest/tests/rmdir/02.t 211178 2010-08-11 16:33:17Z pjd $

desc="rmdir returns ENAMETOOLONG if a component of a pathname exceeded {NAME_MAX} characters"

dir=`dirname $0`
. ${dir}/../misc.sh

echo "1..4"

nx=`namegen_max`
nxx="${nx}x"

expect 0 mkdir ${nx} 0755
expect 0 rmdir ${nx}
expect ENOENT rmdir ${nx}
expect ENAMETOOLONG rmdir ${nxx}
