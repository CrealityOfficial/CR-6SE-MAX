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
#include "../../module/configuration_store.h"
#include "../../core/serial.h"
#include "../../inc/MarlinConfig.h"
#include "../../lcd/dwin/LCD_RTS.h"
=======
#include "../../module/settings.h"
#include "../../core/serial.h"
#include "../../inc/MarlinConfig.h"
>>>>>>> mcu_ctrl

/**
 * M500: Store settings in EEPROM
 */
void GcodeSuite::M500() {
  (void)settings.save();
}

/**
 * M501: Read settings from EEPROM
 */
void GcodeSuite::M501() {
  (void)settings.load();
}

/**
 * M502: Revert to default settings
 */
void GcodeSuite::M502() {
  (void)settings.reset();
}

#if DISABLED(DISABLE_M503)

  /**
   * M503: print settings currently in memory
   */
  void GcodeSuite::M503() {
    (void)settings.report(!parser.boolval('S', true));
  }

#endif // !DISABLE_M503

#if ENABLED(EEPROM_SETTINGS)
<<<<<<< HEAD
=======

  #if ENABLED(MARLIN_DEV_MODE)
    #include "../../libs/hex_print.h"
  #endif

>>>>>>> mcu_ctrl
  /**
   * M504: Validate EEPROM Contents
   */
  void GcodeSuite::M504() {
<<<<<<< HEAD
    if (settings.validate())
      SERIAL_ECHO_MSG("EEPROM OK");
  }
=======
    #if ENABLED(MARLIN_DEV_MODE)
      const bool dowrite = parser.seenval('W');
      if (dowrite || parser.seenval('R')) {
        uint8_t val = 0;
        int addr = parser.value_ushort();
        if (dowrite) {
          val = parser.byteval('V');
          persistentStore.write_data(addr, &val);
          SERIAL_ECHOLNPAIR("Wrote address ", addr, " with ", val);
        }
        else {
          if (parser.seenval('T')) {
            const int endaddr = parser.value_ushort();
            while (addr <= endaddr) {
              persistentStore.read_data(addr, &val);
              SERIAL_ECHOLNPAIR("0x", hex_word(addr), ":", hex_byte(val));
              addr++;
              safe_delay(10);
            }
            SERIAL_EOL();
          }
          else {
            persistentStore.read_data(addr, &val);
            SERIAL_ECHOLNPAIR("Read address ", addr, " and got ", val);
          }
        }
        return;
      }
    #endif

    if (settings.validate())
      SERIAL_ECHO_MSG("EEPROM OK");
  }

>>>>>>> mcu_ctrl
#endif
