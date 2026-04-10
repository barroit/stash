#!/bin/sh
# SPDX-License-Identifier: GPL-3.0-or-later

set -e

trap 'rm -f .tmp-$$' EXIT

cat <<-EOF >.tmp-$$
	C:/Program Files (x86)/Microsoft Visual Studio/2022/BuildTools
	C:/Program Files/Microsoft Visual Studio/2022/Community
	C:/Program Files/Microsoft Visual Studio/2022/Professional
EOF

while read prefix; do
	vcvarsall="$prefix/VC/Auxiliary/Build/vcvarsall.bat"

	if [ -f "$vcvarsall" ]; then
		printf '%s\n' "$vcvarsall"
		exit
	fi
done <.tmp-$$

exec >&2

printf 'vcvarsall.bat not found in any of:\n'

while read prefix; do
	printf '\t%s\n' "$prefix/VC/Auxiliary/Build"
done <.tmp-$$

exit 1
