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

// R25 = 100 kOhm, beta25 = 3950 K, 10 kOhm pull-up, NTCS0603E3104FHT
<<<<<<< HEAD
const short temptable_8[][2] PROGMEM = {
=======
const temp_entry_t temptable_8[] PROGMEM = {
>>>>>>> mcu_ctrl
  { OV(   1), 704 },
  { OV(  54), 216 },
  { OV( 107), 175 },
  { OV( 160), 152 },
  { OV( 213), 137 },
  { OV( 266), 125 },
  { OV( 319), 115 },
  { OV( 372), 106 },
  { OV( 425),  99 },
  { OV( 478),  91 },
  { OV( 531),  85 },
  { OV( 584),  78 },
  { OV( 637),  71 },
  { OV( 690),  65 },
  { OV( 743),  58 },
  { OV( 796),  50 },
  { OV( 849),  42 },
  { OV( 902),  31 },
  { OV( 955),  17 },
  { OV(1008),   0 }
};
