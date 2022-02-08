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
<<<<<<< HEAD
 * printer_event_leds.cpp - LED color changing based on printer status
=======
 * feature/leds/printer_event_leds.cpp - LED color changing based on printer status
>>>>>>> mcu_ctrl
 */

#include "../../inc/MarlinConfigPre.h"

#if ENABLED(PRINTER_EVENT_LEDS)

#include "printer_event_leds.h"

PrinterEventLEDs printerEventLEDs;

#if HAS_LEDS_OFF_FLAG
  bool PrinterEventLEDs::leds_off_after_print; // = false
#endif

#if HAS_TEMP_HOTEND || HAS_HEATED_BED

  uint8_t PrinterEventLEDs::old_intensity = 0;

<<<<<<< HEAD
  inline uint8_t pel_intensity(const float &start, const float &current, const float &target) {
    return (uint8_t)map(constrain(current, start, target), start, target, 0.f, 255.f);
  }

  inline void pel_set_rgb(const uint8_t r, const uint8_t g, const uint8_t b) {
    leds.set_color(
      MakeLEDColor(r, g, b, 0, neo.brightness())
        #if ENABLED(NEOPIXEL_IS_SEQUENTIAL)
          , true
        #endif
      );
=======
  inline uint8_t pel_intensity(const celsius_t start, const celsius_t current, const celsius_t target) {
    if (start == target) return 255;
    return (uint8_t)map(constrain(current, start, target), start, target, 0, 255);
  }

  inline void pel_set_rgb(const uint8_t r, const uint8_t g, const uint8_t b OPTARG(HAS_WHITE_LED, const uint8_t w=0)) {
    leds.set_color(
      LEDColor(r, g, b OPTARG(HAS_WHITE_LED, w) OPTARG(NEOPIXEL_LED, neo.brightness()))
      OPTARG(NEOPIXEL_IS_SEQUENTIAL, true)
    );
>>>>>>> mcu_ctrl
  }

#endif

#if HAS_TEMP_HOTEND

<<<<<<< HEAD
  void PrinterEventLEDs::onHotendHeating(const float &start, const float &current, const float &target) {
=======
  void PrinterEventLEDs::onHotendHeating(const celsius_t start, const celsius_t current, const celsius_t target) {
>>>>>>> mcu_ctrl
    const uint8_t blue = pel_intensity(start, current, target);
    if (blue != old_intensity) {
      old_intensity = blue;
      pel_set_rgb(255, 0, 255 - blue);
    }
  }

#endif

#if HAS_HEATED_BED

<<<<<<< HEAD
  void PrinterEventLEDs::onBedHeating(const float &start, const float &current, const float &target) {
=======
  void PrinterEventLEDs::onBedHeating(const celsius_t start, const celsius_t current, const celsius_t target) {
>>>>>>> mcu_ctrl
    const uint8_t red = pel_intensity(start, current, target);
    if (red != old_intensity) {
      old_intensity = red;
      pel_set_rgb(red, 0, 255);
    }
  }
<<<<<<< HEAD
=======

#endif

#if HAS_HEATED_CHAMBER

  void PrinterEventLEDs::onChamberHeating(const celsius_t start, const celsius_t current, const celsius_t target) {
    const uint8_t green = pel_intensity(start, current, target);
    if (green != old_intensity) {
      old_intensity = green;
      pel_set_rgb(255, green, 255);
    }
  }

>>>>>>> mcu_ctrl
#endif

#endif // PRINTER_EVENT_LEDS
