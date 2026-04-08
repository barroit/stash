# SPDX-License-Identifier: GPL-3.0-or-later

import os
from os import devnull, environ, getpid, unlink
from os.path import isfile
from platform import machine, system
from subprocess import DEVNULL, run

objtree = environ['OBJTREE']

def head(pathname):
	file = open(pathname, 'r')
	line = file.readline().rstrip()

	file.close()
	return line

def warn_off(kconf, name):
	kconf.warn = False
	return ''

def os_type(kconf, name):
	return os.name

def column(kconf, name, row, at):
	cols = row.split('\t')
	idx = int(at) - 1

	return cols[idx]

def repo_info(kconf, name):
	return head(f"{objtree}/repo.info")

def build_info(kconf, name):
	arch = machine().lower()
	platform = system()

	return f"{arch}\t{platform}"

def cc_info(kconf, name):
	return head(f"{objtree}/cc.info")

def ld_info(kconf, name):
	return head(f"{objtree}/ld.info")

def test_cc_flag(kconf, name, cc, flag):
	pid = getpid()
	tmp = f".tmp-{pid}"

	cmd = [ cc, '-Werror', flag, '-c', '-x', 'c', devnull, '-o', devnull ]
	res = run(cmd, stdout=DEVNULL, stderr=DEVNULL)

	if isfile(tmp):
		unlink(tmp)

	if res.returncode == 0:
		return 'y'
	else:
		return 'n'

def test_ld_flag(kconf, name, ld, flag):
	cmd = [ ld, '-v', flag ]
	res = run(cmd, stdout=DEVNULL, stderr=DEVNULL)

	if res.returncode == 0:
		return 'y'
	else:
		return 'n'

functions = {
	'warn-off': (warn_off, 0, 0),

	'os-type': (os_type, 0, 0),

	'column': (column, 2, 2),

	'repo-info': (repo_info, 0, 0),
	'build-info': (build_info, 0, 0),
	'cc-info': (cc_info, 0, 0),
	'ld-info': (ld_info, 0, 0),

	'test-cc-flag': (test_cc_flag, 2, 2),
	'test-ld-flag': (test_ld_flag, 2, 2),
}
