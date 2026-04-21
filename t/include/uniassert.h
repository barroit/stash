/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#ifndef UNIASSERT_H
#define UNIASSERT_H

#include <stdio.h>
#include <string.h>

#define uniassert_ok_or_ret(ok)						\
do {									\
	if (!(ok)) {							\
		fprintf(stderr,						\
			"uniassert:%s:%d:%s: assert %s failed\n",	\
			__FILE__, __LINE__, __func__, #ok);		\
		return 1;						\
	}								\
} while (0)

#define uniassert_strequal(a, b) uniassert_ok_or_ret(!strcmp((a), (b)))
#define uniassert_equal(a, b) uniassert_ok_or_ret((a) == (b))

#define uniassert_is(x) uniassert_ok_or_ret(x)
#define uniassert_not(x) uniassert_ok_or_ret(!(x))

#define uniassert_ok(err) uniassert_not(err)
#define uniassert_no(err) uniassert_is(err)

#endif /* UNIASSERT_H */
