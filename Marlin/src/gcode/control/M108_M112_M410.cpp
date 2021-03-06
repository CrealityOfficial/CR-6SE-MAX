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

#if DISABLED(EMERGENCY_PARSER)

#include "../gcode.h"
<<<<<<< HEAD
#include "../../Marlin.h" // for wait_for_heatup, kill, quickstop_stepper
=======
#include "../../MarlinCore.h" // for wait_for_heatup, kill, M112_KILL_STR
#include "../../module/motion.h" // for quickstop_stepper
>>>>>>> mcu_ctrl

/**
 * M108: Stop the waiting for heaters in M109, M190, M303. Does not affect the target temperature.
 */
void GcodeSuite::M108() {
<<<<<<< HEAD
  #if HAS_RESUME_CONTINUE
    wait_for_user = false;
  #endif
=======
  TERN_(HAS_RESUME_CONTINUE, wait_for_user = false);
>>>>>>> mcu_ctrl
  wait_for_heatup = false;
}

/**
 * M112: Full Shutdown
 */
void GcodeSuite::M112() {
<<<<<<< HEAD
  kill(PSTR("M112 Shutdown"), nullptr, true);
=======
  kill(M112_KILL_STR, nullptr, true);
>>>>>>> mcu_ctrl
}

/**
 * M410: Quickstop - Abort all planned moves
 *
 * This will stop the carriages mid-move, so most likely they
 * will be out of sync with the stepper position after this.
 */
void GcodeSuite::M410() {
  quickstop_stepper();
}

#endif // !EMERGENCY_PARSER
