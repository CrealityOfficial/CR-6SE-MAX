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

#include "../gcode.h"
#include "../../core/serial.h"
#include "../../module/printcounter.h"
#include "../../libs/duration_t.h"
<<<<<<< HEAD
#include "../../lcd/ultralcd.h"
=======
#include "../../lcd/marlinui.h"
>>>>>>> mcu_ctrl

/**
 * M31: Get the time since the start of SD Print (or last M109)
 */
void GcodeSuite::M31() {
<<<<<<< HEAD
  char buffer[21];
=======
  char buffer[22];
>>>>>>> mcu_ctrl
  duration_t(print_job_timer.duration()).toString(buffer);

  ui.set_status(buffer);

<<<<<<< HEAD
  SERIAL_ECHO_START();
  SERIAL_ECHOLNPAIR("Print time: ", buffer);
=======
  SERIAL_ECHO_MSG("Print time: ", buffer);
>>>>>>> mcu_ctrl
}
