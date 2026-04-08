# SPDX-License-Identifier: GPL-3.0-or-later

name := stash
version := 0.0.0

ifneq ($(filter extra-prereqs,$(.FEATURES)),extra-prereqs)
  $(error GNU Make >= 4.3 is required. Your Make version is $(MAKE_VERSION))
endif

kconfigenv := KCONFIG_FUNCTIONS=kconfig PYTHONPATH=$(CURDIR)/scripts
kconfiglib := $(kconfigenv) kconfiglib
menuconfig := $(kconfiglib)/menuconfig.py

find-toolchain := scripts/find-toolchain.py

objtree := build

include scripts/Makefile.helper
include scripts/Makefile.toolchain

.PHONY: menuconfig

menuconfig: $(objtree)/cc.info $(objtree)/ld.info $(objtree)/repo.info
	OBJTREE=$(objtree) MENUCONFIG_STYLE=aquatic $(menuconfig)
