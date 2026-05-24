# SPDX-License-Identifier: GPL-3.0-or-later

menu "Program features"

config NULL_DEVICE
	string "Null device name"
	default "NUL:" if $(host-id) = win32
	default "/dev/null"

config UTF8_LOCALE
	string "Default LC_CTYPE"
	default "$(utf8-locale)"

endmenu # Program features
