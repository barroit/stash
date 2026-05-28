/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include <sys/ioctl.h>
#include <unistd.h>

#include "term.h"

unsigned short term_cols(void)
{
	struct winsize ws;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) < 0)
		return TERM_NICE_COLS;

	return ws.ws_col;
}
