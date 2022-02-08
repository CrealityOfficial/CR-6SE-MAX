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
 * feature/pause.h - Pause feature support functions
 * This may be combined with related G-codes if features are consolidated.
 */

typedef struct {
  float unload_length, load_length;
} fil_change_settings_t;

#include "../inc/MarlinConfigPre.h"

#if ENABLED(ADVANCED_PAUSE_FEATURE)

#include "../libs/nozzle.h"

enum PauseMode : char {
  PAUSE_MODE_SAME,
  PAUSE_MODE_PAUSE_PRINT,
  PAUSE_MODE_CHANGE_FILAMENT,
  PAUSE_MODE_LOAD_FILAMENT,
  PAUSE_MODE_UNLOAD_FILAMENT
};

enum PauseMessage : char {
<<<<<<< HEAD
  PAUSE_MESSAGE_PAUSING,
=======
  PAUSE_MESSAGE_PARKING,
>>>>>>> mcu_ctrl
  PAUSE_MESSAGE_CHANGING,
  PAUSE_MESSAGE_WAITING,
  PAUSE_MESSAGE_UNLOAD,
  PAUSE_MESSAGE_INSERT,
  PAUSE_MESSAGE_LOAD,
  PAUSE_MESSAGE_PURGE,
  PAUSE_MESSAGE_OPTION,
  PAUSE_MESSAGE_RESUME,
  PAUSE_MESSAGE_STATUS,
  PAUSE_MESSAGE_HEAT,
  PAUSE_MESSAGE_HEATING
};

<<<<<<< HEAD
enum PauseMenuResponse : char {
  PAUSE_RESPONSE_WAIT_FOR,
  PAUSE_RESPONSE_EXTRUDE_MORE,
  PAUSE_RESPONSE_RESUME_PRINT
};

extern PauseMode pause_mode;
extern PauseMenuResponse pause_menu_response;
=======
#if M600_PURGE_MORE_RESUMABLE
  enum PauseMenuResponse : char {
    PAUSE_RESPONSE_WAIT_FOR,
    PAUSE_RESPONSE_EXTRUDE_MORE,
    PAUSE_RESPONSE_RESUME_PRINT
  };
  extern PauseMenuResponse pause_menu_response;
  extern PauseMode pause_mode;
#endif
>>>>>>> mcu_ctrl

extern fil_change_settings_t fc_settings[EXTRUDERS];

extern uint8_t did_pause_print;

#if ENABLED(DUAL_X_CARRIAGE)
  #define DXC_PARAMS , const int8_t DXC_ext=-1
  #define DXC_ARGS   , const int8_t DXC_ext
  #define DXC_PASS   , DXC_ext
<<<<<<< HEAD
=======
  #define DXC_SAY    , " dxc:", int(DXC_ext)
>>>>>>> mcu_ctrl
#else
  #define DXC_PARAMS
  #define DXC_ARGS
  #define DXC_PASS
<<<<<<< HEAD
#endif

void do_pause_e_move(const float &length, const feedRate_t &fr_mm_s);

bool pause_print(const float &retract, const xyz_pos_t &park_point, const float &unload_length=0, const bool show_lcd=false DXC_PARAMS);

void wait_for_confirmation(const bool is_reload=false, const int8_t max_beep_count=0 DXC_PARAMS);

void resume_print(const float &slow_load_length=0, const float &fast_load_length=0, const float &extrude_length=ADVANCED_PAUSE_PURGE_LENGTH, const int8_t max_beep_count=0 DXC_PARAMS);

bool load_filament(const float &slow_load_length=0, const float &fast_load_length=0, const float &extrude_length=0, const int8_t max_beep_count=0, const bool show_lcd=false,
                          const bool pause_for_user=false, const PauseMode mode=PAUSE_MODE_PAUSE_PRINT DXC_PARAMS);

bool unload_filament(const float &unload_length, const bool show_lcd=false, const PauseMode mode=PAUSE_MODE_PAUSE_PRINT
  #if BOTH(FILAMENT_UNLOAD_ALL_EXTRUDERS, MIXING_EXTRUDER)
    , const float &mix_multiplier=1.0
  #endif
);

#endif // ADVANCED_PAUSE_FEATURE
=======
  #define DXC_SAY
#endif

// Pause the print. If unload_length is set, do a Filament Unload
bool pause_print(
  const_float_t   retract,                                    // (mm) Retraction length
  const xyz_pos_t &park_point,                                // Parking XY Position and Z Raise
  const bool      show_lcd=false,                             // Set LCD status messages?
  const_float_t   unload_length=0                             // (mm) Filament Change Unload Length - 0 to skip
  DXC_PARAMS                                                  // Dual-X-Carriage extruder index
);

void wait_for_confirmation(
  const bool      is_reload=false,                            // Reload Filament? (otherwise Resume Print)
  const int8_t    max_beep_count=0                            // Beep alert for attention
  DXC_PARAMS                                                  // Dual-X-Carriage extruder index
);

void resume_print(
  const_float_t   slow_load_length=0,                         // (mm) Slow Load Length for finishing move
  const_float_t   fast_load_length=0,                         // (mm) Fast Load Length for initial move
  const_float_t   extrude_length=ADVANCED_PAUSE_PURGE_LENGTH, // (mm) Purge length
  const int8_t    max_beep_count=0,                           // Beep alert for attention
  const celsius_t targetTemp=0                                // (°C) A target temperature for the hotend
  DXC_PARAMS                                                  // Dual-X-Carriage extruder index
);

bool load_filament(
  const_float_t   slow_load_length=0,                         // (mm) Slow Load Length for finishing move
  const_float_t   fast_load_length=0,                         // (mm) Fast Load Length for initial move
  const_float_t   extrude_length=0,                           // (mm) Purge length
  const int8_t    max_beep_count=0,                           // Beep alert for attention
  const bool      show_lcd=false,                             // Set LCD status messages?
  const bool      pause_for_user=false,                       // Pause for user before returning?
  const PauseMode mode=PAUSE_MODE_PAUSE_PRINT                 // Pause Mode to apply
  DXC_PARAMS                                                  // Dual-X-Carriage extruder index
);

bool unload_filament(
  const_float_t   unload_length,                              // (mm) Filament Unload Length - 0 to skip
  const bool      show_lcd=false,                             // Set LCD status messages?
  const PauseMode mode=PAUSE_MODE_PAUSE_PRINT                 // Pause Mode to apply
  #if BOTH(FILAMENT_UNLOAD_ALL_EXTRUDERS, MIXING_EXTRUDER)
    , const_float_t mix_multiplier=1.0f                       // Extrusion multiplier (for a Mixing Extruder)
  #endif
);

#else // !ADVANCED_PAUSE_FEATURE

  constexpr uint8_t did_pause_print = 0;

#endif // !ADVANCED_PAUSE_FEATURE
>>>>>>> mcu_ctrl
