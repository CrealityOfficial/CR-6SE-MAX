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

#include "../inc/MarlinConfig.h"

<<<<<<< HEAD
#if ENABLED(SDIO_SUPPORT)
=======
#include "SdInfo.h"
#include "disk_io_driver.h"
>>>>>>> mcu_ctrl

bool SDIO_Init();
bool SDIO_ReadBlock(uint32_t block, uint8_t *dst);
bool SDIO_WriteBlock(uint32_t block, const uint8_t *src);

<<<<<<< HEAD
class Sd2Card {
  public:
    bool init(uint8_t sckRateID = 0, uint8_t chipSelectPin = 0) { return SDIO_Init(); }
    bool readBlock(uint32_t block, uint8_t *dst) { return SDIO_ReadBlock(block, dst); }
    bool writeBlock(uint32_t block, const uint8_t *src) { return SDIO_WriteBlock(block, src); }
};

#endif // SDIO_SUPPORT
=======
class DiskIODriver_SDIO : public DiskIODriver {
  public:
    bool init(const uint8_t sckRateID=0, const pin_t chipSelectPin=0) override { return SDIO_Init(); }

    bool readCSD(csd_t *csd)                              override { return false; }

    bool readStart(const uint32_t block)                  override { return false; }
    bool readData(uint8_t *dst)                           override { return false; }
    bool readStop()                                       override { return false; }

    bool writeStart(const uint32_t block, const uint32_t) override { return false; }
    bool writeData(const uint8_t *src)                    override { return false; }
    bool writeStop()                                      override { return false; }

    bool readBlock(uint32_t block, uint8_t *dst)          override { return SDIO_ReadBlock(block, dst); }
    bool writeBlock(uint32_t block, const uint8_t *src)   override { return SDIO_WriteBlock(block, src); }

    uint32_t cardSize()                                   override { return 0; }

    bool isReady()                                        override { return true; }

    void idle()                                           override {}
};
>>>>>>> mcu_ctrl
