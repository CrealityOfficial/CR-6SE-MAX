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
 * Einsy-Retro pin assignments
 */

<<<<<<< HEAD
#ifndef __AVR_ATmega2560__
  #error "Oops! Select 'Arduino Mega 2560 or Rambo' in 'Tools > Board.'"
#endif
=======
#include "env_validate.h"
>>>>>>> mcu_ctrl

#define BOARD_INFO_NAME "Einsy Retro"

//
// TMC2130 Configuration_adv defaults for EinsyRetro
//
#if !AXIS_DRIVER_TYPE_X(TMC2130) || !AXIS_DRIVER_TYPE_Y(TMC2130) || !AXIS_DRIVER_TYPE_Z(TMC2130) || !AXIS_DRIVER_TYPE_E0(TMC2130)
  #error "You must set ([XYZ]|E0)_DRIVER_TYPE to TMC2130 in Configuration.h for EinsyRetro."
#endif

<<<<<<< HEAD
// TMC2130 Diag Pins (currently just for reference)
#define X_DIAG_PIN         64
#define Y_DIAG_PIN         69
#define Z_DIAG_PIN         68
#define E0_DIAG_PIN        65
=======
// TMC2130 Diag Pins
#define X_DIAG_PIN                            64
#define Y_DIAG_PIN                            69
#define Z_DIAG_PIN                            68
#define E0_DIAG_PIN                           65
>>>>>>> mcu_ctrl

//
// Limit Switches
//
// Only use Diag Pins when SENSORLESS_HOMING is enabled for the TMC2130 drivers.
// Otherwise use a physical endstop based configuration.
//
// SERVO0_PIN and Z_MIN_PIN configuration for BLTOUCH sensor when combined with SENSORLESS_HOMING.
//

#if DISABLED(SENSORLESS_HOMING)

<<<<<<< HEAD
  #define X_MIN_PIN        12
  #define Y_MIN_PIN        11
  #define Z_MIN_PIN        10
  #define X_MAX_PIN        81
  #define Y_MAX_PIN        57

#else

  #if X_HOME_DIR < 0
    #define X_MIN_PIN      X_DIAG_PIN
    #define X_MAX_PIN      81
  #else
    #define X_MIN_PIN      12
    #define X_MAX_PIN      X_DIAG_PIN
  #endif

  #if Y_HOME_DIR < 0
    #define Y_MIN_PIN      Y_DIAG_PIN
    #define Y_MAX_PIN      57
  #else
    #define Y_MIN_PIN      11
    #define Y_MAX_PIN      Y_DIAG_PIN
  #endif

  #if ENABLED(BLTOUCH)
    #define Z_MIN_PIN      11   // Y-MIN
    #define SERVO0_PIN     10   // Z-MIN
  #else
    #define Z_MIN_PIN      10
=======
  #define X_MIN_PIN                           12  // X-
  #define Y_MIN_PIN                           11  // Y-
  #define Z_MIN_PIN                           10  // Z-
  #define X_MAX_PIN                           81  // X+
  #define Y_MAX_PIN                           57  // Y+

#else

  #if X_HOME_TO_MIN
    #define X_MIN_PIN                 X_DIAG_PIN
    #define X_MAX_PIN                         81  // X+
  #else
    #define X_MIN_PIN                         12  // X-
    #define X_MAX_PIN                 X_DIAG_PIN
  #endif

  #if Y_HOME_TO_MIN
    #define Y_MIN_PIN                 Y_DIAG_PIN
    #define Y_MAX_PIN                         57  // Y+
  #else
    #define Y_MIN_PIN                         11  // Y-
    #define Y_MAX_PIN                 Y_DIAG_PIN
  #endif

  #if ENABLED(BLTOUCH)
    #define Z_MIN_PIN                         11  // Y-MIN
    #define SERVO0_PIN                        10  // Z-MIN
  #else
    #define Z_MIN_PIN                         10
>>>>>>> mcu_ctrl
  #endif

#endif

<<<<<<< HEAD
#define Z_MAX_PIN           7
=======
#define Z_MAX_PIN                              7
>>>>>>> mcu_ctrl

//
// Z Probe (when not Z_MIN_PIN)
//
#ifndef Z_MIN_PROBE_PIN
<<<<<<< HEAD
  #define Z_MIN_PROBE_PIN  10
=======
  #define Z_MIN_PROBE_PIN                     10
>>>>>>> mcu_ctrl
#endif

//
// Steppers
//
<<<<<<< HEAD
#define X_STEP_PIN         37
#define X_DIR_PIN          49
#define X_ENABLE_PIN       29
#define X_CS_PIN           41

#define Y_STEP_PIN         36
#define Y_DIR_PIN          48
#define Y_ENABLE_PIN       28
#define Y_CS_PIN           39

#define Z_STEP_PIN         35
#define Z_DIR_PIN          47
#define Z_ENABLE_PIN       27
#define Z_CS_PIN           67

#define E0_STEP_PIN        34
#define E0_DIR_PIN         43
#define E0_ENABLE_PIN      26
#define E0_CS_PIN          66
=======
#define X_STEP_PIN                            37
#define X_DIR_PIN                             49
#define X_ENABLE_PIN                          29
#define X_CS_PIN                              41

#define Y_STEP_PIN                            36
#define Y_DIR_PIN                             48
#define Y_ENABLE_PIN                          28
#define Y_CS_PIN                              39

#define Z_STEP_PIN                            35
#define Z_DIR_PIN                             47
#define Z_ENABLE_PIN                          27
#define Z_CS_PIN                              67

#define E0_STEP_PIN                           34
#define E0_DIR_PIN                            43
#define E0_ENABLE_PIN                         26
#define E0_CS_PIN                             66
>>>>>>> mcu_ctrl

//
// Temperature Sensors
//
<<<<<<< HEAD
#define TEMP_0_PIN          0   // Analog Input
#define TEMP_1_PIN          1   // Analog Input
#define TEMP_BED_PIN        2   // Analog Input
=======
#define TEMP_0_PIN                             0  // Analog Input
#define TEMP_1_PIN                             1  // Analog Input
#define TEMP_BED_PIN                           2  // Analog Input
>>>>>>> mcu_ctrl

//
// Heaters / Fans
//
<<<<<<< HEAD
#define HEATER_0_PIN        3
#define HEATER_BED_PIN      4

#ifndef FAN_PIN
  #define FAN_PIN           8
#endif
#define FAN1_PIN            6
=======
#define HEATER_0_PIN                           3
#define HEATER_BED_PIN                         4

#ifndef FAN_PIN
  #define FAN_PIN                              8
#endif
#define FAN1_PIN                               6
>>>>>>> mcu_ctrl

//
// Misc. Functions
//
<<<<<<< HEAD
#define SDSS               53
#define LED_PIN            13
#define CASE_LIGHT_PIN      9
=======
#define SDSS                                  53
#define LED_PIN                               13

#ifndef CASE_LIGHT_PIN
  #define CASE_LIGHT_PIN                       9
#endif
>>>>>>> mcu_ctrl

//
// M3/M4/M5 - Spindle/Laser Control
//
// use P1 connector for spindle pins
<<<<<<< HEAD
#define SPINDLE_LASER_PWM_PIN     9   // Hardware PWM
#define SPINDLE_LASER_ENA_PIN    18   // Pullup!
#define SPINDLE_DIR_PIN          19
=======
#define SPINDLE_LASER_PWM_PIN                  9  // Hardware PWM
#define SPINDLE_LASER_ENA_PIN                 18  // Pullup!
#define SPINDLE_DIR_PIN                       19
>>>>>>> mcu_ctrl

//
// Průša i3 MK2 Multiplexer Support
//
<<<<<<< HEAD
#define E_MUX0_PIN         17
#define E_MUX1_PIN         16
#define E_MUX2_PIN         78   // 84 in MK2 Firmware, with BEEPER as 78
=======
#define E_MUX0_PIN                            17
#define E_MUX1_PIN                            16
#define E_MUX2_PIN                            78  // 84 in MK2 Firmware, with BEEPER as 78
>>>>>>> mcu_ctrl

//
// LCD / Controller
//
<<<<<<< HEAD
#if HAS_SPI_LCD || TOUCH_UI_ULTIPANEL || ENABLED(TOUCH_UI_FTDI_EVE)

  #define KILL_PIN         32

  #if ENABLED(ULTIPANEL) || TOUCH_UI_ULTIPANEL || ENABLED(TOUCH_UI_FTDI_EVE)

    #if ENABLED(CR10_STOCKDISPLAY)
      #define LCD_PINS_RS     85
      #define LCD_PINS_ENABLE 71
      #define LCD_PINS_D4     70
      #define BTN_EN1         18
      #define BTN_EN2         19
    #else
      #define LCD_PINS_RS     82
      #define LCD_PINS_ENABLE 18   // On 0.6b, use 61
      #define LCD_PINS_D4     19   // On 0.6b, use 59
      #define LCD_PINS_D5     70
      #define LCD_PINS_D6     85
      #define LCD_PINS_D7     71
      #define BTN_EN1         14
      #define BTN_EN2         72
    #endif

    #define BTN_ENC            9   // AUX-2
    #define BEEPER_PIN        84   // AUX-4

    #define SD_DETECT_PIN     15

  #endif // ULTIPANEL || TOUCH_UI_ULTIPANEL
#endif // HAS_SPI_LCD
=======
#if ANY(HAS_WIRED_LCD, TOUCH_UI_ULTIPANEL, TOUCH_UI_FTDI_EVE)

  #define KILL_PIN                            32

  #if ANY(IS_ULTIPANEL, TOUCH_UI_ULTIPANEL, TOUCH_UI_FTDI_EVE)

    #if ENABLED(CR10_STOCKDISPLAY)
      #define LCD_PINS_RS                     85
      #define LCD_PINS_ENABLE                 71
      #define LCD_PINS_D4                     70
      #define BTN_EN1                         18
      #define BTN_EN2                         19
    #else
      #define LCD_PINS_RS                     82
      #define LCD_PINS_ENABLE                 18  // On 0.6b, use 61
      #define LCD_PINS_D4                     19  // On 0.6b, use 59
      #define LCD_PINS_D5                     70
      #define LCD_PINS_D6                     85
      #define LCD_PINS_D7                     71
      #define BTN_EN1                         14
      #define BTN_EN2                         72
    #endif

    #define BTN_ENC                            9  // AUX-2
    #define BEEPER_PIN                        84  // AUX-4

    #define SD_DETECT_PIN                     15

    #if ENABLED(REPRAP_DISCOUNT_FULL_GRAPHIC_SMART_CONTROLLER)
      #define BTN_ENC_EN             LCD_PINS_D7  // Detect the presence of the encoder
    #endif

  #endif // IS_ULTIPANEL || TOUCH_UI_ULTIPANEL || TOUCH_UI_FTDI_EVE

#endif // HAS_WIRED_LCD || TOUCH_UI_ULTIPANEL || TOUCH_UI_FTDI_EVE
>>>>>>> mcu_ctrl
