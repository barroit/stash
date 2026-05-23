// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include "mbctype.h"
#include "strutil.h"

char *strskip(const char *s1, const char *s2)
{
	do {
		if (!s2[0])
			return (char *)s1;
	} while (*s1++ == *s2++);

	return NULL;
}

int strskip2(const char *s1, const char *s2, const char **__res)
{
	const char *res = strskip(s1, s2);

	if (res == NULL)
		return -1;

	*__res = res;
	return 0;
}

size_t mbslen(const char *s)
{
	size_t len = 0;

	while (*s) {
		s += __mbctype(*s);
		len++;
	}

	return len;
}

wchar_t mbtowc(const char *seq)
{
	unsigned int shift = 6;
	unsigned int mask = 0x1f;
	wchar_t res = 0;
	unsigned int len = __mbctype(*seq);

	switch (len) {
	case _9D:
		res |= seq[3] & 0x3f;
		shift += 6;
		mask >>= 1;
	case _9C:
		res |= (seq[2] & 0x3f) << (shift - 6);
		shift += 6;
		mask >>= 1;
	case _9B:
		res |= ((seq[0] & mask) << shift) |
		       ((seq[1] & 0x3f) << (shift - 6));
		break;
	default:
		res = seq[0];
	}

	return res;
}
