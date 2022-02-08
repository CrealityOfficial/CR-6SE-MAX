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
 * Cheaptronic v1.0 pin assignments
 */

<<<<<<< HEAD
#ifndef __AVR_ATmega2560__
  #error "Oops! Select 'Arduino/Genuino Mega or Mega 2560' in 'Tools > Board.'"
#endif
=======
#include "env_validate.h"
>>>>>>> mcu_ctrl

#define BOARD_INFO_NAME "Cheaptronic v1.0"
//
// Limit Switches
//
<<<<<<< HEAD
#define X_STOP_PIN          3
#define Y_STOP_PIN          2
#define Z_STOP_PIN          5
=======
#define X_STOP_PIN                             3
#define Y_STOP_PIN                             2
#define Z_STOP_PIN                             5
>>>>>>> mcu_ctrl

//
// Steppers
//
<<<<<<< HEAD
#define X_STEP_PIN         14
#define X_DIR_PIN          15
#define X_ENABLE_PIN       24

#define Y_STEP_PIN         35
#define Y_DIR_PIN          36
#define Y_ENABLE_PIN       31

#define Z_STEP_PIN         40
#define Z_DIR_PIN          41
#define Z_ENABLE_PIN       37

#define E0_STEP_PIN        26
#define E0_DIR_PIN         28
#define E0_ENABLE_PIN      25

#define E1_STEP_PIN        33
#define E1_DIR_PIN         34
#define E1_ENABLE_PIN      30
=======
#define X_STEP_PIN                            14
#define X_DIR_PIN                             15
#define X_ENABLE_PIN                          24

#define Y_STEP_PIN                            35
#define Y_DIR_PIN                             36
#define Y_ENABLE_PIN                          31

#define Z_STEP_PIN                            40
#define Z_DIR_PIN                             41
#define Z_ENABLE_PIN                          37

#define E0_STEP_PIN                           26
#define E0_DIR_PIN                            28
#define E0_ENABLE_PIN                         25

#define E1_STEP_PIN                           33
#define E1_DIR_PIN                            34
#define E1_ENABLE_PIN                         30
>>>>>>> mcu_ctrl

//
// Temperature sensors
//
<<<<<<< HEAD
#define TEMP_0_PIN         15   // Analog Input
#define TEMP_1_PIN         14   // Analog Input
#define TEMP_BED_PIN       13   // Analog Input
=======
#define TEMP_0_PIN                            15  // Analog Input
#define TEMP_1_PIN                            14  // Analog Input
#define TEMP_BED_PIN                          13  // Analog Input
>>>>>>> mcu_ctrl

//
// Heaters / Fans
//
<<<<<<< HEAD
#define HEATER_0_PIN       19   // EXTRUDER 1
#define HEATER_1_PIN       23   // EXTRUDER 2
#define HEATER_BED_PIN     22
=======
#define HEATER_0_PIN                          19  // EXTRUDER 1
#define HEATER_1_PIN                          23  // EXTRUDER 2
#define HEATER_BED_PIN                        22
>>>>>>> mcu_ctrl

//
// LCD / Controller
//
// Cheaptronic v1.0 doesn't support LCD
