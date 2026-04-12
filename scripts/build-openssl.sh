#!/bin/sh
# SPDX-License-Identifier: GPL-3.0-or-later

set -e

cd openssl
git clean -xdf

mkdir -p build
cd build

CFLAGS=-O3 ../Configure --release no-deprecated no-stdio no-sock
make -j build_sw
