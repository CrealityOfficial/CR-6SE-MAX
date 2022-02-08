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
#include "../../module/motion.h"
#include "../../module/probe.h"
#include "../../feature/bedlevel/bedlevel.h"

/**
 * G30: Do a single Z probe at the current XY
 *
 * Parameters:
 *
 *   X   Probe X position (default current X)
 *   Y   Probe Y position (default current Y)
 *   E   Engage the probe for each probe (default 1)
 */
void GcodeSuite::G30() {
<<<<<<< HEAD
  const xy_pos_t pos = { parser.linearval('X', current_position.x + probe_offset.x),
                         parser.linearval('Y', current_position.y + probe_offset.y) };

  if (!position_is_reachable_by_probe(pos)) return;

  // Disable leveling so the planner won't mess with us
  #if HAS_LEVELING
    set_bed_leveling_enabled(false);
  #endif
=======

  const xy_pos_t pos = { parser.linearval('X', current_position.x + probe.offset_xy.x),
                         parser.linearval('Y', current_position.y + probe.offset_xy.y) };

  if (!probe.can_reach(pos)) return;

  // Disable leveling so the planner won't mess with us
  TERN_(HAS_LEVELING, set_bed_leveling_enabled(false));
>>>>>>> mcu_ctrl

  remember_feedrate_scaling_off();

  const ProbePtRaise raise_after = parser.boolval('E', true) ? PROBE_PT_STOW : PROBE_PT_NONE;
<<<<<<< HEAD
  const float measured_z = probe_at_point(pos, raise_after, 1);
  if (!isnan(measured_z))
    SERIAL_ECHOLNPAIR("Bed X: ", FIXFLOAT(pos.x), " Y: ", FIXFLOAT(pos.y), " Z: ", FIXFLOAT(measured_z));

  restore_feedrate_and_scaling();

  #ifdef Z_AFTER_PROBING
    if (raise_after == PROBE_PT_STOW) move_z_after_probing();
  #endif
=======
  const float measured_z = probe.probe_at_point(pos, raise_after, 1);
  if (!isnan(measured_z))
    SERIAL_ECHOLNPAIR("Bed X: ", pos.x, " Y: ", pos.y, " Z: ", measured_z);

  restore_feedrate_and_scaling();

  if (raise_after == PROBE_PT_STOW)
    probe.move_z_after_probing();
>>>>>>> mcu_ctrl

  report_current_position();
}

#endif // HAS_BED_PROBE
