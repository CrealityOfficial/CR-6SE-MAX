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

/**
 * M111: Set the debug level
 */
void GcodeSuite::M111() {
  if (parser.seen('S')) marlin_debug_flags = parser.byteval('S');

<<<<<<< HEAD
  static const char str_debug_1[] PROGMEM = MSG_DEBUG_ECHO,
                    str_debug_2[] PROGMEM = MSG_DEBUG_INFO,
                    str_debug_4[] PROGMEM = MSG_DEBUG_ERRORS,
                    str_debug_8[] PROGMEM = MSG_DEBUG_DRYRUN,
                    str_debug_16[] PROGMEM = MSG_DEBUG_COMMUNICATION
                    #if ENABLED(DEBUG_LEVELING_FEATURE)
                      , str_debug_lvl[] PROGMEM = MSG_DEBUG_LEVELING
                    #endif
                    ;

  static PGM_P const debug_strings[] PROGMEM = {
    str_debug_1, str_debug_2, str_debug_4, str_debug_8, str_debug_16
    #if ENABLED(DEBUG_LEVELING_FEATURE)
      , str_debug_lvl
    #endif
  };

  SERIAL_ECHO_START();
  SERIAL_ECHOPGM(MSG_DEBUG_PREFIX);
  if (marlin_debug_flags) {
    uint8_t comma = 0;
    for (uint8_t i = 0; i < COUNT(debug_strings); i++) {
      if (TEST(marlin_debug_flags, i)) {
        if (comma++) SERIAL_CHAR(',');
        serialprintPGM((char*)pgm_read_ptr(&debug_strings[i]));
=======
  static PGMSTR(str_debug_1, STR_DEBUG_ECHO);
  static PGMSTR(str_debug_2, STR_DEBUG_INFO);
  static PGMSTR(str_debug_4, STR_DEBUG_ERRORS);
  static PGMSTR(str_debug_8, STR_DEBUG_DRYRUN);
  static PGMSTR(str_debug_16, STR_DEBUG_COMMUNICATION);
  #if ENABLED(DEBUG_LEVELING_FEATURE)
    static PGMSTR(str_debug_lvl, STR_DEBUG_LEVELING);
  #endif

  static PGM_P const debug_strings[] PROGMEM = {
    str_debug_1, str_debug_2, str_debug_4, str_debug_8, str_debug_16,
    TERN_(DEBUG_LEVELING_FEATURE, str_debug_lvl)
  };

  SERIAL_ECHO_START();
  SERIAL_ECHOPGM(STR_DEBUG_PREFIX);
  if (marlin_debug_flags) {
    uint8_t comma = 0;
    LOOP_L_N(i, COUNT(debug_strings)) {
      if (TEST(marlin_debug_flags, i)) {
        if (comma++) SERIAL_CHAR(',');
        SERIAL_ECHOPGM_P((char*)pgm_read_ptr(&debug_strings[i]));
>>>>>>> mcu_ctrl
      }
    }
  }
  else {
<<<<<<< HEAD
    SERIAL_ECHOPGM(MSG_DEBUG_OFF);
    #if !defined(__AVR__) || !defined(USBCON)
      #if ENABLED(SERIAL_STATS_RX_BUFFER_OVERRUNS)
        SERIAL_ECHOPAIR("\nBuffer Overruns: ", MYSERIAL0.buffer_overruns());
      #endif

      #if ENABLED(SERIAL_STATS_RX_FRAMING_ERRORS)
        SERIAL_ECHOPAIR("\nFraming Errors: ", MYSERIAL0.framing_errors());
      #endif

      #if ENABLED(SERIAL_STATS_DROPPED_RX)
        SERIAL_ECHOPAIR("\nDropped bytes: ", MYSERIAL0.dropped());
      #endif

      #if ENABLED(SERIAL_STATS_MAX_RX_QUEUED)
        SERIAL_ECHOPAIR("\nMax RX Queue Size: ", MYSERIAL0.rxMaxEnqueued());
      #endif
    #endif //  !defined(__AVR__) || !defined(USBCON)
=======
    SERIAL_ECHOPGM(STR_DEBUG_OFF);
    #if !defined(__AVR__) || !defined(USBCON)
      #if ENABLED(SERIAL_STATS_RX_BUFFER_OVERRUNS)
        SERIAL_ECHOPAIR("\nBuffer Overruns: ", MYSERIAL1.buffer_overruns());
      #endif

      #if ENABLED(SERIAL_STATS_RX_FRAMING_ERRORS)
        SERIAL_ECHOPAIR("\nFraming Errors: ", MYSERIAL1.framing_errors());
      #endif

      #if ENABLED(SERIAL_STATS_DROPPED_RX)
        SERIAL_ECHOPAIR("\nDropped bytes: ", MYSERIAL1.dropped());
      #endif

      #if ENABLED(SERIAL_STATS_MAX_RX_QUEUED)
        SERIAL_ECHOPAIR("\nMax RX Queue Size: ", MYSERIAL1.rxMaxEnqueued());
      #endif
    #endif // !__AVR__ || !USBCON
>>>>>>> mcu_ctrl
  }
  SERIAL_EOL();
}
