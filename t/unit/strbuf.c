// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include "strbuf.h"
#include "err.h"

unitest_begin();

unitest_routine(append)
{
	struct strbuf __cleanup(sb_destroy) sb = STRBUF_INIT;

	sb_append_str_at(&sb, sb.len, "test");
	sb_append_str_at(&sb, sb.len, "test");

	die("?%s", sb.buf);
}

unitest_end();
