#!/bin/sh
# SPDX-License-Identifier: GPL-3.0-or-later

set -e

if [ ! -d sqlite ]; then
	git clone --single-branch https://github.com/sqlite/sqlite.git
	(cd sqlite && git fetch --tags origin master)
fi

cd sqlite

git checkout version-3.52.0
git clean -xdf

mkdir -p build
cd build

../configure --all

make OPTIONS=-DSQLITE_OMIT_DEPRECATED -j sqlite3.c
