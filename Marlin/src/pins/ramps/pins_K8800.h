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
 * Velleman K8800 (Vertex)
 */

<<<<<<< HEAD
#if !defined(__AVR_ATmega1280__) && !defined(__AVR_ATmega2560__)
  #error "Oops! Select 'Arduino/Genuino Mega or Mega 2560' in 'Tools > Board.'"
#endif
=======
#include "env_validate.h"
>>>>>>> mcu_ctrl

#define BOARD_INFO_NAME      "K8800"
#define DEFAULT_MACHINE_NAME "Vertex Delta"

//#define LCD_SCREEN_ROT_180

//
// Limit Switches
//
<<<<<<< HEAD
#define X_STOP_PIN          3
#define Y_STOP_PIN         14
#define Z_MIN_PIN          68  // Used for bed leveling
#define Z_MAX_PIN          66
=======
#define X_STOP_PIN                             3
#define Y_STOP_PIN                            14
#define Z_STOP_PIN                            66

#ifndef Z_MIN_PROBE_PIN
  #define Z_MIN_PROBE_PIN                     68
#endif

#define FIL_RUNOUT_PIN                        69  // PK7
>>>>>>> mcu_ctrl

//
// Steppers
//
<<<<<<< HEAD
#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       63

#define E0_STEP_PIN        26
#define E0_DIR_PIN         28
#define E0_ENABLE_PIN      24

#define E1_STEP_PIN        32
#define E1_DIR_PIN         34
#define E1_ENABLE_PIN      30
=======
#define X_STEP_PIN                            54
#define X_DIR_PIN                             55
#define X_ENABLE_PIN                          38

#define Y_STEP_PIN                            60
#define Y_DIR_PIN                             61
#define Y_ENABLE_PIN                          56

#define Z_STEP_PIN                            46
#define Z_DIR_PIN                             48
#define Z_ENABLE_PIN                          63

#define E0_STEP_PIN                           26
#define E0_DIR_PIN                            28
#define E0_ENABLE_PIN                         24
>>>>>>> mcu_ctrl

//
// Temperature Sensors
//
<<<<<<< HEAD
#define TEMP_0_PIN         13
=======
#define TEMP_0_PIN                            13
>>>>>>> mcu_ctrl

//
// Heaters / Fans
//
<<<<<<< HEAD
#define HEATER_0_PIN       10
#define FAN_PIN             8
#define CONTROLLER_FAN_PIN  9
=======
#define HEATER_0_PIN                          10
#define FAN_PIN                                8
#define CONTROLLER_FAN_PIN                     9
>>>>>>> mcu_ctrl

//
// Misc. Functions
//
<<<<<<< HEAD
#define SDSS               25

#define FIL_RUNOUT_PIN     69   // PK7
#define KILL_PIN           20   // PD1
=======
#define KILL_PIN                              20  // PD1
#define CASE_LIGHT_PIN                         7

//
// SD Card
//
#define SDSS                                  25
#define SD_DETECT_PIN                         21  // PD0
>>>>>>> mcu_ctrl

//
// LCD / Controller
//
<<<<<<< HEAD
#define SD_DETECT_PIN      21   // PD0
#define LCD_SDSS           53
#define BEEPER_PIN          6

#define DOGLCD_CS          29
#define DOGLCD_A0          27

#define LCD_PINS_RS        27
#define LCD_PINS_ENABLE    29
#define LCD_PINS_D4        37
#define LCD_PINS_D5        35
#define LCD_PINS_D6        33
#define LCD_PINS_D7        31

#if ENABLED(NEWPANEL)
  #define BTN_EN1          17
  #define BTN_EN2          16
  #define BTN_ENC          23
#endif
=======
#define BEEPER_PIN                             6

#if HAS_WIRED_LCD

  #define LCD_SDSS                            53

  #define DOGLCD_CS                           29
  #define DOGLCD_A0                           27

  #define LCD_PINS_RS                         27
  #define LCD_PINS_ENABLE                     29
  #define LCD_PINS_D4                         37
  #define LCD_PINS_D5                         35
  #define LCD_PINS_D6                         33
  #define LCD_PINS_D7                         31

  #define LCD_CONTRAST_MIN                     0
  #define LCD_CONTRAST_MAX                   100
  #define DEFAULT_LCD_CONTRAST                30

  #if IS_NEWPANEL
    #define BTN_EN1                           17
    #define BTN_EN2                           16
    #define BTN_ENC                           23
  #endif

#endif // HAS_WIRED_LCD
>>>>>>> mcu_ctrl
