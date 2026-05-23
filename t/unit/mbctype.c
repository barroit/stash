// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include "mbctype.h"
#include "uniassert.h"
#include "unitest.h"

unitest_begin();

unitest_routine(ismb1)
{
	unsigned int c;

	for (c = 0x00; c <= 0x7f; c++) {
		uniassert_is(ismb1(c));
		uniassert_not(ismbcb(c));
		uniassert_not(ismb2(c));
		uniassert_not(ismb3(c));
		uniassert_not(ismb4(c));
	}

	return 0;
}

unitest_routine(ismbcb)
{
	unsigned int c;

	for (c = 0x80; c <= 0xbf; c++) {
		uniassert_not(ismb1(c));
		uniassert_is(ismbcb(c));
		uniassert_not(ismb2(c));
		uniassert_not(ismb3(c));
		uniassert_not(ismb4(c));
	}

	return 0;
}

unitest_routine(ismb2)
{
	unsigned int c;

	for (c = 0xc0; c <= 0xdf; c++) {
		uniassert_not(ismb1(c));
		uniassert_not(ismbcb(c));
		uniassert_is(ismb2(c));
		uniassert_not(ismb3(c));
		uniassert_not(ismb4(c));
	}

	return 0;
}

unitest_routine(ismb3)
{
	unsigned int c;

	for (c = 0xe0; c <= 0xef; c++) {
		uniassert_not(ismb1(c));
		uniassert_not(ismbcb(c));
		uniassert_not(ismb2(c));
		uniassert_is(ismb3(c));
		uniassert_not(ismb4(c));
	}

	return 0;
}

unitest_routine(ismb4)
{
	unsigned int c;

	for (c = 0xf0; c <= 0xf7; c++) {
		uniassert_not(ismb1(c));
		uniassert_not(ismbcb(c));
		uniassert_not(ismb2(c));
		uniassert_not(ismb3(c));
		uniassert_is(ismb4(c));
	}

	return 0;
}

unitest_routine(ismb_invalid)
{
	unsigned int c;

	for (c = 0xf8; c <= 0xff; c++) {
		uniassert_not(ismb1(c));
		uniassert_not(ismbcb(c));
		uniassert_not(ismb2(c));
		uniassert_not(ismb3(c));
		uniassert_not(ismb4(c));
	}

	return 0;
}

unitest_end();
