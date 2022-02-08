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
 * feature/pause.cpp - Pause feature support functions
 * This may be combined with related G-codes if features are consolidated.
 */

#include "../inc/MarlinConfigPre.h"

#if ENABLED(ADVANCED_PAUSE_FEATURE)

<<<<<<< HEAD
#include "../Marlin.h"
=======
//#define DEBUG_PAUSE_RESUME

#include "../MarlinCore.h"
>>>>>>> mcu_ctrl
#include "../gcode/gcode.h"
#include "../module/motion.h"
#include "../module/planner.h"
#include "../module/stepper.h"
#include "../module/printcounter.h"
#include "../module/temperature.h"

#if ENABLED(FWRETRACT)
  #include "fwretract.h"
#endif

#if HAS_FILAMENT_SENSOR
  #include "runout.h"
#endif

#if ENABLED(HOST_ACTION_COMMANDS)
  #include "host_actions.h"
#endif

#if ENABLED(EXTENSIBLE_UI)
<<<<<<< HEAD
  #include "../lcd/extensible_ui/ui_api.h"
#endif

#include "../core/language.h"
#include "../lcd/ultralcd.h"
=======
  #include "../lcd/extui/ui_api.h"
#endif

#include "../lcd/marlinui.h"
>>>>>>> mcu_ctrl

#if HAS_BUZZER
  #include "../libs/buzzer.h"
#endif

<<<<<<< HEAD
#include "../libs/nozzle.h"
#include "pause.h"

=======
#if ENABLED(POWER_LOSS_RECOVERY)
  #include "powerloss.h"
#endif

#include "../libs/nozzle.h"
#include "pause.h"

#define DEBUG_OUT ENABLED(DEBUG_PAUSE_RESUME)
#include "../core/debug_out.h"

>>>>>>> mcu_ctrl
// private:

static xyze_pos_t resume_position;

<<<<<<< HEAD
PauseMode pause_mode = PAUSE_MODE_PAUSE_PRINT;

PauseMenuResponse pause_menu_response;
=======
#if M600_PURGE_MORE_RESUMABLE
  PauseMenuResponse pause_menu_response;
  PauseMode pause_mode = PAUSE_MODE_PAUSE_PRINT;
#endif
>>>>>>> mcu_ctrl

fil_change_settings_t fc_settings[EXTRUDERS];

#if ENABLED(SDSUPPORT)
  #include "../sd/cardreader.h"
#endif

#if ENABLED(EMERGENCY_PARSER)
  #define _PMSG(L) L##_M108
#else
  #define _PMSG(L) L##_LCD
#endif

#if HAS_BUZZER
<<<<<<< HEAD
  static void filament_change_beep(const int8_t max_beep_count, const bool init=false) {
    if (pause_mode == PAUSE_MODE_PAUSE_PRINT) return;
    static millis_t next_buzz = 0;
    static int8_t runout_beep = 0;

    if (init) next_buzz = runout_beep = 0;

    const millis_t ms = millis();
    if (ELAPSED(ms, next_buzz)) {
      if (max_beep_count < 0 || runout_beep < max_beep_count + 5) { // Only beep as long as we're supposed to
        next_buzz = ms + ((max_beep_count < 0 || runout_beep < max_beep_count) ? 1000 : 500);
=======
  static void impatient_beep(const int8_t max_beep_count, const bool restart=false) {

    if (TERN0(HAS_LCD_MENU, pause_mode == PAUSE_MODE_PAUSE_PRINT)) return;

    static millis_t next_buzz = 0;
    static int8_t runout_beep = 0;

    if (restart) next_buzz = runout_beep = 0;

    const bool always = max_beep_count < 0;

    const millis_t ms = millis();
    if (ELAPSED(ms, next_buzz)) {
      if (always || runout_beep < max_beep_count + 5) { // Only beep as long as we're supposed to
        next_buzz = ms + ((always || runout_beep < max_beep_count) ? 1000 : 500);
>>>>>>> mcu_ctrl
        BUZZ(50, 880 - (runout_beep & 1) * 220);
        runout_beep++;
      }
    }
  }
<<<<<<< HEAD
=======
  inline void first_impatient_beep(const int8_t max_beep_count) { impatient_beep(max_beep_count, true); }
#else
  inline void impatient_beep(const int8_t, const bool=false) {}
  inline void first_impatient_beep(const int8_t) {}
>>>>>>> mcu_ctrl
#endif

/**
 * Ensure a safe temperature for extrusion
 *
 * - Fail if the TARGET temperature is too low
 * - Display LCD placard with temperature status
 * - Return when heating is done or aborted
 *
 * Returns 'true' if heating was completed, 'false' for abort
 */
<<<<<<< HEAD
static bool ensure_safe_temperature(const PauseMode mode=PAUSE_MODE_SAME) {

  #if ENABLED(PREVENT_COLD_EXTRUSION)
    if (!DEBUGGING(DRYRUN) && thermalManager.targetTooColdToExtrude(active_extruder)) {
      SERIAL_ECHO_MSG(MSG_ERR_HOTEND_TOO_COLD);
      return false;
    }
  #endif

  #if HAS_LCD_MENU
    lcd_pause_show_message(PAUSE_MESSAGE_HEATING, mode);
  #else
    UNUSED(mode);
  #endif

  return thermalManager.wait_for_hotend(active_extruder);
}

void do_pause_e_move(const float &length, const feedRate_t &fr_mm_s) {
  #if HAS_FILAMENT_SENSOR
    runout.reset();
  #endif
  current_position.e += length / planner.e_factor[active_extruder];
  line_to_current_position(fr_mm_s);
  planner.synchronize();
=======
static bool ensure_safe_temperature(const bool wait=true, const PauseMode mode=PAUSE_MODE_SAME) {
  DEBUG_SECTION(est, "ensure_safe_temperature", true);
  DEBUG_ECHOLNPAIR("... wait:", wait, " mode:", mode);

  #if ENABLED(PREVENT_COLD_EXTRUSION)
    if (!DEBUGGING(DRYRUN) && thermalManager.targetTooColdToExtrude(active_extruder))
      thermalManager.setTargetHotend(thermalManager.extrude_min_temp, active_extruder);
  #endif

  ui.pause_show_message(PAUSE_MESSAGE_HEATING, mode); UNUSED(mode);

  if (wait) return thermalManager.wait_for_hotend(active_extruder);

  // Allow interruption by Emergency Parser M108
  wait_for_heatup = TERN1(PREVENT_COLD_EXTRUSION, !thermalManager.allow_cold_extrude);
  while (wait_for_heatup && ABS(thermalManager.wholeDegHotend(active_extruder) - thermalManager.degTargetHotend(active_extruder)) > (TEMP_WINDOW))
    idle();
  wait_for_heatup = false;

  #if ENABLED(PREVENT_COLD_EXTRUSION)
    // A user can cancel wait-for-heating with M108
    if (!DEBUGGING(DRYRUN) && thermalManager.targetTooColdToExtrude(active_extruder)) {
      SERIAL_ECHO_MSG(STR_ERR_HOTEND_TOO_COLD);
      return false;
    }
  #endif

  return true;
>>>>>>> mcu_ctrl
}

/**
 * Load filament into the hotend
 *
 * - Fail if the a safe temperature was not reached
 * - If pausing for confirmation, wait for a click or M108
 * - Show "wait for load" placard
 * - Load and purge filament
 * - Show "Purge more" / "Continue" menu
 * - Return when "Continue" is selected
 *
 * Returns 'true' if load was completed, 'false' for abort
 */
<<<<<<< HEAD
bool load_filament(const float &slow_load_length/*=0*/, const float &fast_load_length/*=0*/, const float &purge_length/*=0*/, const int8_t max_beep_count/*=0*/,
=======
bool load_filament(const_float_t slow_load_length/*=0*/, const_float_t fast_load_length/*=0*/, const_float_t purge_length/*=0*/, const int8_t max_beep_count/*=0*/,
>>>>>>> mcu_ctrl
                   const bool show_lcd/*=false*/, const bool pause_for_user/*=false*/,
                   const PauseMode mode/*=PAUSE_MODE_PAUSE_PRINT*/
                   DXC_ARGS
) {
<<<<<<< HEAD
  #if !HAS_LCD_MENU
    UNUSED(show_lcd);
  #endif

  if (!ensure_safe_temperature(mode)) {
    #if HAS_LCD_MENU
      if (show_lcd) lcd_pause_show_message(PAUSE_MESSAGE_STATUS, mode);
    #endif
=======
  DEBUG_SECTION(lf, "load_filament", true);
  DEBUG_ECHOLNPAIR("... slowlen:", slow_load_length, " fastlen:", fast_load_length, " purgelen:", purge_length, " maxbeep:", max_beep_count, " showlcd:", show_lcd, " pauseforuser:", pause_for_user, " pausemode:", mode DXC_SAY);

  if (!ensure_safe_temperature(false, mode)) {
    if (show_lcd) ui.pause_show_message(PAUSE_MESSAGE_STATUS, mode);
>>>>>>> mcu_ctrl
    return false;
  }

  if (pause_for_user) {
<<<<<<< HEAD
    #if HAS_LCD_MENU
      if (show_lcd) lcd_pause_show_message(PAUSE_MESSAGE_INSERT, mode);
    #endif
    SERIAL_ECHO_MSG(_PMSG(MSG_FILAMENT_CHANGE_INSERT));

    #if HAS_BUZZER
      filament_change_beep(max_beep_count, true);
    #else
      UNUSED(max_beep_count);
    #endif
=======
    if (show_lcd) ui.pause_show_message(PAUSE_MESSAGE_INSERT, mode);
    SERIAL_ECHO_MSG(_PMSG(STR_FILAMENT_CHANGE_INSERT));

    first_impatient_beep(max_beep_count);
>>>>>>> mcu_ctrl

    KEEPALIVE_STATE(PAUSED_FOR_USER);
    wait_for_user = true;    // LCD click or M108 will clear this
    #if ENABLED(HOST_PROMPT_SUPPORT)
<<<<<<< HEAD
      const char tool = '0'
        #if NUM_RUNOUT_SENSORS > 1
          + active_extruder
        #endif
      ;
      host_prompt_reason = PROMPT_USER_CONTINUE;
      host_action_prompt_end();
      host_action_prompt_begin(PSTR("Load Filament T"), false);
      SERIAL_CHAR(tool);
      SERIAL_EOL();
      host_action_prompt_button(CONTINUE_STR);
      host_action_prompt_show();
    #endif
    #if ENABLED(EXTENSIBLE_UI)
      ExtUI::onUserConfirmRequired_P(PSTR("Load Filament"));
    #endif
    while (wait_for_user) {
      #if HAS_BUZZER
        filament_change_beep(max_beep_count);
      #endif
      idle(true);
    }
  }

  #if HAS_LCD_MENU
    if (show_lcd) lcd_pause_show_message(PAUSE_MESSAGE_LOAD, mode);
  #endif
=======
      const char tool = '0' + TERN0(MULTI_FILAMENT_SENSOR, active_extruder);
      host_prompt_do(PROMPT_USER_CONTINUE, PSTR("Load Filament T"), tool, CONTINUE_STR);
    #endif

    TERN_(EXTENSIBLE_UI, ExtUI::onUserConfirmRequired_P(PSTR("Load Filament")));

    while (wait_for_user) {
      impatient_beep(max_beep_count);
      idle_no_sleep();
    }
  }

  if (show_lcd) ui.pause_show_message(PAUSE_MESSAGE_LOAD, mode);
>>>>>>> mcu_ctrl

  #if ENABLED(DUAL_X_CARRIAGE)
    const int8_t saved_ext        = active_extruder;
    const bool saved_ext_dup_mode = extruder_duplication_enabled;
<<<<<<< HEAD
    active_extruder = DXC_ext;
    extruder_duplication_enabled = false;
  #endif

  // Slow Load filament
  if (slow_load_length) do_pause_e_move(slow_load_length, FILAMENT_CHANGE_SLOW_LOAD_FEEDRATE);
=======
    set_duplication_enabled(false, DXC_ext);
  #endif

  // Slow Load filament
  if (slow_load_length) unscaled_e_move(slow_load_length, FILAMENT_CHANGE_SLOW_LOAD_FEEDRATE);
>>>>>>> mcu_ctrl

  // Fast Load Filament
  if (fast_load_length) {
    #if FILAMENT_CHANGE_FAST_LOAD_ACCEL > 0
      const float saved_acceleration = planner.settings.retract_acceleration;
      planner.settings.retract_acceleration = FILAMENT_CHANGE_FAST_LOAD_ACCEL;
    #endif

<<<<<<< HEAD
    do_pause_e_move(fast_load_length, FILAMENT_CHANGE_FAST_LOAD_FEEDRATE);
=======
    unscaled_e_move(fast_load_length, FILAMENT_CHANGE_FAST_LOAD_FEEDRATE);
>>>>>>> mcu_ctrl

    #if FILAMENT_CHANGE_FAST_LOAD_ACCEL > 0
      planner.settings.retract_acceleration = saved_acceleration;
    #endif
  }

  #if ENABLED(DUAL_X_CARRIAGE)      // Tie the two extruders movement back together.
<<<<<<< HEAD
    active_extruder = saved_ext;
    extruder_duplication_enabled = saved_ext_dup_mode;
    stepper.set_directions();
=======
    set_duplication_enabled(saved_ext_dup_mode, saved_ext);
>>>>>>> mcu_ctrl
  #endif

  #if ENABLED(ADVANCED_PAUSE_CONTINUOUS_PURGE)

<<<<<<< HEAD
    #if HAS_LCD_MENU
      if (show_lcd) lcd_pause_show_message(PAUSE_MESSAGE_PURGE);
    #endif

    wait_for_user = true;
    #if ENABLED(HOST_PROMPT_SUPPORT)
      host_prompt_do(PROMPT_USER_CONTINUE, PSTR("Filament Purge Running..."), CONTINUE_STR);
    #endif
    #if ENABLED(EXTENSIBLE_UI)
      ExtUI::onUserConfirmRequired_P(PSTR("Filament Purge Running..."));
    #endif
    for (float purge_count = purge_length; purge_count > 0 && wait_for_user; --purge_count)
      do_pause_e_move(1, ADVANCED_PAUSE_PURGE_FEEDRATE);
=======
    if (show_lcd) ui.pause_show_message(PAUSE_MESSAGE_PURGE);

    TERN_(HOST_PROMPT_SUPPORT, host_prompt_do(PROMPT_USER_CONTINUE, PSTR("Filament Purging..."), CONTINUE_STR));
    TERN_(EXTENSIBLE_UI, ExtUI::onUserConfirmRequired_P(PSTR("Filament Purging...")));
    wait_for_user = true; // A click or M108 breaks the purge_length loop
    for (float purge_count = purge_length; purge_count > 0 && wait_for_user; --purge_count)
      unscaled_e_move(1, ADVANCED_PAUSE_PURGE_FEEDRATE);
>>>>>>> mcu_ctrl
    wait_for_user = false;

  #else

    do {
      if (purge_length > 0) {
        // "Wait for filament purge"
<<<<<<< HEAD
        #if HAS_LCD_MENU
          if (show_lcd) lcd_pause_show_message(PAUSE_MESSAGE_PURGE);
        #endif

        // Extrude filament to get into hotend
        do_pause_e_move(purge_length, ADVANCED_PAUSE_PURGE_FEEDRATE);
      }

      // Show "Purge More" / "Resume" menu and wait for reply
      #if ENABLED(HOST_PROMPT_SUPPORT)
        host_prompt_reason = PROMPT_FILAMENT_RUNOUT;
        host_action_prompt_end();   // Close current prompt
        host_action_prompt_begin(PSTR("Paused"));
        host_action_prompt_button(PSTR("PurgeMore"));
        if (false
          #if HAS_FILAMENT_SENSOR
            || runout.filament_ran_out
          #endif
        )
          host_action_prompt_button(PSTR("DisableRunout"));
        else {
          host_prompt_reason = PROMPT_FILAMENT_RUNOUT;
          host_action_prompt_button(CONTINUE_STR);
        }
        host_action_prompt_show();
      #endif

      #if HAS_LCD_MENU
        if (show_lcd) {
          KEEPALIVE_STATE(PAUSED_FOR_USER);
          wait_for_user = false;
          lcd_pause_show_message(PAUSE_MESSAGE_OPTION);
          while (pause_menu_response == PAUSE_RESPONSE_WAIT_FOR) idle(true);
=======
        if (show_lcd) ui.pause_show_message(PAUSE_MESSAGE_PURGE);

        // Extrude filament to get into hotend
        unscaled_e_move(purge_length, ADVANCED_PAUSE_PURGE_FEEDRATE);
      }

      TERN_(HOST_PROMPT_SUPPORT, filament_load_host_prompt()); // Initiate another host prompt.

      #if M600_PURGE_MORE_RESUMABLE
        if (show_lcd) {
          // Show "Purge More" / "Resume" menu and wait for reply
          KEEPALIVE_STATE(PAUSED_FOR_USER);
          wait_for_user = false;
          #if HAS_LCD_MENU
            ui.pause_show_message(PAUSE_MESSAGE_OPTION); // Also sets PAUSE_RESPONSE_WAIT_FOR
          #else
            pause_menu_response = PAUSE_RESPONSE_WAIT_FOR;
          #endif
          while (pause_menu_response == PAUSE_RESPONSE_WAIT_FOR) idle_no_sleep();
>>>>>>> mcu_ctrl
        }
      #endif

      // Keep looping if "Purge More" was selected
<<<<<<< HEAD
    } while (false
      #if HAS_LCD_MENU
        || (show_lcd && pause_menu_response == PAUSE_RESPONSE_EXTRUDE_MORE)
      #endif
    );

  #endif
=======
    } while (TERN0(M600_PURGE_MORE_RESUMABLE, show_lcd && pause_menu_response == PAUSE_RESPONSE_EXTRUDE_MORE));

  #endif
  TERN_(HOST_PROMPT_SUPPORT, host_action_prompt_end());
>>>>>>> mcu_ctrl

  return true;
}

/**
<<<<<<< HEAD
=======
 * Disabling E steppers for manual filament change should be fine
 * as long as users don't spin the E motor ridiculously fast and
 * send current back to their board, potentially frying it.
 */
inline void disable_active_extruder() {
  #if HAS_E_STEPPER_ENABLE
    disable_e_stepper(active_extruder);
    safe_delay(100);
  #endif
}

/**
>>>>>>> mcu_ctrl
 * Unload filament from the hotend
 *
 * - Fail if the a safe temperature was not reached
 * - Show "wait for unload" placard
 * - Retract, pause, then unload filament
 * - Disable E stepper (on most machines)
 *
 * Returns 'true' if unload was completed, 'false' for abort
 */
<<<<<<< HEAD
bool unload_filament(const float &unload_length, const bool show_lcd/*=false*/,
                     const PauseMode mode/*=PAUSE_MODE_PAUSE_PRINT*/
                     #if BOTH(FILAMENT_UNLOAD_ALL_EXTRUDERS, MIXING_EXTRUDER)
                       , const float &mix_multiplier/*=1.0*/
                     #endif
) {
  #if !HAS_LCD_MENU
    UNUSED(show_lcd);
  #endif

  #if !BOTH(FILAMENT_UNLOAD_ALL_EXTRUDERS, MIXING_EXTRUDER)
    constexpr float mix_multiplier = 1.0;
  #endif

  if (!ensure_safe_temperature(mode)) {
    #if HAS_LCD_MENU
      if (show_lcd) lcd_pause_show_message(PAUSE_MESSAGE_STATUS);
    #endif
    return false;
  }

  #if HAS_LCD_MENU
    if (show_lcd) lcd_pause_show_message(PAUSE_MESSAGE_UNLOAD, mode);
  #endif

  // Retract filament
  do_pause_e_move(-(FILAMENT_UNLOAD_RETRACT_LENGTH) * mix_multiplier, (PAUSE_PARK_RETRACT_FEEDRATE) * mix_multiplier);

  // Wait for filament to cool
  safe_delay(FILAMENT_UNLOAD_DELAY);

  // Quickly purge
  do_pause_e_move((FILAMENT_UNLOAD_RETRACT_LENGTH + FILAMENT_UNLOAD_PURGE_LENGTH) * mix_multiplier,
                  planner.settings.max_feedrate_mm_s[E_AXIS] * mix_multiplier);
=======
bool unload_filament(const_float_t unload_length, const bool show_lcd/*=false*/,
                     const PauseMode mode/*=PAUSE_MODE_PAUSE_PRINT*/
                     #if BOTH(FILAMENT_UNLOAD_ALL_EXTRUDERS, MIXING_EXTRUDER)
                       , const_float_t mix_multiplier/*=1.0*/
                     #endif
) {
  DEBUG_SECTION(uf, "unload_filament", true);
  DEBUG_ECHOLNPAIR("... unloadlen:", unload_length, " showlcd:", show_lcd, " mode:", mode
    #if BOTH(FILAMENT_UNLOAD_ALL_EXTRUDERS, MIXING_EXTRUDER)
      , " mixmult:", mix_multiplier
    #endif
  );

  #if !BOTH(FILAMENT_UNLOAD_ALL_EXTRUDERS, MIXING_EXTRUDER)
    constexpr float mix_multiplier = 1.0f;
  #endif

  if (!ensure_safe_temperature(false, mode)) {
    if (show_lcd) ui.pause_show_message(PAUSE_MESSAGE_STATUS);
    return false;
  }

  if (show_lcd) ui.pause_show_message(PAUSE_MESSAGE_UNLOAD, mode);

  // Retract filament
  unscaled_e_move(-(FILAMENT_UNLOAD_PURGE_RETRACT) * mix_multiplier, (PAUSE_PARK_RETRACT_FEEDRATE) * mix_multiplier);

  // Wait for filament to cool
  safe_delay(FILAMENT_UNLOAD_PURGE_DELAY);

  // Quickly purge
  unscaled_e_move((FILAMENT_UNLOAD_PURGE_RETRACT + FILAMENT_UNLOAD_PURGE_LENGTH) * mix_multiplier,
                  (FILAMENT_UNLOAD_PURGE_FEEDRATE) * mix_multiplier);
>>>>>>> mcu_ctrl

  // Unload filament
  #if FILAMENT_CHANGE_UNLOAD_ACCEL > 0
    const float saved_acceleration = planner.settings.retract_acceleration;
    planner.settings.retract_acceleration = FILAMENT_CHANGE_UNLOAD_ACCEL;
  #endif

<<<<<<< HEAD
  do_pause_e_move(unload_length * mix_multiplier, (FILAMENT_CHANGE_UNLOAD_FEEDRATE) * mix_multiplier);
=======
  unscaled_e_move(unload_length * mix_multiplier, (FILAMENT_CHANGE_UNLOAD_FEEDRATE) * mix_multiplier);
>>>>>>> mcu_ctrl

  #if FILAMENT_CHANGE_FAST_LOAD_ACCEL > 0
    planner.settings.retract_acceleration = saved_acceleration;
  #endif

<<<<<<< HEAD
  // Disable E steppers for manual change
  #if HAS_E_STEPPER_ENABLE
    disable_e_stepper(active_extruder);
    safe_delay(100);
  #endif
=======
  // Disable the Extruder for manual change
  disable_active_extruder();
>>>>>>> mcu_ctrl

  return true;
}

// public:

/**
 * Pause procedure
 *
 * - Abort if already paused
 * - Send host action for pause, if configured
 * - Abort if TARGET temperature is too low
 * - Display "wait for start of filament change" (if a length was specified)
 * - Initial retract, if current temperature is hot enough
 * - Park the nozzle at the given position
 * - Call unload_filament (if a length was specified)
 *
 * Return 'true' if pause was completed, 'false' for abort
 */
uint8_t did_pause_print = 0;

<<<<<<< HEAD
bool pause_print(const float &retract, const xyz_pos_t &park_point, const float &unload_length/*=0*/, const bool show_lcd/*=false*/ DXC_ARGS) {

  #if !HAS_LCD_MENU
    UNUSED(show_lcd);
  #endif
=======
bool pause_print(const_float_t retract, const xyz_pos_t &park_point, const bool show_lcd/*=false*/, const_float_t unload_length/*=0*/ DXC_ARGS) {
  DEBUG_SECTION(pp, "pause_print", true);
  DEBUG_ECHOLNPAIR("... park.x:", park_point.x, " y:", park_point.y, " z:", park_point.z, " unloadlen:", unload_length, " showlcd:", show_lcd DXC_SAY);

  UNUSED(show_lcd);
>>>>>>> mcu_ctrl

  if (did_pause_print) return false; // already paused

  #if ENABLED(HOST_ACTION_COMMANDS)
    #ifdef ACTION_ON_PAUSED
      host_action_paused();
    #elif defined(ACTION_ON_PAUSE)
      host_action_pause();
    #endif
  #endif

<<<<<<< HEAD
  #if ENABLED(HOST_PROMPT_SUPPORT)
    host_prompt_open(PROMPT_INFO, PSTR("Pause"), PSTR("Dismiss"));
  #endif

  if (!DEBUGGING(DRYRUN) && unload_length && thermalManager.targetTooColdToExtrude(active_extruder)) {
    SERIAL_ECHO_MSG(MSG_ERR_HOTEND_TOO_COLD);

    #if HAS_LCD_MENU
      if (show_lcd) { // Show status screen
        lcd_pause_show_message(PAUSE_MESSAGE_STATUS);
        LCD_MESSAGEPGM(MSG_M600_TOO_COLD);
      }
    #endif

    return false; // unable to reach safe temperature
  }
=======
  TERN_(HOST_PROMPT_SUPPORT, host_prompt_open(PROMPT_INFO, PSTR("Pause"), DISMISS_STR));
>>>>>>> mcu_ctrl

  // Indicate that the printer is paused
  ++did_pause_print;

  // Pause the print job and timer
  #if ENABLED(SDSUPPORT)
<<<<<<< HEAD
    if (IS_SD_PRINTING()) {
=======
    const bool was_sd_printing = IS_SD_PRINTING();
    if (was_sd_printing) {
>>>>>>> mcu_ctrl
      card.pauseSDPrint();
      ++did_pause_print; // Indicate SD pause also
    }
  #endif

  print_job_timer.pause();

  // Save current position
  resume_position = current_position;

<<<<<<< HEAD
  // Wait for buffered blocks to complete
  planner.synchronize();

  #if ENABLED(ADVANCED_PAUSE_FANS_PAUSE) && FAN_COUNT > 0
=======
  // Will the nozzle be parking?
  const bool do_park = !axes_should_home();

  #if ENABLED(POWER_LOSS_RECOVERY)
    // Save PLR info in case the power goes out while parked
    const float park_raise = do_park ? nozzle.park_mode_0_height(park_point.z) - current_position.z : POWER_LOSS_ZRAISE;
    if (was_sd_printing && recovery.enabled) recovery.save(true, park_raise, do_park);
  #endif

  // Wait for buffered blocks to complete
  planner.synchronize();

  #if ENABLED(ADVANCED_PAUSE_FANS_PAUSE) && HAS_FAN
>>>>>>> mcu_ctrl
    thermalManager.set_fans_paused(true);
  #endif

  // Initial retract before move to filament change position
<<<<<<< HEAD
  if (retract && thermalManager.hotEnoughToExtrude(active_extruder))
    do_pause_e_move(retract, PAUSE_PARK_RETRACT_FEEDRATE);

  // Park the nozzle by moving up by z_lift and then moving to (x_pos, y_pos)
  if (!axes_need_homing())
    nozzle.park(2, park_point);
=======
  if (retract && thermalManager.hotEnoughToExtrude(active_extruder)) {
    DEBUG_ECHOLNPAIR("... retract:", retract);
    unscaled_e_move(retract, PAUSE_PARK_RETRACT_FEEDRATE);
  }

  // If axes don't need to home then the nozzle can park
  if (do_park) nozzle.park(0, park_point); // Park the nozzle by doing a Minimum Z Raise followed by an XY Move
>>>>>>> mcu_ctrl

  #if ENABLED(DUAL_X_CARRIAGE)
    const int8_t saved_ext        = active_extruder;
    const bool saved_ext_dup_mode = extruder_duplication_enabled;
<<<<<<< HEAD
    active_extruder = DXC_ext;
    extruder_duplication_enabled = false;
  #endif

  if (unload_length)   // Unload the filament
    unload_filament(unload_length, show_lcd, PAUSE_MODE_CHANGE_FILAMENT);

  #if ENABLED(DUAL_X_CARRIAGE)
    active_extruder = saved_ext;
    extruder_duplication_enabled = saved_ext_dup_mode;
    stepper.set_directions();
  #endif

=======
    set_duplication_enabled(false, DXC_ext);
  #endif

  // Unload the filament, if specified
  if (unload_length)
    unload_filament(unload_length, show_lcd, PAUSE_MODE_CHANGE_FILAMENT);

  #if ENABLED(DUAL_X_CARRIAGE)
    set_duplication_enabled(saved_ext_dup_mode, saved_ext);
  #endif

  // Disable the Extruder for manual change
  disable_active_extruder();

>>>>>>> mcu_ctrl
  return true;
}

/**
 * For Paused Print:
 * - Show "Press button (or M108) to resume"
 *
 * For Filament Change:
 * - Show "Insert filament and press button to continue"
 *
 * - Wait for a click before returning
 * - Heaters can time out and must reheat before continuing
 *
 * Used by M125 and M600
 */

void show_continue_prompt(const bool is_reload) {
<<<<<<< HEAD
  #if HAS_LCD_MENU
    lcd_pause_show_message(is_reload ? PAUSE_MESSAGE_INSERT : PAUSE_MESSAGE_WAITING);
  #endif
  SERIAL_ECHO_START();
  serialprintPGM(is_reload ? PSTR(_PMSG(MSG_FILAMENT_CHANGE_INSERT) "\n") : PSTR(_PMSG(MSG_FILAMENT_CHANGE_WAIT) "\n"));
}

void wait_for_confirmation(const bool is_reload/*=false*/, const int8_t max_beep_count/*=0*/ DXC_ARGS) {
=======
  DEBUG_SECTION(scp, "pause_print", true);
  DEBUG_ECHOLNPAIR("... is_reload:", is_reload);

  ui.pause_show_message(is_reload ? PAUSE_MESSAGE_INSERT : PAUSE_MESSAGE_WAITING);
  SERIAL_ECHO_START();
  SERIAL_ECHOPGM_P(is_reload ? PSTR(_PMSG(STR_FILAMENT_CHANGE_INSERT) "\n") : PSTR(_PMSG(STR_FILAMENT_CHANGE_WAIT) "\n"));
}

void wait_for_confirmation(const bool is_reload/*=false*/, const int8_t max_beep_count/*=0*/ DXC_ARGS) {
  DEBUG_SECTION(wfc, "wait_for_confirmation", true);
  DEBUG_ECHOLNPAIR("... is_reload:", is_reload, " maxbeep:", max_beep_count DXC_SAY);

>>>>>>> mcu_ctrl
  bool nozzle_timed_out = false;

  show_continue_prompt(is_reload);

<<<<<<< HEAD
  #if HAS_BUZZER
    filament_change_beep(max_beep_count, true);
  #else
    UNUSED(max_beep_count);
  #endif

  // Start the heater idle timers
  const millis_t nozzle_timeout = (millis_t)(PAUSE_PARK_NOZZLE_TIMEOUT) * 1000UL;

  HOTEND_LOOP() thermalManager.hotend_idle[e].start(nozzle_timeout);
=======
  first_impatient_beep(max_beep_count);

  // Start the heater idle timers
  const millis_t nozzle_timeout = SEC_TO_MS(PAUSE_PARK_NOZZLE_TIMEOUT);

  HOTEND_LOOP() thermalManager.heater_idle[e].start(nozzle_timeout);
>>>>>>> mcu_ctrl

  #if ENABLED(DUAL_X_CARRIAGE)
    const int8_t saved_ext        = active_extruder;
    const bool saved_ext_dup_mode = extruder_duplication_enabled;
<<<<<<< HEAD
    active_extruder = DXC_ext;
    extruder_duplication_enabled = false;
=======
    set_duplication_enabled(false, DXC_ext);
>>>>>>> mcu_ctrl
  #endif

  // Wait for filament insert by user and press button
  KEEPALIVE_STATE(PAUSED_FOR_USER);
<<<<<<< HEAD
  wait_for_user = true;    // LCD click or M108 will clear this
  #if ENABLED(HOST_PROMPT_SUPPORT)
    host_prompt_do(PROMPT_USER_CONTINUE, PSTR("Nozzle Parked"), CONTINUE_STR);
  #endif
  #if ENABLED(EXTENSIBLE_UI)
    ExtUI::onUserConfirmRequired_P(PSTR("Nozzle Parked"));
  #endif
  while (wait_for_user) {
    #if HAS_BUZZER
      filament_change_beep(max_beep_count);
    #endif

    // If the nozzle has timed out...
    if (!nozzle_timed_out)
      HOTEND_LOOP() nozzle_timed_out |= thermalManager.hotend_idle[e].timed_out;
=======
  TERN_(HOST_PROMPT_SUPPORT, host_prompt_do(PROMPT_USER_CONTINUE, GET_TEXT(MSG_NOZZLE_PARKED), CONTINUE_STR));
  TERN_(EXTENSIBLE_UI, ExtUI::onUserConfirmRequired_P(GET_TEXT(MSG_NOZZLE_PARKED)));
  wait_for_user = true;    // LCD click or M108 will clear this
  while (wait_for_user) {
    impatient_beep(max_beep_count);

    // If the nozzle has timed out...
    if (!nozzle_timed_out)
      HOTEND_LOOP() nozzle_timed_out |= thermalManager.heater_idle[e].timed_out;
>>>>>>> mcu_ctrl

    // Wait for the user to press the button to re-heat the nozzle, then
    // re-heat the nozzle, re-show the continue prompt, restart idle timers, start over
    if (nozzle_timed_out) {
<<<<<<< HEAD
      #if HAS_LCD_MENU
        lcd_pause_show_message(PAUSE_MESSAGE_HEAT);
      #endif
      SERIAL_ECHO_MSG(_PMSG(MSG_FILAMENT_CHANGE_HEAT));

      #if ENABLED(HOST_PROMPT_SUPPORT)
        host_prompt_do(PROMPT_USER_CONTINUE, PSTR("HeaterTimeout"), PSTR("Reheat"));
      #endif

      #if ENABLED(EXTENSIBLE_UI)
        ExtUI::onUserConfirmRequired_P(PSTR("HeaterTimeout"));
      #endif

      // Wait for LCD click or M108
      while (wait_for_user) idle(true);

      #if ENABLED(HOST_PROMPT_SUPPORT)
        host_prompt_do(PROMPT_INFO, PSTR("Reheating"));
      #endif
      #if ENABLED(EXTENSIBLE_UI)
        ExtUI::onStatusChanged(PSTR("Reheating..."));
      #endif

      // Re-enable the heaters if they timed out
      HOTEND_LOOP() thermalManager.reset_heater_idle_timer(e);

      // Wait for the heaters to reach the target temperatures
      ensure_safe_temperature();
=======
      ui.pause_show_message(PAUSE_MESSAGE_HEAT);
      SERIAL_ECHO_MSG(_PMSG(STR_FILAMENT_CHANGE_HEAT));

      TERN_(HOST_PROMPT_SUPPORT, host_prompt_do(PROMPT_USER_CONTINUE, GET_TEXT(MSG_HEATER_TIMEOUT), GET_TEXT(MSG_REHEAT)));

      TERN_(EXTENSIBLE_UI, ExtUI::onUserConfirmRequired_P(GET_TEXT(MSG_HEATER_TIMEOUT)));

      wait_for_user_response(0, true); // Wait for LCD click or M108

      TERN_(HOST_PROMPT_SUPPORT, host_prompt_do(PROMPT_INFO, GET_TEXT(MSG_REHEATING)));

      TERN_(EXTENSIBLE_UI, ExtUI::onStatusChanged_P(GET_TEXT(MSG_REHEATING)));

      // Re-enable the heaters if they timed out
      HOTEND_LOOP() thermalManager.reset_hotend_idle_timer(e);

      // Wait for the heaters to reach the target temperatures
      ensure_safe_temperature(false);
>>>>>>> mcu_ctrl

      // Show the prompt to continue
      show_continue_prompt(is_reload);

      // Start the heater idle timers
<<<<<<< HEAD
      const millis_t nozzle_timeout = (millis_t)(PAUSE_PARK_NOZZLE_TIMEOUT) * 1000UL;

      HOTEND_LOOP() thermalManager.hotend_idle[e].start(nozzle_timeout);
      #if ENABLED(HOST_PROMPT_SUPPORT)
        host_prompt_do(PROMPT_USER_CONTINUE, PSTR("Reheat Done"), CONTINUE_STR);
      #endif
      #if ENABLED(EXTENSIBLE_UI)
        ExtUI::onUserConfirmRequired_P(PSTR("Reheat finished."));
      #endif
      wait_for_user = true;
      nozzle_timed_out = false;

      #if HAS_BUZZER
        filament_change_beep(max_beep_count, true);
      #endif
    }

    idle(true);
  }
  #if ENABLED(DUAL_X_CARRIAGE)
    active_extruder = saved_ext;
    extruder_duplication_enabled = saved_ext_dup_mode;
    stepper.set_directions();
=======
      const millis_t nozzle_timeout = SEC_TO_MS(PAUSE_PARK_NOZZLE_TIMEOUT);

      HOTEND_LOOP() thermalManager.heater_idle[e].start(nozzle_timeout);
      TERN_(HOST_PROMPT_SUPPORT, host_prompt_do(PROMPT_USER_CONTINUE, PSTR("Reheat Done"), CONTINUE_STR));
      TERN_(EXTENSIBLE_UI, ExtUI::onUserConfirmRequired_P(PSTR("Reheat finished.")));
      wait_for_user = true;
      nozzle_timed_out = false;

      first_impatient_beep(max_beep_count);
    }
    idle_no_sleep();
  }
  #if ENABLED(DUAL_X_CARRIAGE)
    set_duplication_enabled(saved_ext_dup_mode, saved_ext);
>>>>>>> mcu_ctrl
  #endif
}

/**
 * Resume or Start print procedure
 *
 * - If not paused, do nothing and return
 * - Reset heater idle timers
 * - Load filament if specified, but only if:
 *   - a nozzle timed out, or
 *   - the nozzle is already heated.
 * - Display "wait for print to resume"
<<<<<<< HEAD
=======
 * - Retract to prevent oozing
 * - Move the nozzle back to resume_position
 * - Unretract
>>>>>>> mcu_ctrl
 * - Re-prime the nozzle...
 *   -  FWRETRACT: Recover/prime from the prior G10.
 *   - !FWRETRACT: Retract by resume_position.e, if negative.
 *                 Not sure how this logic comes into use.
<<<<<<< HEAD
 * - Move the nozzle back to resume_position
=======
>>>>>>> mcu_ctrl
 * - Sync the planner E to resume_position.e
 * - Send host action for resume, if configured
 * - Resume the current SD print job, if any
 */
<<<<<<< HEAD
void resume_print(const float &slow_load_length/*=0*/, const float &fast_load_length/*=0*/, const float &purge_length/*=ADVANCED_PAUSE_PURGE_LENGTH*/, const int8_t max_beep_count/*=0*/ DXC_ARGS) {
=======
void resume_print(const_float_t slow_load_length/*=0*/, const_float_t fast_load_length/*=0*/, const_float_t purge_length/*=ADVANCED_PAUSE_PURGE_LENGTH*/, const int8_t max_beep_count/*=0*/, const celsius_t targetTemp/*=0*/ DXC_ARGS) {
  DEBUG_SECTION(rp, "resume_print", true);
  DEBUG_ECHOLNPAIR("... slowlen:", slow_load_length, " fastlen:", fast_load_length, " purgelen:", purge_length, " maxbeep:", max_beep_count, " targetTemp:", targetTemp DXC_SAY);

>>>>>>> mcu_ctrl
  /*
  SERIAL_ECHOLNPAIR(
    "start of resume_print()\ndual_x_carriage_mode:", dual_x_carriage_mode,
    "\nextruder_duplication_enabled:", extruder_duplication_enabled,
    "\nactive_extruder:", active_extruder,
    "\n"
  );
  //*/

  if (!did_pause_print) return;

  // Re-enable the heaters if they timed out
  bool nozzle_timed_out = false;
  HOTEND_LOOP() {
<<<<<<< HEAD
    nozzle_timed_out |= thermalManager.hotend_idle[e].timed_out;
    thermalManager.reset_heater_idle_timer(e);
  }

  if (nozzle_timed_out || thermalManager.hotEnoughToExtrude(active_extruder)) // Load the new filament
    load_filament(slow_load_length, fast_load_length, purge_length, max_beep_count, true, nozzle_timed_out, PAUSE_MODE_SAME DXC_PASS);

  #if HAS_LCD_MENU
    lcd_pause_show_message(PAUSE_MESSAGE_RESUME);
  #endif
=======
    nozzle_timed_out |= thermalManager.heater_idle[e].timed_out;
    thermalManager.reset_hotend_idle_timer(e);
  }

  if (targetTemp > thermalManager.degTargetHotend(active_extruder))
    thermalManager.setTargetHotend(targetTemp, active_extruder);

  // Load the new filament
  load_filament(slow_load_length, fast_load_length, purge_length, max_beep_count, true, nozzle_timed_out, PAUSE_MODE_SAME DXC_PASS);

  if (targetTemp > 0) {
    thermalManager.setTargetHotend(targetTemp, active_extruder);
    thermalManager.wait_for_hotend(active_extruder, false);
  }

  ui.pause_show_message(PAUSE_MESSAGE_RESUME);

  // Check Temperature before moving hotend
  ensure_safe_temperature();

  // Retract to prevent oozing
  unscaled_e_move(-(PAUSE_PARK_RETRACT_LENGTH), feedRate_t(PAUSE_PARK_RETRACT_FEEDRATE));

  if (!axes_should_home()) {
    // Move XY back to saved position
    destination.set(resume_position.x, resume_position.y, current_position.z, current_position.e);
    prepare_internal_move_to_destination(NOZZLE_PARK_XY_FEEDRATE);

    // Move Z back to saved position
    destination.z = resume_position.z;
    prepare_internal_move_to_destination(NOZZLE_PARK_Z_FEEDRATE);
  }

  // Unretract
  unscaled_e_move(PAUSE_PARK_RETRACT_LENGTH, feedRate_t(PAUSE_PARK_RETRACT_FEEDRATE));
>>>>>>> mcu_ctrl

  // Intelligent resuming
  #if ENABLED(FWRETRACT)
    // If retracted before goto pause
    if (fwretract.retracted[active_extruder])
<<<<<<< HEAD
      do_pause_e_move(-fwretract.settings.retract_length, fwretract.settings.retract_feedrate_mm_s);
  #endif

  // If resume_position is negative
  if (resume_position.e < 0) do_pause_e_move(resume_position.e, feedRate_t(PAUSE_PARK_RETRACT_FEEDRATE));

  // Move XY to starting position, then Z
  do_blocking_move_to_xy(resume_position, feedRate_t(NOZZLE_PARK_XY_FEEDRATE));

  // Move Z_AXIS to saved position
  do_blocking_move_to_z(resume_position.z, feedRate_t(NOZZLE_PARK_Z_FEEDRATE));

  #if ADVANCED_PAUSE_RESUME_PRIME != 0
    do_pause_e_move(ADVANCED_PAUSE_RESUME_PRIME, feedRate_t(ADVANCED_PAUSE_PURGE_FEEDRATE));
=======
      unscaled_e_move(-fwretract.settings.retract_length, fwretract.settings.retract_feedrate_mm_s);
  #endif

  // If resume_position is negative
  if (resume_position.e < 0) unscaled_e_move(resume_position.e, feedRate_t(PAUSE_PARK_RETRACT_FEEDRATE));
  #if ADVANCED_PAUSE_RESUME_PRIME != 0
    unscaled_e_move(ADVANCED_PAUSE_RESUME_PRIME, feedRate_t(ADVANCED_PAUSE_PURGE_FEEDRATE));
>>>>>>> mcu_ctrl
  #endif

  // Now all extrusion positions are resumed and ready to be confirmed
  // Set extruder to saved position
  planner.set_e_position_mm((destination.e = current_position.e = resume_position.e));

<<<<<<< HEAD
  #if HAS_LCD_MENU
    lcd_pause_show_message(PAUSE_MESSAGE_STATUS);
  #endif
=======
  ui.pause_show_message(PAUSE_MESSAGE_STATUS);
>>>>>>> mcu_ctrl

  #ifdef ACTION_ON_RESUMED
    host_action_resumed();
  #elif defined(ACTION_ON_RESUME)
    host_action_resume();
  #endif

  --did_pause_print;

<<<<<<< HEAD
  #if ENABLED(HOST_PROMPT_SUPPORT)
    host_prompt_open(PROMPT_INFO, PSTR("Resuming"), PSTR("Dismiss"));
  #endif

  #if ENABLED(SDSUPPORT)
    if (did_pause_print) {
      card.startFileprint();
      --did_pause_print;
    }
  #endif

  #if ENABLED(ADVANCED_PAUSE_FANS_PAUSE) && FAN_COUNT > 0
    thermalManager.set_fans_paused(false);
  #endif

  // Resume the print job timer if it was running
  if (print_job_timer.isPaused()) print_job_timer.start();

  #if HAS_DISPLAY
    ui.reset_status();
    #if HAS_LCD_MENU
      ui.return_to_status();
    #endif
  #endif
=======
  TERN_(HOST_PROMPT_SUPPORT, host_prompt_open(PROMPT_INFO, PSTR("Resuming"), DISMISS_STR));

  // Resume the print job timer if it was running
  if (print_job_timer.isPaused()) print_job_timer.start();

  #if ENABLED(SDSUPPORT)
    if (did_pause_print) {
      --did_pause_print;
      card.startOrResumeFilePrinting();
      // Write PLR now to update the z axis value
      TERN_(POWER_LOSS_RECOVERY, if (recovery.enabled) recovery.save(true));
    }
  #endif

  #if ENABLED(ADVANCED_PAUSE_FANS_PAUSE) && HAS_FAN
    thermalManager.set_fans_paused(false);
  #endif

  TERN_(HAS_FILAMENT_SENSOR, runout.reset());

  TERN_(HAS_STATUS_MESSAGE, ui.reset_status());
  TERN_(HAS_LCD_MENU, ui.return_to_status());
>>>>>>> mcu_ctrl
}

#endif // ADVANCED_PAUSE_FEATURE
