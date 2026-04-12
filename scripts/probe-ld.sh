#!/bin/sh
# SPDX-License-Identifier: GPL-3.0-or-later

set -e

ld=$1
cc=$2
id=$(printf $ld | sed 's,.\+/ld\.\([^/.]\+\).*,\1,')

trap 'rm -f .tmp-$$*' EXIT

$cc -x c -c -o .tmp-$$.o - <<EOF
int main() { return 0; }
EOF

$cc --ld-path=$ld -fuse-ld=$id -Wl,-v \
    -o .tmp-$$.bin .tmp-$$.o >.tmp-$$.out 2>&1 ||
$cc -B$(dirname $ld) -fuse-ld=$id -Wl,-v \
    -o .tmp-$$.bin .tmp-$$.o >.tmp-$$.out 2>/dev/null ||
exit 1

head -1 .tmp-$$.out >.tmp-$$
test -s .tmp-$$ || exit 1

read c1 c2 c3 _ <.tmp-$$

if [ $c1 = GNU ] && [ $c2 = ld ]; then
	# GNU ld (GNU Binutils for Ubuntu) 2.42
	name=BFD
	id=bfd
	version_str=$(awk '{ print $NF }' .tmp-$$)

elif [ $c1 = LLD ] || [ $c2 = LLD ]; then
	# Ubuntu LLD 18.1.3 (compatible with GNU linkers)
	# LLD 18.1.8 (compatible with GNU linkers)
	# Homebrew LLD 22.1.2
	name=LLD
	id=lld
	test $c1 = LLD && version_str=$c2 || version_str=$c3

else
	# GNU gold (GNU Binutils for Ubuntu 2.42) 1.16
	# Microsoft (R) Incremental Linker Version 14.40.33812.0
	exit 1
fi

IFS=. read major minor _ <<EOF
$version_str
EOF

version=$(( $major * 1000 + $minor ))

printf '%s\t%s\t%s\t%s\n' $ld $id $version $name
