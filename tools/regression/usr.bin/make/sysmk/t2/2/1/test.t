#!/bin/sh

# $FreeBSD: stable/9/tools/regression/usr.bin/make/sysmk/t2/2/1/test.t 201526 2010-01-04 18:57:22Z obrien $

cd `dirname $0`
. ../../../../common.sh

# Description
DESC="Can we traverse up to / and find a 'mk/sys.mk' with -m -C?"

# Run
TEST_N=1
TEST_1="-m .../mk -C ../../../t0/2/1"
TEST_MAKE_DIRS="../../mk 755 ../../../t0/mk 755 ../../../t0/2/1 755"
TEST_COPY_FILES="../../mk/sys.mk 644 ../../../t0/mk/sys.mk 644 ../../../t0/2/1/Makefile 644"
TEST_CLEAN_FILES="../../../t0/2/1"
TEST_CLEANUP=clean-special

eval_cmd $*
