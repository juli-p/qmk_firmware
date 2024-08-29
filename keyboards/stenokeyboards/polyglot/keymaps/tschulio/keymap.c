/*
Copyright 2023 StenoKeyboards

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
// #include "keymap_steno.h"

// layer declarations 
enum polyglot_layers {
    _QWERTZ_DE,
    _QWERTZ_NO,
    _NUM_LAYER,
    _SYM_LAYER,
    _STENO,
    _CONTROL_LAYER,
};

#define NUM_LAYER MO(_NUM_LAYER)
#define SYM_LAYER MO(_SYM_LAYER)
#define QWERTZ_DE DF(_QWERTZ_DE)
#define QWERTZ_NO DF(_QWERTZ_NO)
#define CONTROL_LAYER TG(_CONTROL_LAYER)
#define STENO DF(_STENO)

// tap dance declarations
enum {
    TD_MV_CTRL,
    TD_ESC_ALT
};

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data);
void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data);

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

tap_dance_action_t tap_dance_actions[] = {
    // [CTL_MV_SHFT] = ACTION_TAP_DANCE_LAYER_MOVE(KC_LEFT_SHIFT, _CONTROL_LAYER),
    // [CTL_MV_SHFT] = ACTION_TAP_DANCE_TAP_HOLD(KC_LEFT_SHIFT, CONTROL_LAYER),
    [TD_MV_CTRL] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_LCTL, _CONTROL_LAYER),
    [TD_ESC_ALT] = ACTION_TAP_DANCE_TAP_HOLD(KC_ESC, KC_LALT)
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;

    switch (keycode) {
        case TD(TD_ESC_ALT):  // list all tap dance keycodes with tap-hold configurations
            action = &tap_dance_actions[QK_TAP_DANCE_GET_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
    }
    return true;
}

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}


// unicode declarations
enum unicode_names {
    NO_O_LOWER,
    NO_O_UPPER,
    NO_AE_LOWER,
    NO_AE_UPPER,
    NO_A_LOWER,
    NO_A_UPPER
};

const uint32_t PROGMEM unicode_map[] = {
    [NO_O_LOWER]   = 0x00f8,
    [NO_O_UPPER]   = 0x00d8,
    [NO_AE_LOWER]  = 0x00e6,
    [NO_AE_UPPER]  = 0x00c6,
    [NO_A_LOWER]   = 0x00e5,
    [NO_A_UPPER]   = 0x00c5,

};

#define NO_O UP(NO_O_LOWER,NO_O_UPPER)
#define NO_AE UP(NO_AE_LOWER,NO_AE_UPPER)
#define NO_A UP(NO_A_LOWER,NO_A_UPPER)

// keymap definitions

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTZ_DE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       TD(TD_ESC_ALT),    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_LBRC, KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_COMM, KC_DOT,   KC_Z,    KC_X,    KC_C,    KC_V,                           KC_B,  KC_N,  KC_M, KC_SCLN,  KC_QUOT,   KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                 TD(TD_MV_CTRL),NUM_LAYER,KC_LEFT_SHIFT,       KC_SPC,SYM_LAYER,KC_LGUI
                                      //`--------------------------'  `--------------------------'

  ),

  [_QWERTZ_NO] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     TD(TD_ESC_ALT),    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, NO_A, KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_COMM, KC_DOT,   KC_Z,    KC_X,    KC_C,    KC_V,                           KC_B,  KC_N,  KC_M, NO_O,  NO_AE,   KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                 TD(TD_MV_CTRL),NUM_LAYER,KC_LEFT_SHIFT,       KC_SPC,SYM_LAYER,KC_LGUI
                                      //`--------------------------'  `--------------------------'

  ),


  [_NUM_LAYER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
   _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    S(KC_2),   S(KC_8), S(KC_9), RALT(KC_8),  RALT(KC_9), S(KC_7),              KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, RALT(KC_NUBS), _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      S(KC_NUHS), KC_NUBS,S(KC_NUBS), RALT(KC_7), RALT(KC_0), RALT(KC_MINS),          S(KC_0), KC_RBRC, S(KC_RBRC), KC_NUHS, S(KC_6), KC_LALT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                _______, _______, _______,                      _______, XXXXXXX, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_SYM_LAYER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     _______,  KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F6,    KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,RALT(KC_Q),KC_MINS,RALT(KC_E),S(KC_5), S(KC_1),                   KC_LEFT,  KC_DOWN,   KC_UP,KC_RIGHT, KC_HOME,  KC_END,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_F12,  KC_GRV, S(KC_3), S(KC_4), RALT(KC_RBRC), S(KC_MINS),            KC_EQL, RALT(KC_EQL), KC_SLSH, S(KC_SLSH), KC_PSCR, KC_LALT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______,XXXXXXX, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

   [_STENO] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1, 					  STN_ST3, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       XXXXXXX, STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2, 					 STN_ST4,  STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      CONTROL_LAYER,  KC_LSFT,  KC_LCTL,  KC_LALT,  KC_LCMD,  KC_SPC,    			      KC_LEFT, KC_DOWN, KC_UP ,KC_RIGHT,  XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                   STN_N1,  STN_A,   STN_O,                       STN_E,   STN_U, STN_N2
                                       //`--------------------------'  `--------------------------'

   ),

  [_CONTROL_LAYER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     TG(_CONTROL_LAYER),XXXXXXX,XXXXXXX,XXXXXXX,QWERTZ_NO, QWERTZ_DE,                     XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,    STENO,                        XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                          XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                 XXXXXXX,UC_PREV,UC_NEXT,                       XXXXXXX,XXXXXXX,XXXXXXX
                                      //`--------------------------'  `--------------------------'

  ),

};

