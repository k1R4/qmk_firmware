/* Copyright 2020 Richard Titmuss (richard.titmuss@gmail.com)
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

enum torn_layers { _DVORAK, _QWERTY, _LOWER, _RAISE, _ADJUST };

#define USB_POLLING_INTERVAL_MS    1
#define MOUSEKEY_TIME_TO_MAX       40

#define LWR           MO(_LOWER)
#define RSE           MO(_RAISE)
#define QWRT          TG(_QWERTY)
#define KC_MUT        KC_KB_MUTE
#define WM(key)       RGUI(key)
#define UND           LCTL(KC_Z)
#define CUT           LCTL(KC_X)
#define CPY           LCTL(KC_C)
#define PST           LCTL(KC_V)
#define SAV           LCTL(KC_S)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Dvorak
 * ,-----------------------------------------.    ,-----------------------------------------.
 * | Esc  |   '  |   ,  |   .  |   P  |   Y  |    |   F  |   G  |   C  |   R  |   L  |  /   |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * | Shft |   A  |   O  |   E  |   U  |   I  |    |   D  |   H  |   T  |   N  |   S  |  -   |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * | Ctrl |   ;  |   Q  |   J  |   K  |   X  |    |   B  |   M  |   W  |   V  |   Z  |  =   |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 *               |Lower | LGui | Bksp | Spce |    | Mute |Enter | Tab  |Raise |
 *               |      |      |      |      |    |      |      |      |      |
 *               `---------------------------'    `---------------------------'
 */
[_DVORAK] = LAYOUT_split_3x6_4(
    KC_ESC,   KC_QUOT,  KC_COMM,   KC_DOT,  KC_P,    KC_Y,      KC_F,    KC_G,    KC_C,    KC_R,    KC_L,   KC_SLSH,
    KC_LSFT,  KC_A,     KC_O,      KC_E,    KC_U,    KC_I,      KC_D,    KC_H,    KC_T,    KC_N,    KC_S,   KC_MINS,
    KC_LCTL,  KC_SCLN,  KC_Q,      KC_J,    KC_K,    KC_X,      KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,   KC_EQL,
                        LWR,       KC_LGUI, KC_BSPC, KC_SPC,    KC_MUT,  KC_ENT,  KC_TAB,  RSE
),

/* Lower
 * ,-----------------------------------------.    ,-----------------------------------------.
 * | Esc  |   !  |   @  |   #  |   $  |   %  |    |   ^  |   &  |   *  |   (  |   )  |  `   |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * | Shft |   1  |   2  |   3  |   4  |   5  |    |   6  |   7  |   8  |   9  |   0  |  ~   |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * | Ctrl | Undo |  Cut | Copy |Paste | Save |    |   |  |   [  |   ]  |   {  |   }  |  \   |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 *               |Lower | LGui | Bksp | Spce |    | Mute |Enter | Tab  |Raise |
 *               |      |      |      |      |    |      |      |      |      |
 *               `---------------------------'    `---------------------------'
 */
[_LOWER] = LAYOUT_split_3x6_4(
    _______,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_GRV,
    _______,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_TILD,
    _______,  UND,     CUT,     CPY,     PST,     SAV,       KC_PIPE, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, KC_BSLS,
                      _______, _______, _______, _______,   _______, _______, _______, _______
),

/* Raise
 * ,-----------------------------------------.    ,-----------------------------------------.
 * | Esc  |  F4  |  F5  |  F8  |  F10 |  F11 |    |Lftclk|Ms Lft|Ms Dwn|Ms Up |Ms Rgt|Rgtclk|
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * | Shft |  W1  |  W2  |  W3  |  W4  |  W5  |    | Boot | Left | Down |  Up  |Right |  -   |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * | Ctrl |  W6  |  W7  |  W8  |  W9  |Qwerty|    |   |  |   [  |   ]  |   {  |   }  |  =   |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 *               |Lower | LGui | Bksp | Spce |    | Mute |Enter | Tab  |Raise |
 *               |      |      |      |      |    |      |      |      |      |
 *               `---------------------------'    `---------------------------'
 */
[_RAISE] = LAYOUT_split_3x6_4(
    _______, KC_F4,    KC_F5,    KC_F8,    KC_F10,    KC_F11,   KC_BTN1, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_BTN2,
    _______, WM(KC_1), WM(KC_2), WM(KC_3), WM(KC_4), WM(KC_5),  QK_BOOT, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,
    _______, WM(KC_6), WM(KC_7), WM(KC_8), WM(KC_9), QWRT,      KC_PIPE, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, _______,
                      _______, _______, _______, _______,       _______, _______, _______, _______
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------.    ,-----------------------------------------.
 * |      |      |      |      |      |      |    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 *               |      |      |      |      |    |      |      |      |      |
 *               |      |      |      |      |    |      |      |      |      |
 *               `---------------------------'    `---------------------------'
 */
[_ADJUST] = LAYOUT_split_3x6_4(
    _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______,
                      _______, _______, _______, _______,   _______, _______, _______, _______
),

/* Owerty
 * ,-----------------------------------------.    ,-----------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |    |   Y  |   U  |   I  |   O  |   P  |  [   |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * | Shft |   A  |   S  |   D  |   F  |   G  |    |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * | Ctrl |   Z  |   X  |   C  |   V  |   B  |    |   N  |   M  |   ,  |   .  |   /  |  ]   |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 *               |Lower | LGui | Bksp | Spce |    | Mute |Enter | Tab  |Raise |
 *               |      |      |      |      |    |      |      |      |      |
 *               `---------------------------'    `---------------------------'
 */
[_QWERTY] = LAYOUT_split_3x6_4(
    KC_ESC,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
    KC_LSFT,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LCTL,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RBRC,
                       LWR,     KC_LGUI, KC_BSPC, KC_SPC,    KC_MUT,  KC_ENT,  KC_RGUI, RSE
)

};

const uint16_t PROGMEM encoder_keymaps[][2][2] = {
    [_DVORAK] =  { { KC_NO, KC_NO }, { KC_WH_D, KC_WH_U } },
    [_LOWER]  =  { { KC_NO, KC_NO }, { WM(KC_COMM), WM(KC_DOT) } },
    [_RAISE]  =  { { KC_NO, KC_NO }, { KC_VOLD, KC_VOLU } },
    [_ADJUST] =  { { KC_NO, KC_NO }, { KC_PGDN, KC_PGUP } },
    [_QWERTY] =  { { KC_NO, KC_NO }, { KC_WH_D, KC_WH_U } }
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    torn_set_led(2, IS_LAYER_ON_STATE(state, _QWERTY));
    torn_set_led(1, IS_LAYER_ON_STATE(state, _RAISE));
    torn_set_led(0, IS_LAYER_ON_STATE(state, _LOWER));
    return state;
}
