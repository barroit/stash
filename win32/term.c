/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include <windows.h>

#include "term.h"

unsigned short term_cols(void)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	if (out == INVALID_HANDLE_VALUE || out == NULL)
		return TERM_NICE_COLS;

	if (!GetConsoleScreenBufferInfo(out, &csbi))
		return TERM_NICE_COLS;

	return (unsigned short)(csbi.srWindow.Right - csbi.srWindow.Left + 1);
}
