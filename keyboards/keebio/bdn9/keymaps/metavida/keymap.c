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

#define KC_ZMIC LCMD(S(KC_A))
#define KC_ZVID C(A(LCMD(KC_D)))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        Default layer, for common tasks.
        # Top row:
        | Turn: Volume  |               | Turn: Brightness |
        | Mute          | Hold: Layer 2 | Toggle LEDs      |
        # Row 2:
        | Prev Track    | Play/Pause    | Next Track       |
        # Row 3:
        | Zoom Mic Mute | Zoom Camera   | Toggle LEDs      |
     */
    [0] = LAYOUT(
        KC_MUTE,  MO(1),    RGB_TOG,
        KC_MPRV,  KC_MPLY,  KC_MNXT,
        KC_ZMIC,  KC_ZVID, RGB_TOG
    ),
    /*
        Light layer!
        Initially stolen from the brandonschlack keymap
     */
    [1] = LAYOUT(
        XXXXXXX, XXXXXXX, RGB_HUI,
        RGB_RMOD,RGBLIGHT_MODE_RAINBOW_MOOD, RGB_MOD,
        RGBLIGHT_MODE_STATIC_GRADIENT, RGBLIGHT_MODE_KNIGHT, RGBLIGHT_MODE_RAINBOW_SWIRL
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
