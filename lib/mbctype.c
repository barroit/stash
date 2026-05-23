// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2024 Jiamu Sun <barroit@linux.com>
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include "mbctype.h"

unsigned int _mbctype[] = {
	[0x00 ... 0x7f] = _9A,
	[0x80 ... 0xbf] = _9CB,
	[0xc0 ... 0xdf] = _9B,
	[0xe0 ... 0xef] = _9C,
	[0xf0 ... 0xf7] = _9D,
	[0xf8 ... 0xff] = -1,
};
