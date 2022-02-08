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

/**
<<<<<<< HEAD
 * unified.cpp - Unified Bed Leveling
=======
 * M421.cpp - Unified Bed Leveling
>>>>>>> mcu_ctrl
 */

#include "../../../inc/MarlinConfig.h"

#if ENABLED(AUTO_BED_LEVELING_UBL)

#include "../../gcode.h"
#include "../../../feature/bedlevel/bedlevel.h"

#if ENABLED(EXTENSIBLE_UI)
<<<<<<< HEAD
  #include "../../../lcd/extensible_ui/ui_api.h"
=======
  #include "../../../lcd/extui/ui_api.h"
>>>>>>> mcu_ctrl
#endif

/**
 * M421: Set a single Mesh Bed Leveling Z coordinate
 *
 * Usage:
<<<<<<< HEAD
 *   M421 I<xindex> J<yindex> Z<linear>
 *   M421 I<xindex> J<yindex> Q<offset>
 *   M421 I<xindex> J<yindex> N
 *   M421 C Z<linear>
 *   M421 C Q<offset>
=======
 *   M421 I<xindex> J<yindex> Z<linear>  : Set the Mesh Point IJ to the Z value
 *   M421 I<xindex> J<yindex> Q<offset>  : Add the Q value to the Mesh Point IJ
 *   M421 I<xindex> J<yindex> N          : Set the Mesh Point IJ to NAN (not set)
 *   M421 C Z<linear>                    : Set the closest Mesh Point to the Z value
 *   M421 C Q<offset>                    : Add the Q value to the closest Mesh Point
>>>>>>> mcu_ctrl
 */
void GcodeSuite::M421() {
  xy_int8_t ij = { int8_t(parser.intval('I', -1)), int8_t(parser.intval('J', -1)) };
  const bool hasI = ij.x >= 0,
             hasJ = ij.y >= 0,
<<<<<<< HEAD
             hasC = parser.seen('C'),
             hasN = parser.seen('N'),
             hasZ = parser.seen('Z'),
             hasQ = !hasZ && parser.seen('Q');

  if (hasC) ij = ubl.find_closest_mesh_point_of_type(REAL, current_position);

  if (int(hasC) + int(hasI && hasJ) != 1 || !(hasZ || hasQ || hasN))
    SERIAL_ERROR_MSG(MSG_ERR_M421_PARAMETERS);
  else if (!WITHIN(ij.x, 0, GRID_MAX_POINTS_X - 1) || !WITHIN(ij.y, 0, GRID_MAX_POINTS_Y - 1))
    SERIAL_ERROR_MSG(MSG_ERR_MESH_XY);
  else {
    float &zval = ubl.z_values[ij.x][ij.y];
    zval = hasN ? NAN : parser.value_linear_units() + (hasQ ? zval : 0);
    #if ENABLED(EXTENSIBLE_UI)
      ExtUI::onMeshUpdate(ij.x, ij.y, zval);
    #endif
=======
             hasC = parser.seen_test('C'),
             hasN = parser.seen_test('N'),
             hasZ = parser.seen('Z'),
             hasQ = !hasZ && parser.seen('Q');

  if (hasC) ij = ubl.find_closest_mesh_point_of_type(CLOSEST, current_position);

  // Test for bad parameter combinations
  if (int(hasC) + int(hasI && hasJ) != 1 || !(hasZ || hasQ || hasN))
    SERIAL_ERROR_MSG(STR_ERR_M421_PARAMETERS);

  // Test for I J out of range
  else if (!WITHIN(ij.x, 0, GRID_MAX_POINTS_X - 1) || !WITHIN(ij.y, 0, GRID_MAX_POINTS_Y - 1))
    SERIAL_ERROR_MSG(STR_ERR_MESH_XY);
  else {
    float &zval = ubl.z_values[ij.x][ij.y];                               // Altering this Mesh Point
    zval = hasN ? NAN : parser.value_linear_units() + (hasQ ? zval : 0);  // N=NAN, Z=NEWVAL, or Q=ADDVAL
    TERN_(EXTENSIBLE_UI, ExtUI::onMeshUpdate(ij.x, ij.y, zval));          // Ping ExtUI in case it's showing the mesh
>>>>>>> mcu_ctrl
  }
}

#endif // AUTO_BED_LEVELING_UBL
