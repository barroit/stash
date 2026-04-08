# SPDX-License-Identifier: GPL-3.0-or-later

objtree := build

find-toolchain := scripts/find-toolchain.py

$(objtree)/toolchain.info:
	mkdir -p $(@D)
	$(find-toolchain) >$@

$(objtree)/cc.info: $(objtree)/toolchain.info
	head -1 $< >$@

$(objtree)/ld.info: $(objtree)/toolchain.info
	tail -1 $< >$@
