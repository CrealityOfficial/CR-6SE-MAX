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

#if ENABLED(EXPERIMENTAL_I2CBUS)

#include "../../gcode.h"

<<<<<<< HEAD
#include "../../../Marlin.h" // for i2c
=======
#include "../../../feature/twibus.h"
>>>>>>> mcu_ctrl

/**
 * M260: Send data to a I2C slave device
 *
<<<<<<< HEAD
 * This is a PoC, the formating and arguments for the GCODE will
=======
 * This is a PoC, the formatting and arguments for the GCODE will
>>>>>>> mcu_ctrl
 * change to be more compatible, the current proposal is:
 *
 *  M260 A<slave device address base 10> ; Sets the I2C slave address the data will be sent to
 *
 *  M260 B<byte-1 value in base 10>
 *  M260 B<byte-2 value in base 10>
 *  M260 B<byte-3 value in base 10>
 *
 *  M260 S1 ; Send the buffered data and reset the buffer
 *  M260 R1 ; Reset the buffer without sending data
<<<<<<< HEAD
 *
=======
>>>>>>> mcu_ctrl
 */
void GcodeSuite::M260() {
  // Set the target address
  if (parser.seen('A')) i2c.address(parser.value_byte());

  // Add a new byte to the buffer
  if (parser.seen('B')) i2c.addbyte(parser.value_byte());

  // Flush the buffer to the bus
  if (parser.seen('S')) i2c.send();

  // Reset and rewind the buffer
  else if (parser.seen('R')) i2c.reset();
}

/**
 * M261: Request X bytes from I2C slave device
 *
 * Usage: M261 A<slave device address base 10> B<number of bytes>
 */
void GcodeSuite::M261() {
  if (parser.seen('A')) i2c.address(parser.value_byte());

  uint8_t bytes = parser.byteval('B', 1);

  if (i2c.addr && bytes && bytes <= TWIBUS_BUFFER_SIZE)
    i2c.relay(bytes);
  else
    SERIAL_ERROR_MSG("Bad i2c request");
}

#endif
