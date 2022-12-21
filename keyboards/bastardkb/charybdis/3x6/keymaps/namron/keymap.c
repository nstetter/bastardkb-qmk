/**
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
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
#include "namron.h"

// enum charybdis_keymap_layers {
//     _COLEMAK = 0,
//     _MAC,
//     _NAV,
//     _MOUSE,
//     _FN
// };


// auto-mouse: https://github.com/qmk/qmk_firmware/pull/17962

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAK] = LAYOUT_charybdis_3x6(
  // ╭───────────┬───────────┬───────────┬───────────┬───────────┬───────────╮ ╭───────────┬───────────┬───────────┬───────────┬───────────┬───────────╮
       KC_LGUI,   KC_Q,       KC_W,       KC_F,       KC_P,       KC_B,         KC_J,       KC_L,       KC_U,       KC_Y,       KC_SCLN,    KC_EQL,
  // ├───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤ ├───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤
       KC_TAB,    KC_A,       KC_R,       KC_S,       KC_T,       KC_G,         KC_M,       KC_N,       KC_E,       KC_I,       KC_O,       KC_QUOTE,
  // ├───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤ ├───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤
       KC_BSLS,   KC_Z,       KC_X,       KC_C,       KC_D,       KC_V,         KC_K,       KC_H,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_MINS,
  // ╰───────────┴───────────┴───────────┼───────────┼───────────┼───────────┤ ├───────────┴───────────┴───────────┴───────────┴───────────┴───────────╯
                                          SP_CTL,     SP_SHBS,    SP_SUENT,     SP_ALTESC,  SP_NAV
  //                                     ╰───────────┴───────────┴───────────╯ ╰───────────┴───────────╯
  ),

  [_MAC] = LAYOUT_charybdis_3x6(
  // ╭───────────┬───────────┬───────────┬───────────┬───────────┬───────────╮ ╭───────────┬───────────┬───────────┬───────────┬───────────┬───────────╮
       _______,   _______,    _______,    _______,    _______,    _______,      _______,    _______,    _______,    _______,    _______,    _______,
  // ├───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤ ├───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤
       _______,   _______,    _______,    _______,    _______,    _______,      _______,    _______,    _______,    _______,    _______,    _______,
  // ├───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤ ├───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤
       _______,   _______,    _______,    _______,    _______,    _______,      _______,    _______,    _______,    _______,    _______,    _______,
  // ╰───────────┴───────────┴───────────┼───────────┼───────────┼───────────┤ ├───────────┴───────────┴───────────┴───────────┴───────────┴───────────╯
                                          MC_CMD,     _______,    MC_CTLEN,     _______,    _______
  //                                     ╰───────────┴───────────┴───────────╯ ╰───────────┴───────────╯
  ),

  [_NAV] = LAYOUT_charybdis_3x6(
  // ╭───────────┬───────────┬───────────┬───────────┬───────────┬───────────╮ ╭───────────┬───────────┬───────────┬───────────┬───────────┬───────────╮
       KC_NO,     KC_PGUP,    KC_HOME,    KC_UP,      KC_END,     KC_LCBR,      KC_RCBR,    KC_7,       KC_8,       KC_9,       KC_NO,      QK_BOOT,
  // ├───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤ ├───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤
       KC_NO,     KC_PGDN,    KC_LEFT,    KC_DOWN,    KC_RIGHT,   KC_LPRN,      KC_RPRN,    KC_4,       KC_5,       KC_6,       KC_BSPC,    KC_DEL,
  // ├───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤ ├───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤
       ND_GRV,    KC_WH_U,    KC_WH_D,    SP_ASPC,    SP_ATAB,    KC_LBRC,      KC_RBRC,    KC_1,       KC_2,       KC_3,       KC_0,       KC_NO,
  // ╰───────────┴───────────┴───────────┼───────────┼───────────┼───────────┤ ├───────────┴───────────┴───────────┴───────────┴───────────┴───────────╯
                                          _______,    MO(_FN),    XXXXXXX,      _______,    XXXXXXX
  //                                     ╰───────────┴───────────┴───────────╯ ╰───────────┴───────────╯
  ),

  [_MOUSE] = LAYOUT_charybdis_3x6(
  // ╭───────────┬───────────┬───────────┬───────────┬───────────┬───────────╮ ╭───────────┬───────────┬───────────┬───────────┬───────────┬───────────╮
       KC_NO,     KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,        KC_NO,      KC_NO,      DRG_TOG,    KC_NO,      KC_NO,      KC_NO,  
  // ├───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤ ├───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤
       KC_NO,     KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,        KC_NO,      KC_MS_BTN1, KC_MS_BTN2, KC_MS_BTN3, KC_MS_BTN8, KC_NO,  
  // ├───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤ ├───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤
       KC_NO,     KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,        KC_NO,      KC_NO,      SNP_TOG,    KC_NO,      KC_NO,      KC_NO,  
  // ╰───────────┴───────────┴───────────┼───────────┼───────────┼───────────┤ ├───────────┴───────────┴───────────┴───────────┴───────────┴───────────╯
                                          KC_NO,      KC_NO,      KC_NO,        KC_NO,      KC_NO
  //                                     ╰───────────┴───────────┴───────────╯ ╰───────────┴───────────╯
  ),

  [_FN] = LAYOUT_charybdis_3x6(
  // ╭───────────┬───────────┬───────────┬───────────┬───────────┬───────────╮ ╭───────────┬───────────┬───────────┬───────────┬───────────┬───────────╮
       KC_SLEP,   KC_PWR,     KC_NO,      KC_NO,      KC_NO,      KC_NO,        KC_NO,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     RGB_MOD,
  // ├───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤ ├───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤
       TG_DFT,    KC_NO,      KC_WBAK,    KC_NO,      KC_WFWD,    KC_NO,        KC_NO,      KC_F4,      KC_F5,      KC_F6,      KC_F11,     KC_NO,
  // ├───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤ ├───────────┼───────────┼───────────┼───────────┼───────────┼───────────┤
       KC_NO,     KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,        KC_NO,      KC_F1,      KC_F2,      KC_F3,      KC_F12,     KC_NO,
  // ╰───────────┴───────────┴───────────┼───────────┼───────────┼───────────┤ ├───────────┴───────────┴───────────┴───────────┴───────────┴───────────╯
                                          _______,    _______,    XXXXXXX,      _______,    XXXXXXX
  //                                     ╰───────────┴───────────┴───────────╯ ╰───────────┴───────────╯
  ),
};
// clang-format on



/* -------------------------------------------------------------------------- */
/*                                  RGB MATRIX                                */
/* -------------------------------------------------------------------------- */
//https://docs.qmk.fm/#/feature_rgb_matrix?id=functions
#define DEFAULT_BRIGHTNESS 80
#define DEFAULT_RGB_MATRIX_MODE RGB_MATRIX_BREATHING

//run at the end of the firmware's startup process
void keyboard_post_init_user(void) {
    rgb_matrix_enable_noeeprom();
//     rgb_matrix_sethsv_noeeprom(HSV_TEAL);
    rgb_matrix_mode_noeeprom(RGB_MATRIX_BREATHING);
    rgb_matrix_set_speed_noeeprom(70);
}

// layer indicators https://docs.qmk.fm/#/feature_rgb_matrix?id=indicator-examples
bool rgb_matrix_indicators_kb(void) {
     switch(get_highest_layer(layer_state|default_layer_state)) {
          case _MOUSE:
               // rgb_matrix_mode_noeeprom(DEFAULT_RGB_MATRIX_MODE);
               rgb_matrix_sethsv_noeeprom(HSV_BLUE);
               break;
          case _FN:
               // rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
               rgb_matrix_sethsv_noeeprom(HSV_YELLOW);
               break;
          case _NAV:
               // rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
               rgb_matrix_sethsv_noeeprom(HSV_GREEN);
               break;
          case _MAC:
               // rgb_matrix_mode_noeeprom(DEFAULT_RGB_MATRIX_MODE);
               rgb_matrix_sethsv_noeeprom(HSV_WHITE);
               break;
          case _COLEMAK:
               // rgb_matrix_mode_noeeprom(DEFAULT_RGB_MATRIX_MODE);
               rgb_matrix_sethsv_noeeprom(HSV_TEAL);
               break;
          default:
               break;
     }
return false;
}
