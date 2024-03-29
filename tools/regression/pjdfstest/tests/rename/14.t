#!/bin/sh
# $FreeBSD: stable/9/tools/regression/pjdfstest/tests/rename/14.t 211186 2010-08-11 17:34:58Z pjd $

desc="rename returns EISDIR when the 'to' argument is a directory, but 'from' is not a directory"

dir=`dirname $0`
. ${dir}/../misc.sh

echo "1..32"

n0=`namegen`
n1=`namegen`

expect 0 mkdir ${n0} 0755

for type in regular fifo block char socket symlink; do
	create_file ${type} ${n1}
	expect EISDIR rename ${n1} ${n0}
	expect dir lstat ${n0} type
	expect ${type} lstat ${n1} type
	expect 0 unlink ${n1}
done

expect 0 rmdir ${n0}
