#!/bin/sh
# SPDX-License-Identifier: GPL-3.0-or-later

set -e

if [ -d jom ]; then
	exit
fi

mkdir jom
cd jom

curl -L -o jom.zip http://download.qt.io/official_releases/jom/jom.zip
unzip jom.zip
