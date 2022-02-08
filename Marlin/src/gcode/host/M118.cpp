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

/**
 * M118: Display a message in the host console.
 *
 *  A1  Prepend '// ' for an action command, as in OctoPrint
 *  E1  Have the host 'echo:' the text
 *  Pn  Redirect to another serial port
 *        0 : Announce to all ports
 *      1-9 : Serial ports 1 to 9
 */
void GcodeSuite::M118() {
  bool hasE = false, hasA = false;
<<<<<<< HEAD
  #if NUM_SERIAL > 1
=======
  #if HAS_MULTI_SERIAL
>>>>>>> mcu_ctrl
    int8_t port = -1; // Assume no redirect
  #endif
  char *p = parser.string_arg;
  for (uint8_t i = 3; i--;) {
    // A1, E1, and Pn are always parsed out
    if (!( ((p[0] == 'A' || p[0] == 'E') && p[1] == '1') || (p[0] == 'P' && NUMERIC(p[1])) )) break;
    switch (p[0]) {
      case 'A': hasA = true; break;
      case 'E': hasE = true; break;
<<<<<<< HEAD
      #if NUM_SERIAL > 1
=======
      #if HAS_MULTI_SERIAL
>>>>>>> mcu_ctrl
        case 'P': port = p[1] - '0'; break;
      #endif
    }
    p += 2;
    while (*p == ' ') ++p;
  }

<<<<<<< HEAD
  #if NUM_SERIAL > 1
    const int8_t old_serial = serial_port_index;
    if (WITHIN(port, 0, NUM_SERIAL))
      serial_port_index = (
        port == 0 ? SERIAL_BOTH
        : port == 1 ? SERIAL_PORT
        #ifdef SERIAL_PORT_2
          : port == 2 ? SERIAL_PORT_2
        #endif
        : SERIAL_PORT
      );
  #endif

  if (hasE) SERIAL_ECHO_START();
  if (hasA) SERIAL_ECHOPGM("// ");
  SERIAL_ECHOLN(p);

  #if NUM_SERIAL > 1
    serial_port_index = old_serial;
  #endif
=======
  PORT_REDIRECT(WITHIN(port, 0, NUM_SERIAL) ? (port ? SERIAL_PORTMASK(port - 1) : SerialMask::All) : multiSerial.portMask);

  if (hasE) SERIAL_ECHO_START();
  if (hasA) SERIAL_ECHOPGM("//");
  SERIAL_ECHOLN(p);
>>>>>>> mcu_ctrl
}
