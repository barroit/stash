#!/bin/sh
# SPDX-License-Identifier: GPL-3.0-or-later

if [ ! -d openssl ]; then
	git clone --single-branch https://github.com/openssl/openssl.git
	git fetch --tags origin master
fi

cd openssl

git checkout openssl-3.6.2
git clean -xdf

mkdir -p build
cd build

../Configure --release no-deprecated no-stdio no-sock
make -j build_sw
