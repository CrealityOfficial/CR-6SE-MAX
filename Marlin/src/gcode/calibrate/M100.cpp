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

#include "../../inc/MarlinConfig.h"

#if ENABLED(M100_FREE_MEMORY_WATCHER)

#include "../gcode.h"
#include "../queue.h"
<<<<<<< HEAD
#include "../../libs/hex_print_routines.h"

#include "../../Marlin.h" // for idle()
=======
#include "../../libs/hex_print.h"

#include "../../MarlinCore.h" // for idle()
>>>>>>> mcu_ctrl

/**
 * M100 Free Memory Watcher
 *
 * This code watches the free memory block between the bottom of the heap and the top of the stack.
 * This memory block is initialized and watched via the M100 command.
 *
 * M100 I   Initializes the free memory block and prints vitals statistics about the area
 *
 * M100 F   Identifies how much of the free memory block remains free and unused. It also
 *          detects and reports any corruption within the free memory block that may have
 *          happened due to errant firmware.
 *
 * M100 D   Does a hex display of the free memory block along with a flag for any errant
 *          data that does not match the expected value.
 *
 * M100 C x Corrupts x locations within the free memory block. This is useful to check the
 *          correctness of the M100 F and M100 D commands.
 *
 * Also, there are two support functions that can be called from a developer's C code.
 *
 *    uint16_t check_for_free_memory_corruption(PGM_P const free_memory_start);
<<<<<<< HEAD
 *    void M100_dump_routine(PGM_P const title, char *start, char *end);
=======
 *    void M100_dump_routine(PGM_P const title, const char * const start, const uintptr_t size);
>>>>>>> mcu_ctrl
 *
 * Initial version by Roxy-3D
 */
#define M100_FREE_MEMORY_DUMPER     // Enable for the `M100 D` Dump sub-command
#define M100_FREE_MEMORY_CORRUPTOR  // Enable for the `M100 C` Corrupt sub-command

#define TEST_BYTE ((char) 0xE5)

<<<<<<< HEAD
#if defined(__AVR__) || IS_32BIT_TEENSY
=======
#if EITHER(__AVR__, IS_32BIT_TEENSY)
>>>>>>> mcu_ctrl

  extern char __bss_end;
  char *end_bss = &__bss_end,
       *free_memory_start = end_bss, *free_memory_end = 0,
       *stacklimit = 0, *heaplimit = 0;

  #define MEMORY_END_CORRECTION 0

#elif defined(TARGET_LPC1768)

  extern char __bss_end__, __StackLimit, __HeapLimit;

  char *end_bss = &__bss_end__,
       *stacklimit = &__StackLimit,
       *heaplimit = &__HeapLimit;

  #define MEMORY_END_CORRECTION 0x200

  char *free_memory_start = heaplimit,
       *free_memory_end = stacklimit - MEMORY_END_CORRECTION;

#elif defined(__SAM3X8E__)

  extern char _ebss;

  char *end_bss = &_ebss,
       *free_memory_start = end_bss,
       *free_memory_end = 0,
       *stacklimit = 0,
       *heaplimit = 0;

  #define MEMORY_END_CORRECTION 0x10000  // need to stay well below 0x20080000 or M100 F crashes

#elif defined(__SAMD51__)

  extern unsigned int __bss_end__, __StackLimit, __HeapLimit;
  extern "C" void * _sbrk(int incr);

  void *end_bss = &__bss_end__,
       *stacklimit = &__StackLimit,
       *heaplimit = &__HeapLimit;

  #define MEMORY_END_CORRECTION 0x400

  char *free_memory_start = (char *)_sbrk(0) + 0x200,     //  Leave some heap space
       *free_memory_end = (char *)stacklimit - MEMORY_END_CORRECTION;

#else
  #error "M100 - unsupported CPU"
#endif

//
// Utility functions
//

<<<<<<< HEAD
// Location of a variable on its stack frame. Returns a value above
// the stack (once the function returns to the caller).
char* top_of_stack() {
=======
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-local-addr"

// Location of a variable in its stack frame.
// The returned address will be above the stack (after it returns).
char *top_of_stack() {
>>>>>>> mcu_ctrl
  char x;
  return &x + 1; // x is pulled on return;
}

<<<<<<< HEAD
=======
#pragma GCC diagnostic pop

>>>>>>> mcu_ctrl
// Count the number of test bytes at the specified location.
inline int32_t count_test_bytes(const char * const start_free_memory) {
  for (uint32_t i = 0; i < 32000; i++)
    if (char(start_free_memory[i]) != TEST_BYTE)
      return i - 1;

  return -1;
}

//
// M100 sub-commands
//

#if ENABLED(M100_FREE_MEMORY_DUMPER)
  /**
   * M100 D
   *  Dump the free memory block from brkval to the stack pointer.
   *  malloc() eats memory from the start of the block and the stack grows
   *  up from the bottom of the block. Solid test bytes indicate nothing has
   *  used that memory yet. There should not be anything but test bytes within
   *  the block. If so, it may indicate memory corruption due to a bad pointer.
   *  Unexpected bytes are flagged in the right column.
   */
<<<<<<< HEAD
  inline void dump_free_memory(char *start_free_memory, char *end_free_memory) {
=======
  void dump_free_memory(char *start_free_memory, char *end_free_memory) {
>>>>>>> mcu_ctrl
    //
    // Start and end the dump on a nice 16 byte boundary
    // (even though the values are not 16-byte aligned).
    //
<<<<<<< HEAD
    start_free_memory = (char*)((ptr_int_t)((uint32_t)start_free_memory & 0xFFFFFFF0)); // Align to 16-byte boundary
    end_free_memory  = (char*)((ptr_int_t)((uint32_t)end_free_memory  | 0x0000000F)); // Align end_free_memory to the 15th byte (at or above end_free_memory)
=======
    start_free_memory = (char*)(uintptr_t(uint32_t(start_free_memory) & ~0xFUL)); // Align to 16-byte boundary
    end_free_memory   = (char*)(uintptr_t(uint32_t(end_free_memory)   |  0xFUL)); // Align end_free_memory to the 15th byte (at or above end_free_memory)
>>>>>>> mcu_ctrl

    // Dump command main loop
    while (start_free_memory < end_free_memory) {
      print_hex_address(start_free_memory);             // Print the address
      SERIAL_CHAR(':');
<<<<<<< HEAD
      for (uint8_t i = 0; i < 16; i++) {  // and 16 data bytes
=======
      LOOP_L_N(i, 16) {  // and 16 data bytes
>>>>>>> mcu_ctrl
        if (i == 8) SERIAL_CHAR('-');
        print_hex_byte(start_free_memory[i]);
        SERIAL_CHAR(' ');
      }
      serial_delay(25);
      SERIAL_CHAR('|');                   // Point out non test bytes
<<<<<<< HEAD
      for (uint8_t i = 0; i < 16; i++) {
=======
      LOOP_L_N(i, 16) {
>>>>>>> mcu_ctrl
        char ccc = (char)start_free_memory[i]; // cast to char before automatically casting to char on assignment, in case the compiler is broken
        ccc = (ccc == TEST_BYTE) ? ' ' : '?';
        SERIAL_CHAR(ccc);
      }
      SERIAL_EOL();
      start_free_memory += 16;
      serial_delay(25);
      idle();
    }
  }

<<<<<<< HEAD
  void M100_dump_routine(PGM_P const title, char *start, char *end) {
    serialprintPGM(title);
    SERIAL_EOL();
    //
    // Round the start and end locations to produce full lines of output
    //
    start = (char*)((ptr_int_t)((uint32_t)start & 0xFFFFFFF0)); // Align to 16-byte boundary
    end   = (char*)((ptr_int_t)((uint32_t)end   | 0x0000000F)); // Align end_free_memory to the 15th byte (at or above end_free_memory)
    dump_free_memory(start, end);
=======
  void M100_dump_routine(PGM_P const title, const char * const start, const uintptr_t size) {
    SERIAL_ECHOLNPGM_P(title);
    //
    // Round the start and end locations to produce full lines of output
    //
    const char * const end = start + size - 1;
    dump_free_memory(
      (char*)(uintptr_t(uint32_t(start) & ~0xFUL)), // Align to 16-byte boundary
      (char*)(uintptr_t(uint32_t(end)   |  0xFUL))  // Align end_free_memory to the 15th byte (at or above end_free_memory)
    );
>>>>>>> mcu_ctrl
  }

#endif // M100_FREE_MEMORY_DUMPER

inline int check_for_free_memory_corruption(PGM_P const title) {
<<<<<<< HEAD
  serialprintPGM(title);
=======
  SERIAL_ECHOPGM_P(title);
>>>>>>> mcu_ctrl

  char *start_free_memory = free_memory_start, *end_free_memory = free_memory_end;
  int n = end_free_memory - start_free_memory;

<<<<<<< HEAD
  SERIAL_ECHOPAIR("\nfmc() n=", n);
  SERIAL_ECHOPAIR("\nfree_memory_start=", hex_address(free_memory_start));
  SERIAL_ECHOLNPAIR("  end_free_memory=", hex_address(end_free_memory));

  if (end_free_memory < start_free_memory)  {
    SERIAL_ECHOPGM(" end_free_memory < Heap ");
    // SET_INPUT_PULLUP(63);           // if the developer has a switch wired up to their controller board
    // safe_delay(5);                  // this code can be enabled to pause the display as soon as the
    // while ( READ(63))               // malfunction is detected.   It is currently defaulting to a switch
    //   idle();                       // being on pin-63 which is unassigend and available on most controller
    // safe_delay(20);                 // boards.
    // while ( !READ(63))
    //   idle();
    serial_delay(20);
    #if ENABLED(M100_FREE_MEMORY_DUMPER)
      M100_dump_routine(PSTR("   Memory corruption detected with end_free_memory<Heap\n"), (char*)0x1B80, (char*)0x21FF);
=======
  SERIAL_ECHOLNPAIR("\nfmc() n=", n,
                    "\nfree_memory_start=", hex_address(free_memory_start),
                    "  end=", hex_address(end_free_memory));

  if (end_free_memory < start_free_memory)  {
    SERIAL_ECHOPGM(" end_free_memory < Heap ");
    //SET_INPUT_PULLUP(63);           // if the developer has a switch wired up to their controller board
    //safe_delay(5);                  // this code can be enabled to pause the display as soon as the
    //while ( READ(63))               // malfunction is detected.   It is currently defaulting to a switch
    //  idle();                       // being on pin-63 which is unassigend and available on most controller
    //safe_delay(20);                 // boards.
    //while ( !READ(63))
    //  idle();
    serial_delay(20);
    #if ENABLED(M100_FREE_MEMORY_DUMPER)
      M100_dump_routine(PSTR("   Memory corruption detected with end_free_memory<Heap\n"), (const char*)0x1B80, 0x0680);
>>>>>>> mcu_ctrl
    #endif
  }

  // Scan through the range looking for the biggest block of 0xE5's we can find
  int block_cnt = 0;
  for (int i = 0; i < n; i++) {
    if (start_free_memory[i] == TEST_BYTE) {
      int32_t j = count_test_bytes(start_free_memory + i);
      if (j > 8) {
<<<<<<< HEAD
        // SERIAL_ECHOPAIR("Found ", j);
        // SERIAL_ECHOLNPAIR(" bytes free at ", hex_address(start_free_memory + i));
        i += j;
        block_cnt++;
        SERIAL_ECHOPAIR(" (", block_cnt);
        SERIAL_ECHOPAIR(") found=", j);
        SERIAL_ECHOLNPGM("   ");
=======
        //SERIAL_ECHOPAIR("Found ", j);
        //SERIAL_ECHOLNPAIR(" bytes free at ", hex_address(start_free_memory + i));
        i += j;
        block_cnt++;
        SERIAL_ECHOLNPAIR(" (", block_cnt, ") found=", j);
>>>>>>> mcu_ctrl
      }
    }
  }
  SERIAL_ECHOPAIR("  block_found=", block_cnt);

  if (block_cnt != 1)
    SERIAL_ECHOLNPGM("\nMemory Corruption detected in free memory area.");

  if (block_cnt == 0)       // Make sure the special case of no free blocks shows up as an
<<<<<<< HEAD
    block_cnt = -1;         // error to the calling code!

  SERIAL_ECHOPGM(" return=");
  if (block_cnt == 1) {
    SERIAL_CHAR('0');       // if the block_cnt is 1, nothing has broken up the free memory
    SERIAL_EOL();             // area and it is appropriate to say 'no corruption'.
=======
    block_cnt = -1;         //  error to the calling code!

  SERIAL_ECHOPGM(" return=");
  if (block_cnt == 1) {
    SERIAL_CHAR('0');       // If the block_cnt is 1, nothing has broken up the free memory
    SERIAL_EOL();           //  area and it is appropriate to say 'no corruption'.
>>>>>>> mcu_ctrl
    return 0;
  }
  SERIAL_ECHOLNPGM("true");
  return block_cnt;
}

/**
 * M100 F
 *  Return the number of free bytes in the memory pool,
 *  with other vital statistics defining the pool.
 */
inline void free_memory_pool_report(char * const start_free_memory, const int32_t size) {
  int32_t max_cnt = -1, block_cnt = 0;
  char *max_addr = nullptr;
  // Find the longest block of test bytes in the buffer
  for (int32_t i = 0; i < size; i++) {
    char *addr = start_free_memory + i;
    if (*addr == TEST_BYTE) {
      const int32_t j = count_test_bytes(addr);
      if (j > 8) {
<<<<<<< HEAD
        SERIAL_ECHOPAIR("Found ", j);
        SERIAL_ECHOLNPAIR(" bytes free at ", hex_address(addr));
=======
        SERIAL_ECHOLNPAIR("Found ", j, " bytes free at ", hex_address(addr));
>>>>>>> mcu_ctrl
        if (j > max_cnt) {
          max_cnt  = j;
          max_addr = addr;
        }
        i += j;
        block_cnt++;
      }
    }
  }
<<<<<<< HEAD
  if (block_cnt > 1) {
    SERIAL_ECHOLNPGM("\nMemory Corruption detected in free memory area.");
    SERIAL_ECHOPAIR("\nLargest free block is ", max_cnt);
    SERIAL_ECHOLNPAIR(" bytes at ", hex_address(max_addr));
  }
=======
  if (block_cnt > 1) SERIAL_ECHOLNPAIR(
    "\nMemory Corruption detected in free memory area."
    "\nLargest free block is ", max_cnt, " bytes at ", hex_address(max_addr)
  );
>>>>>>> mcu_ctrl
  SERIAL_ECHOLNPAIR("check_for_free_memory_corruption() = ", check_for_free_memory_corruption(PSTR("M100 F ")));
}

#if ENABLED(M100_FREE_MEMORY_CORRUPTOR)
  /**
   * M100 C<num>
   *  Corrupt <num> locations in the free memory pool and report the corrupt addresses.
   *  This is useful to check the correctness of the M100 D and the M100 F commands.
   */
<<<<<<< HEAD
  inline void corrupt_free_memory(char *start_free_memory, const uint32_t size) {
=======
  inline void corrupt_free_memory(char *start_free_memory, const uintptr_t size) {
>>>>>>> mcu_ctrl
    start_free_memory += 8;
    const uint32_t near_top = top_of_stack() - start_free_memory - 250, // -250 to avoid interrupt activity that's altered the stack.
                   j = near_top / (size + 1);

<<<<<<< HEAD
    SERIAL_ECHOLNPGM("Corrupting free memory block.\n");
=======
    SERIAL_ECHOLNPGM("Corrupting free memory block.");
>>>>>>> mcu_ctrl
    for (uint32_t i = 1; i <= size; i++) {
      char * const addr = start_free_memory + i * j;
      *addr = i;
      SERIAL_ECHOPAIR("\nCorrupting address: ", hex_address(addr));
    }
    SERIAL_EOL();
  }
#endif // M100_FREE_MEMORY_CORRUPTOR

/**
 * M100 I
 *  Init memory for the M100 tests. (Automatically applied on the first M100.)
 */
inline void init_free_memory(char *start_free_memory, int32_t size) {
  SERIAL_ECHOLNPGM("Initializing free memory block.\n\n");

  size -= 250;    // -250 to avoid interrupt activity that's altered the stack.
  if (size < 0) {
    SERIAL_ECHOLNPGM("Unable to initialize.\n");
    return;
  }

<<<<<<< HEAD
  start_free_memory += 8;       // move a few bytes away from the heap just because we don't want
                  // to be altering memory that close to it.
=======
  start_free_memory += 8; // move a few bytes away from the heap just because we
                          // don't want to be altering memory that close to it.
>>>>>>> mcu_ctrl
  memset(start_free_memory, TEST_BYTE, size);

  SERIAL_ECHO(size);
  SERIAL_ECHOLNPGM(" bytes of memory initialized.\n");

  for (int32_t i = 0; i < size; i++) {
    if (start_free_memory[i] != TEST_BYTE) {
      SERIAL_ECHOPAIR("? address : ", hex_address(start_free_memory + i));
      SERIAL_ECHOLNPAIR("=", hex_byte(start_free_memory[i]));
      SERIAL_EOL();
    }
  }
}

/**
 * M100: Free Memory Check
 */
void GcodeSuite::M100() {
<<<<<<< HEAD

  char *sp = top_of_stack();
  if (!free_memory_end) free_memory_end = sp - MEMORY_END_CORRECTION;
  SERIAL_ECHOPAIR("\nbss_end               : ", hex_address(end_bss));
  if (heaplimit) SERIAL_ECHOPAIR("\n__heaplimit           : ", hex_address(heaplimit));
  SERIAL_ECHOPAIR("\nfree_memory_start     : ", hex_address(free_memory_start));
  if (stacklimit) SERIAL_ECHOPAIR("\n__stacklimit          : ", hex_address(stacklimit));
  SERIAL_ECHOPAIR("\nfree_memory_end       : ", hex_address(free_memory_end));
  if (MEMORY_END_CORRECTION)  SERIAL_ECHOPAIR("\nMEMORY_END_CORRECTION: ", MEMORY_END_CORRECTION);
  SERIAL_ECHOLNPAIR("\nStack Pointer         : ", hex_address(sp));
=======
  char *sp = top_of_stack();
  if (!free_memory_end) free_memory_end = sp - MEMORY_END_CORRECTION;
                  SERIAL_ECHOPAIR("\nbss_end               : ", hex_address(end_bss));
  if (heaplimit)  SERIAL_ECHOPAIR("\n__heaplimit           : ", hex_address(heaplimit));
                  SERIAL_ECHOPAIR("\nfree_memory_start     : ", hex_address(free_memory_start));
  if (stacklimit) SERIAL_ECHOPAIR("\n__stacklimit          : ", hex_address(stacklimit));
                  SERIAL_ECHOPAIR("\nfree_memory_end       : ", hex_address(free_memory_end));
  if (MEMORY_END_CORRECTION)
                  SERIAL_ECHOPAIR("\nMEMORY_END_CORRECTION : ", MEMORY_END_CORRECTION);
                  SERIAL_ECHOLNPAIR("\nStack Pointer       : ", hex_address(sp));
>>>>>>> mcu_ctrl

  // Always init on the first invocation of M100
  static bool m100_not_initialized = true;
  if (m100_not_initialized || parser.seen('I')) {
    m100_not_initialized = false;
    init_free_memory(free_memory_start, free_memory_end - free_memory_start);
  }

  #if ENABLED(M100_FREE_MEMORY_DUMPER)
    if (parser.seen('D'))
      return dump_free_memory(free_memory_start, free_memory_end);
  #endif

  if (parser.seen('F'))
    return free_memory_pool_report(free_memory_start, free_memory_end - free_memory_start);

  #if ENABLED(M100_FREE_MEMORY_CORRUPTOR)
<<<<<<< HEAD

    if (parser.seen('C'))
      return corrupt_free_memory(free_memory_start, parser.value_int());

=======
    if (parser.seen('C'))
      return corrupt_free_memory(free_memory_start, parser.value_int());
>>>>>>> mcu_ctrl
  #endif
}

#endif // M100_FREE_MEMORY_WATCHER
