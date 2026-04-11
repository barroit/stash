#!/bin/sh
# SPDX-License-Identifier: GPL-3.0-or-later

set -e

read cc

probe_feature()
{
	read name
	read flag

	cat | $cc $flag -Werror -S -x c -o /dev/null - 2>/dev/null && \
	printf '%s=y\n' $name || true
}

cat <<'EOF' | probe_feature &
CC_HAS_BUILTIN_ALIGN_UP

int x = __builtin_align_up(8, 4);
EOF

cat <<'EOF' | probe_feature &
CC_HAS_BUILTIN_ALIGN_DOWN

int x = __builtin_align_down(8, 4);
EOF

cat <<'EOF' | probe_feature &
CC_HAS_REALLOCARRAY
-D_GNU_SOURCE

#include <stdlib.h>

static void a(void)
{
	char *p = reallocarray(NULL, sizeof(*p), 5);

	if (p);
}
EOF

cat <<'EOF' | probe_feature &
CC_HAS_SSIZE_T
-D_GNU_SOURCE

#include <sys/types.h>

ssize_t a = 0;
EOF

cat <<'EOF' | probe_feature &
CC_HAS_TOPLEVEL_REORDER
-ftoplevel-reorder
EOF

cat <<'EOF' | probe_feature &
__unix__

/*
 * Only macOS lacks this.
 */
#ifdef __APPLE__
#  error not on macos
#endif
EOF

wait
