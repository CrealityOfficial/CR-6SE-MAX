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
 * Arduino Mega or Due with RAMPS Duo pin assignments
 *
 * Applies to the following boards:
 *
 *  RAMPS_DUO_EFB (Hotend, Fan, Bed)
 *  RAMPS_DUO_EEB (Hotend0, Hotend1, Bed)
 *  RAMPS_DUO_EFF (Hotend, Fan0, Fan1)
 *  RAMPS_DUO_EEF (Hotend0, Hotend1, Fan)
 *  RAMPS_DUO_SF  (Spindle, Controller Fan)
 *
 *  Differences between
 *  RAMPS_14 | RAMPS_DUO
 *    A9/D63 | A12/D66
 *   A10/D64 | A13/D67
 *   A11/D65 | A14/D68
 *   A12/D66 | A15/D69
 *       A13 | A9
 *       A14 | A10
 *       A15 | A11
 */

<<<<<<< HEAD
#if !defined(__SAM3X8E__) && !defined(__AVR_ATmega2560__)
  #error "Oops! Select 'Arduino Due' or 'Arduino/Genuino Mega or Mega 2560' in 'Tools > Board.'"
#endif

#define BOARD_INFO_NAME "RAMPS Duo"

#define IS_RAMPS_DUO
=======
#define BOARD_INFO_NAME "RAMPS Duo"

#define ALLOW_SAM3X8E
>>>>>>> mcu_ctrl
#include "../ramps/pins_RAMPS.h"

//
// Temperature Sensors
//
#undef TEMP_0_PIN
<<<<<<< HEAD
#define TEMP_0_PIN          9   // Analog Input

#undef TEMP_1_PIN
#define TEMP_1_PIN         11   // Analog Input

#undef TEMP_BED_PIN
#define TEMP_BED_PIN       10   // Analog Input
=======
#define TEMP_0_PIN                             9  // Analog Input

#undef TEMP_1_PIN
#define TEMP_1_PIN                            11  // Analog Input

#undef TEMP_BED_PIN
#define TEMP_BED_PIN                          10  // Analog Input
>>>>>>> mcu_ctrl

// SPI for Max6675 or Max31855 Thermocouple
#undef MAX6675_SS_PIN
#if DISABLED(SDSUPPORT)
<<<<<<< HEAD
  #define MAX6675_SS_PIN   69   // Don't use 53 if there is even the remote possibility of using Display/SD card
#else
  #define MAX6675_SS_PIN   69   // Don't use 49 as this is tied to the switch inside the SD card socket to detect if there is an SD card present
=======
  #define MAX6675_SS_PIN                      69  // Don't use 53 if using Display/SD card
#else
  #define MAX6675_SS_PIN                      69  // Don't use 49 (SD_DETECT_PIN)
>>>>>>> mcu_ctrl
#endif

//
// LCD / Controller
//
<<<<<<< HEAD
#if HAS_SPI_LCD

  #if BOTH(NEWPANEL, PANEL_ONE)
    #undef LCD_PINS_D4
    #define LCD_PINS_D4  68

    #undef LCD_PINS_D5
    #define LCD_PINS_D5  69

    #undef LCD_PINS_D7
    #define LCD_PINS_D7  67
  #endif

  #if ENABLED(NEWPANEL)
=======
#if HAS_WIRED_LCD

  #if BOTH(IS_NEWPANEL, PANEL_ONE)
    #undef LCD_PINS_D4
    #define LCD_PINS_D4                       68

    #undef LCD_PINS_D5
    #define LCD_PINS_D5                       69

    #undef LCD_PINS_D7
    #define LCD_PINS_D7                       67
  #endif

  #if IS_NEWPANEL
>>>>>>> mcu_ctrl

    #if ENABLED(REPRAPWORLD_GRAPHICAL_LCD)

      #undef BTN_EN1
<<<<<<< HEAD
      #define BTN_EN1 67

      #undef BTN_ENC
      #define BTN_ENC 66
=======
      #define BTN_EN1                         67

      #undef BTN_ENC
      #define BTN_ENC                         66
>>>>>>> mcu_ctrl

    #elif ENABLED(MINIPANEL)

      #undef DOGLCD_CS
<<<<<<< HEAD
      #define DOGLCD_CS    69

      #undef LCD_BACKLIGHT_PIN
      #define LCD_BACKLIGHT_PIN 68   // backlight LED on A14/D68

      #undef KILL_PIN
      #define KILL_PIN     67

      #undef BTN_EN2
      #define BTN_EN2      66

    #else

      #if ENABLED(REPRAPWORLD_KEYPAD)
        #undef BTN_EN1
        #define BTN_EN1    67   // encoder

        #undef BTN_ENC
        #define BTN_ENC    66   // enter button
      #elif ENABLED(PANEL_ONE)
        #undef BTN_EN2
        #define BTN_EN2    66   // AUX2 PIN 4
      #endif
    #endif

  #endif // NEWPANEL

#endif // HAS_SPI_LCD
=======
      #define DOGLCD_CS                       69

      #undef LCD_BACKLIGHT_PIN
      #define LCD_BACKLIGHT_PIN               68  // backlight LED on A14/D68

      #undef KILL_PIN
      #define KILL_PIN                        67

      #undef BTN_EN2
      #define BTN_EN2                         66

    #else

      #if IS_RRW_KEYPAD
        #undef BTN_EN1
        #define BTN_EN1                       67  // encoder

        #undef BTN_ENC
        #define BTN_ENC                       66  // enter button
      #elif ENABLED(PANEL_ONE)
        #undef BTN_EN2
        #define BTN_EN2                       66  // AUX2 PIN 4
      #endif
    #endif

    #if ENABLED(REPRAP_DISCOUNT_FULL_GRAPHIC_SMART_CONTROLLER)
      #define BTN_ENC_EN             LCD_PINS_D7  // Detect the presence of the encoder
    #endif

  #endif // IS_NEWPANEL

#endif // HAS_WIRED_LCD
>>>>>>> mcu_ctrl
