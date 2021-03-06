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
#pragma once

/**
 * MKS SGen pin assignments
<<<<<<< HEAD
 */

#ifndef MCU_LPC1769
  #error "Oops! Make sure you have the LPC1769 environment selected in your IDE."
#endif

#define BOARD_INFO_NAME   "MKS SGen"
#define BOARD_WEBSITE_URL "github.com/makerbase-mks/MKS-SGEN"

#include "../lpc1768/pins_MKS_SBASE.h"

#undef E1_STEP_PIN
#undef E1_DIR_PIN
#undef E1_ENABLE_PIN

//#undef BTN_EN1
//#undef BTN_EN2
//#define BTN_EN1            P1_23   // EXP2.5
//#define BTN_EN2            P1_22   // EXP2.3

#if HAS_TMC220x
  /**
   * TMC2208/TMC2209 stepper drivers
   *
   * The shortage of pins becomes apparent.
   * In the worst case you may have to give up the LCD.
   * RX pins must be interrupt-capable.
   */
  #define X_SERIAL_TX_PIN  P4_29   // J8-2
  #define X_SERIAL_RX_PIN  P4_29   // J8-2

  #define Y_SERIAL_TX_PIN  P2_08   // J8-3
  #define Y_SERIAL_RX_PIN  P2_08   // J8-3

  #define Z_SERIAL_TX_PIN  P2_11   // J8-4
  #define Z_SERIAL_RX_PIN  P2_11   // J8-4
  #define E0_SERIAL_TX_PIN P2_13   // J8-5
  #define E0_SERIAL_RX_PIN P2_13   // J8-5

  // Reduce baud rate to improve software serial reliability
  #define TMC_BAUD_RATE 19200
=======
 *
 * The pins diagram can be found and the following URL:
 * https://github.com/makerbase-mks/MKS-SGen/blob/master/Hardware/MKS%20SGEN%20V1.0_001/MKS%20SGEN%20V1.0_001%20PIN.pdf
 */

#define BOARD_INFO_NAME   "MKS SGen"
#define BOARD_WEBSITE_URL "github.com/makerbase-mks/MKS-SGEN"

#define REQUIRE_LPC1769
#include "../lpc1768/pins_MKS_SBASE.h"

#if HAS_TMC_UART
  /**
   * TMC2208/TMC2209 stepper drivers
   */

  #define X_SERIAL_TX_PIN                  P1_22  // J8-2
  #define X_SERIAL_RX_PIN                  P1_22  // J8-2
  #define Y_SERIAL_TX_PIN                  P1_23  // J8-3
  #define Y_SERIAL_RX_PIN                  P1_23  // J8-3
  #define Z_SERIAL_TX_PIN                  P2_12  // J8-4
  #define Z_SERIAL_RX_PIN                  P2_12  // J8-4
  #define E0_SERIAL_TX_PIN                 P2_11  // J8-5
  #define E0_SERIAL_RX_PIN                 P2_11  // J8-5
  #define E1_SERIAL_TX_PIN                 P4_28  // J8-6
  #define E1_SERIAL_RX_PIN                 P4_28  // J8-6

  // Reduce baud rate to improve software serial reliability
  #define TMC_BAUD_RATE                    19200
>>>>>>> mcu_ctrl
#endif
