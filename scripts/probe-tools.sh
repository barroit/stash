#!/bin/sh
# SPDX-License-Identifier: GPL-3.0-or-later

set -e

trap 'rm -f .tmp-$$' EXIT

scripts=$(dirname $0)

while read cc ld; do
	test -n "$cc" && test -n "$ld" || continue

	cc=$($scripts/which.py $cc) || continue
	ld=$($scripts/which.py $ld) || continue

	$scripts/probe-cc.sh $cc >.tmp-$$ || continue
	$scripts/probe-ld.sh $ld >>.tmp-$$ || continue

	cat .tmp-$$
	exit

done <<EOF
$CC	$LD
gcc	ld.bfd
clang	ld64.lld
clang	ld.lld
cc	ld
EOF

exit 1
