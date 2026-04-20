/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#ifndef UNITEST_H
#define UNITEST_H

#include <stddef.h>

#include "attr.h"
#include "cpp.h"

enum unitest_directive {
	UNITEST_TODO = 1,
	UNITEST_SKIP,
};

struct unitest {
	const char *detail;
	enum unitest_directive direct;
	const char *direct_reason;
};

typedef int (*unitest_routine_t)(struct unitest *);

extern unitest_routine_t __unitest_begin[];
extern unitest_routine_t __unitest_end[];

extern unitest_routine_t __unitest_setup;
extern unitest_routine_t __unitest_teardown;

#define unitest_routine(name) unitest_routine_def(__test_ ## name)

#define unitest_routine_def(name) \
	unitest_routine_declare(name); \
	unitest_routine_lvalue(name) = &name; \
	unitest_routine_declare(name)

#define unitest_routine_lvalue(name) \
	static unitest_ld_section int (*name ## _ptr)(struct unitest *)

#define unitest_routine_declare(name) \
	static int name(struct unitest *unitest)

#define unitest_begin(...) \
	unitest_routine_t unitest_ld_section __unitest_begin[1] = { 0 }; \
	CALL(__unitest_begin_, ##__VA_ARGS__)

#define __unitest_begin_0() unitest_routine_t __unitest_setup = NULL

#define __unitest_begin_1(name) \
	unitest_routine_def(name, unitest_routine_t __unitest_setup)

#define unitest_end(...) \
	unitest_routine_t unitest_ld_section __unitest_end[1] = { 0 }; \
	CALL(__unitest_end_, ##__VA_ARGS__)

#define __unitest_end_0() \
	unitest_routine_t __unitest_teardown = NULL

#define __unitest_end_1(name) \
	unitest_routine_def(name, unitest_routine_t __unitest_teardown)

#define unitest_ld_section __section(unitest_ld_section_name) __no_asan __used

#ifdef __APPLE__
# define unitest_ld_section_name "__DATA,__miku_test"
#else
# define unitest_ld_section_name 
#endif

#endif /* UNITEST_H */
