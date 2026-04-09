# SPDX-License-Identifier: GPL-3.0-or-later

menu "Program features"

menuconfig ENABLE_I18N
	bool "Enable i18n support"

if ENABLE_I18N

config TEXT_DOMAIN
	string "GNU gettext text domain"
	default $(repo-name)

endif # ENABLE_I18N

menu "Formatting options"

config CNTL_CHAR_REPL
	string "Control character replacement"
	default "�"

config LINE_WRAP
	int "Line wrap threshold"
	default 80

config OPTION_HELP_INDENT
	int "Option help indentation"
	default 2

config OPTION_HELP_WRAP
	int "Option help wrap threshold"
	default 16

endmenu # Formatting options

config NULL_DEVICE
	string "Null device name"
	default "NUL:" if PLATFORM_IS_NT
	default "/dev/null"

endmenu # Program features
