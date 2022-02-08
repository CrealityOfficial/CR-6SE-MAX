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

/**
 * G29.cpp - Auto Bed Leveling
 */

#include "../../../inc/MarlinConfig.h"

#if HAS_ABL_NOT_UBL

#include "../../gcode.h"
#include "../../../feature/bedlevel/bedlevel.h"
#include "../../../module/motion.h"
#include "../../../module/planner.h"
#include "../../../module/stepper.h"
#include "../../../module/probe.h"
<<<<<<< HEAD
#include "../../../module/configuration_store.h"
#include "../../../module/temperature.h"
#include "../../../sd/cardreader.h"
#include "../../queue.h"

#include "../../../lcd/ultralcd.h"
#ifdef DWIN_LCDDISPLAY
  #include "../../../lcd/dwin/dwin.h"
#endif
#ifdef RTS_AVAILABLE
  #include "../../../lcd/dwin/LCD_RTS.h"
=======
#include "../../queue.h"

#if ENABLED(PROBE_TEMP_COMPENSATION)
  #include "../../../feature/probe_temp_comp.h"
  #include "../../../module/temperature.h"
#endif

#if HAS_STATUS_MESSAGE
  #include "../../../lcd/marlinui.h"
>>>>>>> mcu_ctrl
#endif

#if ENABLED(AUTO_BED_LEVELING_LINEAR)
  #include "../../../libs/least_squares_fit.h"
#endif

#if ABL_PLANAR
  #include "../../../libs/vector_3.h"
#endif

#define DEBUG_OUT ENABLED(DEBUG_LEVELING_FEATURE)
#include "../../../core/debug_out.h"

#if ENABLED(EXTENSIBLE_UI)
<<<<<<< HEAD
  #include "../../../lcd/extensible_ui/ui_api.h"
#endif

#if HOTENDS > 1
  #include "../../../module/tool_change.h"
#endif

#if ABL_GRID
  #if ENABLED(PROBE_Y_FIRST)
    #define PR_OUTER_VAR meshCount.x
    #define PR_OUTER_END abl_grid_points.x
    #define PR_INNER_VAR meshCount.y
    #define PR_INNER_END abl_grid_points.y
  #else
    #define PR_OUTER_VAR meshCount.y
    #define PR_OUTER_END abl_grid_points.y
    #define PR_INNER_VAR meshCount.x
    #define PR_INNER_END abl_grid_points.x
  #endif
#endif

#if ENABLED(G29_RETRY_AND_RECOVER)
  #define G29_RETURN(b) return b;
#else
  #define G29_RETURN(b) return;
=======
  #include "../../../lcd/extui/ui_api.h"
#endif

#if ENABLED(DWIN_CREALITY_LCD)
  #include "../../../lcd/dwin/e3v2/dwin.h"
#endif

#if ENABLED(DWIN_CREALITY_SERMOON_V2)
  #include "../../../lcd/dwin/lcd_dwin_sermoon_v2.h"
#endif
#if HAS_MULTI_HOTEND
  #include "../../../module/tool_change.h"
#endif

#if ABL_USES_GRID
  #if ENABLED(PROBE_Y_FIRST)
    #define PR_OUTER_VAR  abl.meshCount.x
    #define PR_OUTER_SIZE abl.grid_points.x
    #define PR_INNER_VAR  abl.meshCount.y
    #define PR_INNER_SIZE abl.grid_points.y
  #else
    #define PR_OUTER_VAR  abl.meshCount.y
    #define PR_OUTER_SIZE abl.grid_points.y
    #define PR_INNER_VAR  abl.meshCount.x
    #define PR_INNER_SIZE abl.grid_points.x
  #endif
#endif

#define G29_RETURN(b) return TERN_(G29_RETRY_AND_RECOVER, b)

// For manual probing values persist over multiple G29
class G29_State {
public:
  int       verbose_level;
  xy_pos_t  probePos;
  float     measured_z;
  bool      dryrun,
            reenable;

  #if EITHER(PROBE_MANUALLY, AUTO_BED_LEVELING_LINEAR)
    int abl_probe_index;
  #endif

  #if ENABLED(AUTO_BED_LEVELING_LINEAR)
    int abl_points;
  #elif ENABLED(AUTO_BED_LEVELING_3POINT)
    static constexpr int abl_points = 3;
  #elif ABL_USES_GRID
    static constexpr int abl_points = GRID_MAX_POINTS;
  #endif

  #if ABL_USES_GRID

    xy_int8_t meshCount;

    xy_pos_t probe_position_lf,
             probe_position_rb;

    xy_float_t gridSpacing; // = { 0.0f, 0.0f }

    #if ENABLED(AUTO_BED_LEVELING_LINEAR)
      bool                topography_map;
      xy_uint8_t          grid_points;
    #else // Bilinear
      static constexpr xy_uint8_t grid_points = { GRID_MAX_POINTS_X, GRID_MAX_POINTS_Y };
    #endif

    #if ENABLED(AUTO_BED_LEVELING_BILINEAR)
      float Z_offset;
    #endif

    #if ENABLED(AUTO_BED_LEVELING_LINEAR)
      int indexIntoAB[GRID_MAX_POINTS_X][GRID_MAX_POINTS_Y];
      float eqnAMatrix[(GRID_MAX_POINTS) * 3], // "A" matrix of the linear system of equations
            eqnBVector[GRID_MAX_POINTS],       // "B" vector of Z points
            mean;
    #endif
  #endif
};

#if ABL_USES_GRID && EITHER(AUTO_BED_LEVELING_3POINT, AUTO_BED_LEVELING_BILINEAR)
  constexpr xy_uint8_t G29_State::grid_points;
  constexpr int G29_State::abl_points;
>>>>>>> mcu_ctrl
#endif

/**
 * G29: Detailed Z probe, probes the bed at 3 or more points.
 *      Will fail if the printer has not been homed with G28.
 *
 * Enhanced G29 Auto Bed Leveling Probe Routine
 *
 *  O  Auto-level only if needed
 *
 *  D  Dry-Run mode. Just evaluate the bed Topology - Don't apply
 *     or alter the bed level data. Useful to check the topology
 *     after a first run of G29.
 *
 *  J  Jettison current bed leveling data
 *
 *  V  Set the verbose level (0-4). Example: "G29 V3"
 *
 * Parameters With LINEAR leveling only:
 *
 *  P  Set the size of the grid that will be probed (P x P points).
 *     Example: "G29 P4"
 *
 *  X  Set the X size of the grid that will be probed (X x Y points).
 *     Example: "G29 X7 Y5"
 *
 *  Y  Set the Y size of the grid that will be probed (X x Y points).
 *
 *  T  Generate a Bed Topology Report. Example: "G29 P5 T" for a detailed report.
 *     This is useful for manual bed leveling and finding flaws in the bed (to
 *     assist with part placement).
 *     Not supported by non-linear delta printer bed leveling.
 *
 * Parameters With LINEAR and BILINEAR leveling only:
 *
 *  S  Set the XY travel speed between probe points (in units/min)
 *
 *  H  Set bounds to a centered square H x H units in size
 *
 *     -or-
 *
 *  F  Set the Front limit of the probing grid
 *  B  Set the Back limit of the probing grid
 *  L  Set the Left limit of the probing grid
 *  R  Set the Right limit of the probing grid
 *
 * Parameters with DEBUG_LEVELING_FEATURE only:
 *
 *  C  Make a totally fake grid with no actual probing.
 *     For use in testing when no probing is possible.
 *
 * Parameters with BILINEAR leveling only:
 *
 *  Z  Supply an additional Z probe offset
 *
 * Extra parameters with PROBE_MANUALLY:
 *
 *  To do manual probing simply repeat G29 until the procedure is complete.
 *  The first G29 accepts parameters. 'G29 Q' for status, 'G29 A' to abort.
 *
 *  Q  Query leveling and G29 state
 *
 *  A  Abort current leveling procedure
 *
 * Extra parameters with BILINEAR only:
 *
 *  W  Write a mesh point. (If G29 is idle.)
 *  I  X index for mesh point
 *  J  Y index for mesh point
 *  X  X for mesh point, overrides I
 *  Y  Y for mesh point, overrides J
 *  Z  Z for mesh point. Otherwise, raw current Z.
 *
 * Without PROBE_MANUALLY:
 *
 *  E  By default G29 will engage the Z probe, test the bed, then disengage.
 *     Include "E" to engage/disengage the Z probe for each sample.
 *     There's no extra effect if you have a fixed Z probe.
<<<<<<< HEAD
 *
 */
G29_TYPE GcodeSuite::G29() {

  G29_flag = true;

  #if EITHER(DEBUG_LEVELING_FEATURE, PROBE_MANUALLY)
    const bool seenQ = parser.seen('Q');
  #else
    constexpr bool seenQ = false;
  #endif
=======
 */
G29_TYPE GcodeSuite::G29() {
  TERN_(PROBE_MANUALLY, static) G29_State abl;

  TERN_(FULL_REPORT_TO_HOST_FEATURE, set_and_report_grblstate(M_PROBE));

  reset_stepper_timeout();

  for (int x = 0; x < GRID_MAX_POINTS_X; x++)
  {
    for (int y = 0; y < GRID_MAX_POINTS_Y; y++)
    {
      z_values[x][y] = 0;
    }
  }

  const bool seenQ = EITHER(DEBUG_LEVELING_FEATURE, PROBE_MANUALLY) && parser.seen_test('Q');
>>>>>>> mcu_ctrl

  // G29 Q is also available if debugging
  #if ENABLED(DEBUG_LEVELING_FEATURE)
    const uint8_t old_debug_flags = marlin_debug_flags;
    if (seenQ) marlin_debug_flags |= MARLIN_DEBUG_LEVELING;
<<<<<<< HEAD
    if (DEBUGGING(LEVELING)) {
      DEBUG_POS(">>> G29", current_position);
      log_machine_info();
    }
    marlin_debug_flags = old_debug_flags;
    #if DISABLED(PROBE_MANUALLY)
      if (seenQ) G29_RETURN(false);
    #endif
  #endif

  #if ENABLED(PROBE_MANUALLY)
    const bool seenA = parser.seen('A');
  #else
    constexpr bool seenA = false;
  #endif

  const bool  no_action = seenA || seenQ,
              faux =
                #if ENABLED(DEBUG_LEVELING_FEATURE) && DISABLED(PROBE_MANUALLY)
                  parser.boolval('C')
                #else
                  no_action
                #endif
              ;

  // Don't allow auto-leveling without homing first
  if (axis_unhomed_error()) G29_RETURN(false);

  if (!no_action && planner.leveling_active && parser.boolval('O')) { // Auto-level only if needed
    if (DEBUGGING(LEVELING)) DEBUG_ECHOLNPGM("> Auto-level not needed, skip\n<<< G29");
    G29_RETURN(false);
  }

  // Define local vars 'static' for manual probing, 'auto' otherwise
  #if ENABLED(PROBE_MANUALLY)
    #define ABL_VAR static
  #else
    #define ABL_VAR
  #endif

  ABL_VAR int verbose_level;
  ABL_VAR xy_pos_t probePos;
  ABL_VAR float measured_z;
  ABL_VAR bool dryrun, abl_should_enable;

  #if EITHER(PROBE_MANUALLY, AUTO_BED_LEVELING_LINEAR)
    ABL_VAR int abl_probe_index;
  #endif

  #if HAS_SOFTWARE_ENDSTOPS && ENABLED(PROBE_MANUALLY)
    ABL_VAR bool saved_soft_endstops_state = true;
  #endif

  #if ABL_GRID

    #if ENABLED(PROBE_MANUALLY)
      ABL_VAR xy_int8_t meshCount;
    #endif

    ABL_VAR xy_float_t probe_position_lf, probe_position_rb;
    ABL_VAR xy_float_t gridSpacing = { 0, 0 };

    #if ENABLED(AUTO_BED_LEVELING_LINEAR)
      ABL_VAR bool do_topography_map;
      ABL_VAR xy_uint8_t abl_grid_points;
    #else // Bilinear
      constexpr xy_uint8_t abl_grid_points = { GRID_MAX_POINTS_X, GRID_MAX_POINTS_Y };
    #endif

    #if ENABLED(AUTO_BED_LEVELING_LINEAR)
      ABL_VAR int abl_points;
    #elif ENABLED(PROBE_MANUALLY) // Bilinear
      int constexpr abl_points = GRID_MAX_POINTS;
    #endif

    #if ENABLED(AUTO_BED_LEVELING_BILINEAR)

      ABL_VAR float zoffset;

    #elif ENABLED(AUTO_BED_LEVELING_LINEAR)

      ABL_VAR int indexIntoAB[GRID_MAX_POINTS_X][GRID_MAX_POINTS_Y];

      ABL_VAR float eqnAMatrix[(GRID_MAX_POINTS) * 3], // "A" matrix of the linear system of equations
                    eqnBVector[GRID_MAX_POINTS],       // "B" vector of Z points
                    mean;
    #endif

  #elif ENABLED(AUTO_BED_LEVELING_3POINT)

    #if ENABLED(PROBE_MANUALLY)
      int constexpr abl_points = 3; // used to show total points
    #endif

    vector_3 points[3];
    get_three_probe_points(points);

  #endif // AUTO_BED_LEVELING_3POINT

  #if ENABLED(AUTO_BED_LEVELING_LINEAR)
    struct linear_fit_data lsf_results;
    incremental_LSF_reset(&lsf_results);
=======
    DEBUG_SECTION(log_G29, "G29", DEBUGGING(LEVELING));
    if (DEBUGGING(LEVELING)) log_machine_info();
    marlin_debug_flags = old_debug_flags;
    if (DISABLED(PROBE_MANUALLY) && seenQ) G29_RETURN(false);
  #endif

  const bool seenA = TERN0(PROBE_MANUALLY, parser.seen_test('A')),
         no_action = seenA || seenQ,
              faux = ENABLED(DEBUG_LEVELING_FEATURE) && DISABLED(PROBE_MANUALLY) ? parser.boolval('C') : no_action;

  if (!no_action && planner.leveling_active && parser.boolval('O')) { // Auto-level only if needed
    if (DEBUGGING(LEVELING)) DEBUG_ECHOLNPGM("> Auto-level not needed, skip");
    G29_RETURN(false);
  }

  // Send 'N' to force homing before G29 (internal only)
  if (parser.seen_test('N'))
    process_subcommands_now_P(TERN(G28_L0_ENSURES_LEVELING_OFF, PSTR("G28L0"), G28_STR));

  // Don't allow auto-leveling without homing first
  if (homing_needed_error()) G29_RETURN(false);

  #if ENABLED(AUTO_BED_LEVELING_3POINT)
    vector_3 points[3];
    probe.get_three_points(points);
  #endif

  #if ENABLED(AUTO_BED_LEVELING_LINEAR)
    struct linear_fit_data lsf_results;
>>>>>>> mcu_ctrl
  #endif

  /**
   * On the initial G29 fetch command parameters.
   */
  if (!g29_in_progress) {

<<<<<<< HEAD
    #if HOTENDS > 1
      if (active_extruder != 0) tool_change(0);
    #endif

    #if EITHER(PROBE_MANUALLY, AUTO_BED_LEVELING_LINEAR)
      abl_probe_index = -1;
    #endif

    abl_should_enable = planner.leveling_active;

    #if ENABLED(AUTO_BED_LEVELING_BILINEAR)

      const bool seen_w = parser.seen('W');
=======
    TERN_(HAS_MULTI_HOTEND, if (active_extruder) tool_change(0));

    #if EITHER(PROBE_MANUALLY, AUTO_BED_LEVELING_LINEAR)
      abl.abl_probe_index = -1;
    #endif

    abl.reenable = planner.leveling_active;

    #if ENABLED(AUTO_BED_LEVELING_BILINEAR)

      const bool seen_w = parser.seen_test('W');
>>>>>>> mcu_ctrl
      if (seen_w) {
        if (!leveling_is_valid()) {
          SERIAL_ERROR_MSG("No bilinear grid");
          G29_RETURN(false);
        }

        const float rz = parser.seenval('Z') ? RAW_Z_POSITION(parser.value_linear_units()) : current_position.z;
        if (!WITHIN(rz, -10, 10)) {
          SERIAL_ERROR_MSG("Bad Z value");
          G29_RETURN(false);
        }

        const float rx = RAW_X_POSITION(parser.linearval('X', NAN)),
                    ry = RAW_Y_POSITION(parser.linearval('Y', NAN));
        int8_t i = parser.byteval('I', -1), j = parser.byteval('J', -1);

        if (!isnan(rx) && !isnan(ry)) {
          // Get nearest i / j from rx / ry
<<<<<<< HEAD
          i = (rx - bilinear_start.x + 0.5 * gridSpacing.x) / gridSpacing.x;
          j = (ry - bilinear_start.y + 0.5 * gridSpacing.y) / gridSpacing.y;
          LIMIT(i, 0, GRID_MAX_POINTS_X - 1);
          LIMIT(j, 0, GRID_MAX_POINTS_Y - 1);
        }
        if (WITHIN(i, 0, GRID_MAX_POINTS_X - 1) && WITHIN(j, 0, GRID_MAX_POINTS_Y)) {
          set_bed_leveling_enabled(false);
          z_values[i][j] = rz;
          #if ENABLED(ABL_BILINEAR_SUBDIVISION)
            bed_level_virt_interpolate();
          #endif
          #if ENABLED(EXTENSIBLE_UI)
            ExtUI::onMeshUpdate(i, j, rz);
          #endif
          set_bed_leveling_enabled(abl_should_enable);
          if (abl_should_enable) report_current_position();
        }
        G29_RETURN(false);
      } // parser.seen('W')
=======
          i = (rx - bilinear_start.x + 0.5 * abl.gridSpacing.x) / abl.gridSpacing.x;
          j = (ry - bilinear_start.y + 0.5 * abl.gridSpacing.y) / abl.gridSpacing.y;
          LIMIT(i, 0, (GRID_MAX_POINTS_X) - 1);
          LIMIT(j, 0, (GRID_MAX_POINTS_Y) - 1);
        }
        if (WITHIN(i, 0, (GRID_MAX_POINTS_X) - 1) && WITHIN(j, 0, (GRID_MAX_POINTS_Y) - 1)) {
          set_bed_leveling_enabled(false);
          z_values[i][j] = rz;
          TERN_(ABL_BILINEAR_SUBDIVISION, bed_level_virt_interpolate());
          TERN_(EXTENSIBLE_UI, ExtUI::onMeshUpdate(i, j, rz));
          set_bed_leveling_enabled(abl.reenable);
          if (abl.reenable) report_current_position();
        }
        G29_RETURN(false);
      } // parser.seen_test('W')
>>>>>>> mcu_ctrl

    #else

      constexpr bool seen_w = false;

    #endif

    // Jettison bed leveling data
<<<<<<< HEAD
    if (!seen_w && parser.seen('J')) {
=======
    if (!seen_w && parser.seen_test('J')) {
>>>>>>> mcu_ctrl
      reset_bed_level();
      G29_RETURN(false);
    }

<<<<<<< HEAD
    verbose_level = parser.intval('V');
    if (!WITHIN(verbose_level, 0, 4)) {
=======
    abl.verbose_level = parser.intval('V');
    if (!WITHIN(abl.verbose_level, 0, 4)) {
>>>>>>> mcu_ctrl
      SERIAL_ECHOLNPGM("?(V)erbose level implausible (0-4).");
      G29_RETURN(false);
    }

<<<<<<< HEAD
    dryrun = parser.boolval('D')
      #if ENABLED(PROBE_MANUALLY)
        || no_action
      #endif
    ;

    #if ENABLED(AUTO_BED_LEVELING_LINEAR)

      do_topography_map = verbose_level > 2 || parser.boolval('T');

      // X and Y specify points in each direction, overriding the default
      // These values may be saved with the completed mesh
      abl_grid_points.set(
        parser.byteval('X', GRID_MAX_POINTS_X),
        parser.byteval('Y', GRID_MAX_POINTS_Y)
      );
      if (parser.seenval('P')) abl_grid_points.x = abl_grid_points.y = parser.value_int();

      if (!WITHIN(abl_grid_points.x, 2, GRID_MAX_POINTS_X)) {
        SERIAL_ECHOLNPGM("?Probe points (X) implausible (2-" STRINGIFY(GRID_MAX_POINTS_X) ").");
        G29_RETURN(false);
      }
      if (!WITHIN(abl_grid_points.y, 2, GRID_MAX_POINTS_Y)) {
=======
    abl.dryrun = parser.boolval('D') || TERN0(PROBE_MANUALLY, no_action);

    #if ENABLED(AUTO_BED_LEVELING_LINEAR)

      incremental_LSF_reset(&lsf_results);

      abl.topography_map = abl.verbose_level > 2 || parser.boolval('T');

      // X and Y specify points in each direction, overriding the default
      // These values may be saved with the completed mesh
      abl.grid_points.set(
        parser.byteval('X', GRID_MAX_POINTS_X),
        parser.byteval('Y', GRID_MAX_POINTS_Y)
      );
      if (parser.seenval('P')) abl.grid_points.x = abl.grid_points.y = parser.value_int();

      if (!WITHIN(abl.grid_points.x, 2, GRID_MAX_POINTS_X)) {
        SERIAL_ECHOLNPGM("?Probe points (X) implausible (2-" STRINGIFY(GRID_MAX_POINTS_X) ").");
        G29_RETURN(false);
      }
      if (!WITHIN(abl.grid_points.y, 2, GRID_MAX_POINTS_Y)) {
>>>>>>> mcu_ctrl
        SERIAL_ECHOLNPGM("?Probe points (Y) implausible (2-" STRINGIFY(GRID_MAX_POINTS_Y) ").");
        G29_RETURN(false);
      }

<<<<<<< HEAD
      abl_points = abl_grid_points.x * abl_grid_points.y;
      mean = 0;

    #elif ENABLED(AUTO_BED_LEVELING_BILINEAR)

      zoffset = parser.linearval('Z');

    #endif

    #if ABL_GRID

      xy_probe_feedrate_mm_s = MMM_TO_MMS(parser.linearval('S', XY_PROBE_SPEED));

      const float x_min = probe_min_x(), x_max = probe_max_x(),
                  y_min = probe_min_y(), y_max = probe_max_y();

      if (parser.seen('H')) {
        const int16_t size = (int16_t)parser.value_linear_units();
        probe_position_lf.set(
          _MAX(X_CENTER - size / 2, x_min),
          _MAX(Y_CENTER - size / 2, y_min)
        );
        probe_position_rb.set(
          _MIN(probe_position_lf.x + size, x_max),
          _MIN(probe_position_lf.y + size, y_max)
        );
      }
      else {
        probe_position_lf.set(
          parser.seenval('L') ? (int)RAW_X_POSITION(parser.value_linear_units()) : _MAX(X_CENTER - (X_BED_SIZE) / 2,      x_min),
          parser.seenval('F') ? (int)RAW_Y_POSITION(parser.value_linear_units()) : _MAX(Y_CENTER - (Y_BED_SIZE) / 2,      y_min)
        );
        probe_position_rb.set(
          parser.seenval('R') ? (int)RAW_X_POSITION(parser.value_linear_units()) : _MIN(probe_position_lf.x + X_BED_SIZE, x_max),
          parser.seenval('B') ? (int)RAW_Y_POSITION(parser.value_linear_units()) : _MIN(probe_position_lf.y + Y_BED_SIZE, y_max)
        );
      }

      if (
        #if IS_SCARA || ENABLED(DELTA)
             !position_is_reachable_by_probe(probe_position_lf.x, 0)
          || !position_is_reachable_by_probe(probe_position_rb.x, 0)
          || !position_is_reachable_by_probe(0, probe_position_lf.y)
          || !position_is_reachable_by_probe(0, probe_position_rb.y)
        #else
             !position_is_reachable_by_probe(probe_position_lf)
          || !position_is_reachable_by_probe(probe_position_rb)
        #endif
      ) {
=======
      abl.abl_points = abl.grid_points.x * abl.grid_points.y;
      abl.mean = 0;

    #elif ENABLED(AUTO_BED_LEVELING_BILINEAR)

      abl.Z_offset = parser.linearval('Z');

    #endif

    #if ABL_USES_GRID

      xy_probe_feedrate_mm_s = MMM_TO_MMS(parser.linearval('S', XY_PROBE_FEEDRATE));

      const float x_min = probe.min_x(), x_max = probe.max_x(),
                  y_min = probe.min_y(), y_max = probe.max_y();

      if (parser.seen('H')) {
        const int16_t size = (int16_t)parser.value_linear_units();
        abl.probe_position_lf.set(_MAX((X_CENTER) - size / 2, x_min), _MAX((Y_CENTER) - size / 2, y_min));
        abl.probe_position_rb.set(_MIN(abl.probe_position_lf.x + size, x_max), _MIN(abl.probe_position_lf.y + size, y_max));
      }
      else {
        abl.probe_position_lf.set(parser.linearval('L', x_min), parser.linearval('F', y_min));
        abl.probe_position_rb.set(parser.linearval('R', x_max), parser.linearval('B', y_max));
      }

      if (!probe.good_bounds(abl.probe_position_lf, abl.probe_position_rb)) {
        if (DEBUGGING(LEVELING)) {
          DEBUG_ECHOLNPAIR("G29 L", abl.probe_position_lf.x, " R", abl.probe_position_rb.x,
                              " F", abl.probe_position_lf.y, " B", abl.probe_position_rb.y);
        }
>>>>>>> mcu_ctrl
        SERIAL_ECHOLNPGM("? (L,R,F,B) out of bounds.");
        G29_RETURN(false);
      }

<<<<<<< HEAD
      // probe at the points of a lattice grid
      gridSpacing.set((probe_position_rb.x - probe_position_lf.x) / (abl_grid_points.x - 1),
                      (probe_position_rb.y - probe_position_lf.y) / (abl_grid_points.y - 1));

    #endif // ABL_GRID

    if (verbose_level > 0) {
      SERIAL_ECHOPGM("G29 Auto Bed Leveling");
      if (dryrun) SERIAL_ECHOPGM(" (DRYRUN)");
=======
      // Probe at the points of a lattice grid
      abl.gridSpacing.set((abl.probe_position_rb.x - abl.probe_position_lf.x) / (abl.grid_points.x - 1),
                            (abl.probe_position_rb.y - abl.probe_position_lf.y) / (abl.grid_points.y - 1));

    #endif // ABL_USES_GRID

    if (abl.verbose_level > 0) {
      SERIAL_ECHOPGM("G29 Auto Bed Leveling");
      if (abl.dryrun) SERIAL_ECHOPGM(" (DRYRUN)");
>>>>>>> mcu_ctrl
      SERIAL_EOL();
    }

    planner.synchronize();

<<<<<<< HEAD
=======
    #if ENABLED(AUTO_BED_LEVELING_3POINT)
      if (DEBUGGING(LEVELING)) DEBUG_ECHOLNPGM("> 3-point Leveling");
      points[0].z = points[1].z = points[2].z = 0;  // Probe at 3 arbitrary points
    #endif

    #if BOTH(AUTO_BED_LEVELING_BILINEAR, EXTENSIBLE_UI)
      ExtUI::onMeshLevelingStart();
    #endif

    if (!faux) {
      remember_feedrate_scaling_off();

      #if ENABLED(PREHEAT_BEFORE_LEVELING)
        if (!abl.dryrun) probe.preheat_for_probing(LEVELING_NOZZLE_TEMP, LEVELING_BED_TEMP);
      #endif
    }

>>>>>>> mcu_ctrl
    // Disable auto bed leveling during G29.
    // Be formal so G29 can be done successively without G28.
    if (!no_action) set_bed_leveling_enabled(false);

<<<<<<< HEAD
    #if HAS_BED_PROBE
      // Deploy the probe. Probe will raise if needed.
      if (DEPLOY_PROBE()) {
        set_bed_leveling_enabled(abl_should_enable);
=======
    // Deploy certain probes before starting probing
    #if HAS_BED_PROBE
      if (ENABLED(BLTOUCH))
        do_z_clearance(Z_CLEARANCE_DEPLOY_PROBE);
      else if (probe.deploy()) {
        set_bed_leveling_enabled(abl.reenable);
>>>>>>> mcu_ctrl
        G29_RETURN(false);
      }
    #endif

<<<<<<< HEAD
    do_blocking_move_to_z(_MAX(Z_CLEARANCE_BETWEEN_PROBES, Z_CLEARANCE_DEPLOY_PROBE));

    if (!faux) remember_feedrate_scaling_off();

    #if ENABLED(AUTO_BED_LEVELING_BILINEAR)

      #if ENABLED(PROBE_MANUALLY)
        if (!no_action)
      #endif
      if (gridSpacing != bilinear_grid_spacing || probe_position_lf != bilinear_start) {
=======
    #if ENABLED(AUTO_BED_LEVELING_BILINEAR)
      if (TERN1(PROBE_MANUALLY, !no_action)
        && (abl.gridSpacing != bilinear_grid_spacing || abl.probe_position_lf != bilinear_start)
      ) {
>>>>>>> mcu_ctrl
        // Reset grid to 0.0 or "not probed". (Also disables ABL)
        reset_bed_level();

        // Initialize a grid with the given dimensions
<<<<<<< HEAD
        bilinear_grid_spacing = gridSpacing;
        bilinear_start = probe_position_lf;

        // Can't re-enable (on error) until the new grid is written
        abl_should_enable = false;
      }

    #endif // AUTO_BED_LEVELING_BILINEAR

    #if ENABLED(AUTO_BED_LEVELING_3POINT)

      if (DEBUGGING(LEVELING)) DEBUG_ECHOLNPGM("> 3-point Leveling");

      // Probe at 3 arbitrary points
      points[0].z = points[1].z = points[2].z = 0;

    #endif // AUTO_BED_LEVELING_3POINT

=======
        bilinear_grid_spacing = abl.gridSpacing;
        bilinear_start = abl.probe_position_lf;

        // Can't re-enable (on error) until the new grid is written
        abl.reenable = false;
      }
    #endif // AUTO_BED_LEVELING_BILINEAR

>>>>>>> mcu_ctrl
  } // !g29_in_progress

  #if ENABLED(PROBE_MANUALLY)

    // For manual probing, get the next index to probe now.
    // On the first probe this will be incremented to 0.
    if (!no_action) {
<<<<<<< HEAD
      ++abl_probe_index;
=======
      ++abl.abl_probe_index;
>>>>>>> mcu_ctrl
      g29_in_progress = true;
    }

    // Abort current G29 procedure, go back to idle state
    if (seenA && g29_in_progress) {
      SERIAL_ECHOLNPGM("Manual G29 aborted");
<<<<<<< HEAD
      #if HAS_SOFTWARE_ENDSTOPS
        soft_endstops_enabled = saved_soft_endstops_state;
      #endif
      set_bed_leveling_enabled(abl_should_enable);
      g29_in_progress = false;
      #if ENABLED(LCD_BED_LEVELING)
        ui.wait_for_bl_move = false;
      #endif
    }

    // Query G29 status
    if (verbose_level || seenQ) {
      SERIAL_ECHOPGM("Manual G29 ");
      if (g29_in_progress) {
        SERIAL_ECHOPAIR("point ", _MIN(abl_probe_index + 1, abl_points));
        SERIAL_ECHOLNPAIR(" of ", abl_points);
=======
      SET_SOFT_ENDSTOP_LOOSE(false);
      set_bed_leveling_enabled(abl.reenable);
      g29_in_progress = false;
      TERN_(LCD_BED_LEVELING, ui.wait_for_move = false);
    }

    // Query G29 status
    if (abl.verbose_level || seenQ) {
      SERIAL_ECHOPGM("Manual G29 ");
      if (g29_in_progress) {
        SERIAL_ECHOPAIR("point ", _MIN(abl.abl_probe_index + 1, abl.abl_points));
        SERIAL_ECHOLNPAIR(" of ", abl.abl_points);
>>>>>>> mcu_ctrl
      }
      else
        SERIAL_ECHOLNPGM("idle");
    }

    if (no_action) G29_RETURN(false);

<<<<<<< HEAD
    if (abl_probe_index == 0) {
      // For the initial G29 S2 save software endstop state
      #if HAS_SOFTWARE_ENDSTOPS
        saved_soft_endstops_state = soft_endstops_enabled;
      #endif
=======
    if (abl.abl_probe_index == 0) {
      // For the initial G29 S2 save software endstop state
      SET_SOFT_ENDSTOP_LOOSE(true);
>>>>>>> mcu_ctrl
      // Move close to the bed before the first point
      do_blocking_move_to_z(0);
    }
    else {

      #if EITHER(AUTO_BED_LEVELING_LINEAR, AUTO_BED_LEVELING_3POINT)
<<<<<<< HEAD
        const uint16_t index = abl_probe_index - 1;
=======
        const uint16_t index = abl.abl_probe_index - 1;
>>>>>>> mcu_ctrl
      #endif

      // For G29 after adjusting Z.
      // Save the previous Z before going to the next point
<<<<<<< HEAD
      measured_z = current_position.z;

      #if ENABLED(AUTO_BED_LEVELING_LINEAR)

        mean += measured_z;
        eqnBVector[index] = measured_z;
        eqnAMatrix[index + 0 * abl_points] = probePos.x;
        eqnAMatrix[index + 1 * abl_points] = probePos.y;
        eqnAMatrix[index + 2 * abl_points] = 1;

        incremental_LSF(&lsf_results, probePos, measured_z);

      #elif ENABLED(AUTO_BED_LEVELING_3POINT)

        points[index].z = measured_z;

      #elif ENABLED(AUTO_BED_LEVELING_BILINEAR)

        const float newz = measured_z + zoffset;
        z_values[meshCount.x][meshCount.y] = newz;
        #if ENABLED(EXTENSIBLE_UI)
          ExtUI::onMeshUpdate(meshCount, newz);
        #endif

        if (DEBUGGING(LEVELING)) DEBUG_ECHOLNPAIR_P(PSTR("Save X"), meshCount.x, SP_Y_STR, meshCount.y, SP_Z_STR, measured_z + zoffset);
=======
      abl.measured_z = current_position.z;

      #if ENABLED(AUTO_BED_LEVELING_LINEAR)

        abl.mean += abl.measured_z;
        abl.eqnBVector[index] = abl.measured_z;
        abl.eqnAMatrix[index + 0 * abl.abl_points] = abl.probePos.x;
        abl.eqnAMatrix[index + 1 * abl.abl_points] = abl.probePos.y;
        abl.eqnAMatrix[index + 2 * abl.abl_points] = 1;

        incremental_LSF(&lsf_results, abl.probePos, abl.measured_z);

      #elif ENABLED(AUTO_BED_LEVELING_3POINT)

        points[index].z = abl.measured_z;

      #elif ENABLED(AUTO_BED_LEVELING_BILINEAR)

        const float newz = abl.measured_z + abl.Z_offset;
        z_values[abl.meshCount.x][abl.meshCount.y] = newz;
        TERN_(EXTENSIBLE_UI, ExtUI::onMeshUpdate(abl.meshCount, newz));

        if (DEBUGGING(LEVELING)) DEBUG_ECHOLNPAIR_P(PSTR("Save X"), abl.meshCount.x, SP_Y_STR, abl.meshCount.y, SP_Z_STR, abl.measured_z + abl.Z_offset);
>>>>>>> mcu_ctrl

      #endif
    }

    //
    // If there's another point to sample, move there with optional lift.
    //

<<<<<<< HEAD
    #if ABL_GRID

      // Skip any unreachable points
      while (abl_probe_index < abl_points) {

        // Set meshCount.x, meshCount.y based on abl_probe_index, with zig-zag
        PR_OUTER_VAR = abl_probe_index / PR_INNER_END;
        PR_INNER_VAR = abl_probe_index - (PR_OUTER_VAR * PR_INNER_END);

        // Probe in reverse order for every other row/column
        bool zig = (PR_OUTER_VAR & 1); // != ((PR_OUTER_END) & 1);

        if (zig) PR_INNER_VAR = (PR_INNER_END - 1) - PR_INNER_VAR;

        probePos = probe_position_lf + gridSpacing * meshCount.asFloat();

        #if ENABLED(AUTO_BED_LEVELING_LINEAR)
          indexIntoAB[meshCount.x][meshCount.y] = abl_probe_index;
        #endif

        // Keep looping till a reachable point is found
        if (position_is_reachable(probePos)) break;
        ++abl_probe_index;
      }

      // Is there a next point to move to?
      if (abl_probe_index < abl_points) {
        _manual_goto_xy(probePos); // Can be used here too!
        #if HAS_SOFTWARE_ENDSTOPS
          // Disable software endstops to allow manual adjustment
          // If G29 is not completed, they will not be re-enabled
          soft_endstops_enabled = false;
        #endif
        G29_RETURN(false);
      }
      else {

        // Leveling done! Fall through to G29 finishing code below

        SERIAL_ECHOLNPGM("Grid probing done.");

        // Re-enable software endstops, if needed
        #if HAS_SOFTWARE_ENDSTOPS
          soft_endstops_enabled = saved_soft_endstops_state;
        #endif
=======
    #if ABL_USES_GRID

      // Skip any unreachable points
      while (abl.abl_probe_index < abl.abl_points) {

        // Set abl.meshCount.x, abl.meshCount.y based on abl.abl_probe_index, with zig-zag
        PR_OUTER_VAR = abl.abl_probe_index / PR_INNER_SIZE;
        PR_INNER_VAR = abl.abl_probe_index - (PR_OUTER_VAR * PR_INNER_SIZE);

        // Probe in reverse order for every other row/column
        const bool zig = (PR_OUTER_VAR & 1); // != ((PR_OUTER_SIZE) & 1);
        if (zig) PR_INNER_VAR = (PR_INNER_SIZE - 1) - PR_INNER_VAR;

        abl.probePos = abl.probe_position_lf + abl.gridSpacing * abl.meshCount.asFloat();

        TERN_(AUTO_BED_LEVELING_LINEAR, abl.indexIntoAB[abl.meshCount.x][abl.meshCount.y] = abl.abl_probe_index);

        // Keep looping till a reachable point is found
        if (position_is_reachable(abl.probePos)) break;
        ++abl.abl_probe_index;
      }

      // Is there a next point to move to?
      if (abl.abl_probe_index < abl.abl_points) {
        _manual_goto_xy(abl.probePos); // Can be used here too!
        // Disable software endstops to allow manual adjustment
        // If G29 is not completed, they will not be re-enabled
        SET_SOFT_ENDSTOP_LOOSE(true);
        G29_RETURN(false);
      }
      else {
        // Leveling done! Fall through to G29 finishing code below
        SERIAL_ECHOLNPGM("Grid probing done.");
        // Re-enable software endstops, if needed
        SET_SOFT_ENDSTOP_LOOSE(false);
>>>>>>> mcu_ctrl
      }

    #elif ENABLED(AUTO_BED_LEVELING_3POINT)

      // Probe at 3 arbitrary points
<<<<<<< HEAD
      if (abl_probe_index < abl_points) {
        probePos = points[abl_probe_index];
        _manual_goto_xy(probePos);
        #if HAS_SOFTWARE_ENDSTOPS
          // Disable software endstops to allow manual adjustment
          // If G29 is not completed, they will not be re-enabled
          soft_endstops_enabled = false;
        #endif
=======
      if (abl.abl_probe_index < abl.abl_points) {
        abl.probePos = points[abl.abl_probe_index];
        _manual_goto_xy(abl.probePos);
        // Disable software endstops to allow manual adjustment
        // If G29 is not completed, they will not be re-enabled
        SET_SOFT_ENDSTOP_LOOSE(true);
>>>>>>> mcu_ctrl
        G29_RETURN(false);
      }
      else {

        SERIAL_ECHOLNPGM("3-point probing done.");

        // Re-enable software endstops, if needed
<<<<<<< HEAD
        #if HAS_SOFTWARE_ENDSTOPS
          soft_endstops_enabled = saved_soft_endstops_state;
        #endif

        if (!dryrun) {
=======
        SET_SOFT_ENDSTOP_LOOSE(false);

        if (!abl.dryrun) {
>>>>>>> mcu_ctrl
          vector_3 planeNormal = vector_3::cross(points[0] - points[1], points[2] - points[1]).get_normal();
          if (planeNormal.z < 0) planeNormal *= -1;
          planner.bed_level_matrix = matrix_3x3::create_look_at(planeNormal);

          // Can't re-enable (on error) until the new grid is written
<<<<<<< HEAD
          abl_should_enable = false;
=======
          abl.reenable = false;
>>>>>>> mcu_ctrl
        }

      }

    #endif // AUTO_BED_LEVELING_3POINT

  #else // !PROBE_MANUALLY
  {
    const ProbePtRaise raise_after = parser.boolval('E') ? PROBE_PT_STOW : PROBE_PT_RAISE;

<<<<<<< HEAD
    measured_z = 0;

    #if ABL_GRID

      // bool zig = PR_OUTER_END & 1;  // Always end at RIGHT and BACK_PROBE_BED_POSITION
      bool zig = 1;

      uint8_t showcount = 0;

      measured_z = 0;

      xy_int8_t meshCount;

      // Outer loop is X with PROBE_Y_FIRST enabled
      // Outer loop is Y with PROBE_Y_FIRST disabled
      for (PR_OUTER_VAR = 0; PR_OUTER_VAR < PR_OUTER_END && !isnan(measured_z); PR_OUTER_VAR++) {

        int8_t inStart, inStop, inInc;

        if (zig) {                    // Zig away from origin
          inStart = 0;                // Left or front
          inStop = PR_INNER_END;      // Right or back
          inInc = 1;                  // Zig right
        }
        else {                        // Zag towards origin
          inStart = PR_INNER_END - 1; // Right or back
          inStop = -1;                // Left or front
          inInc = -1;                 // Zag left
=======
    abl.measured_z = 0;

    #if ABL_USES_GRID

      bool zig = PR_OUTER_SIZE & 1;  // Always end at RIGHT and BACK_PROBE_BED_POSITION

      abl.measured_z = 0;

      // Outer loop is X with PROBE_Y_FIRST enabled
      // Outer loop is Y with PROBE_Y_FIRST disabled
      for (PR_OUTER_VAR = 0; PR_OUTER_VAR < PR_OUTER_SIZE && !isnan(abl.measured_z); PR_OUTER_VAR++) {

        int8_t inStart, inStop, inInc;

        if (zig) {                      // Zig away from origin
          inStart = 0;                  // Left or front
          inStop = PR_INNER_SIZE;       // Right or back
          inInc = 1;                    // Zig right
        }
        else {                          // Zag towards origin
          inStart = PR_INNER_SIZE - 1;  // Right or back
          inStop = -1;                  // Left or front
          inInc = -1;                   // Zag left
>>>>>>> mcu_ctrl
        }

        zig ^= true; // zag

        // An index to print current state
<<<<<<< HEAD
        uint8_t pt_index = (PR_OUTER_VAR) * (PR_INNER_END) + 1;
=======
        uint8_t pt_index = (PR_OUTER_VAR) * (PR_INNER_SIZE) + 1;
>>>>>>> mcu_ctrl

        // Inner loop is Y with PROBE_Y_FIRST enabled
        // Inner loop is X with PROBE_Y_FIRST disabled
        for (PR_INNER_VAR = inStart; PR_INNER_VAR != inStop; pt_index++, PR_INNER_VAR += inInc) {

<<<<<<< HEAD
          probePos = probe_position_lf + gridSpacing * meshCount.asFloat();

          #if ENABLED(AUTO_BED_LEVELING_LINEAR)
            indexIntoAB[meshCount.x][meshCount.y] = ++abl_probe_index; // 0...
          #endif

          #if IS_KINEMATIC
            // Avoid probing outside the round or hexagonal area
            if (!position_is_reachable_by_probe(probePos)) continue;
          #endif

          if (verbose_level) SERIAL_ECHOLNPAIR("Probing mesh point ", int(pt_index), "/", int(GRID_MAX_POINTS), ".");
          #if HAS_DISPLAY
            ui.status_printf_P(0, PSTR(S_FMT " %i/%i"), GET_TEXT(MSG_PROBING_MESH), int(pt_index), int(GRID_MAX_POINTS));
          #endif

          measured_z = faux ? 0.001f * random(-100, 101) : probe_at_point(probePos, raise_after, verbose_level);

          if (isnan(measured_z)) {
            set_bed_leveling_enabled(abl_should_enable);
            break; // Breaks out of both loops
          }

          #if ENABLED(AUTO_BED_LEVELING_LINEAR)

            mean += measured_z;
            eqnBVector[abl_probe_index] = measured_z;
            eqnAMatrix[abl_probe_index + 0 * abl_points] = probePos.x;
            eqnAMatrix[abl_probe_index + 1 * abl_points] = probePos.y;
            eqnAMatrix[abl_probe_index + 2 * abl_points] = 1;

            incremental_LSF(&lsf_results, probePos, measured_z);

          #elif ENABLED(AUTO_BED_LEVELING_BILINEAR)

            z_values[meshCount.x][meshCount.y] = measured_z + zoffset;
            #if ENABLED(EXTENSIBLE_UI)
              ExtUI::onMeshUpdate(meshCount, z_values[meshCount.x][meshCount.y]);
            #endif

            #ifdef RTS_AVAILABLE
              if(!IS_SD_PRINTING())
              {
                if((showcount++) < GRID_MAX_POINTS)
                {
                  rtscheck.RTS_SndData(showcount, AUTO_BED_LEVEL_TITLE_VP);
                  if(language_change_font != 0)
                  {
                    rtscheck.RTS_SndData(ExchangePageBase + 26, ExchangepageAddr);
                    change_page_font = 26;
                  }
                  rtscheck.RTS_SndData(AUTO_BED_LEVEL_PREHEAT, AUTO_BED_PREHEAT_HEAD_DATA_VP);
                  rtscheck.RTS_SndData(AUTO_BED_LEVEL_PREHEAT, HEAD_SET_TEMP_VP);
                  rtscheck.RTS_SndData(probe_offset.z * 100, AUTO_BED_LEVEL_ZOFFSET_VP);

                  rtscheck.RTS_SndData(feedrate_percentage, PRINT_SPEED_RATE_VP);
                  rtscheck.RTS_SndData(thermalManager.temp_hotend[0].target, HEAD_SET_TEMP_VP);
                  rtscheck.RTS_SndData(thermalManager.temp_bed.target, BED_SET_TEMP_VP);
                }
              }
            #endif

          #endif

          abl_should_enable = false;
          idle();

        } // inner
      } // outer
=======
          abl.probePos = abl.probe_position_lf + abl.gridSpacing * abl.meshCount.asFloat();

          TERN_(AUTO_BED_LEVELING_LINEAR, abl.indexIntoAB[abl.meshCount.x][abl.meshCount.y] = ++abl.abl_probe_index); // 0...

          // Avoid probing outside the round or hexagonal area
          if (TERN0(IS_KINEMATIC, !probe.can_reach(abl.probePos))) continue;

          if (abl.verbose_level) SERIAL_ECHOLNPAIR("Probing mesh point ", pt_index, "/", abl.abl_points, ".");
          TERN_(HAS_STATUS_MESSAGE, ui.status_printf_P(0, PSTR(S_FMT " %i/%i"), GET_TEXT(MSG_PROBING_MESH), int(pt_index), int(abl.abl_points)));

          abl.measured_z = faux ? 0.001f * random(-100, 101) : probe.probe_at_point(abl.probePos, raise_after, abl.verbose_level);

          if (isnan(abl.measured_z)) {
            set_bed_leveling_enabled(abl.reenable);
            break; // Breaks out of both loops
          }

          #if ENABLED(PROBE_TEMP_COMPENSATION)
            temp_comp.compensate_measurement(TSI_BED, thermalManager.degBed(), abl.measured_z);
            temp_comp.compensate_measurement(TSI_PROBE, thermalManager.degProbe(), abl.measured_z);
            TERN_(USE_TEMP_EXT_COMPENSATION, temp_comp.compensate_measurement(TSI_EXT, thermalManager.degHotend(), abl.measured_z));
          #endif

          #if ENABLED(AUTO_BED_LEVELING_LINEAR)

            abl.mean += abl.measured_z;
            abl.eqnBVector[abl.abl_probe_index] = abl.measured_z;
            abl.eqnAMatrix[abl.abl_probe_index + 0 * abl.abl_points] = abl.probePos.x;
            abl.eqnAMatrix[abl.abl_probe_index + 1 * abl.abl_points] = abl.probePos.y;
            abl.eqnAMatrix[abl.abl_probe_index + 2 * abl.abl_points] = 1;

            incremental_LSF(&lsf_results, abl.probePos, abl.measured_z);

          #elif ENABLED(AUTO_BED_LEVELING_BILINEAR)

            const float z = abl.measured_z + abl.Z_offset;
            z_values[abl.meshCount.x][abl.meshCount.y] = z;
            TERN_(EXTENSIBLE_UI, ExtUI::onMeshUpdate(abl.meshCount, z));

            TERN_(DWIN_CREALITY_SERMOON_V2, gLcdSermoonV2UI.ShowLevelingProgress(abl.meshCount));
          #endif

          abl.reenable = false;
          idle_no_sleep();
        } // inner
      } // outer 
>>>>>>> mcu_ctrl

    #elif ENABLED(AUTO_BED_LEVELING_3POINT)

      // Probe at 3 arbitrary points

<<<<<<< HEAD
      for (uint8_t i = 0; i < 3; ++i) {
        if (verbose_level) SERIAL_ECHOLNPAIR("Probing point ", int(i), "/3.");
        #if HAS_DISPLAY
          ui.status_printf_P(0, PSTR(S_FMT " %i/3"), GET_TEXT(MSG_PROBING_MESH), int(i));
        #endif

        // Retain the last probe position
        probePos = points[i];
        measured_z = faux ? 0.001 * random(-100, 101) : probe_at_point(probePos, raise_after, verbose_level);
        if (isnan(measured_z)) {
          set_bed_leveling_enabled(abl_should_enable);
          break;
        }
        points[i].z = measured_z;
      }

      if (!dryrun && !isnan(measured_z)) {
=======
      LOOP_L_N(i, 3) {
        if (abl.verbose_level) SERIAL_ECHOLNPAIR("Probing point ", i + 1, "/3.");
        TERN_(HAS_STATUS_MESSAGE, ui.status_printf_P(0, PSTR(S_FMT " %i/3"), GET_TEXT(MSG_PROBING_MESH), int(i + 1)));

        // Retain the last probe position
        abl.probePos = points[i];
        abl.measured_z = faux ? 0.001 * random(-100, 101) : probe.probe_at_point(abl.probePos, raise_after, abl.verbose_level);
        if (isnan(abl.measured_z)) {
          set_bed_leveling_enabled(abl.reenable);
          break;
        }
        points[i].z = abl.measured_z;
      }

      if (!abl.dryrun && !isnan(abl.measured_z)) {
>>>>>>> mcu_ctrl
        vector_3 planeNormal = vector_3::cross(points[0] - points[1], points[2] - points[1]).get_normal();
        if (planeNormal.z < 0) planeNormal *= -1;
        planner.bed_level_matrix = matrix_3x3::create_look_at(planeNormal);

        // Can't re-enable (on error) until the new grid is written
<<<<<<< HEAD
        abl_should_enable = false;
=======
        abl.reenable = false;
>>>>>>> mcu_ctrl
      }

    #endif // AUTO_BED_LEVELING_3POINT

<<<<<<< HEAD
    #if HAS_DISPLAY
      ui.reset_status();
    #endif

    // Stow the probe. No raise for FIX_MOUNTED_PROBE.
    if (STOW_PROBE()) {
      set_bed_leveling_enabled(abl_should_enable);
      measured_z = NAN;
    }
  }
  #endif // !PROBE_MANUALLY

=======
    TERN_(HAS_STATUS_MESSAGE, ui.reset_status());
    SERIAL_ECHO_START();
    // Stow the probe. No raise for FIX_MOUNTED_PROBE.
    if (probe.stow()) {
      set_bed_leveling_enabled(abl.reenable);
      abl.measured_z = NAN;
    }
  }
  #endif // !PROBE_MANUALLY
>>>>>>> mcu_ctrl
  //
  // G29 Finishing Code
  //
  // Unless this is a dry run, auto bed leveling will
  // definitely be enabled after this point.
  //
  // If code above wants to continue leveling, it should
  // return or loop before this point.
  //

  if (DEBUGGING(LEVELING)) DEBUG_POS("> probing complete", current_position);

  #if ENABLED(PROBE_MANUALLY)
    g29_in_progress = false;
<<<<<<< HEAD
    #if ENABLED(LCD_BED_LEVELING)
      ui.wait_for_bl_move = false;
    #endif
  #endif

  // Calculate leveling, print reports, correct the position
  if (!isnan(measured_z)) {
    #if ENABLED(AUTO_BED_LEVELING_BILINEAR)

      if (!dryrun) extrapolate_unprobed_bed_level();
      print_bilinear_leveling_grid();

      #ifdef RTS_AVAILABLE
        if(3 == waitway)
        {
          waitway = 0;
        }
      #endif

      settings.save();
      refresh_bed_level();

      #if ENABLED(ABL_BILINEAR_SUBDIVISION)
        print_bilinear_leveling_grid_virt();
      #endif
=======
    TERN_(LCD_BED_LEVELING, ui.wait_for_move = false);
  #endif
  // Calculate leveling, print reports, correct the position
  if (!isnan(abl.measured_z)) {
    #if ENABLED(AUTO_BED_LEVELING_BILINEAR)

      if (!abl.dryrun) extrapolate_unprobed_bed_level();

      print_bilinear_leveling_grid();

      TERN_(DWIN_CREALITY_SERMOON_V2, gLcdSermoonV2UI.LevelingCompleted());
      print_bilinear_leveling_grid();
      refresh_bed_level();

      TERN_(ABL_BILINEAR_SUBDIVISION, print_bilinear_leveling_grid_virt());
>>>>>>> mcu_ctrl

    #elif ENABLED(AUTO_BED_LEVELING_LINEAR)

      // For LINEAR leveling calculate matrix, print reports, correct the position

      /**
       * solve the plane equation ax + by + d = z
       * A is the matrix with rows [x y 1] for all the probed points
       * B is the vector of the Z positions
       * the normal vector to the plane is formed by the coefficients of the
       * plane equation in the standard form, which is Vx*x+Vy*y+Vz*z+d = 0
       * so Vx = -a Vy = -b Vz = 1 (we want the vector facing towards positive Z
       */
      struct { float a, b, d; } plane_equation_coefficients;

      finish_incremental_LSF(&lsf_results);
      plane_equation_coefficients.a = -lsf_results.A;  // We should be able to eliminate the '-' on these three lines and down below
      plane_equation_coefficients.b = -lsf_results.B;  // but that is not yet tested.
      plane_equation_coefficients.d = -lsf_results.D;

<<<<<<< HEAD
      mean /= abl_points;

      if (verbose_level) {
        SERIAL_ECHOPAIR_F("Eqn coefficients: a: ", plane_equation_coefficients.a, 8);
        SERIAL_ECHOPAIR_F(" b: ", plane_equation_coefficients.b, 8);
        SERIAL_ECHOPAIR_F(" d: ", plane_equation_coefficients.d, 8);
        if (verbose_level > 2)
          SERIAL_ECHOPAIR_F("\nMean of sampled points: ", mean, 8);
=======
      abl.mean /= abl.abl_points;

      if (abl.verbose_level) {
        SERIAL_ECHOPAIR_F("Eqn coefficients: a: ", plane_equation_coefficients.a, 8);
        SERIAL_ECHOPAIR_F(" b: ", plane_equation_coefficients.b, 8);
        SERIAL_ECHOPAIR_F(" d: ", plane_equation_coefficients.d, 8);
        if (abl.verbose_level > 2)
          SERIAL_ECHOPAIR_F("\nMean of sampled points: ", abl.mean, 8);
>>>>>>> mcu_ctrl
        SERIAL_EOL();
      }

      // Create the matrix but don't correct the position yet
<<<<<<< HEAD
      if (!dryrun)
=======
      if (!abl.dryrun)
>>>>>>> mcu_ctrl
        planner.bed_level_matrix = matrix_3x3::create_look_at(
          vector_3(-plane_equation_coefficients.a, -plane_equation_coefficients.b, 1)    // We can eliminate the '-' here and up above
        );

      // Show the Topography map if enabled
<<<<<<< HEAD
      if (do_topography_map) {
=======
      if (abl.topography_map) {
>>>>>>> mcu_ctrl

        float min_diff = 999;

        auto print_topo_map = [&](PGM_P const title, const bool get_min) {
<<<<<<< HEAD
          serialprintPGM(title);
          for (int8_t yy = abl_grid_points.y - 1; yy >= 0; yy--) {
            for (uint8_t xx = 0; xx < abl_grid_points.x; xx++) {
              const int ind = indexIntoAB[xx][yy];
              xyz_float_t tmp = { eqnAMatrix[ind + 0 * abl_points],
                                  eqnAMatrix[ind + 1 * abl_points], 0 };
              apply_rotation_xyz(planner.bed_level_matrix, tmp);
              if (get_min) NOMORE(min_diff, eqnBVector[ind] - tmp.z);
              const float subval = get_min ? mean : tmp.z + min_diff,
                            diff = eqnBVector[ind] - subval;
=======
          SERIAL_ECHOPGM_P(title);
          for (int8_t yy = abl.grid_points.y - 1; yy >= 0; yy--) {
            LOOP_L_N(xx, abl.grid_points.x) {
              const int ind = abl.indexIntoAB[xx][yy];
              xyz_float_t tmp = { abl.eqnAMatrix[ind + 0 * abl.abl_points],
                                  abl.eqnAMatrix[ind + 1 * abl.abl_points], 0 };
              planner.bed_level_matrix.apply_rotation_xyz(tmp);
              if (get_min) NOMORE(min_diff, abl.eqnBVector[ind] - tmp.z);
              const float subval = get_min ? abl.mean : tmp.z + min_diff,
                            diff = abl.eqnBVector[ind] - subval;
>>>>>>> mcu_ctrl
              SERIAL_CHAR(' '); if (diff >= 0.0) SERIAL_CHAR('+');   // Include + for column alignment
              SERIAL_ECHO_F(diff, 5);
            } // xx
            SERIAL_EOL();
          } // yy
          SERIAL_EOL();
        };

        print_topo_map(PSTR("\nBed Height Topography:\n"
                               "   +--- BACK --+\n"
                               "   |           |\n"
                               " L |    (+)    | R\n"
                               " E |           | I\n"
                               " F | (-) N (+) | G\n"
                               " T |           | H\n"
                               "   |    (-)    | T\n"
                               "   |           |\n"
                               "   O-- FRONT --+\n"
                               " (0,0)\n"), true);
<<<<<<< HEAD
        if (verbose_level > 3)
          print_topo_map(PSTR("\nCorrected Bed Height vs. Bed Topology:\n"), false);

      } //do_topography_map
=======
        if (abl.verbose_level > 3)
          print_topo_map(PSTR("\nCorrected Bed Height vs. Bed Topology:\n"), false);

      } // abl.topography_map
>>>>>>> mcu_ctrl

    #endif // AUTO_BED_LEVELING_LINEAR

    #if ABL_PLANAR

      // For LINEAR and 3POINT leveling correct the current position

<<<<<<< HEAD
      if (verbose_level > 0)
        planner.bed_level_matrix.debug(PSTR("\n\nBed Level Correction Matrix:"));

      if (!dryrun) {
=======
      if (abl.verbose_level > 0)
        planner.bed_level_matrix.debug(PSTR("\n\nBed Level Correction Matrix:"));

      if (!abl.dryrun) {
>>>>>>> mcu_ctrl
        //
        // Correct the current XYZ position based on the tilted plane.
        //

        if (DEBUGGING(LEVELING)) DEBUG_POS("G29 uncorrected XYZ", current_position);

        xyze_pos_t converted = current_position;
        planner.force_unapply_leveling(converted); // use conversion machinery

        // Use the last measured distance to the bed, if possible
<<<<<<< HEAD
        if ( NEAR(current_position.x, probePos.x - probe_offset.x)
          && NEAR(current_position.y, probePos.y - probe_offset.y)
        ) {
          const float simple_z = current_position.z - measured_z;
=======
        if ( NEAR(current_position.x, abl.probePos.x - probe.offset_xy.x)
          && NEAR(current_position.y, abl.probePos.y - probe.offset_xy.y)
        ) {
          const float simple_z = current_position.z - abl.measured_z;
>>>>>>> mcu_ctrl
          if (DEBUGGING(LEVELING)) DEBUG_ECHOLNPAIR("Probed Z", simple_z, "  Matrix Z", converted.z, "  Discrepancy ", simple_z - converted.z);
          converted.z = simple_z;
        }

        // The rotated XY and corrected Z are now current_position
        current_position = converted;

        if (DEBUGGING(LEVELING)) DEBUG_POS("G29 corrected XYZ", current_position);
      }

    #elif ENABLED(AUTO_BED_LEVELING_BILINEAR)

<<<<<<< HEAD
      if (!dryrun) {
=======
      if (!abl.dryrun) {
>>>>>>> mcu_ctrl
        if (DEBUGGING(LEVELING)) DEBUG_ECHOLNPAIR("G29 uncorrected Z:", current_position.z);

        // Unapply the offset because it is going to be immediately applied
        // and cause compensation movement in Z
<<<<<<< HEAD
        current_position.z -= bilinear_z_offset(current_position);
=======
        const float fade_scaling_factor = TERN(ENABLE_LEVELING_FADE_HEIGHT, planner.fade_scaling_factor_for_z(current_position.z), 1);
        current_position.z -= fade_scaling_factor * bilinear_z_offset(current_position);
>>>>>>> mcu_ctrl

        if (DEBUGGING(LEVELING)) DEBUG_ECHOLNPAIR(" corrected Z:", current_position.z);
      }

    #endif // ABL_PLANAR

    // Auto Bed Leveling is complete! Enable if possible.
<<<<<<< HEAD
    planner.leveling_active = dryrun ? abl_should_enable : true;
  } // !isnan(measured_z)
=======
    planner.leveling_active = !abl.dryrun || abl.reenable;
  } // !isnan(abl.measured_z)
>>>>>>> mcu_ctrl

  // Restore state after probing
  if (!faux) restore_feedrate_and_scaling();

<<<<<<< HEAD
  if (DEBUGGING(LEVELING)) DEBUG_ECHOLNPGM("<<< G29");

  if (planner.leveling_active)
    sync_plan_position();

  #if HAS_BED_PROBE && defined(Z_AFTER_PROBING)
    move_z_after_probing();
=======
  // Sync the planner from the current_position
  if (planner.leveling_active) sync_plan_position();

  #if HAS_BED_PROBE
    probe.move_z_after_probing();
>>>>>>> mcu_ctrl
  #endif

  #ifdef Z_PROBE_END_SCRIPT
    if (DEBUGGING(LEVELING)) DEBUG_ECHOLNPAIR("Z Probe End Script: ", Z_PROBE_END_SCRIPT);
    planner.synchronize();
    process_subcommands_now_P(PSTR(Z_PROBE_END_SCRIPT));
  #endif

<<<<<<< HEAD
  #ifdef DWIN_LCDDISPLAY

    if(checkkey == Leveing) Goto_ProcessFrame();
    
=======
  #if ENABLED(DWIN_CREALITY_LCD)
    DWIN_CompletedLeveling();
>>>>>>> mcu_ctrl
  #endif

  report_current_position();

<<<<<<< HEAD
  do_blocking_move_to_xy(safe_homing_xy);

  #ifdef RTS_AVAILABLE
    WRITE(COM_PIN, 0);
    delay(200);
    WRITE(COM_PIN, 1);
    delay(200);
    G29_flag = false;
  #endif

  G29_RETURN(isnan(measured_z));
=======
  TERN_(FULL_REPORT_TO_HOST_FEATURE, set_and_report_grblstate(M_IDLE));

  G29_RETURN(isnan(abl.measured_z));

>>>>>>> mcu_ctrl
}

#endif // HAS_ABL_NOT_UBL
