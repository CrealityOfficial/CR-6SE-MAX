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

//
// Backlash Menu
//

#include "../../inc/MarlinConfigPre.h"

<<<<<<< HEAD
#if HAS_LCD_MENU && ENABLED(BACKLASH_GCODE)

#include "menu.h"
=======
#if BOTH(HAS_LCD_MENU, BACKLASH_GCODE)

#include "menu_item.h"
>>>>>>> mcu_ctrl

#include "../../feature/backlash.h"

void menu_backlash() {
  START_MENU();
  BACK_ITEM(MSG_MAIN);

  EDIT_ITEM_FAST(percent, MSG_BACKLASH_CORRECTION, &backlash.correction, all_off, all_on);

<<<<<<< HEAD
  #define EDIT_BACKLASH_DISTANCE(N) EDIT_ITEM_FAST(float43, MSG_BACKLASH_##N, &backlash.distance_mm[_AXIS(N)], 0.0f, 9.9f);
  EDIT_BACKLASH_DISTANCE(A);
  EDIT_BACKLASH_DISTANCE(B);
  EDIT_BACKLASH_DISTANCE(C);
=======
  #if DISABLED(CORE_BACKLASH) || ENABLED(MARKFORGED_XY)
    #define _CAN_CALI AXIS_CAN_CALIBRATE
  #else
    #define _CAN_CALI(A) true
  #endif
  #define EDIT_BACKLASH_DISTANCE(N) EDIT_ITEM_FAST(float43, MSG_BACKLASH_##N, &backlash.distance_mm[_AXIS(N)], 0.0f, 9.9f);
  if (_CAN_CALI(A)) EDIT_BACKLASH_DISTANCE(A);
  if (_CAN_CALI(B)) EDIT_BACKLASH_DISTANCE(B);
  if (_CAN_CALI(C)) EDIT_BACKLASH_DISTANCE(C);
>>>>>>> mcu_ctrl

  #ifdef BACKLASH_SMOOTHING_MM
    EDIT_ITEM_FAST(float43, MSG_BACKLASH_SMOOTHING, &backlash.smoothing_mm, 0.0f, 9.9f);
  #endif

  END_MENU();
}

<<<<<<< HEAD
#endif // HAS_LCD_MENU && BACKLASH_COMPENSATION
=======
#endif // HAS_LCD_MENU && BACKLASH_GCODE
>>>>>>> mcu_ctrl
