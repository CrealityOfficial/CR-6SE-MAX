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

#include "../../inc/MarlinConfig.h"

#if HAS_M206_COMMAND

#include "../gcode.h"
#include "../../module/motion.h"
<<<<<<< HEAD
#include "../../lcd/ultralcd.h"
#include "../../libs/buzzer.h"
=======
#include "../../lcd/marlinui.h"
#include "../../libs/buzzer.h"
#include "../../MarlinCore.h"

void M206_report() {
  SERIAL_ECHOLNPAIR_P(PSTR("M206 X"), home_offset.x, SP_Y_STR, home_offset.y, SP_Z_STR, home_offset.z);
}
>>>>>>> mcu_ctrl

/**
 * M206: Set Additional Homing Offset (X Y Z). SCARA aliases T=X, P=Y
 *
 * *** @thinkyhead: I recommend deprecating M206 for SCARA in favor of M665.
 * ***              M206 for SCARA will remain enabled in 1.1.x for compatibility.
 * ***              In the 2.0 release, it will simply be disabled by default.
 */
void GcodeSuite::M206() {
<<<<<<< HEAD
  LOOP_XYZ(i)
    if (parser.seen(axis_codes[i]))
=======
  LOOP_LINEAR_AXES(i)
    if (parser.seen(AXIS_CHAR(i)))
>>>>>>> mcu_ctrl
      set_home_offset((AxisEnum)i, parser.value_linear_units());

  #if ENABLED(MORGAN_SCARA)
    if (parser.seen('T')) set_home_offset(A_AXIS, parser.value_float()); // Theta
    if (parser.seen('P')) set_home_offset(B_AXIS, parser.value_float()); // Psi
  #endif

<<<<<<< HEAD
  report_current_position();
=======
  if (!parser.seen("XYZ"))
    M206_report();
  else
    report_current_position();
>>>>>>> mcu_ctrl
}

/**
 * M428: Set home_offset based on the distance between the
 *       current_position and the nearest "reference point."
 *       If an axis is past center its endstop position
 *       is the reference-point. Otherwise it uses 0. This allows
 *       the Z offset to be set near the bed when using a max endstop.
 *
 *       M428 can't be used more than 2cm away from 0 or an endstop.
 *
 *       Use M206 to set these values directly.
 */
void GcodeSuite::M428() {
<<<<<<< HEAD
  if (axis_unhomed_error()) return;

  xyz_float_t diff;
  LOOP_XYZ(i) {
=======
  if (homing_needed_error()) return;

  xyz_float_t diff;
  LOOP_LINEAR_AXES(i) {
>>>>>>> mcu_ctrl
    diff[i] = base_home_pos((AxisEnum)i) - current_position[i];
    if (!WITHIN(diff[i], -20, 20) && home_dir((AxisEnum)i) > 0)
      diff[i] = -current_position[i];
    if (!WITHIN(diff[i], -20, 20)) {
<<<<<<< HEAD
      SERIAL_ERROR_MSG(MSG_ERR_M428_TOO_FAR);
=======
      SERIAL_ERROR_MSG(STR_ERR_M428_TOO_FAR);
>>>>>>> mcu_ctrl
      LCD_ALERTMESSAGEPGM_P(PSTR("Err: Too far!"));
      BUZZ(200, 40);
      return;
    }
  }

<<<<<<< HEAD
  LOOP_XYZ(i) set_home_offset((AxisEnum)i, diff[i]);
=======
  LOOP_LINEAR_AXES(i) set_home_offset((AxisEnum)i, diff[i]);
>>>>>>> mcu_ctrl
  report_current_position();
  LCD_MESSAGEPGM(MSG_HOME_OFFSETS_APPLIED);
  BUZZ(100, 659);
  BUZZ(100, 698);
}

#endif // HAS_M206_COMMAND
