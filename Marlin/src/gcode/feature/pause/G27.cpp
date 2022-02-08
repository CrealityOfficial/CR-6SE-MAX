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


#include "../../../inc/MarlinConfig.h"

#if ENABLED(NOZZLE_PARK_FEATURE)

#include "../../gcode.h"
#include "../../../libs/nozzle.h"
#include "../../../module/motion.h"
<<<<<<< HEAD
#include "../../../lcd/dwin/LCD_RTS.h"
=======

>>>>>>> mcu_ctrl
/**
 * G27: Park the nozzle
 */
void GcodeSuite::G27() {
  // Don't allow nozzle parking without homing first
<<<<<<< HEAD
  // if (axis_unhomed_error()) return;

  if (axis_unhomed_error())
  {
    if(waitway == 7)
    {
      do_blocking_move_to_z(_MIN(current_position.z + NOZZLE_PARK_Z_FEEDRATE, Z_MAX_POS), feedRate_t(NOZZLE_PARK_Z_FEEDRATE));
      if(language_change_font != 0)
      {
        rtscheck.RTS_SndData(ExchangePageBase + 1, ExchangepageAddr);
        change_page_font = 1;
      }
      rtscheck.RTS_SndData(2, MOTOR_FREE_ICON_VP); 
      rtscheck.RTS_SndData(0, PRINT_PROCESS_TITLE_VP);
      rtscheck.RTS_SndData(0, PRINT_PROCESS_VP);
      delay(2);
      for(int j = 0;j < 10;j ++)
      {
        // clean screen.
        rtscheck.RTS_SndData(0, CONTINUE_PRINT_FILE_TEXT_VP + j);
      }
      waitway = 0;
    }
    return;
  }

  nozzle.park(parser.ushortval('P'));

  #ifdef RTS_AVAILABLE
    if(waitway == 7)
    {
      if(language_change_font != 0)
      {
        rtscheck.RTS_SndData(ExchangePageBase + 1, ExchangepageAddr);
        change_page_font = 1;
      }
      rtscheck.RTS_SndData(2, MOTOR_FREE_ICON_VP); 
      rtscheck.RTS_SndData(0, PRINT_PROCESS_TITLE_VP);
      rtscheck.RTS_SndData(0, PRINT_PROCESS_VP);
      delay(2);
      for(int j = 0;j < 10;j ++)
      {
        // clean screen.
        rtscheck.RTS_SndData(0, CONTINUE_PRINT_FILE_TEXT_VP + j);
      }
      waitway = 0;
    }
  #endif
=======
  if (homing_needed_error()) return;
  nozzle.park(parser.ushortval('P'));
>>>>>>> mcu_ctrl
}

#endif // NOZZLE_PARK_FEATURE
