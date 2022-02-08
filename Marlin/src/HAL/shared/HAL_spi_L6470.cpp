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

/**
 * Software L6470 SPI functions originally from Arduino Sd2Card Library
 * Copyright (c) 2009 by William Greiman
 */

#include "../../inc/MarlinConfig.h"

<<<<<<< HEAD
#if HAS_DRIVER(L6470)
=======
#if HAS_L64XX
>>>>>>> mcu_ctrl

#include "Delay.h"

#include "../../core/serial.h"
<<<<<<< HEAD
#include "../../libs/L6470/L6470_Marlin.h"
=======
#include "../../libs/L64XX/L64XX_Marlin.h"
>>>>>>> mcu_ctrl

// Make sure GCC optimizes this file.
// Note that this line triggers a bug in GCC which is fixed by casting.
// See the note below.
#pragma GCC optimize (3)

// run at ~4Mhz
<<<<<<< HEAD
uint8_t L6470_SpiTransfer_Mode_0(uint8_t b) { // using Mode 0
=======
inline uint8_t L6470_SpiTransfer_Mode_0(uint8_t b) { // using Mode 0
>>>>>>> mcu_ctrl
  for (uint8_t bits = 8; bits--;) {
    WRITE(L6470_CHAIN_MOSI_PIN, b & 0x80);
    b <<= 1;        // little setup time

    WRITE(L6470_CHAIN_SCK_PIN, HIGH);
    DELAY_NS(125);  // 10 cycles @ 84mhz

    b |= (READ(L6470_CHAIN_MISO_PIN) != 0);

    WRITE(L6470_CHAIN_SCK_PIN, LOW);
    DELAY_NS(125);  // 10 cycles @ 84mhz
  }
  return b;
}

<<<<<<< HEAD
uint8_t L6470_SpiTransfer_Mode_3(uint8_t b) { // using Mode 3
=======
inline uint8_t L6470_SpiTransfer_Mode_3(uint8_t b) { // using Mode 3
>>>>>>> mcu_ctrl
  for (uint8_t bits = 8; bits--;) {
    WRITE(L6470_CHAIN_SCK_PIN, LOW);
    WRITE(L6470_CHAIN_MOSI_PIN, b & 0x80);

    DELAY_NS(125);  // 10 cycles @ 84mhz
<<<<<<< HEAD

    WRITE(L6470_CHAIN_SCK_PIN, HIGH);
=======
    WRITE(L6470_CHAIN_SCK_PIN, HIGH);
    DELAY_NS(125);  // Need more delay for fast CPUs
>>>>>>> mcu_ctrl

    b <<= 1;        // little setup time
    b |= (READ(L6470_CHAIN_MISO_PIN) != 0);
  }
<<<<<<< HEAD

  DELAY_NS(125);  // 10 cycles @ 84mhz
=======
  DELAY_NS(125);    // 10 cycles @ 84mhz
>>>>>>> mcu_ctrl
  return b;
}

/**
<<<<<<< HEAD
 * The following are weak-linked and defined as do-nothing
 * functions by the L6470-Arduino library. They must be
 * defined by the client (Marlin) to provide an SPI interface.
 */

uint8_t L6470_transfer(uint8_t data, int16_t ss_pin, const uint8_t chain_position) {
=======
 * L64XX methods for SPI init and transfer
 */
void L64XX_Marlin::spi_init() {
  OUT_WRITE(L6470_CHAIN_SS_PIN, HIGH);
  OUT_WRITE(L6470_CHAIN_SCK_PIN, HIGH);
  OUT_WRITE(L6470_CHAIN_MOSI_PIN, HIGH);
  SET_INPUT(L6470_CHAIN_MISO_PIN);

  #if PIN_EXISTS(L6470_BUSY)
    SET_INPUT(L6470_BUSY_PIN);
  #endif

  OUT_WRITE(L6470_CHAIN_MOSI_PIN, HIGH);
}

uint8_t L64XX_Marlin::transfer_single(uint8_t data, int16_t ss_pin) {
  // First device in chain has data sent last
  extDigitalWrite(ss_pin, LOW);

  DISABLE_ISRS(); // Disable interrupts during SPI transfer (can't allow partial command to chips)
  const uint8_t data_out = L6470_SpiTransfer_Mode_3(data);
  ENABLE_ISRS();  // Enable interrupts

  extDigitalWrite(ss_pin, HIGH);
  return data_out;
}

uint8_t L64XX_Marlin::transfer_chain(uint8_t data, int16_t ss_pin, uint8_t chain_position) {
>>>>>>> mcu_ctrl
  uint8_t data_out = 0;

  // first device in chain has data sent last
  extDigitalWrite(ss_pin, LOW);

<<<<<<< HEAD
  for (uint8_t i = L6470::chain[0]; (i >= 1) && !spi_abort; i--) {    // stop sending data if spi_abort is active
    DISABLE_ISRS();  // disable interrupts during SPI transfer (can't allow partial command to chips)
    uint8_t temp = L6470_SpiTransfer_Mode_3(uint8_t(i == chain_position ? data : dSPIN_NOP));
    ENABLE_ISRS();  // enable interrupts
=======
  for (uint8_t i = L64XX::chain[0]; !L64xxManager.spi_abort && i >= 1; i--) {   // Send data unless aborted
    DISABLE_ISRS();   // Disable interrupts during SPI transfer (can't allow partial command to chips)
    const uint8_t temp = L6470_SpiTransfer_Mode_3(uint8_t(i == chain_position ? data : dSPIN_NOP));
    ENABLE_ISRS();    // Enable interrupts
>>>>>>> mcu_ctrl
    if (i == chain_position) data_out = temp;
  }

  extDigitalWrite(ss_pin, HIGH);
  return data_out;
}

<<<<<<< HEAD
void L6470_transfer(uint8_t L6470_buf[], const uint8_t length) {
  // first device in chain has data sent last

  if (spi_active) {                    // interrupted SPI transfer so need to
    WRITE(L6470_CHAIN_SS_PIN, HIGH);   // guarantee min high of 650nS
=======
/**
 * Platform-supplied L6470 buffer transfer method
 */
void L64XX_Marlin::transfer(uint8_t L6470_buf[], const uint8_t length) {
  // First device in chain has its data sent last

  if (spi_active) {                   // Interrupted SPI transfer so need to
    WRITE(L6470_CHAIN_SS_PIN, HIGH);  //  guarantee min high of 650ns
>>>>>>> mcu_ctrl
    DELAY_US(1);
  }

  WRITE(L6470_CHAIN_SS_PIN, LOW);
  for (uint8_t i = length; i >= 1; i--)
    L6470_SpiTransfer_Mode_3(uint8_t(L6470_buf[i]));
  WRITE(L6470_CHAIN_SS_PIN, HIGH);
}

<<<<<<< HEAD
void L6470_spi_init() {
  OUT_WRITE(L6470_CHAIN_SS_PIN, HIGH);
  OUT_WRITE(L6470_CHAIN_SCK_PIN, HIGH);
  OUT_WRITE(L6470_CHAIN_MOSI_PIN, HIGH);
  SET_INPUT(L6470_CHAIN_MISO_PIN);

  #if PIN_EXISTS(L6470_BUSY)
    SET_INPUT(L6470_BUSY_PIN);
  #endif

  OUT_WRITE(L6470_CHAIN_MOSI_PIN, HIGH);
}

#pragma GCC reset_options

#endif // HAS_DRIVER(L6470)
=======
#pragma GCC reset_options

#endif // HAS_L64XX
>>>>>>> mcu_ctrl
