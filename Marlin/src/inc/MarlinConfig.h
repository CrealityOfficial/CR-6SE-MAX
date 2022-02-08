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

//
// Prefix header for all Marlin sources
//

#include "MarlinConfigPre.h"

<<<<<<< HEAD
#include "../HAL/HAL.h"

#include "../pins/pins.h"
#include HAL_PATH(../HAL, spi_pins.h)

#include "Conditionals_post.h"
#include HAL_PATH(../HAL, inc/Conditionals_post.h)

#include "SanityCheck.h"
#include HAL_PATH(../HAL, inc/SanityCheck.h)

// Include all core headers
#include "../core/types.h"
#include "../core/language.h"
#include "../core/utility.h"
#include "../core/serial.h"
=======
#ifndef __MARLIN_DEPS__
  #include "../HAL/HAL.h"
#endif

#include "../pins/pins.h"

#ifndef __MARLIN_DEPS__
  #include HAL_PATH(../HAL, timers.h)
  #include HAL_PATH(../HAL, spi_pins.h)
#endif

#include "Conditionals_post.h"

#ifndef __MARLIN_DEPS__

  #include HAL_PATH(../HAL, inc/Conditionals_post.h)

  #include "../core/types.h"  // Ahead of sanity-checks

  #include "SanityCheck.h"
  #include HAL_PATH(../HAL, inc/SanityCheck.h)

  // Include all core headers
  #include "../core/language.h"
  #include "../core/utility.h"
  #include "../core/serial.h"

#endif

#include "../core/multi_language.h"
>>>>>>> mcu_ctrl
