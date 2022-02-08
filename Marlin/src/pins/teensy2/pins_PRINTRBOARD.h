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
 *  Rev B  2 JUN 2017
 *
 *  Converted to Arduino pin numbering
 */

/**
 *  There are two Arduino IDE extensions that are compatible with this board
 *  and with the mainstream Marlin software.
 *
<<<<<<< HEAD
 *  Teensyduino - http://www.pjrc.com/teensy/teensyduino.html
=======
 *  Teensyduino - https://www.pjrc.com/teensy/teensyduino.html
>>>>>>> mcu_ctrl
 *    Select Teensy++ 2.0 in Arduino IDE from the 'Tools > Board' menu
 *
 *    Installation instructions are at the above URL.  Don't bother loading the
 *    libraries - they are not used with the Marlin software.
 *
 *  Printrboard - https://github.com/scwimbush/Printrboard-HID-Arduino-IDE-Support
 *
 *    Installation:
 *
 *       1. Go to the above URL, click on the "Clone or Download" button and then
 *          click on "Download ZIP" button.
 *       2. Unzip the file, find the "printrboard" directory and then copy it to the
 *          hardware directory in Arduino.  The Arduino hardware directory will probably
 *          be located in a path similar to this: C:\Program Files (x86)\Arduino\hardware.
 *       3. Restart Arduino.
 *       4. Select "Printrboard" from the 'Tools > Board' menu.
 *
 *  Teensyduino is the most popular option. Printrboard is used if your board doesn't have
 *  the Teensyduino bootloader on it.
 */

/**
 *  To burn the bootloader that comes with Printrboard:
 *
 *   1. Connect your programmer to the board.
 *   2. In the Arduino IDE select "Printrboard" and then select the programmer.
 *   3. In the Arduino IDE click on "burn bootloader". Don't worry about the "verify failed at 1F000" error message.
 *   4. The programmer is no longer needed. Remove it.
 */

<<<<<<< HEAD
#ifndef __AVR_AT90USB1286__
  #error "Oops! Select 'Teensy++ 2.0' or 'Printrboard' in 'Tools > Board.'"
#endif
=======
#include "env_validate.h"
>>>>>>> mcu_ctrl

#define BOARD_INFO_NAME "Printrboard"

// Disable JTAG pins so they can be used for the Extrudrboard
#define DISABLE_JTAG

//
// Limit Switches
//
<<<<<<< HEAD
#define X_STOP_PIN         47   // E3
#define Y_STOP_PIN         20   // B0 SS
#define Z_STOP_PIN         36   // E4
=======
#define X_STOP_PIN                            47  // E3
#define Y_STOP_PIN                            20  // B0 SS
#define Z_STOP_PIN                            36  // E4
>>>>>>> mcu_ctrl

//
// Steppers
//
<<<<<<< HEAD
#define X_STEP_PIN         28   // A0
#define X_DIR_PIN          29   // A1
#define X_ENABLE_PIN       19   // E7

#define Y_STEP_PIN         30   // A2
#define Y_DIR_PIN          31   // A3
#define Y_ENABLE_PIN       18   // E6

#define Z_STEP_PIN         32   // A4
#define Z_DIR_PIN          33   // A5
#define Z_ENABLE_PIN       17   // C7

#define E0_STEP_PIN        34   // A6
#define E0_DIR_PIN         35   // A7
#define E0_ENABLE_PIN      13   // C3
=======
#define X_STEP_PIN                            28  // A0
#define X_DIR_PIN                             29  // A1
#define X_ENABLE_PIN                          19  // E7

#define Y_STEP_PIN                            30  // A2
#define Y_DIR_PIN                             31  // A3
#define Y_ENABLE_PIN                          18  // E6

#define Z_STEP_PIN                            32  // A4
#define Z_DIR_PIN                             33  // A5
#define Z_ENABLE_PIN                          17  // C7

#define E0_STEP_PIN                           34  // A6
#define E0_DIR_PIN                            35  // A7
#define E0_ENABLE_PIN                         13  // C3
>>>>>>> mcu_ctrl

//
// Temperature Sensors
//
<<<<<<< HEAD
#define TEMP_0_PIN          1   // Analog Input
#define TEMP_BED_PIN        0   // Analog Input
=======
#define TEMP_0_PIN                             1  // Analog Input
#define TEMP_BED_PIN                           0  // Analog Input
>>>>>>> mcu_ctrl

//
// Heaters / Fans
//
<<<<<<< HEAD
#define HEATER_0_PIN       15   // C5 PWM3B - Extruder
#define HEATER_1_PIN       44   // F6
#define HEATER_2_PIN       45   // F7
#define HEATER_BED_PIN     14   // C4 PWM3C

#ifndef FAN_PIN
  #define FAN_PIN          16   // C6 PWM3A
=======
#define HEATER_0_PIN                          15  // C5 PWM3B - Extruder
#define HEATER_1_PIN                          44  // F6
#define HEATER_2_PIN                          45  // F7
#define HEATER_BED_PIN                        14  // C4 PWM3C

#ifndef FAN_PIN
  #define FAN_PIN                             16  // C6 PWM3A
>>>>>>> mcu_ctrl
#endif

//
// Misc. Functions
//
<<<<<<< HEAD
#define SDSS               26   // B6 SDCS
#define FILWIDTH_PIN        2   // Analog Input
=======
#define SDSS                                  26  // B6 SDCS
#define FILWIDTH_PIN                           2  // Analog Input
>>>>>>> mcu_ctrl

//
// LCD / Controller
//
<<<<<<< HEAD
#if BOTH(ULTRA_LCD, NEWPANEL)

  #define LCD_PINS_RS       9   // E1       JP11-11
  #define LCD_PINS_ENABLE   8   // E0       JP11-10
  #define LCD_PINS_D4       7   // D7       JP11-8
  #define LCD_PINS_D5       6   // D6       JP11-7
  #define LCD_PINS_D6       5   // D5       JP11-6
  #define LCD_PINS_D7       4   // D4       JP11-5

  #if ANY(VIKI2, miniVIKI)
    #define BEEPER_PIN      8   // E0       JP11-10

    #define DOGLCD_A0      40   // F2       JP2-2
    #define DOGLCD_CS      41   // F3       JP2-4
    #define LCD_SCREEN_ROT_180

    #define BTN_EN1         2   // D2 TX1   JP2-5
    #define BTN_EN2         3   // D3 RX1   JP2-7
    #define BTN_ENC        45   // F7 TDI   JP2-12

    #undef SDSS
    #define SDSS           43   // F5 TMS   JP2-8

    #define STAT_LED_RED_PIN  12   // C2    JP11-14
    #define STAT_LED_BLUE_PIN 10   // C0    JP11-12

  #elif ENABLED(LCD_I2C_PANELOLU2)

    #define BTN_EN1         3   // D3 RX1   JP2-7
    #define BTN_EN2         2   // D2 TX1   JP2-5
    #define BTN_ENC        41   // F3       JP2-4
    #undef SDSS
    #define SDSS           38   // F0       B-THERM connector - use SD card on Panelolu2

  #else

    #define BTN_EN1        10   // C0       JP11-12
    #define BTN_EN2        11   // C1       JP11-13
    #define BTN_ENC        12   // C2       JP11-14

  #endif

#endif // HAS_SPI_LCD && NEWPANEL
=======
#if IS_ULTRA_LCD && IS_NEWPANEL

  #define LCD_PINS_RS                          9  // E1       JP11-11
  #define LCD_PINS_ENABLE                      8  // E0       JP11-10
  #define LCD_PINS_D4                          7  // D7       JP11-8
  #define LCD_PINS_D5                          6  // D6       JP11-7
  #define LCD_PINS_D6                          5  // D5       JP11-6
  #define LCD_PINS_D7                          4  // D4       JP11-5

  #if ANY(VIKI2, miniVIKI)
    #define BEEPER_PIN                         8  // E0       JP11-10

    #define DOGLCD_A0                         40  // F2       JP2-2
    #define DOGLCD_CS                         41  // F3       JP2-4
    #define LCD_SCREEN_ROT_180

    #define BTN_EN1                            2  // D2 TX1   JP2-5
    #define BTN_EN2                            3  // D3 RX1   JP2-7
    #define BTN_ENC                           45  // F7 TDI   JP2-12

    #undef SDSS
    #define SDSS                              43  // F5 TMS   JP2-8

    #define STAT_LED_RED_PIN                  12  // C2    JP11-14
    #define STAT_LED_BLUE_PIN                 10  // C0    JP11-12

  #elif ENABLED(LCD_I2C_PANELOLU2)

    #define BTN_EN1                            3  // D3 RX1   JP2-7
    #define BTN_EN2                            2  // D2 TX1   JP2-5
    #define BTN_ENC                           41  // F3       JP2-4
    #undef SDSS
    #define SDSS                              38  // F0       B-THERM connector - use SD card on Panelolu2

  #else

    #define BTN_EN1                           10  // C0       JP11-12
    #define BTN_EN2                           11  // C1       JP11-13
    #define BTN_ENC                           12  // C2       JP11-14

  #endif

#endif // IS_ULTRA_LCD && IS_NEWPANEL
>>>>>>> mcu_ctrl
