/* Copyright 2019 Danny Nguyen <danny@keeb.io>
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

enum encoder_names {
  _LEFT,
  _RIGHT,
  _MIDDLE,
};

enum my_layers {
    _MUSIC = 0,
    _ZOOM,
    _LIGHTS
};

#define MUSIC  TO(_MUSIC)
#define ZOOM   TO(_ZOOM)
#define LIGHTS TO(_LIGHTS)

#define KC_ZMIC LCMD(S(KC_A))
#define KC_ZVID C(A(LCMD(KC_D)))
#define KC_ZCHAT C(A(LCMD(KC_C)))
#define KC_ZPAU C(A(LCMD(KC_T)))
#define KC_ZDUAL C(A(LCMD(KC_V)))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        Enjoying some tunes!
        # Top row:
        | Turn: Volume |               | Turn: Brightness |
        | Mute         | To Zoom layer | To Lights layer  |
        | Prev Track   | Play/Pause    | Next Track       |
        | ____________ | _____________ | Toggle LEDs      |
     */
    [_MUSIC] = LAYOUT(
        KC_MUTE,  ZOOM,    LIGHTS,
        KC_MPRV,  KC_MPLY, KC_MNXT,
        _______,  _______, RGB_TOG
    ),
    /*
        Time for a meeting
        # Top row:
        | Turn: Volume   |                  | Turn: Brightness |
        | Mute           | To Music layer   | To Lights layer  |
        | Show/Hide Chat | Pause Scrn Share | Dual Monitors    |
        | Zoom Mic Mute  | Zoom Camera      | Toggle LEDs      |
     */
    [_ZOOM] = LAYOUT(
        KC_MUTE,  MUSIC,   LIGHTS,
        KC_ZCHAT, KC_ZPAU, KC_ZDUAL,
        KC_ZMIC,  KC_ZVID, RGB_TOG
    ),
    /*
        Light layer!
        | Turn: Volume  |                | Turn: Brightness |
        | _____________ | To Music layer | To Zoom layer    |
        | Next pattern  | ______________ | Prev pattern     |
        | _____________ | ______________ | ________________ |
     */
    [_LIGHTS] = LAYOUT(
        XXXXXXX, MUSIC, ZOOM,
        RGB_RMOD,RGBLIGHT_MODE_RAINBOW_MOOD, RGB_MOD,
        XXXXXXX, XXXXXXX, XXXXXXX
    ),
};

bool encoder_update_user(uint8_t index, bool counter_clockwise) {
    if (index == _LEFT) {
        if (counter_clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    }
    else if (index == _MIDDLE) {
        if (counter_clockwise) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
        }
    }
    else if (index == _RIGHT) {
        if (counter_clockwise) {
            tap_code(KC_BRID);
        } else {
            tap_code(KC_BRIU);
        }
    }
    return false;
}
