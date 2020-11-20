/* Copyright 2020 Gautham Yerroju <gautham.yerroju@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "gotham.h"

uint16_t layout_timer;
uint16_t clipboard_timer;

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    xprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif
    if (process_record_keymap(keycode, record)
#if defined OLED_DRIVER_ENABLE
#    ifndef DISABLE_USERSPACE_OLED
        && process_record_user_oled(keycode, record)
#    endif
#endif
#ifdef ENCODER_ENABLE
        && process_record_user_encoder(keycode, record)
#endif
#ifdef THUMBSTICK_ENABLE
        && process_record_user_thumbstick(keycode, record)
#endif
    ) {
        switch (keycode) {
            case KC_LAYOUT:
                if (record->event.pressed) {
                    layout_timer = timer_read();
                } else {
                    if (timer_elapsed(layout_timer) > TAPPING_TERM) {  // Hold, QWERTY
                        set_single_persistent_default_layer(_QWERTY);
                    } else {  // Tap, cycle between available layouts
                        uint32_t new_default_layer = _QWERTY + (get_highest_layer(default_layer_state) + 1) % LAYOUT_COUNT;
                        set_single_persistent_default_layer(new_default_layer);
                    }
                }
                break;

            case KC_MAKE:
                if (!record->event.pressed) {
                    SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP ":flash"
#if (defined(BOOTLOADER_DFU) || defined(BOOTLOADER_LUFA_DFU) || defined(BOOTLOADER_QMK_DFU))
                                " BOOTLOADER=atmel-dfu"
#elif defined(BOOTLOADER_HALFKAY)
                                " BOOTLOADER=halfkay"
#elif defined(BOOTLOADER_CATERINA)
                                " BOOTLOADER=caterina"
#endif
                                " -j5 --output-sync\n");
                }
                break;

            case VRSN:  // Prints firmware version
                if (record->event.pressed) {
                    SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE);
                }
                break;

            case KC_CCCV:  // One key copy/paste
                if (record->event.pressed) {
                    clipboard_timer = timer_read();
                } else {
                    if (timer_elapsed(clipboard_timer) > TAPPING_TERM) {  // Hold, copy
                        tap_code16(LCTL(KC_C));
                    } else {  // Tap, paste
                        tap_code16(LCTL(KC_V));
                    }
                }
                break;
        }
    }
    return true;
}
