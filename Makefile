# SPDX-License-Identifier: GPL-3.0-or-later

name := stash
version := 0.0.0

ifneq ($(filter extra-prereqs,$(.FEATURES)),extra-prereqs)
  $(error GNU Make >= 4.3 is required. Your Make version is $(MAKE_VERSION))
endif

MAKEFLAGS += -rR

objtree := build

lib-src := sqlite/build/sqlite3.c \
	   lib/parse_argv.c

cmd-src := cmd/add.c \
	   cmd/help.c \
	   cmd/search.c \
	   cmd/version.c

main-src := main.c commands.c

link-src := openssl/build/libcrypto

main-obj := $(addprefix $(objtree)/,$(main-src:.c=.o))
cmd-obj := $(addprefix $(objtree)/,$(cmd-src:.c=.o))
lib-obj := $(addprefix $(objtree)/,$(lib-src:.c=.o))

$(objtree)/$(name):

include scripts/Makefile.toolchain
include scripts/Makefile.kconfig
include scripts/Makefile.flags

ifneq ($(wildcard deps/auto.conf),)
  CC := $(CONFIG_CC_PROGRAM)
  LD := $(CONFIG_LD_ID)
endif

link-$(CONFIG_UNIX) := $(addsuffix .a,$(link-src))
link-$(CONFIG_WIN32) := $(addsuffix .lib,$(link-src))

obj-y := $(main-obj) $(cmd-obj) $(lib-obj)

cmd-y := $(addprefix $(objtree)/stash-,$(notdir $(basename $(cmd-obj))))

.PNONY: commands

commands: $(objtree)/$(name) $(cmd-y)

$(objtree)/$(name): $(obj-y) $(link-y)
	$(CC) $(LDFLAGS) -fuse-ld=$(LD) $^ -o $@

$(cmd-y):

$(filter-out stash-version stash-help,$(cmd-y)): $(link-y)

$(objtree)/stash-%: $(objtree)/cmd/main_%.o $(objtree)/cmd/%.o $(lib-obj)
	$(CC) $(LDFLAGS) -fuse-ld=$(LD) $^ -o $@

cmd/main_%.c:
	scripts/gen-command-entry.sh $* >$@

$(objtree)/sqlite/build/sqlite3.o: sqlite/build/sqlite3.c
	mkdir -p $(@D)
	$(CC) -O3 -w -c $< -o $@

sqlite/build/sqlite3.c openssl/build/libcrypto.a:
	$(error No $@ found. \
		Run 'scripts/build-$(firstword $(subst /, ,$@)).sh' first)

$(objtree)/main.o: $(objtree)/commands.o

$(objtree)/%.o: %.c include/config.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(obj-y:.o=.d)

commands.c: include/commands.h .commands
	printf '%s\n' $(notdir $(cmd-src)) | scripts/gen-commands_c.sh >$@

include/commands.h: .commands
	printf '%s\n' $(notdir $(cmd-src)) | scripts/gen-commands_h.sh >$@

.commands: .force
	@trap 'rm -f .tmp-$$$$' EXIT && \
	printf '%s\n' $(cmd-src) | sort >.tmp-$$$$ && \
	test -f $@ && diff .tmp-$$$$ $@ >/dev/null || mv .tmp-$$$$ $@

.force:

.PHONY: clean distclean

distclean: clean
	rm -rf build deps
	rm -f .config*

clean:
	test -d $(objtree) && \
	find $(objtree) \( -name '*.o' -o -name '*.d' \) ! -name sqlite3.o \
			-exec rm {} + || true
	rm -f commands.c include/commands.h include/config.h \
	      $(objtree)/$(name) $(objtree)/$(name)-*
