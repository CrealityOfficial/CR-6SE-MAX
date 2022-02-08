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

<<<<<<< HEAD
#if HAS_DRIVER(L6470)

#include "../../gcode.h"
#include "../../../libs/L6470/L6470_Marlin.h"
#include "../../../module/stepper/indirection.h"

inline void echo_yes_no(const bool yes) { serialprintPGM(yes ? PSTR(" YES") : PSTR(" NO ")); }

void L6470_status_decode(const uint16_t status, const uint8_t axis) {
  if (L6470.spi_abort) return;  // don't do anything if set_directions() has occurred
  L6470.say_axis(axis);
  #if ENABLED(L6470_CHITCHAT)
    char temp_buf[20];
    sprintf_P(temp_buf, PSTR("   status: %4x   "), status);
    SERIAL_ECHO(temp_buf);
    print_bin(status);
  #endif
  SERIAL_ECHOPGM("\n...OUTPUT: ");
  serialprintPGM(status & STATUS_HIZ ? PSTR("OFF") : PSTR("ON "));
  SERIAL_ECHOPGM("   BUSY: "); echo_yes_no(!(status & STATUS_BUSY));
  SERIAL_ECHOPGM("   DIR: ");
  serialprintPGM((((status & STATUS_DIR) >> 4) ^ L6470.index_to_dir[axis]) ? PSTR("FORWARD") : PSTR("REVERSE"));
  SERIAL_ECHOPGM("   Last Command: ");
  if (status & STATUS_WRONG_CMD) SERIAL_ECHOPGM("IN");
  SERIAL_ECHOPGM("VALID    ");
  serialprintPGM(status & STATUS_NOTPERF_CMD ? PSTR("Not PERFORMED") : PSTR("COMPLETED    "));
  SERIAL_ECHOPAIR("\n...THERMAL: ", !(status & STATUS_TH_SD) ? "SHUTDOWN" : !(status & STATUS_TH_WRN) ? "WARNING " : "OK      ");
  SERIAL_ECHOPGM("   OVERCURRENT:"); echo_yes_no(!(status & STATUS_OCD));
  SERIAL_ECHOPGM("   STALL:"); echo_yes_no(!(status & STATUS_STEP_LOSS_A) || !(status & STATUS_STEP_LOSS_B));
  SERIAL_ECHOPGM("   STEP-CLOCK MODE:"); echo_yes_no(status & STATUS_SCK_MOD);
=======
#if HAS_L64XX

#include "../../gcode.h"
#include "../../../libs/L64XX/L64XX_Marlin.h"
#include "../../../module/stepper/indirection.h"

void echo_yes_no(const bool yes);

inline void L6470_say_status(const L64XX_axis_t axis) {
  if (L64xxManager.spi_abort) return;
  const L64XX_Marlin::L64XX_shadow_t &sh = L64xxManager.shadow;
  L64xxManager.get_status(axis);
  L64xxManager.say_axis(axis);
  #if ENABLED(L6470_CHITCHAT)
    char temp_buf[20];
    sprintf_P(temp_buf, PSTR("   status: %4x   "), sh.STATUS_AXIS_RAW);
    SERIAL_ECHO(temp_buf);
    print_bin(sh.STATUS_AXIS_RAW);
    switch (sh.STATUS_AXIS_LAYOUT) {
      case L6470_STATUS_LAYOUT: SERIAL_ECHOPGM("   L6470"); break;
      case L6474_STATUS_LAYOUT: SERIAL_ECHOPGM("   L6474"); break;
      case L6480_STATUS_LAYOUT: SERIAL_ECHOPGM("   L6480/powerSTEP01"); break;
    }
  #endif
  SERIAL_ECHOPGM("\n...OUTPUT: ");
  SERIAL_ECHOPGM_P(sh.STATUS_AXIS & STATUS_HIZ ? PSTR("OFF") : PSTR("ON "));
  SERIAL_ECHOPGM("   BUSY: "); echo_yes_no((sh.STATUS_AXIS & STATUS_BUSY) == 0);
  SERIAL_ECHOPGM("   DIR: ");
  SERIAL_ECHOPGM_P((((sh.STATUS_AXIS & STATUS_DIR) >> 4) ^ L64xxManager.index_to_dir[axis]) ? PSTR("FORWARD") : PSTR("REVERSE"));
  if (sh.STATUS_AXIS_LAYOUT == L6480_STATUS_LAYOUT) {
    SERIAL_ECHOPGM("   Last Command: ");
    if (sh.STATUS_AXIS & sh.STATUS_AXIS_WRONG_CMD) SERIAL_ECHOPGM("VALID");
    else                                           SERIAL_ECHOPGM("ERROR");
    SERIAL_ECHOPGM("\n...THERMAL: ");
    switch ((sh.STATUS_AXIS & (sh.STATUS_AXIS_TH_SD | sh.STATUS_AXIS_TH_WRN)) >> 11) {
      case 0: SERIAL_ECHOPGM("DEVICE SHUTDOWN"); break;
      case 1: SERIAL_ECHOPGM("BRIDGE SHUTDOWN"); break;
      case 2: SERIAL_ECHOPGM("WARNING        "); break;
      case 3: SERIAL_ECHOPGM("OK             "); break;
    }
  }
  else {
    SERIAL_ECHOPGM("   Last Command: ");
    if (!(sh.STATUS_AXIS & sh.STATUS_AXIS_WRONG_CMD)) SERIAL_ECHOPGM("IN");
    SERIAL_ECHOPGM("VALID    ");
    SERIAL_ECHOPGM_P(sh.STATUS_AXIS & sh.STATUS_AXIS_NOTPERF_CMD ?  PSTR("COMPLETED    ") : PSTR("Not PERFORMED"));
    SERIAL_ECHOPAIR("\n...THERMAL: ", !(sh.STATUS_AXIS & sh.STATUS_AXIS_TH_SD) ? "SHUTDOWN       " : !(sh.STATUS_AXIS & sh.STATUS_AXIS_TH_WRN) ? "WARNING        " : "OK             ");
  }
  SERIAL_ECHOPGM("   OVERCURRENT:"); echo_yes_no((sh.STATUS_AXIS & sh.STATUS_AXIS_OCD) == 0);
  if (sh.STATUS_AXIS_LAYOUT != L6474_STATUS_LAYOUT) {
    SERIAL_ECHOPGM("   STALL:"); echo_yes_no((sh.STATUS_AXIS & sh.STATUS_AXIS_STEP_LOSS_A) == 0 || (sh.STATUS_AXIS & sh.STATUS_AXIS_STEP_LOSS_B) == 0);
    SERIAL_ECHOPGM("   STEP-CLOCK MODE:"); echo_yes_no((sh.STATUS_AXIS & sh.STATUS_AXIS_SCK_MOD) != 0);
  }
  else {
    SERIAL_ECHOPGM("   STALL: NA "
                   "   STEP-CLOCK MODE: NA"
                   "   UNDER VOLTAGE LOCKOUT: "); echo_yes_no((sh.STATUS_AXIS & sh.STATUS_AXIS_UVLO) == 0);
  }
>>>>>>> mcu_ctrl
  SERIAL_EOL();
}

/**
 * M122: Debug L6470 drivers
 */
void GcodeSuite::M122() {
<<<<<<< HEAD

  L6470.spi_active = true;    // let set_directions() know we're in the middle of a series of SPI transfers

  #define L6470_SAY_STATUS(Q) L6470_status_decode(stepper##Q.getStatus(), Q)

  //if (parser.seen('S'))
  // tmc_set_report_interval(parser.value_bool());
  //else

  #if AXIS_DRIVER_TYPE_X(L6470)
    L6470_SAY_STATUS(X);
  #endif
  #if AXIS_DRIVER_TYPE_X2(L6470)
    L6470_SAY_STATUS(X2);
  #endif
  #if AXIS_DRIVER_TYPE_Y(L6470)
    L6470_SAY_STATUS(Y);
  #endif
  #if AXIS_DRIVER_TYPE_Y2(L6470)
    L6470_SAY_STATUS(Y2);
  #endif
  #if AXIS_DRIVER_TYPE_Z(L6470)
    L6470_SAY_STATUS(Z);
  #endif
  #if AXIS_DRIVER_TYPE_Z2(L6470)
    L6470_SAY_STATUS(Z2);
  #endif
  #if AXIS_DRIVER_TYPE_Z3(L6470)
    L6470_SAY_STATUS(Z3);
  #endif
  #if AXIS_DRIVER_TYPE_E0(L6470)
    L6470_SAY_STATUS(E0);
  #endif
  #if AXIS_DRIVER_TYPE_E1(L6470)
    L6470_SAY_STATUS(E1);
  #endif
  #if AXIS_DRIVER_TYPE_E2(L6470)
    L6470_SAY_STATUS(E2);
  #endif
  #if AXIS_DRIVER_TYPE_E3(L6470)
    L6470_SAY_STATUS(E3);
  #endif
  #if AXIS_DRIVER_TYPE_E4(L6470)
    L6470_SAY_STATUS(E4);
  #endif
  #if AXIS_DRIVER_TYPE_E5(L6470)
    L6470_SAY_STATUS(E5);
  #endif

  L6470.spi_active = false;   // done with all SPI transfers - clear handshake flags
  L6470.spi_abort = false;
}

#endif // HAS_DRIVER(L6470)
=======
  L64xxManager.pause_monitor(true); // Keep monitor_driver() from stealing status
  L64xxManager.spi_active = true;   // Tell set_directions() a series of SPI transfers is underway

  //if (parser.seen('S'))
  //  tmc_set_report_interval(parser.value_bool());
  //else

  #if AXIS_IS_L64XX(X)
    L6470_say_status(X);
  #endif
  #if AXIS_IS_L64XX(X2)
    L6470_say_status(X2);
  #endif
  #if AXIS_IS_L64XX(Y)
    L6470_say_status(Y);
  #endif
  #if AXIS_IS_L64XX(Y2)
    L6470_say_status(Y2);
  #endif
  #if AXIS_IS_L64XX(Z)
    L6470_say_status(Z);
  #endif
  #if AXIS_IS_L64XX(Z2)
    L6470_say_status(Z2);
  #endif
  #if AXIS_IS_L64XX(Z3)
    L6470_say_status(Z3);
  #endif
  #if AXIS_IS_L64XX(Z4)
    L6470_say_status(Z4);
  #endif
  #if AXIS_IS_L64XX(E0)
    L6470_say_status(E0);
  #endif
  #if AXIS_IS_L64XX(E1)
    L6470_say_status(E1);
  #endif
  #if AXIS_IS_L64XX(E2)
    L6470_say_status(E2);
  #endif
  #if AXIS_IS_L64XX(E3)
    L6470_say_status(E3);
  #endif
  #if AXIS_IS_L64XX(E4)
    L6470_say_status(E4);
  #endif
  #if AXIS_IS_L64XX(E5)
    L6470_say_status(E5);
  #endif
  #if AXIS_IS_L64XX(E6)
    L6470_say_status(E6);
  #endif
  #if AXIS_IS_L64XX(E7)
    L6470_say_status(E7);
  #endif

  L64xxManager.spi_active = false;   // done with all SPI transfers - clear handshake flags
  L64xxManager.spi_abort = false;
  L64xxManager.pause_monitor(false);
}

#endif // HAS_L64XX
>>>>>>> mcu_ctrl
