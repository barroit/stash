# SPDX-License-Identifier: GPL-3.0-or-later

ifneq ($(eval_build_env),)
  -include deps/features.conf
endif

deps/features.conf: .config
	mkdir -p $(@D)
	trap 'rm -f .tmp-$$$$' EXIT && \
	cat $(objtree)/cc.info | cut -f1 | \
	./scripts/probe-cc-features.sh | sort > .tmp-$$$$ && \
	test -f $@ && diff .tmp-$$$$ $@ >/dev/null || mv .tmp-$$$$ $@
