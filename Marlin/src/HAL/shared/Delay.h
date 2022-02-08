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

<<<<<<< HEAD
=======
#include "../../inc/MarlinConfigPre.h"

>>>>>>> mcu_ctrl
/**
 * Busy wait delay cycles routines:
 *
 *  DELAY_CYCLES(count): Delay execution in cycles
 *  DELAY_NS(count): Delay execution in nanoseconds
 *  DELAY_US(count): Delay execution in microseconds
 */

<<<<<<< HEAD
#include "../../core/millis_t.h"
#include "../../core/macros.h"

#if defined(__arm__) || defined(__thumb__)

  #if __CORTEX_M == 7

    // Cortex-M3 through M7 can use the cycle counter of the DWT unit
    // http://www.anthonyvh.com/2017/05/18/cortex_m-cycle_counter/

    FORCE_INLINE static void enableCycleCounter() {
      CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

      #if __CORTEX_M == 7
        DWT->LAR = 0xC5ACCE55; // Unlock DWT on the M7
      #endif

      DWT->CYCCNT = 0;
      DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
    }

    FORCE_INLINE volatile uint32_t getCycleCount() { return DWT->CYCCNT; }

    FORCE_INLINE static void DELAY_CYCLES(const uint32_t x) {
      const uint32_t endCycles = getCycleCount() + x;
      while (PENDING(getCycleCount(), endCycles)) {}
    }

  #else

    // https://blueprints.launchpad.net/gcc-arm-embedded/+spec/delay-cycles

    #define nop() __asm__ __volatile__("nop;\n\t":::)

    FORCE_INLINE static void __delay_4cycles(uint32_t cy) { // +1 cycle
      #if ARCH_PIPELINE_RELOAD_CYCLES < 2
        #define EXTRA_NOP_CYCLES A("nop")
      #else
        #define EXTRA_NOP_CYCLES ""
      #endif

      __asm__ __volatile__(
        A(".syntax unified") // is to prevent CM0,CM1 non-unified syntax
        L("1")
        A("subs %[cnt],#1")
        EXTRA_NOP_CYCLES
        A("bne 1b")
        : [cnt]"+r"(cy)   // output: +r means input+output
        :                 // input:
        : "cc"            // clobbers:
      );
    }

    // Delay in cycles
    FORCE_INLINE static void DELAY_CYCLES(uint32_t x) {

      if (__builtin_constant_p(x)) {
        #define MAXNOPS 4

        if (x <= (MAXNOPS)) {
          switch (x) { case 4: nop(); case 3: nop(); case 2: nop(); case 1: nop(); }
        }
        else { // because of +1 cycle inside delay_4cycles
          const uint32_t rem = (x - 1) % (MAXNOPS);
          switch (rem) { case 3: nop(); case 2: nop(); case 1: nop(); }
          if ((x = (x - 1) / (MAXNOPS)))
            __delay_4cycles(x); // if need more then 4 nop loop is more optimal
        }
        #undef MAXNOPS
      }
      else if ((x >>= 2))
        __delay_4cycles(x);
    }
    #undef nop

  #endif
=======
#include "../../core/macros.h"

void calibrate_delay_loop();

#if defined(__arm__) || defined(__thumb__)

  // We want to have delay_cycle function with the lowest possible overhead, so we adjust at the function at runtime based on the current CPU best feature
  typedef void (*DelayImpl)(uint32_t);
  extern DelayImpl DelayCycleFnc;

  // I've measured 36 cycles on my system to call the cycle waiting method, but it shouldn't change much to have a bit more margin, it only consume a bit more flash
  #define TRIP_POINT_FOR_CALLING_FUNCTION   40

  // A simple recursive template class that output exactly one 'nop' of code per recursion
  template <int N> struct NopWriter {
    FORCE_INLINE static void build() {
      __asm__ __volatile__("nop");
      NopWriter<N-1>::build();
    }
  };
  // End the loop
  template <> struct NopWriter<0> { FORCE_INLINE static void build() {} };

  namespace Private {
    // Split recursing template in 2 different class so we don't reach the maximum template instantiation depth limit
    template <bool belowTP, int N> struct Helper {
      FORCE_INLINE static void build() {
        DelayCycleFnc(N - 2); //  Approximative cost of calling the function (might be off by one or 2 cycles)
      }
    };

    template <int N> struct Helper<true, N> {
      FORCE_INLINE static void build() {
        NopWriter<N - 1>::build();
      }
    };

    template <> struct Helper<true, 0> {
      FORCE_INLINE static void build() {}
    };

  }
  // Select a behavior based on the constexpr'ness of the parameter
  // If called with a compile-time parameter, then write as many NOP as required to reach the asked cycle count
  // (there is some tripping point here to start looping when it's more profitable than gruntly executing NOPs)
  // If not called from a compile-time parameter, fallback to a runtime loop counting version instead
  template <bool compileTime, int Cycles>
  struct SmartDelay {
    FORCE_INLINE SmartDelay(int) {
      if (Cycles == 0) return;
      Private::Helper<Cycles < TRIP_POINT_FOR_CALLING_FUNCTION, Cycles>::build();
    }
  };
  // Runtime version below. There is no way this would run under less than ~TRIP_POINT_FOR_CALLING_FUNCTION cycles
  template <int T>
  struct SmartDelay<false, T> {
    FORCE_INLINE SmartDelay(int v) { DelayCycleFnc(v); }
  };

  #define DELAY_CYCLES(X) do { SmartDelay<IS_CONSTEXPR(X), IS_CONSTEXPR(X) ? X : 0> _smrtdly_X(X); } while(0)

  // For delay in microseconds, no smart delay selection is required, directly call the delay function
  // Teensy compiler is too old and does not accept smart delay compile-time / run-time selection correctly
  #define DELAY_US(x) DelayCycleFnc((x) * ((F_CPU) / 1000000UL))
>>>>>>> mcu_ctrl

#elif defined(__AVR__)

  #define nop() __asm__ __volatile__("nop;\n\t":::)

  FORCE_INLINE static void __delay_4cycles(uint8_t cy) {
    __asm__ __volatile__(
      L("1")
      A("dec %[cnt]")
      A("nop")
      A("brne 1b")
      : [cnt] "+r"(cy)  // output: +r means input+output
      :                 // input:
      : "cc"            // clobbers:
    );
  }

  // Delay in cycles
  FORCE_INLINE static void DELAY_CYCLES(uint16_t x) {

    if (__builtin_constant_p(x)) {
      #define MAXNOPS 4

      if (x <= (MAXNOPS)) {
        switch (x) { case 4: nop(); case 3: nop(); case 2: nop(); case 1: nop(); }
      }
      else {
        const uint32_t rem = (x) % (MAXNOPS);
        switch (rem) { case 3: nop(); case 2: nop(); case 1: nop(); }
        if ((x = (x) / (MAXNOPS)))
          __delay_4cycles(x); // if need more then 4 nop loop is more optimal
      }

      #undef MAXNOPS
    }
    else if ((x >>= 2))
      __delay_4cycles(x);
  }
  #undef nop

<<<<<<< HEAD
#elif defined(ESP32)

  FORCE_INLINE static void DELAY_CYCLES(uint32_t x) {
    unsigned long ccount, stop;

    __asm__ __volatile__ ( "rsr     %0, ccount" : "=a" (ccount) );

    stop = ccount + x; // This can overflow

    while (ccount < stop) { // This doesn't deal with overflows
      __asm__ __volatile__ ( "rsr     %0, ccount" : "=a" (ccount) );
    }
  }

#elif defined(__PLAT_LINUX__)

  // specified inside platform

=======
  // Delay in microseconds
  #define DELAY_US(x) DELAY_CYCLES((x) * ((F_CPU) / 1000000UL))

#elif defined(__PLAT_LINUX__) || defined(ESP32)

  // DELAY_CYCLES specified inside platform

  // Delay in microseconds
  #define DELAY_US(x) DELAY_CYCLES((x) * ((F_CPU) / 1000000UL))
>>>>>>> mcu_ctrl
#else

  #error "Unsupported MCU architecture"

#endif

<<<<<<< HEAD
// Delay in nanoseconds
#define DELAY_NS(x) DELAY_CYCLES( (x) * (F_CPU / 1000000UL) / 1000UL )

// Delay in microseconds
#define DELAY_US(x) DELAY_CYCLES( (x) * (F_CPU / 1000000UL) )
=======
/**************************************************************
 *  Delay in nanoseconds. Requires the F_CPU macro.
 *  These macros follow avr-libc delay conventions.
 *
 * For AVR there are three possible operation modes, due to its
 * slower clock speeds and thus coarser delay resolution. For
 * example, when F_CPU = 16000000 the resolution is 62.5ns.
 *
 *  Round up (default)
 *    Round up the delay according to the CPU clock resolution.
 *    e.g., 100 will give a delay of 2 cycles (125ns).
 *
 *  Round down (DELAY_NS_ROUND_DOWN)
 *    Round down the delay according to the CPU clock resolution.
 *    e.g., 100 will be rounded down to 1 cycle (62.5ns).
 *
 *  Nearest (DELAY_NS_ROUND_CLOSEST)
 *    Round the delay to the nearest number of clock cycles.
 *    e.g., 165 will be rounded up to 3 cycles (187.5ns) because
 *          it's closer to the requested delay than 2 cycle (125ns).
 */

#ifndef __AVR__
  #undef DELAY_NS_ROUND_DOWN
  #undef DELAY_NS_ROUND_CLOSEST
#endif

#if ENABLED(DELAY_NS_ROUND_DOWN)
  #define DELAY_NS(x) DELAY_CYCLES((x) * ((F_CPU) / 1000000UL) / 1000UL)          // floor
#elif ENABLED(DELAY_NS_ROUND_CLOSEST)
  #define DELAY_NS(x) DELAY_CYCLES(((x) * ((F_CPU) / 1000000UL) + 500) / 1000UL)  // round
#else
  #define DELAY_NS(x) DELAY_CYCLES(((x) * ((F_CPU) / 1000000UL) + 999) / 1000UL)  // "ceil"
#endif
>>>>>>> mcu_ctrl
