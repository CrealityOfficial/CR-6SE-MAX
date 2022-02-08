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
 * Neopixel support
 */

=======
 * NeoPixel support
 */

#ifndef _NEOPIXEL_INCLUDE_
  #error "Always include 'leds.h' and not 'neopixel.h' directly."
#endif

>>>>>>> mcu_ctrl
// ------------------------
// Includes
// ------------------------

#include "../../inc/MarlinConfig.h"

<<<<<<< HEAD
// #include "../../libs/Adafruit_NeoPixel.h"
#include <Adafruit_NeoPixel.h>

=======
#include <Adafruit_NeoPixel.h>
>>>>>>> mcu_ctrl
#include <stdint.h>

// ------------------------
// Defines
// ------------------------

<<<<<<< HEAD
#define MULTIPLE_NEOPIXEL_TYPES (defined(NEOPIXEL2_TYPE) && (NEOPIXEL2_TYPE != NEOPIXEL_TYPE))

#define NEOPIXEL_IS_RGB  (NEOPIXEL_TYPE == NEO_RGB || NEOPIXEL_TYPE == NEO_RBG || NEOPIXEL_TYPE == NEO_GRB || NEOPIXEL_TYPE == NEO_GBR || NEOPIXEL_TYPE == NEO_BRG || NEOPIXEL_TYPE == NEO_BGR)
#define NEOPIXEL_IS_RGBW !NEOPIXEL_IS_RGB

#if NEOPIXEL_IS_RGB
  #define NEO_WHITE 255, 255, 255, 0
#else
  #define NEO_WHITE 0, 0, 0, 255
=======
#define _NEO_IS_RGB(N) (N == NEO_RGB || N == NEO_RBG || N == NEO_GRB || N == NEO_GBR || N == NEO_BRG || N == NEO_BGR)

#if !_NEO_IS_RGB(NEOPIXEL_TYPE)
  #define HAS_WHITE_LED 1
#endif

#if HAS_WHITE_LED
  #define NEO_WHITE 0, 0, 0, 255
#else
  #define NEO_WHITE 255, 255, 255
#endif

#if defined(NEOPIXEL2_TYPE) && NEOPIXEL2_TYPE != NEOPIXEL_TYPE && DISABLED(NEOPIXEL2_SEPARATE)
  #define MULTIPLE_NEOPIXEL_TYPES 1
#endif

#if EITHER(MULTIPLE_NEOPIXEL_TYPES, NEOPIXEL2_INSERIES)
  #define CONJOINED_NEOPIXEL 1
>>>>>>> mcu_ctrl
#endif

// ------------------------
// Function prototypes
// ------------------------

class Marlin_NeoPixel {
private:
<<<<<<< HEAD
  static Adafruit_NeoPixel adaneo1
    #if MULTIPLE_NEOPIXEL_TYPES
      , adaneo2
    #endif
  ;

public:
=======
  static Adafruit_NeoPixel adaneo1;
  #if CONJOINED_NEOPIXEL
    static Adafruit_NeoPixel adaneo2;
  #endif

public:
  static int8_t neoindex;

>>>>>>> mcu_ctrl
  static void init();
  static void set_color_startup(const uint32_t c);

  static void set_color(const uint32_t c);

<<<<<<< HEAD
  #ifdef NEOPIXEL_BKGD_LED_INDEX
    static void set_color_background();
=======
  #ifdef NEOPIXEL_BKGD_INDEX_FIRST
    static void set_background_color(uint8_t r, uint8_t g, uint8_t b, uint8_t w);
    static void reset_background_color();
>>>>>>> mcu_ctrl
  #endif

  static inline void begin() {
    adaneo1.begin();
<<<<<<< HEAD
    #if MULTIPLE_NEOPIXEL_TYPES
      adaneo2.begin();
    #endif
  }

  static inline void set_pixel_color(const uint16_t n, const uint32_t c) {
    adaneo1.setPixelColor(n, c);
    #if MULTIPLE_NEOPIXEL_TYPES
      adaneo2.setPixelColor(n, c);
=======
    TERN_(CONJOINED_NEOPIXEL, adaneo2.begin());
  }

  static inline void set_pixel_color(const uint16_t n, const uint32_t c) {
    #if ENABLED(NEOPIXEL2_INSERIES)
      if (n >= NEOPIXEL_PIXELS) adaneo2.setPixelColor(n - (NEOPIXEL_PIXELS), c);
      else adaneo1.setPixelColor(n, c);
    #else
      adaneo1.setPixelColor(n, c);
      TERN_(MULTIPLE_NEOPIXEL_TYPES, adaneo2.setPixelColor(n, c));
>>>>>>> mcu_ctrl
    #endif
  }

  static inline void set_brightness(const uint8_t b) {
    adaneo1.setBrightness(b);
<<<<<<< HEAD
    #if MULTIPLE_NEOPIXEL_TYPES
      adaneo2.setBrightness(b);
    #endif
  }

  static inline void show() {
    adaneo1.show();
    #if PIN_EXISTS(NEOPIXEL2)
      #if MULTIPLE_NEOPIXEL_TYPES
        adaneo2.show();
      #else
        adaneo1.setPin(NEOPIXEL2_PIN);
=======
    TERN_(CONJOINED_NEOPIXEL, adaneo2.setBrightness(b));
  }

  static inline void show() {
    // Some platforms cannot maintain PWM output when NeoPixel disables interrupts for long durations.
    TERN_(HAS_PAUSE_SERVO_OUTPUT, PAUSE_SERVO_OUTPUT());
    adaneo1.show();
    #if PIN_EXISTS(NEOPIXEL2)
      #if CONJOINED_NEOPIXEL
        adaneo2.show();
      #else
        IF_DISABLED(NEOPIXEL2_SEPARATE, adaneo1.setPin(NEOPIXEL2_PIN));
>>>>>>> mcu_ctrl
        adaneo1.show();
        adaneo1.setPin(NEOPIXEL_PIN);
      #endif
    #endif
<<<<<<< HEAD
  }

  #if 0
    bool set_led_color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t w, const uint8_t p);
  #endif

  // Accessors
  static inline uint16_t pixels() { return adaneo1.numPixels(); }
  static inline uint8_t brightness() { return adaneo1.getBrightness(); }
  static inline uint32_t Color(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
    return adaneo1.Color(r, g, b, w);
=======
    TERN_(HAS_PAUSE_SERVO_OUTPUT, RESUME_SERVO_OUTPUT());
  }

  // Accessors
  static inline uint16_t pixels() { return adaneo1.numPixels() * TERN1(NEOPIXEL2_INSERIES, 2); }

  static inline uint8_t brightness() { return adaneo1.getBrightness(); }

  static inline uint32_t Color(uint8_t r, uint8_t g, uint8_t b OPTARG(HAS_WHITE_LED, uint8_t w)) {
    return adaneo1.Color(r, g, b OPTARG(HAS_WHITE_LED, w));
>>>>>>> mcu_ctrl
  }
};

extern Marlin_NeoPixel neo;
<<<<<<< HEAD
=======

// Neo pixel channel 2
#if ENABLED(NEOPIXEL2_SEPARATE)

  #if _NEO_IS_RGB(NEOPIXEL2_TYPE)
    #define NEOPIXEL2_IS_RGB 1
    #define NEO2_WHITE 255, 255, 255
  #else
    #define NEOPIXEL2_IS_RGBW 1
    #define HAS_WHITE_LED2 1      // A white component can be passed for NEOPIXEL2
    #define NEO2_WHITE 0, 0, 0, 255
  #endif

  class Marlin_NeoPixel2 {
  private:
    static Adafruit_NeoPixel adaneo;

  public:
    static int8_t neoindex;

    static void init();
    static void set_color_startup(const uint32_t c);

    static void set_color(const uint32_t c);

    static inline void begin() { adaneo.begin(); }
    static inline void set_pixel_color(const uint16_t n, const uint32_t c) { adaneo.setPixelColor(n, c); }
    static inline void set_brightness(const uint8_t b) { adaneo.setBrightness(b); }
    static inline void show() {
      adaneo.show();
      adaneo.setPin(NEOPIXEL2_PIN);
    }

    // Accessors
    static inline uint16_t pixels() { return adaneo.numPixels();}
    static inline uint8_t brightness() { return adaneo.getBrightness(); }
    static inline uint32_t Color(uint8_t r, uint8_t g, uint8_t b OPTARG(HAS_WHITE_LED2, uint8_t w)) {
      return adaneo.Color(r, g, b OPTARG(HAS_WHITE_LED2, w));
    }
  };

  extern Marlin_NeoPixel2 neo2;

#endif // NEOPIXEL2_SEPARATE

#undef _NEO_IS_RGB
>>>>>>> mcu_ctrl
