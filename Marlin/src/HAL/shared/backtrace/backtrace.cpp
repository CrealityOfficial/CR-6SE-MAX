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

=======
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
>>>>>>> mcu_ctrl
#if defined(__arm__) || defined(__thumb__)

#include "backtrace.h"
#include "unwinder.h"
#include "unwmemaccess.h"

<<<<<<< HEAD
#include "../../../core/serial.h"
#include <stdarg.h>

// Dump a backtrace entry
static bool UnwReportOut(void* ctx, const UnwReport* bte) {
=======
#include "../HAL_MinSerial.h"
#include <stdarg.h>

// Dump a backtrace entry
static bool UnwReportOut(void *ctx, const UnwReport *bte) {
>>>>>>> mcu_ctrl
  int *p = (int*)ctx;

  (*p)++;

<<<<<<< HEAD
  SERIAL_CHAR('#'); SERIAL_PRINT(*p,DEC); SERIAL_ECHOPGM(" : ");
  SERIAL_ECHOPGM(bte->name ? bte->name : "unknown"); SERIAL_ECHOPGM("@0x"); SERIAL_PRINT(bte->function, HEX);
  SERIAL_CHAR('+'); SERIAL_PRINT(bte->address - bte->function,DEC);
  SERIAL_ECHOPGM(" PC:"); SERIAL_PRINT(bte->address,HEX); SERIAL_CHAR('\n');
=======
  const uint32_t a = bte->address, f = bte->function;
  MinSerial::TX('#');    MinSerial::TXDec(*p);    MinSerial::TX(" : ");
  MinSerial::TX(bte->name?:"unknown");            MinSerial::TX('@');   MinSerial::TXHex(f);
  MinSerial::TX('+');    MinSerial::TXDec(a - f);
  MinSerial::TX(" PC:"); MinSerial::TXHex(a);
  MinSerial::TX('\n');
>>>>>>> mcu_ctrl
  return true;
}

#ifdef UNW_DEBUG
<<<<<<< HEAD
  void UnwPrintf(const char* format, ...) {
=======
  void UnwPrintf(const char *format, ...) {
>>>>>>> mcu_ctrl
    char dest[256];
    va_list argptr;
    va_start(argptr, format);
    vsprintf(dest, format, argptr);
    va_end(argptr);
<<<<<<< HEAD
    TX(&dest[0]);
=======
    MinSerial::TX(&dest[0]);
>>>>>>> mcu_ctrl
  }
#endif

/* Table of function pointers for passing to the unwinder */
static const UnwindCallbacks UnwCallbacks = {
  UnwReportOut,
  UnwReadW,
  UnwReadH,
  UnwReadB
  #ifdef UNW_DEBUG
   , UnwPrintf
  #endif
};

<<<<<<< HEAD
void backtrace() {

  UnwindFrame btf;
  uint32_t sp = 0, lr = 0, pc = 0;
=======
// Perform a backtrace to the serial port
void backtrace() {

  unsigned long sp = 0, lr = 0, pc = 0;
>>>>>>> mcu_ctrl

  // Capture the values of the registers to perform the traceback
  __asm__ __volatile__ (
    " mov %[lrv],lr\n"
    " mov %[spv],sp\n"
    " mov %[pcv],pc\n"
    : [spv]"+r"( sp ),
      [lrv]"+r"( lr ),
      [pcv]"+r"( pc )
    ::
  );

<<<<<<< HEAD
=======
  backtrace_ex(sp, lr, pc);
}

void backtrace_ex(unsigned long sp, unsigned long lr, unsigned long pc) {
  UnwindFrame btf;

>>>>>>> mcu_ctrl
  // Fill the traceback structure
  btf.sp = sp;
  btf.fp = btf.sp;
  btf.lr = lr;
  btf.pc = pc | 1; // Force Thumb, as CORTEX only support it

  // Perform a backtrace
<<<<<<< HEAD
  SERIAL_ERROR_MSG("Backtrace:");
=======
  MinSerial::TX("Backtrace:");
>>>>>>> mcu_ctrl
  int ctr = 0;
  UnwindStart(&btf, &UnwCallbacks, &ctr);
}

#else // !__arm__ && !__thumb__

void backtrace() {}

<<<<<<< HEAD
#endif
=======
#endif // __arm__ || __thumb__
>>>>>>> mcu_ctrl
