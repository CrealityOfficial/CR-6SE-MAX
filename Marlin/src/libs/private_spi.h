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

#include "softspi.h"
#include <stdint.h>

template<uint8_t MisoPin, uint8_t MosiPin, uint8_t SckPin>
class SPIclass {
  static SoftSPI<MisoPin, MosiPin, SckPin> softSPI;
  public:
    FORCE_INLINE static void init() { softSPI.begin(); }
    FORCE_INLINE static void send(uint8_t data) { softSPI.send(data); }
    FORCE_INLINE static uint8_t receive() { return softSPI.receive(); }
};

// Hardware SPI
template<>
<<<<<<< HEAD
class SPIclass<MISO_PIN, MOSI_PIN, SCK_PIN> {
  public:
    FORCE_INLINE static void init() {
      OUT_WRITE(SCK_PIN, LOW);
      OUT_WRITE(MOSI_PIN, HIGH);
      SET_INPUT_PULLUP(MISO_PIN);
    }
    FORCE_INLINE static uint8_t receive() {
      #if defined(__AVR__) || defined(__MK20DX256__) || defined(__MK64FX512__) || defined(__MK66FX1M0__)
=======
class SPIclass<SD_MISO_PIN, SD_MOSI_PIN, SD_SCK_PIN> {
  public:
    FORCE_INLINE static void init() {
      OUT_WRITE(SD_SCK_PIN, LOW);
      OUT_WRITE(SD_MOSI_PIN, HIGH);
      SET_INPUT_PULLUP(SD_MISO_PIN);
    }
    FORCE_INLINE static uint8_t receive() {
      #if defined(__AVR__) || defined(__MK20DX256__) || defined(__MK64FX512__) || defined(__MK66FX1M0__) || defined(__IMXRT1062__)
>>>>>>> mcu_ctrl
        SPDR = 0;
        for (;!TEST(SPSR, SPIF););
        return SPDR;
      #else
        return spiRec();
      #endif
    }
};
