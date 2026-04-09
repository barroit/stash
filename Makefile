# SPDX-License-Identifier: GPL-3.0-or-later

name := stash
version := 0.0.0

ifneq ($(filter extra-prereqs,$(.FEATURES)),extra-prereqs)
  $(error GNU Make >= 4.3 is required. Your Make version is $(MAKE_VERSION))
endif

objtree := build

$(objtree)/$(name):

include scripts/Makefile.toolchain
include scripts/Makefile.kconfig
include scripts/Makefile.flags

ifneq ($(wildcard deps/auto.conf),)
  CC := $(CONFIG_CC_PROGRAM)
  LD := $(CONFIG_LD_ID)
endif

includes := include sqlite/build openssl/include openssl/build/include
headers != find $(includes) -type f -name '*.h'

lib-y := sqlite/build/sqlite3.o \
	 lib/parse_args.o

cmd-y := cmd/add.o

main-y := main.o

$(objtree)/$(name): $(addprefix $(objtree)/,$(main-y) $(cmd-y) $(lib-y))
	$(CC) $(LDFLAGS) -fuse-ld=$(LD) -o $@ $^ openssl/build/libcrypto.a

$(objtree)/sqlite/build/sqlite3.o: sqlite/build/sqlite3.c
	mkdir -p $(@D)
	$(CC) -O3 -w -c -o $@ $<

sqlite/build/sqlite3.c openssl/build/libcrypto.a:
	$(error No $@ found. \
		Run 'scripts/build-$(firstword $(subst /, ,$@)).sh' first)

$(objtree)/%.o: %.c $(headers)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(addprefix -I,$(includes)) -c -o $@ $<

.PHONY: clean distclean

distclean: clean
	rm -rf openssl sqlite

clean:
	rm -f .config* include/config.h
	rm -rf $(objtree) deps
