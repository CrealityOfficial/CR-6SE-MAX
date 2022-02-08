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
 * parser.cpp - Parser for a GCode line, providing a parameter interface.
 */

#include "parser.h"

<<<<<<< HEAD
#include "../Marlin.h"

#if NUM_SERIAL > 1
  #include "queue.h"
=======
#include "../MarlinCore.h"

#if ENABLE_DEBUG_FUNC
  #include "../debug/debug.h"
>>>>>>> mcu_ctrl
#endif

// Must be declared for allocation and to satisfy the linker
// Zero values need no initialization.

bool GCodeParser::volumetric_enabled;

#if ENABLED(INCH_MODE_SUPPORT)
  float GCodeParser::linear_unit_factor, GCodeParser::volumetric_unit_factor;
#endif

#if ENABLED(TEMPERATURE_UNITS_SUPPORT)
  TempUnit GCodeParser::input_temp_units = TEMPUNIT_C;
#endif

char *GCodeParser::command_ptr,
     *GCodeParser::string_arg,
     *GCodeParser::value_ptr;
char GCodeParser::command_letter;
<<<<<<< HEAD
int GCodeParser::codenum;
=======
uint16_t GCodeParser::codenum;
>>>>>>> mcu_ctrl

#if USE_GCODE_SUBCODES
  uint8_t GCodeParser::subcode;
#endif

#if ENABLED(GCODE_MOTION_MODES)
  int16_t GCodeParser::motion_mode_codenum = -1;
  #if USE_GCODE_SUBCODES
    uint8_t GCodeParser::motion_mode_subcode;
  #endif
#endif

#if ENABLED(FASTER_GCODE_PARSER)
  // Optimized Parameters
  uint32_t GCodeParser::codebits;  // found bits
  uint8_t GCodeParser::param[26];  // parameter offsets from command_ptr
#else
  char *GCodeParser::command_args; // start of parameters
#endif

// Create a global instance of the GCode parser singleton
GCodeParser parser;

/**
 * Clear all code-seen (and value pointers)
 *
 * Since each param is set/cleared on seen codes,
 * this may be optimized by commenting out ZERO(param)
 */
void GCodeParser::reset() {
  string_arg = nullptr;                 // No whole line argument
  command_letter = '?';                 // No command letter
  codenum = 0;                          // No command code
<<<<<<< HEAD
  #if USE_GCODE_SUBCODES
    subcode = 0;                        // No command sub-code
  #endif
=======
  TERN_(USE_GCODE_SUBCODES, subcode = 0); // No command sub-code
>>>>>>> mcu_ctrl
  #if ENABLED(FASTER_GCODE_PARSER)
    codebits = 0;                       // No codes yet
    //ZERO(param);                      // No parameters (should be safe to comment out this line)
  #endif
}

<<<<<<< HEAD
// Populate all fields by parsing a single line of GCode
// 58 bytes of SRAM are used to speed up seen/value
=======
#if ENABLED(GCODE_QUOTED_STRINGS)

  // Pass the address after the first quote (if any)
  char* GCodeParser::unescape_string(char* &src) {
    if (*src == '"') ++src;     // Skip the leading quote
    char * const out = src;     // Start of the string
    char *dst = src;            // Prepare to unescape and terminate
    for (;;) {
      char c = *src++;          // Get the next char
      switch (c) {
        case '\\': c = *src++; break; // Get the escaped char
        case '"' : c = '\0'; break;   // Convert bare quote to nul
      }
      if (!(*dst++ = c)) break; // Copy and break on nul
    }
    return out;
  }

#endif

/**
 * Populate the command line state (command_letter, codenum, subcode, and string_arg)
 * by parsing a single line of GCode. 58 bytes of SRAM are used to speed up seen/value.
 */
>>>>>>> mcu_ctrl
void GCodeParser::parse(char *p) {

  reset(); // No codes to report

<<<<<<< HEAD
=======
  auto uppercase = [](char c) {
    if (TERN0(GCODE_CASE_INSENSITIVE, WITHIN(c, 'a', 'z')))
      c += 'A' - 'a';
    return c;
  };

>>>>>>> mcu_ctrl
  // Skip spaces
  while (*p == ' ') ++p;

  // Skip N[-0-9] if included in the command line
<<<<<<< HEAD
  if (*p == 'N' && NUMERIC_SIGNED(p[1])) {
    #if ENABLED(FASTER_GCODE_PARSER)
      //set('N', p + 1);     // (optional) Set the 'N' parameter value
    #endif
=======
  if (uppercase(*p) == 'N' && NUMERIC_SIGNED(p[1])) {
    //TERN_(FASTER_GCODE_PARSER, set('N', p + 1)); // (optional) Set the 'N' parameter value
>>>>>>> mcu_ctrl
    p += 2;                  // skip N[-0-9]
    while (NUMERIC(*p)) ++p; // skip [0-9]*
    while (*p == ' ')   ++p; // skip [ ]*
  }

  // *p now points to the current command, which should be G, M, or T
  command_ptr = p;

  // Get the command letter, which must be G, M, or T
<<<<<<< HEAD
  const char letter = *p++;
=======
  const char letter = uppercase(*p++);
>>>>>>> mcu_ctrl

  // Nullify asterisk and trailing whitespace
  char *starpos = strchr(p, '*');
  if (starpos) {
    --starpos;                          // *
    while (*starpos == ' ') --starpos;  // spaces...
    starpos[1] = '\0';
  }

<<<<<<< HEAD
  #if ENABLED(GCODE_MOTION_MODES)
    #if ENABLED(ARC_SUPPORT)
      #define GTOP 3
    #else
      #define GTOP 1
    #endif
  #endif

  // Bail if the letter is not G, M, or T
  // (or a valid parameter for the current motion mode)
  switch (letter) {

    case 'G': case 'M': case 'T':
    #if ENABLED(CANCEL_OBJECTS)
      case 'O':
    #endif
      // Skip spaces to get the numeric part
      while (*p == ' ') p++;

      #if ENABLED(PRUSA_MMU2)
=======
  #if ANY(MARLIN_DEV_MODE, SWITCHING_TOOLHEAD, MAGNETIC_SWITCHING_TOOLHEAD, ELECTROMAGNETIC_SWITCHING_TOOLHEAD)
    #define SIGNED_CODENUM 1
  #endif

  /**
   * Screen for good command letters.
   * With Realtime Reporting, commands S000, P000, and R000 are allowed.
   */
  #if ENABLED(REALTIME_REPORTING_COMMANDS)
    switch (letter) {
      case 'P': case 'R' ... 'S': {
        uint8_t digits = 0;
        char *a = p;
        while (*a++ == '0') digits++; // Count up '0' characters
        if (digits == 3) {            // Three '0' digits is a good command
          codenum = 0;
          command_letter = letter;
          return;
        }
      }
    }
  #endif

  /**
   * Screen for good command letters. G, M, and T are always accepted.
   * With Motion Modes enabled any axis letter can come first.
   */
  switch (letter) {
    case 'G': case 'M': case 'T': TERN_(MARLIN_DEV_MODE, case 'D':) 
    TERN_(ENABLE_DEBUG_FUNC, case 'P':) {
      // Skip spaces to get the numeric part
      while (*p == ' ') p++;

      #if HAS_PRUSA_MMU2
>>>>>>> mcu_ctrl
        if (letter == 'T') {
          // check for special MMU2 T?/Tx/Tc commands
          if (*p == '?' || *p == 'x' || *p == 'c') {
            command_letter = letter;
            string_arg = p;
            return;
          }
        }
      #endif

      // Bail if there's no command code number
<<<<<<< HEAD
      if (!NUMERIC(*p)) return;
=======
      if (!TERN(SIGNED_CODENUM, NUMERIC_SIGNED(*p), NUMERIC(*p))) return;
>>>>>>> mcu_ctrl

      // Save the command letter at this point
      // A '?' signifies an unknown command
      command_letter = letter;

<<<<<<< HEAD
      // Get the code number - integer digits only
      codenum = 0;
      do { codenum *= 10, codenum += *p++ - '0'; } while (NUMERIC(*p));

      // Allow for decimal point in command
      #if USE_GCODE_SUBCODES
      if (*p == '.') {
        p++;
        while (NUMERIC(*p))
        subcode *= 10, subcode += *p++ - '0';
      }
=======
      #if ENABLED(SIGNED_CODENUM)
        int sign = 1; // Allow for a negative code like D-1 or T-1
        if (*p == '-') { sign = -1; ++p; }
      #endif

      // Get the code number - integer digits only
      codenum = 0;

      do { codenum = codenum * 10 + *p++ - '0'; } while (NUMERIC(*p));

      #if ENABLE_DEBUG_FUNC
        gDebug.GetParaAfterCmd(p);
      #endif
      // Apply the sign, if any
      TERN_(SIGNED_CODENUM, codenum *= sign);

      // Allow for decimal point in command
      #if USE_GCODE_SUBCODES
        if (*p == '.') {
          p++;
          while (NUMERIC(*p))
            subcode = subcode * 10 + *p++ - '0';
        }
>>>>>>> mcu_ctrl
      #endif

      // Skip all spaces to get to the first argument, or nul
      while (*p == ' ') p++;

      #if ENABLED(GCODE_MOTION_MODES)
<<<<<<< HEAD
        if (letter == 'G' && (codenum <= GTOP || codenum == 5
                                #if ENABLED(G38_PROBE_TARGET)
                                  || codenum == 38
                                #endif
                             )
        ) {
          motion_mode_codenum = codenum;
          #if USE_GCODE_SUBCODES
            motion_mode_subcode = subcode;
          #endif
        }
      #endif

      break;

    #if ENABLED(GCODE_MOTION_MODES)
      #if ENABLED(ARC_SUPPORT)
        case 'I': case 'J': case 'R':
          if (motion_mode_codenum != 2 && motion_mode_codenum != 3) return;
      #endif
      case 'P': case 'Q':
        if (motion_mode_codenum != 5) return;
      case 'X': case 'Y': case 'Z': case 'E': case 'F':
        if (motion_mode_codenum < 0) return;
        command_letter = 'G';
        codenum = motion_mode_codenum;
        #if USE_GCODE_SUBCODES
          subcode = motion_mode_subcode;
        #endif
        p--; // Back up one character to use the current parameter
      break;
    #endif // GCODE_MOTION_MODES
=======
        if (letter == 'G'
          && (codenum <= TERN(ARC_SUPPORT, 3, 1) || TERN0(BEZIER_CURVE_SUPPORT, codenum == 5) || TERN0(G38_PROBE_TARGET, codenum == 38))
        ) {
          motion_mode_codenum = codenum;
          TERN_(USE_GCODE_SUBCODES, motion_mode_subcode = subcode);
        }
      #endif

      } break;

    #if ENABLED(GCODE_MOTION_MODES)

      #if EITHER(BEZIER_CURVE_SUPPORT, ARC_SUPPORT)
        case 'I' ... 'J': case 'P':
          if (TERN1(BEZIER_CURVE_SUPPORT, motion_mode_codenum != 5)
            && TERN1(ARC_P_CIRCLES, !WITHIN(motion_mode_codenum, 2, 3))
          ) return;
      #endif

      #if ENABLED(BEZIER_CURVE_SUPPORT)
        case 'Q': if (motion_mode_codenum != 5) return;
      #endif

      #if ENABLED(ARC_SUPPORT)
        case 'R': if (!WITHIN(motion_mode_codenum, 2, 3)) return;
      #endif

      case 'X' ... 'Z': case 'E' ... 'F':
        if (motion_mode_codenum < 0) return;
        command_letter = 'G';
        codenum = motion_mode_codenum;
        TERN_(USE_GCODE_SUBCODES, subcode = motion_mode_subcode);
        p--; // Back up one character to use the current parameter
        break;

    #endif
>>>>>>> mcu_ctrl

    default: return;
  }

  // The command parameters (if any) start here, for sure!

<<<<<<< HEAD
  #if DISABLED(FASTER_GCODE_PARSER)
    command_args = p; // Scan for parameters in seen()
  #endif

  // Only use string_arg for these M codes
  if (letter == 'M') switch (codenum) {
    #if ENABLED(GCODE_MACROS)
      case 810 ... 819:
    #endif
    #if ENABLED(EXPECTED_PRINTER_CHECK)
      case 16:
    #endif
    case 23: case 28: case 30: case 117: case 118: case 928: string_arg = p; return;
    default: break;
  }
/*
  #if ENABLED(CANCEL_OBJECTS)
  if (letter == 'O') switch (codenum) {
    case 1:  string_arg = p; return;
    default: break;
  }
  #endif
*/
=======
  IF_DISABLED(FASTER_GCODE_PARSER, command_args = p); // Scan for parameters in seen()

  // Only use string_arg for these M codes
  if (letter == 'M') switch (codenum) {
    TERN_(GCODE_MACROS, case 810 ... 819:)
    TERN_(EXPECTED_PRINTER_CHECK, case 16:)
    case 23: case 28: case 30: case 117 ... 118: case 928:
      string_arg = unescape_string(p);
      return;
    default: break;
  }

>>>>>>> mcu_ctrl
  #if ENABLED(DEBUG_GCODE_PARSER)
    const bool debug = codenum == 800;
  #endif

  /**
   * Find all parameters, set flags and pointers for fast parsing
   *
   * Most codes ignore 'string_arg', but those that want a string will get the right pointer.
   * The following loop assigns the first "parameter" having no numeric value to 'string_arg'.
   * This allows M0/M1 with expire time to work: "M0 S5 You Win!"
   * For 'M118' you must use 'E1' and 'A1' rather than just 'E' or 'A'
   */
<<<<<<< HEAD
  string_arg = nullptr;
  while (const char code = *p++) {              // Get the next parameter. A NUL ends the loop

    // Special handling for M32 [P] !/path/to/file.g#
    // The path must be the last parameter
    if (code == '!' && letter == 'M' && codenum == 32) {
=======
  #if ENABLED(GCODE_QUOTED_STRINGS)
    bool quoted_string_arg = false;
  #endif
  string_arg = nullptr;
  while (const char param = uppercase(*p++)) {  // Get the next parameter. A NUL ends the loop

    // Special handling for M32 [P] !/path/to/file.g#
    // The path must be the last parameter
    if (param == '!' && is_command('M', 32)) {
>>>>>>> mcu_ctrl
      string_arg = p;                           // Name starts after '!'
      char * const lb = strchr(p, '#');         // Already seen '#' as SD char (to pause buffering)
      if (lb) *lb = '\0';                       // Safe to mark the end of the filename
      return;
    }

<<<<<<< HEAD
    // Arguments MUST be uppercase for fast GCode parsing
    #if ENABLED(FASTER_GCODE_PARSER)
      #define PARAM_TEST WITHIN(code, 'A', 'Z')
    #else
      #define PARAM_TEST true
    #endif

    if (PARAM_TEST) {

      while (*p == ' ') p++;                    // Skip spaces between parameters & values

      const bool has_num = valid_float(p);

      #if ENABLED(DEBUG_GCODE_PARSER)
        if (debug) {
          SERIAL_ECHOPAIR("Got letter ", code, " at index ", (int)(p - command_ptr - 1));
          if (has_num) SERIAL_ECHOPGM(" (has_num)");
        }
      #endif

      if (!has_num && !string_arg) {            // No value? First time, keep as string_arg
=======
    #if ENABLED(GCODE_QUOTED_STRINGS)
      if (!quoted_string_arg && param == '"') {
        quoted_string_arg = true;
        string_arg = unescape_string(p);
      }
    #endif

    #if ENABLED(FASTER_GCODE_PARSER)
      // Arguments MUST be uppercase for fast GCode parsing
      #define PARAM_OK(P) WITHIN((P), 'A', 'Z')
    #else
      #define PARAM_OK(P) true
    #endif

    if (PARAM_OK(param)) {

      while (*p == ' ') p++;                    // Skip spaces between parameters & values

      #if ENABLED(GCODE_QUOTED_STRINGS)
        const bool is_str = (*p == '"'), has_val = is_str || valid_float(p);
        char * const valptr = has_val ? is_str ? unescape_string(p) : p : nullptr;
      #else
        const bool has_val = valid_float(p);
        #if ENABLED(FASTER_GCODE_PARSER)
          char * const valptr = has_val ? p : nullptr;
        #endif
      #endif

      #if ENABLED(DEBUG_GCODE_PARSER)
        if (debug) {
          SERIAL_ECHOPAIR("Got param ", AS_CHAR(param), " at index ", p - command_ptr - 1);
          if (has_val) SERIAL_ECHOPGM(" (has_val)");
        }
      #endif

      if (!has_val && !string_arg) {            // No value? First time, keep as string_arg
>>>>>>> mcu_ctrl
        string_arg = p - 1;
        #if ENABLED(DEBUG_GCODE_PARSER)
          if (debug) SERIAL_ECHOPAIR(" string_arg: ", hex_address((void*)string_arg)); // DEBUG
        #endif
      }

<<<<<<< HEAD
      #if ENABLED(DEBUG_GCODE_PARSER)
        if (debug) SERIAL_EOL();
      #endif

      #if ENABLED(FASTER_GCODE_PARSER)
        set(code, has_num ? p : nullptr);       // Set parameter exists and pointer (nullptr for no number)
      #endif
=======
      if (TERN0(DEBUG_GCODE_PARSER, debug)) SERIAL_EOL();

      TERN_(FASTER_GCODE_PARSER, set(param, valptr)); // Set parameter exists and pointer (nullptr for no value)
>>>>>>> mcu_ctrl
    }
    else if (!string_arg) {                     // Not A-Z? First time, keep as the string_arg
      string_arg = p - 1;
      #if ENABLED(DEBUG_GCODE_PARSER)
        if (debug) SERIAL_ECHOPAIR(" string_arg: ", hex_address((void*)string_arg)); // DEBUG
      #endif
    }

    if (!WITHIN(*p, 'A', 'Z')) {                // Another parameter right away?
      while (*p && DECIMAL_SIGNED(*p)) p++;     // Skip over the value section of a parameter
      while (*p == ' ') p++;                    // Skip over all spaces
    }
  }
}

#if ENABLED(CNC_COORDINATE_SYSTEMS)

  // Parse the next parameter as a new command
  bool GCodeParser::chain() {
    #if ENABLED(FASTER_GCODE_PARSER)
      char *next_command = command_ptr;
      if (next_command) {
        while (*next_command && *next_command != ' ') ++next_command;
        while (*next_command == ' ') ++next_command;
        if (!*next_command) next_command = nullptr;
      }
    #else
      const char *next_command = command_args;
    #endif
    if (next_command) parse(next_command);
    return !!next_command;
  }

#endif // CNC_COORDINATE_SYSTEMS

<<<<<<< HEAD
void GCodeParser::unknown_command_error() {
  SERIAL_ECHO_START();
  SERIAL_ECHOLNPAIR(MSG_UNKNOWN_COMMAND, command_ptr, "\"");
=======
void GCodeParser::unknown_command_warning() {
  SERIAL_ECHO_MSG(STR_UNKNOWN_COMMAND, command_ptr, "\"");
>>>>>>> mcu_ctrl
}

#if ENABLED(DEBUG_GCODE_PARSER)

  void GCodeParser::debug() {
    SERIAL_ECHOPAIR("Command: ", command_ptr, " (", command_letter);
    SERIAL_ECHO(codenum);
    SERIAL_ECHOLNPGM(")");
    #if ENABLED(FASTER_GCODE_PARSER)
      SERIAL_ECHOPGM(" args: { ");
<<<<<<< HEAD
      for (char c = 'A'; c <= 'Z'; ++c) if (seen(c)) { SERIAL_CHAR(c); SERIAL_CHAR(' '); }
=======
      for (char c = 'A'; c <= 'Z'; ++c) if (seen(c)) SERIAL_CHAR(c, ' ');
>>>>>>> mcu_ctrl
      SERIAL_CHAR('}');
    #else
      SERIAL_ECHOPAIR(" args: { ", command_args, " }");
    #endif
<<<<<<< HEAD
    if (string_arg) SERIAL_ECHOPAIR(" string: \"", string_arg, "\"");
=======
    if (string_arg) {
      SERIAL_ECHOPAIR(" string: \"", string_arg);
      SERIAL_CHAR('"');
    }
>>>>>>> mcu_ctrl
    SERIAL_ECHOLNPGM("\n");
    for (char c = 'A'; c <= 'Z'; ++c) {
      if (seen(c)) {
        SERIAL_ECHOPAIR("Code '", c); SERIAL_ECHOPGM("':");
        if (has_value()) {
<<<<<<< HEAD
          SERIAL_ECHOPAIR(
=======
          SERIAL_ECHOLNPAIR(
>>>>>>> mcu_ctrl
            "\n    float: ", value_float(),
            "\n     long: ", value_long(),
            "\n    ulong: ", value_ulong(),
            "\n   millis: ", value_millis(),
            "\n   sec-ms: ", value_millis_from_seconds(),
            "\n      int: ", value_int(),
            "\n   ushort: ", value_ushort(),
<<<<<<< HEAD
            "\n     byte: ", (int)value_byte(),
            "\n     bool: ", (int)value_bool(),
=======
            "\n     byte: ", value_byte(),
            "\n     bool: ", value_bool(),
>>>>>>> mcu_ctrl
            "\n   linear: ", value_linear_units(),
            "\n  celsius: ", value_celsius()
          );
        }
        else
<<<<<<< HEAD
          SERIAL_ECHOPGM(" (no value)");
        SERIAL_ECHOLNPGM("\n");
=======
          SERIAL_ECHOLNPGM(" (no value)");
>>>>>>> mcu_ctrl
      }
    }
  }

#endif // DEBUG_GCODE_PARSER
