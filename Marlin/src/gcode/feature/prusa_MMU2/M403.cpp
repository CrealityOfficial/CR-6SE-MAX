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

#include "../../../inc/MarlinConfigPre.h"

<<<<<<< HEAD
#if ENABLED(PRUSA_MMU2)

#include "../../gcode.h"
#include "../../../feature/prusa_MMU2/mmu2.h"
=======
#if HAS_PRUSA_MMU2

#include "../../gcode.h"
#include "../../../feature/mmu/mmu2.h"
>>>>>>> mcu_ctrl

/**
 * M403: Set filament type for MMU2
 *
 * Valid filament type values:
 *
 *  0   Default
 *  1   Flexible
 *  2   PVA
 */
void GcodeSuite::M403() {
  int8_t index = parser.intval('E', -1),
         type = parser.intval('F', -1);

<<<<<<< HEAD
  if (WITHIN(index, 0, 4) && WITHIN(type, 0, 2))
=======
  if (WITHIN(index, 0, EXTRUDERS - 1) && WITHIN(type, 0, 2))
>>>>>>> mcu_ctrl
    mmu2.set_filament_type(index, type);
  else
    SERIAL_ECHO_MSG("M403 - bad arguments.");
}

<<<<<<< HEAD
#endif // PRUSA_MMU2
=======
#endif // HAS_PRUSA_MMU2
>>>>>>> mcu_ctrl
