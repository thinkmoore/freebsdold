# $FreeBSD: stable/9/tools/regression/usr.bin/comm/regress.sh 200442 2009-12-12 18:18:46Z jh $

LC_ALL=C; export LC_ALL

echo 1..3

REGRESSION_START($1)

REGRESSION_TEST(`00', `comm -12 regress.00a.in regress.00b.in')
REGRESSION_TEST(`01', `comm -12 regress.01a.in regress.01b.in')
REGRESSION_TEST(`02', `comm regress.02a.in regress.02b.in')

REGRESSION_END()
