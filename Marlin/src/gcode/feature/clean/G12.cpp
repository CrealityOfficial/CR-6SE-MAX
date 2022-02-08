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

#if ENABLED(NOZZLE_CLEAN_FEATURE)

#include "../../../libs/nozzle.h"

#include "../../gcode.h"
#include "../../parser.h"
#include "../../../module/motion.h"

#if HAS_LEVELING
  #include "../../../module/planner.h"
  #include "../../../feature/bedlevel/bedlevel.h"
#endif

/**
 * G12: Clean the nozzle
<<<<<<< HEAD
 */
void GcodeSuite::G12() {
  // Don't allow nozzle cleaning without homing first
  if (axis_unhomed_error()) return;
=======
 *
 *  E<bool>          : 0=Never or 1=Always apply the "software endstop" limits
 *  P0 S<strokes>    : Stroke cleaning with S strokes
 *  P1 Sn T<objects> : Zigzag cleaning with S repeats and T zigzags
 *  P2 Sn R<radius>  : Circle cleaning with S repeats and R radius
 */
void GcodeSuite::G12() {
  // Don't allow nozzle cleaning without homing first
  if (homing_needed_error()) return;

  #ifdef WIPE_SEQUENCE_COMMANDS
    if (!parser.seen_any()) {
      gcode.process_subcommands_now_P(PSTR(WIPE_SEQUENCE_COMMANDS));
      return;
    }
  #endif
>>>>>>> mcu_ctrl

  const uint8_t pattern = parser.ushortval('P', 0),
                strokes = parser.ushortval('S', NOZZLE_CLEAN_STROKES),
                objects = parser.ushortval('T', NOZZLE_CLEAN_TRIANGLES);
<<<<<<< HEAD
  const float radius = parser.floatval('R', NOZZLE_CLEAN_CIRCLE_RADIUS);
=======
  const float radius = parser.linearval('R', NOZZLE_CLEAN_CIRCLE_RADIUS);
>>>>>>> mcu_ctrl

  const bool seenxyz = parser.seen("XYZ");
  const uint8_t cleans =  (!seenxyz || parser.boolval('X') ? _BV(X_AXIS) : 0)
                        | (!seenxyz || parser.boolval('Y') ? _BV(Y_AXIS) : 0)
<<<<<<< HEAD
                        #if DISABLED(NOZZLE_CLEAN_NO_Z)
                          | (!seenxyz || parser.boolval('Z') ? _BV(Z_AXIS) : 0)
                        #endif
=======
                        | TERN(NOZZLE_CLEAN_NO_Z, 0, (!seenxyz || parser.boolval('Z') ? _BV(Z_AXIS) : 0))
>>>>>>> mcu_ctrl
                      ;

  #if HAS_LEVELING
    // Disable bed leveling if cleaning Z
    TEMPORARY_BED_LEVELING_STATE(!TEST(cleans, Z_AXIS) && planner.leveling_active);
  #endif

<<<<<<< HEAD
  nozzle.clean(pattern, strokes, radius, objects, cleans);
=======
  SET_SOFT_ENDSTOP_LOOSE(!parser.boolval('E'));

  nozzle.clean(pattern, strokes, radius, objects, cleans);

  SET_SOFT_ENDSTOP_LOOSE(false);
>>>>>>> mcu_ctrl
}

#endif // NOZZLE_CLEAN_FEATURE
