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
// Pt1000 with 4k7 pullup
const short temptable_1047[][2] PROGMEM = {
=======
#define REVERSE_TEMP_SENSOR_RANGE_1047 1

// Pt1000 with 4k7 pullup
const temp_entry_t temptable_1047[] PROGMEM = {
>>>>>>> mcu_ctrl
  // only a few values are needed as the curve is very flat
  PtLine(  0, 1000, 4700),
  PtLine( 50, 1000, 4700),
  PtLine(100, 1000, 4700),
  PtLine(150, 1000, 4700),
  PtLine(200, 1000, 4700),
  PtLine(250, 1000, 4700),
<<<<<<< HEAD
  PtLine(300, 1000, 4700)
=======
  PtLine(300, 1000, 4700),
  PtLine(350, 1000, 4700),
  PtLine(400, 1000, 4700),
  PtLine(450, 1000, 4700),
  PtLine(500, 1000, 4700)
>>>>>>> mcu_ctrl
};
