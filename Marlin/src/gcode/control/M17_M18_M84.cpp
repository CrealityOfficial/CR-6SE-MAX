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

#include "../gcode.h"
<<<<<<< HEAD
#include "../../Marlin.h" // for stepper_inactive_time, disable_e_steppers
#include "../../lcd/ultralcd.h"
#include "../../module/stepper.h"

#if BOTH(AUTO_BED_LEVELING_UBL, ULTRA_LCD)
=======
#include "../../MarlinCore.h" // for stepper_inactive_time, disable_e_steppers
#include "../../lcd/marlinui.h"
#include "../../module/stepper.h"

#if ENABLED(AUTO_BED_LEVELING_UBL)
>>>>>>> mcu_ctrl
  #include "../../feature/bedlevel/bedlevel.h"
#endif

/**
 * M17: Enable stepper motors
 */
void GcodeSuite::M17() {
  if (parser.seen("XYZE")) {
<<<<<<< HEAD
    if (parser.seen('X')) enable_X();
    if (parser.seen('Y')) enable_Y();
    if (parser.seen('Z')) enable_Z();
    #if HAS_E_STEPPER_ENABLE
      if (parser.seen('E')) enable_e_steppers();
    #endif
=======
    if (parser.seen_test('X')) ENABLE_AXIS_X();
    if (parser.seen_test('Y')) ENABLE_AXIS_Y();
    if (parser.seen_test('Z')) ENABLE_AXIS_Z();
    if (TERN0(HAS_E_STEPPER_ENABLE, parser.seen_test('E'))) enable_e_steppers();
>>>>>>> mcu_ctrl
  }
  else {
    LCD_MESSAGEPGM(MSG_NO_MOVE);
    enable_all_steppers();
  }
}

/**
 * M18, M84: Disable stepper motors
 */
void GcodeSuite::M18_M84() {
  if (parser.seenval('S')) {
<<<<<<< HEAD
=======
    reset_stepper_timeout();
>>>>>>> mcu_ctrl
    stepper_inactive_time = parser.value_millis_from_seconds();
  }
  else {
    if (parser.seen("XYZE")) {
      planner.synchronize();
<<<<<<< HEAD
      if (parser.seen('X')) disable_X();
      if (parser.seen('Y')) disable_Y();
      if (parser.seen('Z')) disable_Z();
      #if HAS_E_STEPPER_ENABLE
        if (parser.seen('E')) disable_e_steppers();
      #endif
=======
      if (parser.seen_test('X')) DISABLE_AXIS_X();
      if (parser.seen_test('Y')) DISABLE_AXIS_Y();
      if (parser.seen_test('Z')) DISABLE_AXIS_Z();
      if (TERN0(HAS_E_STEPPER_ENABLE, parser.seen_test('E'))) disable_e_steppers();
>>>>>>> mcu_ctrl
    }
    else
      planner.finish_and_disable();

<<<<<<< HEAD
    #if HAS_LCD_MENU && ENABLED(AUTO_BED_LEVELING_UBL)
      if (ubl.lcd_map_control) {
        ubl.lcd_map_control = false;
        ui.defer_status_screen(false);
      }
    #endif
=======
    TERN_(AUTO_BED_LEVELING_UBL, ubl.steppers_were_disabled());
>>>>>>> mcu_ctrl
  }
}
