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

#include "stopwatch.h"

#include "../inc/MarlinConfig.h"

#if ENABLED(EXTENSIBLE_UI)
<<<<<<< HEAD
  #include "../lcd/extensible_ui/ui_api.h"
=======
  #include "../lcd/extui/ui_api.h"
>>>>>>> mcu_ctrl
#endif

Stopwatch::State Stopwatch::state;
millis_t Stopwatch::accumulator;
millis_t Stopwatch::startTimestamp;
millis_t Stopwatch::stopTimestamp;

bool Stopwatch::stop() {
<<<<<<< HEAD
  #if ENABLED(DEBUG_STOPWATCH)
    Stopwatch::debug(PSTR("stop"));
  #endif

  if (isRunning() || isPaused()) {
    #if ENABLED(EXTENSIBLE_UI)
      ExtUI::onPrintTimerStopped();
    #endif
=======
  Stopwatch::debug(PSTR("stop"));

  if (isRunning() || isPaused()) {
    TERN_(EXTENSIBLE_UI, ExtUI::onPrintTimerStopped());
>>>>>>> mcu_ctrl
    state = STOPPED;
    stopTimestamp = millis();
    return true;
  }
  else return false;
}

bool Stopwatch::pause() {
<<<<<<< HEAD
  #if ENABLED(DEBUG_STOPWATCH)
    Stopwatch::debug(PSTR("pause"));
  #endif

  if (isRunning()) {
    #if ENABLED(EXTENSIBLE_UI)
      ExtUI::onPrintTimerPaused();
    #endif
=======
  Stopwatch::debug(PSTR("pause"));

  if (isRunning()) {
    TERN_(EXTENSIBLE_UI, ExtUI::onPrintTimerPaused());
>>>>>>> mcu_ctrl
    state = PAUSED;
    stopTimestamp = millis();
    return true;
  }
  else return false;
}

bool Stopwatch::start() {
<<<<<<< HEAD
  #if ENABLED(DEBUG_STOPWATCH)
    Stopwatch::debug(PSTR("start"));
  #endif

  #if ENABLED(EXTENSIBLE_UI)
    ExtUI::onPrintTimerStarted();
  #endif
=======
  Stopwatch::debug(PSTR("start"));

  TERN_(EXTENSIBLE_UI, ExtUI::onPrintTimerStarted());
>>>>>>> mcu_ctrl

  if (!isRunning()) {
    if (isPaused()) accumulator = duration();
    else reset();

    state = RUNNING;
    startTimestamp = millis();
    return true;
  }
  else return false;
}

void Stopwatch::resume(const millis_t with_time) {
<<<<<<< HEAD
  #if ENABLED(DEBUG_STOPWATCH)
    Stopwatch::debug(PSTR("resume"));
  #endif
=======
  Stopwatch::debug(PSTR("resume"));
>>>>>>> mcu_ctrl

  reset();
  if ((accumulator = with_time)) state = RUNNING;
}

void Stopwatch::reset() {
<<<<<<< HEAD
  #if ENABLED(DEBUG_STOPWATCH)
    Stopwatch::debug(PSTR("reset"));
  #endif
=======
  Stopwatch::debug(PSTR("reset"));
>>>>>>> mcu_ctrl

  state = STOPPED;
  startTimestamp = 0;
  stopTimestamp = 0;
  accumulator = 0;
}

millis_t Stopwatch::duration() {
<<<<<<< HEAD
  return ((isRunning() ? millis() : stopTimestamp)
          - startTimestamp) / 1000UL + accumulator;
=======
  return accumulator + MS_TO_SEC((isRunning() ? millis() : stopTimestamp) - startTimestamp);
>>>>>>> mcu_ctrl
}

#if ENABLED(DEBUG_STOPWATCH)

  void Stopwatch::debug(const char func[]) {
    if (DEBUGGING(INFO)) {
      SERIAL_ECHOPGM("Stopwatch::");
<<<<<<< HEAD
      serialprintPGM(func);
=======
      SERIAL_ECHOPGM_P(func);
>>>>>>> mcu_ctrl
      SERIAL_ECHOLNPGM("()");
    }
  }

#endif
