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

#include "../../module/stepper.h"
#include "../../module/endstops.h"
<<<<<<< HEAD
#include "../../module/printcounter.h"
#include "../../sd/cardreader.h"
#include "../../feature/power_loss_recovery.h"

#if HOTENDS > 1
=======

#if HAS_MULTI_HOTEND
>>>>>>> mcu_ctrl
  #include "../../module/tool_change.h"
#endif

#if HAS_LEVELING
  #include "../../feature/bedlevel/bedlevel.h"
#endif

#if ENABLED(SENSORLESS_HOMING)
  #include "../../feature/tmc_util.h"
#endif

#include "../../module/probe.h"

#if ENABLED(BLTOUCH)
  #include "../../feature/bltouch.h"
#endif

<<<<<<< HEAD
#include "../../lcd/ultralcd.h"
#ifdef DWIN_LCDDISPLAY
  #include "../../lcd/dwin/dwin.h"
#elif ENABLED(RTS_AVAILABLE)
  #include "../../lcd/dwin/LCD_RTS.h"
#endif

#if HAS_DRIVER(L6470)                         // set L6470 absolute position registers to counts
  #include "../../libs/L6470/L6470_Marlin.h"
=======
#include "../../lcd/marlinui.h"
#if ENABLED(DWIN_CREALITY_LCD)
  #include "../../lcd/dwin/e3v2/dwin.h"
#endif

#if ENABLED(EXTENSIBLE_UI)
  #include "../../lcd/extui/ui_api.h"
#endif

#if HAS_L64XX                         // set L6470 absolute position registers to counts
  #include "../../libs/L64XX/L64XX_Marlin.h"
#endif

#if ENABLED(LASER_MOVE_G28_OFF)
  #include "../../feature/spindle_laser.h"
#endif

#if ENABLED(DWIN_CREALITY_SERMOON_V2)
  #include "../../lcd/dwin/lcd_dwin_sermoon_v2.h"
>>>>>>> mcu_ctrl
#endif

#define DEBUG_OUT ENABLED(DEBUG_LEVELING_FEATURE)
#include "../../core/debug_out.h"

#if ENABLED(QUICK_HOME)

  static void quick_home_xy() {

    // Pretend the current position is 0,0
    current_position.set(0.0, 0.0);
    sync_plan_position();

<<<<<<< HEAD
    const int x_axis_home_dir =
      #if ENABLED(DUAL_X_CARRIAGE)
        x_home_dir(active_extruder)
      #else
        home_dir(X_AXIS)
      #endif
    ;
=======
    const int x_axis_home_dir = TOOL_X_HOME_DIR(active_extruder);
>>>>>>> mcu_ctrl

    const float mlx = max_length(X_AXIS),
                mly = max_length(Y_AXIS),
                mlratio = mlx > mly ? mly / mlx : mlx / mly,
                fr_mm_s = _MIN(homing_feedrate(X_AXIS), homing_feedrate(Y_AXIS)) * SQRT(sq(mlratio) + 1.0);

    #if ENABLED(SENSORLESS_HOMING)
      sensorless_t stealth_states {
          tmc_enable_stallguard(stepperX)
        , tmc_enable_stallguard(stepperY)
        , false
        , false
          #if AXIS_HAS_STALLGUARD(X2)
            || tmc_enable_stallguard(stepperX2)
          #endif
        , false
          #if AXIS_HAS_STALLGUARD(Y2)
            || tmc_enable_stallguard(stepperY2)
          #endif
      };
    #endif

<<<<<<< HEAD
    do_blocking_move_to_xy(1.5 * mlx * x_axis_home_dir, 1.5 * mly * home_dir(Y_AXIS), fr_mm_s);
=======
    do_blocking_move_to_xy(1.5 * mlx * x_axis_home_dir, 1.5 * mly * Y_HOME_DIR, fr_mm_s);
>>>>>>> mcu_ctrl

    endstops.validate_homing_move();

    current_position.set(0.0, 0.0);

<<<<<<< HEAD
    #if ENABLED(SENSORLESS_HOMING)
=======
    #if ENABLED(SENSORLESS_HOMING) && DISABLED(ENDSTOPS_ALWAYS_ON_DEFAULT)
>>>>>>> mcu_ctrl
      tmc_disable_stallguard(stepperX, stealth_states.x);
      tmc_disable_stallguard(stepperY, stealth_states.y);
      #if AXIS_HAS_STALLGUARD(X2)
        tmc_disable_stallguard(stepperX2, stealth_states.x2);
      #endif
      #if AXIS_HAS_STALLGUARD(Y2)
        tmc_disable_stallguard(stepperY2, stealth_states.y2);
      #endif
    #endif
  }

#endif // QUICK_HOME

#if ENABLED(Z_SAFE_HOMING)

  inline void home_z_safely() {
<<<<<<< HEAD

    // Disallow Z homing if X or Y are unknown
    if (!TEST(axis_known_position, X_AXIS) || !TEST(axis_known_position, Y_AXIS)) {
      LCD_MESSAGEPGM(MSG_ERR_Z_HOMING);
      SERIAL_ECHO_MSG(MSG_ERR_Z_HOMING_SER);
      return;
    }

    if (DEBUGGING(LEVELING)) DEBUG_ECHOLNPGM("home_z_safely >>>");
=======
    DEBUG_SECTION(log_G28, "home_z_safely", DEBUGGING(LEVELING));

    // Disallow Z homing if X or Y homing is needed
    if (homing_needed_error(_BV(X_AXIS) | _BV(Y_AXIS))) return;
>>>>>>> mcu_ctrl

    sync_plan_position();

    /**
     * Move the Z probe (or just the nozzle) to the safe homing point
     * (Z is already at the right height)
     */
<<<<<<< HEAD
    destination.set(safe_homing_xy, current_position.z);

    #if HOMING_Z_WITH_PROBE
      destination -= probe_offset;
    #endif

=======
    constexpr xy_float_t safe_homing_xy = { Z_SAFE_HOMING_X_POINT, Z_SAFE_HOMING_Y_POINT };
    #if HAS_HOME_OFFSET
      xy_float_t okay_homing_xy = safe_homing_xy;
      okay_homing_xy -= home_offset;
    #else
      constexpr xy_float_t okay_homing_xy = safe_homing_xy;
    #endif

    destination.set(okay_homing_xy, current_position.z);

    TERN_(HOMING_Z_WITH_PROBE, destination -= probe.offset_xy);

>>>>>>> mcu_ctrl
    if (position_is_reachable(destination)) {

      if (DEBUGGING(LEVELING)) DEBUG_POS("home_z_safely", destination);

<<<<<<< HEAD
      // This causes the carriage on Dual X to unpark
      #if ENABLED(DUAL_X_CARRIAGE)
        active_extruder_parked = false;
      #endif

      #if ENABLED(SENSORLESS_HOMING)
        safe_delay(500); // Short delay needed to settle
      #endif
=======
      // Free the active extruder for movement
      TERN_(DUAL_X_CARRIAGE, idex_set_parked(false));

      TERN_(SENSORLESS_HOMING, safe_delay(500)); // Short delay needed to settle
>>>>>>> mcu_ctrl

      do_blocking_move_to_xy(destination);
      homeaxis(Z_AXIS);
    }
    else {
      LCD_MESSAGEPGM(MSG_ZPROBE_OUT);
<<<<<<< HEAD
      SERIAL_ECHO_MSG(MSG_ZPROBE_OUT_SER);
    }

    if (DEBUGGING(LEVELING)) DEBUG_ECHOLNPGM("<<< home_z_safely");
=======
      SERIAL_ECHO_MSG(STR_ZPROBE_OUT_SER);
    }
>>>>>>> mcu_ctrl
  }

#endif // Z_SAFE_HOMING

#if ENABLED(IMPROVE_HOMING_RELIABILITY)

  slow_homing_t begin_slow_homing() {
    slow_homing_t slow_homing{0};
    slow_homing.acceleration.set(planner.settings.max_acceleration_mm_per_s2[X_AXIS],
                                 planner.settings.max_acceleration_mm_per_s2[Y_AXIS]);
    planner.settings.max_acceleration_mm_per_s2[X_AXIS] = 100;
    planner.settings.max_acceleration_mm_per_s2[Y_AXIS] = 100;
    #if HAS_CLASSIC_JERK
      slow_homing.jerk_xy = planner.max_jerk;
      planner.max_jerk.set(0, 0);
    #endif
    planner.reset_acceleration_rates();
    return slow_homing;
  }

  void end_slow_homing(const slow_homing_t &slow_homing) {
    planner.settings.max_acceleration_mm_per_s2[X_AXIS] = slow_homing.acceleration.x;
    planner.settings.max_acceleration_mm_per_s2[Y_AXIS] = slow_homing.acceleration.y;
<<<<<<< HEAD
    #if HAS_CLASSIC_JERK
      planner.max_jerk = slow_homing.jerk_xy;
    #endif
=======
    TERN_(HAS_CLASSIC_JERK, planner.max_jerk = slow_homing.jerk_xy);
>>>>>>> mcu_ctrl
    planner.reset_acceleration_rates();
  }

#endif // IMPROVE_HOMING_RELIABILITY

/**
 * G28: Home all axes according to settings
 *
 * Parameters
 *
 *  None  Home to all axes with no parameters.
 *        With QUICK_HOME enabled XY will home together, then Z.
 *
 *  O   Home only if position is unknown
 *
 *  Rn  Raise by n mm/inches before homing
 *
 * Cartesian/SCARA parameters
 *
 *  X   Home to the X endstop
 *  Y   Home to the Y endstop
 *  Z   Home to the Z endstop
<<<<<<< HEAD
 *
 */
void GcodeSuite::G28(const bool always_home_all) {
  if (DEBUGGING(LEVELING)) {
    DEBUG_ECHOLNPGM(">>> G28");
    log_machine_info();
  }

  home_flag = true;

  if(waitway == 4 || waitway == 6 || waitway == 7)
  {
    if(language_change_font != 0)
    {
      // exchange to 60 page
      rtscheck.RTS_SndData(ExchangePageBase + 60, ExchangepageAddr);
      change_page_font = 60;
    }
  }
=======
 */
void GcodeSuite::G28() {
  #if ENABLED(DWIN_CREALITY_SERMOON_V2)
    gLcdSermoonV2UI.SetStaGoingHome(GO_HOME_DOING);
  #endif
  DEBUG_SECTION(log_G28, "G28", DEBUGGING(LEVELING));
  if (DEBUGGING(LEVELING)) log_machine_info();

  TERN_(LASER_MOVE_G28_OFF, cutter.set_inline_enabled(false));  // turn off laser

  TERN_(FULL_REPORT_TO_HOST_FEATURE, set_and_report_grblstate(M_HOMING));
>>>>>>> mcu_ctrl

  #if ENABLED(DUAL_X_CARRIAGE)
    bool IDEX_saved_duplication_state = extruder_duplication_enabled;
    DualXMode IDEX_saved_mode = dual_x_carriage_mode;
  #endif

  #if ENABLED(MARLIN_DEV_MODE)
<<<<<<< HEAD
    if (parser.seen('S')) {
      LOOP_XYZ(a) set_axis_is_at_home((AxisEnum)a);
      sync_plan_position();
      SERIAL_ECHOLNPGM("Simulated Homing");
      report_current_position();
      if (DEBUGGING(LEVELING)) DEBUG_ECHOLNPGM("<<< G28");
=======
    if (parser.seen_test('S')) {
      LOOP_LINEAR_AXES(a) set_axis_is_at_home((AxisEnum)a);
      sync_plan_position();
      SERIAL_ECHOLNPGM("Simulated Homing");
      report_current_position();
>>>>>>> mcu_ctrl
      return;
    }
  #endif

  // Home (O)nly if position is unknown
<<<<<<< HEAD
  if (!homing_needed() && parser.boolval('O')) {
    if (DEBUGGING(LEVELING)) DEBUG_ECHOLNPGM("> homing not needed, skip\n<<< G28");
    return;
  }

  // Wait for planner moves to finish!
  planner.synchronize();

  // Disable the leveling matrix before homing
  #if HAS_LEVELING

    // Cancel the active G29 session
    #if ENABLED(PROBE_MANUALLY)
      g29_in_progress = false;
    #endif

    #if ENABLED(RESTORE_LEVELING_AFTER_G28)
      const bool leveling_was_active = planner.leveling_active;
    #endif
    set_bed_leveling_enabled(false);
  #endif

  #if ENABLED(CNC_WORKSPACE_PLANES)
    workspace_plane = PLANE_XY;
  #endif

  #define HAS_CURRENT_HOME(N) (defined(N##_CURRENT_HOME) && N##_CURRENT_HOME != N##_CURRENT)
  #define HAS_HOMING_CURRENT (HAS_CURRENT_HOME(X) || HAS_CURRENT_HOME(X2) || HAS_CURRENT_HOME(Y) || HAS_CURRENT_HOME(Y2))

  #if HAS_HOMING_CURRENT
    auto debug_current = [](const char * const s, const int16_t a, const int16_t b){
      DEBUG_ECHO(s); DEBUG_ECHOLNPGM(" current: ", a, " -> ", b);
=======
  if (!axes_should_home() && parser.boolval('O')) {
    if (DEBUGGING(LEVELING)) DEBUG_ECHOLNPGM("> homing not needed, skip");
    return;
  }

  TERN_(DWIN_CREALITY_LCD, DWIN_StartHoming());
  TERN_(EXTENSIBLE_UI, ExtUI::onHomingStart());

  planner.synchronize();          // Wait for planner moves to finish!

  SET_SOFT_ENDSTOP_LOOSE(false);  // Reset a leftover 'loose' motion state

  // Disable the leveling matrix before homing
  #if HAS_LEVELING
    const bool leveling_restore_state = parser.boolval('L', TERN(RESTORE_LEVELING_AFTER_G28, planner.leveling_active, ENABLED(ENABLE_LEVELING_AFTER_G28)));
    IF_ENABLED(PROBE_MANUALLY, g29_in_progress = false); // Cancel the active G29 session
    set_bed_leveling_enabled(false);
  #endif

  // Reset to the XY plane
  TERN_(CNC_WORKSPACE_PLANES, workspace_plane = PLANE_XY);

  // Count this command as movement / activity
  reset_stepper_timeout();

  #define HAS_CURRENT_HOME(N) (defined(N##_CURRENT_HOME) && N##_CURRENT_HOME != N##_CURRENT)
  #if HAS_CURRENT_HOME(X) || HAS_CURRENT_HOME(X2) || HAS_CURRENT_HOME(Y) || HAS_CURRENT_HOME(Y2)
    #define HAS_HOMING_CURRENT 1
  #endif

  #if HAS_HOMING_CURRENT
    auto debug_current = [](PGM_P const s, const int16_t a, const int16_t b){
      DEBUG_ECHOPGM_P(s); DEBUG_ECHOLNPAIR(" current: ", a, " -> ", b);
>>>>>>> mcu_ctrl
    };
    #if HAS_CURRENT_HOME(X)
      const int16_t tmc_save_current_X = stepperX.getMilliamps();
      stepperX.rms_current(X_CURRENT_HOME);
<<<<<<< HEAD
      if (DEBUGGING(LEVELING)) debug_current("X", tmc_save_current_X, X_CURRENT_HOME);
=======
      if (DEBUGGING(LEVELING)) debug_current(PSTR("X"), tmc_save_current_X, X_CURRENT_HOME);
>>>>>>> mcu_ctrl
    #endif
    #if HAS_CURRENT_HOME(X2)
      const int16_t tmc_save_current_X2 = stepperX2.getMilliamps();
      stepperX2.rms_current(X2_CURRENT_HOME);
<<<<<<< HEAD
      if (DEBUGGING(LEVELING)) debug_current("X2", tmc_save_current_X2, X2_CURRENT_HOME);
=======
      if (DEBUGGING(LEVELING)) debug_current(PSTR("X2"), tmc_save_current_X2, X2_CURRENT_HOME);
>>>>>>> mcu_ctrl
    #endif
    #if HAS_CURRENT_HOME(Y)
      const int16_t tmc_save_current_Y = stepperY.getMilliamps();
      stepperY.rms_current(Y_CURRENT_HOME);
<<<<<<< HEAD
      if (DEBUGGING(LEVELING)) debug_current("Y", tmc_save_current_Y, Y_CURRENT_HOME);
=======
      if (DEBUGGING(LEVELING)) debug_current(PSTR("Y"), tmc_save_current_Y, Y_CURRENT_HOME);
>>>>>>> mcu_ctrl
    #endif
    #if HAS_CURRENT_HOME(Y2)
      const int16_t tmc_save_current_Y2 = stepperY2.getMilliamps();
      stepperY2.rms_current(Y2_CURRENT_HOME);
<<<<<<< HEAD
      if (DEBUGGING(LEVELING)) debug_current("Y2", tmc_save_current_Y2, Y2_CURRENT_HOME);
    #endif
  #endif

  #if BOTH(STEALTHCHOP_XY, HOME_USING_SPREADCYCLE)
    if (DEBUGGING(LEVELING)) DEBUG_ECHOLNPGM("Set XY to spreadCycle...");
    process_subcommands_now_P(PSTR("M569S0XY"));
  #endif

  #if ENABLED(IMPROVE_HOMING_RELIABILITY)
    slow_homing_t slow_homing = begin_slow_homing();
  #endif

  // Always home with tool 0 active
  #if HOTENDS > 1
    #if DISABLED(DELTA) || ENABLED(DELTA_HOME_TO_SAFE_ZONE)
      const uint8_t old_tool_index = active_extruder;
    #endif
    tool_change(0, true);
  #endif

  #if HAS_DUPLICATION_MODE
    extruder_duplication_enabled = false;
  #endif
=======
      if (DEBUGGING(LEVELING)) debug_current(PSTR("Y2"), tmc_save_current_Y2, Y2_CURRENT_HOME);
    #endif
  #endif

  TERN_(IMPROVE_HOMING_RELIABILITY, slow_homing_t slow_homing = begin_slow_homing());

  // Always home with tool 0 active
  #if HAS_MULTI_HOTEND
    #if DISABLED(DELTA) || ENABLED(DELTA_HOME_TO_SAFE_ZONE)
      const uint8_t old_tool_index = active_extruder;
    #endif
    // PARKING_EXTRUDER homing requires different handling of movement / solenoid activation, depending on the side of homing
    #if ENABLED(PARKING_EXTRUDER)
      const bool pe_final_change_must_unpark = parking_extruder_unpark_after_homing(old_tool_index, X_HOME_DIR + 1 == old_tool_index * 2);
    #endif
    tool_change(0, true);
  #endif

  TERN_(HAS_DUPLICATION_MODE, set_duplication_enabled(false));
>>>>>>> mcu_ctrl

  remember_feedrate_scaling_off();

  endstops.enable(true); // Enable endstops for next homing move

  #if ENABLED(DELTA)

<<<<<<< HEAD
    home_delta();
    UNUSED(always_home_all);

    #if ENABLED(IMPROVE_HOMING_RELIABILITY)
      end_slow_homing(slow_homing);
    #endif

  #else // NOT DELTA

    const bool homeX = parser.seen('X'), homeY = parser.seen('Y'), homeZ = parser.seen('Z'),
               home_all = always_home_all || (homeX == homeY && homeX == homeZ),
               doX = home_all || homeX, doY = home_all || homeY, doZ = home_all || homeZ;

    destination = current_position;

    #if Z_HOME_DIR > 0  // If homing away from BED do Z first
=======
    constexpr bool doZ = true; // for NANODLP_Z_SYNC if your DLP is on a DELTA

    home_delta();

    TERN_(IMPROVE_HOMING_RELIABILITY, end_slow_homing(slow_homing));

  #elif ENABLED(AXEL_TPARA)

    constexpr bool doZ = true; // for NANODLP_Z_SYNC if your DLP is on a TPARA

    home_TPARA();

  #else

    const bool homeZ = parser.seen_test('Z'),
               needX = homeZ && TERN0(Z_SAFE_HOMING, axes_should_home(_BV(X_AXIS))),
               needY = homeZ && TERN0(Z_SAFE_HOMING, axes_should_home(_BV(Y_AXIS))),
               homeX = needX || parser.seen_test('X'), homeY = needY || parser.seen_test('Y'),
               home_all = homeX == homeY && homeX == homeZ, // All or None
               doX = home_all || homeX, doY = home_all || homeY, doZ = home_all || homeZ;

    #if ENABLED(HOME_Z_FIRST)
>>>>>>> mcu_ctrl

      if (doZ) homeaxis(Z_AXIS);

    #endif

<<<<<<< HEAD
    const float z_homing_height = (
      #if ENABLED(UNKNOWN_Z_NO_RAISE)
        !TEST(axis_known_position, Z_AXIS) ? 0 :
      #endif
        (parser.seenval('R') ? parser.value_linear_units() : Z_HOMING_HEIGHT)
    );

    if(finish_home == false && waitway != 7)
    {
      if (z_homing_height && (doX || doY)) {
        destination.z = z_homing_height + (TEST(axis_known_position, Z_AXIS) ? 0.0f : current_position.z);
        if (destination.z > current_position.z) {
          if (DEBUGGING(LEVELING)) DEBUG_ECHOLNPAIR("Raise Z (before homing) to ", destination.z);
          do_blocking_move_to_z(destination.z);
        }
      }
    }

    if(waitway == 7)
    {
      do_blocking_move_to_z(_MIN(current_position.z + NOZZLE_PARK_Z_FEEDRATE, Z_MAX_POS), feedRate_t(NOZZLE_PARK_Z_FEEDRATE));
=======
    const float z_homing_height = parser.seenval('R') ? parser.value_linear_units() : Z_HOMING_HEIGHT;

    if (z_homing_height && (doX || doY || TERN0(Z_SAFE_HOMING, doZ))) {
      // Raise Z before homing any other axes and z is not already high enough (never lower z)
      if (DEBUGGING(LEVELING)) DEBUG_ECHOLNPAIR("Raise Z (before homing) by ", z_homing_height);
      do_z_clearance(z_homing_height);
      TERN_(BLTOUCH, bltouch.init());
>>>>>>> mcu_ctrl
    }

    #if ENABLED(QUICK_HOME)

      if (doX && doY) quick_home_xy();

    #endif

    // Home Y (before X)
<<<<<<< HEAD
    #if ENABLED(HOME_Y_BEFORE_X)

      if (doY
        #if ENABLED(CODEPENDENT_XY_HOMING)
          || doX
        #endif
      ) homeaxis(Y_AXIS);

    #endif

    // Home X
    if (doX
      #if ENABLED(CODEPENDENT_XY_HOMING) && DISABLED(HOME_Y_BEFORE_X)
        || doY
      #endif
    ) {
=======
    if (ENABLED(HOME_Y_BEFORE_X) && (doY || TERN0(CODEPENDENT_XY_HOMING, doX)))
      homeaxis(Y_AXIS);

    // Home X
    if (doX || (doY && ENABLED(CODEPENDENT_XY_HOMING) && DISABLED(HOME_Y_BEFORE_X))) {
>>>>>>> mcu_ctrl

      #if ENABLED(DUAL_X_CARRIAGE)

        // Always home the 2nd (right) extruder first
        active_extruder = 1;
        homeaxis(X_AXIS);

        // Remember this extruder's position for later tool change
<<<<<<< HEAD
        inactive_extruder_x_pos = current_position.x;
=======
        inactive_extruder_x = current_position.x;
>>>>>>> mcu_ctrl

        // Home the 1st (left) extruder
        active_extruder = 0;
        homeaxis(X_AXIS);

<<<<<<< HEAD
        // Consider the active extruder to be parked
        raised_parked_position = current_position;
        delayed_move_time = 0;
        active_extruder_parked = true;
=======
        // Consider the active extruder to be in its "parked" position
        idex_set_parked();
>>>>>>> mcu_ctrl

      #else

        homeaxis(X_AXIS);

      #endif
    }

    // Home Y (after X)
<<<<<<< HEAD
    #if DISABLED(HOME_Y_BEFORE_X)
      if (doY) homeaxis(Y_AXIS);
    #endif

    #if ENABLED(IMPROVE_HOMING_RELIABILITY)
      end_slow_homing(slow_homing);
    #endif

    // Home Z last if homing towards the bed
    #if Z_HOME_DIR < 0
      if (doZ) {
        #if ENABLED(BLTOUCH)
          bltouch.init();
        #endif
        #if ENABLED(Z_SAFE_HOMING)
          home_z_safely();
        #else
          homeaxis(Z_AXIS);
        #endif

        #if HOMING_Z_WITH_PROBE && defined(Z_AFTER_PROBING)
          move_z_after_probing();
        #endif

      } // doZ
    #endif // Z_HOME_DIR < 0

    sync_plan_position();

  #endif // !DELTA (G28)
=======
    if (DISABLED(HOME_Y_BEFORE_X) && doY)
      homeaxis(Y_AXIS);

    TERN_(IMPROVE_HOMING_RELIABILITY, end_slow_homing(slow_homing));

    // Home Z last if homing towards the bed
    #if DISABLED(HOME_Z_FIRST)
      if (doZ) {
        #if EITHER(Z_MULTI_ENDSTOPS, Z_STEPPER_AUTO_ALIGN)
          stepper.set_all_z_lock(false);
          stepper.set_separate_multi_axis(false);
        #endif

        TERN(Z_SAFE_HOMING, home_z_safely(), homeaxis(Z_AXIS));
        probe.move_z_after_homing();
      }
    #endif

    sync_plan_position();

  #endif
>>>>>>> mcu_ctrl

  /**
   * Preserve DXC mode across a G28 for IDEX printers in DXC_DUPLICATION_MODE.
   * This is important because it lets a user use the LCD Panel to set an IDEX Duplication mode, and
   * then print a standard GCode file that contains a single print that does a G28 and has no other
   * IDEX specific commands in it.
   */
  #if ENABLED(DUAL_X_CARRIAGE)

<<<<<<< HEAD
    if (dxc_is_duplicating()) {

      #if ENABLED(IMPROVE_HOMING_RELIABILITY)
        slow_homing = begin_slow_homing();
      #endif
=======
    if (idex_is_duplicating()) {

      TERN_(IMPROVE_HOMING_RELIABILITY, slow_homing = begin_slow_homing());
>>>>>>> mcu_ctrl

      // Always home the 2nd (right) extruder first
      active_extruder = 1;
      homeaxis(X_AXIS);

      // Remember this extruder's position for later tool change
<<<<<<< HEAD
      inactive_extruder_x_pos = current_position.x;
=======
      inactive_extruder_x = current_position.x;
>>>>>>> mcu_ctrl

      // Home the 1st (left) extruder
      active_extruder = 0;
      homeaxis(X_AXIS);

      // Consider the active extruder to be parked
<<<<<<< HEAD
      raised_parked_position = current_position;
      delayed_move_time = 0;
      active_extruder_parked = true;
      extruder_duplication_enabled = IDEX_saved_duplication_state;
      dual_x_carriage_mode         = IDEX_saved_mode;
      stepper.set_directions();

      #if ENABLED(IMPROVE_HOMING_RELIABILITY)
        end_slow_homing(slow_homing);
      #endif
=======
      idex_set_parked();

      dual_x_carriage_mode = IDEX_saved_mode;
      set_duplication_enabled(IDEX_saved_duplication_state);

      TERN_(IMPROVE_HOMING_RELIABILITY, end_slow_homing(slow_homing));
>>>>>>> mcu_ctrl
    }

  #endif // DUAL_X_CARRIAGE

  endstops.not_homing();

  // Clear endstop state for polled stallGuard endstops
<<<<<<< HEAD
  #if ENABLED(SPI_ENDSTOPS)
    endstops.clear_endstop_state();
  #endif
=======
  TERN_(SPI_ENDSTOPS, endstops.clear_endstop_state());
>>>>>>> mcu_ctrl

  #if BOTH(DELTA, DELTA_HOME_TO_SAFE_ZONE)
    // move to a height where we can use the full xy-area
    do_blocking_move_to_z(delta_clip_start_height);
  #endif

<<<<<<< HEAD
  #if HAS_LEVELING && ENABLED(RESTORE_LEVELING_AFTER_G28)
    set_bed_leveling_enabled(leveling_was_active);
  #endif
=======
  #if ENABLED(BLTOUCH_AND_Z_LIMIT)
  if (gLcdSermoonV2UI.isBedLeveling == false) 
  #endif  
  TERN_(HAS_LEVELING, set_bed_leveling_enabled(leveling_restore_state));
>>>>>>> mcu_ctrl

  restore_feedrate_and_scaling();

  // Restore the active tool after homing
<<<<<<< HEAD
  #if HOTENDS > 1 && (DISABLED(DELTA) || ENABLED(DELTA_HOME_TO_SAFE_ZONE))
    #if EITHER(PARKING_EXTRUDER, DUAL_X_CARRIAGE)
      #define NO_FETCH false // fetch the previous toolhead
    #else
      #define NO_FETCH true
    #endif
    tool_change(old_tool_index, NO_FETCH);
=======
  #if HAS_MULTI_HOTEND && (DISABLED(DELTA) || ENABLED(DELTA_HOME_TO_SAFE_ZONE))
    tool_change(old_tool_index, TERN(PARKING_EXTRUDER, !pe_final_change_must_unpark, DISABLED(DUAL_X_CARRIAGE)));   // Do move if one of these
>>>>>>> mcu_ctrl
  #endif

  #if HAS_HOMING_CURRENT
    if (DEBUGGING(LEVELING)) DEBUG_ECHOLNPGM("Restore driver current...");
    #if HAS_CURRENT_HOME(X)
      stepperX.rms_current(tmc_save_current_X);
    #endif
    #if HAS_CURRENT_HOME(X2)
      stepperX2.rms_current(tmc_save_current_X2);
    #endif
    #if HAS_CURRENT_HOME(Y)
      stepperY.rms_current(tmc_save_current_Y);
    #endif
    #if HAS_CURRENT_HOME(Y2)
      stepperY2.rms_current(tmc_save_current_Y2);
    #endif
  #endif

<<<<<<< HEAD
  #if BOTH(STEALTHCHOP_XY, HOME_USING_SPREADCYCLE)
    if (DEBUGGING(LEVELING)) DEBUG_ECHOLNPGM("Set XY to StealthChop...");
    process_subcommands_now_P(PSTR("M569S1XY"));
  #endif

  ui.refresh();

  #ifdef RTS_AVAILABLE
    if(change_page_font != 62)
    {
      if(waitway == 6)
      {
        if(language_change_font != 0)
        {
          do_blocking_move_to_z(0);
          rtscheck.RTS_SndData(ExchangePageBase + 25, ExchangepageAddr);
          change_page_font = 25;
        }
        waitway = 0;
      }
      else if(waitway == 4)
      {
        if(language_change_font != 0)
        {
          do_blocking_move_to_z(0);
          rtscheck.RTS_SndData(ExchangePageBase + 15 + AxisUnitMode, ExchangepageAddr);
          change_page_font = 15;
        }
        waitway = 0;
      }
      else if(waitway == 7)
      {
        if(language_change_font != 0)
        {
          // exchange to 1 page
          rtscheck.RTS_SndData(ExchangePageBase + 1, ExchangepageAddr);
          change_page_font = 1;
        }
        rtscheck.RTS_SndData(2, MOTOR_FREE_ICON_VP); 
        rtscheck.RTS_SndData(0, PRINT_PROCESS_TITLE_VP);
        rtscheck.RTS_SndData(0, PRINT_PROCESS_VP);
        delay(2);
        for(int j = 0;j < 10;j ++)
        {
          // clean screen.
          rtscheck.RTS_SndData(0, CONTINUE_PRINT_FILE_TEXT_VP + j);
        }
        waitway = 0;
      }
      rtscheck.RTS_SndData(10*current_position[X_AXIS], AXIS_X_COORD_VP);
      rtscheck.RTS_SndData(10*current_position[Y_AXIS], AXIS_Y_COORD_VP);
      rtscheck.RTS_SndData(10*current_position[Z_AXIS], AXIS_Z_COORD_VP);

      if(finish_home) finish_home = false;

      if(StartPrint_flag) 
      {
        StartPrint_flag = 0;
        recovery.info.current_position.z = 0;
      }
      errorway = errornum = 0;
    }
  #endif

  home_flag = false;
  endstops.enable_z_probe(false);

  report_current_position();

  #if ENABLED(NANODLP_Z_SYNC)
    #if ENABLED(NANODLP_ALL_AXIS)
      #define _HOME_SYNC true       // For any axis, output sync text.
    #else
      #define _HOME_SYNC doZ        // Only for Z-axis
    #endif
    if (_HOME_SYNC)
      SERIAL_ECHOLNPGM(MSG_Z_MOVE_COMP);
  #endif

  if (DEBUGGING(LEVELING)) DEBUG_ECHOLNPGM("<<< G28");

  #if HAS_DRIVER(L6470)
    // Set L6470 absolute position registers to counts
    for (uint8_t j = 1; j <= L6470::chain[0]; j++) {
      const uint8_t cv = L6470::chain[j];
      L6470.set_param(cv, L6470_ABS_POS, stepper.position((AxisEnum)L6470.axis_xref[cv]));
    }
  #endif

=======
  ui.refresh();

  TERN_(DWIN_CREALITY_LCD, DWIN_CompletedHoming());
  TERN_(EXTENSIBLE_UI, ExtUI::onHomingComplete());

  report_current_position();

  if (ENABLED(NANODLP_Z_SYNC) && (doZ || ENABLED(NANODLP_ALL_AXIS)))
    SERIAL_ECHOLNPGM(STR_Z_MOVE_COMP);

  TERN_(FULL_REPORT_TO_HOST_FEATURE, set_and_report_grblstate(M_IDLE));

  #if HAS_L64XX
    // Set L6470 absolute position registers to counts
    // constexpr *might* move this to PROGMEM.
    // If not, this will need a PROGMEM directive and an accessor.
    static constexpr AxisEnum L64XX_axis_xref[MAX_L64XX] = {
      X_AXIS, Y_AXIS, Z_AXIS,
      X_AXIS, Y_AXIS, Z_AXIS, Z_AXIS,
      E_AXIS, E_AXIS, E_AXIS, E_AXIS, E_AXIS, E_AXIS
    };
    for (uint8_t j = 1; j <= L64XX::chain[0]; j++) {
      const uint8_t cv = L64XX::chain[j];
      L64xxManager.set_param((L64XX_axis_t)cv, L6470_ABS_POS, stepper.position(L64XX_axis_xref[cv]));
    }
  #endif

  #if ENABLED(DWIN_CREALITY_SERMOON_V2)
    gLcdSermoonV2UI.SetStaGoingHome(GO_HOME_DONE);
    if(!gLcdSermoonV2UI.GetHaGoHoBeFlag())
      gLcdSermoonV2UI.SetHaGoHoBeFlag(true);
  #endif
>>>>>>> mcu_ctrl
}
