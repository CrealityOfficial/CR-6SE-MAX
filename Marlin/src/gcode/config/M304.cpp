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

#if ENABLED(PIDTEMPBED)

#include "../gcode.h"
#include "../../module/temperature.h"

<<<<<<< HEAD
void GcodeSuite::M304() {
=======
/**
 * M304 - Set and/or Report the current Bed PID values
 *
 *  P<pval> - Set the P value
 *  I<ival> - Set the I value
 *  D<dval> - Set the D value
 */
void GcodeSuite::M304() {

>>>>>>> mcu_ctrl
  if (parser.seen('P')) thermalManager.temp_bed.pid.Kp = parser.value_float();
  if (parser.seen('I')) thermalManager.temp_bed.pid.Ki = scalePID_i(parser.value_float());
  if (parser.seen('D')) thermalManager.temp_bed.pid.Kd = scalePID_d(parser.value_float());

<<<<<<< HEAD
  SERIAL_ECHO_START();
  SERIAL_ECHOLNPAIR(" p:", thermalManager.temp_bed.pid.Kp,
                    " i:", unscalePID_i(thermalManager.temp_bed.pid.Ki),
                    " d:", unscalePID_d(thermalManager.temp_bed.pid.Kd));
=======
  SERIAL_ECHO_MSG(" p:", thermalManager.temp_bed.pid.Kp,
                  " i:", unscalePID_i(thermalManager.temp_bed.pid.Ki),
                  " d:", unscalePID_d(thermalManager.temp_bed.pid.Kd));

>>>>>>> mcu_ctrl
}

#endif // PIDTEMPBED
