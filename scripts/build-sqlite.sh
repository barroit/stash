#!/bin/sh
# SPDX-License-Identifier: GPL-3.0-or-later

set -e

cd sqlite
git clean -xdf

mkdir -p build
cd build

../configure --all

make OPTIONS=-DSQLITE_OMIT_DEPRECATED -j sqlite3.c
