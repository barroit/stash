// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include <stdio.h>
#include <stdlib.h>

#include "parse_argv.h"

int parse_argv(int argc, const char **argv, unsigned int stop_mode)
{
	const char **next = argv;

	while (*next)
		puts(*next++);

	return 0;
}
