/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#ifndef PARSE_ARGS_H
#define PARSE_ARGS_H

#include <stddef.h>
#include <stdint.h>

#define PA_STOP_BARE 1

#define PA_ARG_NO_VAL  (1 << 0)
#define PA_ARG_OPT_VAL (1 << 1)

typedef int (*pa_command_fn)(int, const char **);

enum pa_opt_class {
	PA_OPTC_END,
	PA_OPTC_OPT,
	PA_OPTC_CMD,
};

enum pa_opt_type {
	PA_ARG_CNT,
	PA_ARG_STR,
};

struct pa_opt {
	enum pa_opt_class class;
	const char *name;
	char alias;

	enum pa_opt_type type;
	union {
		void *val;
		pa_command_fn *cmd_val;
	};
	union {
		intptr_t ext;
		pa_command_fn cmd_fn;
	};

	unsigned int flag;

	const char *vph;
	const char *help;
};

#define PA_OPT_END() { .class = PA_OPTC_END }

#define PA_OPT_CMD(n, v, f, h) {	\
	.class   = PA_OPTC_CMD,		\
	.name    = n,			\
	.cmd_val = v,			\
	.cmd_fn  = f,			\
	.help    = h,			\
}

#define PA_OPT_FILE(n, a, v, h) \
	PA_OPT_STR(n, a, v, "filename", h)

#define PA_OPT_STR(n, a, v, _v, h) \
	__PA_OPT(n, a, PA_ARG_STR, v, NULL, 0, _v, h)

#define PA_OPT_CNT(n, a, v, h) \
	__PA_OPT(n, a, PA_ARG_CMD, v, 0, 0, NULL, h)

#define __PA_OPT(n, a, t, v, _f, f, _v, h) {	\
	.class = PA_ARG_OPT,			\
	.name  = n,				\
	.alias = a,				\
	.type  = type,				\
	.val   = v,				\
	.fb    = _f,				\
	.flag  = f,				\
	.vph   = _v,				\
	.help  = h,				\
}

int pa_parse_args(int argc, const char **argv,
		  struct pa_opt *opts, unsigned int flag);

#endif /* PARSE_ARGS_H */
