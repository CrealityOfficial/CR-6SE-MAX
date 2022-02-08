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
 * queue.h - The G-code command queue, which holds commands before they
 *           go to the parser and dispatcher.
 */

#include "../inc/MarlinConfig.h"

class GCodeQueue {
public:
  /**
<<<<<<< HEAD
   * GCode line number handling. Hosts may include line numbers when sending
   * commands to Marlin, and lines will be checked for sequentiality.
   * M110 N<int> sets the current line number.
   */
  static long last_N, stopped_N;

  static inline void stop() { stopped_N = last_N; }

  /**
   * GCode Command Queue
   * A simple ring buffer of BUFSIZE command strings.
=======
   * The buffers per serial port.
   */
  struct SerialState {
    /**
     * GCode line number handling. Hosts may include line numbers when sending
     * commands to Marlin, and lines will be checked for sequentiality.
     * M110 N<int> sets the current line number.
     */
    long last_N;
    int count;                      //!< Number of characters read in the current line of serial input
    char line_buffer[MAX_CMD_SIZE]; //!< The current line accumulator
    uint8_t input_state;            //!< The input state
  };

  static SerialState serial_state[NUM_SERIAL]; //!< Serial states for each serial port

  /**
   * GCode Command Queue
   * A simple (circular) ring buffer of BUFSIZE command strings.
>>>>>>> mcu_ctrl
   *
   * Commands are copied into this buffer by the command injectors
   * (immediate, serial, sd card) and they are processed sequentially by
   * the main loop. The gcode.process_next_command method parses the next
   * command and hands off execution to individual handler functions.
   */
<<<<<<< HEAD
  static uint8_t length,  // Count of commands in the queue
                 index_r; // Ring buffer read position

  static char command_buffer[BUFSIZE][MAX_CMD_SIZE];

  /*
   * The port that the command was received on
   */
  #if NUM_SERIAL > 1
    static int16_t port[BUFSIZE];
  #endif

  GCodeQueue();
=======
  struct CommandLine {
    char buffer[MAX_CMD_SIZE];      //!< The command buffer
    bool skip_ok;                   //!< Skip sending ok when command is processed?
    #if ENABLED(HAS_MULTI_SERIAL)
      serial_index_t port;          //!< Serial port the command was received on
    #endif
  };

  /**
   * A handy ring buffer type
   */
  struct RingBuffer {
    uint8_t length,                 //!< Number of commands in the queue
            index_r,                //!< Ring buffer's read position
            index_w;                //!< Ring buffer's write position
    CommandLine commands[BUFSIZE];  //!< The ring buffer of commands

    inline serial_index_t command_port() const { return TERN0(HAS_MULTI_SERIAL, commands[index_r].port); }

    inline void clear() { length = index_r = index_w = 0; }

    void advance_pos(uint8_t &p, const int inc) { if (++p >= BUFSIZE) p = 0; length += inc; }

    void commit_command(bool skip_ok
      OPTARG(HAS_MULTI_SERIAL, serial_index_t serial_ind = serial_index_t())
    );

    bool enqueue(const char *cmd, bool skip_ok = true
      OPTARG(HAS_MULTI_SERIAL, serial_index_t serial_ind = serial_index_t())
    );

    void ok_to_send();

    inline bool full(uint8_t cmdCount=1) const { return length > (BUFSIZE - cmdCount); }

    inline bool occupied() const { return length != 0; }

    inline bool empty() const { return !occupied(); }

    inline CommandLine& peek_next_command() { return commands[index_r]; }

    inline char* peek_next_command_string() { return peek_next_command().buffer; }
  };

  /**
   * The ring buffer of commands
   */
  static RingBuffer ring_buffer;
>>>>>>> mcu_ctrl

  /**
   * Clear the Marlin command queue
   */
<<<<<<< HEAD
  static void clear();

  /**
   * Enqueue one or many commands to run from program memory.
   * Aborts the current queue, if any.
   * Note: process_injected_command() will process them.
   */
  static void inject_P(PGM_P const pgcode);
=======
  static void clear() { ring_buffer.clear(); }

  /**
   * Next Injected Command (PROGMEM) pointer. (nullptr == empty)
   * Internal commands are enqueued ahead of serial / SD commands.
   */
  static PGM_P injected_commands_P;

  /**
   * Injected Commands (SRAM)
   */
  static char injected_commands[64];

  /**
   * Enqueue command(s) to run from PROGMEM. Drained by process_injected_command_P().
   * Don't inject comments or use leading spaces!
   * Aborts the current PROGMEM queue so only use for one or two commands.
   */
  static inline void inject_P(PGM_P const pgcode) { injected_commands_P = pgcode; }

  /**
   * Enqueue command(s) to run from SRAM. Drained by process_injected_command().
   * Aborts the current SRAM queue so only use for one or two commands.
   */
  static inline void inject(char * const gcode) {
    strncpy(injected_commands, gcode, sizeof(injected_commands) - 1);
  }
>>>>>>> mcu_ctrl

  /**
   * Enqueue and return only when commands are actually enqueued
   */
<<<<<<< HEAD
  static void enqueue_one_now(const char* cmd);
=======
  static void enqueue_one_now(const char *cmd);

  /**
   * Attempt to enqueue a single G-code command
   * and return 'true' if successful.
   */
  static bool enqueue_one_P(PGM_P const pgcode);
>>>>>>> mcu_ctrl

  /**
   * Enqueue from program memory and return only when commands are actually enqueued
   */
  static void enqueue_now_P(PGM_P const cmd);

  /**
   * Check whether there are any commands yet to be executed
   */
<<<<<<< HEAD
  static bool has_commands_queued();
=======
  static bool has_commands_queued() { return ring_buffer.length || injected_commands_P || injected_commands[0]; }
>>>>>>> mcu_ctrl

  /**
   * Get the next command in the queue, optionally log it to SD, then dispatch it
   */
  static void advance();

  /**
<<<<<<< HEAD
=======
   * Run the entire queue in-place
   */
  static void exhaust();

  /**
>>>>>>> mcu_ctrl
   * Add to the circular command queue the next command from:
   *  - The command-injection queue (injected_commands_P)
   *  - The active serial input (usually USB)
   *  - The SD card file being actively printed
   */
  static void get_available_commands();

  /**
   * Send an "ok" message to the host, indicating
   * that a command was successfully processed.
   *
   * If ADVANCED_OK is enabled also include:
   *   N<int>  Line number of the command, if any
   *   P<int>  Planner space remaining
   *   B<int>  Block queue space remaining
   */
<<<<<<< HEAD
  static void ok_to_send();
=======
  static inline void ok_to_send() { ring_buffer.ok_to_send(); }
>>>>>>> mcu_ctrl

  /**
   * Clear the serial line and request a resend of
   * the next expected line number.
   */
<<<<<<< HEAD
  static void flush_and_request_resend();

private:

  static uint8_t index_w;  // Ring buffer write position
=======
  static void flush_and_request_resend(const serial_index_t serial_ind);

  /**
   * (Re)Set the current line number for the last received command
   */
  static inline void set_current_line_number(long n) { serial_state[ring_buffer.command_port().index].last_N = n; }

private:
>>>>>>> mcu_ctrl

  static void get_serial_commands();

  #if ENABLED(SDSUPPORT)
    static void get_sdcard_commands();
  #endif

<<<<<<< HEAD
  static void _commit_command(bool say_ok
    #if NUM_SERIAL > 1
      , int16_t p=-1
    #endif
  );

  static bool _enqueue(const char* cmd, bool say_ok=false
    #if NUM_SERIAL > 1
      , int16_t p=-1
    #endif
  );

  // Process the next "immediate" command
=======
  // Process the next "immediate" command (PROGMEM)
  static bool process_injected_command_P();

  // Process the next "immediate" command (SRAM)
>>>>>>> mcu_ctrl
  static bool process_injected_command();

  /**
   * Enqueue with Serial Echo
   * Return true on success
   */
<<<<<<< HEAD
  static bool enqueue_one(const char* cmd);

  static void gcode_line_error(PGM_P const err, const int8_t port);

};

extern GCodeQueue queue;
=======
  static bool enqueue_one(const char *cmd);

  static void gcode_line_error(PGM_P const err, const serial_index_t serial_ind);

  friend class GcodeSuite;
};

extern GCodeQueue queue;

extern const char G28_STR[];
>>>>>>> mcu_ctrl
