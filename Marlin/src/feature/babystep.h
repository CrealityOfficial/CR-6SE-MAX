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

#include "../inc/MarlinConfigPre.h"

<<<<<<< HEAD
#if IS_CORE || EITHER(BABYSTEP_XY, I2C_POSITION_ENCODERS)
  #define BS_TODO_AXIS(A) A
#else
  #define BS_TODO_AXIS(A) 0
=======
#if ENABLED(INTEGRATED_BABYSTEPPING)
  #define BABYSTEPS_PER_SEC 1000UL
  #define BABYSTEP_TICKS ((STEPPER_TIMER_RATE) / (BABYSTEPS_PER_SEC))
#else
  #define BABYSTEPS_PER_SEC 976UL
  #define BABYSTEP_TICKS ((TEMP_TIMER_RATE) / (BABYSTEPS_PER_SEC))
#endif

#if IS_CORE || EITHER(BABYSTEP_XY, I2C_POSITION_ENCODERS)
  #define BS_AXIS_IND(A) A
  #define BS_AXIS(I) AxisEnum(I)
#else
  #define BS_AXIS_IND(A) 0
  #define BS_AXIS(I) Z_AXIS
>>>>>>> mcu_ctrl
#endif

#if ENABLED(BABYSTEP_DISPLAY_TOTAL)
  #if ENABLED(BABYSTEP_XY)
<<<<<<< HEAD
    #define BS_TOTAL_AXIS(A) A
  #else
    #define BS_TOTAL_AXIS(A) 0
=======
    #define BS_TOTAL_IND(A) A
  #else
    #define BS_TOTAL_IND(A) 0
>>>>>>> mcu_ctrl
  #endif
#endif

class Babystep {
public:
<<<<<<< HEAD
  static volatile int16_t steps[BS_TODO_AXIS(Z_AXIS) + 1];
  static int16_t accum;                                     // Total babysteps in current edit

  #if ENABLED(BABYSTEP_DISPLAY_TOTAL)
    static int16_t axis_total[BS_TOTAL_AXIS(Z_AXIS) + 1];   // Total babysteps since G28
    static inline void reset_total(const AxisEnum axis) {
      if (true
        #if ENABLED(BABYSTEP_XY)
          && axis == Z_AXIS
        #endif
      ) axis_total[BS_TOTAL_AXIS(axis)] = 0;
=======
  static volatile int16_t steps[BS_AXIS_IND(Z_AXIS) + 1];
  static int16_t accum;                                     // Total babysteps in current edit

  #if ENABLED(BABYSTEP_DISPLAY_TOTAL)
    static int16_t axis_total[BS_TOTAL_IND(Z_AXIS) + 1];   // Total babysteps since G28
    static inline void reset_total(const AxisEnum axis) {
      if (TERN1(BABYSTEP_XY, axis == Z_AXIS))
        axis_total[BS_TOTAL_IND(axis)] = 0;
>>>>>>> mcu_ctrl
    }
  #endif

  static void add_steps(const AxisEnum axis, const int16_t distance);
<<<<<<< HEAD
  static void add_mm(const AxisEnum axis, const float &mm);
  static void task();
=======
  static void add_mm(const AxisEnum axis, const_float_t mm);

  static inline bool has_steps() {
    return steps[BS_AXIS_IND(X_AXIS)] || steps[BS_AXIS_IND(Y_AXIS)] || steps[BS_AXIS_IND(Z_AXIS)];
  }

  //
  // Called by the Temperature or Stepper ISR to
  // apply accumulated babysteps to the axes.
  //
  static inline void task() {
    LOOP_LE_N(i, BS_AXIS_IND(Z_AXIS)) step_axis(BS_AXIS(i));
  }

>>>>>>> mcu_ctrl
private:
  static void step_axis(const AxisEnum axis);
};

extern Babystep babystep;