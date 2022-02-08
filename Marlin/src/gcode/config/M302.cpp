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

#if ENABLED(PREVENT_COLD_EXTRUSION)

#include "../gcode.h"
#include "../../module/temperature.h"

/**
 * M302: Allow cold extrudes, or set the minimum extrude temperature
 *
 *       S<temperature> sets the minimum extrude temperature
 *       P<bool> enables (1) or disables (0) cold extrusion
 *
 *  Examples:
 *
 *       M302         ; report current cold extrusion state
 *       M302 P0      ; enable cold extrusion checking
<<<<<<< HEAD
 *       M302 P1      ; disables cold extrusion checking
=======
 *       M302 P1      ; disable cold extrusion checking
>>>>>>> mcu_ctrl
 *       M302 S0      ; always allow extrusion (disables checking)
 *       M302 S170    ; only allow extrusion above 170
 *       M302 S170 P1 ; set min extrude temp to 170 but leave disabled
 */
void GcodeSuite::M302() {
  const bool seen_S = parser.seen('S');
  if (seen_S) {
    thermalManager.extrude_min_temp = parser.value_celsius();
    thermalManager.allow_cold_extrude = (thermalManager.extrude_min_temp == 0);
  }

  if (parser.seen('P'))
    thermalManager.allow_cold_extrude = (thermalManager.extrude_min_temp == 0) || parser.value_bool();
  else if (!seen_S) {
    // Report current state
    SERIAL_ECHO_START();
    SERIAL_ECHOPGM("Cold extrudes are ");
<<<<<<< HEAD
    serialprintPGM(thermalManager.allow_cold_extrude ? PSTR("en") : PSTR("dis"));
=======
    SERIAL_ECHOPGM_P(thermalManager.allow_cold_extrude ? PSTR("en") : PSTR("dis"));
>>>>>>> mcu_ctrl
    SERIAL_ECHOLNPAIR("abled (min temp ", thermalManager.extrude_min_temp, "C)");
  }
}

#endif // PREVENT_COLD_EXTRUSION
