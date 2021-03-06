// Copyright 2021 m.ki (@m.ki)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* QWERTY */
    [_QWERTY] = LAYOUT(
    KC_ESC,  KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_0,    KC_0,  KC_MINUS,
    KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,  KC_BSPC,
    KC_LCTRL,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,    KC_MINUS,    KC_ENT,
    KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT,  KC_UP,       KC_RSFT,
    KC_LALT, KC_LGUI,        KC_LCTRL,KC_SPACE,LT(_RAISE,KC_SPACE),LT(_LOWER,KC_SPACE),KC_SPACE, KC_RCTL, KC_LEFT, KC_DOWN, KC_RIGHT
  ),
     [_LOWER] = LAYOUT(
    KC_ESC,  KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_0,    KC_0,  KC_MINUS,
    KC_TAB,  KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_0,    KC_0,  KC_BSPC,
    KC_LCTRL,KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_PERC,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN, KC_RPRN, KC_ENTER,
    KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT,  KC_UP, KC_RSFT,
    KC_LALT, KC_LGUI,        KC_LCTRL,KC_SPACE,LT(_RAISE,KC_SPACE),LT(_LOWER,KC_SPACE),KC_SPACE, KC_RCTL, KC_LEFT, KC_DOWN, KC_RIGHT
  ),
     [_RAISE] = LAYOUT(
    KC_ESC,  KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_0,    KC_0,  KC_MINUS,
    KC_TAB,  KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_0,    KC_0,  KC_BSPC,
    KC_LCTRL,KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_PERC,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN, KC_RPRN, KC_ENTER,
    KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT,  KC_UP, KC_RSFT,
    KC_LALT, KC_LGUI,        KC_LCTRL,KC_SPACE,LT(_RAISE,KC_SPACE),LT(_LOWER,KC_SPACE),KC_SPACE, KC_RCTL, KC_LEFT, KC_DOWN, KC_RIGHT
  ),
    [_ADJUST] = LAYOUT(
    KC_ESC,  KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_0,    KC_0,  KC_MINUS,
    KC_TAB,  KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_0,    KC_0,  KC_BSPC,
    KC_LCTRL,KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_PERC,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN, KC_RPRN, KC_ENTER,
    KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT,  KC_UP, KC_RSFT,
    KC_LALT, KC_LGUI,        KC_LCTRL,KC_SPACE,LT(_RAISE,KC_SPACE),LT(_LOWER,KC_SPACE),KC_SPACE, KC_RCTL, KC_LEFT, KC_DOWN, KC_RIGHT
  )
};
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* Left encoder */
        switch (get_highest_layer(layer_state)) {
            case _QWERTY:
                if (clockwise) {
                    tap_code(KC_TAB);
                } else {
                    tap_code16(S(KC_TAB));
                }
                break;
            case _RAISE:
                if (clockwise) {
                //    tap_code(KC_VOLU);
                    if(keymap_config.swap_lalt_lgui==false){
                        tap_code(KC_LANG2);
                    }else {
                        tap_code16(A(KC_GRV));
                    }
                } else {
                    if(keymap_config.swap_lalt_lgui==false){
                    tap_code(KC_LANG1);
                    } else {
                        tap_code16(A(KC_GRV));
                    }
                }
                break;
            case _ADJUST:
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
            }
        }

    } else if (index == 1) { /* Right encoder */
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
}

