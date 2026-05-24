// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include <stdlib.h>
#include <locale.h>

#include "err.h"
#include "foreach.h"
#include "unicode.h"

unsigned int _uc_mbctype[] = {
	[0x00 ... 0x7f] = _9A,
	[0x80 ... 0xbf] = _9CB,
	[0xc0 ... 0xdf] = _9B,
	[0xe0 ... 0xef] = _9C,
	[0xf0 ... 0xf7] = _9D,
	[0xf8 ... 0xff] = -1,
};

static int try_c_locales(void)
{
	unsigned int idx;
	const char *cands[] = {
		"C.UTF-8",
		"C.UTF8",
		"C.utf-8",
		"C.utf8",
	};

	foreach_idx(idx, sizeof_array(cands)) {
		if (setlocale(LC_CTYPE, cands[idx]))
			return 0;
	}

	return 1;
}

void uc_force_utf8_ctype(void)
{
	const char *ctype = getenv("LC_CTYPE");

	if (ctype) {
		if (!setlocale(LC_CTYPE, ctype))
			warn("invalid 'LC_CTYPE' found in env");
		else
			return;
	}

	if (setlocale(LC_CTYPE, CONFIG_UTF8_LOCALE))
		return;

	if (!try_c_locales())
		return;

	__die("either install one, or specify a valid one via LC_CTYPE",
	      "can't set locale to UTF-8");
}

size_t uc_mbslen(const char *s)
{
	size_t len = 0;

	while (*s) {
		s += uc_mbctype(*s);
		len++;
	}

	return len;
}

wchar_t uc_mbtowc(const char *seq)
{
	unsigned int shift = 6;
	unsigned int mask = 0x1f;
	wchar_t res = 0;
	unsigned int len = uc_mbctype(*seq);

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
