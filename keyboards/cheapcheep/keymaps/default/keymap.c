#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = KEYMAP(
		KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_BSPC, 
		KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O, 
		KC_Z, KC_X, KC_C, KC_V, KC_B, KC_K, KC_M, KC_COMM, KC_DOT, KC_ENT, 
		KC_LCMD, KC_LALT, KC_LSFT, MO(1), KC_SPC, KC_SPC, MO(2), KC_RGUI, KC_RALT, KC_RCTL),

	[1] = KEYMAP(
		KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, 
		KC_ESC, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_LBRC, KC_RBRC, KC_QUOT, KC_SCLN, KC_TRNS, 
		KC_TAB, KC_DEL, KC_PSCR, KC_MINS, KC_EQL, KC_BSLS, KC_SLSH, KC_COMM, KC_DOT, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

	[2] = KEYMAP(
		KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, 
		KC_GRV, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_LCBR, KC_RCBR, KC_DQUO, KC_COLN, KC_TRNS, 
		KC_TRNS, KC_MPLY, KC_TRNS, KC_UNDS, KC_PLUS, KC_PIPE, KC_QUES, KC_LABK, KC_RABK, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

};


void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	return true;
}