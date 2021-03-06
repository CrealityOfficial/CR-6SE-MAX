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

/**
 * planner_bezier.h
 *
 * Compute and buffer movement commands for Bézier curves
<<<<<<< HEAD
 *
=======
>>>>>>> mcu_ctrl
 */

#include "../core/types.h"

void cubic_b_spline(
  const xyze_pos_t &position,       // current position
  const xyze_pos_t &target,         // target position
  const xy_pos_t (&offsets)[2],     // a pair of offsets
<<<<<<< HEAD
  const feedRate_t &scaled_fr_mm_s, // mm/s scaled by feedrate %
=======
  const_feedRate_t scaled_fr_mm_s,  // mm/s scaled by feedrate %
>>>>>>> mcu_ctrl
  const uint8_t extruder
);
