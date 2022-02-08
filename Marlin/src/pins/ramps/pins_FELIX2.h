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
 * FELIXprinters v2.0/3.0 (RAMPS v1.4) pin assignments
 */

#if HOTENDS > 2 || E_STEPPERS > 2
  #error "Felix 2.0+ supports up to 2 hotends / E-steppers. Comment out this line to continue."
#endif

#define BOARD_INFO_NAME "Felix 2.0+"

//
// Heaters / Fans
//
// Power outputs EFBF or EFBE
<<<<<<< HEAD
#define MOSFET_D_PIN        7
=======
#define MOSFET_D_PIN                          7
>>>>>>> mcu_ctrl

#include "pins_RAMPS.h"

//
// Misc. Functions
//
<<<<<<< HEAD
#define SDPOWER_PIN         1

#define PS_ON_PIN          12
=======
#define SDPOWER_PIN                           1

#define PS_ON_PIN                            12
>>>>>>> mcu_ctrl

//
// LCD / Controller
//
<<<<<<< HEAD
#if BOTH(ULTRA_LCD, NEWPANEL)

  #define SD_DETECT_PIN     6

#endif // NEWPANEL && ULTRA_LCD
=======
#if IS_ULTRA_LCD && IS_NEWPANEL

  #define SD_DETECT_PIN                       6

#endif
>>>>>>> mcu_ctrl

//
// M3/M4/M5 - Spindle/Laser Control
//
<<<<<<< HEAD
#undef SPINDLE_LASER_PWM_PIN     // Definitions in pins_RAMPS.h are not valid with this board
=======
#undef SPINDLE_LASER_PWM_PIN                      // Definitions in pins_RAMPS.h are not valid with this board
>>>>>>> mcu_ctrl
#undef SPINDLE_LASER_ENA_PIN
#undef SPINDLE_DIR_PIN
