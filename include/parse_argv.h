/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#ifndef PARSE_ARGS_H
#define PARSE_ARGS_H

// stash --options -flags commands --options -flags args...
// stash --options -flags commands --options -flags
// stash --options -flags commands
// stash --options -flags

#define STOP_AT_FINISH   0
#define STOP_AT_ARGUMENT 1

int parse_argv(int argc, const char **argv, unsigned int stop_mode);

#endif /* PARSE_ARGS_H */
