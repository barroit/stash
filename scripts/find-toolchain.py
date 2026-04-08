#!/usr/bin/python3
# SPDX-License-Identifier: GPL-3.0-or-later

from os import environ
from os.path import realpath
from shutil import which
from subprocess import run
from sys import exit
from textwrap import dedent

CC = environ.get('CC')
LD = environ.get('LD')

toolchains = [
	[ CC,      LD       ],
	[ 'gcc',   'ld.bfd' ],
	[ 'clang', 'ld.lld' ],
	[ 'cc',    'ld'     ],
]

def try_cc(cc):
	__program = which(cc)
	program = realpath(__program)

	if not program:
		return

	cmd = [ cc, '-E', '-P', '-x', 'c', '-' ]
	file = dedent("""\
		#if defined(__clang__)
		Clang	__clang_major__	__clang_minor__	__clang_patchlevel__
		#elif defined(__GNUC__)
		GCC	__GNUC__	__GNUC_MINOR__	__GNUC_PATCHLEVEL__
		#endif
	""")
	res = run(cmd, text=True, input=file, capture_output=True)

	if not res.stdout:
		return

	cols = res.stdout.split()
	name = cols[0]

	if len(cols) < 4 or name != 'GCC' and name != 'Clang':
		return

	major = int(cols[1]) * 1000
	minor = int(cols[2])
	version = major + minor

	if name == 'GCC' and version < 12 * 1000 or \
	   name == 'Clang' and version < 18 * 1000:
		return

	return f"{program}\t{version}\t{name}"

def try_ld(ld):
	__program = which(ld)
	program = realpath(__program)

	if not program:
		return

	cmd = [ ld, '-v' ]
	res = run(cmd, text=True, capture_output=True)

	if not res.stdout:
		return

	cols = res.stdout.split()

	# GNU ld (GNU Binutils for Ubuntu) 2.42
	if cols[0] == 'GNU' and cols[1] == 'ld':
		name = 'BFD'
		version_str = cols[-1]

	# good
	# 	Ubuntu LLD 18.1.3 (compatible with GNU linkers)
	# or
	# 	LLD 18.1.8 (compatible with GNU linkers)
	#
	# bad
	# 	GNU gold (GNU Binutils for Ubuntu 2.42) 1.16
	# or
	# 	Microsoft (R) Incremental Linker Version 14.40.33812.0
	else:
		while len(cols) > 1 and cols[0] != 'LLD':
			cols.pop(0)

		if cols[0] != 'LLD':
			return

		name = 'LLD'
		version_str = cols[1]

	cols = version_str.split('.')
	major = int(cols[0]) * 1000
	minor = int(cols[1])
	version = major + minor

	return f"{program}\t{version}\t{name}"

for [ cc, ld ] in toolchains:
	if not cc or not ld:
		continue

	cc_meta = try_cc(cc)

	if not cc_meta:
		continue

	ld_meta = try_ld(ld)

	if not ld_meta:
		continue

	print(cc_meta)
	print(ld_meta)
	exit()

exit('no available cc and ld found in PATH')
