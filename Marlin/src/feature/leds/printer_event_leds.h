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
#pragma once

/**
<<<<<<< HEAD
 * printer_event_leds.h - LED color changing based on printer status
=======
 * feature/leds/printer_event_leds.h - LED color changing based on printer status
>>>>>>> mcu_ctrl
 */

#include "leds.h"
#include "../../inc/MarlinConfig.h"

class PrinterEventLEDs {
private:
  static uint8_t old_intensity;

  #if HAS_LEDS_OFF_FLAG
    static bool leds_off_after_print;
  #endif

<<<<<<< HEAD
  static inline void set_done() {
    #if ENABLED(LED_COLOR_PRESETS)
      leds.set_default();
    #else
      leds.set_off();
    #endif
  }
=======
  static inline void set_done() { TERN(LED_COLOR_PRESETS, leds.set_default(), leds.set_off()); }
>>>>>>> mcu_ctrl

public:
  #if HAS_TEMP_HOTEND
    static inline LEDColor onHotendHeatingStart() { old_intensity = 0; return leds.get_color(); }
<<<<<<< HEAD
    static void onHotendHeating(const float &start, const float &current, const float &target);
=======
    static void onHotendHeating(const celsius_t start, const celsius_t current, const celsius_t target);
>>>>>>> mcu_ctrl
  #endif

  #if HAS_HEATED_BED
    static inline LEDColor onBedHeatingStart() { old_intensity = 127; return leds.get_color(); }
<<<<<<< HEAD
    static void onBedHeating(const float &start, const float &current, const float &target);
  #endif

  #if HAS_TEMP_HOTEND || HAS_HEATED_BED
    static inline void onHeatingDone() { leds.set_color(LEDColorWhite()); }
=======
    static void onBedHeating(const celsius_t start, const celsius_t current, const celsius_t target);
  #endif

  #if HAS_HEATED_CHAMBER
    static inline LEDColor onChamberHeatingStart() { old_intensity = 127; return leds.get_color(); }
    static void onChamberHeating(const celsius_t start, const celsius_t current, const celsius_t target);
  #endif

  #if HAS_TEMP_HOTEND || HAS_HEATED_BED || HAS_HEATED_CHAMBER
    static inline void onHeatingDone()             { leds.set_white(); }
>>>>>>> mcu_ctrl
    static inline void onPidTuningDone(LEDColor c) { leds.set_color(c); }
  #endif

  #if ENABLED(SDSUPPORT)

    static inline void onPrintCompleted() {
      leds.set_green();
      #if HAS_LEDS_OFF_FLAG
        leds_off_after_print = true;
      #else
        safe_delay(2000);
        set_done();
      #endif
    }

    static inline void onResumeAfterWait() {
      #if HAS_LEDS_OFF_FLAG
        if (leds_off_after_print) {
          set_done();
          leds_off_after_print = false;
        }
      #endif
    }

  #endif // SDSUPPORT
};

extern PrinterEventLEDs printerEventLEDs;
