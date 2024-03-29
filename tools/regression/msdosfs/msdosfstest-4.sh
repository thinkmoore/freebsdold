#!/bin/sh
# $FreeBSD: stable/9/tools/regression/msdosfs/msdosfstest-4.sh 148117 2005-07-18 12:15:24Z imura $
# A really simple script to create a swap-backed msdosfs filesystem, then
# test to see if msdosfs_conv.c rev 1.45[1] works properly.

mkdir /tmp/msdosfstest
mdconfig -a -t swap -s 128m -u 10
bsdlabel -w md10 auto
newfs_msdos -F 16 -b 8192 /dev/md10a
mount_msdosfs -L uk_UA.KOI8-U -D CP866 -l /dev/md10a /tmp/msdosfstest
# mkdir /tmp/msdosfstest/U+0456 (CYRILLIC SMALL LETTER BYELORUSSIAN-UKRAINIAN I)
mkdir /tmp/msdosfstest/�
if [ $? -eq 0 ]; then
	echo "ok 4 (pass stage 1/3)"
	# cd /tmp/msdosfstest/U+0456 (CYRILLIC SMALL LETTER BYELORUSSIAN-UKRAINIAN I)
	cd /tmp/msdosfstest/�
	if [ $? -eq 0 ]; then
		echo "ok 4 (pass stage 2/3)"
		cd /tmp
		umount /tmp/msdosfstest
		mount_msdosfs -L uk_UA.KOI8-U -D CP866 -s /dev/md10a /tmp/msdosfstest
		cd /tmp/msdosfstest/_~1
		if [ $? -eq 0 ]; then
			echo "ok 4 (pass stage 3/3)"
		else
			echo "not ok 4"
		fi
	else
		echo "not ok 4"
	fi
else
	echo "not ok 4"
fi
cd /tmp
umount /tmp/msdosfstest
mdconfig -d -u 10
rmdir /tmp/msdosfstest
