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

#include "../../../inc/MarlinConfigPre.h"
<<<<<<< HEAD
#include "../../../feature/bedlevel/bedlevel.h"
=======
>>>>>>> mcu_ctrl

extern xy_pos_t bilinear_grid_spacing, bilinear_start;
extern xy_float_t bilinear_grid_factor;
extern bed_mesh_t z_values;
float bilinear_z_offset(const xy_pos_t &raw);

void extrapolate_unprobed_bed_level();
void print_bilinear_leveling_grid();
void refresh_bed_level();
#if ENABLED(ABL_BILINEAR_SUBDIVISION)
  void print_bilinear_leveling_grid_virt();
  void bed_level_virt_interpolate();
#endif

#if IS_CARTESIAN && DISABLED(SEGMENT_LEVELED_MOVES)
<<<<<<< HEAD
  void bilinear_line_to_destination(const feedRate_t &scaled_fr_mm_s, uint16_t x_splits=0xFFFF, uint16_t y_splits=0xFFFF);
=======
  void bilinear_line_to_destination(const_feedRate_t scaled_fr_mm_s, uint16_t x_splits=0xFFFF, uint16_t y_splits=0xFFFF);
>>>>>>> mcu_ctrl
#endif

#define _GET_MESH_X(I) float(bilinear_start.x + (I) * bilinear_grid_spacing.x)
#define _GET_MESH_Y(J) float(bilinear_start.y + (J) * bilinear_grid_spacing.y)
#define Z_VALUES_ARR  z_values
