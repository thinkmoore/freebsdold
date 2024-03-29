#!/bin/sh
# $FreeBSD: stable/9/tools/regression/pjdfstest/tests/open/22.t 211186 2010-08-11 17:34:58Z pjd $

desc="open returns EEXIST when O_CREAT and O_EXCL were specified and the file exists"

dir=`dirname $0`
. ${dir}/../misc.sh

echo "1..21"

n0=`namegen`

for type in regular dir fifo block char socket symlink; do
	create_file ${type} ${n0}
	expect EEXIST open ${n0} O_CREAT,O_EXCL 0644
	if [ "${type}" = "dir" ]; then
		expect 0 rmdir ${n0}
	else
		expect 0 unlink ${n0}
	fi
done
