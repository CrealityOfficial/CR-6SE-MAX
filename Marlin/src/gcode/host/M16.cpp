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

#include "../../inc/MarlinConfigPre.h"

#if ENABLED(EXPECTED_PRINTER_CHECK)

#include "../gcode.h"
<<<<<<< HEAD
#include "../../Marlin.h"
=======
#include "../../MarlinCore.h"
>>>>>>> mcu_ctrl

/**
 * M16: Expected Printer Check
 */
void GcodeSuite::M16() {

  if (strcmp_P(parser.string_arg, PSTR(MACHINE_NAME)))
<<<<<<< HEAD
    kill(GET_TEXT(MSG_EXPECTED_PRINTER));
=======
    kill(GET_TEXT(MSG_KILL_EXPECTED_PRINTER));
>>>>>>> mcu_ctrl

}

#endif
