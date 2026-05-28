// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

const char *cmd_list_help = "list";

static const char *usage[] = {
	"test",
	NULL,
};

int cmd_list(int argc, const char **argv)
{
	pa_command_fn cmd = cmd_list_all;
	struct pa_opt opts[] = {
		CMD_LIST_CMDS(&cmd),
		PA_OPT_END(),
	};

	argc = pa_parse_args(argc, argv, opts, usage, 0);
	return 0;
}
