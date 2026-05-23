/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#ifndef STRUTIL_H
#define STRUTIL_H

#include <stddef.h>

char *strskip(const char *s1, const char *s2);

int strskip2(const char *s1, const char *s2, const char **res);

size_t mbslen(const char *s);

wchar_t mbtowc(const char *seq);

#endif /* STRUTIL_H */
