// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Copyright 2026 Jiamu Sun <39@barroit.sh>
 */

#ifndef ATTR_H
#define ATTR_H

#define __attr __attribute__

/*
 * optimization & inlining
 */

#undef __always_inline
#define __always_inline inline __attr((__always_inline__))

#ifdef __cold
# undef __cold
#endif
#define __cold __attr((__cold__))

/*
 * function behavior & semantics
 */

#define __noreturn __attr((__noreturn__))

#ifdef __pure
# undef __pure
#endif
#define __pure __attr((__pure__))

#define __malloc __attr((__malloc__))

#define __cleanup(x) __attr((__cleanup__(x)))

/*
 * static analysis & diagnostics
 */

#define __printf(fmt, va) __attr((__format__(__printf__, fmt, va)))

#define __warn_unused_result __attr((__warn_unused_result__))

#if __has_attribute(__access__)
# define __read_only(...) __attr((__access__(__read_only__, __VA_ARGS__)))
#else
# define __read_only(...)
#endif

/*
 * usage & visibility
 */

#ifdef __used
# undef __used
#endif
#define __used __attr((__used__))

#define __maybe_unused __attr((__unused__))

/*
 * linker & layout
 */

#define __section(x) __attr((__section__(x)))

#define __constructor __attr((__constructor__))

#endif /* ATTR_H */
