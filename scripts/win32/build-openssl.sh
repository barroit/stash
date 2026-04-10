#!/bin/sh
# SPDX-License-Identifier: GPL-3.0-or-later

set -e

if [ ! -d openssl ]; then
	git clone --single-branch https://github.com/openssl/openssl.git
	(cd openssl && git fetch --tags origin master)
fi

cd openssl

git checkout openssl-3.6.2
git clean -xdf

mkdir -p build
cd build

vcvarsall=$(../../scripts/nt/find-vcvarsall.sh)
jom=../../jom/jom.exe

export PATH=/c/Strawberry/perl/bin/:$PATH
export MSYS2_ARG_CONV_EXCL='CFLAGS'

trap 'rm -f .tmp-$$' EXIT

cat <<EOF >>.tmp-$$
"$vcvarsall" amd64 && "$jom" -j$(nproc) build_sw
EOF

perl ../Configure CFLAGS='/FS /O2' no-deprecated no-stdio no-sock
cmd <.tmp-$$
