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

#include "platforms.h"

<<<<<<< HEAD
=======
#ifndef GCC_VERSION
  #define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#endif

>>>>>>> mcu_ctrl
#include HAL_PATH(.,HAL.h)

#define HAL_ADC_RANGE _BV(HAL_ADC_RESOLUTION)

<<<<<<< HEAD
inline void watchdog_refresh() {
  #if ENABLED(USE_WATCHDOG)
    HAL_watchdog_refresh();
  #endif
=======
#ifndef I2C_ADDRESS
  #define I2C_ADDRESS(A) uint8_t(A)
#endif

// Needed for AVR sprintf_P PROGMEM extension
#ifndef S_FMT
  #define S_FMT "%s"
#endif

// String helper
#ifndef PGMSTR
  #define PGMSTR(NAM,STR) const char NAM[] = STR
#endif

inline void watchdog_refresh() {
  TERN_(USE_WATCHDOG, HAL_watchdog_refresh());
>>>>>>> mcu_ctrl
}
