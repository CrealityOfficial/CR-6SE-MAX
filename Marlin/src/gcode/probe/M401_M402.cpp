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

/**
 * M401: Deploy and activate the Z probe
 */
void GcodeSuite::M401() {
<<<<<<< HEAD
  DEPLOY_PROBE();
=======
  probe.deploy();
  TERN_(PROBE_TARE, probe.tare());
>>>>>>> mcu_ctrl
  report_current_position();
}

/**
 * M402: Deactivate and stow the Z probe
 */
void GcodeSuite::M402() {
<<<<<<< HEAD
  STOW_PROBE();
  #ifdef Z_AFTER_PROBING
    move_z_after_probing();
  #endif
=======
  probe.stow();
  probe.move_z_after_probing();
>>>>>>> mcu_ctrl
  report_current_position();
}

#endif // HAS_BED_PROBE
