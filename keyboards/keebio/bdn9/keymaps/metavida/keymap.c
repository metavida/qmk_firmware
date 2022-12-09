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

#define TO_MUSIC  TO(_MUSIC)
#define TO_ZOOM   TO(_ZOOM)
#define TO_LIGHTS TO(_LIGHTS)

// Each of the following is configured
// as a global shortcut in the Zoom app.
#define KC_ZMIC LCMD(S(KC_A))     // Toggle microphone mute
#define KC_ZVID C(A(LCMD(KC_D)))  // Toggle video
#define KC_ZCHAT C(A(LCMD(KC_C))) // Show/Hide chat
#define KC_ZPAU C(A(LCMD(KC_T)))  // Pause/Play Screen Share
#define KC_ZDUAL C(A(LCMD(KC_V))) // Toggle Dual Monitor mode

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_MUSIC] = LAYOUT(
  //    Enjoying some tunes!
  //  ⸝───────⸜          ⸝───────⸜
  // ⎸ KC_VOL* ⎹         ⎸ KC_BRI* ⎹
  // ┌────────┬────────┬─────────┐
      KC_MUTE, TO_ZOOM, TO_LIGHTS,
  // ├────────┼────────┼─────────┤
  //   Prev    Play/Pau   Next
      KC_MPRV, KC_MPLY, KC_MNXT,
  // ├────────┼────────┼─────────┤
      _______, _______, RGB_TOG
  // └────────┴────────┴─────────┘
  ),
  [_ZOOM] = LAYOUT(
  //     Time for a meeting
  //  ⸝───────⸜           ⸝────────⸜
  // ⎸ KC_VOL* ⎹          ⎸ KC_BRI*  ⎹
  // ┌─────────┬─────────┬─────────┐
      KC_MUTE,  TO_MUSIC, TO_LIGHTS,
  // ├─────────┼─────────┼─────────┤
      KC_ZCHAT, KC_ZPAU,  KC_ZDUAL,
  // ├─────────┼─────────┼─────────┤
      KC_ZMIC,  KC_ZVID,  RGB_TOG
  // └─────────┴─────────┴─────────┘
  ),
  [_LIGHTS] = LAYOUT(
  //     Light layer!
  //  ⸝───────⸜           ⸝────────⸜
  // ⎸ RBG hue ⎹          ⎸ RGB sat  ⎹
  // ┌─────────┬─────────┬─────────┐
      _______,  TO_MUSIC, TO_ZOOM,
  // ├─────────┼─────────┼─────────┤
  //   Next                Prev
      RGB_RMOD, _______,  RGB_MOD,
  // ├─────────┼─────────┼─────────┤
      _______,  _______,  _______
  // └─────────┴─────────┴─────────┘
  ),
};

bool music_mode = false;
bool zoom_mode = false;
bool lights_mode = false;
bool base_mode = false;

layer_state_t layer_state_set_user(layer_state_t state) {
  music_mode = false;
  zoom_mode = false;
  lights_mode = false;
  base_mode = false;

  switch (get_highest_layer(state)) {
    case _MUSIC:
      music_mode = true; // For use in encoder evaluation
      rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
      rgblight_sethsv_noeeprom(HSV_CHARTREUSE);
      break;
    case _ZOOM:
      zoom_mode = true; // For use in encoder evaluation
      rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
      rgblight_sethsv_noeeprom(HSV_BLUE);
      break;
    case _LIGHTS:
      lights_mode = true; // For use in encoder evaluation
      rgblight_mode_noeeprom(RGBLIGHT_MODE_TWINKLE);
      rgblight_sethsv_noeeprom(HSV_ORANGE);
      break;
    default: //  for any other layers, or the default layer
      base_mode = true;
      rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
      rgblight_sethsv_noeeprom(HSV_RED);
      break;
  }
  return state;
}

void keyboard_post_init_user(void) {
  // Call the post init code.
  rgblight_enable_noeeprom(); // enables Rgb, without saving settings
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT); // to static light without saving
  rgblight_sethsv_noeeprom(HSV_CHARTREUSE);
}

bool encoder_update_user(uint8_t index, bool counter_clockwise) {
  if(lights_mode == true) {
    if (index == _LEFT) {
      if (counter_clockwise) {
        rgblight_increase_hue();
      } else {
        rgblight_decrease_hue();
      }
    }
    else if (index == _RIGHT) {
      if (counter_clockwise) {
        rgblight_increase_sat();
      } else {
        rgblight_decrease_sat();
      }
    }
  } else {
    if (index == _LEFT) {
      if (counter_clockwise) {
        tap_code(KC_VOLD);
      } else {
        tap_code(KC_VOLU);
      }
    }
    else if (index == _RIGHT) {
      if (counter_clockwise) {
        tap_code(KC_BRID);
      } else {
        tap_code(KC_BRIU);
      }
    }
  }
  return false;
}
