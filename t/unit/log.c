// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#include <stdlib.h>
#include <stdio.h>

#include "log.h"
#include "uniassert.h"
#include "unitest.h"

unitest_begin(setup)
{
	puts("setup");
}

unitest_routine(logf_fd)
{
	return 0;
}

unitest_end(teardown)
{
	puts("teardown");
}
