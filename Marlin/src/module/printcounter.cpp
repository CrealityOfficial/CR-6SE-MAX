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

#if DISABLED(PRINTCOUNTER)

#include "../libs/stopwatch.h"
Stopwatch print_job_timer;      // Global Print Job Timer instance

#else // PRINTCOUNTER

#if ENABLED(EXTENSIBLE_UI)
<<<<<<< HEAD
  #include "../lcd/extensible_ui/ui_api.h"
#endif

#include "printcounter.h"
#include "../Marlin.h"
#include "../HAL/shared/persistent_store_api.h"
=======
  #include "../lcd/extui/ui_api.h"
#endif

#include "printcounter.h"
#include "../MarlinCore.h"
#include "../HAL/shared/eeprom_api.h"
>>>>>>> mcu_ctrl

#if HAS_BUZZER && SERVICE_WARNING_BUZZES > 0
  #include "../libs/buzzer.h"
#endif

<<<<<<< HEAD
=======
#if PRINTCOUNTER_SYNC
  #include "../module/planner.h"
  #warning "To prevent step loss, motion will pause for PRINTCOUNTER auto-save."
#endif

>>>>>>> mcu_ctrl
// Service intervals
#if HAS_SERVICE_INTERVALS
  #if SERVICE_INTERVAL_1 > 0
    #define SERVICE_INTERVAL_SEC_1   (3600UL * SERVICE_INTERVAL_1)
  #else
    #define SERVICE_INTERVAL_SEC_1   (3600UL * 100)
  #endif
  #if SERVICE_INTERVAL_2 > 0
    #define SERVICE_INTERVAL_SEC_2   (3600UL * SERVICE_INTERVAL_2)
  #else
    #define SERVICE_INTERVAL_SEC_2   (3600UL * 100)
  #endif
  #if SERVICE_INTERVAL_3 > 0
    #define SERVICE_INTERVAL_SEC_3   (3600UL * SERVICE_INTERVAL_3)
  #else
    #define SERVICE_INTERVAL_SEC_3   (3600UL * 100)
  #endif
#endif

PrintCounter print_job_timer;   // Global Print Job Timer instance

printStatistics PrintCounter::data;

const PrintCounter::eeprom_address_t PrintCounter::address = STATS_EEPROM_ADDRESS;

millis_t PrintCounter::lastDuration;
bool PrintCounter::loaded = false;

millis_t PrintCounter::deltaDuration() {
<<<<<<< HEAD
  #if ENABLED(DEBUG_PRINTCOUNTER)
    debug(PSTR("deltaDuration"));
  #endif

=======
  TERN_(DEBUG_PRINTCOUNTER, debug(PSTR("deltaDuration")));
>>>>>>> mcu_ctrl
  millis_t tmp = lastDuration;
  lastDuration = duration();
  return lastDuration - tmp;
}

void PrintCounter::incFilamentUsed(float const &amount) {
<<<<<<< HEAD
  #if ENABLED(DEBUG_PRINTCOUNTER)
    debug(PSTR("incFilamentUsed"));
  #endif
=======
  TERN_(DEBUG_PRINTCOUNTER, debug(PSTR("incFilamentUsed")));
>>>>>>> mcu_ctrl

  // Refuses to update data if object is not loaded
  if (!isLoaded()) return;

  data.filamentUsed += amount; // mm
}

void PrintCounter::initStats() {
<<<<<<< HEAD
  #if ENABLED(DEBUG_PRINTCOUNTER)
    debug(PSTR("initStats"));
  #endif
=======
  TERN_(DEBUG_PRINTCOUNTER, debug(PSTR("initStats")));
>>>>>>> mcu_ctrl

  loaded = true;
  data = { 0, 0, 0, 0, 0.0
    #if HAS_SERVICE_INTERVALS
      #if SERVICE_INTERVAL_1 > 0
        , SERVICE_INTERVAL_SEC_1
      #endif
      #if SERVICE_INTERVAL_2 > 0
        , SERVICE_INTERVAL_SEC_2
      #endif
      #if SERVICE_INTERVAL_3 > 0
        , SERVICE_INTERVAL_SEC_3
      #endif
    #endif
  };

  saveStats();
  persistentStore.access_start();
  persistentStore.write_data(address, (uint8_t)0x16);
  persistentStore.access_finish();
}

#if HAS_SERVICE_INTERVALS
  inline void _print_divider() { SERIAL_ECHO_MSG("============================================="); }
  inline bool _service_warn(const char * const msg) {
    _print_divider();
    SERIAL_ECHO_START();
<<<<<<< HEAD
    serialprintPGM(msg);
=======
    SERIAL_ECHOPGM_P(msg);
>>>>>>> mcu_ctrl
    SERIAL_ECHOLNPGM("!");
    _print_divider();
    return true;
  }
#endif

void PrintCounter::loadStats() {
<<<<<<< HEAD
  #if ENABLED(DEBUG_PRINTCOUNTER)
    debug(PSTR("loadStats"));
  #endif
=======
  TERN_(DEBUG_PRINTCOUNTER, debug(PSTR("loadStats")));
>>>>>>> mcu_ctrl

  // Check if the EEPROM block is initialized
  uint8_t value = 0;
  persistentStore.access_start();
  persistentStore.read_data(address, &value, sizeof(uint8_t));
  if (value != 0x16)
    initStats();
  else
    persistentStore.read_data(address + sizeof(uint8_t), (uint8_t*)&data, sizeof(printStatistics));
  persistentStore.access_finish();
  loaded = true;

  #if HAS_SERVICE_INTERVALS
    bool doBuzz = false;
    #if SERVICE_INTERVAL_1 > 0
      if (data.nextService1 == 0) doBuzz = _service_warn(PSTR(" " SERVICE_NAME_1));
    #endif
    #if SERVICE_INTERVAL_2 > 0
      if (data.nextService2 == 0) doBuzz = _service_warn(PSTR(" " SERVICE_NAME_2));
    #endif
    #if SERVICE_INTERVAL_3 > 0
      if (data.nextService3 == 0) doBuzz = _service_warn(PSTR(" " SERVICE_NAME_3));
    #endif
    #if HAS_BUZZER && SERVICE_WARNING_BUZZES > 0
      if (doBuzz) for (int i = 0; i < SERVICE_WARNING_BUZZES; i++) BUZZ(200, 404);
    #else
      UNUSED(doBuzz);
    #endif
  #endif // HAS_SERVICE_INTERVALS
}

void PrintCounter::saveStats() {
<<<<<<< HEAD
  #if ENABLED(DEBUG_PRINTCOUNTER)
    debug(PSTR("saveStats"));
  #endif
=======
  TERN_(DEBUG_PRINTCOUNTER, debug(PSTR("saveStats")));
>>>>>>> mcu_ctrl

  // Refuses to save data if object is not loaded
  if (!isLoaded()) return;

<<<<<<< HEAD
=======
  TERN_(PRINTCOUNTER_SYNC, planner.synchronize());

>>>>>>> mcu_ctrl
  // Saves the struct to EEPROM
  persistentStore.access_start();
  persistentStore.write_data(address + sizeof(uint8_t), (uint8_t*)&data, sizeof(printStatistics));
  persistentStore.access_finish();

<<<<<<< HEAD
  #if ENABLED(EXTENSIBLE_UI)
    ExtUI::onConfigurationStoreWritten(true);
  #endif
=======
  TERN_(EXTENSIBLE_UI, ExtUI::onConfigurationStoreWritten(true));
>>>>>>> mcu_ctrl
}

#if HAS_SERVICE_INTERVALS
  inline void _service_when(char buffer[], const char * const msg, const uint32_t when) {
<<<<<<< HEAD
    SERIAL_ECHOPGM(MSG_STATS);
    serialprintPGM(msg);
=======
    SERIAL_ECHOPGM(STR_STATS);
    SERIAL_ECHOPGM_P(msg);
>>>>>>> mcu_ctrl
    SERIAL_ECHOLNPAIR(" in ", duration_t(when).toString(buffer));
  }
#endif

void PrintCounter::showStats() {
<<<<<<< HEAD
  char buffer[21];

  SERIAL_ECHOPGM(MSG_STATS);
=======
  char buffer[22];

  SERIAL_ECHOPGM(STR_STATS);
>>>>>>> mcu_ctrl
  SERIAL_ECHOLNPAIR(
    "Prints: ", data.totalPrints,
    ", Finished: ", data.finishedPrints,
    ", Failed: ", data.totalPrints - data.finishedPrints
                    - ((isRunning() || isPaused()) ? 1 : 0) // Remove 1 from failures with an active counter
  );

<<<<<<< HEAD
  SERIAL_ECHOPGM(MSG_STATS);
=======
  SERIAL_ECHOPGM(STR_STATS);
>>>>>>> mcu_ctrl
  duration_t elapsed = data.printTime;
  elapsed.toString(buffer);
  SERIAL_ECHOPAIR("Total time: ", buffer);
  #if ENABLED(DEBUG_PRINTCOUNTER)
    SERIAL_ECHOPAIR(" (", data.printTime);
    SERIAL_CHAR(')');
  #endif

  elapsed = data.longestPrint;
  elapsed.toString(buffer);
  SERIAL_ECHOPAIR(", Longest job: ", buffer);
  #if ENABLED(DEBUG_PRINTCOUNTER)
    SERIAL_ECHOPAIR(" (", data.longestPrint);
    SERIAL_CHAR(')');
  #endif

<<<<<<< HEAD
  SERIAL_ECHOPAIR("\n" MSG_STATS "Filament used: ", data.filamentUsed / 1000);
=======
  SERIAL_ECHOPAIR("\n" STR_STATS "Filament used: ", data.filamentUsed / 1000);
>>>>>>> mcu_ctrl
  SERIAL_CHAR('m');
  SERIAL_EOL();

  #if SERVICE_INTERVAL_1 > 0
    _service_when(buffer, PSTR(SERVICE_NAME_1), data.nextService1);
  #endif
  #if SERVICE_INTERVAL_2 > 0
    _service_when(buffer, PSTR(SERVICE_NAME_2), data.nextService2);
  #endif
  #if SERVICE_INTERVAL_3 > 0
    _service_when(buffer, PSTR(SERVICE_NAME_3), data.nextService3);
  #endif
}

void PrintCounter::tick() {
  if (!isRunning()) return;

  millis_t now = millis();

<<<<<<< HEAD
  static uint32_t update_next; // = 0
  if (ELAPSED(now, update_next)) {
    #if ENABLED(DEBUG_PRINTCOUNTER)
      debug(PSTR("tick"));
    #endif
=======
  static millis_t update_next; // = 0
  if (ELAPSED(now, update_next)) {
    update_next = now + updateInterval;

    TERN_(DEBUG_PRINTCOUNTER, debug(PSTR("tick")));

>>>>>>> mcu_ctrl
    millis_t delta = deltaDuration();
    data.printTime += delta;

    #if SERVICE_INTERVAL_1 > 0
      data.nextService1 -= _MIN(delta, data.nextService1);
    #endif
    #if SERVICE_INTERVAL_2 > 0
      data.nextService2 -= _MIN(delta, data.nextService2);
    #endif
    #if SERVICE_INTERVAL_3 > 0
      data.nextService3 -= _MIN(delta, data.nextService3);
    #endif
<<<<<<< HEAD

    update_next = now + updateInterval * 1000;
  }

  static uint32_t eeprom_next; // = 0
  if (ELAPSED(now, eeprom_next)) {
    eeprom_next = now + saveInterval * 1000;
    saveStats();
  }
=======
  }

  #if PRINTCOUNTER_SAVE_INTERVAL > 0
    static millis_t eeprom_next; // = 0
    if (ELAPSED(now, eeprom_next)) {
      eeprom_next = now + saveInterval;
      saveStats();
    }
  #endif
>>>>>>> mcu_ctrl
}

// @Override
bool PrintCounter::start() {
<<<<<<< HEAD
  #if ENABLED(DEBUG_PRINTCOUNTER)
    debug(PSTR("start"));
  #endif
=======
  TERN_(DEBUG_PRINTCOUNTER, debug(PSTR("start")));
>>>>>>> mcu_ctrl

  bool paused = isPaused();

  if (super::start()) {
    if (!paused) {
      data.totalPrints++;
      lastDuration = 0;
    }
    return true;
  }

  return false;
}

<<<<<<< HEAD
// @Override
bool PrintCounter::stop() {
  #if ENABLED(DEBUG_PRINTCOUNTER)
    debug(PSTR("stop"));
  #endif

  if (super::stop()) {
    data.finishedPrints++;
    data.printTime += deltaDuration();

    if (duration() > data.longestPrint)
      data.longestPrint = duration();

    saveStats();
    return true;
  }
  else return false;
=======
bool PrintCounter::_stop(const bool completed) {
  TERN_(DEBUG_PRINTCOUNTER, debug(PSTR("stop")));

  const bool did_stop = super::stop();
  if (did_stop) {
    data.printTime += deltaDuration();
    if (completed) {
      data.finishedPrints++;
      if (duration() > data.longestPrint)
        data.longestPrint = duration();
    }
  }
  saveStats();
  return did_stop;
>>>>>>> mcu_ctrl
}

// @Override
void PrintCounter::reset() {
<<<<<<< HEAD
  #if ENABLED(DEBUG_PRINTCOUNTER)
    debug(PSTR("stop"));
  #endif
=======
  TERN_(DEBUG_PRINTCOUNTER, debug(PSTR("stop")));
>>>>>>> mcu_ctrl

  super::reset();
  lastDuration = 0;
}

#if HAS_SERVICE_INTERVALS

  void PrintCounter::resetServiceInterval(const int index) {
    switch (index) {
      #if SERVICE_INTERVAL_1 > 0
        case 1: data.nextService1 = SERVICE_INTERVAL_SEC_1;
      #endif
      #if SERVICE_INTERVAL_2 > 0
        case 2: data.nextService2 = SERVICE_INTERVAL_SEC_2;
      #endif
      #if SERVICE_INTERVAL_3 > 0
        case 3: data.nextService3 = SERVICE_INTERVAL_SEC_3;
      #endif
    }
    saveStats();
  }

  bool PrintCounter::needsService(const int index) {
<<<<<<< HEAD
=======
    if (!loaded) loadStats();
>>>>>>> mcu_ctrl
    switch (index) {
      #if SERVICE_INTERVAL_1 > 0
        case 1: return data.nextService1 == 0;
      #endif
      #if SERVICE_INTERVAL_2 > 0
        case 2: return data.nextService2 == 0;
      #endif
      #if SERVICE_INTERVAL_3 > 0
        case 3: return data.nextService3 == 0;
      #endif
      default: return false;
    }
  }

#endif // HAS_SERVICE_INTERVALS

#if ENABLED(DEBUG_PRINTCOUNTER)

  void PrintCounter::debug(const char func[]) {
    if (DEBUGGING(INFO)) {
      SERIAL_ECHOPGM("PrintCounter::");
<<<<<<< HEAD
      serialprintPGM(func);
=======
      SERIAL_ECHOPGM_P(func);
>>>>>>> mcu_ctrl
      SERIAL_ECHOLNPGM("()");
    }
  }

#endif

#endif // PRINTCOUNTER
