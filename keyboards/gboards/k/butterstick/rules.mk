# Platform defs
MCU = atmega32u4
BOOTLOADER = atmel-dfu

# QMK Options
MOUSEKEY_ENABLE		= yes				# Mouse keys
EXTRAKEY_ENABLE		= yes       # Audio control and System control
CONSOLE_ENABLE		= yes       # Console for debug
COMMAND_ENABLE		= no				# Commands for debug and configuration
NKRO_ENABLE				= yes       # USB Nkey Rollover

# Extra defs
OPT_DEFS 						+= -DDEBUG_MATRIX
EXTRAFLAGS 					+= -flto
