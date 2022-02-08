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
 *
 */

#include "../../inc/MarlinConfig.h"
#include "../../module/printcounter.h"

#if HAS_RESUME_CONTINUE

#include "../gcode.h"
#include "../../module/stepper.h"

#if HAS_LCD_MENU
  #include "../../lcd/ultralcd.h"
#endif

#ifdef RTS_AVAILABLE
  #include "../../lcd/dwin/LCD_RTS.h"
#endif

#if ENABLED(EXTENSIBLE_UI)
  #include "../../lcd/extensible_ui/ui_api.h"
#endif

#include "../../sd/cardreader.h"

#if HAS_LEDS_OFF_FLAG
  #include "../../feature/leds/printer_event_leds.h"
=======
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "../../inc/MarlinConfigPre.h"

#if HAS_RESUME_CONTINUE

#include "../../inc/MarlinConfig.h"

#include "../gcode.h"

#include "../../module/planner.h" // for synchronize()
#include "../../MarlinCore.h"     // for wait_for_user_response()

#if HAS_LCD_MENU
  #include "../../lcd/marlinui.h"
#elif ENABLED(EXTENSIBLE_UI)
  #include "../../lcd/extui/ui_api.h"
>>>>>>> mcu_ctrl
#endif

#if ENABLED(HOST_PROMPT_SUPPORT)
  #include "../../feature/host_actions.h"
#endif

/**
 * M0: Unconditional stop - Wait for user button press on LCD
 * M1: Conditional stop   - Wait for user button press on LCD
 */
void GcodeSuite::M0_M1() {
<<<<<<< HEAD

  #ifdef RTS_AVAILABLE
    if(printingIsActive())
    {
      if(language_change_font != 0)
      {
        rtscheck.RTS_SndData(ExchangePageBase + 12, ExchangepageAddr);
        change_page_font = 12;
      }
      // card.pauseSDPrint();
      // print_job_timer.pause();
      // pause_action_flag = true;  
    }  
  #endif

  const char * const args = parser.string_arg;

  millis_t ms = 0;
  bool hasP = false, hasS = false;
  if (parser.seenval('P')) {
    ms = parser.value_millis(); // milliseconds to wait
    hasP = ms > 0;
  }
  if (parser.seenval('S')) {
    ms = parser.value_millis_from_seconds(); // seconds to wait
    hasS = ms > 0;
  }

  const bool has_message = !hasP && !hasS && args && *args;
=======
  millis_t ms = 0;
  if (parser.seenval('P')) ms = parser.value_millis();              // Milliseconds to wait
  if (parser.seenval('S')) ms = parser.value_millis_from_seconds(); // Seconds to wait
>>>>>>> mcu_ctrl

  planner.synchronize();

  #if HAS_LCD_MENU

<<<<<<< HEAD
    if (has_message)
      ui.set_status(args, true);
=======
    if (parser.string_arg)
      ui.set_status(parser.string_arg, true);
>>>>>>> mcu_ctrl
    else {
      LCD_MESSAGEPGM(MSG_USERWAIT);
      #if ENABLED(LCD_PROGRESS_BAR) && PROGRESS_MSG_EXPIRE > 0
        ui.reset_progress_bar_timeout();
      #endif
    }

  #elif ENABLED(EXTENSIBLE_UI)
<<<<<<< HEAD

    if (has_message)
      ExtUI::onUserConfirmRequired(args); // Can this take an SRAM string??
    else
      ExtUI::onUserConfirmRequired_P(GET_TEXT(MSG_USERWAIT));

  #else

    if (has_message) {
      SERIAL_ECHO_START();
      SERIAL_ECHOLN(args);
=======
    if (parser.string_arg)
      ExtUI::onUserConfirmRequired(parser.string_arg); // Can this take an SRAM string??
    else
      ExtUI::onUserConfirmRequired_P(GET_TEXT(MSG_USERWAIT));
  #else

    if (parser.string_arg) {
      SERIAL_ECHO_START();
      SERIAL_ECHOLN(parser.string_arg);
>>>>>>> mcu_ctrl
    }

  #endif

<<<<<<< HEAD
  KEEPALIVE_STATE(PAUSED_FOR_USER);
  wait_for_user = true;

  #if ENABLED(HOST_PROMPT_SUPPORT)
    host_prompt_do(PROMPT_USER_CONTINUE, PSTR("M0/1 Break Called"), CONTINUE_STR);
  #endif

  if (ms > 0) {
    ms += millis();  // wait until this time for a click
    while (PENDING(millis(), ms) && wait_for_user) idle();
  }
  else
    while (wait_for_user) idle();

  #if HAS_LEDS_OFF_FLAG
    printerEventLEDs.onResumeAfterWait();
  #endif

  #if HAS_LCD_MENU
    ui.reset_status();
  #endif

  wait_for_user = false;
=======
  TERN_(HOST_PROMPT_SUPPORT, host_prompt_do(PROMPT_USER_CONTINUE, parser.codenum ? PSTR("M1 Stop") : PSTR("M0 Stop"), CONTINUE_STR));

  wait_for_user_response(ms);

  TERN_(HAS_LCD_MENU, ui.reset_status());
>>>>>>> mcu_ctrl
}

#endif // HAS_RESUME_CONTINUE
