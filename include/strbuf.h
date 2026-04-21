/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#ifndef STRBUF_H
#define STRBUF_H

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#include "attr.h"

#define STRBUF_ALLOC    (1 << 0)
#define STRBUF_PREALLOC (1 << 1)

struct strbuf {
	char *buf;
	size_t len;
	size_t cap;
	uint32_t mode;
};

#define STRBUF_INIT { .buf = NULL, .len = 0, .cap = 0, .mode = STRBUF_ALLOC }
#define STRBUF_INIT_PREALLOC(__buf, __cap) \
	{ .buf = __buf, .len = 0, .cap = __cap, .mode = STRBUF_PREALLOC }

void sb_destroy(struct strbuf *sb);

void sb_reinit(struct strbuf *sb, uint32_t mode);

#define sb_write_ch(sb, c) sb_write_ch_at(sb, (sb)->len, c)

#define sb_write_str(sb, s) sb_write_str_at(sb, (sb)->len, s)

#define sb_vwritef(sb, fmt, ap) sb_vwritef_at(sb, (sb)->len, fmt, ap)

#define sb_writef(sb, fmt, ...) sb_vwritef_at(sb, (sb)->len, fmt, ##__VA_ARGS__)

size_t sb_write_ch_at(struct strbuf *sb, size_t pos, char c);

size_t sb_write_str_at(struct strbuf *sb, size_t pos, const char *s);

size_t sb_vwritef_at(struct strbuf *sb,
		     size_t pos, const char *fmt, va_list ap);

size_t sb_writef_at(struct strbuf *sb,
		    size_t pos, const char *fmt, ...) __printf(3, 4);

#endif /* STRBUF_H */
