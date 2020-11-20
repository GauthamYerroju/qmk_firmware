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

#pragma once

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)

#    ifdef RGBLIGHT_ENABLE
extern rgblight_config_t rgblight_config;
#    endif

#    ifdef RGB_MATRIX_ENABLE
extern rgb_config_t rgb_matrix_config;
#    endif

#endif

#ifdef AUDIO_ENABLE
extern audio_config_t audio_config;
#endif

#ifdef OLED_ANIMATIONS_ENABLE
static bool     oled_showing_info;
static uint16_t oled_info_timer;
#endif

// 5x3 Logos

void render_corne_logo(void) {
    static const char PROGMEM font_logo[16] = {0x80, 0x81, 0x82, 0x83, 0x84, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0};
    oled_write_P(font_logo, false);
};

void render_qmk_logo(void) {
    static const char PROGMEM font_qmk_logo[16] = {0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0};
    oled_write_P(font_qmk_logo, false);
};

// 5x2 Keyboard, Controller logos

void render_keyboard(void) {
    static const char PROGMEM font_keyboard[11] = {0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0};
    oled_write_P(font_keyboard, false);
};

void render_controller(void) {
    static const char PROGMEM font_controller[11] = {0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0};
    oled_write_P(font_controller, false);
};

void render_device(void) {
    if (IS_LAYER_ON(_GAME)) {
        render_controller();
    } else {
        render_keyboard();
    }
}

// 5x1 Layer indicator

void render_layer(void) {
    static const char PROGMEM font_layer[8][6] = {
        {0x85, 0x86, 0x87, 0x88, 0x89, 0},  // Base
        {0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0},  // Lower
        {0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0},  // Raise
        {0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0},  // Adjust
        {0x9a, 0x98, 0x99, 0x9d, 0x9e, 0},  // Mouse
        "NUMBR",                            // Game Number
        "ARROW",                            // Game Nav
        "-mac-",                            // Mac mode
    };
    uint8_t  layer         = is_mac_mode() ? 7 : 0;
    uint32_t highest_layer = get_highest_layer(layer_state);
    if (highest_layer == _LOWER) {
        layer = 1;
    } else if (highest_layer == _RAISE) {
        layer = 2;
    } else if (highest_layer == _ADJUST) {
        layer = 3;
    } else if (highest_layer == _MOUSE) {
        layer = 4;
    } else if (highest_layer == _GAMENUM) {
        layer = 5;
    } else if (highest_layer == _GAMENAV) {
        layer = 6;
    }
    oled_write_P(font_layer[layer], false);
};

    // 2x1 Audio, clicky and RGB status indicators

#ifdef AUDIO_ENABLE
void render_audio_status(void) {
    static const char PROGMEM font_audio_off[3] = {0x8f, 0x90, 0};
    static const char PROGMEM font_audio_on[3]  = {0x91, 0x92, 0};
    oled_write_P(audio_config.enable ? font_audio_on : font_audio_off, false);
};

void render_clicky_status(void) {
    static const char PROGMEM font_clicky_off[3] = {0xaf, 0xb0, 0};
    static const char PROGMEM font_clicky_on[3]  = {0xb1, 0xb2, 0};
    oled_write_P(audio_config.clicky_enable ? font_clicky_on : font_clicky_off, false);
};
#endif

#if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
void render_rgb_status(void) {
    static const char PROGMEM font_rgb_off[3] = {0xcf, 0xd0, 0};
    static const char PROGMEM font_rgb_on[3]  = {0xd1, 0xd2, 0};
#    ifdef RGBLIGHT_ENABLE
    bool rgb_enabled = rgblight_config.enable;
#    elif RGB_MATRIX_ENABLE
    bool rgb_enabled = rgb_matrix_config.enable;
#    endif
    oled_write_P(rgb_enabled ? font_rgb_on : font_rgb_off, false);
};
#endif

// 2x1 Ctrl, Alt, Shift, GUI, Mouse

void render_mod_ctrl(void) {
    static const char PROGMEM font_ctrl[3] = {0x93, 0x94, 0};
    oled_write_P(font_ctrl, false);
};

void render_mod_alt(void) {
    static const char PROGMEM font_alt[3] = {0xb3, 0xb4, 0};
    oled_write_P(font_alt, false);
};

void render_mod_shift(void) {
    static const char PROGMEM font_shift[3] = {0xd3, 0xd4, 0};
    oled_write_P(font_shift, false);
};

void render_mod_gui(void) {
    static const char PROGMEM font_gui[3] = {0x95, 0x96, 0};
    oled_write_P(font_gui, false);
};

#ifdef MOUSEKEY_ENABLE
void render_mod_mouse(void) {
    static const char PROGMEM font_mouse[3] = {0x97, 0x98, 0};
    oled_write_P(font_mouse, false);
};
#endif

// 5x2 Mod and feature indicator clusters

void render_mod_status(void) {
#ifdef NO_ACTION_ONESHOT
    uint8_t modifiers = get_mods();
#else
    uint8_t modifiers = get_mods() | get_oneshot_mods();
#endif

    (modifiers & MOD_MASK_CTRL) ? render_mod_ctrl() : oled_write_P(PSTR("  "), false);
    oled_write_P(PSTR(" "), false);
    (modifiers & MOD_MASK_SHIFT) ? render_mod_shift() : oled_write_P(PSTR("  "), false);

    (modifiers & MOD_MASK_ALT) ? render_mod_alt() : oled_write_P(PSTR("  "), false);
    oled_write_P(PSTR(" "), false);
    (modifiers & MOD_MASK_GUI) ? render_mod_gui() : oled_write_P(PSTR("  "), false);
}

void render_feature_status(void) {
#if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
    render_rgb_status();
#endif

#ifdef AUDIO_ENABLE
    oled_write_P(PSTR(" "), false);
    render_audio_status();
#endif
};

// Keylogger
#define KEYLOGGER_LENGTH 5
static char     keylog_str[KEYLOGGER_LENGTH + 1] = {"\n"};
// clang-format off
static const char PROGMEM code_to_name[0xFF] = {
//   0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',  // 0x
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2',  // 1x
    '3', '4', '5', '6', '7', '8', '9', '0',  20,  19,  27,  26,  22, '-', '=', '[',  // 2x
    ']','\\', '#', ';','\'', '`', ',', '.', '/', 128, ' ', ' ', ' ', ' ', ' ', ' ',  // 3x
    ' ', ' ', ' ', ' ', ' ', ' ', 'P', 'S', ' ', ' ', ' ', ' ',  16, ' ', ' ', ' ',  // 4x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 5x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 6x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 7x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 8x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 9x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Ax
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Bx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Cx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Dx
    'C', 'S', 'A', 'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Ex
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '        // Fx
};
// clang-format on

void add_keylog(uint16_t keycode) {
  if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) || (keycode >= QK_MODS && keycode <= QK_MODS_MAX)) {
    keycode = keycode & 0xFF;
  } else if (keycode > 0xFF) {
    keycode = 0;
  }

  for (uint8_t i = (KEYLOGGER_LENGTH - 1); i > 0; --i) {
    keylog_str[i] = keylog_str[i - 1];
  }

  if (keycode < (sizeof(code_to_name) / sizeof(char))) {
    keylog_str[0] = pgm_read_byte(&code_to_name[keycode]);
  }
}

void render_keylogger_status(void) {
  oled_write(keylog_str, false);
}

void render_prompt(void) {
    bool blink = (timer_read() % 1000) < 500;
    uint32_t highest_layer = get_highest_layer(layer_state);

    if (highest_layer == _LOWER) {
        oled_write_ln_P(blink ? PSTR("> lo_") : PSTR("> lo "), false);
    } else if (highest_layer == _RAISE) {
        oled_write_ln_P(blink ? PSTR("> hi_") : PSTR("> hi "), false);
    } else if (highest_layer == _ADJUST) {
        oled_write_ln_P(blink ? PSTR("> aj_") : PSTR("> aj "), false);
    } else if (highest_layer == _GAME) {
        oled_write_ln_P(blink ? PSTR("> Gm_") : PSTR("> Gm "), false);
    } else if (highest_layer == _GAMENUM) {
        oled_write_ln_P(blink ? PSTR("> GN_") : PSTR("> GN "), false);
    } else if (highest_layer == _GAMENAV) {
        oled_write_ln_P(blink ? PSTR("> GA_") : PSTR("> GA "), false);
    } else {
        oled_write_ln_P(blink ? PSTR("> _  ") : PSTR(">    "), false);
    }
};

bool process_record_keymap_oled(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
// Pause animations to show state change
#ifdef OLED_ANIMATIONS_ENABLE
#    ifdef THUMBSTICK_ENABLE
            case TMB_MODE:
            oled_info_timer = timer_read();
                break;
#    endif
#    ifdef ENCODER_ENABLE
            case ENC_MODE_L ... ENC_MODE_R:
                oled_info_timer = timer_read();
                break;
#    endif
#endif // OLED_ANIMATIONS_ENABLE
            default:
#if defined(OLED_ANIMATIONS_ENABLE) && defined(OLED_ANIM_STARFIELD)
                starfield_speed_set(starfield_speed_get() + 8);
#endif
                add_keylog(keycode);
                break;
        }
    }
    return true;
}

void render_status_main(void) {
    oled_write_ln("", false);
    oled_write_ln("", false);

    render_device();

    oled_write_ln("", false);
    oled_write_ln("", false);

    render_layer();

    oled_write_ln("", false);
    oled_write_ln("", false);
    oled_write_ln("", false);

    #if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE) || defined(AUDIO_ENABLE)
        (get_highest_layer(layer_state) == _ADJUST) ? render_feature_status() : render_mod_status();
    #else
        render_mod_status();
    #endif
}

void render_status_secondary(void) {
    oled_write_ln("", false);
    oled_write_ln("", false);

    render_corne_logo();

    oled_write_ln("", false);
    oled_write_ln("", false);
    oled_write_ln("", false);

    render_qmk_logo();

    oled_write_ln("", false);
    oled_write_ln("", false);
    oled_write_ln("", false);

    render_prompt();
}

void render_status(void) {
#ifdef OLED_ANIMATIONS_ENABLE
    if (IS_LAYER_ON(_ADJUST) || timer_elapsed(oled_info_timer) <= OLED_INFO_TIMEOUT) {
        if (!oled_showing_info) {
            oled_clear();
#    ifdef OLED_ANIM_STARFIELD
            set_starfield_center();
#    endif
            oled_showing_info = true;
        }
#endif

        if (is_master) {
            render_status_main();
        } else {
            render_status_secondary();
        }

#ifdef OLED_ANIMATIONS_ENABLE
    } else {
        if (oled_showing_info) {
            oled_clear();
            oled_showing_info = false;
        }
#    if defined(OLED_ANIM_STARFIELD)
        render_starfield();
#    elif defined(OLED_ANIM_IMAGE_BOUNCE)
        render_image_bounce();
#    endif
    }
#endif
}

oled_rotation_t oled_init_keymap(oled_rotation_t rotation) {
#ifdef OLED_ANIMATIONS_ENABLE
    oled_showing_info = false;
    oled_info_timer   = timer_read() + OLED_INFO_TIMEOUT;
#endif
    return OLED_ROTATION;
}
