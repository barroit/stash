# SPDX-License-Identifier: GPL-3.0-or-later

name := stash
version := 0.0.0

ifneq ($(filter extra-prereqs,$(.FEATURES)),extra-prereqs)
  $(error GNU Make >= 4.3 is required. Your Make version is $(MAKE_VERSION))
endif

objtree := build

clean :=
distclean :=
clean_target := clean distclean

include scripts/Makefile.helper
include scripts/Makefile.toolchain
include scripts/Makefile.kconfig
include scripts/Makefile.flags

CC := $(CONFIG_CC_PROGRAM)
LD := $(CONFIG_LD_ID)

$(objtree)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -Iinclude -c -o $@ $<

lib-y := lib/parse_args.o

cmd-y := cmd/add.o

main-y := main.o

$(objtree)/$(name): $(addprefix $(objtree)/,$(main-y) $(cmd-y) $(lib-y))
	$(CC) $(LDFLAGS) -fuse-ld=$(LD) -o $@ $^

.PHONY: clean distclean

distclean: clean
	rm -rf $(objtree) $(distclean)

clean:
	rm -f $(clean)
