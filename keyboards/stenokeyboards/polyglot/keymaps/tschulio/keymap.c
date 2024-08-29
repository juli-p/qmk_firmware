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
#include "keymap_steno.h"

// layer declarations 
enum polyglot_layers {
    _CONTROL_LAYER,
    _QWERTZ_DE,
    _QWERTZ_NO,
    _NUM_LAYER,
    _SYM_LAYER,
    _STENO,
};

#define NUM_LAYER MO(_NUM_LAYER)
#define SYM_LAYER MO(_SYM_LAYER)
#define QWERTZ_DE DF(_QWERTZ_DE)
#define QWERTZ_NO DF(_QWERTZ_NO)
#define CONTROL_LAYER DF(_CONTROL_LAYER)
#define STENO DF(_STENO)

// tap dance declarations
enum {
    CTL_MV_SHFT,
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [CTL_MV_SHFT] = ACTION_TAP_DANCE_LAYER_MOVE(KC_LEFT_SHIFT, _CONTROL_LAYER),
};

// unicode declarations
enum unicode_names {
    NO_O_L,
    NO_O_U,
    NO_ae,
    NO_AE,
    NO_a,
    NO_A
};

const uint32_t PROGMEM unicode_map[] = {
    [NO_O_L]  = 0x00f8,
    [NO_O_U]  = 0x00d8,
    [NO_ae]  = 0x00c6,
    [NO_AE]  = 0x00e6,
    [NO_a]  = 0x00c5,
    [NO_A]  = 0x00e5,

};

#define NO_O UP(NO_O_L,NO_O_U)

// keymap definitions

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_CONTROL_LAYER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,QWERTZ_NO, QWERTZ_DE,                     XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,    STENO,                        XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                          XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                 XXXXXXX,UC_PREV,UC_NEXT,                       XXXXXXX,XXXXXXX,XXXXXXX
                                      //`--------------------------'  `--------------------------'

  ),

  [_QWERTZ_DE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_L, KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_COMM, KC_DOT,   KC_Z,    KC_X,    KC_C,    KC_V,                           KC_B,  KC_N,  KC_M, NO_O,  KC_L,   KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                 KC_LCTL,NUM_LAYER,CTL_MV_SHFT,       KC_SPC,SYM_LAYER,KC_LGUI
                                      //`--------------------------'  `--------------------------'

  ),

  [_QWERTZ_NO] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_LBRC, KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_COMM, KC_DOT,   KC_Z,    KC_X,    KC_C,    KC_V,                           KC_B,  KC_N,  KC_M, KC_SCLN,  KC_QUOT,   KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                 KC_LCTL,NUM_LAYER,CTL_MV_SHFT,       KC_SPC,SYM_LAYER,KC_LGUI
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

};

