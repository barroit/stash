// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include <stdlib.h>
#include <locale.h>

#include "err.h"
#include "foreach.h"
#include "utf8.h"

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

void utf8_setup(void)
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
