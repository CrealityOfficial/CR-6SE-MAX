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

/**
 * lcdprint.cpp
 */

#include "../inc/MarlinConfigPre.h"

<<<<<<< HEAD
#if HAS_SPI_LCD

#include "lcdprint.h"
#include "../core/language.h"

/**
 * lcd_put_u8str_ind_P
 * Print a string with an index substituted within it
 */
lcd_uint_t lcd_put_u8str_ind_P(PGM_P const pstr, const uint8_t ind, const lcd_uint_t maxlen/*=LCD_WIDTH*/) {
  uint8_t *p = (uint8_t*)pstr;
  lcd_uint_t n = maxlen;
  for (; n; n--) {
=======
#if HAS_WIRED_LCD && !HAS_GRAPHICAL_TFT

#include "marlinui.h"
#include "lcdprint.h"

/**
 * lcd_put_u8str_ind_P
 *
 * Print a string with an index substituted within it:
 *
 *   = displays  '0'....'10' for indexes 0 - 10
 *   ~ displays  '1'....'11' for indexes 0 - 10
 *   * displays 'E1'...'E11' for indexes 0 - 10 (By default. Uses LCD_FIRST_TOOL)
 */
lcd_uint_t lcd_put_u8str_ind_P(PGM_P const pstr, const int8_t ind, PGM_P const inStr/*=nullptr*/, const lcd_uint_t maxlen/*=LCD_WIDTH*/) {
  uint8_t *p = (uint8_t*)pstr;
  int8_t n = maxlen;
  while (n > 0) {
>>>>>>> mcu_ctrl
    wchar_t ch;
    p = get_utf8_value_cb(p, read_byte_rom, &ch);
    if (!ch) break;
    if (ch == '=' || ch == '~' || ch == '*') {
<<<<<<< HEAD
      if (ch == '*') { lcd_put_wchar('E'); n--; }
      // lcd_put_int(ind); n--; if (ind >= 10) n--;
      // if (ind >= 0)
        {
          lcd_put_wchar(ind + ((ch == '=') ? '0' : LCD_FIRST_TOOL));
          n--;
        }
      // else if (ind == -1) { PGM_P const b = GET_TEXT(MSG_BED); lcd_put_u8str_P(b); n -= utf8_strlen_P(b); }
      // else if (ind == -2) { PGM_P const c = GET_TEXT(MSG_CHAMBER); lcd_put_u8str_P(c); n -= utf8_strlen_P(c); }
      if (n) n -= lcd_put_u8str_max_P((PGM_P)p, n);
      break;
    }
    lcd_put_wchar(ch);
=======
      if (ind >= 0) {
        if (ch == '*') { lcd_put_wchar('E'); n--; }
        if (n) {
          int8_t inum = ind + ((ch == '=') ? 0 : LCD_FIRST_TOOL);
          if (inum >= 10) {
            lcd_put_wchar('0' + (inum / 10)); n--;
            inum %= 10;
          }
          if (n) { lcd_put_wchar('0' + inum); n--; }
        }
      }
      else {
        PGM_P const b = ind == -2 ? GET_TEXT(MSG_CHAMBER) : GET_TEXT(MSG_BED);
        n -= lcd_put_u8str_max_P(b, n * (MENU_FONT_WIDTH)) / (MENU_FONT_WIDTH);
      }
      if (n) {
        n -= lcd_put_u8str_max_P((PGM_P)p, n * (MENU_FONT_WIDTH)) / (MENU_FONT_WIDTH);
        break;
      }
    }
    else if (ch == '$' && inStr) {
      n -= lcd_put_u8str_max_P(inStr, n * (MENU_FONT_WIDTH)) / (MENU_FONT_WIDTH);
    }
    else {
      lcd_put_wchar(ch);
      n--;
    }
>>>>>>> mcu_ctrl
  }
  return n;
}

<<<<<<< HEAD
#endif // HAS_SPI_LCD
=======
#endif // HAS_WIRED_LCD
>>>>>>> mcu_ctrl
