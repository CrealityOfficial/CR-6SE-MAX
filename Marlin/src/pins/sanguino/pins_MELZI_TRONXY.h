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
 * Melzi pin assignments
 */

#define BOARD_INFO_NAME "Melzi (Tronxy)"
<<<<<<< HEAD
=======

#if HAS_MARLINUI_U8GLIB
  #ifndef BOARD_ST7920_DELAY_1
    #define BOARD_ST7920_DELAY_1 DELAY_NS(0)
  #endif
  #ifndef BOARD_ST7920_DELAY_2
    #define BOARD_ST7920_DELAY_2 DELAY_NS(125)
  #endif
  #ifndef BOARD_ST7920_DELAY_3
    #define BOARD_ST7920_DELAY_3 DELAY_NS(0)
  #endif
#endif

>>>>>>> mcu_ctrl
#include "pins_MELZI.h"

#undef Z_ENABLE_PIN
#undef LCD_PINS_RS
#undef LCD_PINS_ENABLE
#undef LCD_PINS_D4
#undef LCD_PINS_D5
#undef LCD_PINS_D6
#undef LCD_PINS_D7
#undef BTN_EN1
#undef BTN_EN2
#undef BTN_ENC
#undef LCD_SDSS

<<<<<<< HEAD
#define Z_ENABLE_PIN    14
#define LCD_PINS_RS     30
#define LCD_PINS_ENABLE 28
#define LCD_PINS_D4     16
#define LCD_PINS_D5     17
#define LCD_PINS_D6     27
#define LCD_PINS_D7     29
#define BTN_EN1         10
#define BTN_EN2         11
#define BTN_ENC         26

#if HAS_GRAPHICAL_LCD
  #define BOARD_ST7920_DELAY_1 DELAY_NS(0)
  #define BOARD_ST7920_DELAY_2 DELAY_NS(125)
  #define BOARD_ST7920_DELAY_3 DELAY_NS(0)
#endif
=======
#define Z_ENABLE_PIN                          14
#define LCD_PINS_RS                           30
#define LCD_PINS_ENABLE                       28
#define LCD_PINS_D4                           16
#define LCD_PINS_D5                           17
#define LCD_PINS_D6                           27
#define LCD_PINS_D7                           29
#define BTN_EN1                               10
#define BTN_EN2                               11
#define BTN_ENC                               26
>>>>>>> mcu_ctrl
