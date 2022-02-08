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

#if HAS_BED_PROBE

#include "../gcode.h"
#include "../../feature/bedlevel/bedlevel.h"
#include "../../module/probe.h"

<<<<<<< HEAD
extern const char SP_Y_STR[], SP_Z_STR[];

=======
>>>>>>> mcu_ctrl
/**
 * M851: Set the nozzle-to-probe offsets in current units
 */
void GcodeSuite::M851() {

  // Show usage with no parameters
  if (!parser.seen("XYZ")) {
<<<<<<< HEAD
    SERIAL_ECHOLNPAIR_P(PSTR(MSG_PROBE_OFFSET " X"), probe_offset.x, SP_Y_STR, probe_offset.y, SP_Z_STR, probe_offset.z);
    return;
  }

  xyz_pos_t offs = probe_offset;

=======
    SERIAL_ECHOLNPAIR_P(
      #if HAS_PROBE_XY_OFFSET
        PSTR(STR_PROBE_OFFSET " X"), probe.offset_xy.x, SP_Y_STR, probe.offset_xy.y, SP_Z_STR
      #else
        PSTR(STR_PROBE_OFFSET " X0 Y0 Z")
      #endif
      , probe.offset.z
    );
    return;
  }

  // Start with current offsets and modify
  xyz_pos_t offs = probe.offset;

  // Assume no errors
>>>>>>> mcu_ctrl
  bool ok = true;

  if (parser.seenval('X')) {
    const float x = parser.value_float();
<<<<<<< HEAD
    if (WITHIN(x, -(X_BED_SIZE), X_BED_SIZE))
      offs.x = x;
    else {
      SERIAL_ECHOLNPAIR("?X out of range (-", int(X_BED_SIZE), " to ", int(X_BED_SIZE), ")");
      ok = false;
    }
=======
    #if HAS_PROBE_XY_OFFSET
      if (WITHIN(x, -(X_BED_SIZE), X_BED_SIZE))
        offs.x = x;
      else {
        SERIAL_ECHOLNPAIR("?X out of range (-", X_BED_SIZE, " to ", X_BED_SIZE, ")");
        ok = false;
      }
    #else
      if (x) SERIAL_ECHOLNPAIR("?X must be 0 (NOZZLE_AS_PROBE)."); // ...but let 'ok' stay true
    #endif
>>>>>>> mcu_ctrl
  }

  if (parser.seenval('Y')) {
    const float y = parser.value_float();
<<<<<<< HEAD
    if (WITHIN(y, -(Y_BED_SIZE), Y_BED_SIZE))
      offs.y = y;
    else {
      SERIAL_ECHOLNPAIR("?Y out of range (-", int(Y_BED_SIZE), " to ", int(Y_BED_SIZE), ")");
      ok = false;
    }
=======
    #if HAS_PROBE_XY_OFFSET
      if (WITHIN(y, -(Y_BED_SIZE), Y_BED_SIZE))
        offs.y = y;
      else {
        SERIAL_ECHOLNPAIR("?Y out of range (-", Y_BED_SIZE, " to ", Y_BED_SIZE, ")");
        ok = false;
      }
    #else
      if (y) SERIAL_ECHOLNPAIR("?Y must be 0 (NOZZLE_AS_PROBE)."); // ...but let 'ok' stay true
    #endif
>>>>>>> mcu_ctrl
  }

  if (parser.seenval('Z')) {
    const float z = parser.value_float();
    if (WITHIN(z, Z_PROBE_OFFSET_RANGE_MIN, Z_PROBE_OFFSET_RANGE_MAX))
      offs.z = z;
    else {
<<<<<<< HEAD
      SERIAL_ECHOLNPAIR("?Z out of range (", int(Z_PROBE_OFFSET_RANGE_MIN), " to ", int(Z_PROBE_OFFSET_RANGE_MAX), ")");
=======
      SERIAL_ECHOLNPAIR("?Z out of range (", Z_PROBE_OFFSET_RANGE_MIN, " to ", Z_PROBE_OFFSET_RANGE_MAX, ")");
>>>>>>> mcu_ctrl
      ok = false;
    }
  }

  // Save the new offsets
<<<<<<< HEAD
  if (ok) probe_offset = offs;
=======
  if (ok) probe.offset = offs;
>>>>>>> mcu_ctrl
}

#endif // HAS_BED_PROBE