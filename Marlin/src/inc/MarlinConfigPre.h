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

#ifndef __MARLIN_FIRMWARE__
#define __MARLIN_FIRMWARE__
#endif

//
// Prefix header to acquire configurations
//
#include <stdint.h>

<<<<<<< HEAD
#include "../HAL/platforms.h"

#include "../core/boards.h"
#include "../core/macros.h"
#include "../../Configuration.h"

#ifdef CUSTOM_VERSION_FILE
  #if defined(__has_include)
    #if __has_include(XSTR(../../CUSTOM_VERSION_FILE))
      #include XSTR(../../CUSTOM_VERSION_FILE)
    #endif
  #else
    #include XSTR(../../CUSTOM_VERSION_FILE)
=======
#ifndef __MARLIN_DEPS__
  #include "../HAL/platforms.h"
#endif

#include "../core/macros.h"
#include "../core/boards.h"
#include "../../Configuration.h"

#ifdef CUSTOM_VERSION_FILE
  #if __has_include(STRINGIFY(../../CUSTOM_VERSION_FILE))
    #include STRINGIFY(../../CUSTOM_VERSION_FILE)
>>>>>>> mcu_ctrl
  #endif
#endif

#include "Version.h"

#include "Conditionals_LCD.h"
<<<<<<< HEAD
#include HAL_PATH(../HAL, inc/Conditionals_LCD.h)
=======

#ifndef __MARLIN_DEPS__
  #include HAL_PATH(../HAL, inc/Conditionals_LCD.h)
#endif
>>>>>>> mcu_ctrl

#include "../core/drivers.h"
#include "../../Configuration_adv.h"

#include "Conditionals_adv.h"
<<<<<<< HEAD
#include HAL_PATH(../HAL, inc/Conditionals_adv.h)
=======

#ifndef __MARLIN_DEPS__
  #include HAL_PATH(../HAL, inc/Conditionals_adv.h)
#endif
>>>>>>> mcu_ctrl
