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

//
// Motion Menu
//

#include "../../inc/MarlinConfigPre.h"

#if HAS_LCD_MENU

<<<<<<< HEAD
#include "menu.h"
#include "menu_addon.h"

#include "../../module/motion.h"
=======
#include "menu_item.h"
#include "menu_addon.h"

#include "../../module/motion.h"
#include "../../gcode/parser.h" // for inch support
>>>>>>> mcu_ctrl

#if ENABLED(DELTA)
  #include "../../module/delta.h"
#endif

#if ENABLED(PREVENT_COLD_EXTRUSION)
  #include "../../module/temperature.h"
#endif

#if HAS_LEVELING
  #include "../../module/planner.h"
  #include "../../feature/bedlevel/bedlevel.h"
#endif

<<<<<<< HEAD
extern millis_t manual_move_start_time;
extern int8_t manual_move_axis;
#if ENABLED(MANUAL_E_MOVES_RELATIVE)
  float manual_move_e_origin = 0;
#endif
#if IS_KINEMATIC
  extern float manual_move_offset;
#endif

//
// Tell ui.update() to start a move to current_position" after a short delay.
//
inline void manual_move_to_current(AxisEnum axis
  #if E_MANUAL > 1
    , const int8_t eindex=-1
  #endif
) {
  #if E_MANUAL > 1
    if (axis == E_AXIS) ui.manual_move_e_index = eindex >= 0 ? eindex : active_extruder;
  #endif
  manual_move_start_time = millis() + (move_menu_scale < 0.99f ? 0UL : 250UL); // delay for bigger moves
  manual_move_axis = (int8_t)axis;
}
=======
#if ENABLED(MANUAL_E_MOVES_RELATIVE)
  float manual_move_e_origin = 0;
#endif
>>>>>>> mcu_ctrl

//
// "Motion" > "Move Axis" submenu
//

static void _lcd_move_xyz(PGM_P const name, const AxisEnum axis) {
  if (ui.use_click()) return ui.goto_previous_screen_no_defer();
<<<<<<< HEAD
  if (ui.encoderPosition && !ui.processing_manual_move) {

    // Start with no limits to movement
    float min = current_position[axis] - 1000,
          max = current_position[axis] + 1000;

    // Limit to software endstops, if enabled
    #if HAS_SOFTWARE_ENDSTOPS
      if (soft_endstops_enabled) switch (axis) {
        case X_AXIS:
          #if ENABLED(MIN_SOFTWARE_ENDSTOP_X)
            min = soft_endstop.min.x;
          #endif
          #if ENABLED(MAX_SOFTWARE_ENDSTOP_X)
            max = soft_endstop.max.x;
          #endif
          break;
        case Y_AXIS:
          #if ENABLED(MIN_SOFTWARE_ENDSTOP_Y)
            min = soft_endstop.min.y;
          #endif
          #if ENABLED(MAX_SOFTWARE_ENDSTOP_Y)
            max = soft_endstop.max.y;
          #endif
          break;
        case Z_AXIS:
          #if ENABLED(MIN_SOFTWARE_ENDSTOP_Z)
            min = soft_endstop.min.z;
          #endif
          #if ENABLED(MAX_SOFTWARE_ENDSTOP_Z)
            max = soft_endstop.max.z;
          #endif
        default: break;
      }
    #endif // HAS_SOFTWARE_ENDSTOPS
=======
  if (ui.encoderPosition && !ui.manual_move.processing) {
    // Get motion limit from software endstops, if any
    float min, max;
    soft_endstop.get_manual_axis_limits(axis, min, max);
>>>>>>> mcu_ctrl

    // Delta limits XY based on the current offset from center
    // This assumes the center is 0,0
    #if ENABLED(DELTA)
      if (axis != Z_AXIS) {
        max = SQRT(sq((float)(DELTA_PRINTABLE_RADIUS)) - sq(current_position[Y_AXIS - axis])); // (Y_AXIS - axis) == the other axis
        min = -max;
      }
    #endif

    // Get the new position
<<<<<<< HEAD
    const float diff = float(int32_t(ui.encoderPosition)) * move_menu_scale;
    #if IS_KINEMATIC
      manual_move_offset += diff;
      if (int32_t(ui.encoderPosition) < 0)
        NOLESS(manual_move_offset, min - current_position[axis]);
      else
        NOMORE(manual_move_offset, max - current_position[axis]);
    #else
      current_position[axis] += diff;
      if (int32_t(ui.encoderPosition) < 0)
        NOLESS(current_position[axis], min);
      else
        NOMORE(current_position[axis], max);
    #endif

    manual_move_to_current(axis);
=======
    const float diff = float(int32_t(ui.encoderPosition)) * ui.manual_move.menu_scale;
    (void)ui.manual_move.apply_diff(axis, diff, min, max);
    ui.manual_move.soon(axis);
>>>>>>> mcu_ctrl
    ui.refresh(LCDVIEW_REDRAW_NOW);
  }
  ui.encoderPosition = 0;
  if (ui.should_draw()) {
<<<<<<< HEAD
    const float pos = NATIVE_TO_LOGICAL(ui.processing_manual_move ? destination[axis] : current_position[axis]
      #if IS_KINEMATIC
        + manual_move_offset
      #endif
    , axis);
    MenuEditItemBase::draw_edit_screen(name, move_menu_scale >= 0.1f ? ftostr41sign(pos) : ftostr43sign(pos));
=======
    const float pos = ui.manual_move.axis_value(axis);
    if (parser.using_inch_units()) {
      const float imp_pos = LINEAR_UNIT(pos);
      MenuEditItemBase::draw_edit_screen(name, ftostr63(imp_pos));
    }
    else
      MenuEditItemBase::draw_edit_screen(name, ui.manual_move.menu_scale >= 0.1f ? ftostr41sign(pos) : ftostr63(pos));
>>>>>>> mcu_ctrl
  }
}
void lcd_move_x() { _lcd_move_xyz(GET_TEXT(MSG_MOVE_X), X_AXIS); }
void lcd_move_y() { _lcd_move_xyz(GET_TEXT(MSG_MOVE_Y), Y_AXIS); }
void lcd_move_z() { _lcd_move_xyz(GET_TEXT(MSG_MOVE_Z), Z_AXIS); }

#if E_MANUAL

<<<<<<< HEAD
  static void lcd_move_e(
    #if E_MANUAL > 1
      const int8_t eindex=-1
    #endif
  ) {
    if (ui.use_click()) return ui.goto_previous_screen_no_defer();
    if (ui.encoderPosition) {
      if (!ui.processing_manual_move) {
        const float diff = float(int32_t(ui.encoderPosition)) * move_menu_scale;
        #if IS_KINEMATIC
          manual_move_offset += diff;
        #else
          current_position.e += diff;
        #endif
        manual_move_to_current(E_AXIS
          #if E_MANUAL > 1
            , eindex
          #endif
        );
=======
  static void lcd_move_e(TERN_(MULTI_E_MANUAL, const int8_t eindex=active_extruder)) {
    if (ui.use_click()) return ui.goto_previous_screen_no_defer();
    if (ui.encoderPosition) {
      if (!ui.manual_move.processing) {
        const float diff = float(int32_t(ui.encoderPosition)) * ui.manual_move.menu_scale;
        TERN(IS_KINEMATIC, ui.manual_move.offset, current_position.e) += diff;
        ui.manual_move.soon(E_AXIS OPTARG(MULTI_E_MANUAL, eindex));
>>>>>>> mcu_ctrl
        ui.refresh(LCDVIEW_REDRAW_NOW);
      }
      ui.encoderPosition = 0;
    }
    if (ui.should_draw()) {
<<<<<<< HEAD
      #if E_MANUAL > 1
        MenuItemBase::init(eindex);
      #endif
      MenuEditItemBase::draw_edit_screen(
        GET_TEXT(
          #if E_MANUAL > 1
            MSG_MOVE_EN
          #else
            MSG_MOVE_E
          #endif
        ),
        ftostr41sign(current_position.e
          #if IS_KINEMATIC
            + manual_move_offset
          #endif
          #if ENABLED(MANUAL_E_MOVES_RELATIVE)
            - manual_move_e_origin
          #endif
=======
      TERN_(MULTI_E_MANUAL, MenuItemBase::init(eindex));
      MenuEditItemBase::draw_edit_screen(
        GET_TEXT(TERN(MULTI_E_MANUAL, MSG_MOVE_EN, MSG_MOVE_E)),
        ftostr41sign(current_position.e
          PLUS_TERN0(IS_KINEMATIC, ui.manual_move.offset)
          MINUS_TERN0(MANUAL_E_MOVES_RELATIVE, manual_move_e_origin)
>>>>>>> mcu_ctrl
        )
      );
    } // should_draw
  }

#endif // E_MANUAL

//
// "Motion" > "Move Xmm" > "Move XYZ" submenu
//

<<<<<<< HEAD
#ifndef SHORT_MANUAL_Z_MOVE
  #define SHORT_MANUAL_Z_MOVE 0.025
=======
#ifndef FINE_MANUAL_MOVE
  #define FINE_MANUAL_MOVE 0.025
>>>>>>> mcu_ctrl
#endif

screenFunc_t _manual_move_func_ptr;

<<<<<<< HEAD
void _goto_manual_move(const float scale) {
  ui.defer_status_screen();
  move_menu_scale = scale;
  ui.goto_screen(_manual_move_func_ptr);
}

void _menu_move_distance(const AxisEnum axis, const screenFunc_t func, const int8_t eindex=-1) {
=======
void _goto_manual_move(const_float_t scale) {
  ui.defer_status_screen();
  ui.manual_move.menu_scale = scale;
  ui.goto_screen(_manual_move_func_ptr);
}

void _menu_move_distance(const AxisEnum axis, const screenFunc_t func, const int8_t eindex=active_extruder) {
>>>>>>> mcu_ctrl
  _manual_move_func_ptr = func;
  START_MENU();
  if (LCD_HEIGHT >= 4) {
    switch (axis) {
<<<<<<< HEAD
      case X_AXIS: STATIC_ITEM(MSG_MOVE_X, SS_CENTER|SS_INVERT); break;
      case Y_AXIS: STATIC_ITEM(MSG_MOVE_Y, SS_CENTER|SS_INVERT); break;
      case Z_AXIS: STATIC_ITEM(MSG_MOVE_Z, SS_CENTER|SS_INVERT); break;
      default:
        #if ENABLED(MANUAL_E_MOVES_RELATIVE)
          manual_move_e_origin = current_position.e;
        #endif
        STATIC_ITEM(MSG_MOVE_E, SS_CENTER|SS_INVERT);
        break;
    }
  }
  #if ENABLED(PREVENT_COLD_EXTRUSION)
    if (axis == E_AXIS && thermalManager.tooColdToExtrude(eindex >= 0 ? eindex : active_extruder))
      BACK_ITEM(MSG_HOTEND_TOO_COLD);
    else
  #endif
  {
    BACK_ITEM(MSG_MOVE_AXIS);
    SUBMENU(MSG_MOVE_10MM, []{ _goto_manual_move(10);    });
    SUBMENU(MSG_MOVE_1MM,  []{ _goto_manual_move( 1);    });
    SUBMENU(MSG_MOVE_01MM, []{ _goto_manual_move( 0.1f); });
    if (axis == Z_AXIS && (SHORT_MANUAL_Z_MOVE) > 0.0f && (SHORT_MANUAL_Z_MOVE) < 0.1f) {
      extern const char NUL_STR[];
      SUBMENU_P(NUL_STR, []{ _goto_manual_move(float(SHORT_MANUAL_Z_MOVE)); });
      MENU_ITEM_ADDON_START(0);
        char tmp[20], numstr[10];
        // Determine digits needed right of decimal
        const uint8_t digs = !UNEAR_ZERO((SHORT_MANUAL_Z_MOVE) * 1000 - int((SHORT_MANUAL_Z_MOVE) * 1000)) ? 4 :
                             !UNEAR_ZERO((SHORT_MANUAL_Z_MOVE) *  100 - int((SHORT_MANUAL_Z_MOVE) *  100)) ? 3 : 2;
        sprintf_P(tmp, GET_TEXT(MSG_MOVE_Z_DIST), dtostrf(SHORT_MANUAL_Z_MOVE, 1, digs, numstr));
        lcd_put_u8str(tmp);
      MENU_ITEM_ADDON_END();
=======
      case X_AXIS: STATIC_ITEM(MSG_MOVE_X, SS_DEFAULT|SS_INVERT); break;
      case Y_AXIS: STATIC_ITEM(MSG_MOVE_Y, SS_DEFAULT|SS_INVERT); break;
      case Z_AXIS: STATIC_ITEM(MSG_MOVE_Z, SS_DEFAULT|SS_INVERT); break;
      default:
        TERN_(MANUAL_E_MOVES_RELATIVE, manual_move_e_origin = current_position.e);
        STATIC_ITEM(MSG_MOVE_E, SS_DEFAULT|SS_INVERT);
        break;
    }
  }

  BACK_ITEM(MSG_MOVE_AXIS);
  if (parser.using_inch_units()) {
    SUBMENU(MSG_MOVE_01IN,   []{ _goto_manual_move(IN_TO_MM(0.100f)); });
    SUBMENU(MSG_MOVE_001IN,  []{ _goto_manual_move(IN_TO_MM(0.010f)); });
    SUBMENU(MSG_MOVE_0001IN, []{ _goto_manual_move(IN_TO_MM(0.001f)); });
  }
  else {
    SUBMENU(MSG_MOVE_10MM, []{ _goto_manual_move(10);    });
    SUBMENU(MSG_MOVE_1MM,  []{ _goto_manual_move( 1);    });
    SUBMENU(MSG_MOVE_01MM, []{ _goto_manual_move( 0.1f); });
    if (axis == Z_AXIS && (FINE_MANUAL_MOVE) > 0.0f && (FINE_MANUAL_MOVE) < 0.1f) {
      // Determine digits needed right of decimal
      constexpr uint8_t digs = !UNEAR_ZERO((FINE_MANUAL_MOVE) * 1000 - int((FINE_MANUAL_MOVE) * 1000)) ? 4 :
                               !UNEAR_ZERO((FINE_MANUAL_MOVE) *  100 - int((FINE_MANUAL_MOVE) *  100)) ? 3 : 2;
      PGM_P const label = GET_TEXT(MSG_MOVE_N_MM);
      char tmp[strlen_P(label) + 10 + 1], numstr[10];
      sprintf_P(tmp, label, dtostrf(FINE_MANUAL_MOVE, 1, digs, numstr));

      #if DISABLED(HAS_GRAPHICAL_TFT)
        SUBMENU_P(NUL_STR, []{ _goto_manual_move(float(FINE_MANUAL_MOVE)); });
        MENU_ITEM_ADDON_START(0 + ENABLED(HAS_MARLINUI_HD44780));
        lcd_put_u8str(tmp);
        MENU_ITEM_ADDON_END();
      #else
        SUBMENU_P(tmp, []{ _goto_manual_move(float(FINE_MANUAL_MOVE)); });
      #endif
>>>>>>> mcu_ctrl
    }
  }
  END_MENU();
}

<<<<<<< HEAD
=======
#if E_MANUAL

  inline void _goto_menu_move_distance_e() {
    ui.goto_screen([]{ _menu_move_distance(E_AXIS, []{ lcd_move_e(); }); });
  }

  inline void _menu_move_distance_e_maybe() {
    #if ENABLED(PREVENT_COLD_EXTRUSION)
      const bool too_cold = thermalManager.tooColdToExtrude(active_extruder);
      if (too_cold) {
        ui.goto_screen([]{
          MenuItem_confirm::select_screen(
            GET_TEXT(MSG_BUTTON_PROCEED), GET_TEXT(MSG_BACK),
            _goto_menu_move_distance_e, ui.goto_previous_screen,
            GET_TEXT(MSG_HOTEND_TOO_COLD), (const char *)nullptr, PSTR("!")
          );
        });
        return;
      }
    #endif
    _goto_menu_move_distance_e();
  }

#endif // E_MANUAL

>>>>>>> mcu_ctrl
void menu_move() {
  START_MENU();
  BACK_ITEM(MSG_MOTION);

<<<<<<< HEAD
  #if HAS_SOFTWARE_ENDSTOPS && ENABLED(SOFT_ENDSTOPS_MENU_ITEM)
    EDIT_ITEM(bool, MSG_LCD_SOFT_ENDSTOPS, &soft_endstops_enabled);
  #endif

  if (
    #if IS_KINEMATIC || ENABLED(NO_MOTION_BEFORE_HOMING)
      all_axes_homed()
    #else
      true
    #endif
  ) {
    if (
      #if ENABLED(DELTA)
        current_position.z <= delta_clip_start_height
      #else
        true
      #endif
    ) {
=======
  #if BOTH(HAS_SOFTWARE_ENDSTOPS, SOFT_ENDSTOPS_MENU_ITEM)
    EDIT_ITEM(bool, MSG_LCD_SOFT_ENDSTOPS, &soft_endstop._enabled);
  #endif

  if (NONE(IS_KINEMATIC, NO_MOTION_BEFORE_HOMING) || all_axes_homed()) {
    if (TERN1(DELTA, current_position.z <= delta_clip_start_height)) {
>>>>>>> mcu_ctrl
      SUBMENU(MSG_MOVE_X, []{ _menu_move_distance(X_AXIS, lcd_move_x); });
      SUBMENU(MSG_MOVE_Y, []{ _menu_move_distance(Y_AXIS, lcd_move_y); });
    }
    #if ENABLED(DELTA)
      else
        ACTION_ITEM(MSG_FREE_XY, []{ line_to_z(delta_clip_start_height); ui.synchronize(); });
    #endif

    SUBMENU(MSG_MOVE_Z, []{ _menu_move_distance(Z_AXIS, lcd_move_z); });
  }
  else
    GCODES_ITEM(MSG_AUTO_HOME, G28_STR);

  #if ANY(SWITCHING_EXTRUDER, SWITCHING_NOZZLE, MAGNETIC_SWITCHING_TOOLHEAD)

    #if EXTRUDERS >= 4
      switch (active_extruder) {
        case 0: GCODES_ITEM_N(1, MSG_SELECT_E, PSTR("T1")); break;
        case 1: GCODES_ITEM_N(0, MSG_SELECT_E, PSTR("T0")); break;
        case 2: GCODES_ITEM_N(3, MSG_SELECT_E, PSTR("T3")); break;
        case 3: GCODES_ITEM_N(2, MSG_SELECT_E, PSTR("T2")); break;
        #if EXTRUDERS == 6
          case 4: GCODES_ITEM_N(5, MSG_SELECT_E, PSTR("T5")); break;
          case 5: GCODES_ITEM_N(4, MSG_SELECT_E, PSTR("T4")); break;
        #endif
      }
    #elif EXTRUDERS == 3
      if (active_extruder < 2) {
        if (active_extruder)
          GCODES_ITEM_N(0, MSG_SELECT_E, PSTR("T0"));
        else
          GCODES_ITEM_N(1, MSG_SELECT_E, PSTR("T1"));
      }
    #else
      if (active_extruder)
        GCODES_ITEM_N(0, MSG_SELECT_E, PSTR("T0"));
      else
        GCODES_ITEM_N(1, MSG_SELECT_E, PSTR("T1"));
    #endif

  #elif ENABLED(DUAL_X_CARRIAGE)

    if (active_extruder)
      GCODES_ITEM_N(0, MSG_SELECT_E, PSTR("T0"));
    else
      GCODES_ITEM_N(1, MSG_SELECT_E, PSTR("T1"));

  #endif

  #if E_MANUAL

    // The current extruder
<<<<<<< HEAD
    SUBMENU(MSG_MOVE_E, []{ _menu_move_distance(E_AXIS, []{ lcd_move_e(); }, -1); });
=======
    SUBMENU(MSG_MOVE_E, []{ _menu_move_distance_e_maybe(); });
>>>>>>> mcu_ctrl

    #define SUBMENU_MOVE_E(N) SUBMENU_N(N, MSG_MOVE_EN, []{ _menu_move_distance(E_AXIS, []{ lcd_move_e(MenuItemBase::itemIndex); }, MenuItemBase::itemIndex); });

    #if EITHER(SWITCHING_EXTRUDER, SWITCHING_NOZZLE)

      // ...and the non-switching
<<<<<<< HEAD
      #if E_MANUAL == 5
        SUBMENU_MOVE_E(4);
      #elif E_MANUAL == 3
        SUBMENU_MOVE_E(2);
      #endif

    #elif E_MANUAL > 1

      // Independent extruders with one E-stepper per hotend
      for (uint8_t n = 0; n < E_MANUAL; n++) SUBMENU_MOVE_E(n);
=======
      #if E_MANUAL == 7 || E_MANUAL == 5 || E_MANUAL == 3
        SUBMENU_MOVE_E(E_MANUAL - 1);
      #endif

    #elif MULTI_E_MANUAL

      // Independent extruders with one E-stepper per hotend
      LOOP_L_N(n, E_MANUAL) SUBMENU_MOVE_E(n);
>>>>>>> mcu_ctrl

    #endif

  #endif // E_MANUAL

  END_MENU();
}

#if ENABLED(AUTO_BED_LEVELING_UBL)
  void _lcd_ubl_level_bed();
#elif ENABLED(LCD_BED_LEVELING)
  void menu_bed_leveling();
#endif

<<<<<<< HEAD
=======
#if ENABLED(ASSISTED_TRAMMING_WIZARD)
  void goto_tramming_wizard();
#endif

>>>>>>> mcu_ctrl
void menu_motion() {
  START_MENU();

  //
  // ^ Main
  //
  BACK_ITEM(MSG_MAIN);

  //
  // Move Axis
  //
<<<<<<< HEAD
  #if ENABLED(DELTA)
    if (all_axes_homed())
  #endif
      SUBMENU(MSG_MOVE_AXIS, menu_move);
=======
  if (TERN1(DELTA, all_axes_homed()))
    SUBMENU(MSG_MOVE_AXIS, menu_move);
>>>>>>> mcu_ctrl

  //
  // Auto Home
  //
  GCODES_ITEM(MSG_AUTO_HOME, G28_STR);
  #if ENABLED(INDIVIDUAL_AXIS_HOMING_MENU)
<<<<<<< HEAD
    GCODES_ITEM(MSG_AUTO_HOME_X, PSTR("G28 X"));
    GCODES_ITEM(MSG_AUTO_HOME_Y, PSTR("G28 Y"));
    GCODES_ITEM(MSG_AUTO_HOME_Z, PSTR("G28 Z"));
=======
    GCODES_ITEM(MSG_AUTO_HOME_X, PSTR("G28X"));
    GCODES_ITEM(MSG_AUTO_HOME_Y, PSTR("G28Y"));
    GCODES_ITEM(MSG_AUTO_HOME_Z, PSTR("G28Z"));
  #endif

  //
  // Auto-calibration
  //
  #if ENABLED(CALIBRATION_GCODE)
    GCODES_ITEM(MSG_AUTO_CALIBRATE, PSTR("G425"));
>>>>>>> mcu_ctrl
  #endif

  //
  // Auto Z-Align
  //
<<<<<<< HEAD
  #if ENABLED(Z_STEPPER_AUTO_ALIGN)
=======
  #if EITHER(Z_STEPPER_AUTO_ALIGN, MECHANICAL_GANTRY_CALIBRATION)
>>>>>>> mcu_ctrl
    GCODES_ITEM(MSG_AUTO_Z_ALIGN, PSTR("G34"));
  #endif

  //
<<<<<<< HEAD
=======
  // Assisted Bed Tramming
  //
  #if ENABLED(ASSISTED_TRAMMING_WIZARD)
    SUBMENU(MSG_TRAMMING_WIZARD, goto_tramming_wizard);
  #endif

  //
>>>>>>> mcu_ctrl
  // Level Bed
  //
  #if ENABLED(AUTO_BED_LEVELING_UBL)

    SUBMENU(MSG_UBL_LEVEL_BED, _lcd_ubl_level_bed);

  #elif ENABLED(LCD_BED_LEVELING)

<<<<<<< HEAD
    if (!g29_in_progress) SUBMENU(MSG_BED_LEVELING, menu_bed_leveling);
=======
    if (!g29_in_progress)
      SUBMENU(MSG_BED_LEVELING, menu_bed_leveling);
>>>>>>> mcu_ctrl

  #elif HAS_LEVELING && DISABLED(SLIM_LCD_MENUS)

    #if DISABLED(PROBE_MANUALLY)
<<<<<<< HEAD
      GCODES_ITEM(MSG_LEVEL_BED, PSTR("G28\nG29"));
    #endif
=======
      GCODES_ITEM(MSG_LEVEL_BED, PSTR("G29N"));
    #endif

>>>>>>> mcu_ctrl
    if (all_axes_homed() && leveling_is_valid()) {
      bool show_state = planner.leveling_active;
      EDIT_ITEM(bool, MSG_BED_LEVELING, &show_state, _lcd_toggle_bed_leveling);
    }
<<<<<<< HEAD
=======

>>>>>>> mcu_ctrl
    #if ENABLED(ENABLE_LEVELING_FADE_HEIGHT)
      editable.decimal = planner.z_fade_height;
      EDIT_ITEM_FAST(float3, MSG_Z_FADE_HEIGHT, &editable.decimal, 0, 100, []{ set_z_fade_height(editable.decimal); });
    #endif

  #endif

  #if ENABLED(LEVEL_BED_CORNERS) && DISABLED(LCD_BED_LEVELING)
<<<<<<< HEAD
    ACTION_ITEM(MSG_LEVEL_CORNERS, _lcd_level_bed_corners);
  #endif

  #if ENABLED(Z_MIN_PROBE_REPEATABILITY_TEST)
    GCODES_ITEM(MSG_M48_TEST, PSTR("G28\nM48 P10"));
=======
    SUBMENU(MSG_LEVEL_CORNERS, _lcd_level_bed_corners);
  #endif

  #if ENABLED(Z_MIN_PROBE_REPEATABILITY_TEST)
    GCODES_ITEM(MSG_M48_TEST, PSTR("G28O\nM48 P10"));
>>>>>>> mcu_ctrl
  #endif

  //
  // Disable Steppers
  //
  GCODES_ITEM(MSG_DISABLE_STEPPERS, PSTR("M84"));

  END_MENU();
}

#endif // HAS_LCD_MENU
