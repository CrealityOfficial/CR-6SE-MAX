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
#include "../../module/motion.h"

/**
 * M220: Set speed percentage factor, aka "Feed Rate"
 *
 * Parameters
 *   S<percent> : Set the feed rate percentage factor
 *
<<<<<<< HEAD
 * With PRUSA_MMU2...
=======
 * Report the current speed percentage factor if no parameter is specified
 *
 * For MMU2 and MMU2S devices...
>>>>>>> mcu_ctrl
 *   B : Flag to back up the current factor
 *   R : Flag to restore the last-saved factor
 */
void GcodeSuite::M220() {

<<<<<<< HEAD
  #if ENABLED(PRUSA_MMU2)
    static int16_t backup_feedrate_percentage = 100;
    if (parser.seen('B')) backup_feedrate_percentage = feedrate_percentage;
    if (parser.seen('R')) feedrate_percentage = backup_feedrate_percentage;
  #endif

  if (parser.seenval('S')) feedrate_percentage = parser.value_int();

=======
  static int16_t backup_feedrate_percentage = 100;
  if (parser.seen('B')) backup_feedrate_percentage = feedrate_percentage;
  if (parser.seen('R')) feedrate_percentage = backup_feedrate_percentage;

  if (parser.seenval('S')) feedrate_percentage = parser.value_int();

  if (!parser.seen_any()) {
    SERIAL_ECHOPAIR("FR:", feedrate_percentage);
    SERIAL_CHAR('%');
    SERIAL_EOL();
  }
>>>>>>> mcu_ctrl
}
