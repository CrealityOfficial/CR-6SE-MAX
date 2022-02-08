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
 * leds.h - Marlin general RGB LED support
 */

#include "../../inc/MarlinConfigPre.h"

#include <string.h>

<<<<<<< HEAD
#if ENABLED(NEOPIXEL_LED)
  #include "neopixel.h"
#endif

#define HAS_WHITE_LED EITHER(RGBW_LED, NEOPIXEL_LED)

=======
// A white component can be passed
#if EITHER(RGBW_LED, PCA9632_RGBW)
  #define HAS_WHITE_LED 1
#endif

#if ENABLED(NEOPIXEL_LED)
  #define _NEOPIXEL_INCLUDE_
  #include "neopixel.h"
  #undef _NEOPIXEL_INCLUDE_
#endif

>>>>>>> mcu_ctrl
/**
 * LEDcolor type for use with leds.set_color
 */
typedef struct LEDColor {
  uint8_t r, g, b
<<<<<<< HEAD
    #if HAS_WHITE_LED
      , w
      #if ENABLED(NEOPIXEL_LED)
        , i
      #endif
    #endif
  ;

  LEDColor() : r(255), g(255), b(255)
    #if HAS_WHITE_LED
      , w(255)
      #if ENABLED(NEOPIXEL_LED)
        , i(NEOPIXEL_BRIGHTNESS)
      #endif
    #endif
  {}

  LEDColor(uint8_t r, uint8_t g, uint8_t b
    #if HAS_WHITE_LED
      , uint8_t w=0
      #if ENABLED(NEOPIXEL_LED)
        , uint8_t i=NEOPIXEL_BRIGHTNESS
      #endif
    #endif
    ) : r(r), g(g), b(b)
    #if HAS_WHITE_LED
      , w(w)
      #if ENABLED(NEOPIXEL_LED)
        , i(i)
      #endif
    #endif
  {}

  LEDColor(const uint8_t (&rgbw)[4]) : r(rgbw[0]), g(rgbw[1]), b(rgbw[2])
    #if HAS_WHITE_LED
      , w(rgbw[3])
      #if ENABLED(NEOPIXEL_LED)
        , i(NEOPIXEL_BRIGHTNESS)
      #endif
    #endif
=======
    OPTARG(HAS_WHITE_LED, w)
    OPTARG(NEOPIXEL_LED, i)
  ;

  LEDColor() : r(255), g(255), b(255)
    OPTARG(HAS_WHITE_LED, w(255))
    OPTARG(NEOPIXEL_LED, i(NEOPIXEL_BRIGHTNESS))
  {}

  LEDColor(uint8_t r, uint8_t g, uint8_t b OPTARG(HAS_WHITE_LED, uint8_t w=0) OPTARG(NEOPIXEL_LED, uint8_t i=NEOPIXEL_BRIGHTNESS))
    : r(r), g(g), b(b) OPTARG(HAS_WHITE_LED, w(w)) OPTARG(NEOPIXEL_LED, i(i)) {}

  LEDColor(const uint8_t (&rgbw)[4]) : r(rgbw[0]), g(rgbw[1]), b(rgbw[2])
    OPTARG(HAS_WHITE_LED, w(rgbw[3]))
    OPTARG(NEOPIXEL_LED, i(NEOPIXEL_BRIGHTNESS))
>>>>>>> mcu_ctrl
  {}

  LEDColor& operator=(const uint8_t (&rgbw)[4]) {
    r = rgbw[0]; g = rgbw[1]; b = rgbw[2];
<<<<<<< HEAD
    #if HAS_WHITE_LED
      w = rgbw[3];
    #endif
=======
    TERN_(HAS_WHITE_LED, w = rgbw[3]);
>>>>>>> mcu_ctrl
    return *this;
  }

  LEDColor& operator=(const LEDColor &right) {
    if (this != &right) memcpy(this, &right, sizeof(LEDColor));
    return *this;
  }

  bool operator==(const LEDColor &right) {
    if (this == &right) return true;
    return 0 == memcmp(this, &right, sizeof(LEDColor));
  }

  bool operator!=(const LEDColor &right) { return !operator==(right); }

  bool is_off() const {
<<<<<<< HEAD
    return 3 > r + g + b
      #if HAS_WHITE_LED
        + w
      #endif
    ;
=======
    return 3 > r + g + b + TERN0(HAS_WHITE_LED, w);
>>>>>>> mcu_ctrl
  }
} LEDColor;

/**
<<<<<<< HEAD
 * Color helpers and presets
 */
#if HAS_WHITE_LED
  #if ENABLED(NEOPIXEL_LED)
    #define MakeLEDColor(R,G,B,W,I) LEDColor(R, G, B, W, I)
  #else
    #define MakeLEDColor(R,G,B,W,I) LEDColor(R, G, B, W)
  #endif
#else
  #define MakeLEDColor(R,G,B,W,I)   LEDColor(R, G, B)
#endif
=======
 * Color presets
 */
>>>>>>> mcu_ctrl

#define LEDColorOff()             LEDColor(  0,   0,   0)
#define LEDColorRed()             LEDColor(255,   0,   0)
#if ENABLED(LED_COLORS_REDUCE_GREEN)
  #define LEDColorOrange()        LEDColor(255,  25,   0)
  #define LEDColorYellow()        LEDColor(255,  75,   0)
#else
  #define LEDColorOrange()        LEDColor(255,  80,   0)
  #define LEDColorYellow()        LEDColor(255, 255,   0)
#endif
#define LEDColorGreen()           LEDColor(  0, 255,   0)
#define LEDColorBlue()            LEDColor(  0,   0, 255)
#define LEDColorIndigo()          LEDColor(  0, 255, 255)
#define LEDColorViolet()          LEDColor(255,   0, 255)
<<<<<<< HEAD
#if HAS_WHITE_LED
=======
#if HAS_WHITE_LED && DISABLED(RGB_LED)
>>>>>>> mcu_ctrl
  #define LEDColorWhite()         LEDColor(  0,   0,   0, 255)
#else
  #define LEDColorWhite()         LEDColor(255, 255, 255)
#endif

class LEDLights {
public:
  LEDLights() {} // ctor

  static void setup(); // init()

  static void set_color(const LEDColor &color
<<<<<<< HEAD
    #if ENABLED(NEOPIXEL_LED)
      , bool isSequence=false
    #endif
  );

  inline void set_color(uint8_t r, uint8_t g, uint8_t b
    #if HAS_WHITE_LED
      , uint8_t w=0
      #if ENABLED(NEOPIXEL_LED)
        , uint8_t i=NEOPIXEL_BRIGHTNESS
      #endif
    #endif
    #if ENABLED(NEOPIXEL_LED)
      , bool isSequence=false
    #endif
  ) {
    set_color(MakeLEDColor(r, g, b, w, i)
      #if ENABLED(NEOPIXEL_LED)
        , isSequence
      #endif
    );
=======
    OPTARG(NEOPIXEL_IS_SEQUENTIAL, bool isSequence=false)
  );

  static inline void set_color(uint8_t r, uint8_t g, uint8_t b
    OPTARG(HAS_WHITE_LED, uint8_t w=0)
    OPTARG(NEOPIXEL_LED, uint8_t i=NEOPIXEL_BRIGHTNESS)
    OPTARG(NEOPIXEL_IS_SEQUENTIAL, bool isSequence=false)
  ) {
    set_color(LEDColor(r, g, b OPTARG(HAS_WHITE_LED, w) OPTARG(NEOPIXEL_LED, i)) OPTARG(NEOPIXEL_IS_SEQUENTIAL, isSequence));
>>>>>>> mcu_ctrl
  }

  static inline void set_off()   { set_color(LEDColorOff()); }
  static inline void set_green() { set_color(LEDColorGreen()); }
  static inline void set_white() { set_color(LEDColorWhite()); }

  #if ENABLED(LED_COLOR_PRESETS)
    static const LEDColor defaultLEDColor;
    static inline void set_default()  { set_color(defaultLEDColor); }
    static inline void set_red()      { set_color(LEDColorRed()); }
    static inline void set_orange()   { set_color(LEDColorOrange()); }
    static inline void set_yellow()   { set_color(LEDColorYellow()); }
    static inline void set_blue()     { set_color(LEDColorBlue()); }
    static inline void set_indigo()   { set_color(LEDColorIndigo()); }
    static inline void set_violet()   { set_color(LEDColorViolet()); }
  #endif

  #if ENABLED(PRINTER_EVENT_LEDS)
    static inline LEDColor get_color() { return lights_on ? color : LEDColorOff(); }
  #endif

<<<<<<< HEAD
  #if EITHER(LED_CONTROL_MENU, PRINTER_EVENT_LEDS)
=======
  #if ANY(LED_CONTROL_MENU, PRINTER_EVENT_LEDS, CASE_LIGHT_IS_COLOR_LED)
>>>>>>> mcu_ctrl
    static LEDColor color; // last non-off color
    static bool lights_on; // the last set color was "on"
  #endif

  #if ENABLED(LED_CONTROL_MENU)
    static void toggle();  // swap "off" with color
<<<<<<< HEAD
=======
  #endif
  #if EITHER(LED_CONTROL_MENU, CASE_LIGHT_USE_RGB_LED)
>>>>>>> mcu_ctrl
    static inline void update() { set_color(color); }
  #endif

  #ifdef LED_BACKLIGHT_TIMEOUT
    private:
      static millis_t led_off_time;
    public:
      static inline void reset_timeout(const millis_t &ms) {
        led_off_time = ms + LED_BACKLIGHT_TIMEOUT;
<<<<<<< HEAD
        if (!lights_on) set_default();
=======
        if (!lights_on) update();
>>>>>>> mcu_ctrl
      }
      static void update_timeout(const bool power_on);
  #endif
};

extern LEDLights leds;
<<<<<<< HEAD
=======

#if ENABLED(NEOPIXEL2_SEPARATE)

  class LEDLights2 {
  public:
    LEDLights2() {}

    static void setup(); // init()

    static void set_color(const LEDColor &color);

    static inline void set_color(uint8_t r, uint8_t g, uint8_t b
      OPTARG(HAS_WHITE_LED, uint8_t w=0)
      OPTARG(NEOPIXEL_LED, uint8_t i=NEOPIXEL_BRIGHTNESS)
    ) {
      set_color(LEDColor(r, g, b
        OPTARG(HAS_WHITE_LED, w)
        OPTARG(NEOPIXEL_LED, i)
      ));
    }

    static inline void set_off()   { set_color(LEDColorOff()); }
    static inline void set_green() { set_color(LEDColorGreen()); }
    static inline void set_white() { set_color(LEDColorWhite()); }

    #if ENABLED(NEO2_COLOR_PRESETS)
      static const LEDColor defaultLEDColor;
      static inline void set_default()  { set_color(defaultLEDColor); }
      static inline void set_red()      { set_color(LEDColorRed()); }
      static inline void set_orange()   { set_color(LEDColorOrange()); }
      static inline void set_yellow()   { set_color(LEDColorYellow()); }
      static inline void set_blue()     { set_color(LEDColorBlue()); }
      static inline void set_indigo()   { set_color(LEDColorIndigo()); }
      static inline void set_violet()   { set_color(LEDColorViolet()); }
    #endif

    #if ENABLED(NEOPIXEL2_SEPARATE)
      static LEDColor color; // last non-off color
      static bool lights_on; // the last set color was "on"
      static void toggle();  // swap "off" with color
      static inline void update() { set_color(color); }
    #endif
  };

  extern LEDLights2 leds2;

#endif // NEOPIXEL2_SEPARATE
>>>>>>> mcu_ctrl
