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
#include "../../module/tool_change.h"

<<<<<<< HEAD
#if ENABLED(DEBUG_LEVELING_FEATURE) || EXTRUDERS > 1
  #include "../../module/motion.h"
#endif

#if ENABLED(PRUSA_MMU2)
  #include "../../feature/prusa_MMU2/mmu2.h"
=======
#if EITHER(HAS_MULTI_EXTRUDER, DEBUG_LEVELING_FEATURE)
  #include "../../module/motion.h"
#endif

#if HAS_PRUSA_MMU2
  #include "../../feature/mmu/mmu2.h"
>>>>>>> mcu_ctrl
#endif

#define DEBUG_OUT ENABLED(DEBUG_LEVELING_FEATURE)
#include "../../core/debug_out.h"

/**
 * T0-T<n>: Switch tool, usually switching extruders
 *
 *   F[units/min] Set the movement feedrate
 *   S1           Don't move the tool in XY after change
 *
<<<<<<< HEAD
 * For PRUSA_MMU2:
=======
 * For PRUSA_MMU2(S) and EXTENDABLE_EMU_MMU2(S)
>>>>>>> mcu_ctrl
 *   T[n] Gcode to extrude at least 38.10 mm at feedrate 19.02 mm/s must follow immediately to load to extruder wheels.
 *   T?   Gcode to extrude shouldn't have to follow. Load to extruder wheels is done automatically.
 *   Tx   Same as T?, but nozzle doesn't have to be preheated. Tc requires a preheated nozzle to finish filament load.
 *   Tc   Load to nozzle after filament was prepared by Tc and nozzle is already heated.
 */
<<<<<<< HEAD
void GcodeSuite::T(const uint8_t tool_index) {

  if (DEBUGGING(LEVELING)) {
    DEBUG_ECHOLNPAIR(">>> T(", tool_index, ")");
    DEBUG_POS("BEFORE", current_position);
  }

  #if ENABLED(PRUSA_MMU2)
=======
void GcodeSuite::T(const int8_t tool_index) {

  DEBUG_SECTION(log_T, "T", DEBUGGING(LEVELING));
  if (DEBUGGING(LEVELING)) DEBUG_ECHOLNPAIR("...(", tool_index, ")");

  // Count this command as movement / activity
  reset_stepper_timeout();

  #if HAS_PRUSA_MMU2
>>>>>>> mcu_ctrl
    if (parser.string_arg) {
      mmu2.tool_change(parser.string_arg);   // Special commands T?/Tx/Tc
      return;
    }
  #endif

<<<<<<< HEAD
  #if EXTRUDERS < 2

    tool_change(tool_index);

  #else

    tool_change(
      tool_index,
      (tool_index == active_extruder) || parser.boolval('S')
    );

  #endif

  if (DEBUGGING(LEVELING)) {
    DEBUG_POS("AFTER", current_position);
    DEBUG_ECHOLNPGM("<<< T()");
  }
=======
  tool_change(tool_index
    #if HAS_MULTI_EXTRUDER
      ,  TERN(PARKING_EXTRUDER, false, tool_index == active_extruder) // For PARKING_EXTRUDER motion is decided in tool_change()
      || parser.boolval('S')
    #endif
  );
>>>>>>> mcu_ctrl
}
