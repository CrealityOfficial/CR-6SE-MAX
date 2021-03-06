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

#include "../inc/MarlinConfig.h"
<<<<<<< HEAD

/**
 * Define debug bit-masks
 */
=======
#include "serial_hook.h"

#if HAS_MEATPACK
  #include "../feature/meatpack.h"
#endif

// Commonly-used strings in serial output
extern const char NUL_STR[], SP_P_STR[], SP_T_STR[],
                  X_STR[], Y_STR[], Z_STR[], E_STR[],
                  X_LBL[], Y_LBL[], Z_LBL[], E_LBL[],
                  SP_A_STR[], SP_B_STR[], SP_C_STR[],
                  SP_X_STR[], SP_Y_STR[], SP_Z_STR[], SP_E_STR[],
                  SP_X_LBL[], SP_Y_LBL[], SP_Z_LBL[], SP_E_LBL[];

//
// Debugging flags for use by M111
//
>>>>>>> mcu_ctrl
enum MarlinDebugFlags : uint8_t {
  MARLIN_DEBUG_NONE          = 0,
  MARLIN_DEBUG_ECHO          = _BV(0), ///< Echo commands in order as they are processed
  MARLIN_DEBUG_INFO          = _BV(1), ///< Print messages for code that has debug output
  MARLIN_DEBUG_ERRORS        = _BV(2), ///< Not implemented
  MARLIN_DEBUG_DRYRUN        = _BV(3), ///< Ignore temperature setting and E movement commands
  MARLIN_DEBUG_COMMUNICATION = _BV(4), ///< Not implemented
  #if ENABLED(DEBUG_LEVELING_FEATURE)
    MARLIN_DEBUG_LEVELING    = _BV(5), ///< Print detailed output for homing and leveling
    MARLIN_DEBUG_MESH_ADJUST = _BV(6), ///< UBL bed leveling
  #else
    MARLIN_DEBUG_LEVELING    = 0,
    MARLIN_DEBUG_MESH_ADJUST = 0,
  #endif
<<<<<<< HEAD
=======
  MARLIN_DEBUG_LEVELING_ONLY = 0x20,
>>>>>>> mcu_ctrl
  MARLIN_DEBUG_ALL           = 0xFF
};

extern uint8_t marlin_debug_flags;
#define DEBUGGING(F) (marlin_debug_flags & (MARLIN_DEBUG_## F))

<<<<<<< HEAD
#define SERIAL_BOTH 0x7F
#if NUM_SERIAL > 1
  extern int8_t serial_port_index;
  #define _PORT_REDIRECT(n,p)   REMEMBER(n,serial_port_index,p)
  #define _PORT_RESTORE(n)      RESTORE(n)
  #define SERIAL_OUT(WHAT, V...) do{ \
    if (!serial_port_index || serial_port_index == SERIAL_BOTH) (void)MYSERIAL0.WHAT(V); \
    else if (serial_port_index) (void)MYSERIAL0.WHAT(V); \
  }while(0)
  #define SERIAL_ASSERT(P)      if(serial_port_index!=(P)){ debugger(); }
#else
  #define _PORT_REDIRECT(n,p)   NOOP
  #define _PORT_RESTORE(n)      NOOP
  #define SERIAL_OUT(WHAT, V...) (void)MYSERIAL0.WHAT(V)
  #define SERIAL_ASSERT(P)      NOOP
#endif

#define PORT_REDIRECT(p)        _PORT_REDIRECT(1,p)
#define PORT_RESTORE()          _PORT_RESTORE(1)

#define SERIAL_CHAR(x)          SERIAL_OUT(write, x)
#define SERIAL_ECHO(x)          SERIAL_OUT(print, x)
#define SERIAL_ECHO_F(V...)     SERIAL_OUT(print, V)
#define SERIAL_ECHOLN(x)        SERIAL_OUT(println, x)
#define SERIAL_PRINT(x,b)       SERIAL_OUT(print, x, b)
#define SERIAL_PRINTLN(x,b)     SERIAL_OUT(println, x, b)
#define SERIAL_PRINTF(V...)     SERIAL_OUT(printf, V)
#define SERIAL_FLUSH()          SERIAL_OUT(flush)

#ifdef __STM32F1__
  #define SERIAL_FLUSHTX()      SERIAL_OUT(flush)
#elif TX_BUFFER_SIZE > 0
  #define SERIAL_FLUSHTX()      SERIAL_OUT(flushTX)
#else
  #define SERIAL_FLUSHTX()
#endif

// Print up to 12 pairs of values. Odd elements auto-wrapped in PSTR().
#define __SEP_N(N,V...)   _SEP_##N(V)
#define _SEP_N(N,V...)    __SEP_N(N,V)
#define _SEP_1(PRE)       SERIAL_ECHOPGM(PRE)
#define _SEP_2(PRE,V)     serial_echopair_PGM(PSTR(PRE),V)
#define _SEP_3(a,b,c)     do{ _SEP_2(a,b); SERIAL_ECHOPGM(c); }while(0)
#define _SEP_4(a,b,V...)  do{ _SEP_2(a,b); _SEP_2(V); }while(0)
#define _SEP_5(a,b,V...)  do{ _SEP_2(a,b); _SEP_3(V); }while(0)
#define _SEP_6(a,b,V...)  do{ _SEP_2(a,b); _SEP_4(V); }while(0)
#define _SEP_7(a,b,V...)  do{ _SEP_2(a,b); _SEP_5(V); }while(0)
#define _SEP_8(a,b,V...)  do{ _SEP_2(a,b); _SEP_6(V); }while(0)
#define _SEP_9(a,b,V...)  do{ _SEP_2(a,b); _SEP_7(V); }while(0)
#define _SEP_10(a,b,V...) do{ _SEP_2(a,b); _SEP_8(V); }while(0)
#define _SEP_11(a,b,V...) do{ _SEP_2(a,b); _SEP_9(V); }while(0)
#define _SEP_12(a,b,V...) do{ _SEP_2(a,b); _SEP_10(V); }while(0)
#define _SEP_13(a,b,V...) do{ _SEP_2(a,b); _SEP_11(V); }while(0)
#define _SEP_14(a,b,V...) do{ _SEP_2(a,b); _SEP_12(V); }while(0)
#define _SEP_15(a,b,V...) do{ _SEP_2(a,b); _SEP_13(V); }while(0)
#define _SEP_16(a,b,V...) do{ _SEP_2(a,b); _SEP_14(V); }while(0)
#define _SEP_17(a,b,V...) do{ _SEP_2(a,b); _SEP_15(V); }while(0)
#define _SEP_18(a,b,V...) do{ _SEP_2(a,b); _SEP_16(V); }while(0)
#define _SEP_19(a,b,V...) do{ _SEP_2(a,b); _SEP_17(V); }while(0)
#define _SEP_20(a,b,V...) do{ _SEP_2(a,b); _SEP_18(V); }while(0)
#define _SEP_21(a,b,V...) do{ _SEP_2(a,b); _SEP_19(V); }while(0)
#define _SEP_22(a,b,V...) do{ _SEP_2(a,b); _SEP_20(V); }while(0)
#define _SEP_23(a,b,V...) do{ _SEP_2(a,b); _SEP_21(V); }while(0)
#define _SEP_24(a,b,V...) do{ _SEP_2(a,b); _SEP_22(V); }while(0)

#define SERIAL_ECHOPAIR(V...) _SEP_N(NUM_ARGS(V),V)

// Print up to 12 pairs of values. Odd elements must be PSTR pointers.
#define __SEP_N_P(N,V...)   _SEP_##N##_P(V)
#define _SEP_N_P(N,V...)    __SEP_N_P(N,V)
#define _SEP_1_P(PRE)       serialprintPGM(PRE)
#define _SEP_2_P(PRE,V)     serial_echopair_PGM(PRE,V)
#define _SEP_3_P(a,b,c)     do{ _SEP_2_P(a,b); serialprintPGM(c); }while(0)
#define _SEP_4_P(a,b,V...)  do{ _SEP_2_P(a,b); _SEP_2_P(V); }while(0)
#define _SEP_5_P(a,b,V...)  do{ _SEP_2_P(a,b); _SEP_3_P(V); }while(0)
#define _SEP_6_P(a,b,V...)  do{ _SEP_2_P(a,b); _SEP_4_P(V); }while(0)
#define _SEP_7_P(a,b,V...)  do{ _SEP_2_P(a,b); _SEP_5_P(V); }while(0)
#define _SEP_8_P(a,b,V...)  do{ _SEP_2_P(a,b); _SEP_6_P(V); }while(0)
#define _SEP_9_P(a,b,V...)  do{ _SEP_2_P(a,b); _SEP_7_P(V); }while(0)
#define _SEP_10_P(a,b,V...) do{ _SEP_2_P(a,b); _SEP_8_P(V); }while(0)
#define _SEP_11_P(a,b,V...) do{ _SEP_2_P(a,b); _SEP_9_P(V); }while(0)
#define _SEP_12_P(a,b,V...) do{ _SEP_2_P(a,b); _SEP_10_P(V); }while(0)
#define _SEP_13_P(a,b,V...) do{ _SEP_2_P(a,b); _SEP_11_P(V); }while(0)
#define _SEP_14_P(a,b,V...) do{ _SEP_2_P(a,b); _SEP_12_P(V); }while(0)
#define _SEP_15_P(a,b,V...) do{ _SEP_2_P(a,b); _SEP_13_P(V); }while(0)
#define _SEP_16_P(a,b,V...) do{ _SEP_2_P(a,b); _SEP_14_P(V); }while(0)
#define _SEP_17_P(a,b,V...) do{ _SEP_2_P(a,b); _SEP_15_P(V); }while(0)
#define _SEP_18_P(a,b,V...) do{ _SEP_2_P(a,b); _SEP_16_P(V); }while(0)
#define _SEP_19_P(a,b,V...) do{ _SEP_2_P(a,b); _SEP_17_P(V); }while(0)
#define _SEP_20_P(a,b,V...) do{ _SEP_2_P(a,b); _SEP_18_P(V); }while(0)
#define _SEP_21_P(a,b,V...) do{ _SEP_2_P(a,b); _SEP_19_P(V); }while(0)
#define _SEP_22_P(a,b,V...) do{ _SEP_2_P(a,b); _SEP_20_P(V); }while(0)
#define _SEP_23_P(a,b,V...) do{ _SEP_2_P(a,b); _SEP_21_P(V); }while(0)
#define _SEP_24_P(a,b,V...) do{ _SEP_2_P(a,b); _SEP_22_P(V); }while(0)

#define SERIAL_ECHOPAIR_P(V...) _SEP_N_P(NUM_ARGS(V),V)

// Print up to 12 pairs of values followed by newline
#define __SELP_N(N,V...)   _SELP_##N(V)
#define _SELP_N(N,V...)    __SELP_N(N,V)
#define _SELP_1(PRE)       SERIAL_ECHOLNPGM(PRE)
#define _SELP_2(PRE,V)     do{ serial_echopair_PGM(PSTR(PRE),V); SERIAL_EOL(); }while(0)
#define _SELP_3(a,b,c)     do{ _SEP_2(a,b); SERIAL_ECHOLNPGM(c); }while(0)
#define _SELP_4(a,b,V...)  do{ _SEP_2(a,b); _SELP_2(V); }while(0)
#define _SELP_5(a,b,V...)  do{ _SEP_2(a,b); _SELP_3(V); }while(0)
#define _SELP_6(a,b,V...)  do{ _SEP_2(a,b); _SELP_4(V); }while(0)
#define _SELP_7(a,b,V...)  do{ _SEP_2(a,b); _SELP_5(V); }while(0)
#define _SELP_8(a,b,V...)  do{ _SEP_2(a,b); _SELP_6(V); }while(0)
#define _SELP_9(a,b,V...)  do{ _SEP_2(a,b); _SELP_7(V); }while(0)
#define _SELP_10(a,b,V...) do{ _SEP_2(a,b); _SELP_8(V); }while(0)
#define _SELP_11(a,b,V...) do{ _SEP_2(a,b); _SELP_9(V); }while(0)
#define _SELP_12(a,b,V...) do{ _SEP_2(a,b); _SELP_10(V); }while(0)
#define _SELP_13(a,b,V...) do{ _SEP_2(a,b); _SELP_11(V); }while(0)
#define _SELP_14(a,b,V...) do{ _SEP_2(a,b); _SELP_12(V); }while(0)
#define _SELP_15(a,b,V...) do{ _SEP_2(a,b); _SELP_13(V); }while(0)
#define _SELP_16(a,b,V...) do{ _SEP_2(a,b); _SELP_14(V); }while(0)
#define _SELP_17(a,b,V...) do{ _SEP_2(a,b); _SELP_15(V); }while(0)
#define _SELP_18(a,b,V...) do{ _SEP_2(a,b); _SELP_16(V); }while(0)
#define _SELP_19(a,b,V...) do{ _SEP_2(a,b); _SELP_17(V); }while(0)
#define _SELP_20(a,b,V...) do{ _SEP_2(a,b); _SELP_18(V); }while(0)
#define _SELP_21(a,b,V...) do{ _SEP_2(a,b); _SELP_19(V); }while(0)
#define _SELP_22(a,b,V...) do{ _SEP_2(a,b); _SELP_20(V); }while(0)
#define _SELP_23(a,b,V...) do{ _SEP_2(a,b); _SELP_21(V); }while(0)
#define _SELP_24(a,b,V...) do{ _SEP_2(a,b); _SELP_22(V); }while(0) // Eat two args, pass the rest up

#define SERIAL_ECHOLNPAIR(V...) _SELP_N(NUM_ARGS(V),V)

// Print up to 12 pairs of values followed by newline
#define __SELP_N_P(N,V...)   _SELP_##N##_P(V)
#define _SELP_N_P(N,V...)    __SELP_N_P(N,V)
#define _SELP_1_P(PRE)       serialprintPGM(PRE)
#define _SELP_2_P(PRE,V)     do{ serial_echopair_PGM(PRE,V); SERIAL_EOL(); }while(0)
#define _SELP_3_P(a,b,c)     do{ _SEP_2_P(a,b); serialprintPGM(c); }while(0)
#define _SELP_4_P(a,b,V...)  do{ _SEP_2_P(a,b); _SELP_2_P(V); }while(0)
#define _SELP_5_P(a,b,V...)  do{ _SEP_2_P(a,b); _SELP_3_P(V); }while(0)
#define _SELP_6_P(a,b,V...)  do{ _SEP_2_P(a,b); _SELP_4_P(V); }while(0)
#define _SELP_7_P(a,b,V...)  do{ _SEP_2_P(a,b); _SELP_5_P(V); }while(0)
#define _SELP_8_P(a,b,V...)  do{ _SEP_2_P(a,b); _SELP_6_P(V); }while(0)
#define _SELP_9_P(a,b,V...)  do{ _SEP_2_P(a,b); _SELP_7_P(V); }while(0)
#define _SELP_10_P(a,b,V...) do{ _SEP_2_P(a,b); _SELP_8_P(V); }while(0)
#define _SELP_11_P(a,b,V...) do{ _SEP_2_P(a,b); _SELP_9_P(V); }while(0)
#define _SELP_12_P(a,b,V...) do{ _SEP_2_P(a,b); _SELP_10_P(V); }while(0)
#define _SELP_13_P(a,b,V...) do{ _SEP_2_P(a,b); _SELP_11_P(V); }while(0)
#define _SELP_14_P(a,b,V...) do{ _SEP_2_P(a,b); _SELP_12_P(V); }while(0)
#define _SELP_15_P(a,b,V...) do{ _SEP_2_P(a,b); _SELP_13_P(V); }while(0)
#define _SELP_16_P(a,b,V...) do{ _SEP_2_P(a,b); _SELP_14_P(V); }while(0)
#define _SELP_17_P(a,b,V...) do{ _SEP_2_P(a,b); _SELP_15_P(V); }while(0)
#define _SELP_18_P(a,b,V...) do{ _SEP_2_P(a,b); _SELP_16_P(V); }while(0)
#define _SELP_19_P(a,b,V...) do{ _SEP_2_P(a,b); _SELP_17_P(V); }while(0)
#define _SELP_20_P(a,b,V...) do{ _SEP_2_P(a,b); _SELP_18_P(V); }while(0)
#define _SELP_21_P(a,b,V...) do{ _SEP_2_P(a,b); _SELP_19_P(V); }while(0)
#define _SELP_22_P(a,b,V...) do{ _SEP_2_P(a,b); _SELP_20_P(V); }while(0)
#define _SELP_23_P(a,b,V...) do{ _SEP_2_P(a,b); _SELP_21_P(V); }while(0)
#define _SELP_24_P(a,b,V...) do{ _SEP_2_P(a,b); _SELP_22_P(V); }while(0) // Eat two args, pass the rest up

#define SERIAL_ECHOLNPAIR_P(V...) _SELP_N_P(NUM_ARGS(V),V)

// Print up to 20 comma-separated pairs of values
#define __SLST_N(N,V...)   _SLST_##N(V)
#define _SLST_N(N,V...)    __SLST_N(N,V)
#define _SLST_1(a)         SERIAL_ECHO(a)
#define _SLST_2(a,b)       do{ SERIAL_ECHO(a); SERIAL_ECHOPAIR(", ",b);     }while(0)
#define _SLST_3(a,b,c)     do{ SERIAL_ECHO(a); _SEP_2(", ",b); _SLST_1(c);  }while(0)
#define _SLST_4(a,b,V...)  do{ SERIAL_ECHO(a); _SEP_2(", ",b); _SLST_2(V);  }while(0)
#define _SLST_5(a,b,V...)  do{ SERIAL_ECHO(a); _SEP_2(", ",b); _SLST_3(V);  }while(0)
#define _SLST_6(a,b,V...)  do{ SERIAL_ECHO(a); _SEP_2(", ",b); _SLST_4(V);  }while(0)
#define _SLST_7(a,b,V...)  do{ SERIAL_ECHO(a); _SEP_2(", ",b); _SLST_5(V);  }while(0)
#define _SLST_8(a,b,V...)  do{ SERIAL_ECHO(a); _SEP_2(", ",b); _SLST_6(V);  }while(0)
#define _SLST_9(a,b,V...)  do{ SERIAL_ECHO(a); _SEP_2(", ",b); _SLST_7(V);  }while(0)
#define _SLST_10(a,b,V...) do{ SERIAL_ECHO(a); _SEP_2(", ",b); _SLST_8(V);  }while(0)
#define _SLST_11(a,b,V...) do{ SERIAL_ECHO(a); _SEP_2(", ",b); _SLST_9(V);  }while(0)
#define _SLST_12(a,b,V...) do{ SERIAL_ECHO(a); _SEP_2(", ",b); _SLST_10(V); }while(0)
#define _SLST_13(a,b,V...) do{ SERIAL_ECHO(a); _SEP_2(", ",b); _SLST_11(V); }while(0)
#define _SLST_14(a,b,V...) do{ SERIAL_ECHO(a); _SEP_2(", ",b); _SLST_12(V); }while(0)
#define _SLST_15(a,b,V...) do{ SERIAL_ECHO(a); _SEP_2(", ",b); _SLST_13(V); }while(0)
#define _SLST_16(a,b,V...) do{ SERIAL_ECHO(a); _SEP_2(", ",b); _SLST_14(V); }while(0)
#define _SLST_17(a,b,V...) do{ SERIAL_ECHO(a); _SEP_2(", ",b); _SLST_15(V); }while(0)
#define _SLST_18(a,b,V...) do{ SERIAL_ECHO(a); _SEP_2(", ",b); _SLST_16(V); }while(0)
#define _SLST_19(a,b,V...) do{ SERIAL_ECHO(a); _SEP_2(", ",b); _SLST_17(V); }while(0)
#define _SLST_20(a,b,V...) do{ SERIAL_ECHO(a); _SEP_2(", ",b); _SLST_18(V); }while(0) // Eat two args, pass the rest up

#define SERIAL_ECHOLIST(pre,V...)   do{ SERIAL_ECHOPGM(pre); _SLST_N(NUM_ARGS(V),V); }while(0)
#define SERIAL_ECHOLIST_N(N,V...)   _SLST_N(N,LIST_N(N,V))

#define SERIAL_ECHOPGM_P(P)         (serialprintPGM(P))
#define SERIAL_ECHOLNPGM_P(P)       (serialprintPGM(P "\n"))
=======
//
// Serial redirection
//
// Step 1: Find out what the first serial leaf is
#if BOTH(HAS_MULTI_SERIAL, SERIAL_CATCHALL)
  #define _SERIAL_LEAF_1 MYSERIAL
#else
  #define _SERIAL_LEAF_1 MYSERIAL1
#endif

// Hook Meatpack if it's enabled on the first leaf
#if ENABLED(MEATPACK_ON_SERIAL_PORT_1)
  typedef MeatpackSerial<decltype(_SERIAL_LEAF_1)> SerialLeafT1;
  extern SerialLeafT1 mpSerial1;
  #define SERIAL_LEAF_1 mpSerial1
#else
  #define SERIAL_LEAF_1 _SERIAL_LEAF_1
#endif

// Step 2: For multiserial wrap all serial ports in a single
//         interface with the ability to output to multiple serial ports.
#if HAS_MULTI_SERIAL
  #define _PORT_REDIRECT(n,p) REMEMBER(n,multiSerial.portMask,p)
  #define _PORT_RESTORE(n,p)  RESTORE(n)
  #define SERIAL_ASSERT(P)    if(multiSerial.portMask!=(P)){ debugger(); }
  // If we have a catchall, use that directly
  #ifdef SERIAL_CATCHALL
    #define _SERIAL_LEAF_2 SERIAL_CATCHALL
  #elif HAS_ETHERNET
    typedef ConditionalSerial<decltype(MYSERIAL2)> SerialLeafT2;  // We need to create an instance here
    extern SerialLeafT2 msSerial2;
    #define _SERIAL_LEAF_2 msSerial2
  #else
    #define _SERIAL_LEAF_2 MYSERIAL2 // Don't create a useless instance here, directly use the existing instance
  #endif

  // Nothing complicated here
  #define _SERIAL_LEAF_3 MYSERIAL3

  // Hook Meatpack if it's enabled on the second leaf
  #if ENABLED(MEATPACK_ON_SERIAL_PORT_2)
    typedef MeatpackSerial<decltype(_SERIAL_LEAF_2)> SerialLeafT2;
    extern SerialLeafT2 mpSerial2;
    #define SERIAL_LEAF_2 mpSerial2
  #else
    #define SERIAL_LEAF_2 _SERIAL_LEAF_2
  #endif

  // Hook Meatpack if it's enabled on the third leaf
  #if ENABLED(MEATPACK_ON_SERIAL_PORT_3)
    typedef MeatpackSerial<decltype(_SERIAL_LEAF_3)> SerialLeafT3;
    extern SerialLeafT3 mpSerial3;
    #define SERIAL_LEAF_3 mpSerial3
  #else
    #define SERIAL_LEAF_3 _SERIAL_LEAF_3
  #endif

  #define __S_MULTI(N) decltype(SERIAL_LEAF_##N),
  #define _S_MULTI(N) __S_MULTI(N)

  typedef MultiSerial< REPEAT_1(NUM_SERIAL, _S_MULTI) 0> SerialOutputT;

  #undef __S_MULTI
  #undef _S_MULTI

  extern SerialOutputT        multiSerial;
  #define SERIAL_IMPL         multiSerial
#else
  #define _PORT_REDIRECT(n,p) NOOP
  #define _PORT_RESTORE(n)    NOOP
  #define SERIAL_ASSERT(P)    NOOP
  #define SERIAL_IMPL         SERIAL_LEAF_1
#endif

#define SERIAL_OUT(WHAT, V...)  (void)SERIAL_IMPL.WHAT(V)

#define PORT_REDIRECT(p)   _PORT_REDIRECT(1,p)
#define PORT_RESTORE()     _PORT_RESTORE(1)
#define SERIAL_PORTMASK(P) SerialMask::from(P)

//
// SERIAL_CHAR - Print one or more individual chars
//
inline void SERIAL_CHAR(char a) { SERIAL_IMPL.write(a); }
template <typename ... Args>
void SERIAL_CHAR(char a, Args ... args) { SERIAL_IMPL.write(a); SERIAL_CHAR(args ...); }

/**
 * SERIAL_ECHO - Print a single string or value.
 *   Any numeric parameter (including char) is printed as a base-10 number.
 *   A string pointer or literal will be output as a string.
 *
 * NOTE: Use SERIAL_CHAR to print char as a single character.
 */
template <typename T>
void SERIAL_ECHO(T x) { SERIAL_IMPL.print(x); }

// Wrapper for ECHO commands to interpret a char
typedef struct SerialChar { char c; SerialChar(char n) : c(n) { } } serial_char_t;
inline void SERIAL_ECHO(serial_char_t x) { SERIAL_IMPL.write(x.c); }
#define AS_CHAR(C) serial_char_t(C)
#define AS_DIGIT(C) AS_CHAR('0' + (C))

// SERIAL_ECHO_F prints a floating point value with optional precision
inline void SERIAL_ECHO_F(EnsureDouble x, int digit=2) { SERIAL_IMPL.print(x, digit); }

template <typename T>
void SERIAL_ECHOLN(T x) { SERIAL_IMPL.println(x); }

// SERIAL_PRINT works like SERIAL_ECHO but allow to specify the encoding base of the number printed
template <typename T, typename U>
void SERIAL_PRINT(T x, U y) { SERIAL_IMPL.print(x, y); }

template <typename T, typename U>
void SERIAL_PRINTLN(T x, U y) { SERIAL_IMPL.println(x, y); }

// Flush the serial port
inline void SERIAL_FLUSH()    { SERIAL_IMPL.flush(); }
inline void SERIAL_FLUSHTX()  { SERIAL_IMPL.flushTX(); }

// Print a single PROGMEM string to serial
void serialprintPGM(PGM_P str);

//
// SERIAL_ECHOPAIR... macros are used to output string-value pairs.
//

// Print up to 20 pairs of values. Odd elements must be literal strings.
#define __SEP_N(N,V...)           _SEP_##N(V)
#define _SEP_N(N,V...)            __SEP_N(N,V)
#define _SEP_N_REF()              _SEP_N
#define _SEP_1(s)                 SERIAL_ECHOPGM(s);
#define _SEP_2(s,v)               serial_echopair_PGM(PSTR(s),v);
#define _SEP_3(s,v,V...)          _SEP_2(s,v); DEFER2(_SEP_N_REF)()(TWO_ARGS(V),V);
#define SERIAL_ECHOPAIR(V...)     do{ EVAL(_SEP_N(TWO_ARGS(V),V)); }while(0)

// Print up to 20 pairs of values followed by newline. Odd elements must be literal strings.
#define __SELP_N(N,V...)          _SELP_##N(V)
#define _SELP_N(N,V...)           __SELP_N(N,V)
#define _SELP_N_REF()             _SELP_N
#define _SELP_1(s)                SERIAL_ECHOLNPGM(s);
#define _SELP_2(s,v)              serial_echopair_PGM(PSTR(s),v); SERIAL_EOL();
#define _SELP_3(s,v,V...)         _SEP_2(s,v); DEFER2(_SELP_N_REF)()(TWO_ARGS(V),V);
#define SERIAL_ECHOLNPAIR(V...)   do{ EVAL(_SELP_N(TWO_ARGS(V),V)); }while(0)

// Print up to 20 pairs of values. Odd elements must be PSTR pointers.
#define __SEP_N_P(N,V...)         _SEP_##N##_P(V)
#define _SEP_N_P(N,V...)          __SEP_N_P(N,V)
#define _SEP_N_P_REF()            _SEP_N_P
#define _SEP_1_P(s)               serialprintPGM(s);
#define _SEP_2_P(s,v)             serial_echopair_PGM(s,v);
#define _SEP_3_P(s,v,V...)        _SEP_2_P(s,v); DEFER2(_SEP_N_P_REF)()(TWO_ARGS(V),V);
#define SERIAL_ECHOPAIR_P(V...)   do{ EVAL(_SEP_N_P(TWO_ARGS(V),V)); }while(0)

// Print up to 20 pairs of values followed by newline. Odd elements must be PSTR pointers.
#define __SELP_N_P(N,V...)        _SELP_##N##_P(V)
#define _SELP_N_P(N,V...)         __SELP_N_P(N,V)
#define _SELP_N_P_REF()           _SELP_N_P
#define _SELP_1_P(s)              { serialprintPGM(s); SERIAL_EOL(); }
#define _SELP_2_P(s,v)            { serial_echopair_PGM(s,v); SERIAL_EOL(); }
#define _SELP_3_P(s,v,V...)       { _SEP_2_P(s,v); DEFER2(_SELP_N_P_REF)()(TWO_ARGS(V),V); }
#define SERIAL_ECHOLNPAIR_P(V...) do{ EVAL(_SELP_N_P(TWO_ARGS(V),V)); }while(0)

#ifdef AllowDifferentTypeInList

  inline void SERIAL_ECHOLIST_IMPL() {}
  template <typename T>
  void SERIAL_ECHOLIST_IMPL(T && t) { SERIAL_IMPL.print(t); }

  template <typename T, typename ... Args>
  void SERIAL_ECHOLIST_IMPL(T && t, Args && ... args) {
    SERIAL_IMPL.print(t);
    serialprintPGM(PSTR(", "));
    SERIAL_ECHOLIST_IMPL(args...);
  }

  template <typename ... Args>
  void SERIAL_ECHOLIST(PGM_P const str, Args && ... args) {
    SERIAL_IMPL.print(str);
    SERIAL_ECHOLIST_IMPL(args...);
  }

#else // Optimization if the listed type are all the same (seems to be the case in the codebase so use that instead)

  template <typename ... Args>
  void SERIAL_ECHOLIST(PGM_P const str, Args && ... args) {
    serialprintPGM(str);
    typename Private::first_type_of<Args...>::type values[] = { args... };
    constexpr size_t argsSize = sizeof...(args);
    for (size_t i = 0; i < argsSize; i++) {
      if (i) serialprintPGM(PSTR(", "));
      SERIAL_IMPL.print(values[i]);
    }
  }

#endif

#define SERIAL_ECHOPGM_P(P)         (serialprintPGM(P))
#define SERIAL_ECHOLNPGM_P(P)       do{ serialprintPGM(P); SERIAL_EOL(); }while(0)
>>>>>>> mcu_ctrl

#define SERIAL_ECHOPGM(S)           (serialprintPGM(PSTR(S)))
#define SERIAL_ECHOLNPGM(S)         (serialprintPGM(PSTR(S "\n")))

#define SERIAL_ECHOPAIR_F_P(P,V...) do{ serialprintPGM(P); SERIAL_ECHO_F(V); }while(0)
#define SERIAL_ECHOLNPAIR_F_P(V...) do{ SERIAL_ECHOPAIR_F_P(V); SERIAL_EOL(); }while(0)

#define SERIAL_ECHOPAIR_F(S,V...)   SERIAL_ECHOPAIR_F_P(PSTR(S),V)
#define SERIAL_ECHOLNPAIR_F(V...)   do{ SERIAL_ECHOPAIR_F(V); SERIAL_EOL(); }while(0)

#define SERIAL_ECHO_START()         serial_echo_start()
#define SERIAL_ERROR_START()        serial_error_start()
#define SERIAL_EOL()                SERIAL_CHAR('\n')

<<<<<<< HEAD
#define SERIAL_ECHO_MSG(S)          do{ SERIAL_ECHO_START(); SERIAL_ECHOLNPGM(S); }while(0)
#define SERIAL_ERROR_MSG(S)         do{ SERIAL_ERROR_START(); SERIAL_ECHOLNPGM(S); }while(0)
=======
#define SERIAL_ECHO_MSG(V...)       do{ SERIAL_ECHO_START(); SERIAL_ECHOLNPAIR(V); }while(0)
#define SERIAL_ERROR_MSG(V...)      do{ SERIAL_ERROR_START(); SERIAL_ECHOLNPAIR(V); }while(0)
>>>>>>> mcu_ctrl

#define SERIAL_ECHO_SP(C)           serial_spaces(C)

#define SERIAL_ECHO_TERNARY(TF, PRE, ON, OFF, POST) serial_ternary(TF, PSTR(PRE), PSTR(ON), PSTR(OFF), PSTR(POST))

<<<<<<< HEAD
//
// Functions for serial printing from PROGMEM. (Saves loads of SRAM.)
//
=======
#if SERIAL_FLOAT_PRECISION
  #define SERIAL_DECIMAL(V) SERIAL_PRINT(V, SERIAL_FLOAT_PRECISION)
#else
  #define SERIAL_DECIMAL(V) SERIAL_ECHO(V)
#endif

//
// Functions for serial printing from PROGMEM. (Saves loads of SRAM.)
//
void serial_echopair_PGM(PGM_P const s_P, serial_char_t v);
>>>>>>> mcu_ctrl
void serial_echopair_PGM(PGM_P const s_P, const char *v);
void serial_echopair_PGM(PGM_P const s_P, char v);
void serial_echopair_PGM(PGM_P const s_P, int v);
void serial_echopair_PGM(PGM_P const s_P, long v);
void serial_echopair_PGM(PGM_P const s_P, float v);
void serial_echopair_PGM(PGM_P const s_P, double v);
<<<<<<< HEAD
void serial_echopair_PGM(PGM_P const s_P, unsigned int v);
void serial_echopair_PGM(PGM_P const s_P, unsigned long v);
inline void serial_echopair_PGM(PGM_P const s_P, uint8_t v) { serial_echopair_PGM(s_P, (int)v); }
inline void serial_echopair_PGM(PGM_P const s_P, bool v)    { serial_echopair_PGM(s_P, (int)v); }
inline void serial_echopair_PGM(PGM_P const s_P, void *v)   { serial_echopair_PGM(s_P, (unsigned long)v); }

void serialprintPGM(PGM_P str);
=======
void serial_echopair_PGM(PGM_P const s_P, unsigned char v);
void serial_echopair_PGM(PGM_P const s_P, unsigned int v);
void serial_echopair_PGM(PGM_P const s_P, unsigned long v);
inline void serial_echopair_PGM(PGM_P const s_P, bool v)    { serial_echopair_PGM(s_P, (int)v); }
inline void serial_echopair_PGM(PGM_P const s_P, void *v)   { serial_echopair_PGM(s_P, (uintptr_t)v); }

>>>>>>> mcu_ctrl
void serial_echo_start();
void serial_error_start();
void serial_ternary(const bool onoff, PGM_P const pre, PGM_P const on, PGM_P const off, PGM_P const post=nullptr);
void serialprint_onoff(const bool onoff);
void serialprintln_onoff(const bool onoff);
void serialprint_truefalse(const bool tf);
void serial_spaces(uint8_t count);

void print_bin(const uint16_t val);
<<<<<<< HEAD

void print_xyz(const float &x, const float &y, const float &z, PGM_P const prefix=nullptr, PGM_P const suffix=nullptr);

inline void print_xyz(const xyz_pos_t &xyz, PGM_P const prefix=nullptr, PGM_P const suffix=nullptr) {
  print_xyz(xyz.x, xyz.y, xyz.z, prefix, suffix);
}

#define SERIAL_POS(SUFFIX,VAR) do { print_xyz(VAR, PSTR("  " STRINGIFY(VAR) "="), PSTR(" : " SUFFIX "\n")); }while(0)
#define SERIAL_XYZ(PREFIX,V...) do { print_xyz(V, PSTR(PREFIX), nullptr); }while(0)
=======
void print_pos(const_float_t x, const_float_t y, const_float_t z, PGM_P const prefix=nullptr, PGM_P const suffix=nullptr);

inline void print_pos(const xyz_pos_t &xyz, PGM_P const prefix=nullptr, PGM_P const suffix=nullptr) {
  print_pos(xyz.x, xyz.y, xyz.z, prefix, suffix);
}

#define SERIAL_POS(SUFFIX,VAR) do { print_pos(VAR, PSTR("  " STRINGIFY(VAR) "="), PSTR(" : " SUFFIX "\n")); }while(0)
#define SERIAL_XYZ(PREFIX,V...) do { print_pos(V, PSTR(PREFIX), nullptr); }while(0)
>>>>>>> mcu_ctrl
