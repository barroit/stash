// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include "atexit.h"
#include "err.h"
#include "parse_argv.h"

int main(int argc, const char **argv)
{
	atexit_setup();

	argc = parse_argv(argc, argv, STOP_AT_ARGUMENT);

	return 0;
}
