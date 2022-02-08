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

#if ENABLED(HOST_PROMPT_SUPPORT) && DISABLED(EMERGENCY_PARSER)

#include "../../feature/host_actions.h"
#include "../gcode.h"
<<<<<<< HEAD
#include "../../Marlin.h"
=======
#include "../../MarlinCore.h"
>>>>>>> mcu_ctrl

/**
 * M876: Handle Prompt Response
 */
void GcodeSuite::M876() {
<<<<<<< HEAD
  if (parser.seenval('S')) host_response_handler((uint8_t)parser.value_int());
=======

  if (parser.seenval('S')) host_response_handler((uint8_t)parser.value_int());

>>>>>>> mcu_ctrl
}

#endif // HOST_PROMPT_SUPPORT && !EMERGENCY_PARSER
