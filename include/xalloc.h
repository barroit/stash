/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#ifndef XALLOC_H
#define XALLOC_H

#include "attr.h"
#include "calc.h"
#include "compiler.h"

#define xmalloc(size) __xmalloc(__FILE__, __LINE__, __func__, size)
#define xreallocarray(ptr, nmemb, size) \
	__xreallocarray(__FILE__, __LINE__, __func__, ptr, nmemb, size)

void *__xmalloc(const char *file, int line, const char *func, size_t size);

void *__xreallocarray(const char *file, int line, const char *func,
		      void *ptr, size_t nmemb, size_t size);

#define XREALLOCBUF(x, new, cap)			\
do {							\
	if (assert_diff_type(*(x), void));		\
	if (assert_diff_type(*(x), void *));		\
	cap = next_buf_size(cap);			\
	if (cap < (new))				\
		cap = next_buf_size(new);		\
	x = xreallocarray(x, sizeof(*(x)), cap);	\
} while (0)

#endif /* XALLOC_H */
