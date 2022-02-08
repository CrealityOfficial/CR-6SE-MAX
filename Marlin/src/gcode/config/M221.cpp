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
#include "../../module/planner.h"

<<<<<<< HEAD
#if EXTRUDERS
=======
#if HAS_EXTRUDERS
>>>>>>> mcu_ctrl

/**
 * M221: Set extrusion percentage (M221 T0 S95)
 */
void GcodeSuite::M221() {

  const int8_t target_extruder = get_target_extruder_from_command();
  if (target_extruder < 0) return;

<<<<<<< HEAD
  if (parser.seenval('S')) {
    planner.flow_percentage[target_extruder] = parser.value_int();
    planner.refresh_e_factor(target_extruder);
  }
  else {
    SERIAL_ECHO_START();
    SERIAL_CHAR('E');
    SERIAL_CHAR('0' + target_extruder);
=======
  if (parser.seenval('S'))
    planner.set_flow(target_extruder, parser.value_int());
  else {
    SERIAL_ECHO_START();
    SERIAL_CHAR('E', '0' + target_extruder);
>>>>>>> mcu_ctrl
    SERIAL_ECHOPAIR(" Flow: ", planner.flow_percentage[target_extruder]);
    SERIAL_CHAR('%');
    SERIAL_EOL();
  }
}

#endif // EXTRUDERS
