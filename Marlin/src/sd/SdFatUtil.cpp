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
<<<<<<< HEAD
=======
 * sd/SdFatUtil.cpp
 *
>>>>>>> mcu_ctrl
 * Arduino SdFat Library
 * Copyright (c) 2008 by William Greiman
 *
 * This file is part of the Arduino Sd2Card Library
 */

#include "../inc/MarlinConfig.h"

#if ENABLED(SDSUPPORT)

#include "SdFatUtil.h"
#include <string.h>

/**
 * Amount of free RAM
 * \return The number of free bytes.
 */
#ifdef __arm__

  extern "C" char* sbrk(int incr);
  int SdFatUtil::FreeRam() {
    char top;
    return &top - reinterpret_cast<char*>(sbrk(0));
  }

#else

  extern char* __brkval;
  extern char __bss_end;
  int SdFatUtil::FreeRam() {
    char top;
    return __brkval ? &top - __brkval : &top - &__bss_end;
  }

#endif

#endif // SDSUPPORT
