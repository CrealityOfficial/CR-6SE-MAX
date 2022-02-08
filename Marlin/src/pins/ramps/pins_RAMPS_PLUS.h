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
 * Arduino Mega with RAMPS v1.4Plus, also known as 3DYMY version, pin assignments
 * The differences to the RAMPS v1.4 are:
 *  - Swap heater E0 with E1
 *  - Swap pins 8 and 10. Bed/Fan/Hotend as labeled on the board are on pins 8/9/10.
 *  - Change pins 16->42, 17->44 and 29->53 used for display.
 *
 * Applies to the following boards:
 *
 *  RAMPS_PLUS_EFB (Extruder, Fan, Bed)
 *  RAMPS_PLUS_EEB (Extruder, Extruder, Bed)
 *  RAMPS_PLUS_EFF (Extruder, Fan, Fan)
 *  RAMPS_PLUS_EEF (Extruder, Extruder, Fan)
 *  RAMPS_PLUS_SF  (Spindle, Controller Fan)
<<<<<<< HEAD
 *
 */

#if !defined(__AVR_ATmega1280__) && !defined(__AVR_ATmega2560__)
 #error "Oops! Select 'Arduino/Genuino Mega or Mega 2560' in 'Tools > Board.'"
#endif

#define BOARD_INFO_NAME "RAMPS 1.4 Plus"

#define RAMPS_D8_PIN  10
#define RAMPS_D10_PIN  8
=======
 */

#include "env_validate.h"

#define BOARD_INFO_NAME "RAMPS 1.4 Plus"

#define RAMPS_D8_PIN                          10
#define RAMPS_D10_PIN                          8
>>>>>>> mcu_ctrl

#include "pins_RAMPS.h"

//
// Steppers - Swap E0 / E1 on 3DYMY
//
#undef E0_STEP_PIN
#undef E0_DIR_PIN
#undef E0_ENABLE_PIN

#undef E1_STEP_PIN
#undef E1_DIR_PIN
#undef E1_ENABLE_PIN

<<<<<<< HEAD
#define E0_STEP_PIN        36
#define E0_DIR_PIN         34
#define E0_ENABLE_PIN      30

#define E1_STEP_PIN        26
#define E1_DIR_PIN         28
#define E1_ENABLE_PIN      24
=======
#define E0_STEP_PIN                           36
#define E0_DIR_PIN                            34
#define E0_ENABLE_PIN                         30

#define E1_STEP_PIN                           26
#define E1_DIR_PIN                            28
#define E1_ENABLE_PIN                         24
>>>>>>> mcu_ctrl

#undef X_CS_PIN
#undef Y_CS_PIN
#undef Z_CS_PIN
#undef E0_CS_PIN
#undef E1_CS_PIN

<<<<<<< HEAD
#if ENABLED(ULTRA_LCD, REPRAPWORLD_GRAPHICAL_LCD, CR10_STOCKDISPLAY) && !BOTH(NEWPANEL, PANEL_ONE)
  #if DISABLED(MKS_12864OLED) || ENABLED(MKS_12864OLED_SSD1306)
    #undef LCD_PINS_RS
    #define LCD_PINS_RS     42   // 3DYMY boards pin 16 -> 42
    #undef LCD_PINS_ENABLE
    #define LCD_PINS_ENABLE 44   // 3DYMY boards pin 17 -> 44
  #endif
  #undef LCD_PINS_D7
  #define LCD_PINS_D7       53   // 3DYMY boards pin 29 -> 53
=======
#if IS_ULTRA_LCD && NONE(REPRAPWORLD_GRAPHICAL_LCD, CR10_STOCKDISPLAY) && !BOTH(IS_NEWPANEL, PANEL_ONE)
  #if DISABLED(MKS_12864OLED) || ENABLED(MKS_12864OLED_SSD1306)
    #undef LCD_PINS_RS
    #define LCD_PINS_RS                       42  // 3DYMY boards pin 16 -> 42
    #undef LCD_PINS_ENABLE
    #define LCD_PINS_ENABLE                   44  // 3DYMY boards pin 17 -> 44
  #endif
  #undef LCD_PINS_D7
  #define LCD_PINS_D7                         53  // 3DYMY boards pin 29 -> 53
>>>>>>> mcu_ctrl
#endif
