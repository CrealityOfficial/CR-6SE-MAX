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

#if ENABLED(BEZIER_CURVE_SUPPORT)

#include "../../module/motion.h"
#include "../../module/planner_bezier.h"

/**
 * Parameters interpreted according to:
<<<<<<< HEAD
 * http://linuxcnc.org/docs/2.6/html/gcode/parser.html#sec:G5-Cubic-Spline
=======
 * https://linuxcnc.org/docs/2.7/html/gcode/g-code.html#gcode:g5
>>>>>>> mcu_ctrl
 * However I, J omission is not supported at this point; all
 * parameters can be omitted and default to zero.
 */

#include "../gcode.h"
<<<<<<< HEAD
#include "../../Marlin.h" // for IsRunning()
=======
#include "../../MarlinCore.h" // for IsRunning()
>>>>>>> mcu_ctrl

/**
 * G5: Cubic B-spline
 */
void GcodeSuite::G5() {
  if (MOTION_CONDITIONS) {

    #if ENABLED(CNC_WORKSPACE_PLANES)
      if (workspace_plane != PLANE_XY) {
<<<<<<< HEAD
        SERIAL_ERROR_MSG(MSG_ERR_BAD_PLANE_MODE);
=======
        SERIAL_ERROR_MSG(STR_ERR_BAD_PLANE_MODE);
>>>>>>> mcu_ctrl
        return;
      }
    #endif

    get_destination_from_command();

    const xy_pos_t offsets[2] = {
      { parser.linearval('I'), parser.linearval('J') },
      { parser.linearval('P'), parser.linearval('Q') }
    };

    cubic_b_spline(current_position, destination, offsets, MMS_SCALED(feedrate_mm_s), active_extruder);
    current_position = destination;
  }
}

#endif // BEZIER_CURVE_SUPPORT
