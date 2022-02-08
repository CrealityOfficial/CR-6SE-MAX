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
 * Gen3 Monolithic Electronics pin assignments
 */

/**
 * Rev B    26 DEC 2016
 *
 * added pointer to a current Arduino IDE extension
<<<<<<< HEAD
 *
=======
>>>>>>> mcu_ctrl
 */

/**
 * A useable Arduino IDE extension (board manager) can be found at
 * https://github.com/Lauszus/Sanguino
 *
 * This extension has been tested on Arduino 1.6.12 & 1.8.0
 *
 * Here's the JSON path:
 * https://raw.githubusercontent.com/Lauszus/Sanguino/master/package_lauszus_sanguino_index.json
 *
 * When installing select 1.0.2
 *
 * Installation instructions can be found at https://learn.sparkfun.com/pages/CustomBoardsArduino
 * Just use the above JSON URL instead of Sparkfun's JSON.
 *
 * Once installed select the Sanguino board and then select the CPU.
<<<<<<< HEAD
 *
 */

#ifndef __AVR_ATmega644P__
  #error "Oops! Select 'Sanguino' in 'Tools > Board.'"
#endif

#define BOARD_INFO_NAME "Gen3 Monolithic"
#define DEBUG_PIN 0
=======
 */

#define REQUIRE_MEGA644P
#include "env_validate.h"

#define BOARD_INFO_NAME "Gen3 Monolithic"
#define DEBUG_PIN                              0
>>>>>>> mcu_ctrl

//
// Limit Switches
//
<<<<<<< HEAD
#define X_STOP_PIN         20
#define Y_STOP_PIN         25
#define Z_STOP_PIN         30
=======
#define X_STOP_PIN                            20
#define Y_STOP_PIN                            25
#define Z_STOP_PIN                            30
>>>>>>> mcu_ctrl

//
// Steppers
//
<<<<<<< HEAD
#define X_STEP_PIN         15
#define X_DIR_PIN          18
#define X_ENABLE_PIN       24   // actually uses Y_enable_pin

#define Y_STEP_PIN         23
#define Y_DIR_PIN          22
#define Y_ENABLE_PIN       24   // shared with X_enable_pin

#define Z_STEP_PIN         27
#define Z_DIR_PIN          28
#define Z_ENABLE_PIN       29

#define E0_STEP_PIN        12
#define E0_DIR_PIN         17
#define E0_ENABLE_PIN       3
=======
#define X_STEP_PIN                            15
#define X_DIR_PIN                             18
#define X_ENABLE_PIN                          24  // actually uses Y_enable_pin

#define Y_STEP_PIN                            23
#define Y_DIR_PIN                             22
#define Y_ENABLE_PIN                          24  // shared with X_enable_pin

#define Z_STEP_PIN                            27
#define Z_DIR_PIN                             28
#define Z_ENABLE_PIN                          29

#define E0_STEP_PIN                           12
#define E0_DIR_PIN                            17
#define E0_ENABLE_PIN                          3
>>>>>>> mcu_ctrl

//
// Temperature Sensors
//
<<<<<<< HEAD
#define TEMP_0_PIN          0   // Analog Input
=======
#define TEMP_0_PIN                             0  // Analog Input
>>>>>>> mcu_ctrl

//
// Heaters
//
<<<<<<< HEAD
#define HEATER_0_PIN       16
=======
#define HEATER_0_PIN                          16
>>>>>>> mcu_ctrl

//
// Misc. Functions
//
<<<<<<< HEAD
#define PS_ON_PIN          14   // Alex, does this work on the card?
=======
#define PS_ON_PIN                             14  // Alex, does this work on the card?
>>>>>>> mcu_ctrl

// Alex extras from Gen3+
