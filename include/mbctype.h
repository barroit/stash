/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright 2024, 2025 Jiamu Sun <barroit@linux.com>
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#ifndef MBTYPE_H
#define MBTYPE_H

extern unsigned int _mbctype[];

enum mbctype {
	_9CB,  /* continuation bytes */
	_9A,   /* 1-byte */
	_9B,   /* 2-byte */
	_9C,   /* 3-byte */
	_9D,   /* 4-byte */
};

#define __ismbctype(c, t) (__mbctype(c) == t)
#define __mbctype(c) _mbctype[(unsigned int)c]

#define ismb1(c)  __ismbctype(c, _9A)
#define ismb2(c)  __ismbctype(c, _9B)
#define ismb3(c)  __ismbctype(c, _9C)
#define ismb4(c)  __ismbctype(c, _9D)
#define ismbcb(c) __ismbctype(c, _9CB)

#endif /* MBTYPE_H */
