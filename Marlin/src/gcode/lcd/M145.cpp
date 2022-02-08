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

<<<<<<< HEAD
#if HOTENDS && HAS_LCD_MENU

#include "../gcode.h"
#include "../../lcd/ultralcd.h"
=======
#if PREHEAT_COUNT

#include "../gcode.h"
#include "../../lcd/marlinui.h"

#if HAS_HOTEND
  #include "../../module/temperature.h"
#endif
>>>>>>> mcu_ctrl

/**
 * M145: Set the heatup state for a material in the LCD menu
 *
 *   S<material>
 *   H<hotend temp>
 *   B<bed temp>
 *   F<fan speed>
 */
void GcodeSuite::M145() {
  const uint8_t material = (uint8_t)parser.intval('S');
<<<<<<< HEAD
  if (material >= COUNT(ui.preheat_hotend_temp))
    SERIAL_ERROR_MSG(MSG_ERR_MATERIAL_INDEX);
  else {
    int v;
    if (parser.seenval('H')) {
      v = parser.value_int();
      ui.preheat_hotend_temp[material] = constrain(v, EXTRUDE_MINTEMP, HEATER_0_MAXTEMP - 15);
    }
    if (parser.seenval('F')) {
      v = parser.value_int();
      ui.preheat_fan_speed[material] = (uint8_t)constrain(v, 0, 255);
    }
    #if TEMP_SENSOR_BED != 0
      if (parser.seenval('B')) {
        v = parser.value_int();
        ui.preheat_bed_temp[material] = constrain(v, BED_MINTEMP, BED_MAXTEMP - 10);
      }
=======
  if (material >= PREHEAT_COUNT)
    SERIAL_ERROR_MSG(STR_ERR_MATERIAL_INDEX);
  else {
    preheat_t &mat = ui.material_preset[material];
    #if HAS_HOTEND
      if (parser.seenval('H'))
        mat.hotend_temp = constrain(parser.value_int(), EXTRUDE_MINTEMP, thermalManager.hotend_max_target(0));
    #endif
    #if HAS_HEATED_BED
      if (parser.seenval('B'))
        mat.bed_temp = constrain(parser.value_int(), BED_MINTEMP, BED_MAX_TARGET);
    #endif
    #if HAS_FAN
      if (parser.seenval('F'))
        mat.fan_speed = constrain(parser.value_int(), 0, 255);
>>>>>>> mcu_ctrl
    #endif
  }
}

<<<<<<< HEAD
#endif // HOTENDS && HAS_LCD_MENU
=======
#endif // PREHEAT_COUNT
>>>>>>> mcu_ctrl
