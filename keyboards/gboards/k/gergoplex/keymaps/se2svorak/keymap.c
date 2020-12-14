/* 
 * CTTSRK's swedish to svorak gergoplex layout a.k.a.
 *
 * se2svorak
 *
 * Tested with the standard windows Swedish layout and the macos Swedish Pro
 * layouts. Finnish should also work since afaik it's identical in both cases.
 *
 * There's a mac mode and a pc mode to work around the differences in keycodes
 * on the different platforms. The mode switch persists over power cycles.
 *
 * The symbls layer has live versions of the relevant dead diacritic keys from
 * the Swedish layout. The dead key versions are on the Numbers & Navigation
 * layer.
 *
 * This layout currently has no overloads because a) they feel laggy and
 * b) for now I don't want to wait for key relase before getting feedback on
 * the screen. Maybe there's a fast way to do it?
 *
 * TODO: Would be nice to have a mode for connecting to computers that are
 * configured for US keyboards, will add if I figure out a DRY way to do it.
 */

#include QMK_KEYBOARD_H
#include "g/keymap_combo.h"
#include "keymap_swedish.h"

enum se2svorak_layers {
    BASEPC,
    BASEMAC,
    SYM,
    SYMMAC,
    NUM,
    NUMMAC,
    MOUSE,
    MOUSEMAC,
    FN,
    MEDIA,
    MEDIAMAC,
};


// OS-specific keys
#define MACPIPE A(SE_7)
#define MACBSLS S(MACPIPE)
#define MACLCBR S(SE_LBRC)
#define MACRCBR S(SE_RBRC)
#define MACLOCK C(G(KC_Q))
#define WINLOCK G(KC_L)

// Finetune volume
#define FINVOLD S(A(KC_VOLD))
#define FINVOLU S(A(KC_VOLU))


enum se2svorak_keycodes {
    // Live versions of some dead keys
    LV_CIRC = SAFE_RANGE,
    LV_GRV,
    LV_TILD,

    // Reconfigure for pc/mac
    ADJ_PC,
    ADJ_MAC,

    // Switch to layer when held + mac adjusted versions
    LAY_SYM,
    MAC_SYM,
    LAY_NUM,
    MAC_NUM,
    LAY_MOU,
    MAC_MOU,
    LAY_MED,
    MAC_MED,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

    case ADJ_PC:
        if (record->event.pressed) {
            set_single_persistent_default_layer(BASEPC);
        }
        return false;
        break;
    case ADJ_MAC:
        if (record->event.pressed) {
            set_single_persistent_default_layer(BASEMAC);
        }
        return false;
        break;

    case LV_CIRC:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LSFT) SS_TAP(X_RBRC) SS_UP(X_LSFT) " ");
        }
        break;
    case LV_GRV:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LSFT) SS_TAP(X_EQL) SS_UP(X_LSFT) " ");
        }
        break;
    case LV_TILD:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_RBRC) SS_UP(X_RALT) " ");
        }
        break;

    // Toggle the specified layers on both key press and release, emulating
    // the "momentarily switch to layer when held" behaviour of MO().
    case LAY_SYM:
        layer_invert(SYM);
        break;
    case MAC_SYM:
        layer_invert(SYM);
        layer_invert(SYMMAC);
        break;
    case LAY_NUM:
        layer_invert(NUM);
        break;
    case MAC_NUM:
        layer_invert(NUM);
        layer_invert(NUMMAC);
        break;
    case LAY_MED:
        layer_invert(MEDIA);
        break;
    case MAC_MED:
        layer_invert(MEDIA);
        layer_invert(MEDIAMAC);
        break;
    case LAY_MOU:
        layer_invert(MOUSE);
        break;
    case MAC_MOU:
        layer_invert(MOUSE);
        layer_invert(MOUSEMAC);
        break;

    }
    return true;
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {



/* CHORDS
 *
 * These are mapped in "gergoplex.def", which has to be updated to reflect any
 * changes in the base layer here.
 *
 * Chords on the right dvorak home row mess with the common letter sequences
 * 'th', 'nt' and 'sn' when typing fast, so avoid mapping any chords there.
 *
 *   +-----+-----+-----+-----+-----+            +-----+-----+-----+-----+-----+
 *   |     |    esc    |     |     |            |     |     | backspace |     |
 *   +-----+-----+-----+-----+-----+            +-----+-----+-----+-----+-----+
 *   |     |    tab    |     |     |            |     |     |     |     |     |
 *   +ctl+a+-----+-----+-----+-----+            +-----+-----+-----+-----+-----+
 *   |     |   shift   _     |     |            |     |     |   enter  ctl    |
 *   +-----+-----+-----+-----+-----+            +-----+-----+-----+-----+-----+
 *                  +-----+-------+-----+  +-----+-------+-----+
 *                  |     |       |     |  |     |       |     |
 *                  +-----+-------+     |  |     +-------+-----+
 *                                |     |  |     |
 *                                +-----+  +-----+
 */



/* BASE
 *   +-----+-----+-----+-----+-----+            +-----+-----+-----+-----+-----+
 *   | ' * | , ; | . : |  P  |  Y  |            |  F  |  G  |  C  |  R  |  L  |
 *   +-----+-----+-----+-----+-----+            +-----+-----+-----+-----+-----+
 *   |  A  |  O  |  E  |  U  |  I  |            |  D  |  H  |  T  |  N  |  S  |
 *   +-----+-----+-----+-----+-----+            +-----+-----+-----+-----+-----+
 *   | ctl |  Q  |  J  |  K  |  X  |            |  B  |  M  |  W  |  V  |  Z  |
 *   +-----+-----+-----+-----+-----+            +-----+-----+-----+-----+-----+
 *                  +-----+-------+-----+  +-----+-------+-----+
 *                  | alt | space |     |  |     | shift | win |
 *                  +-----+-------+ sym |  | num +-------+-----+
 *                  mac cmd       |     |  |     |       mac opt
 *                                +-----+  +-----+
 */
[BASEPC] = LAYOUT_gergoplex(
SE_QUOT, SE_COMM, SE_DOT,  SE_P,   SE_Y,      SE_F,    SE_G,    SE_C,  SE_R,  SE_L, 
SE_A,    SE_O,    SE_E,    SE_U,   KC_I,      SE_D,    SE_H,    SE_T,  SE_N,  SE_S,
KC_LCTL, SE_Q,    SE_J,    SE_K,   SE_X,      SE_B,    SE_M,    SE_W,  SE_V,  SE_Z,
                  KC_LALT, KC_SPC, LAY_SYM,   LAY_NUM, KC_LSFT, KC_LGUI
),
[BASEMAC] = LAYOUT_gergoplex(
SE_QUOT, SE_COMM, SE_DOT,  SE_P,   SE_Y,      SE_F,    SE_G,    SE_C,  SE_R,  SE_L, 
SE_A,    SE_O,    SE_E,    SE_U,   KC_I,      SE_D,    SE_H,    SE_T,  SE_N,  SE_S,
KC_LCTL, SE_Q,    SE_J,    SE_K,   SE_X,      SE_B,    SE_M,    SE_W,  SE_V,  SE_Z,
                  KC_LCMD, KC_SPC, MAC_SYM,   MAC_NUM, KC_LSFT, KC_LOPT
),



/* SYMBOLS
 *   +-----+-----+-----+-----+-----+            +-----+-----+-----+-----+-----+
 *   |  !  |  @  |  #  |  $  |  %  |            |  ^  |  &  |  _  |  (  |  )  |
 *   +-----+-----+-----+-----+-----+            +-----+-----+-----+-----+-----+
 *   |Aring| Odia| Adia|  "  |  `  |            |  +  |  <  |  >  |  ~  |  -  |
 *   +-----+-----+-----+-----+-----+            +-----+-----+-----+-----+-----+
 *   | ctl |  \  |  {  |  }  |  ?  |            |  |  |  [  |  ]  |  /  |  =  |
 *   +-----+-----+-----+-----+-----+            +-----+-----+-----+-----+-----+
 *                  +-----+-------+-----+  +-----+-------+-----+
 *                  | adj |       | XXX |  |     | shift | win |
 *                  +-----+-------+ XXX |  | del +-------+-----+
 *   toggle pc/mac mode^          | XXX |  |     |       mac opt
 *                                +-----+  +-----+
 */
[SYM] = LAYOUT_gergoplex(
SE_EXLM, SE_AT,   SE_HASH, SE_DLR,  SE_PERC,    LV_CIRC, SE_AMPR, SE_UNDS, SE_LPRN, SE_RPRN,
SE_ARNG, SE_ODIA, SE_ADIA, SE_DQUO, LV_GRV,     SE_PLUS, SE_LABK, SE_RABK, LV_TILD, SE_MINS,
_______, SE_BSLS, SE_LCBR, SE_RCBR, SE_QUES,    SE_PIPE, SE_LBRC, SE_RBRC, SE_SLSH, SE_EQL,
                  ADJ_MAC, KC_NO,   _______,    KC_DEL,  _______, _______
),
[SYMMAC] = LAYOUT_gergoplex(
_______, _______, _______, _______, _______,    _______, _______, _______, _______, _______,
_______, _______, _______, _______, _______,    _______, _______, _______, _______, _______,
_______, MACBSLS, MACLCBR, MACRCBR, _______,    MACPIPE, _______, _______, _______, _______,
                  ADJ_PC,  _______, _______,    _______, _______, _______

),



/* NUMBERS & NAVIGATION
 *   +-----+-----+-----+-----+-----+            +-----+-----+-----+-----+-----+
 *   |  1  |  2  |  3  |  4  |  5  |            |  6  |  7  |  8  |  9  |  0  |
 *   +-----+-----+-----+-----+-----+            +-----+-----+-----+-----+-----+
 *   |     | circ|acute| diae|grave|            | pgup|     |  up |tilde| home|
 *   +-----+-----+-----+-----+-----+            +-----+-----+-----+-----+-----+
 *   | ctl |mouse|  fn |media|     |            | pgdn| left| down|right| end |
 *   +-----+-----+-----+-----+-----+            +-----+-----+-----+-----+-----+
 *                  +-----+-------+-----+  +-----+-------+-----+
 *                  | alt | space |     |  | XXX |       |     |
 *                  +-----+-------+ bspc|  | XXX +-------+-----+
 *                  mac cmd       |     |  | XXX |
 *                                +-----+  +-----+
 */
[NUM] = LAYOUT_gergoplex(
SE_1,    SE_2,    SE_3,    SE_4,    SE_5,       SE_6,    SE_7,    SE_8,    SE_9,    SE_0,
XXXXXXX, SE_CIRC, SE_ACUT, SE_DIAE, SE_GRV,     KC_PGUP, XXXXXXX, KC_UP,   SE_TILD, KC_HOME,
_______, LAY_MOU, MO(FN),  LAY_MED, XXXXXXX,    KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,
                  _______, _______, KC_BSPC,    _______, XXXXXXX, XXXXXXX
),
[NUMMAC] = LAYOUT_gergoplex(
_______, _______, _______, _______, _______,    _______, _______, _______, _______, _______,
_______, _______, _______, _______, _______,    _______, _______, _______, _______, _______,
_______, MAC_MOU, _______, MAC_MED, _______,    _______, _______, _______, _______, _______,
                  _______, _______, _______,    _______, _______, _______
),



/* MOUSE
 *   +-----+-----+-----+-----+-----+            +-----+-----+-----+-----+-----+
 *   |     |     |     |     |     |            | del | lmb | mmb | rmb | acl2|
 *   +-----+-----+-----+-----+-----+            +-----+-----+-----+-----+-----+
 *   |     |     |     |     |     |            | mwu | lmb | mup | rmb | acl1|
 *   +-----+-----+-----+-----+-----+            +-----+-----+-----+-----+-----+
 *   | ctl | XXX |     |     |     |            | mwd |mleft|mdown|mrght| acl0|
 *   +-----+-----+-----+-----+-----+            +-----+-----+-----+-----+-----+
 *                  +-----+-------+-----+  +-----+-------+-----+
 *                  | alt | space |     |  | XXX |       |     |
 *                  +-----+-------+ bspc|  | XXX +-------+-----+
 *                  mac cmd       |     |  | XXX |
 *                                +-----+  +-----+
 */
[MOUSE] = LAYOUT_gergoplex(
XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_DEL,  KC_BTN1, KC_BTN3, KC_BTN2, KC_ACL2,
XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_WH_U, KC_BTN1, KC_MS_U, KC_BTN2, KC_ACL1,
_______, _______, XXXXXXX, XXXXXXX, XXXXXXX,    KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, KC_ACL0,
                  _______, _______, KC_BSPC,    _______, XXXXXXX, XXXXXXX
),
[MOUSEMAC] = LAYOUT_gergoplex(  // Switch scroll direction on mac
_______, _______, _______, _______, _______,    _______, _______, _______, _______, _______,
_______, _______, _______, _______, _______,    KC_WH_D, _______, _______, _______, _______,
_______, _______, _______, _______, _______,    KC_WH_U, _______, _______, _______, _______,
                  _______, _______, _______,    _______, _______, _______
),



/* FUNCTION keys
 *   +-----+-----+-----+-----+-----+            +-----+-----+-----+-----+-----+
 *   |     |     |     |     |     |            | del | F1  | F2  | F3  | F4  |
 *   +-----+-----+-----+-----+-----+            +-----+-----+-----+-----+-----+
 *   |     |     |     |     |     |            |     | F5  | F6  | F7  | F8  |
 *   +-----+-----+-----+-----+-----+            +-----+-----+-----+-----+-----+
 *   | ctl |     | XXX |     |     |            |     | F9  | F10 | F11 | F12 |
 *   +-----+-----+-----+-----+-----+            +-----+-----+-----+-----+-----+
 *                  +-----+-------+-----+  +-----+-------+-----+
 *                  | alt | space |     |  | XXX |       |     |
 *                  +-----+-------+ bspc|  | XXX +-------+-----+
 *                  mac cmd       |     |  | XXX |
 *                                +-----+  +-----+
 */
[FN] = LAYOUT_gergoplex(
XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,
XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, KC_F5,   KC_F6,   KC_F7,   KC_F8,
_______, XXXXXXX, _______, XXXXXXX, XXXXXXX,    XXXXXXX, KC_F9,   KC_F10,  KC_F11,  KC_F12,
                  _______, _______, KC_BSPC,    _______, XXXXXXX, XXXXXXX
),



/* MEDIA keys, volume, brightness, screen lock
 *   +-----+-----+-----+-----+-----+            +-----+-----+-----+-----+-----+
 *   |     |     |     |     |     |            | del | prev|pause| next| lock|
 *   +-----+-----+-----+-----+-----+            +-----+-----+-----+-----+-----+
 *   |     |     |     |     |     |            | brup| mute|voldn|volup|     |
 *   +-----+-----+-----+-----+-----+            +-----+-----+-----+-----+-----+
 *   | ctl |     |     | XXX |     |            | brdn|     |voldn|volup|     |
 *   +-----+-----+-----+-----+-----+            +-----+-----+-----+-----+-----+
 *                  +-----+-------+-----+  +-----+-------+-----+
 *                  | alt | space |     |  | XXX |       |     |
 *                  +-----+-------+ bspc|  | XXX +-------+-----+
 *                  mac cmd       |     |  | XXX |
 *                                +-----+  +-----+
 */
[MEDIA] = LAYOUT_gergoplex(
XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_DEL,  KC_MPRV, KC_MPLY, KC_MNXT, WINLOCK,
XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_BRIU, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX,
_______, XXXXXXX, XXXXXXX, _______, XXXXXXX,    KC_BRID, XXXXXXX, FINVOLD, FINVOLU, XXXXXXX,
                  _______, _______, KC_BSPC,    _______, XXXXXXX, XXXXXXX
),
[MEDIAMAC] = LAYOUT_gergoplex(
_______, _______, _______, _______, _______,    _______, _______, _______, _______, MACLOCK,
_______, _______, _______, _______, _______,    _______, _______, _______, _______, _______,
_______, _______, _______, _______, _______,    _______, _______, _______, _______, _______,
                  _______, _______, _______,    _______, _______, _______
),



};
