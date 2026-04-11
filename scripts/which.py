#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later

from shutil import which
from sys import argv, exit

path = which(argv[1])

if not path:
	exit(1)

path = path.encode('unicode_escape').decode()

print(path)
