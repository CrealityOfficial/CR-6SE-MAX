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
// Bed Leveling Menus
//

#include "../../inc/MarlinConfigPre.h"

#if ENABLED(LCD_BED_LEVELING)

<<<<<<< HEAD
#include "menu.h"
=======
#include "menu_item.h"
>>>>>>> mcu_ctrl
#include "../../module/planner.h"
#include "../../feature/bedlevel/bedlevel.h"

#if HAS_BED_PROBE && DISABLED(BABYSTEP_ZPROBE_OFFSET)
  #include "../../module/probe.h"
#endif

<<<<<<< HEAD
=======
#if HAS_GRAPHICAL_TFT
  #include "../tft/tft.h"
  #if ENABLED(TOUCH_SCREEN)
    #include "../tft/touch.h"
  #endif
#endif

>>>>>>> mcu_ctrl
#if EITHER(PROBE_MANUALLY, MESH_BED_LEVELING)

  #include "../../module/motion.h"
  #include "../../gcode/queue.h"

  //
  // Motion > Level Bed handlers
  //

  static uint8_t manual_probe_index;

  // LCD probed points are from defaults
<<<<<<< HEAD
  constexpr uint8_t total_probe_points = (
    #if ENABLED(AUTO_BED_LEVELING_3POINT)
      3
    #elif ABL_GRID || ENABLED(MESH_BED_LEVELING)
      GRID_MAX_POINTS
    #endif
  );

  bool MarlinUI::wait_for_bl_move; // = false
=======
  constexpr uint8_t total_probe_points = TERN(AUTO_BED_LEVELING_3POINT, 3, GRID_MAX_POINTS);
>>>>>>> mcu_ctrl

  //
  // Bed leveling is done. Wait for G29 to complete.
  // A flag is used so that this can release control
  // and allow the command queue to be processed.
  //
  // When G29 finishes the last move:
<<<<<<< HEAD
  // - Raise Z to the "manual probe height"
=======
  // - Raise Z to the "Z after probing" height
>>>>>>> mcu_ctrl
  // - Don't return until done.
  //
  // ** This blocks the command queue! **
  //
  void _lcd_level_bed_done() {
<<<<<<< HEAD
    if (!ui.wait_for_bl_move) {
      #if MANUAL_PROBE_HEIGHT > 0 && DISABLED(MESH_BED_LEVELING)
        // Display "Done" screen and wait for moves to complete
        line_to_z(MANUAL_PROBE_HEIGHT);
        ui.synchronize(GET_TEXT(MSG_LEVEL_BED_DONE));
      #endif
      ui.goto_previous_screen_no_defer();
      #if HAS_BUZZER
        ui.completion_feedback();
      #endif
=======
    if (!ui.wait_for_move) {
      #if Z_AFTER_PROBING > 0 && DISABLED(MESH_BED_LEVELING)
        // Display "Done" screen and wait for moves to complete
        line_to_z(Z_AFTER_PROBING);
        ui.synchronize(GET_TEXT(MSG_LEVEL_BED_DONE));
      #endif
      ui.goto_previous_screen_no_defer();
      ui.completion_feedback();
>>>>>>> mcu_ctrl
    }
    if (ui.should_draw()) MenuItem_static::draw(LCD_HEIGHT >= 4, GET_TEXT(MSG_LEVEL_BED_DONE));
    ui.refresh(LCDVIEW_CALL_REDRAW_NEXT);
  }

  void _lcd_level_goto_next_point();

  //
  // Step 7: Get the Z coordinate, click goes to the next point or exits
  //
  void _lcd_level_bed_get_z() {

    if (ui.use_click()) {

      //
      // Save the current Z position and move
      //

      // If done...
      if (++manual_probe_index >= total_probe_points) {
        //
        // The last G29 records the point and enables bed leveling
        //
<<<<<<< HEAD
        ui.wait_for_bl_move = true;
        ui.goto_screen(_lcd_level_bed_done);
        #if ENABLED(MESH_BED_LEVELING)
          queue.inject_P(PSTR("G29 S2"));
        #elif ENABLED(PROBE_MANUALLY)
          queue.inject_P(PSTR("G29 V1"));
=======
        ui.wait_for_move = true;
        ui.goto_screen(_lcd_level_bed_done);
        #if ENABLED(MESH_BED_LEVELING)
          queue.inject_P(PSTR("G29S2"));
        #elif ENABLED(PROBE_MANUALLY)
          queue.inject_P(PSTR("G29V1"));
>>>>>>> mcu_ctrl
        #endif
      }
      else
        _lcd_level_goto_next_point();

      return;
    }

    //
    // Encoder knob or keypad buttons adjust the Z position
    //
    if (ui.encoderPosition) {
      const float z = current_position.z + float(int32_t(ui.encoderPosition)) * (MESH_EDIT_Z_STEP);
      line_to_z(constrain(z, -(LCD_PROBE_Z_RANGE) * 0.5f, (LCD_PROBE_Z_RANGE) * 0.5f));
      ui.refresh(LCDVIEW_CALL_REDRAW_NEXT);
      ui.encoderPosition = 0;
    }

    //
    // Draw on first display, then only on Z change
    //
    if (ui.should_draw()) {
      const float v = current_position.z;
      MenuEditItemBase::draw_edit_screen(GET_TEXT(MSG_MOVE_Z), ftostr43sign(v + (v < 0 ? -0.0001f : 0.0001f), '+'));
    }
  }

  //
  // Step 6: Display "Next point: 1 / 9" while waiting for move to finish
  //
  void _lcd_level_bed_moving() {
    if (ui.should_draw()) {
      char msg[10];
      sprintf_P(msg, PSTR("%i / %u"), int(manual_probe_index + 1), total_probe_points);
      MenuEditItemBase::draw_edit_screen(GET_TEXT(MSG_LEVEL_BED_NEXT_POINT), msg);
    }
    ui.refresh(LCDVIEW_CALL_NO_REDRAW);
<<<<<<< HEAD
    if (!ui.wait_for_bl_move) ui.goto_screen(_lcd_level_bed_get_z);
=======
    if (!ui.wait_for_move) ui.goto_screen(_lcd_level_bed_get_z);
>>>>>>> mcu_ctrl
  }

  //
  // Step 5: Initiate a move to the next point
  //
  void _lcd_level_goto_next_point() {
    ui.goto_screen(_lcd_level_bed_moving);

    // G29 Records Z, moves, and signals when it pauses
<<<<<<< HEAD
    ui.wait_for_bl_move = true;
    #if ENABLED(MESH_BED_LEVELING)
      queue.inject_P(manual_probe_index ? PSTR("G29 S2") : PSTR("G29 S1"));
    #elif ENABLED(PROBE_MANUALLY)
      queue.inject_P(PSTR("G29 V1"));
=======
    ui.wait_for_move = true;
    #if ENABLED(MESH_BED_LEVELING)
      queue.inject_P(manual_probe_index ? PSTR("G29S2") : PSTR("G29S1"));
    #elif ENABLED(PROBE_MANUALLY)
      queue.inject_P(PSTR("G29V1"));
>>>>>>> mcu_ctrl
    #endif
  }

  //
  // Step 4: Display "Click to Begin", wait for click
  //         Move to the first probe position
  //
  void _lcd_level_bed_homing_done() {
<<<<<<< HEAD
    if (ui.should_draw()) MenuItem_static::draw(1, GET_TEXT(MSG_LEVEL_BED_WAITING));
=======
    if (ui.should_draw()) {
      MenuItem_static::draw(1, GET_TEXT(MSG_LEVEL_BED_WAITING));
      // Color UI needs a control to detect a touch
      #if BOTH(TOUCH_SCREEN, HAS_GRAPHICAL_TFT)
        touch.add_control(CLICK, 0, 0, TFT_WIDTH, TFT_HEIGHT);
      #endif
    }
>>>>>>> mcu_ctrl
    if (ui.use_click()) {
      manual_probe_index = 0;
      _lcd_level_goto_next_point();
    }
  }

  //
  // Step 3: Display "Homing XYZ" - Wait for homing to finish
  //
  void _lcd_level_bed_homing() {
    _lcd_draw_homing();
    if (all_axes_homed()) ui.goto_screen(_lcd_level_bed_homing_done);
  }

  #if ENABLED(PROBE_MANUALLY)
    extern bool g29_in_progress;
  #endif

  //
  // Step 2: Continue Bed Leveling...
  //
  void _lcd_level_bed_continue() {
    ui.defer_status_screen();
    set_all_unhomed();
    ui.goto_screen(_lcd_level_bed_homing);
    queue.inject_P(G28_STR);
  }

#endif // PROBE_MANUALLY || MESH_BED_LEVELING

#if ENABLED(MESH_EDIT_MENU)

  inline void refresh_planner() {
<<<<<<< HEAD
    set_current_from_steppers_for_axis(ALL_AXES);
=======
    set_current_from_steppers_for_axis(ALL_AXES_ENUM);
>>>>>>> mcu_ctrl
    sync_plan_position();
  }

  void menu_edit_mesh() {
    static uint8_t xind, yind; // =0
    START_MENU();
    BACK_ITEM(MSG_BED_LEVELING);
<<<<<<< HEAD
    EDIT_ITEM(uint8, MSG_MESH_X, &xind, 0, GRID_MAX_POINTS_X - 1);
    EDIT_ITEM(uint8, MSG_MESH_Y, &yind, 0, GRID_MAX_POINTS_Y - 1);
=======
    EDIT_ITEM(uint8, MSG_MESH_X, &xind, 0, (GRID_MAX_POINTS_X) - 1);
    EDIT_ITEM(uint8, MSG_MESH_Y, &yind, 0, (GRID_MAX_POINTS_Y) - 1);
>>>>>>> mcu_ctrl
    EDIT_ITEM_FAST(float43, MSG_MESH_EDIT_Z, &Z_VALUES(xind, yind), -(LCD_PROBE_Z_RANGE) * 0.5, (LCD_PROBE_Z_RANGE) * 0.5, refresh_planner);
    END_MENU();
  }

#endif // MESH_EDIT_MENU

/**
 * Step 1: Bed Level entry-point
 *
 * << Motion
 *    Auto Home           (if homing needed)
 *    Leveling On/Off     (if data exists, and homed)
 *    Fade Height: ---    (Req: ENABLE_LEVELING_FADE_HEIGHT)
 *    Mesh Z Offset: ---  (Req: MESH_BED_LEVELING)
 *    Z Probe Offset: --- (Req: HAS_BED_PROBE, Opt: BABYSTEP_ZPROBE_OFFSET)
 *    Level Bed >
 *    Level Corners >     (if homed)
 *    Load Settings       (Req: EEPROM_SETTINGS)
 *    Save Settings       (Req: EEPROM_SETTINGS)
 */
void menu_bed_leveling() {
<<<<<<< HEAD
  START_MENU();
  BACK_ITEM(MSG_MOTION);

  const bool is_homed = all_axes_known();

=======
  const bool is_homed = all_axes_trusted(),
             is_valid = leveling_is_valid();

  START_MENU();
  BACK_ITEM(MSG_MOTION);

>>>>>>> mcu_ctrl
  // Auto Home if not using manual probing
  #if NONE(PROBE_MANUALLY, MESH_BED_LEVELING)
    if (!is_homed) GCODES_ITEM(MSG_AUTO_HOME, G28_STR);
  #endif

  // Level Bed
  #if EITHER(PROBE_MANUALLY, MESH_BED_LEVELING)
    // Manual leveling uses a guided procedure
    SUBMENU(MSG_LEVEL_BED, _lcd_level_bed_continue);
  #else
    // Automatic leveling can just run the G-code
<<<<<<< HEAD
    GCODES_ITEM(MSG_LEVEL_BED, is_homed ? PSTR("G29") : PSTR("G28\nG29"));
  #endif

  #if ENABLED(MESH_EDIT_MENU)
    if (leveling_is_valid())
      SUBMENU(MSG_EDIT_MESH, menu_edit_mesh);
  #endif

  // Homed and leveling is valid? Then leveling can be toggled.
  if (is_homed && leveling_is_valid()) {
=======
    GCODES_ITEM(MSG_LEVEL_BED, is_homed ? PSTR("G29") : PSTR("G29N"));
  #endif

  #if ENABLED(MESH_EDIT_MENU)
    if (is_valid) SUBMENU(MSG_EDIT_MESH, menu_edit_mesh);
  #endif

  // Homed and leveling is valid? Then leveling can be toggled.
  if (is_homed && is_valid) {
>>>>>>> mcu_ctrl
    bool show_state = planner.leveling_active;
    EDIT_ITEM(bool, MSG_BED_LEVELING, &show_state, _lcd_toggle_bed_leveling);
  }

  // Z Fade Height
  #if ENABLED(ENABLE_LEVELING_FADE_HEIGHT)
    // Shadow for editing the fade height
    editable.decimal = planner.z_fade_height;
    EDIT_ITEM_FAST(float3, MSG_Z_FADE_HEIGHT, &editable.decimal, 0, 100, []{ set_z_fade_height(editable.decimal); });
  #endif

  //
  // Mesh Bed Leveling Z-Offset
  //
  #if ENABLED(MESH_BED_LEVELING)
    EDIT_ITEM(float43, MSG_BED_Z, &mbl.z_offset, -1, 1);
  #endif

  #if ENABLED(BABYSTEP_ZPROBE_OFFSET)
    SUBMENU(MSG_ZPROBE_ZOFFSET, lcd_babystep_zoffset);
  #elif HAS_BED_PROBE
<<<<<<< HEAD
    EDIT_ITEM(float52, MSG_ZPROBE_ZOFFSET, &probe_offset.z, Z_PROBE_OFFSET_RANGE_MIN, Z_PROBE_OFFSET_RANGE_MAX);
=======
    EDIT_ITEM(LCD_Z_OFFSET_TYPE, MSG_ZPROBE_ZOFFSET, &probe.offset.z, Z_PROBE_OFFSET_RANGE_MIN, Z_PROBE_OFFSET_RANGE_MAX);
>>>>>>> mcu_ctrl
  #endif

  #if ENABLED(LEVEL_BED_CORNERS)
    SUBMENU(MSG_LEVEL_CORNERS, _lcd_level_bed_corners);
  #endif

  #if ENABLED(EEPROM_SETTINGS)
<<<<<<< HEAD
    ACTION_ITEM(MSG_LOAD_EEPROM, lcd_load_settings);
    ACTION_ITEM(MSG_STORE_EEPROM, lcd_store_settings);
=======
    ACTION_ITEM(MSG_LOAD_EEPROM, ui.load_settings);
    ACTION_ITEM(MSG_STORE_EEPROM, ui.store_settings);
>>>>>>> mcu_ctrl
  #endif
  END_MENU();
}

#endif // LCD_BED_LEVELING
