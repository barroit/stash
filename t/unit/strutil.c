// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include "strutil.h"
#include "uniassert.h"
#include "unitest.h"

unitest_begin();

unitest_routine(strskip_prefix)
{
	const char s[] = "Hatsune Miku";
	char *res = strskip(s, "Hatsune ");

	uniassert_equal(res, s + 8);
	uniassert_strequal(res, "Miku");
	return 0;
}

unitest_routine(strskip_empty)
{
	const char s[] = "miku";
	char *res = strskip(s, "");

	uniassert_equal(res, s);
	uniassert_strequal(res, "miku");
	return 0;
}

unitest_routine(strskip_mismatch)
{
	const char s[] = "miku";

	uniassert_not(strskip(s, "rin"));
	return 0;
}

unitest_routine(strskip_short)
{
	const char s[] = "mi";

	uniassert_not(strskip(s, "miku"));
	return 0;
}

unitest_routine(strskip2_prefix)
{
	const char s[] = "Hatsune Miku";
	const char *res;
	int err;

	err = strskip2(s, "Hatsune ", &res);

	uniassert_equal_signed(err, 0);
	uniassert_equal(res, s + 8);
	uniassert_strequal(res, "Miku");
	return 0;
}

unitest_routine(strskip2_mismatch)
{
	const char s[] = "miku";
	const char *res = s;
	int err;

	err = strskip2(s, "rin", &res);

	uniassert_equal_signed(err, -1);
	uniassert_equal(res, s);
	return 0;
}

unitest_routine(mbslen_empty)
{
	uniassert_equal(mbslen(""), 0);
	return 0;
}

unitest_routine(mbslen_utf8)
{
	const char s[] = {
		'A',
		'\xc2', '\xa2',
		'\xe3', '\x81', '\xbf',
		'\xf0', '\x9f', '\x98', '\x80',
		0,
	};

	uniassert_equal(mbslen(s), 4);
	return 0;
}

unitest_routine(mbtowc_ascii)
{
	uniassert_equal(mbtowc("A"), 0x41);
	return 0;
}

unitest_routine(mbtowc_2byte)
{
	const char seq[] = { '\xc2', '\xa2', 0 };

	uniassert_equal(mbtowc(seq), 0xa2);
	return 0;
}

unitest_routine(mbtowc_3byte)
{
	const char seq[] = { '\xe3', '\x81', '\xbf', 0 };

	uniassert_equal(mbtowc(seq), 0x307f);
	return 0;
}

unitest_routine(mbtowc_4byte)
{
	const char seq[] = { '\xf0', '\x9f', '\x98', '\x80', 0 };

	uniassert_equal(mbtowc(seq), 0x1f600);
	return 0;
}

unitest_end();
