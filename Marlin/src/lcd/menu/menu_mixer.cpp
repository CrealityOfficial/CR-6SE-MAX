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
// Mixer Menu
//

#include "../../inc/MarlinConfigPre.h"

<<<<<<< HEAD
#if HAS_LCD_MENU && ENABLED(MIXING_EXTRUDER)

#include "menu.h"
=======
#if BOTH(HAS_LCD_MENU, MIXING_EXTRUDER)

#include "menu_item.h"
>>>>>>> mcu_ctrl
#include "menu_addon.h"

#include "../../feature/mixing.h"

<<<<<<< HEAD
#define CHANNEL_MIX_EDITING !DUAL_MIXING_EXTRUDER

#if ENABLED(GRADIENT_MIX)

  void lcd_mixer_gradient_z_start_edit() {
    ui.defer_status_screen();
    ENCODER_RATE_MULTIPLY(true);
    if (ui.encoderPosition != 0) {
      mixer.gradient.start_z += float(int32_t(ui.encoderPosition)) * 0.1;
      ui.encoderPosition = 0;
      NOLESS(mixer.gradient.start_z, 0);
      NOMORE(mixer.gradient.start_z, Z_MAX_POS);
    }
    if (ui.should_draw()) {
      char tmp[21];
      strcpy_P(tmp, GET_TEXT(MSG_START_Z));
      sprintf_P(tmp + strlen(tmp), PSTR(": %4d.%d mm"), int(mixer.gradient.start_z), int(mixer.gradient.start_z * 10) % 10);
      SETCURSOR(2, (LCD_HEIGHT - 1) / 2);
      lcd_put_u8str(tmp);
    }

    if (ui.lcd_clicked) {
      if (mixer.gradient.start_z > mixer.gradient.end_z)
        mixer.gradient.end_z = mixer.gradient.start_z;
      mixer.refresh_gradient();
      ui.goto_previous_screen();
    }
  }

  void lcd_mixer_gradient_z_end_edit() {
    ui.defer_status_screen();
    ENCODER_RATE_MULTIPLY(true);
    if (ui.encoderPosition != 0) {
      mixer.gradient.end_z += float(int32_t(ui.encoderPosition)) * 0.1;
      ui.encoderPosition = 0;
      NOLESS(mixer.gradient.end_z, 0);
      NOMORE(mixer.gradient.end_z, Z_MAX_POS);
    }

    if (ui.should_draw()) {
      char tmp[21];
      strcpy_P(tmp, GET_TEXT(MSG_END_Z));
      sprintf_P(tmp + strlen(tmp), PSTR(": %4d.%d mm"), int(mixer.gradient.end_z), int(mixer.gradient.end_z * 10) % 10);
      SETCURSOR(2, (LCD_HEIGHT - 1) / 2);
=======
#if HAS_GRAPHICAL_TFT
  #include "../tft/tft.h"
#endif

#define CHANNEL_MIX_EDITING !HAS_DUAL_MIXING

#if ENABLED(GRADIENT_MIX)

  void _lcd_mixer_gradient_z_edit(const bool isend) {
    ui.defer_status_screen();
    ENCODER_RATE_MULTIPLY(true);

    float &zvar = isend ? mixer.gradient.end_z : mixer.gradient.start_z;

    if (ui.encoderPosition) {
      zvar += float(int32_t(ui.encoderPosition)) * 0.1;
      ui.encoderPosition = 0;
      NOLESS(zvar, 0);
      NOMORE(zvar, Z_MAX_POS);
    }

    if (ui.should_draw()) {
      char tmp[16];
      SETCURSOR(1, (LCD_HEIGHT - 1) / 2);
      lcd_put_u8str_P(isend ? GET_TEXT(MSG_END_Z) : GET_TEXT(MSG_START_Z));
      sprintf_P(tmp, PSTR("%4d.%d mm"), int(zvar), int(zvar * 10) % 10);
      SETCURSOR_RJ(9, (LCD_HEIGHT - 1) / 2);
>>>>>>> mcu_ctrl
      lcd_put_u8str(tmp);
    }

    if (ui.lcd_clicked) {
<<<<<<< HEAD
      if (mixer.gradient.end_z < mixer.gradient.start_z)
        mixer.gradient.start_z = mixer.gradient.end_z;
      mixer.refresh_gradient();
      ui.goto_previous_screen();
    }
=======
      if (isend && zvar < mixer.gradient.start_z)
        mixer.gradient.start_z = zvar;
      else if (!isend && zvar > mixer.gradient.end_z)
        mixer.gradient.end_z = zvar;
      mixer.refresh_gradient();
      ui.goto_previous_screen();
    }
    else {
      TERN_(HAS_GRAPHICAL_TFT, tft.draw_edit_screen_buttons());
    }
>>>>>>> mcu_ctrl
  }

  void lcd_mixer_edit_gradient_menu() {
    START_MENU();
    BACK_ITEM(MSG_MIXER);

    EDIT_ITEM(int8, MSG_START_VTOOL, &mixer.gradient.start_vtool, 0, MIXING_VIRTUAL_TOOLS - 1, mixer.refresh_gradient);
    EDIT_ITEM(int8, MSG_END_VTOOL, &mixer.gradient.end_vtool, 0, MIXING_VIRTUAL_TOOLS - 1, mixer.refresh_gradient);

    #if ENABLED(GRADIENT_VTOOL)
<<<<<<< HEAD
      EDIT_ITEM(int8, MSG_GRADIENT_ALIAS, &mixer.gradient.vtool_index, 0, MIXING_VIRTUAL_TOOLS - 1, mixer.refresh_gradient);
=======
      EDIT_ITEM(int8, MSG_GRADIENT_ALIAS, &mixer.gradient.vtool_index, -1, MIXING_VIRTUAL_TOOLS - 1, mixer.refresh_gradient);
>>>>>>> mcu_ctrl
    #endif

    char tmp[18];

<<<<<<< HEAD
    SUBMENU(MSG_START_Z, lcd_mixer_gradient_z_start_edit);
    MENU_ITEM_ADDON_START(9);
=======
    PGM_P const slabel = GET_TEXT(MSG_START_Z);
    SUBMENU_P(slabel, []{ _lcd_mixer_gradient_z_edit(false); });
    MENU_ITEM_ADDON_START_RJ(11);
>>>>>>> mcu_ctrl
      sprintf_P(tmp, PSTR("%4d.%d mm"), int(mixer.gradient.start_z), int(mixer.gradient.start_z * 10) % 10);
      lcd_put_u8str(tmp);
    MENU_ITEM_ADDON_END();

<<<<<<< HEAD
    SUBMENU(MSG_END_Z, lcd_mixer_gradient_z_end_edit);
    MENU_ITEM_ADDON_START(9);
=======
    PGM_P const elabel = GET_TEXT(MSG_END_Z);
    SUBMENU_P(elabel, []{ _lcd_mixer_gradient_z_edit(true); });
    MENU_ITEM_ADDON_START_RJ(11);
>>>>>>> mcu_ctrl
      sprintf_P(tmp, PSTR("%4d.%d mm"), int(mixer.gradient.end_z), int(mixer.gradient.end_z * 10) % 10);
      lcd_put_u8str(tmp);
    MENU_ITEM_ADDON_END();

    END_MENU();
  }

#endif // GRADIENT_MIX

static uint8_t v_index;

<<<<<<< HEAD
#if DUAL_MIXING_EXTRUDER
=======
#if HAS_DUAL_MIXING
>>>>>>> mcu_ctrl
  void _lcd_draw_mix(const uint8_t y) {
    char tmp[20]; // "100%_100%"
    sprintf_P(tmp, PSTR("%3d%% %3d%%"), int(mixer.mix[0]), int(mixer.mix[1]));
    SETCURSOR(2, y); lcd_put_u8str_P(GET_TEXT(MSG_MIX));
<<<<<<< HEAD
    SETCURSOR_RJ(9, y); lcd_put_u8str(tmp);
=======
    SETCURSOR_RJ(10, y); lcd_put_u8str(tmp);
>>>>>>> mcu_ctrl
  }
#endif

void _lcd_mixer_select_vtool() {
  mixer.T(v_index);
<<<<<<< HEAD
  #if DUAL_MIXING_EXTRUDER
    _lcd_draw_mix(LCD_HEIGHT - 1);
  #endif
=======
  TERN_(HAS_DUAL_MIXING, _lcd_draw_mix(LCD_HEIGHT - 1));
>>>>>>> mcu_ctrl
}

#if CHANNEL_MIX_EDITING

  void _lcd_mixer_cycle_mix() {
    uint16_t bits = 0;
    MIXER_STEPPER_LOOP(i) if (mixer.collector[i]) SBI(bits, i);
    bits = (bits + 1) & (_BV(MIXING_STEPPERS) - 1);
    if (!bits) ++bits;
    MIXER_STEPPER_LOOP(i) mixer.collector[i] = TEST(bits, i) ? 10.0f : 0.0f;
    ui.refresh();
  }

  void _lcd_mixer_commit_vtool() {
    mixer.normalize();
    ui.goto_previous_screen();
  }

#endif

void lcd_mixer_mix_edit() {

<<<<<<< HEAD
  #if DUAL_MIXING_EXTRUDER && !CHANNEL_MIX_EDITING

    // Adjust 2-channel mix from the encoder
    if (ui.encoderPosition != 0) {
=======
  #if HAS_DUAL_MIXING && !CHANNEL_MIX_EDITING

    // Adjust 2-channel mix from the encoder
    if (ui.encoderPosition) {
>>>>>>> mcu_ctrl
      mixer.mix[0] += int32_t(ui.encoderPosition);
      ui.encoderPosition = 0;
      if (mixer.mix[0] < 0) mixer.mix[0] += 101;
      if (mixer.mix[0] > 100) mixer.mix[0] -= 101;
      mixer.mix[1] = 100 - mixer.mix[0];
    }
    _lcd_draw_mix((LCD_HEIGHT - 1) / 2);

    // Click to commit the change
    if (ui.lcd_clicked) {
      mixer.update_vtool_from_mix();
      ui.goto_previous_screen();
    }

<<<<<<< HEAD
=======
    TERN_(HAS_GRAPHICAL_TFT, tft.draw_edit_screen_buttons());

>>>>>>> mcu_ctrl
  #else

    START_MENU();
    BACK_ITEM(MSG_MIXER);

    #if CHANNEL_MIX_EDITING

<<<<<<< HEAD
      for (uint8_t n = 1; n <= MIXING_STEPPERS; n++)
        EDIT_ITEM_FAST_N(float52, n, MSG_MIX_COMPONENT_N, &mixer.collector[n-1], 0, 10);
=======
      LOOP_S_LE_N(n, 1, MIXING_STEPPERS)
        EDIT_ITEM_FAST_N(float42_52, n, MSG_MIX_COMPONENT_N, &mixer.collector[n-1], 0, 10);
>>>>>>> mcu_ctrl

      ACTION_ITEM(MSG_CYCLE_MIX, _lcd_mixer_cycle_mix);
      ACTION_ITEM(MSG_COMMIT_VTOOL, _lcd_mixer_commit_vtool);

    #endif

    END_MENU();

  #endif
}

<<<<<<< HEAD
#if DUAL_MIXING_EXTRUDER
=======
#if HAS_DUAL_MIXING
>>>>>>> mcu_ctrl

  //
  // Toggle Dual-Mix
  //
  inline void _lcd_mixer_toggle_mix() {
    mixer.mix[0] = mixer.mix[0] == 100 ? 0 : 100;
    mixer.mix[1] = 100 - mixer.mix[0];
    mixer.update_vtool_from_mix();
    ui.refresh(LCDVIEW_CALL_REDRAW_NEXT);
  }

#endif

#if CHANNEL_MIX_EDITING

  //
  // Prepare and Edit Mix
  //
  inline void _lcd_goto_mix_edit() {
    mixer.refresh_collector(10, v_index);
    ui.goto_screen(lcd_mixer_mix_edit);
    lcd_mixer_mix_edit();
  }

#endif

#if ENABLED(GRADIENT_MIX)
  //
  // Reverse Gradient
  //
  inline void _lcd_mixer_reverse_gradient() {
    const uint8_t sv = mixer.gradient.start_vtool;
    mixer.gradient.start_vtool = mixer.gradient.end_vtool;
    mixer.gradient.end_vtool = sv;
    mixer.refresh_gradient();
    ui.refresh(LCDVIEW_CALL_REDRAW_NEXT);
  }
#endif

void menu_mixer() {
  START_MENU();
  BACK_ITEM(MSG_MAIN);

  v_index = mixer.get_current_vtool();
<<<<<<< HEAD
  EDIT_ITEM(uint8, MSG_ACTIVE_VTOOL, &v_index, 0, MIXING_VIRTUAL_TOOLS - 1, _lcd_mixer_select_vtool
    #if DUAL_MIXING_EXTRUDER
      , true
    #endif
  );

  #if DUAL_MIXING_EXTRUDER
  {
    char tmp[10];
    SUBMENU(MSG_MIX, lcd_mixer_mix_edit);
    MENU_ITEM_ADDON_START(10);
=======
  EDIT_ITEM(uint8, MSG_ACTIVE_VTOOL, &v_index, 0, MIXING_VIRTUAL_TOOLS - 1, _lcd_mixer_select_vtool, ENABLED(HAS_DUAL_MIXING));

  #if HAS_DUAL_MIXING
  {
    char tmp[11];
    SUBMENU(MSG_MIX, lcd_mixer_mix_edit);
    MENU_ITEM_ADDON_START_RJ(9);
>>>>>>> mcu_ctrl
      mixer.update_mix_from_vtool();
      sprintf_P(tmp, PSTR("%3d;%3d%%"), int(mixer.mix[0]), int(mixer.mix[1]));
      lcd_put_u8str(tmp);
    MENU_ITEM_ADDON_END();
    ACTION_ITEM(MSG_TOGGLE_MIX, _lcd_mixer_toggle_mix);
  }
  #else
    SUBMENU(MSG_MIX, _lcd_goto_mix_edit);
  #endif

  //
  // Reset All V-Tools
  //
  CONFIRM_ITEM(MSG_RESET_VTOOLS,
    MSG_BUTTON_RESET, MSG_BUTTON_CANCEL,
    []{
      mixer.reset_vtools();
      LCD_MESSAGEPGM(MSG_VTOOLS_RESET);
      ui.return_to_status();
    },
<<<<<<< HEAD
    ui.goto_previous_screen,
    GET_TEXT(MSG_RESET_VTOOLS), (PGM_P)nullptr, PSTR("?")
=======
    nullptr,
    GET_TEXT(MSG_RESET_VTOOLS), (const char *)nullptr, PSTR("?")
>>>>>>> mcu_ctrl
  );

  #if ENABLED(GRADIENT_MIX)
  {
    char tmp[13];
    SUBMENU(MSG_GRADIENT, lcd_mixer_edit_gradient_menu);
<<<<<<< HEAD
    MENU_ITEM_ADDON_START(10);
=======
    MENU_ITEM_ADDON_START_RJ(9);
>>>>>>> mcu_ctrl
      sprintf_P(tmp, PSTR("T%i->T%i"), mixer.gradient.start_vtool, mixer.gradient.end_vtool);
      lcd_put_u8str(tmp);
    MENU_ITEM_ADDON_END();
    ACTION_ITEM(MSG_REVERSE_GRADIENT, _lcd_mixer_reverse_gradient);
  }
  #endif

  END_MENU();
}

#endif // HAS_LCD_MENU && MIXING_EXTRUDER
