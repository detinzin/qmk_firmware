
/* Copyright 2015-2017 Jack Humbert
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

#include QMK_KEYBOARD_H
#include <stdlib.h>

extern keymap_config_t keymap_config;

#define BLKSEL LALT(LSFT(KC_INS))
#define SPC_TX LT(_TEXT, KC_SPC)
#define CTL_CAPS LCTL_T(KC_CAPS)
#define ESC_TX LT(_TEXT, KC_ESC)
#define TAB_NP LT(_NUMPAD, KC_TAB)

enum layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
  _TEXT,
  _NUMPAD
};

enum keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  BACKLIT,
  TX_NEQ,

  DYNAMIC_MACRO_RANGE
};

  #include "dynamic_macro.h"

enum {
  TD_B_TMUX = 0,
  TD_QT_DQT,
  TD_J_UNDS,
  TD_K_EQL,
  TD_Q_1,
  TD_F_2,
  TD_E_3,
  TD_R_4
};

void the_quote (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
    SEND_STRING("\" ");
    reset_tap_dance(state);
  } else {
    register_code(KC_QUOT);
    unregister_code(KC_QUOT);
  }
}

void the_equals (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 3) {
    SEND_STRING("uaaau que engraçado merm~ao");
    reset_tap_dance(state);
  } else if (state->count == 4) {
    SEND_STRING("kkkkkk");
    reset_tap_dance(state);
  } else {
    register_code(KC_K);
    unregister_code(KC_K);
  }
}

void the_f_2_www (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
    SEND_STRING("2");
    reset_tap_dance(state);
  } else {
    register_code(KC_F);
    unregister_code(KC_F);
  }
}


qk_tap_dance_action_t tap_dance_actions[] = {

  // Tap B, 2x Ctrl+B
  [TD_B_TMUX]  = ACTION_TAP_DANCE_DOUBLE(KC_B, LCTL(KC_B)),

  // Tap KC_QUOTE, 2x Outputs "
  [TD_QT_DQT]  = ACTION_TAP_DANCE_FN(the_quote),

  // Tap J, 2x Underscore
  [TD_J_UNDS]  = ACTION_TAP_DANCE_DOUBLE(KC_J, KC_UNDS),

  // Tap K, 2x <SPACE>=<SPACE>
  [TD_K_EQL]  = ACTION_TAP_DANCE_FN(the_equals),

  [TD_Q_1] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_1),

  [TD_F_2] = ACTION_TAP_DANCE_FN(the_f_2_www),

  [TD_E_3] = ACTION_TAP_DANCE_DOUBLE(KC_E, KC_3)

  // Other declarations would go here, separated by commas, if you have them
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |B/TMUX|   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Lead | Alt  |GUI   |Lower |Spc_Tx|Enter |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_4x12(
  TAB_NP,   TD(TD_Q_1),    KC_W,    TD(TD_E_3),    KC_R,  KC_T,          KC_Y,     KC_U,          KC_I,         KC_O,    KC_P,    KC_BSPC,
  ESC_TX,   KC_A,    KC_S,    KC_D,    TD(TD_F_2),  KC_G,          KC_H,     TD(TD_J_UNDS), TD(TD_K_EQL), KC_L,    KC_SCLN, TD(TD_QT_DQT),
  KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,  TD(TD_B_TMUX), KC_N,     KC_M,          KC_COMM,      KC_DOT,  KC_SLSH, KC_RSFT,
  CTL_CAPS, KC_LEAD, KC_LALT, KC_LGUI, LOWER, KC_SPACE,        KC_ENTER, RAISE,         KC_LEFT,      KC_DOWN, KC_UP,   LCTL_T(KC_RGHT)
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   =  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_4x12(
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC,
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_EQL,     KC_LCBR, KC_RCBR, KC_PIPE,
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  _______,
  _______, _______, _______, _______, _______, _______, _______, _______,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   +  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |Pg Up |Pg Dn |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_4x12(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_PLUS,  KC_LBRC, KC_RBRC, KC_BSLS,
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |PSCR  |NUMPAD|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |r_RMOD|r_MOD |r_TOG |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_ortho_4x12(
  _______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, DF(_NUMPAD),
  _______, DYN_REC_START1, _______, _______, DYN_MACRO_PLAY1, _______, _______, _______, _______, _______, _______, _______,
  _______, DYN_REC_STOP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  VLK_TOG, _______, _______, _______, _______, _______, _______, _______, _______, RGB_RMOD, RGB_MOD, RGB_TOG
),

/* Text editing layer
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |Home  |Up    |End   |Pg Up |BLKSEL|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |Save  |Ctrl  |Shift |Alt   |      |Left  |Down  |Right |Pg Dn |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Undo  |Cut   |Copy  |Paste |      |      |      |      |Ins   |Del   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |Alt+En|      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_TEXT] = LAYOUT_ortho_4x12(
  TX_NEQ,  _______,    _______,    _______,    _______,    _______, _______,      KC_HOME, KC_UP,   KC_END,  KC_PGUP, BLKSEL,
  _______, _______,    LCTL(KC_S), KC_LCTL,    KC_LSFT,    KC_LALT, _______,      KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______,
  _______, LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), _______, _______,      _______, _______, KC_INS,  KC_DEL,  _______,
  _______, _______,    _______,    _______,    _______,    _______, LALT(KC_ENT), _______, _______, _______, _______, _______
),

/* Number Pad
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |  7   |  8   |  9   |  -   |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |  4   |  5   |  6   |  +   |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |  1   |  2   |  3   |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |QUERTY|      |      |      |      |      |ENTER |  0   |  .   |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMPAD] = LAYOUT_ortho_4x12(
  _______,     _______, KC_HOME, KC_UP,   KC_END,  _______, _______, KC_KP_7, KC_KP_8, KC_KP_9, KC_PMNS, _______,
  _______,     _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS, _______,
  _______,     _______, _______, _______, _______, _______, _______, KC_KP_1, KC_KP_2, KC_KP_3, _______, _______,
  DF(_QWERTY), _______, _______, _______, _______, _______, KC_PENT, KC_KP_0, KC_PDOT, _______, _______, _______
)


};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_dynamic_macro(keycode, record)) {
        return false;
    }

  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case TX_NEQ:
      if (record->event.pressed) {
        SEND_STRING("!= ");
      }
  }
  return true;
}

LEADER_EXTERNS();

void matrix_scan_user(void) {

  LEADER_DICTIONARY() {
    leading = false;

    SEQ_ONE_KEY(KC_Q) {
      SEND_STRING("1");
    }

    SEQ_ONE_KEY(KC_W) {
      SEND_STRING("2");
    }

    SEQ_ONE_KEY(KC_E) {
      SEND_STRING("3");
    }

    SEQ_ONE_KEY(KC_R) {
      SEND_STRING("4");
    }

    SEQ_TWO_KEYS(KC_W, KC_O) {
      SEND_STRING("quem e onde?"SS_TAP(X_ENTER));
    }

    leader_end();
  }
}

void leader_start() {
}

void leader_end() {
}