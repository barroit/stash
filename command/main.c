// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include "atexit.h"
#include "err.h"
#include "parse_argv.h"
#include "utf8.h"

int cmd_main(int argc, const char **argv)
{
	pa_command_fn cmd;
	struct pa_opt opts[] = {
		CMD_MAIN_CMDS(&cmd),
		PA_OPT_END(),
	};

	atexit_setup();
	utf8_setup();

	// argc = pa_parse_args(argc, argv, , PA_STOP_BARE);
	return 0;
}
