// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include <stdlib.h>

#include "foreach.h"

int main(void)
{
	unsigned int next;
	unsigned int stop = __unitest_end - __unitest_begin - 1;
	unitest_routine_t *tests = (typeof(tests))__unitest_begin + 1;

	// if (__unitest_teardown)
	// 	atexit_push(__unitest_teardown);

	if (__unitest_setup)
		__unitest_setup();

	foreach(next, stop)
		tests[next]();

	if (!__unitest_failures)
		exit(0);

	exit(1);
}
