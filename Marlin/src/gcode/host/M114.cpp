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

#include "../../inc/MarlinConfig.h"

#include "../gcode.h"
#include "../../module/motion.h"
#include "../../module/stepper.h"

#if ENABLED(M114_DETAIL)

<<<<<<< HEAD
  #if HAS_DRIVER(L6470)
    //C:\Users\bobku\Documents\GitHub\Marlin-Bob-2\Marlin\src\gcode\host\M114.cpp
    //C:\Users\bobku\Documents\GitHub\Marlin-Bob-2\Marlin\src\module\bob_L6470.cpp
    #include "../../libs/L6470/L6470_Marlin.h"
=======
  #if HAS_L64XX
    #include "../../libs/L64XX/L64XX_Marlin.h"
>>>>>>> mcu_ctrl
    #define DEBUG_OUT ENABLED(L6470_CHITCHAT)
    #include "../../core/debug_out.h"
  #endif

<<<<<<< HEAD
  void report_xyze(const xyze_pos_t &pos, const uint8_t n=4, const uint8_t precision=3) {
    char str[12];
    for (uint8_t a = 0; a < n; a++) {
      SERIAL_CHAR(' ');
      SERIAL_CHAR(axis_codes[a]);
      SERIAL_CHAR(':');
=======
  void report_all_axis_pos(const xyze_pos_t &pos, const uint8_t n=XYZE, const uint8_t precision=3) {
    char str[12];
    LOOP_L_N(a, n) {
      SERIAL_CHAR(' ', axis_codes[a], ':');
      if (pos[a] >= 0) SERIAL_CHAR(' ');
>>>>>>> mcu_ctrl
      SERIAL_ECHO(dtostrf(pos[a], 1, precision, str));
    }
    SERIAL_EOL();
  }
<<<<<<< HEAD

  void report_xyz(const xyz_pos_t &pos, const uint8_t precision=3) {
    char str[12];
    for (uint8_t a = X_AXIS; a <= Z_AXIS; a++) {
      SERIAL_CHAR(' ');
      SERIAL_CHAR(axis_codes[a]);
      SERIAL_CHAR(':');
=======
  inline void report_linear_axis_pos(const xyze_pos_t &pos) { report_all_axis_pos(pos, XYZ); }

  void report_linear_axis_pos(const xyz_pos_t &pos, const uint8_t precision=3) {
    char str[12];
    LOOP_LINEAR_AXES(a) {
      SERIAL_CHAR(' ', AXIS_CHAR(a), ':');
>>>>>>> mcu_ctrl
      SERIAL_ECHO(dtostrf(pos[a], 1, precision, str));
    }
    SERIAL_EOL();
  }
<<<<<<< HEAD
  inline void report_xyz(const xyze_pos_t &pos) { report_xyze(pos, 3); }

  void report_current_position_detail() {

    SERIAL_ECHOPGM("\nLogical:");
    report_xyz(current_position.asLogical());

    SERIAL_ECHOPGM("Raw:    ");
    report_xyz(current_position);
=======

  void report_current_position_detail() {
    // Position as sent by G-code
    SERIAL_ECHOPGM("\nLogical:");
    report_linear_axis_pos(current_position.asLogical());

    // Cartesian position in native machine space
    SERIAL_ECHOPGM("Raw:    ");
    report_linear_axis_pos(current_position);
>>>>>>> mcu_ctrl

    xyze_pos_t leveled = current_position;

    #if HAS_LEVELING
<<<<<<< HEAD
      SERIAL_ECHOPGM("Leveled:");
      planner.apply_leveling(leveled);
      report_xyz(leveled);

      SERIAL_ECHOPGM("UnLevel:");
      xyze_pos_t unleveled = leveled;
      planner.unapply_leveling(unleveled);
      report_xyz(unleveled);
    #endif

    #if IS_KINEMATIC
      #if IS_SCARA
        SERIAL_ECHOPGM("ScaraK: ");
      #else
        SERIAL_ECHOPGM("DeltaK: ");
      #endif
      inverse_kinematics(leveled);  // writes delta[]
      report_xyz(delta);
=======
      // Current position with leveling applied
      SERIAL_ECHOPGM("Leveled:");
      planner.apply_leveling(leveled);
      report_linear_axis_pos(leveled);

      // Test planner un-leveling. This should match the Raw result.
      SERIAL_ECHOPGM("UnLevel:");
      xyze_pos_t unleveled = leveled;
      planner.unapply_leveling(unleveled);
      report_linear_axis_pos(unleveled);
    #endif

    #if IS_KINEMATIC
      // Kinematics applied to the leveled position
      SERIAL_ECHOPGM(TERN(IS_SCARA, "ScaraK: ", "DeltaK: "));
      inverse_kinematics(leveled);  // writes delta[]
      report_linear_axis_pos(delta);
>>>>>>> mcu_ctrl
    #endif

    planner.synchronize();

<<<<<<< HEAD
    #if HAS_DRIVER(L6470)
=======
    #if HAS_L64XX
>>>>>>> mcu_ctrl
      char temp_buf[80];
      int32_t temp;
      //#define ABS_POS_SIGN_MASK 0b1111 1111 1110 0000 0000 0000 0000 0000
      #define ABS_POS_SIGN_MASK 0b11111111111000000000000000000000
      #define REPORT_ABSOLUTE_POS(Q) do{                            \
<<<<<<< HEAD
          L6470.say_axis(Q, false);                                 \
=======
          L64xxManager.say_axis(Q, false);                          \
>>>>>>> mcu_ctrl
          temp = L6470_GETPARAM(L6470_ABS_POS,Q);                   \
          if (temp & ABS_POS_SIGN_MASK) temp |= ABS_POS_SIGN_MASK;  \
          sprintf_P(temp_buf, PSTR(":%8ld   "), temp);              \
          DEBUG_ECHO(temp_buf);                                     \
        }while(0)

      DEBUG_ECHOPGM("\nL6470:");
<<<<<<< HEAD
      #if AXIS_DRIVER_TYPE_X(L6470)
        REPORT_ABSOLUTE_POS(X);
      #endif
      #if AXIS_DRIVER_TYPE_X2(L6470)
        REPORT_ABSOLUTE_POS(X2);
      #endif
      #if AXIS_DRIVER_TYPE_Y(L6470)
        REPORT_ABSOLUTE_POS(Y);
      #endif
      #if AXIS_DRIVER_TYPE_Y2(L6470)
        REPORT_ABSOLUTE_POS(Y2);
      #endif
      #if AXIS_DRIVER_TYPE_Z(L6470)
        REPORT_ABSOLUTE_POS(Z);
      #endif
      #if AXIS_DRIVER_TYPE_Z2(L6470)
        REPORT_ABSOLUTE_POS(Z2);
      #endif
      #if AXIS_DRIVER_TYPE_Z3(L6470)
        REPORT_ABSOLUTE_POS(Z3);
      #endif
      #if AXIS_DRIVER_TYPE_E0(L6470)
        REPORT_ABSOLUTE_POS(E0);
      #endif
      #if AXIS_DRIVER_TYPE_E1(L6470)
        REPORT_ABSOLUTE_POS(E1);
      #endif
      #if AXIS_DRIVER_TYPE_E2(L6470)
        REPORT_ABSOLUTE_POS(E2);
      #endif
      #if AXIS_DRIVER_TYPE_E3(L6470)
        REPORT_ABSOLUTE_POS(E3);
      #endif
      #if AXIS_DRIVER_TYPE_E4(L6470)
        REPORT_ABSOLUTE_POS(E4);
      #endif
      #if AXIS_DRIVER_TYPE_E5(L6470)
        REPORT_ABSOLUTE_POS(E5);
      #endif
      SERIAL_EOL();
    #endif // HAS_DRIVER(L6470)

    SERIAL_ECHOPGM("Stepper:");
    LOOP_XYZE(i) {
      SERIAL_CHAR(' ');
      SERIAL_CHAR(axis_codes[i]);
      SERIAL_CHAR(':');
=======
      #if AXIS_IS_L64XX(X)
        REPORT_ABSOLUTE_POS(X);
      #endif
      #if AXIS_IS_L64XX(X2)
        REPORT_ABSOLUTE_POS(X2);
      #endif
      #if AXIS_IS_L64XX(Y)
        REPORT_ABSOLUTE_POS(Y);
      #endif
      #if AXIS_IS_L64XX(Y2)
        REPORT_ABSOLUTE_POS(Y2);
      #endif
      #if AXIS_IS_L64XX(Z)
        REPORT_ABSOLUTE_POS(Z);
      #endif
      #if AXIS_IS_L64XX(Z2)
        REPORT_ABSOLUTE_POS(Z2);
      #endif
      #if AXIS_IS_L64XX(Z3)
        REPORT_ABSOLUTE_POS(Z3);
      #endif
      #if AXIS_IS_L64XX(Z4)
        REPORT_ABSOLUTE_POS(Z4);
      #endif
      #if AXIS_IS_L64XX(E0)
        REPORT_ABSOLUTE_POS(E0);
      #endif
      #if AXIS_IS_L64XX(E1)
        REPORT_ABSOLUTE_POS(E1);
      #endif
      #if AXIS_IS_L64XX(E2)
        REPORT_ABSOLUTE_POS(E2);
      #endif
      #if AXIS_IS_L64XX(E3)
        REPORT_ABSOLUTE_POS(E3);
      #endif
      #if AXIS_IS_L64XX(E4)
        REPORT_ABSOLUTE_POS(E4);
      #endif
      #if AXIS_IS_L64XX(E5)
        REPORT_ABSOLUTE_POS(E5);
      #endif
      #if AXIS_IS_L64XX(E6)
        REPORT_ABSOLUTE_POS(E6);
      #endif
      #if AXIS_IS_L64XX(E7)
        REPORT_ABSOLUTE_POS(E7);
      #endif
      SERIAL_EOL();
    #endif // HAS_L64XX

    SERIAL_ECHOPGM("Stepper:");
    LOOP_LOGICAL_AXES(i) {
      SERIAL_CHAR(' ', axis_codes[i], ':');
>>>>>>> mcu_ctrl
      SERIAL_ECHO(stepper.position((AxisEnum)i));
    }
    SERIAL_EOL();

    #if IS_SCARA
      const xy_float_t deg = {
        planner.get_axis_position_degrees(A_AXIS),
        planner.get_axis_position_degrees(B_AXIS)
      };
      SERIAL_ECHOPGM("Degrees:");
<<<<<<< HEAD
      report_xyze(deg, 2);
=======
      report_all_axis_pos(deg, 2);
>>>>>>> mcu_ctrl
    #endif

    SERIAL_ECHOPGM("FromStp:");
    get_cartesian_from_steppers();  // writes 'cartes' (with forward kinematics)
    xyze_pos_t from_steppers = { cartes.x, cartes.y, cartes.z, planner.get_axis_position_mm(E_AXIS) };
<<<<<<< HEAD
    report_xyze(from_steppers);

    const xyze_float_t diff = from_steppers - leveled;
    SERIAL_ECHOPGM("Diff: ");
    report_xyze(diff);
=======
    report_all_axis_pos(from_steppers);

    const xyze_float_t diff = from_steppers - leveled;
    SERIAL_ECHOPGM("Diff:   ");
    report_all_axis_pos(diff);

    TERN_(FULL_REPORT_TO_HOST_FEATURE, report_current_grblstate_moving());
>>>>>>> mcu_ctrl
  }

#endif // M114_DETAIL

/**
<<<<<<< HEAD
 * M114: Report current position to host
=======
 * M114: Report the current position to host.
 *       Since steppers are moving, the count positions are
 *       projected by using planner calculations.
 *   D - Report more detail. This syncs the planner. (Requires M114_DETAIL)
 *   E - Report E stepper position (Requires M114_DETAIL)
 *   R - Report the realtime position instead of projected.
>>>>>>> mcu_ctrl
 */
void GcodeSuite::M114() {

  #if ENABLED(M114_DETAIL)
<<<<<<< HEAD
    if (parser.seen('D')) {
      report_current_position_detail();
      return;
    }
    if (parser.seen('E')) {
=======
    if (parser.seen_test('D')) {
      #if DISABLED(M114_LEGACY)
        planner.synchronize();
      #endif
      report_current_position();
      report_current_position_detail();
      return;
    }
    if (parser.seen_test('E')) {
>>>>>>> mcu_ctrl
      SERIAL_ECHOLNPAIR("Count E:", stepper.position(E_AXIS));
      return;
    }
  #endif

<<<<<<< HEAD
  planner.synchronize();
  report_current_position();
=======
  #if ENABLED(M114_REALTIME)
    if (parser.seen_test('R')) { report_real_position(); return; }
  #endif

  TERN_(M114_LEGACY, planner.synchronize());
  report_current_position_projected();

  TERN_(FULL_REPORT_TO_HOST_FEATURE, report_current_grblstate_moving());
>>>>>>> mcu_ctrl
}
