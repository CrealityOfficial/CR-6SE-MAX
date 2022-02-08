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
#include "../inc/MarlinConfig.h"

#if ENABLED(EXTERNAL_CLOSED_LOOP_CONTROLLER)

#if !PIN_EXISTS(CLOSED_LOOP_ENABLE) || !PIN_EXISTS(CLOSED_LOOP_MOVE_COMPLETE)
  #error "CLOSED_LOOP_ENABLE_PIN and CLOSED_LOOP_MOVE_COMPLETE_PIN are required for EXTERNAL_CLOSED_LOOP_CONTROLLER."
#endif

#include "closedloop.h"

<<<<<<< HEAD
void init_closedloop() {
=======
ClosedLoop closedloop;

void ClosedLoop::init() {
>>>>>>> mcu_ctrl
  OUT_WRITE(CLOSED_LOOP_ENABLE_PIN, LOW);
  SET_INPUT_PULLUP(CLOSED_LOOP_MOVE_COMPLETE_PIN);
}

<<<<<<< HEAD
void set_closedloop(const byte val) {
=======
void ClosedLoop::set(const byte val) {
>>>>>>> mcu_ctrl
  OUT_WRITE(CLOSED_LOOP_ENABLE_PIN, val);
}

#endif // EXTERNAL_CLOSED_LOOP_CONTROLLER
