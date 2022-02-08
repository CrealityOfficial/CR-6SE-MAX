/**
 * Marlin 3D Printer Firmware
<<<<<<< HEAD
 * Copyright (c) 2019 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
=======
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
>>>>>>> mcu_ctrl
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
<<<<<<< HEAD
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
=======
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
>>>>>>> mcu_ctrl
 *
 */

#include "../inc/MarlinConfig.h"

<<<<<<< HEAD
#if HAS_CASE_LIGHT

uint8_t case_light_brightness = CASE_LIGHT_DEFAULT_BRIGHTNESS;
bool case_light_on = CASE_LIGHT_DEFAULT_ON;

#if ENABLED(CASE_LIGHT_USE_NEOPIXEL)
  #include "leds/leds.h"
  LEDColor case_light_color =
    #ifdef CASE_LIGHT_NEOPIXEL_COLOR
      CASE_LIGHT_NEOPIXEL_COLOR
    #else
      { 255, 255, 255, 255 }
    #endif
  ;
#endif

/**
 * The following are needed because ARM chips ignore a "WRITE(CASE_LIGHT_PIN,x)" command to the pins that
 * are directly controlled by the PWM module. In order to turn them off the brightness level needs to be
 * set to off.  Since we can't use the pwm register to save the last brightness level we need a variable
 * to save it.
 */
uint8_t case_light_brightness_sav;   // saves brighness info so can restore when "M355 S1" received
bool case_light_arg_flag;  // flag to notify if S or P argument type

#ifndef INVERT_CASE_LIGHT
  #define INVERT_CASE_LIGHT false
#endif

void update_case_light() {

  if (!(case_light_arg_flag && !case_light_on))
    case_light_brightness_sav = case_light_brightness;  // save brightness except if this is an S0 argument
  if (case_light_arg_flag && case_light_on)
    case_light_brightness = case_light_brightness_sav;  // restore last brightens if this is an S1 argument

  const uint8_t i = case_light_on ? case_light_brightness : 0, n10ct = INVERT_CASE_LIGHT ? 255 - i : i;

  #if ENABLED(CASE_LIGHT_USE_NEOPIXEL)

    leds.set_color(
      MakeLEDColor(case_light_color.r, case_light_color.g, case_light_color.b, case_light_color.w, n10ct),
      false
    );

  #else // !CASE_LIGHT_USE_NEOPIXEL

    #if DISABLED(CASE_LIGHT_NO_BRIGHTNESS)
      if (PWM_PIN(CASE_LIGHT_PIN))
        analogWrite(pin_t(CASE_LIGHT_PIN),
=======
#if ENABLED(CASE_LIGHT_ENABLE)

#include "caselight.h"

CaseLight caselight;

#if CASELIGHT_USES_BRIGHTNESS && !defined(CASE_LIGHT_DEFAULT_BRIGHTNESS)
  #define CASE_LIGHT_DEFAULT_BRIGHTNESS 0 // For use on PWM pin as non-PWM just sets a default
#endif

#if CASELIGHT_USES_BRIGHTNESS
  uint8_t CaseLight::brightness = CASE_LIGHT_DEFAULT_BRIGHTNESS;
#endif

bool CaseLight::on = CASE_LIGHT_DEFAULT_ON;

#if CASE_LIGHT_IS_COLOR_LED
  #include "leds/leds.h"
  constexpr uint8_t init_case_light[] = CASE_LIGHT_DEFAULT_COLOR;
  LEDColor CaseLight::color = { init_case_light[0], init_case_light[1], init_case_light[2] OPTARG(HAS_WHITE_LED, init_case_light[3]) };
#endif

void CaseLight::update(const bool sflag) {
  #if CASELIGHT_USES_BRIGHTNESS
    /**
     * The brightness_sav (and sflag) is needed because ARM chips ignore
     * a "WRITE(CASE_LIGHT_PIN,x)" command to the pins that are directly
     * controlled by the PWM module. In order to turn them off the brightness
     * level needs to be set to OFF. Since we can't use the PWM register to
     * save the last brightness level we need a variable to save it.
     */
    static uint8_t brightness_sav;  // Save brightness info for restore on "M355 S1"

    if (on || !sflag)
      brightness_sav = brightness;  // Save brightness except for M355 S0
    if (sflag && on)
      brightness = brightness_sav;  // Restore last brightness for M355 S1

    const uint8_t i = on ? brightness : 0, n10ct = ENABLED(INVERT_CASE_LIGHT) ? 255 - i : i;
    UNUSED(n10ct);
  #endif

  #if CASE_LIGHT_IS_COLOR_LED
    leds.set_color(LEDColor(color.r, color.g, color.b OPTARG(HAS_WHITE_LED, color.w), n10ct));
  #else // !CASE_LIGHT_IS_COLOR_LED

    #if CASELIGHT_USES_BRIGHTNESS
      if (pin_is_pwm())
        analogWrite(pin_t(CASE_LIGHT_PIN), (
>>>>>>> mcu_ctrl
          #if CASE_LIGHT_MAX_PWM == 255
            n10ct
          #else
            map(n10ct, 0, 255, 0, CASE_LIGHT_MAX_PWM)
          #endif
<<<<<<< HEAD
        );
      else
    #endif
      {
        const bool s = case_light_on ? !INVERT_CASE_LIGHT : INVERT_CASE_LIGHT;
        WRITE(CASE_LIGHT_PIN, s ? HIGH : LOW);
      }

  #endif // !CASE_LIGHT_USE_NEOPIXEL
}

#endif // HAS_CASE_LIGHT
=======
        ));
      else
    #endif
      {
        const bool s = on ? TERN(INVERT_CASE_LIGHT, LOW, HIGH) : TERN(INVERT_CASE_LIGHT, HIGH, LOW);
        WRITE(CASE_LIGHT_PIN, s ? HIGH : LOW);
      }

  #endif // !CASE_LIGHT_IS_COLOR_LED

  #if ENABLED(CASE_LIGHT_USE_RGB_LED)
    if (leds.lights_on) leds.update(); else leds.set_off();
  #endif
}

#endif // CASE_LIGHT_ENABLE
>>>>>>> mcu_ctrl
