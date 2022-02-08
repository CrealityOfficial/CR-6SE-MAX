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
 * Melzi (Malyan M150) pin assignments
 */

#define BOARD_INFO_NAME "Melzi (Malyan)"
<<<<<<< HEAD
=======

// Alter timing for graphical display
#if HAS_MARLINUI_U8GLIB
  #ifndef BOARD_ST7920_DELAY_1
    #define BOARD_ST7920_DELAY_1 DELAY_NS(125)
  #endif
  #ifndef BOARD_ST7920_DELAY_2
    #define BOARD_ST7920_DELAY_2 DELAY_NS(125)
  #endif
  #ifndef BOARD_ST7920_DELAY_3
    #define BOARD_ST7920_DELAY_3 DELAY_NS(125)
  #endif
#endif

>>>>>>> mcu_ctrl
#include "pins_MELZI.h"

#undef LCD_SDSS
#undef LCD_PINS_RS
#undef LCD_PINS_ENABLE
#undef LCD_PINS_D4
#undef BTN_EN1
#undef BTN_EN2
#undef BTN_ENC

<<<<<<< HEAD
#define LCD_PINS_RS        17   // ST9720 CS
#define LCD_PINS_ENABLE    16   // ST9720 DAT
#define LCD_PINS_D4        11   // ST9720 CLK
#define BTN_EN1            30
#define BTN_EN2            29
#define BTN_ENC            28

// Alter timing for graphical display
#if HAS_GRAPHICAL_LCD
  #define BOARD_ST7920_DELAY_1 DELAY_NS(125)
  #define BOARD_ST7920_DELAY_2 DELAY_NS(125)
  #define BOARD_ST7920_DELAY_3 DELAY_NS(125)
#endif
=======
#define LCD_PINS_RS                           17  // ST9720 CS
#define LCD_PINS_ENABLE                       16  // ST9720 DAT
#define LCD_PINS_D4                           11  // ST9720 CLK
#define BTN_EN1                               30
#define BTN_EN2                               29
#define BTN_ENC                               28
>>>>>>> mcu_ctrl
