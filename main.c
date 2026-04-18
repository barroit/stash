// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include <stdlib.h>

#include "parse_argv.h"

int main(int argc, const char **argv)
{
	argc = parse_argv(argc, argv, STOP_AT_ARGUMENT);

	return 0;
}
