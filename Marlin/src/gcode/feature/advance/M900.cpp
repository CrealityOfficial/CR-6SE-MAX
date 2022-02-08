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

#include "../../../inc/MarlinConfig.h"

#if ENABLED(LIN_ADVANCE)

#include "../../gcode.h"
#include "../../../module/planner.h"
#include "../../../module/stepper.h"

#if ENABLED(EXTRA_LIN_ADVANCE_K)
<<<<<<< HEAD
  float saved_extruder_advance_K[EXTRUDERS];
  uint8_t lin_adv_slot = 0;
#endif


=======
  float other_extruder_advance_K[EXTRUDERS];
  uint8_t lin_adv_slot = 0;
#endif

>>>>>>> mcu_ctrl
/**
 * M900: Get or Set Linear Advance K-factor
 *  T<tool>     Which tool to address
 *  K<factor>   Set current advance K factor (Slot 0).
 *  L<factor>   Set secondary advance K factor (Slot 1). Requires EXTRA_LIN_ADVANCE_K.
 *  S<0/1>      Activate slot 0 or 1. Requires EXTRA_LIN_ADVANCE_K.
 */
void GcodeSuite::M900() {

<<<<<<< HEAD
=======
  auto echo_value_oor = [](const char ltr, const bool ten=true) {
    SERIAL_CHAR('?', ltr);
    SERIAL_ECHOPGM(" value out of range");
    if (ten) SERIAL_ECHOPGM(" (0-10)");
    SERIAL_ECHOLNPGM(".");
  };

>>>>>>> mcu_ctrl
  #if EXTRUDERS < 2
    constexpr uint8_t tool_index = 0;
  #else
    const uint8_t tool_index = parser.intval('T', active_extruder);
    if (tool_index >= EXTRUDERS) {
<<<<<<< HEAD
      SERIAL_ECHOLNPGM("?T value out of range.");
=======
      echo_value_oor('T', false);
>>>>>>> mcu_ctrl
      return;
    }
  #endif

<<<<<<< HEAD
  #if ENABLED(EXTRA_LIN_ADVANCE_K)

    bool ext_slot = TEST(lin_adv_slot, tool_index);

    if (parser.seenval('S')) {
      const bool slot = parser.value_bool();
      if (ext_slot != slot) {
        ext_slot = slot;
        SET_BIT_TO(lin_adv_slot, tool_index, slot);
        planner.synchronize();
        const float temp = planner.extruder_advance_K[tool_index];
        planner.extruder_advance_K[tool_index] = saved_extruder_advance_K[tool_index];
        saved_extruder_advance_K[tool_index] = temp;
      }
    }

    if (parser.seenval('K')) {
      const float newK = parser.value_float();
      if (WITHIN(newK, 0, 10)) {
        if (ext_slot)
          saved_extruder_advance_K[tool_index] = newK;
        else {
          planner.synchronize();
          planner.extruder_advance_K[tool_index] = newK;
        }
      }
      else
        SERIAL_ECHOLNPGM("?K value out of range (0-10).");
    }

    if (parser.seenval('L')) {
      const float newL = parser.value_float();
      if (WITHIN(newL, 0, 10)) {
        if (!ext_slot)
          saved_extruder_advance_K[tool_index] = newL;
        else {
          planner.synchronize();
          planner.extruder_advance_K[tool_index] = newL;
        }
      }
      else
        SERIAL_ECHOLNPGM("?L value out of range (0-10).");
    }

    if (!parser.seen_any()) {
      #if EXTRUDERS < 2
        SERIAL_ECHOLNPAIR("Advance S", ext_slot, " K", planner.extruder_advance_K[0],
                          "(Slot ", 1 - ext_slot, " K", saved_extruder_advance_K[0], ")");
      #else
        LOOP_L_N(i, EXTRUDERS) {
          const int slot = (int)TEST(lin_adv_slot, i);
          SERIAL_ECHOLNPAIR("Advance T", int(i), " S", slot, " K", planner.extruder_advance_K[i],
                            "(Slot ", 1 - slot, " K", saved_extruder_advance_K[i], ")");
          SERIAL_EOL();
        }
      #endif
    }

  #else

    if (parser.seenval('K')) {
      const float newK = parser.value_float();
      if (WITHIN(newK, 0, 10)) {
        planner.synchronize();
        planner.extruder_advance_K[tool_index] = newK;
      }
      else
        SERIAL_ECHOLNPGM("?K value out of range (0-10).");
    }
    else {
=======
  float &kref = planner.extruder_advance_K[tool_index], newK = kref;
  const float oldK = newK;

  #if ENABLED(EXTRA_LIN_ADVANCE_K)

    float &lref = other_extruder_advance_K[tool_index];

    const bool old_slot = TEST(lin_adv_slot, tool_index), // The tool's current slot (0 or 1)
               new_slot = parser.boolval('S', old_slot);  // The passed slot (default = current)

    // If a new slot is being selected swap the current and
    // saved K values. Do here so K/L will apply correctly.
    if (new_slot != old_slot) {                       // Not the same slot?
      SET_BIT_TO(lin_adv_slot, tool_index, new_slot); // Update the slot for the tool
      newK = lref;                                    // Get new K value from backup
      lref = oldK;                                    // Save K to backup
    }

    // Set the main K value. Apply if the main slot is active.
    if (parser.seenval('K')) {
      const float K = parser.value_float();
      if (!WITHIN(K, 0, 10)) echo_value_oor('K');
      else if (new_slot)        lref = K;             // S1 Knn
      else                      newK = K;             // S0 Knn
    }

    // Set the extra K value. Apply if the extra slot is active.
    if (parser.seenval('L')) {
      const float L = parser.value_float();
      if (!WITHIN(L, 0, 10)) echo_value_oor('L');
      else if (!new_slot)       lref = L;             // S0 Lnn
      else                      newK = L;             // S1 Lnn
    }

  #else

    if (parser.seenval('K')) {
      const float K = parser.value_float();
      if (WITHIN(K, 0, 10))
        newK = K;
      else
        echo_value_oor('K');
    }

  #endif

  if (newK != oldK) {
    planner.synchronize();
    kref = newK;
  }

  if (!parser.seen_any()) {

    #if ENABLED(EXTRA_LIN_ADVANCE_K)

      #if EXTRUDERS < 2
        SERIAL_ECHOLNPAIR("Advance S", new_slot, " K", kref, "(S", !new_slot, " K", lref, ")");
      #else
        LOOP_L_N(i, EXTRUDERS) {
          const bool slot = TEST(lin_adv_slot, i);
          SERIAL_ECHOLNPAIR("Advance T", i, " S", slot, " K", planner.extruder_advance_K[i],
                            "(S", !slot, " K", other_extruder_advance_K[i], ")");
          SERIAL_EOL();
        }
      #endif

    #else

>>>>>>> mcu_ctrl
      SERIAL_ECHO_START();
      #if EXTRUDERS < 2
        SERIAL_ECHOLNPAIR("Advance K=", planner.extruder_advance_K[0]);
      #else
        SERIAL_ECHOPGM("Advance K");
        LOOP_L_N(i, EXTRUDERS) {
<<<<<<< HEAD
          SERIAL_CHAR(' '); SERIAL_ECHO(int(i));
          SERIAL_CHAR('='); SERIAL_ECHO(planner.extruder_advance_K[i]);
        }
        SERIAL_EOL();
      #endif
    }

  #endif
=======
          SERIAL_CHAR(' ', '0' + i, ':');
          SERIAL_DECIMAL(planner.extruder_advance_K[i]);
        }
        SERIAL_EOL();
      #endif

    #endif
  }

>>>>>>> mcu_ctrl
}

#endif // LIN_ADVANCE
