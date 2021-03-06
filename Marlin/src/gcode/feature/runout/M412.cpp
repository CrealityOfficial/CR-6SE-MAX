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

#include "../../../inc/MarlinConfig.h"

#if HAS_FILAMENT_SENSOR

#include "../../gcode.h"
#include "../../../feature/runout.h"

/**
 * M412: Enable / Disable filament runout detection
<<<<<<< HEAD
 */
void GcodeSuite::M412() {
  if (parser.seen("RS"
    #ifdef FILAMENT_RUNOUT_DISTANCE_MM
      "D"
    #endif
    #if ENABLED(HOST_ACTION_COMMANDS)
      "H"
    #endif
=======
 *
 * Parameters
 *  R         : Reset the runout sensor
 *  S<bool>   : Reset and enable/disable the runout sensor
 *  H<bool>   : Enable/disable host handling of filament runout
 *  D<linear> : Extra distance to continue after runout is triggered
 */
void GcodeSuite::M412() {
  if (parser.seen("RS"
    TERN_(HAS_FILAMENT_RUNOUT_DISTANCE, "D")
    TERN_(HOST_ACTION_COMMANDS, "H")
>>>>>>> mcu_ctrl
  )) {
    #if ENABLED(HOST_ACTION_COMMANDS)
      if (parser.seen('H')) runout.host_handling = parser.value_bool();
    #endif
<<<<<<< HEAD
    const bool seenR = parser.seen('R'), seenS = parser.seen('S');
    if (seenR || seenS) runout.reset();
    if (seenS) runout.enabled = parser.value_bool();
    #ifdef FILAMENT_RUNOUT_DISTANCE_MM
=======
    const bool seenR = parser.seen_test('R'), seenS = parser.seen('S');
    if (seenR || seenS) runout.reset();
    if (seenS) runout.enabled = parser.value_bool();
    #if HAS_FILAMENT_RUNOUT_DISTANCE
>>>>>>> mcu_ctrl
      if (parser.seen('D')) runout.set_runout_distance(parser.value_linear_units());
    #endif
  }
  else {
    SERIAL_ECHO_START();
    SERIAL_ECHOPGM("Filament runout ");
    serialprintln_onoff(runout.enabled);
<<<<<<< HEAD
    #ifdef FILAMENT_RUNOUT_DISTANCE_MM
=======
    #if HAS_FILAMENT_RUNOUT_DISTANCE
>>>>>>> mcu_ctrl
      SERIAL_ECHOLNPAIR("Filament runout distance (mm): ", runout.runout_distance());
    #endif
  }
}

#endif // HAS_FILAMENT_SENSOR
