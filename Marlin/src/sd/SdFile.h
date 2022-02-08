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
<<<<<<< HEAD
 * \file
 * \brief SdFile class
 */

/**
=======
 * sd/SdFile.h
 *
>>>>>>> mcu_ctrl
 * Arduino SdFat Library
 * Copyright (c) 2009 by William Greiman
 *
 * This file is part of the Arduino Sd2Card Library
 */

#include "SdBaseFile.h"

#include <stdint.h>
#include <string.h>

/**
 * \class SdFile
 * \brief SdBaseFile with Print.
 */
<<<<<<< HEAD
class SdFile : public SdBaseFile/*, public Print*/ {
 public:
  SdFile() {}
  SdFile(const char* name, uint8_t oflag);
  #if ARDUINO >= 100
    size_t write(uint8_t b);
  #else
   void write(uint8_t b);
  #endif

  int16_t write(const void* buf, uint16_t nbyte);
  void write(const char* str);
=======
class SdFile : public SdBaseFile {
 public:
  SdFile() {}
  SdFile(const char *name, uint8_t oflag);
  #if ARDUINO >= 100
    size_t write(uint8_t b);
  #else
    void write(uint8_t b);
  #endif

  int16_t write(const void *buf, uint16_t nbyte);
  void write(const char *str);
>>>>>>> mcu_ctrl
  void write_P(PGM_P str);
  void writeln_P(PGM_P str);
};
