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
#pragma once

<<<<<<< HEAD
// Pt100 with 4k7 pullup
const short temptable_147[][2] PROGMEM = {
=======
#define REVERSE_TEMP_SENSOR_RANGE_147 1

// Pt100 with 4k7 pullup
const temp_entry_t temptable_147[] PROGMEM = {
>>>>>>> mcu_ctrl
  // only a few values are needed as the curve is very flat
  PtLine(  0, 100, 4700),
  PtLine( 50, 100, 4700),
  PtLine(100, 100, 4700),
  PtLine(150, 100, 4700),
  PtLine(200, 100, 4700),
  PtLine(250, 100, 4700),
  PtLine(300, 100, 4700)
};
