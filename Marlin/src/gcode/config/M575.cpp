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

#if ENABLED(BAUD_RATE_GCODE)

#include "../gcode.h"

/**
 * M575 - Change serial baud rate
 *
 *   P<index>    - Serial port index. Omit for all.
 *   B<baudrate> - Baud rate (bits per second)
 */
void GcodeSuite::M575() {
<<<<<<< HEAD
  const int32_t baud = parser.ulongval('B');
=======
  int32_t baud = parser.ulongval('B');
  switch (baud) {
    case   24:
    case   96:
    case  192:
    case  384:
    case  576:
    case 1152: baud *= 100; break;
    case  250:
    case  500: baud *= 1000; break;
    case   19: baud = 19200; break;
    case   38: baud = 38400; break;
    case   57: baud = 57600; break;
    case  115: baud = 115200; break;
  }
>>>>>>> mcu_ctrl
  switch (baud) {
    case 2400: case 9600: case 19200: case 38400: case 57600:
    case 115200: case 250000: case 500000: case 1000000: {
      const int8_t port = parser.intval('P', -99);
      const bool set0 = (port == -99 || port == 0);
<<<<<<< HEAD
      if (set0) {
        SERIAL_ECHO_START();
        SERIAL_ECHOLNPAIR(" Serial "
          #if NUM_SERIAL > 1
            , '0',
          #else
            "0"
          #endif
          " baud rate set to ", baud
        );
      }
      #if NUM_SERIAL > 1
        const bool set1 = (port == -99 || port == 1);
        if (set1) {
          SERIAL_ECHO_START();
          SERIAL_ECHOLNPAIR(" Serial ", '1', " baud rate set to ", baud);
        }
=======
      if (set0) SERIAL_ECHO_MSG(" Serial ", '0', " baud rate set to ", baud);
      #if HAS_MULTI_SERIAL
        const bool set1 = (port == -99 || port == 1);
        if (set1) SERIAL_ECHO_MSG(" Serial ", '1', " baud rate set to ", baud);
>>>>>>> mcu_ctrl
      #endif

      SERIAL_FLUSH();

<<<<<<< HEAD
      if (set0) { MYSERIAL0.end(); MYSERIAL0.begin(baud); }

      #if NUM_SERIAL > 1
        if (set1) { MYSERIAL1.end(); MYSERIAL1.begin(baud); }
=======
      if (set0) { MYSERIAL1.end(); MYSERIAL1.begin(baud); }

      #if HAS_MULTI_SERIAL
        if (set1) { MYSERIAL2.end(); MYSERIAL2.begin(baud); }
>>>>>>> mcu_ctrl
      #endif

    } break;
    default: SERIAL_ECHO_MSG("?(B)aud rate implausible.");
  }
}

<<<<<<< HEAD
#endif // NUM_SERIAL > 0 && BAUD_RATE_GCODE
=======
#endif // BAUD_RATE_GCODE
>>>>>>> mcu_ctrl
