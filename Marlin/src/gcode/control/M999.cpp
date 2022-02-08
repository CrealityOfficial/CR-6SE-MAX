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

<<<<<<< HEAD
#include "../../lcd/ultralcd.h" // for lcd_reset_alert_level
#include "../../Marlin.h"       // for Running
=======
#include "../../lcd/marlinui.h" // for lcd_reset_alert_level
#include "../../MarlinCore.h"   // for marlin_state
>>>>>>> mcu_ctrl
#include "../queue.h"           // for flush_and_request_resend

/**
 * M999: Restart after being stopped
 *
 * Default behavior is to flush the serial buffer and request
 * a resend to the host starting on the last N line received.
 *
 * Sending "M999 S1" will resume printing without flushing the
 * existing command buffer.
<<<<<<< HEAD
 *
 */
void GcodeSuite::M999() {
  Running = true;
=======
 */
void GcodeSuite::M999() {
  marlin_state = MF_RUNNING;
>>>>>>> mcu_ctrl
  ui.reset_alert_level();

  if (parser.boolval('S')) return;

<<<<<<< HEAD
  queue.flush_and_request_resend();
=======
  queue.flush_and_request_resend(queue.ring_buffer.command_port());
>>>>>>> mcu_ctrl
}
