// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "size.h"
#include "strbuf.h"
#include "xalloc.h"

void sb_destroy(struct strbuf *sb)
{
	free(sb->buf);
}

void sb_reinit(struct strbuf *sb, uint32_t mode)
{
	memset(sb, 0, sizeof(*sb));

	sb->mode = mode;
}

size_t sb_append_ch_at(struct strbuf *sb, size_t pos, char c)
{
	size_t new = pos + 1;

	assert(pos <= sb->len);

	if (new + 1 > sb->cap) {
		if (sb->mode & STRBUF_PREALLOC)
			return 0;
		else
			XREALLOCBUF(sb->buf, new + 1, sb->cap);
	}

	sb->buf[pos] = c;
	sb->buf[pos + 1] = 0;

	sb->len = new;
	return 1;
}

size_t sb_append_str_at(struct strbuf *sb, size_t pos, const char *s)
{
	size_t len = strlen(s);
	size_t new = pos + len;

	assert(pos <= sb->len);

	if (new + 1 > sb->cap) {
		if (sb->mode & STRBUF_PREALLOC)
			return 0;
		else
			XREALLOCBUF(sb->buf, new + 1, sb->cap);
	}

	memcpy(&sb->buf[pos], s, len + 1);

	sb->len = new;
	return len;
}

size_t sb_vappendf_at(struct strbuf *sb,
		      size_t pos, const char *fmt, va_list ap)
{
	va_list cp;
	size_t room;
	int nr;

	assert(pos <= sb->len);
	va_copy(cp, ap);

	if (!(sb->mode & STRBUF_PREALLOC))
		XREALLOCBUF(sb->buf, sb->len + 39 * 6 + 1, sb->cap);

	room = sb->cap - (pos + 1);
	nr = vsnprintf(&sb->buf[pos], room + 1, fmt, ap);
	assert(nr >= 0);

	if (nr <= room)
		goto out;

	if (sb->mode & STRBUF_PREALLOC) {
		nr = room;
		goto out;
	}

	XREALLOCBUF(sb->buf, pos + nr + 1, sb->cap);

	room = sb->cap - (pos + 1);
	nr = vsnprintf(&sb->buf[pos], room + 1, fmt, cp);
	assert(nr >= 0);

out:
	sb->len = pos + nr;
	va_end(cp);
	return nr;
}

size_t sb_appendf_at(struct strbuf *sb, size_t pos, const char *fmt, ...)
{
	va_list ap;
	size_t nr;

	va_start(ap, fmt);
	nr = sb_vappendf_at(sb, pos, fmt, ap);

	va_end(ap);
	return nr;
}
