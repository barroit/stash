/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#ifndef UNITEST_H
#define UNITEST_H

#include <stddef.h>

#include "attr.h"
#include "cpp.h"

typedef void (*unitest_routine_t)(void);

extern unitest_routine_t __unitest_begin[];
extern unitest_routine_t __unitest_end[];

extern unitest_routine_t __unitest_setup;
extern unitest_routine_t __unitest_teardown;

extern unsigned int __unitest_failures;

#define unitest_routine(name) __unitest_routine(__test_ ## name)

#define __unitest_routine(name) \
	unitest_routine_def(name, unitest_routine_lv(name))

#define unitest_routine_def(name, lv) \
	static void name(void); lv = &name; static void name(void)

#define unitest_routine_lv(name) \
	static unitest_ld_section void (*name ## _ptr)(void)

#define unitest_begin(...) \
	unsigned int __unitest_failures = 0; \
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

#define unitest_ld_section __section(".miku_test") __used

#ifdef __APPLE__
# define unitest_ld_section_name "__DATA,__miku_test"
#else
# define unitest_ld_section_name 
#endif

#endif /* UNITEST_H */
