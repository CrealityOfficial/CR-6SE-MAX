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
 * queue.cpp - The G-code command queue
 */

#include "queue.h"
GCodeQueue queue;

#include "gcode.h"

<<<<<<< HEAD
#ifdef RTS_AVAILABLE
  #include "../lcd/dwin/LCD_RTS.h"
#endif
#include "../lcd/ultralcd.h"
#include "../sd/cardreader.h"
#include "../module/planner.h"
#include "../module/temperature.h"
#include "../Marlin.h"
=======
#include "../lcd/marlinui.h"
#include "../sd/cardreader.h"
#include "../module/motion.h"
#include "../module/planner.h"
#include "../module/temperature.h"
#include "../MarlinCore.h"
#include "../core/bug_on.h"
>>>>>>> mcu_ctrl

#if ENABLED(PRINTER_EVENT_LEDS)
  #include "../feature/leds/printer_event_leds.h"
#endif

<<<<<<< HEAD
#if ENABLED(BINARY_FILE_TRANSFER)
  #include "../feature/binary_protocol.h"
#endif

#if ENABLED(POWER_LOSS_RECOVERY)
  #include "../feature/power_loss_recovery.h"
#endif

/**
 * GCode line number handling. Hosts may opt to include line numbers when
 * sending commands to Marlin, and lines will be checked for sequentiality.
 * M110 N<int> sets the current line number.
 */
long gcode_N, GCodeQueue::last_N, GCodeQueue::stopped_N = 0;

/**
 * GCode Command Queue
 * A simple ring buffer of BUFSIZE command strings.
 *
 * Commands are copied into this buffer by the command injectors
 * (immediate, serial, sd card) and they are processed sequentially by
 * the main loop. The gcode.process_next_command method parses the next
 * command and hands off execution to individual handler functions.
 */
uint8_t GCodeQueue::length = 0,  // Count of commands in the queue
        GCodeQueue::index_r = 0, // Ring buffer read position
        GCodeQueue::index_w = 0; // Ring buffer write position

char GCodeQueue::command_buffer[BUFSIZE][MAX_CMD_SIZE];

/*
 * The port that the command was received on
 */
#if NUM_SERIAL > 1
  int16_t GCodeQueue::port[BUFSIZE];
=======
#if HAS_ETHERNET
  #include "../feature/ethernet.h"
#endif

#if ENABLED(BINARY_FILE_TRANSFER)
  #include "../feature/binary_stream.h"
#endif

#if ENABLED(POWER_LOSS_RECOVERY)
  #include "../feature/powerloss.h"
#endif

#if ENABLED(GCODE_REPEAT_MARKERS)
  #include "../feature/repeat.h"
#endif

// Frequently used G-code strings
PGMSTR(G28_STR, "G28");

GCodeQueue::SerialState GCodeQueue::serial_state[NUM_SERIAL] = { 0 };
GCodeQueue::RingBuffer GCodeQueue::ring_buffer = { 0 };

#if NO_TIMEOUTS > 0
  static millis_t last_command_time = 0;
>>>>>>> mcu_ctrl
#endif

/**
 * Serial command injection
 */

<<<<<<< HEAD
// Number of characters read in the current line of serial input
static int serial_count[NUM_SERIAL] = { 0 };

bool send_ok[BUFSIZE];

/**
 * Next Injected Command pointer. nullptr if no commands are being injected.
 * Used by Marlin internally to ensure that commands initiated from within
 * are enqueued ahead of any pending serial or sd card commands.
 */
static PGM_P injected_commands_P = nullptr;

GCodeQueue::GCodeQueue() {
  // Send "ok" after commands by default
  for (uint8_t i = 0; i < COUNT(send_ok); i++) send_ok[i] = true;
}

/**
 * Check whether there are any commands yet to be executed
 */
bool GCodeQueue::has_commands_queued() {
  return queue.length || injected_commands_P;
}

/**
 * Clear the Marlin command queue
 */
void GCodeQueue::clear() {
  index_r = index_w = length = 0;
}

/**
 * Once a new command is in the ring buffer, call this to commit it
 */
void GCodeQueue::_commit_command(bool say_ok
  #if NUM_SERIAL > 1
    , int16_t p/*=-1*/
  #endif
) {
  send_ok[index_w] = say_ok;
  #if NUM_SERIAL > 1
    port[index_w] = p;
  #endif
  #if ENABLED(POWER_LOSS_RECOVERY)
    recovery.commit_sdpos(index_w);
  #endif
  if (++index_w >= BUFSIZE) index_w = 0;
  length++;
=======
/**
 * Next Injected PROGMEM Command pointer. (nullptr == empty)
 * Internal commands are enqueued ahead of serial / SD commands.
 */
PGM_P GCodeQueue::injected_commands_P; // = nullptr

/**
 * Injected SRAM Commands
 */
char GCodeQueue::injected_commands[64]; // = { 0 }


void GCodeQueue::RingBuffer::commit_command(bool skip_ok
  OPTARG(HAS_MULTI_SERIAL, serial_index_t serial_ind/*=-1*/)
) {
  commands[index_w].skip_ok = skip_ok;
  TERN_(HAS_MULTI_SERIAL, commands[index_w].port = serial_ind);
  TERN_(POWER_LOSS_RECOVERY, recovery.commit_sdpos(index_w));
  advance_pos(index_w, 1);
>>>>>>> mcu_ctrl
}

/**
 * Copy a command from RAM into the main command buffer.
 * Return true if the command was successfully added.
 * Return false for a full buffer, or if the 'command' is a comment.
 */
<<<<<<< HEAD
bool GCodeQueue::_enqueue(const char* cmd, bool say_ok/*=false*/
  #if NUM_SERIAL > 1
    , int16_t pn/*=-1*/
  #endif
) {
  if (*cmd == ';' || length >= BUFSIZE) return false;
  strcpy(command_buffer[index_w], cmd);
  _commit_command(say_ok
    #if NUM_SERIAL > 1
      , pn
=======
bool GCodeQueue::RingBuffer::enqueue(const char *cmd, bool skip_ok/*=true*/
  OPTARG(HAS_MULTI_SERIAL, serial_index_t serial_ind/*=-1*/)
) {
  if (*cmd == ';' || length >= BUFSIZE) return false;
  strcpy(commands[index_w].buffer, cmd);
  commit_command(skip_ok
    #if HAS_MULTI_SERIAL
      , serial_ind
>>>>>>> mcu_ctrl
    #endif
  );
  return true;
}

/**
 * Enqueue with Serial Echo
 * Return true if the command was consumed
 */
<<<<<<< HEAD
bool GCodeQueue::enqueue_one(const char* cmd) {

  //SERIAL_ECHOPGM("enqueue_one(\"");
  //SERIAL_ECHO(cmd);
  //SERIAL_ECHOPGM("\") \n");

  if (*cmd == 0 || *cmd == '\n' || *cmd == '\r') return true;

  if (_enqueue(cmd)) {
    SERIAL_ECHO_START();
    SERIAL_ECHOLNPAIR(MSG_ENQUEUEING, cmd, "\"");
=======
bool GCodeQueue::enqueue_one(const char *cmd) {
  //SERIAL_ECHOLNPAIR("enqueue_one(\"", cmd, "\")");

  if (*cmd == 0 || ISEOL(*cmd)) return true;

  if (ring_buffer.enqueue(cmd)) {
    SERIAL_ECHO_MSG(STR_ENQUEUEING, cmd, "\"");
>>>>>>> mcu_ctrl
    return true;
  }
  return false;
}

/**
<<<<<<< HEAD
 * Process the next "immediate" command.
 * Return 'true' if any commands were processed,
 * or remain to process.
 */
bool GCodeQueue::process_injected_command() {
  if (injected_commands_P == nullptr) return false;
=======
 * Process the next "immediate" command from PROGMEM.
 * Return 'true' if any commands were processed.
 */
bool GCodeQueue::process_injected_command_P() {
  if (!injected_commands_P) return false;
>>>>>>> mcu_ctrl

  char c;
  size_t i = 0;
  while ((c = pgm_read_byte(&injected_commands_P[i])) && c != '\n') i++;

  // Extract current command and move pointer to next command
  char cmd[i + 1];
  memcpy_P(cmd, injected_commands_P, i);
  cmd[i] = '\0';
  injected_commands_P = c ? injected_commands_P + i + 1 : nullptr;

  // Execute command if non-blank
  if (i) {
    parser.parse(cmd);
<<<<<<< HEAD
    PORT_REDIRECT(SERIAL_PORT);
=======
>>>>>>> mcu_ctrl
    gcode.process_parsed_command();
  }
  return true;
}

/**
<<<<<<< HEAD
 * Enqueue one or many commands to run from program memory.
 * Do not inject a comment or use leading spaces!
 * Aborts the current queue, if any.
 * Note: process_injected_command() will be called to drain any commands afterwards
 */
void GCodeQueue::inject_P(PGM_P const pgcode) { injected_commands_P = pgcode; }
=======
 * Process the next "immediate" command from SRAM.
 * Return 'true' if any commands were processed.
 */
bool GCodeQueue::process_injected_command() {
  if (injected_commands[0] == '\0') return false;

  char c;
  size_t i = 0;
  while ((c = injected_commands[i]) && c != '\n') i++;

  // Execute a non-blank command
  if (i) {
    injected_commands[i] = '\0';
    parser.parse(injected_commands);
    gcode.process_parsed_command();
  }

  // Copy the next command into place
  for (
    uint8_t d = 0, s = i + !!c;                     // dst, src
    (injected_commands[d] = injected_commands[s]);  // copy, exit if 0
    d++, s++                                        // next dst, src
  );

  return true;
}
>>>>>>> mcu_ctrl

/**
 * Enqueue and return only when commands are actually enqueued.
 * Never call this from a G-code handler!
 */
<<<<<<< HEAD
void GCodeQueue::enqueue_one_now(const char* cmd) { while (!enqueue_one(cmd)) idle(); }
=======
void GCodeQueue::enqueue_one_now(const char *cmd) { while (!enqueue_one(cmd)) idle(); }

/**
 * Attempt to enqueue a single G-code command
 * and return 'true' if successful.
 */
bool GCodeQueue::enqueue_one_P(PGM_P const pgcode) {
  size_t i = 0;
  PGM_P p = pgcode;
  char c;
  while ((c = pgm_read_byte(&p[i])) && c != '\n') i++;
  char cmd[i + 1];
  memcpy_P(cmd, p, i);
  cmd[i] = '\0';
  return ring_buffer.enqueue(cmd);
}
>>>>>>> mcu_ctrl

/**
 * Enqueue from program memory and return only when commands are actually enqueued
 * Never call this from a G-code handler!
 */
void GCodeQueue::enqueue_now_P(PGM_P const pgcode) {
  size_t i = 0;
  PGM_P p = pgcode;
  for (;;) {
    char c;
    while ((c = pgm_read_byte(&p[i])) && c != '\n') i++;
    char cmd[i + 1];
    memcpy_P(cmd, p, i);
    cmd[i] = '\0';
    enqueue_one_now(cmd);
    if (!c) break;
    p += i + 1;
  }
}

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
void GCodeQueue::ok_to_send() {
  #if NUM_SERIAL > 1
    const int16_t pn = port[index_r];
    if (pn < 0) return;
    PORT_REDIRECT(pn);
  #endif
  if (!send_ok[index_r]) return;
  SERIAL_ECHOPGM(MSG_OK);
  #if ENABLED(ADVANCED_OK)
    char* p = command_buffer[index_r];
    if (*p == 'N') {
      SERIAL_ECHO(' ');
      SERIAL_ECHO(*p++);
      while (NUMERIC_SIGNED(*p))
        SERIAL_ECHO(*p++);
    }
    SERIAL_ECHOPGM(" P"); SERIAL_ECHO(int(BLOCK_BUFFER_SIZE - planner.movesplanned() - 1));
    SERIAL_ECHOPGM(" B"); SERIAL_ECHO(BUFSIZE - length);
=======
void GCodeQueue::RingBuffer::ok_to_send() {
  #if NO_TIMEOUTS > 0
    // Start counting from the last command's execution
    last_command_time = millis();
  #endif
  CommandLine &command = commands[index_r];
  #if HAS_MULTI_SERIAL
    const serial_index_t serial_ind = command.port;
    if (!serial_ind.valid()) return;              // Optimization here, skip processing if it's not going anywhere
    PORT_REDIRECT(SERIAL_PORTMASK(serial_ind));   // Reply to the serial port that sent the command
  #endif
  if (command.skip_ok) return;
  SERIAL_ECHOPGM(STR_OK);
  #if ENABLED(ADVANCED_OK)
    char* p = command.buffer;
    if (*p == 'N') {
      SERIAL_CHAR(' ', *p++);
      while (NUMERIC_SIGNED(*p))
        SERIAL_CHAR(*p++);
    }
    SERIAL_ECHOPAIR_P(SP_P_STR, planner.moves_free(),
                      SP_B_STR, BUFSIZE - length);
>>>>>>> mcu_ctrl
  #endif
  SERIAL_EOL();
}

/**
 * Send a "Resend: nnn" message to the host to
 * indicate that a command needs to be re-sent.
 */
<<<<<<< HEAD
void GCodeQueue::flush_and_request_resend() {
  #if NUM_SERIAL > 1
    const int16_t p = port[index_r];
    if (p < 0) return;
    PORT_REDIRECT(p);
  #endif
  SERIAL_FLUSH();
  SERIAL_ECHOPGM(MSG_RESEND);
  SERIAL_ECHOLN(last_N + 1);
  ok_to_send();
}

inline bool serial_data_available() {
  return false
    || MYSERIAL0.available()
    #if NUM_SERIAL > 1
      || MYSERIAL1.available()
    #endif
  ;
}

inline int read_serial(const uint8_t index) {
  switch (index) {
    case 0: return MYSERIAL0.read();
    #if NUM_SERIAL > 1
      case 1: return MYSERIAL1.read();
    #endif
    default: return -1;
  }
}

void GCodeQueue::gcode_line_error(PGM_P const err, const int8_t port) {
  PORT_REDIRECT(port);
  SERIAL_ERROR_START();
  serialprintPGM(err);
  SERIAL_ECHOLN(last_N);
  while (read_serial(port) != -1);           // clear out the RX buffer
  flush_and_request_resend();
  serial_count[port] = 0;
=======
void GCodeQueue::flush_and_request_resend(const serial_index_t serial_ind) {
  #if HAS_MULTI_SERIAL
    if (!serial_ind.valid()) return;              // Optimization here, skip if the command came from SD or Flash Drive
    PORT_REDIRECT(SERIAL_PORTMASK(serial_ind));   // Reply to the serial port that sent the command
  #endif
  SERIAL_FLUSH();
  SERIAL_ECHOLNPAIR(STR_RESEND, serial_state[serial_ind.index].last_N + 1);
  SERIAL_ECHOLNPGM(STR_OK);
}

static bool serial_data_available(serial_index_t index) {
  const int a = SERIAL_IMPL.available(index);
  #if BOTH(RX_BUFFER_MONITOR, RX_BUFFER_SIZE)
    if (a > RX_BUFFER_SIZE - 2) {
      PORT_REDIRECT(SERIAL_PORTMASK(index));
      SERIAL_ERROR_MSG("RX BUF overflow, increase RX_BUFFER_SIZE: ", a);
    }
  #endif
  return a > 0;
}

#if NO_TIMEOUTS > 0
  // Multiserial already handles dispatch to/from multiple ports
  static bool any_serial_data_available() {
    LOOP_L_N(p, NUM_SERIAL)
      if (serial_data_available(p))
        return true;
    return false;
  }
#endif

inline int read_serial(const serial_index_t index) { return SERIAL_IMPL.read(index); }

void GCodeQueue::gcode_line_error(PGM_P const err, const serial_index_t serial_ind) {
  PORT_REDIRECT(SERIAL_PORTMASK(serial_ind)); // Reply to the serial port that sent the command
  SERIAL_ERROR_START();
  SERIAL_ECHOLNPAIR_P(err, serial_state[serial_ind.index].last_N);
  while (read_serial(serial_ind) != -1) { /* nada */ } // Clear out the RX buffer. Why don't use flush here ?
  flush_and_request_resend(serial_ind);
  serial_state[serial_ind.index].count = 0;
>>>>>>> mcu_ctrl
}

FORCE_INLINE bool is_M29(const char * const cmd) {  // matches "M29" & "M29 ", but not "M290", etc
  const char * const m29 = strstr_P(cmd, PSTR("M29"));
  return m29 && !NUMERIC(m29[3]);
}

<<<<<<< HEAD
=======
#define PS_NORMAL 0
#define PS_EOL    1
#define PS_QUOTED 2
#define PS_PAREN  3
#define PS_ESC    4

inline void process_stream_char(const char c, uint8_t &sis, char (&buff)[MAX_CMD_SIZE], int &ind) {

  if (sis == PS_EOL) return;    // EOL comment or overflow

  #if ENABLED(PAREN_COMMENTS)
    else if (sis == PS_PAREN) { // Inline comment
      if (c == ')') sis = PS_NORMAL;
      return;
    }
  #endif

  else if (sis >= PS_ESC)       // End escaped char
    sis -= PS_ESC;

  else if (c == '\\') {         // Start escaped char
    sis += PS_ESC;
    if (sis == PS_ESC) return;  // Keep if quoting
  }

  #if ENABLED(GCODE_QUOTED_STRINGS)

    else if (sis == PS_QUOTED) {
      if (c == '"') sis = PS_NORMAL; // End quoted string
    }
    else if (c == '"')          // Start quoted string
      sis = PS_QUOTED;

  #endif

  else if (c == ';') {          // Start end-of-line comment
    sis = PS_EOL;
    return;
  }

  #if ENABLED(PAREN_COMMENTS)
    else if (c == '(') {        // Start inline comment
      sis = PS_PAREN;
      return;
    }
  #endif

  // Backspace erases previous characters
  if (c == 0x08) {
    if (ind) buff[--ind] = '\0';
  }
  else {
    buff[ind++] = c;
    if (ind >= MAX_CMD_SIZE - 1)
      sis = PS_EOL;             // Skip the rest on overflow
  }
}

/**
 * Handle a line being completed. For an empty line
 * keep sensor readings going and watchdog alive.
 */
inline bool process_line_done(uint8_t &sis, char (&buff)[MAX_CMD_SIZE], int &ind) {
  sis = PS_NORMAL;                    // "Normal" Serial Input State
  buff[ind] = '\0';                   // Of course, I'm a Terminator.
  const bool is_empty = (ind == 0);   // An empty line?
  if (is_empty)
    thermalManager.manage_heater();   // Keep sensors satisfied
  else
    ind = 0;                          // Start a new line
  return is_empty;                    // Inform the caller
}

>>>>>>> mcu_ctrl
/**
 * Get all commands waiting on the serial port and queue them.
 * Exit when the buffer is full or when no more characters are
 * left on the serial port.
 */
void GCodeQueue::get_serial_commands() {
<<<<<<< HEAD
  static char serial_line_buffer[NUM_SERIAL][MAX_CMD_SIZE];
  static bool serial_comment_mode[NUM_SERIAL] = { false }
              #if ENABLED(PAREN_COMMENTS)
                , serial_comment_paren_mode[NUM_SERIAL] = { false }
              #endif
            ;

=======
>>>>>>> mcu_ctrl
  #if ENABLED(BINARY_FILE_TRANSFER)
    if (card.flag.binary_mode) {
      /**
       * For binary stream file transfer, use serial_line_buffer as the working
       * receive buffer (which limits the packet size to MAX_CMD_SIZE).
       * The receive buffer also limits the packet size for reliable transmission.
       */
<<<<<<< HEAD
      binaryStream[card.transfer_port_index].receive(serial_line_buffer[card.transfer_port_index]);
=======
      binaryStream[card.transfer_port_index.index].receive(serial_state[card.transfer_port_index.index].line_buffer);
>>>>>>> mcu_ctrl
      return;
    }
  #endif

  // If the command buffer is empty for too long,
  // send "wait" to indicate Marlin is still waiting.
  #if NO_TIMEOUTS > 0
<<<<<<< HEAD
    static millis_t last_command_time = 0;
    const millis_t ms = millis();
    if (length == 0 && !serial_data_available() && ELAPSED(ms, last_command_time + NO_TIMEOUTS)) {
      SERIAL_ECHOLNPGM(MSG_WAIT);
=======
    const millis_t ms = millis();
    if (ring_buffer.empty() && !any_serial_data_available() && ELAPSED(ms, last_command_time + NO_TIMEOUTS)) {
      SERIAL_ECHOLNPGM(STR_WAIT);
>>>>>>> mcu_ctrl
      last_command_time = ms;
    }
  #endif

<<<<<<< HEAD
  /**
   * Loop while serial characters are incoming and the queue is not full
   */
  while (length < BUFSIZE && serial_data_available()) {
    for (uint8_t i = 0; i < NUM_SERIAL; ++i) {
      int c;
      if ((c = read_serial(i)) < 0) continue;

      char serial_char = c;

      /**
       * If the character ends the line
       */
      if (serial_char == '\n' || serial_char == '\r') {

        // Start with comment mode off
        serial_comment_mode[i] = false;
        #if ENABLED(PAREN_COMMENTS)
          serial_comment_paren_mode[i] = false;
        #endif

        // Skip empty lines and comments
        if (!serial_count[i]) { thermalManager.manage_heater(); continue; }

        serial_line_buffer[i][serial_count[i]] = 0;       // Terminate string
        serial_count[i] = 0;                              // Reset buffer

        char* command = serial_line_buffer[i];

        while (*command == ' ') command++;                // Skip leading spaces
=======
  // Loop while serial characters are incoming and the queue is not full
  for (bool hadData = true; hadData;) {
    // Unless a serial port has data, this will exit on next iteration
    hadData = false;

    LOOP_L_N(p, NUM_SERIAL) {
      // Check if the queue is full and exit if it is.
      if (ring_buffer.full()) return;

      // No data for this port ? Skip it
      if (!serial_data_available(p)) continue;

      // Ok, we have some data to process, let's make progress here
      hadData = true;

      const int c = read_serial(p);
      if (c < 0) {
        // This should never happen, let's log it
        PORT_REDIRECT(SERIAL_PORTMASK(p));     // Reply to the serial port that sent the command
        // Crash here to get more information why it failed
        BUG_ON("SP available but read -1");
        SERIAL_ERROR_MSG(STR_ERR_SERIAL_MISMATCH);
        SERIAL_FLUSH();
        continue;
      }

      const char serial_char = (char)c;
      SerialState &serial = serial_state[p];

      if (ISEOL(serial_char)) {

        // Reset our state, continue if the line was empty
        if (process_line_done(serial.input_state, serial.line_buffer, serial.count))
          continue;

        char* command = serial.line_buffer;

        while (*command == ' ') command++;                   // Skip leading spaces
>>>>>>> mcu_ctrl
        char *npos = (*command == 'N') ? command : nullptr;  // Require the N parameter to start the line

        if (npos) {

<<<<<<< HEAD
          bool M110 = strstr_P(command, PSTR("M110")) != nullptr;
=======
          const bool M110 = !!strstr_P(command, PSTR("M110"));
>>>>>>> mcu_ctrl

          if (M110) {
            char* n2pos = strchr(command + 4, 'N');
            if (n2pos) npos = n2pos;
          }

<<<<<<< HEAD
          gcode_N = strtol(npos + 1, nullptr, 10);

          if (gcode_N != last_N + 1 && !M110)
            return gcode_line_error(PSTR(MSG_ERR_LINE_NO), i);
=======
          const long gcode_N = strtol(npos + 1, nullptr, 10);

          if (gcode_N != serial.last_N + 1 && !M110) {
            // In case of error on a serial port, don't prevent other serial port from making progress
            gcode_line_error(PSTR(STR_ERR_LINE_NO), p);
            break;
          }
>>>>>>> mcu_ctrl

          char *apos = strrchr(command, '*');
          if (apos) {
            uint8_t checksum = 0, count = uint8_t(apos - command);
            while (count) checksum ^= command[--count];
<<<<<<< HEAD
            if (strtol(apos + 1, nullptr, 10) != checksum)
              return gcode_line_error(PSTR(MSG_ERR_CHECKSUM_MISMATCH), i);
          }
          else
            return gcode_line_error(PSTR(MSG_ERR_NO_CHECKSUM), i);

          last_N = gcode_N;
        }
        #if ENABLED(SDSUPPORT)
          // Pronterface "M29" and "M29 " has no line number
          else if (card.flag.saving && !is_M29(command))
            return gcode_line_error(PSTR(MSG_ERR_NO_CHECKSUM), i);
        #endif

        // Movement commands alert when stopped
=======
            if (strtol(apos + 1, nullptr, 10) != checksum) {
              // In case of error on a serial port, don't prevent other serial port from making progress
              gcode_line_error(PSTR(STR_ERR_CHECKSUM_MISMATCH), p);
              break;
            }
          }
          else {
            // In case of error on a serial port, don't prevent other serial port from making progress
            gcode_line_error(PSTR(STR_ERR_NO_CHECKSUM), p);
            break;
          }

          serial.last_N = gcode_N;
        }
        #if ENABLED(SDSUPPORT)
          // Pronterface "M29" and "M29 " has no line number
          else if (card.flag.saving && !is_M29(command)) {
            gcode_line_error(PSTR(STR_ERR_NO_CHECKSUM), p);
            break;
          }
        #endif

        //
        // Movement commands give an alert when the machine is stopped
        //

>>>>>>> mcu_ctrl
        if (IsStopped()) {
          char* gpos = strchr(command, 'G');
          if (gpos) {
            switch (strtol(gpos + 1, nullptr, 10)) {
<<<<<<< HEAD
              case 0:
              case 1:
              #if ENABLED(ARC_SUPPORT)
                case 2:
                case 3:
              #endif
              #if ENABLED(BEZIER_CURVE_SUPPORT)
                case 5:
              #endif
                SERIAL_ECHOLNPGM(MSG_ERR_STOPPED);
=======
              case 0 ... 1:
              TERN_(ARC_SUPPORT, case 2 ... 3:)
              TERN_(BEZIER_CURVE_SUPPORT, case 5:)
                PORT_REDIRECT(SERIAL_PORTMASK(p));     // Reply to the serial port that sent the command
                SERIAL_ECHOLNPGM(STR_ERR_STOPPED);
>>>>>>> mcu_ctrl
                LCD_MESSAGEPGM(MSG_STOPPED);
                break;
            }
          }
        }

        #if DISABLED(EMERGENCY_PARSER)
          // Process critical commands early
<<<<<<< HEAD
          if (strcmp(command, "M108") == 0) {
            wait_for_heatup = false;
            #if HAS_LCD_MENU
              wait_for_user = false;
            #endif
          }
          if (strcmp(command, "M112") == 0) kill();
          if (strcmp(command, "M410") == 0) quickstop_stepper();
        #endif

        #if defined(NO_TIMEOUTS) && NO_TIMEOUTS > 0
=======
          if (command[0] == 'M') switch (command[3]) {
            case '8': if (command[2] == '0' && command[1] == '1') { wait_for_heatup = false; TERN_(HAS_LCD_MENU, wait_for_user = false); } break;
            case '2': if (command[2] == '1' && command[1] == '1') kill(M112_KILL_STR, nullptr, true); break;
            case '0': if (command[1] == '4' && command[2] == '1') quickstop_stepper(); break;
          }
        #endif

        #if NO_TIMEOUTS > 0
>>>>>>> mcu_ctrl
          last_command_time = ms;
        #endif

        // Add the command to the queue
<<<<<<< HEAD
        _enqueue(serial_line_buffer[i], true
          #if NUM_SERIAL > 1
            , i
          #endif
        );
      }
      else if (serial_count[i] >= MAX_CMD_SIZE - 1) {
        // Keep fetching, but ignore normal characters beyond the max length
        // The command will be injected when EOL is reached
      }
      else if (serial_char == '\\') {  // Handle escapes
        // if we have one more character, copy it over
        if ((c = read_serial(i)) >= 0 && !serial_comment_mode[i]
          #if ENABLED(PAREN_COMMENTS)
            && !serial_comment_paren_mode[i]
          #endif
        )
          serial_line_buffer[i][serial_count[i]++] = (char)c;
      }
      else { // it's not a newline, carriage return or escape char
        if (serial_char == ';') serial_comment_mode[i] = true;
        #if ENABLED(PAREN_COMMENTS)
          else if (serial_char == '(') serial_comment_paren_mode[i] = true;
          else if (serial_char == ')') serial_comment_paren_mode[i] = false;
        #endif
        else if (!serial_comment_mode[i]
          #if ENABLED(PAREN_COMMENTS)
            && ! serial_comment_paren_mode[i]
          #endif
        ) serial_line_buffer[i][serial_count[i]++] = serial_char;
      }
    } // for NUM_SERIAL
=======
        ring_buffer.enqueue(serial.line_buffer, false
          #if HAS_MULTI_SERIAL
            , p
          #endif
        );
      }
      else
        process_stream_char(serial_char, serial.input_state, serial.line_buffer, serial.count);

    } // NUM_SERIAL loop
>>>>>>> mcu_ctrl
  } // queue has space, serial has data
}

#if ENABLED(SDSUPPORT)

  /**
<<<<<<< HEAD
   * Get commands from the SD Card until the command buffer is full
   * or until the end of the file is reached. The special character '#'
   * can also interrupt buffering.
   */
  inline void GCodeQueue::get_sdcard_commands() {
    static bool stop_buffering = false,
                sd_comment_mode = false
                #if ENABLED(PAREN_COMMENTS)
                  , sd_comment_paren_mode = false
                #endif
              ;

    if (!IS_SD_PRINTING()) return;

    /**
     * '#' stops reading from SD to the buffer prematurely, so procedural
     * macro calls are possible. If it occurs, stop_buffering is triggered
     * and the buffer is run dry; this character _can_ occur in serial com
     * due to checksums, however, no checksums are used in SD printing.
     */

    if (length == 0) stop_buffering = false;

    uint16_t sd_count = 0;
    bool card_eof = card.eof();
    while (length < BUFSIZE && !card_eof && !stop_buffering) {
      const int16_t n = card.get();
      char sd_char = (char)n;
      card_eof = card.eof();
      if (card_eof || n == -1
          || sd_char == '\n' || sd_char == '\r'
          || ((sd_char == '#' || sd_char == ':') && !sd_comment_mode
            #if ENABLED(PAREN_COMMENTS)
              && !sd_comment_paren_mode
            #endif
          )
      ) {
        if (card_eof) {

          card.printingHasFinished();

          print_finish = 1;

          if (IS_SD_PRINTING())
            sd_count = 0; // If a sub-file was printing, continue from call point
          else {
            SERIAL_ECHOLNPGM(MSG_FILE_PRINTED);
            #if ENABLED(PRINTER_EVENT_LEDS)
              printerEventLEDs.onPrintCompleted();
              #if HAS_RESUME_CONTINUE
                inject_P(PSTR("M0 S"
                  #if HAS_LCD_MENU
                    "1800"
                  #else
                    "60"
                  #endif
                ));
              #endif
            #endif // PRINTER_EVENT_LEDS
          }

          #ifdef RTS_AVAILABLE
            rtscheck.RTS_SndData(100, PRINT_PROCESS_VP);
            delay(1);
            rtscheck.RTS_SndData(100 ,PRINT_PROCESS_TITLE_VP);
            if(language_change_font != 0)
            {
              rtscheck.RTS_SndData(ExchangePageBase + 9, ExchangepageAddr);
              change_page_font = 9;
            }
          #endif          
        }
        else if (n == -1)
        {
          error_sd_num++;
          SERIAL_ERROR_MSG(MSG_SD_ERR_READ);
          if(error_sd_num > 50)
          {
            waitway = 0;
            rtscheck.RTS_SndData(ExchangePageBase + 62, ExchangepageAddr);
            change_page_font = 62;
            rtscheck.RTS_SndData(Error_204, ABNORMAL_TEXT_VP);
            errorway = 4;
          }
        }

        if(n != -1) error_sd_num = 0;

        if (sd_char == '#') stop_buffering = true;

        sd_comment_mode = false; // for new command
        #if ENABLED(PAREN_COMMENTS)
          sd_comment_paren_mode = false;
        #endif

        // Skip empty lines and comments
        if (!sd_count) { thermalManager.manage_heater(); continue; }

        command_buffer[index_w][sd_count] = '\0'; // terminate string
        sd_count = 0; // clear sd line buffer

        _commit_command(false);

        #if ENABLED(POWER_LOSS_RECOVERY)
          recovery.cmd_sdpos = card.getIndex(); // Prime for the next _commit_command
        #endif
      }
      else if (sd_count >= MAX_CMD_SIZE - 1) {
        /**
         * Keep fetching, but ignore normal characters beyond the max length
         * The command will be injected when EOL is reached
         */
      }
      else {
        if (sd_char == ';') sd_comment_mode = true;
        #if ENABLED(PAREN_COMMENTS)
          else if (sd_char == '(') sd_comment_paren_mode = true;
          else if (sd_char == ')') sd_comment_paren_mode = false;
        #endif
        else if (!sd_comment_mode
          #if ENABLED(PAREN_COMMENTS)
            && ! sd_comment_paren_mode
          #endif
        ) command_buffer[index_w][sd_count++] = sd_char;
      }
=======
   * Get lines from the SD Card until the command buffer is full
   * or until the end of the file is reached. Because this method
   * always receives complete command-lines, they can go directly
   * into the main command queue.
   */
  inline void GCodeQueue::get_sdcard_commands() {
    static uint8_t sd_input_state = PS_NORMAL;

    // Get commands if there are more in the file
    if (!IS_SD_FETCHING()) return;

    int sd_count = 0;
    while (!ring_buffer.full() && !card.eof()) {
      const int16_t n = card.get();
      const bool card_eof = card.eof();
      if (n < 0 && !card_eof) { /*SERIAL_ERROR_MSG(STR_SD_ERR_READ);*/ return;/*continue;*/ }

      CommandLine &command = ring_buffer.commands[ring_buffer.index_w];
      const char sd_char = (char)n;
      const bool is_eol = ISEOL(sd_char);
      if (is_eol || card_eof) {

        // Reset stream state, terminate the buffer, and commit a non-empty command
        if (!is_eol && sd_count) ++sd_count;          // End of file with no newline
        if (!process_line_done(sd_input_state, command.buffer, sd_count)) {

          // M808 L saves the sdpos of the next line. M808 loops to a new sdpos.
          TERN_(GCODE_REPEAT_MARKERS, repeat.early_parse_M808(command.buffer));

          #if DISABLED(PARK_HEAD_ON_PAUSE)
            // When M25 is non-blocking it can still suspend SD commands
            // Otherwise the M125 handler needs to know SD printing is active
            if (command.buffer[0] == 'M' && command.buffer[1] == '2' && command.buffer[2] == '5' && !NUMERIC(command.buffer[3]))
              card.pauseSDPrint();
          #endif

          // Put the new command into the buffer (no "ok" sent)
          ring_buffer.commit_command(true);

          // Prime Power-Loss Recovery for the NEXT commit_command
          TERN_(POWER_LOSS_RECOVERY, recovery.cmd_sdpos = card.getIndex());
        }

        if (card.eof()) card.fileHasFinished();         // Handle end of file reached
      }
      else
        process_stream_char(sd_char, sd_input_state, command.buffer, sd_count);
>>>>>>> mcu_ctrl
    }
  }

#endif // SDSUPPORT

/**
 * Add to the circular command queue the next command from:
<<<<<<< HEAD
 *  - The command-injection queue (injected_commands_P)
=======
 *  - The command-injection queues (injected_commands_P, injected_commands)
>>>>>>> mcu_ctrl
 *  - The active serial input (usually USB)
 *  - The SD card file being actively printed
 */
void GCodeQueue::get_available_commands() {
<<<<<<< HEAD

  get_serial_commands();

  #if ENABLED(SDSUPPORT)
    get_sdcard_commands();
  #endif
=======
  if (ring_buffer.full()) return;

  get_serial_commands();

  TERN_(SDSUPPORT, get_sdcard_commands());
}

/**
 * Run the entire queue in-place. Blocks SD completion/abort until complete.
 */
void GCodeQueue::exhaust() {
  while (ring_buffer.occupied()) advance();
  planner.synchronize();
>>>>>>> mcu_ctrl
}

/**
 * Get the next command in the queue, optionally log it to SD, then dispatch it
 */
void GCodeQueue::advance() {

  // Process immediate commands
<<<<<<< HEAD
  if (process_injected_command()) return;

  // Return if the G-code buffer is empty
  if (!length) return;
=======
  if (process_injected_command_P() || process_injected_command()) return;

  // Return if the G-code buffer is empty
  if (ring_buffer.empty()) return;
>>>>>>> mcu_ctrl

  #if ENABLED(SDSUPPORT)

    if (card.flag.saving) {
<<<<<<< HEAD
      char* command = command_buffer[index_r];
      if (is_M29(command)) {
        // M29 closes the file
        card.closefile();
        SERIAL_ECHOLNPGM(MSG_FILE_SAVED);

        #if !defined(__AVR__) || !defined(USBCON)
          #if ENABLED(SERIAL_STATS_DROPPED_RX)
            SERIAL_ECHOLNPAIR("Dropped bytes: ", MYSERIAL0.dropped());
          #endif

          #if ENABLED(SERIAL_STATS_MAX_RX_QUEUED)
            SERIAL_ECHOLNPAIR("Max RX Queue Size: ", MYSERIAL0.rxMaxEnqueued());
          #endif
        #endif //  !defined(__AVR__) || !defined(USBCON)
=======
      char * const cmd = ring_buffer.peek_next_command_string();
      if (is_M29(cmd)) {
        // M29 closes the file
        card.closefile();
        SERIAL_ECHOLNPGM(STR_FILE_SAVED);

        #if !defined(__AVR__) || !defined(USBCON)
          #if ENABLED(SERIAL_STATS_DROPPED_RX)
            SERIAL_ECHOLNPAIR("Dropped bytes: ", MYSERIAL1.dropped());
          #endif
          #if ENABLED(SERIAL_STATS_MAX_RX_QUEUED)
            SERIAL_ECHOLNPAIR("Max RX Queue Size: ", MYSERIAL1.rxMaxEnqueued());
          #endif
        #endif
>>>>>>> mcu_ctrl

        ok_to_send();
      }
      else {
        // Write the string from the read buffer to SD
<<<<<<< HEAD
        card.write_command(command);
=======
        card.write_command(cmd);
>>>>>>> mcu_ctrl
        if (card.flag.logging)
          gcode.process_next_command(); // The card is saving because it's logging
        else
          ok_to_send();
      }
    }
    else
      gcode.process_next_command();

  #else

    gcode.process_next_command();

  #endif // SDSUPPORT

  // The queue may be reset by a command handler or by code invoked by idle() within a handler
<<<<<<< HEAD
  if (length) {
    --length;
    if (++index_r >= BUFSIZE) index_r = 0;
  }

=======
  ring_buffer.advance_pos(ring_buffer.index_r, -1);
>>>>>>> mcu_ctrl
}
