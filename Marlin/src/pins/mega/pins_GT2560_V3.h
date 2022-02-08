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
<<<<<<< HEAD
 * GT2560 V3.0 pin assignment
 */

#if !defined(__AVR_ATmega1280__) && !defined(__AVR_ATmega2560__)
  #error "Oops! Select 'Arduino/Genuino Mega or Mega 2560' in 'Tools > Board.'"
#endif

#ifndef BOARD_INFO_NAME
  #define BOARD_INFO_NAME "GT2560 V3.0"
=======
 * Geeetech GT2560 3.0/3.1 pin assignments
 *
 * Also GT2560 RevB and GT2560 4.0/4.1
 */

#define ALLOW_MEGA1280
#include "env_validate.h"

#ifndef BOARD_INFO_NAME
  #define BOARD_INFO_NAME "GT2560 3.x"
>>>>>>> mcu_ctrl
#endif

//
// Servos
//
<<<<<<< HEAD
#define SERVO0_PIN         11   //13 untested  3Dtouch
=======
#define SERVO0_PIN                            11  // 13 untested  3Dtouch
>>>>>>> mcu_ctrl

//
// Limit Switches
//
#ifndef X_STOP_PIN
  #ifndef X_MIN_PIN
<<<<<<< HEAD
    #define X_MIN_PIN      24
  #endif
  #ifndef X_MAX_PIN
    #define X_MAX_PIN      22
=======
    #define X_MIN_PIN                         24
  #endif
  #ifndef X_MAX_PIN
    #define X_MAX_PIN                         22
>>>>>>> mcu_ctrl
  #endif
#endif
#ifndef Y_STOP_PIN
  #ifndef Y_MIN_PIN
<<<<<<< HEAD
    #define Y_MIN_PIN      28
  #endif
  #ifndef Y_MAX_PIN
    #define Y_MAX_PIN      26
=======
    #define Y_MIN_PIN                         28
  #endif
  #ifndef Y_MAX_PIN
    #define Y_MAX_PIN                         26
>>>>>>> mcu_ctrl
  #endif
#endif
#ifndef Z_STOP_PIN
  #ifndef Z_MIN_PIN
<<<<<<< HEAD
    #define Z_MIN_PIN      30
  #endif
  #ifndef Z_MAX_PIN
    #define Z_MAX_PIN      32
=======
    #define Z_MIN_PIN                         30
  #endif
  #ifndef Z_MAX_PIN
    #define Z_MAX_PIN                         32
>>>>>>> mcu_ctrl
  #endif
#endif

//
// Z Probe (when not Z_MIN_PIN)
//
#ifndef Z_MIN_PROBE_PIN
<<<<<<< HEAD
  #define Z_MIN_PROBE_PIN  32
=======
  #define Z_MIN_PROBE_PIN                     32
>>>>>>> mcu_ctrl
#endif

//
// Runout Sensor
//
#ifndef FIL_RUNOUT_PIN
<<<<<<< HEAD
  #define FIL_RUNOUT_PIN   66
#endif
#ifndef FIL_RUNOUT2_PIN
  #define FIL_RUNOUT2_PIN  67
=======
  #define FIL_RUNOUT_PIN                      66
#endif
#ifndef FIL_RUNOUT2_PIN
  #define FIL_RUNOUT2_PIN                     67
#endif
#ifndef FIL_RUNOUT3_PIN
  #define FIL_RUNOUT3_PIN                     54
>>>>>>> mcu_ctrl
#endif

//
// Power Recovery
//
<<<<<<< HEAD
#define POWER_LOSS_PIN     69   // Pin to detect power loss
#define POWER_LOSS_STATE   LOW
=======
#define POWER_LOSS_PIN                        69  // Pin to detect power loss
#define POWER_LOSS_STATE                     LOW
>>>>>>> mcu_ctrl

//
// Steppers
//
<<<<<<< HEAD
#define X_STEP_PIN         37
#define X_DIR_PIN          39
#define X_ENABLE_PIN       35

#define Y_STEP_PIN         31
#define Y_DIR_PIN          33
#define Y_ENABLE_PIN       29

#define Z_STEP_PIN         25
#define Z_DIR_PIN          23
#define Z_ENABLE_PIN       27

#define E0_STEP_PIN        46
#define E0_DIR_PIN         44
#define E0_ENABLE_PIN      12

#define E1_STEP_PIN        49
#define E1_DIR_PIN         47
#define E1_ENABLE_PIN      48

#define E2_STEP_PIN        43
#define E2_DIR_PIN         45
#define E2_ENABLE_PIN      41
=======
#define X_STEP_PIN                            37
#define X_DIR_PIN                             39
#define X_ENABLE_PIN                          35

#define Y_STEP_PIN                            31
#define Y_DIR_PIN                             33
#define Y_ENABLE_PIN                          29

#define Z_STEP_PIN                            25
#define Z_DIR_PIN                             23
#define Z_ENABLE_PIN                          27

#define E0_STEP_PIN                           46
#define E0_DIR_PIN                            44
#define E0_ENABLE_PIN                         12

#define E1_STEP_PIN                           49
#define E1_DIR_PIN                            47
#define E1_ENABLE_PIN                         48

#define E2_STEP_PIN                           43
#define E2_DIR_PIN                            45
#define E2_ENABLE_PIN                         41
>>>>>>> mcu_ctrl

//
// Temperature Sensors
//
<<<<<<< HEAD
#define TEMP_0_PIN         11   // Analog Input
#define TEMP_1_PIN          9   // Analog Input
#define TEMP_2_PIN          1   // Analog Input
#define TEMP_BED_PIN       10   // Analog Input
=======
#define TEMP_0_PIN                            11  // Analog Input
#define TEMP_1_PIN                             9  // Analog Input
#define TEMP_2_PIN                             8  // Analog Input
#define TEMP_BED_PIN                          10  // Analog Input
>>>>>>> mcu_ctrl

//
// Heaters / Fans
//
<<<<<<< HEAD
#define HEATER_0_PIN       10
#define HEATER_1_PIN        3
#define HEATER_2_PIN        1
#define HEATER_BED_PIN      4
#define FAN_PIN             9
//#define FAN1_PIN          8
//#define FAN2_PIN          7
=======
#define HEATER_0_PIN                          10
#define HEATER_1_PIN                           3
#define HEATER_2_PIN                           2
#define HEATER_BED_PIN                         4
#define FAN_PIN                                9
#define FAN1_PIN                               8
#define FAN2_PIN                               7
>>>>>>> mcu_ctrl

//
// Misc. Functions
//
<<<<<<< HEAD
#define SD_DETECT_PIN      38
#define SDSS               53
#define LED_PIN             6
#define PS_ON_PIN          12
#define SUICIDE_PIN        54   // This pin must be enabled at boot to keep power flowing

#ifndef CASE_LIGHT_PIN
  #define CASE_LIGHT_PIN    6   // 21
=======
#define SD_DETECT_PIN                         38
#define SDSS                                  53
#define LED_PIN                               13  // Use 6 (case light) for external LED. 13 is internal (yellow) LED.
#define PS_ON_PIN                             12

#if NUM_RUNOUT_SENSORS < 3
  #define SUICIDE_PIN                         54  // This pin must be enabled at boot to keep power flowing
#endif

#ifndef CASE_LIGHT_PIN
  #define CASE_LIGHT_PIN                       6  // 21
>>>>>>> mcu_ctrl
#endif

//
// LCD Controller
//
<<<<<<< HEAD
#define BEEPER_PIN         18

#ifndef LCD_PINS_RS
  #define LCD_PINS_RS      20
#endif
#ifndef LCD_PINS_ENABLE
  #define LCD_PINS_ENABLE  17
#endif
#ifndef LCD_PINS_D4
  #define LCD_PINS_D4      16
#endif
#ifndef LCD_PINS_D5
  #define LCD_PINS_D5      21
#endif
#ifndef LCD_PINS_D6
  #define LCD_PINS_D6       5
#endif
#ifndef LCD_PINS_D7
  #define LCD_PINS_D7      36
#endif

#if ENABLED(NEWPANEL)
  #ifndef BTN_EN1
    #define BTN_EN1        42
  #endif
  #ifndef BTN_EN2
    #define BTN_EN2        40
  #endif
  #ifndef BTN_ENC
    #define BTN_ENC        19
=======
#define BEEPER_PIN                            18

#if ENABLED(YHCB2004)
  #ifndef YHCB2004_CLK
    #define YHCB2004_CLK                       5
    #define DIO52                   YHCB2004_CLK
  #endif
  #ifndef YHCB2004_MOSI
    #define YHCB2004_MOSI                     21
    #define DIO50                  YHCB2004_MOSI
  #endif
  #ifndef YHCB2004_MISO
    #define YHCB2004_MISO                     36
    #define DIO51                  YHCB2004_MISO
  #endif
#elif HAS_WIRED_LCD
  #ifndef LCD_PINS_RS
    #define LCD_PINS_RS                       20
  #endif
  #ifndef LCD_PINS_ENABLE
    #define LCD_PINS_ENABLE                   17
  #endif
  #ifndef LCD_PINS_D4
    #define LCD_PINS_D4                       16
  #endif
  #ifndef LCD_PINS_D5
    #define LCD_PINS_D5                       21
  #endif
  #ifndef LCD_PINS_D6
    #define LCD_PINS_D6                        5
  #endif
  #ifndef LCD_PINS_D7
    #define LCD_PINS_D7                       36
  #endif
#endif

#if ENABLED(YHCB2004)
  #ifndef BTN_EN1
    #define BTN_EN1                           16
  #endif
  #ifndef BTN_EN2
    #define BTN_EN2                           17
  #endif
  #ifndef BTN_ENC
    #define BTN_ENC                           19
  #endif
#elif IS_NEWPANEL
  #ifndef BTN_EN1
    #define BTN_EN1                           42
  #endif
  #ifndef BTN_EN2
    #define BTN_EN2                           40
  #endif
  #ifndef BTN_ENC
    #define BTN_ENC                           19
>>>>>>> mcu_ctrl
  #endif
#endif
