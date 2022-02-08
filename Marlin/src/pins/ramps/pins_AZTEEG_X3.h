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
#pragma once

/**
 * AZTEEG_X3 Arduino Mega with RAMPS v1.4 pin assignments
 */

<<<<<<< HEAD
#ifndef __AVR_ATmega2560__
  #error "Oops! Select 'Arduino/Genuino Mega or Mega 2560' in 'Tools > Board.'"
#elif HOTENDS > 2 || E_STEPPERS > 2
=======
#define REQUIRE_MEGA2560
#include "env_validate.h"

#if HOTENDS > 2 || E_STEPPERS > 2
>>>>>>> mcu_ctrl
  #error "Azteeg X3 supports up to 2 hotends / E-steppers. Comment out this line to continue."
#endif

#if ENABLED(CASE_LIGHT_ENABLE) && !PIN_EXISTS(CASE_LIGHT)
<<<<<<< HEAD
  #define CASE_LIGHT_PIN    6   // Define before RAMPS pins include
=======
  #define CASE_LIGHT_PIN                       6  // Define before RAMPS pins include
>>>>>>> mcu_ctrl
#endif
#define BOARD_INFO_NAME "Azteeg X3"

//
// Servos
//
<<<<<<< HEAD
#define SERVO0_PIN         44   // SERVO1 port
#define SERVO1_PIN         55   // SERVO2 port
=======
#define SERVO0_PIN                            44  // SERVO1 port
#define SERVO1_PIN                            55  // SERVO2 port
>>>>>>> mcu_ctrl

#include "pins_RAMPS_13.h"

//
// LCD / Controller
//
#undef STAT_LED_RED_PIN
#undef STAT_LED_BLUE_PIN

#if ANY(VIKI2, miniVIKI)

  #undef DOGLCD_A0
  #undef DOGLCD_CS
  #undef BTN_ENC
<<<<<<< HEAD
  #define DOGLCD_A0         31
  #define DOGLCD_CS         32
  #define BTN_ENC           12

  #define STAT_LED_RED_PIN  64
  #define STAT_LED_BLUE_PIN 63

#else

  #define STAT_LED_RED_PIN   6
  #define STAT_LED_BLUE_PIN 11
=======
  #define DOGLCD_A0                           31
  #define DOGLCD_CS                           32
  #define BTN_ENC                             12

  #define STAT_LED_RED_PIN                    64
  #define STAT_LED_BLUE_PIN                   63

#else

  #define STAT_LED_RED_PIN                     6
  #define STAT_LED_BLUE_PIN                   11
>>>>>>> mcu_ctrl

#endif

//
// Misc
//
<<<<<<< HEAD
#if ENABLED(CASE_LIGHT_ENABLE) && PIN_EXISTS(CASE_LIGHT, STAT_LED_RED) && STAT_LED_RED_PIN == CASE_LIGHT_PIN
=======
#if ENABLED(CASE_LIGHT_ENABLE) && PINS_EXIST(CASE_LIGHT, STAT_LED_RED) && STAT_LED_RED_PIN == CASE_LIGHT_PIN
>>>>>>> mcu_ctrl
  #undef STAT_LED_RED_PIN
#endif

//
// M3/M4/M5 - Spindle/Laser Control
//
<<<<<<< HEAD
#undef SPINDLE_LASER_PWM_PIN    // Definitions in pins_RAMPS.h are no good with the AzteegX3 board
=======
#undef SPINDLE_LASER_PWM_PIN                      // Definitions in pins_RAMPS.h are no good with the AzteegX3 board
>>>>>>> mcu_ctrl
#undef SPINDLE_LASER_ENA_PIN
#undef SPINDLE_DIR_PIN

#if HAS_CUTTER
<<<<<<< HEAD
  #undef SDA                       // use EXP3 header
  #undef SCL
  #if SERVO0_PIN == 7
    #undef SERVO0_PIN
    #define SERVO0_PIN     11
  #endif
  #define SPINDLE_LASER_PWM_PIN     7   // Hardware PWM
  #define SPINDLE_LASER_ENA_PIN    20   // Pullup!
  #define SPINDLE_DIR_PIN          21
=======
  #undef SDA                                      // use EXP3 header
  #undef SCL
  #if SERVO0_PIN == 7
    #undef SERVO0_PIN
    #define SERVO0_PIN                        11
  #endif
  #define SPINDLE_LASER_PWM_PIN                7  // Hardware PWM
  #define SPINDLE_LASER_ENA_PIN               20  // Pullup!
  #define SPINDLE_DIR_PIN                     21
>>>>>>> mcu_ctrl
#endif
