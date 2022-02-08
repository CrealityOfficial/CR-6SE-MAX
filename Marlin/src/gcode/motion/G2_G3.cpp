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

#if ENABLED(ARC_SUPPORT)

#include "../gcode.h"
#include "../../module/motion.h"
#include "../../module/planner.h"
#include "../../module/temperature.h"

#if ENABLED(DELTA)
  #include "../../module/delta.h"
#elif ENABLED(SCARA)
  #include "../../module/scara.h"
#endif

#if N_ARC_CORRECTION < 1
  #undef N_ARC_CORRECTION
  #define N_ARC_CORRECTION 1
#endif

/**
<<<<<<< HEAD
 * Plan an arc in 2 dimensions
 *
 * The arc is approximated by generating many small linear segments.
 * The length of each segment is configured in MM_PER_ARC_SEGMENT (Default 1mm)
 * Arcs should only be made relatively large (over 5mm), as larger arcs with
 * larger segments will tend to be more efficient. Your slicer should have
 * options for G2/G3 arc generation. In future these options may be GCode tunable.
=======
 * Plan an arc in 2 dimensions, with optional linear motion in a 3rd dimension
 *
 * The arc is traced by generating many small linear segments, as configured by
 * MM_PER_ARC_SEGMENT (Default 1mm). In the future we hope more slicers will include
 * an option to generate G2/G3 arcs for curved surfaces, as this will allow faster
 * boards to produce much smoother curved surfaces.
>>>>>>> mcu_ctrl
 */
void plan_arc(
  const xyze_pos_t &cart,   // Destination position
  const ab_float_t &offset, // Center of rotation relative to current_position
<<<<<<< HEAD
  const uint8_t clockwise   // Clockwise?
=======
  const bool clockwise,     // Clockwise?
  const uint8_t circles     // Take the scenic route
>>>>>>> mcu_ctrl
) {
  #if ENABLED(CNC_WORKSPACE_PLANES)
    AxisEnum p_axis, q_axis, l_axis;
    switch (gcode.workspace_plane) {
      default:
      case GcodeSuite::PLANE_XY: p_axis = X_AXIS; q_axis = Y_AXIS; l_axis = Z_AXIS; break;
      case GcodeSuite::PLANE_YZ: p_axis = Y_AXIS; q_axis = Z_AXIS; l_axis = X_AXIS; break;
      case GcodeSuite::PLANE_ZX: p_axis = Z_AXIS; q_axis = X_AXIS; l_axis = Y_AXIS; break;
    }
  #else
    constexpr AxisEnum p_axis = X_AXIS, q_axis = Y_AXIS, l_axis = Z_AXIS;
  #endif

  // Radius vector from center to current location
  ab_float_t rvec = -offset;

  const float radius = HYPOT(rvec.a, rvec.b),
<<<<<<< HEAD
              #if ENABLED(AUTO_BED_LEVELING_UBL)
                start_L  = current_position[l_axis],
              #endif
=======
>>>>>>> mcu_ctrl
              center_P = current_position[p_axis] - rvec.a,
              center_Q = current_position[q_axis] - rvec.b,
              rt_X = cart[p_axis] - center_P,
              rt_Y = cart[q_axis] - center_Q,
<<<<<<< HEAD
              linear_travel = cart[l_axis] - current_position[l_axis],
              extruder_travel = cart.e - current_position.e;

  // CCW angle of rotation between position and target from the circle center. Only one atan2() trig computation required.
  float angular_travel = ATAN2(rvec.a * rt_Y - rvec.b * rt_X, rvec.a * rt_X + rvec.b * rt_Y);
  if (angular_travel < 0) angular_travel += RADIANS(360);
  #ifdef MIN_ARC_SEGMENTS
    uint16_t min_segments = CEIL((MIN_ARC_SEGMENTS) * (angular_travel / RADIANS(360)));
    NOLESS(min_segments, 1U);
  #else
    constexpr uint16_t min_segments = 1;
  #endif
  if (clockwise) angular_travel -= RADIANS(360);

  // Make a circle if the angular rotation is 0 and the target is current position
  if (angular_travel == 0 && current_position[p_axis] == cart[p_axis] && current_position[q_axis] == cart[q_axis]) {
    angular_travel = RADIANS(360);
    #ifdef MIN_ARC_SEGMENTS
      min_segments = MIN_ARC_SEGMENTS;
    #endif
  }

=======
              start_L = current_position[l_axis];

  #ifdef MIN_ARC_SEGMENTS
    uint16_t min_segments = MIN_ARC_SEGMENTS;
  #else
    constexpr uint16_t min_segments = 1;
  #endif

  // Angle of rotation between position and target from the circle center.
  float angular_travel;

  // Do a full circle if starting and ending positions are "identical"
  if (NEAR(current_position[p_axis], cart[p_axis]) && NEAR(current_position[q_axis], cart[q_axis])) {
    // Preserve direction for circles
    angular_travel = clockwise ? -RADIANS(360) : RADIANS(360);
  }
  else {
    // Calculate the angle
    angular_travel = ATAN2(rvec.a * rt_Y - rvec.b * rt_X, rvec.a * rt_X + rvec.b * rt_Y);

    // Angular travel too small to detect? Just return.
    if (!angular_travel) return;

    // Make sure angular travel over 180 degrees goes the other way around.
    switch (((angular_travel < 0) << 1) | clockwise) {
      case 1: angular_travel -= RADIANS(360); break; // Positive but CW? Reverse direction.
      case 2: angular_travel += RADIANS(360); break; // Negative but CCW? Reverse direction.
    }

    #ifdef MIN_ARC_SEGMENTS
      min_segments = CEIL(min_segments * ABS(angular_travel) / RADIANS(360));
      NOLESS(min_segments, 1U);
    #endif
  }

  float linear_travel = cart[l_axis] - start_L,
        extruder_travel = cart.e - current_position.e;

  // If circling around...
  if (ENABLED(ARC_P_CIRCLES) && circles) {
    const float total_angular = angular_travel + circles * RADIANS(360),  // Total rotation with all circles and remainder
              part_per_circle = RADIANS(360) / total_angular,             // Each circle's part of the total
                 l_per_circle = linear_travel * part_per_circle,          // L movement per circle
                 e_per_circle = extruder_travel * part_per_circle;        // E movement per circle
    xyze_pos_t temp_position = current_position;                          // for plan_arc to compare to current_position
    for (uint16_t n = circles; n--;) {
      temp_position.e += e_per_circle;                                    // Destination E axis
      temp_position[l_axis] += l_per_circle;                              // Destination L axis
      plan_arc(temp_position, offset, clockwise, 0);                      // Plan a single whole circle
    }
    linear_travel = cart[l_axis] - current_position[l_axis];
    extruder_travel = cart.e - current_position.e;
  }

>>>>>>> mcu_ctrl
  const float flat_mm = radius * angular_travel,
              mm_of_travel = linear_travel ? HYPOT(flat_mm, linear_travel) : ABS(flat_mm);
  if (mm_of_travel < 0.001f) return;

<<<<<<< HEAD
  uint16_t segments = FLOOR(mm_of_travel / (MM_PER_ARC_SEGMENT));
  NOLESS(segments, min_segments);
=======
  const feedRate_t scaled_fr_mm_s = MMS_SCALED(feedrate_mm_s);

  // Start with a nominal segment length
  float seg_length = (
    #ifdef ARC_SEGMENTS_PER_R
      constrain(MM_PER_ARC_SEGMENT * radius, MM_PER_ARC_SEGMENT, ARC_SEGMENTS_PER_R)
    #elif ARC_SEGMENTS_PER_SEC
      _MAX(scaled_fr_mm_s * RECIPROCAL(ARC_SEGMENTS_PER_SEC), MM_PER_ARC_SEGMENT)
    #else
      MM_PER_ARC_SEGMENT
    #endif
  );
  // Divide total travel by nominal segment length
  uint16_t segments = FLOOR(mm_of_travel / seg_length);
  NOLESS(segments, min_segments);         // At least some segments
  seg_length = mm_of_travel / segments;
>>>>>>> mcu_ctrl

  /**
   * Vector rotation by transformation matrix: r is the original vector, r_T is the rotated vector,
   * and phi is the angle of rotation. Based on the solution approach by Jens Geisler.
   *     r_T = [cos(phi) -sin(phi);
   *            sin(phi)  cos(phi)] * r ;
   *
   * For arc generation, the center of the circle is the axis of rotation and the radius vector is
   * defined from the circle center to the initial position. Each line segment is formed by successive
   * vector rotations. This requires only two cos() and sin() computations to form the rotation
   * matrix for the duration of the entire arc. Error may accumulate from numerical round-off, since
   * all double numbers are single precision on the Arduino. (True double precision will not have
   * round off issues for CNC applications.) Single precision error can accumulate to be greater than
   * tool precision in some cases. Therefore, arc path correction is implemented.
   *
   * Small angle approximation may be used to reduce computation overhead further. This approximation
   * holds for everything, but very small circles and large MM_PER_ARC_SEGMENT values. In other words,
   * theta_per_segment would need to be greater than 0.1 rad and N_ARC_CORRECTION would need to be large
   * to cause an appreciable drift error. N_ARC_CORRECTION~=25 is more than small enough to correct for
   * numerical drift error. N_ARC_CORRECTION may be on the order a hundred(s) before error becomes an
   * issue for CNC machines with the single precision Arduino calculations.
   *
   * This approximation also allows plan_arc to immediately insert a line segment into the planner
   * without the initial overhead of computing cos() or sin(). By the time the arc needs to be applied
   * a correction, the planner should have caught up to the lag caused by the initial plan_arc overhead.
   * This is important when there are successive arc motions.
   */
  // Vector rotation matrix values
  xyze_pos_t raw;
  const float theta_per_segment = angular_travel / segments,
              linear_per_segment = linear_travel / segments,
              extruder_per_segment = extruder_travel / segments,
<<<<<<< HEAD
              sin_T = theta_per_segment,
              cos_T = 1 - 0.5f * sq(theta_per_segment); // Small angle approximation
=======
              sq_theta_per_segment = sq(theta_per_segment),
              sin_T = theta_per_segment - sq_theta_per_segment * theta_per_segment / 6,
              cos_T = 1 - 0.5f * sq_theta_per_segment; // Small angle approximation
>>>>>>> mcu_ctrl

  // Initialize the linear axis
  raw[l_axis] = current_position[l_axis];

  // Initialize the extruder axis
  raw.e = current_position.e;

<<<<<<< HEAD
  const feedRate_t scaled_fr_mm_s = MMS_SCALED(feedrate_mm_s);

  #if ENABLED(SCARA_FEEDRATE_SCALING)
    const float inv_duration = scaled_fr_mm_s / MM_PER_ARC_SEGMENT;
=======
  #if ENABLED(SCARA_FEEDRATE_SCALING)
    const float inv_duration = scaled_fr_mm_s / seg_length;
>>>>>>> mcu_ctrl
  #endif

  millis_t next_idle_ms = millis() + 200UL;

  #if N_ARC_CORRECTION > 1
    int8_t arc_recalc_count = N_ARC_CORRECTION;
  #endif

  for (uint16_t i = 1; i < segments; i++) { // Iterate (segments-1) times

    thermalManager.manage_heater();
    if (ELAPSED(millis(), next_idle_ms)) {
      next_idle_ms = millis() + 200UL;
      idle();
    }

    #if N_ARC_CORRECTION > 1
      if (--arc_recalc_count) {
        // Apply vector rotation matrix to previous rvec.a / 1
        const float r_new_Y = rvec.a * sin_T + rvec.b * cos_T;
        rvec.a = rvec.a * cos_T - rvec.b * sin_T;
        rvec.b = r_new_Y;
      }
      else
    #endif
    {
      #if N_ARC_CORRECTION > 1
        arc_recalc_count = N_ARC_CORRECTION;
      #endif

      // Arc correction to radius vector. Computed only every N_ARC_CORRECTION increments.
      // Compute exact location by applying transformation matrix from initial radius vector(=-offset).
      // To reduce stuttering, the sin and cos could be computed at different times.
      // For now, compute both at the same time.
      const float cos_Ti = cos(i * theta_per_segment), sin_Ti = sin(i * theta_per_segment);
      rvec.a = -offset[0] * cos_Ti + offset[1] * sin_Ti;
      rvec.b = -offset[0] * sin_Ti - offset[1] * cos_Ti;
    }

    // Update raw location
    raw[p_axis] = center_P + rvec.a;
    raw[q_axis] = center_Q + rvec.b;
    #if ENABLED(AUTO_BED_LEVELING_UBL)
      raw[l_axis] = start_L;
      UNUSED(linear_per_segment);
    #else
      raw[l_axis] += linear_per_segment;
    #endif
    raw.e += extruder_per_segment;

    apply_motion_limits(raw);

    #if HAS_LEVELING && !PLANNER_LEVELING
      planner.apply_leveling(raw);
    #endif

<<<<<<< HEAD
    if (!planner.buffer_line(raw, scaled_fr_mm_s, active_extruder, MM_PER_ARC_SEGMENT
      #if ENABLED(SCARA_FEEDRATE_SCALING)
        , inv_duration
      #endif
    ))
      break;
=======
    if (!planner.buffer_line(raw, scaled_fr_mm_s, active_extruder, 0
      OPTARG(SCARA_FEEDRATE_SCALING, inv_duration)
    )) break;
>>>>>>> mcu_ctrl
  }

  // Ensure last segment arrives at target location.
  raw = cart;
<<<<<<< HEAD
  #if ENABLED(AUTO_BED_LEVELING_UBL)
    raw[l_axis] = start_L;
  #endif
=======
  TERN_(AUTO_BED_LEVELING_UBL, raw[l_axis] = start_L);
>>>>>>> mcu_ctrl

  apply_motion_limits(raw);

  #if HAS_LEVELING && !PLANNER_LEVELING
    planner.apply_leveling(raw);
  #endif

<<<<<<< HEAD
  planner.buffer_line(raw, scaled_fr_mm_s, active_extruder, MM_PER_ARC_SEGMENT
    #if ENABLED(SCARA_FEEDRATE_SCALING)
      , inv_duration
    #endif
  );

  #if ENABLED(AUTO_BED_LEVELING_UBL)
    raw[l_axis] = start_L;
  #endif
  current_position = raw;
=======
  planner.buffer_line(raw, scaled_fr_mm_s, active_extruder, 0
    OPTARG(SCARA_FEEDRATE_SCALING, inv_duration)
  );

  TERN_(AUTO_BED_LEVELING_UBL, raw[l_axis] = start_L);
  current_position = raw;

>>>>>>> mcu_ctrl
} // plan_arc

/**
 * G2: Clockwise Arc
 * G3: Counterclockwise Arc
 *
 * This command has two forms: IJ-form (JK, KI) and R-form.
 *
 *  - Depending on the current Workspace Plane orientation,
 *    use parameters IJ/JK/KI to specify the XY/YZ/ZX offsets.
 *    At least one of the IJ/JK/KI parameters is required.
 *    XY/YZ/ZX can be omitted to do a complete circle.
 *    The given XY/YZ/ZX is not error-checked. The arc ends
 *    based on the angle of the destination.
 *    Mixing IJ/JK/KI with R will throw an error.
 *
 *  - R specifies the radius. X or Y (Y or Z / Z or X) is required.
<<<<<<< HEAD
 *    Omitting both XY/YZ/ZX will throw an error.
 *    XY/YZ/ZX must differ from the current XY/YZ/ZX.
 *    Mixing R with IJ/JK/KI will throw an error.
 *
 *  - P specifies the number of full circles to do
 *    before the specified arc move.
=======
 *      Omitting both XY/YZ/ZX will throw an error.
 *      XY/YZ/ZX must differ from the current XY/YZ/ZX.
 *      Mixing R with IJ/JK/KI will throw an error.
 *
 *  - P specifies the number of full circles to do
 *      before the specified arc move.
>>>>>>> mcu_ctrl
 *
 *  Examples:
 *
 *    G2 I10           ; CW circle centered at X+10
 *    G3 X20 Y12 R14   ; CCW circle with r=14 ending at X20 Y12
 */
void GcodeSuite::G2_G3(const bool clockwise) {
  if (MOTION_CONDITIONS) {

<<<<<<< HEAD
=======
    TERN_(FULL_REPORT_TO_HOST_FEATURE, set_and_report_grblstate(M_RUNNING));

>>>>>>> mcu_ctrl
    #if ENABLED(SF_ARC_FIX)
      const bool relative_mode_backup = relative_mode;
      relative_mode = true;
    #endif

<<<<<<< HEAD
    get_destination_from_command();

    #if ENABLED(SF_ARC_FIX)
      relative_mode = relative_mode_backup;
    #endif
=======
    get_destination_from_command();   // Get X Y Z E F (and set cutter power)

    TERN_(SF_ARC_FIX, relative_mode = relative_mode_backup);
>>>>>>> mcu_ctrl

    ab_float_t arc_offset = { 0, 0 };
    if (parser.seenval('R')) {
      const float r = parser.value_linear_units();
      if (r) {
        const xy_pos_t p1 = current_position, p2 = destination;
        if (p1 != p2) {
          const xy_pos_t d2 = (p2 - p1) * 0.5f;          // XY vector to midpoint of move from current
          const float e = clockwise ^ (r < 0) ? -1 : 1,  // clockwise -1/1, counterclockwise 1/-1
                      len = d2.magnitude(),              // Distance to mid-point of move from current
                      h2 = (r - len) * (r + len),        // factored to reduce rounding error
                      h = (h2 >= 0) ? SQRT(h2) : 0.0f;   // Distance to the arc pivot-point from midpoint
          const xy_pos_t s = { -d2.y, d2.x };            // Perpendicular bisector. (Divide by len for unit vector.)
          arc_offset = d2 + s / len * e * h;             // The calculated offset (mid-point if |r| <= len)
        }
      }
    }
    else {
      #if ENABLED(CNC_WORKSPACE_PLANES)
        char achar, bchar;
        switch (gcode.workspace_plane) {
          default:
          case GcodeSuite::PLANE_XY: achar = 'I'; bchar = 'J'; break;
          case GcodeSuite::PLANE_YZ: achar = 'J'; bchar = 'K'; break;
          case GcodeSuite::PLANE_ZX: achar = 'K'; bchar = 'I'; break;
        }
      #else
        constexpr char achar = 'I', bchar = 'J';
      #endif
      if (parser.seenval(achar)) arc_offset.a = parser.value_linear_units();
      if (parser.seenval(bchar)) arc_offset.b = parser.value_linear_units();
    }

    if (arc_offset) {

      #if ENABLED(ARC_P_CIRCLES)
        // P indicates number of circles to do
<<<<<<< HEAD
        int8_t circles_to_do = parser.byteval('P');
        if (!WITHIN(circles_to_do, 0, 100))
          SERIAL_ERROR_MSG(MSG_ERR_ARC_ARGS);

        while (circles_to_do--)
          plan_arc(current_position, arc_offset, clockwise);
      #endif

      // Send the arc to the planner
      plan_arc(destination, arc_offset, clockwise);
      reset_stepper_timeout();
    }
    else
      SERIAL_ERROR_MSG(MSG_ERR_ARC_ARGS);
=======
        const int8_t circles_to_do = parser.byteval('P');
        if (!WITHIN(circles_to_do, 0, 100))
          SERIAL_ERROR_MSG(STR_ERR_ARC_ARGS);
      #else
        constexpr uint8_t circles_to_do = 0;
      #endif

      // Send the arc to the planner
      plan_arc(destination, arc_offset, clockwise, circles_to_do);
      reset_stepper_timeout();
    }
    else
      SERIAL_ERROR_MSG(STR_ERR_ARC_ARGS);

    TERN_(FULL_REPORT_TO_HOST_FEATURE, set_and_report_grblstate(M_IDLE));
>>>>>>> mcu_ctrl
  }
}

#endif // ARC_SUPPORT
