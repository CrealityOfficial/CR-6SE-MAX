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

#include "../inc/MarlinConfig.h"

#if ENABLED(HOST_ACTION_COMMANDS)

#include "host_actions.h"

//#define DEBUG_HOST_ACTIONS

#if ENABLED(ADVANCED_PAUSE_FEATURE)
  #include "pause.h"
  #include "../gcode/queue.h"
#endif

#if HAS_FILAMENT_SENSOR
  #include "runout.h"
#endif

<<<<<<< HEAD
void host_action(const char * const pstr, const bool eol) {
  SERIAL_ECHOPGM("//action:");
  serialprintPGM(pstr);
=======
void host_action(PGM_P const pstr, const bool eol) {
  PORT_REDIRECT(SerialMask::All);
  SERIAL_ECHOPGM("//action:");
  SERIAL_ECHOPGM_P(pstr);
>>>>>>> mcu_ctrl
  if (eol) SERIAL_EOL();
}

#ifdef ACTION_ON_KILL
  void host_action_kill() { host_action(PSTR(ACTION_ON_KILL)); }
#endif
#ifdef ACTION_ON_PAUSE
  void host_action_pause(const bool eol/*=true*/) { host_action(PSTR(ACTION_ON_PAUSE), eol); }
#endif
#ifdef ACTION_ON_PAUSED
  void host_action_paused(const bool eol/*=true*/) { host_action(PSTR(ACTION_ON_PAUSED), eol); }
#endif
#ifdef ACTION_ON_RESUME
  void host_action_resume() { host_action(PSTR(ACTION_ON_RESUME)); }
#endif
#ifdef ACTION_ON_RESUMED
  void host_action_resumed() { host_action(PSTR(ACTION_ON_RESUMED)); }
#endif
#ifdef ACTION_ON_CANCEL
  void host_action_cancel() { host_action(PSTR(ACTION_ON_CANCEL)); }
#endif
<<<<<<< HEAD

#if ENABLED(HOST_PROMPT_SUPPORT)

  const char CONTINUE_STR[] PROGMEM = "Continue";
=======
#ifdef ACTION_ON_START
  void host_action_start() { host_action(PSTR(ACTION_ON_START)); }
#endif

#if ENABLED(HOST_PROMPT_SUPPORT)

  PGMSTR(CONTINUE_STR, "Continue");
  PGMSTR(DISMISS_STR, "Dismiss");
>>>>>>> mcu_ctrl

  #if HAS_RESUME_CONTINUE
    extern bool wait_for_user;
  #endif

  PromptReason host_prompt_reason = PROMPT_NOT_DEFINED;

<<<<<<< HEAD
  void host_action_prompt(const char * const ptype, const bool eol=true) {
    host_action(PSTR("prompt_"), false);
    serialprintPGM(ptype);
    if (eol) SERIAL_EOL();
  }

  void host_action_prompt_plus(const char * const ptype, const char * const pstr, const bool eol=true) {
    host_action_prompt(ptype, false);
    SERIAL_CHAR(' ');
    serialprintPGM(pstr);
    if (eol) SERIAL_EOL();
  }
  void host_action_prompt_begin(const char * const pstr, const bool eol/*=true*/) { host_action_prompt_plus(PSTR("begin"), pstr, eol); }
  void host_action_prompt_button(const char * const pstr) { host_action_prompt_plus(PSTR("button"), pstr); }
  void host_action_prompt_end() { host_action_prompt(PSTR("end")); }
  void host_action_prompt_show() { host_action_prompt(PSTR("show")); }
  void host_prompt_do(const PromptReason reason, const char * const pstr, const char * const pbtn/*=nullptr*/) {
    host_prompt_reason = reason;
    host_action_prompt_end();
    host_action_prompt_begin(pstr);
    if (pbtn) host_action_prompt_button(pbtn);
    host_action_prompt_show();
  }

  inline void say_m876_response(const char * const pstr) {
    SERIAL_ECHOPGM("M876 Responding PROMPT_");
    serialprintPGM(pstr);
    SERIAL_EOL();
  }

  void host_response_handler(const uint8_t response) {
    #ifdef DEBUG_HOST_ACTIONS
      SERIAL_ECHOLNPAIR("M876 Handle Reason: ", host_prompt_reason);
      SERIAL_ECHOLNPAIR("M876 Handle Response: ", response);
    #endif
    const char *msg = PSTR("UNKNOWN STATE");
    const PromptReason hpr = host_prompt_reason;
    host_prompt_reason = PROMPT_NOT_DEFINED;
    switch (hpr) {
      case PROMPT_FILAMENT_RUNOUT:
        msg = PSTR("FILAMENT_RUNOUT");
        if (response == 0) {
          #if ENABLED(ADVANCED_PAUSE_FEATURE)
            pause_menu_response = PAUSE_RESPONSE_EXTRUDE_MORE;
          #endif
          host_action_prompt_end();   // Close current prompt
          host_action_prompt_begin(PSTR("Paused"));
          host_action_prompt_button(PSTR("Purge More"));
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
        }
        else if (response == 1) {
          #if HAS_FILAMENT_SENSOR
            if (runout.filament_ran_out) {
              runout.enabled = false;
              runout.reset();
            }
          #endif
          #if ENABLED(ADVANCED_PAUSE_FEATURE)
            pause_menu_response = PAUSE_RESPONSE_RESUME_PRINT;
          #endif
        }
        break;
      case PROMPT_USER_CONTINUE:
        #if HAS_RESUME_CONTINUE
          wait_for_user = false;
        #endif
        msg = PSTR("FILAMENT_RUNOUT_CONTINUE");
        break;
      case PROMPT_PAUSE_RESUME:
        msg = PSTR("LCD_PAUSE_RESUME");
        #if ENABLED(ADVANCED_PAUSE_FEATURE)
=======
  void host_action_notify(const char * const message) {
    PORT_REDIRECT(SerialMask::All);
    host_action(PSTR("notification "), false);
    SERIAL_ECHOLN(message);
  }

  void host_action_notify_P(PGM_P const message) {
    PORT_REDIRECT(SerialMask::All);
    host_action(PSTR("notification "), false);
    SERIAL_ECHOLNPGM_P(message);
  }

  void host_action_prompt(PGM_P const ptype, const bool eol=true) {
    PORT_REDIRECT(SerialMask::All);
    host_action(PSTR("prompt_"), false);
    SERIAL_ECHOPGM_P(ptype);
    if (eol) SERIAL_EOL();
  }

  void host_action_prompt_plus(PGM_P const ptype, PGM_P const pstr, const char extra_char='\0') {
    host_action_prompt(ptype, false);
    PORT_REDIRECT(SerialMask::All);
    SERIAL_CHAR(' ');
    SERIAL_ECHOPGM_P(pstr);
    if (extra_char != '\0') SERIAL_CHAR(extra_char);
    SERIAL_EOL();
  }
  void host_action_prompt_begin(const PromptReason reason, PGM_P const pstr, const char extra_char/*='\0'*/) {
    host_action_prompt_end();
    host_prompt_reason = reason;
    host_action_prompt_plus(PSTR("begin"), pstr, extra_char);
  }
  void host_action_prompt_button(PGM_P const pstr) { host_action_prompt_plus(PSTR("button"), pstr); }
  void host_action_prompt_end() { host_action_prompt(PSTR("end")); }
  void host_action_prompt_show() { host_action_prompt(PSTR("show")); }

  void _host_prompt_show(PGM_P const btn1/*=nullptr*/, PGM_P const btn2/*=nullptr*/) {
    if (btn1) host_action_prompt_button(btn1);
    if (btn2) host_action_prompt_button(btn2);
    host_action_prompt_show();
  }
  void host_prompt_do(const PromptReason reason, PGM_P const pstr, PGM_P const btn1/*=nullptr*/, PGM_P const btn2/*=nullptr*/) {
    host_action_prompt_begin(reason, pstr);
    _host_prompt_show(btn1, btn2);
  }
  void host_prompt_do(const PromptReason reason, PGM_P const pstr, const char extra_char, PGM_P const btn1/*=nullptr*/, PGM_P const btn2/*=nullptr*/) {
    host_action_prompt_begin(reason, pstr, extra_char);
    _host_prompt_show(btn1, btn2);
  }

  void filament_load_host_prompt() {
    const bool disable_to_continue = TERN0(HAS_FILAMENT_SENSOR, runout.filament_ran_out);
    host_prompt_do(PROMPT_FILAMENT_RUNOUT, PSTR("Paused"), PSTR("PurgeMore"),
      disable_to_continue ? PSTR("DisableRunout") : CONTINUE_STR
    );
  }

  //
  // Handle responses from the host, such as:
  //  - Filament runout responses: Purge More, Continue
  //  - General "Continue" response
  //  - Resume Print response
  //  - Dismissal of info
  //
  void host_response_handler(const uint8_t response) {
    const PromptReason hpr = host_prompt_reason;
    host_prompt_reason = PROMPT_NOT_DEFINED;  // Reset now ahead of logic
    switch (hpr) {
      case PROMPT_FILAMENT_RUNOUT:
        switch (response) {

          case 0: // "Purge More" button
            #if BOTH(M600_PURGE_MORE_RESUMABLE, ADVANCED_PAUSE_FEATURE)
              pause_menu_response = PAUSE_RESPONSE_EXTRUDE_MORE;  // Simulate menu selection (menu exits, doesn't extrude more)
            #endif
            break;

          case 1: // "Continue" / "Disable Runout" button
            #if BOTH(M600_PURGE_MORE_RESUMABLE, ADVANCED_PAUSE_FEATURE)
              pause_menu_response = PAUSE_RESPONSE_RESUME_PRINT;  // Simulate menu selection
            #endif
            #if HAS_FILAMENT_SENSOR
              if (runout.filament_ran_out) {                      // Disable a triggered sensor
                runout.enabled = false;
                runout.reset();
              }
            #endif
            break;
        }
        break;
      case PROMPT_USER_CONTINUE:
        TERN_(HAS_RESUME_CONTINUE, wait_for_user = false);
        break;
      case PROMPT_PAUSE_RESUME:
        #if BOTH(ADVANCED_PAUSE_FEATURE, SDSUPPORT)
>>>>>>> mcu_ctrl
          extern const char M24_STR[];
          queue.inject_P(M24_STR);
        #endif
        break;
      case PROMPT_INFO:
<<<<<<< HEAD
        msg = PSTR("GCODE_INFO");
        break;
      default: break;
    }
    say_m876_response(msg);
=======
        break;
      default: break;
    }
>>>>>>> mcu_ctrl
  }

#endif // HOST_PROMPT_SUPPORT

#endif // HOST_ACTION_COMMANDS
