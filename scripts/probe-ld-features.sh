#!/bin/sh
# SPDX-License-Identifier: GPL-3.0-or-later

set -e

ld=$1

probe_feature()
{
	read name
	read flags

	$ld -v $flags >/dev/null 2>&1 && \
	printf '%s=y\n' $name || true
}

probe_feature <<'EOF' &
LD_HAS_COMPRESS_DEBUG_SECTIONS_ZLIB
--compress-debug-sections=zlib
EOF

probe_feature <<'EOF' &
LD_HAS_COMPRESS_DEBUG_SECTIONS_ZSTD
--compress-debug-sections=zstd
EOF

wait
