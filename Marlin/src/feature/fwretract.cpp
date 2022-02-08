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
 * fwretract.cpp - Implement firmware-based retraction
 */

#include "../inc/MarlinConfig.h"

#if ENABLED(FWRETRACT)

#include "fwretract.h"

FWRetract fwretract; // Single instance - this calls the constructor

#include "../module/motion.h"
#include "../module/planner.h"
#include "../module/stepper.h"

<<<<<<< HEAD
=======
#include "../gcode/parser.h"

>>>>>>> mcu_ctrl
#if ENABLED(RETRACT_SYNC_MIXING)
  #include "mixing.h"
#endif

// private:

<<<<<<< HEAD
#if EXTRUDERS > 1
=======
#if HAS_MULTI_EXTRUDER
>>>>>>> mcu_ctrl
  bool FWRetract::retracted_swap[EXTRUDERS];          // Which extruders are swap-retracted
#endif

// public:

fwretract_settings_t FWRetract::settings;             // M207 S F Z W, M208 S F W R

#if ENABLED(FWRETRACT_AUTORETRACT)
  bool FWRetract::autoretract_enabled;                // M209 S - Autoretract switch
#endif

bool FWRetract::retracted[EXTRUDERS];                 // Which extruders are currently retracted

float FWRetract::current_retract[EXTRUDERS],          // Retract value used by planner
      FWRetract::current_hop;

void FWRetract::reset() {
<<<<<<< HEAD
  #if ENABLED(FWRETRACT_AUTORETRACT)
    autoretract_enabled = false;
  #endif
=======
  TERN_(FWRETRACT_AUTORETRACT, autoretract_enabled = false);
>>>>>>> mcu_ctrl
  settings.retract_length = RETRACT_LENGTH;
  settings.retract_feedrate_mm_s = RETRACT_FEEDRATE;
  settings.retract_zraise = RETRACT_ZRAISE;
  settings.retract_recover_extra = RETRACT_RECOVER_LENGTH;
  settings.retract_recover_feedrate_mm_s = RETRACT_RECOVER_FEEDRATE;
  settings.swap_retract_length = RETRACT_LENGTH_SWAP;
  settings.swap_retract_recover_extra = RETRACT_RECOVER_LENGTH_SWAP;
  settings.swap_retract_recover_feedrate_mm_s = RETRACT_RECOVER_FEEDRATE_SWAP;
  current_hop = 0.0;

<<<<<<< HEAD
  for (uint8_t i = 0; i < EXTRUDERS; ++i) {
    retracted[i] = false;
    #if EXTRUDERS > 1
      retracted_swap[i] = false;
    #endif
=======
  LOOP_L_N(i, EXTRUDERS) {
    retracted[i] = false;
    TERN_(HAS_MULTI_EXTRUDER, retracted_swap[i] = false);
>>>>>>> mcu_ctrl
    current_retract[i] = 0.0;
  }
}

/**
 * Retract or recover according to firmware settings
 *
 * This function handles retract/recover moves for G10 and G11,
 * plus auto-retract moves sent from G0/G1 when E-only moves are done.
 *
 * To simplify the logic, doubled retract/recover moves are ignored.
 *
 * Note: Auto-retract will apply the set Z hop in addition to any Z hop
 *       included in the G-code. Use M207 Z0 to to prevent double hop.
 */
<<<<<<< HEAD
void FWRetract::retract(const bool retracting
  #if EXTRUDERS > 1
    , bool swapping /* =false */
  #endif
) {
=======
void FWRetract::retract(const bool retracting OPTARG(HAS_MULTI_EXTRUDER, bool swapping/*=false*/)) {
>>>>>>> mcu_ctrl
  // Prevent two retracts or recovers in a row
  if (retracted[active_extruder] == retracting) return;

  // Prevent two swap-retract or recovers in a row
<<<<<<< HEAD
  #if EXTRUDERS > 1
=======
  #if HAS_MULTI_EXTRUDER
>>>>>>> mcu_ctrl
    // Allow G10 S1 only after G11
    if (swapping && retracted_swap[active_extruder] == retracting) return;
    // G11 priority to recover the long retract if activated
    if (!retracting) swapping = retracted_swap[active_extruder];
  #else
    constexpr bool swapping = false;
  #endif

  /* // debugging
    SERIAL_ECHOLNPAIR(
<<<<<<< HEAD
      "retracting ", retracting,
      " swapping ", swapping,
      " active extruder ", active_extruder
    );
    for (uint8_t i = 0; i < EXTRUDERS; ++i) {
      SERIAL_ECHOLNPAIR("retracted[", i, "] ", retracted[i]);
      #if EXTRUDERS > 1
        SERIAL_ECHOLNPAIR("retracted_swap[", i, "] ", retracted_swap[i]);
=======
      "retracting ", AS_DIGIT(retracting),
      " swapping ", swapping,
      " active extruder ", active_extruder
    );
    LOOP_L_N(i, EXTRUDERS) {
      SERIAL_ECHOLNPAIR("retracted[", i, "] ", AS_DIGIT(retracted[i]));
      #if HAS_MULTI_EXTRUDER
        SERIAL_ECHOLNPAIR("retracted_swap[", i, "] ", AS_DIGIT(retracted_swap[i]));
>>>>>>> mcu_ctrl
      #endif
    }
    SERIAL_ECHOLNPAIR("current_position.z ", current_position.z);
    SERIAL_ECHOLNPAIR("current_position.e ", current_position.e);
    SERIAL_ECHOLNPAIR("current_hop ", current_hop);
  //*/

<<<<<<< HEAD
  const float base_retract = (
                (swapping ? settings.swap_retract_length : settings.retract_length)
                #if ENABLED(RETRACT_SYNC_MIXING)
                  * (MIXING_STEPPERS)
                #endif
              );
=======
  const float base_retract = TERN1(RETRACT_SYNC_MIXING, (MIXING_STEPPERS))
                * (swapping ? settings.swap_retract_length : settings.retract_length);
>>>>>>> mcu_ctrl

  // The current position will be the destination for E and Z moves
  destination = current_position;

  #if ENABLED(RETRACT_SYNC_MIXING)
    const uint8_t old_mixing_tool = mixer.get_current_vtool();
    mixer.T(MIXER_AUTORETRACT_TOOL);
  #endif

  const feedRate_t fr_max_z = planner.settings.max_feedrate_mm_s[Z_AXIS];
  if (retracting) {
    // Retract by moving from a faux E position back to the current E position
    current_retract[active_extruder] = base_retract;
<<<<<<< HEAD
    prepare_internal_move_to_destination(                 // set current to destination
      settings.retract_feedrate_mm_s
      #if ENABLED(RETRACT_SYNC_MIXING)
        * (MIXING_STEPPERS)
      #endif
=======
    prepare_internal_move_to_destination(                 // set current from destination
      settings.retract_feedrate_mm_s * TERN1(RETRACT_SYNC_MIXING, (MIXING_STEPPERS))
>>>>>>> mcu_ctrl
    );

    // Is a Z hop set, and has the hop not yet been done?
    if (!current_hop && settings.retract_zraise > 0.01f) {  // Apply hop only once
      current_hop += settings.retract_zraise;               // Add to the hop total (again, only once)
      // Raise up, set_current_to_destination. Maximum Z feedrate
      prepare_internal_move_to_destination(fr_max_z);
    }
  }
  else {
    // If a hop was done and Z hasn't changed, undo the Z hop
    if (current_hop) {
      current_hop = 0;
      // Lower Z, set_current_to_destination. Maximum Z feedrate
      prepare_internal_move_to_destination(fr_max_z);
    }

    const float extra_recover = swapping ? settings.swap_retract_recover_extra : settings.retract_recover_extra;
    if (extra_recover) {
      current_position.e -= extra_recover;          // Adjust the current E position by the extra amount to recover
      sync_plan_position_e();                             // Sync the planner position so the extra amount is recovered
    }

    current_retract[active_extruder] = 0;

<<<<<<< HEAD
    const feedRate_t fr_mm_s = (
      (swapping ? settings.swap_retract_recover_feedrate_mm_s : settings.retract_recover_feedrate_mm_s)
      #if ENABLED(RETRACT_SYNC_MIXING)
        * (MIXING_STEPPERS)
      #endif
    );
    prepare_internal_move_to_destination(fr_mm_s);        // Recover E, set_current_to_destination
  }

  #if ENABLED(RETRACT_SYNC_MIXING)
    mixer.T(old_mixing_tool);                             // Restore original mixing tool
  #endif
=======
    // Recover E, set_current_to_destination
    prepare_internal_move_to_destination(
      (swapping ? settings.swap_retract_recover_feedrate_mm_s : settings.retract_recover_feedrate_mm_s)
      * TERN1(RETRACT_SYNC_MIXING, (MIXING_STEPPERS))
    );
  }

  TERN_(RETRACT_SYNC_MIXING, mixer.T(old_mixing_tool));   // Restore original mixing tool
>>>>>>> mcu_ctrl

  retracted[active_extruder] = retracting;                // Active extruder now retracted / recovered

  // If swap retract/recover update the retracted_swap flag too
<<<<<<< HEAD
  #if EXTRUDERS > 1
=======
  #if HAS_MULTI_EXTRUDER
>>>>>>> mcu_ctrl
    if (swapping) retracted_swap[active_extruder] = retracting;
  #endif

  /* // debugging
<<<<<<< HEAD
    SERIAL_ECHOLNPAIR("retracting ", retracting);
    SERIAL_ECHOLNPAIR("swapping ", swapping);
    SERIAL_ECHOLNPAIR("active_extruder ", active_extruder);
    for (uint8_t i = 0; i < EXTRUDERS; ++i) {
      SERIAL_ECHOLNPAIR("retracted[", i, "] ", retracted[i]);
      #if EXTRUDERS > 1
        SERIAL_ECHOLNPAIR("retracted_swap[", i, "] ", retracted_swap[i]);
=======
    SERIAL_ECHOLNPAIR("retracting ", AS_DIGIT(retracting));
    SERIAL_ECHOLNPAIR("swapping ", AS_DIGIT(swapping));
    SERIAL_ECHOLNPAIR("active_extruder ", active_extruder);
    LOOP_L_N(i, EXTRUDERS) {
      SERIAL_ECHOLNPAIR("retracted[", i, "] ", AS_DIGIT(retracted[i]));
      #if HAS_MULTI_EXTRUDER
        SERIAL_ECHOLNPAIR("retracted_swap[", i, "] ", AS_DIGIT(retracted_swap[i]));
>>>>>>> mcu_ctrl
      #endif
    }
    SERIAL_ECHOLNPAIR("current_position.z ", current_position.z);
    SERIAL_ECHOLNPAIR("current_position.e ", current_position.e);
    SERIAL_ECHOLNPAIR("current_hop ", current_hop);
  //*/
}

<<<<<<< HEAD
=======
//extern const char SP_Z_STR[];

/**
 * M207: Set firmware retraction values
 *
 *   S[+units]    retract_length
 *   W[+units]    swap_retract_length (multi-extruder)
 *   F[units/min] retract_feedrate_mm_s
 *   Z[units]     retract_zraise
 */
void FWRetract::M207() {
  if (!parser.seen("FSWZ")) return M207_report();
  if (parser.seenval('S')) settings.retract_length        = parser.value_axis_units(E_AXIS);
  if (parser.seenval('F')) settings.retract_feedrate_mm_s = MMM_TO_MMS(parser.value_axis_units(E_AXIS));
  if (parser.seenval('Z')) settings.retract_zraise        = parser.value_linear_units();
  if (parser.seenval('W')) settings.swap_retract_length   = parser.value_axis_units(E_AXIS);
}

void FWRetract::M207_report(const bool forReplay/*=false*/) {
  if (!forReplay) { SERIAL_ECHO_MSG("; Retract: S<length> F<units/m> Z<lift>"); SERIAL_ECHO_START(); }
  SERIAL_ECHOLNPAIR_P(
      PSTR("  M207 S"), LINEAR_UNIT(settings.retract_length)
    , PSTR(" W"), LINEAR_UNIT(settings.swap_retract_length)
    , PSTR(" F"), LINEAR_UNIT(MMS_TO_MMM(settings.retract_feedrate_mm_s))
    , SP_Z_STR, LINEAR_UNIT(settings.retract_zraise)
  );
}

/**
 * M208: Set firmware un-retraction values
 *
 *   S[+units]    retract_recover_extra (in addition to M207 S*)
 *   W[+units]    swap_retract_recover_extra (multi-extruder)
 *   F[units/min] retract_recover_feedrate_mm_s
 *   R[units/min] swap_retract_recover_feedrate_mm_s
 */
void FWRetract::M208() {
  if (!parser.seen("FSRW")) return M208_report();
  if (parser.seen('S')) settings.retract_recover_extra              = parser.value_axis_units(E_AXIS);
  if (parser.seen('F')) settings.retract_recover_feedrate_mm_s      = MMM_TO_MMS(parser.value_axis_units(E_AXIS));
  if (parser.seen('R')) settings.swap_retract_recover_feedrate_mm_s = MMM_TO_MMS(parser.value_axis_units(E_AXIS));
  if (parser.seen('W')) settings.swap_retract_recover_extra         = parser.value_axis_units(E_AXIS);
}

void FWRetract::M208_report(const bool forReplay/*=false*/) {
  if (!forReplay) { SERIAL_ECHO_MSG("; Recover: S<length> F<units/m>"); SERIAL_ECHO_START(); }
  SERIAL_ECHOLNPAIR(
      "  M208 S", LINEAR_UNIT(settings.retract_recover_extra)
    , " W", LINEAR_UNIT(settings.swap_retract_recover_extra)
    , " F", LINEAR_UNIT(MMS_TO_MMM(settings.retract_recover_feedrate_mm_s))
  );
}

#if ENABLED(FWRETRACT_AUTORETRACT)

  /**
   * M209: Enable automatic retract (M209 S1)
   *   For slicers that don't support G10/11, reversed extrude-only
   *   moves will be classified as retraction.
   */
  void FWRetract::M209() {
    if (!parser.seen('S')) return M209_report();
    if (MIN_AUTORETRACT <= MAX_AUTORETRACT)
      enable_autoretract(parser.value_bool());
  }

  void FWRetract::M209_report(const bool forReplay/*=false*/) {
    if (!forReplay) { SERIAL_ECHO_MSG("; Auto-Retract: S=0 to disable, 1 to interpret E-only moves as retract/recover"); SERIAL_ECHO_START(); }
    SERIAL_ECHOLNPAIR("  M209 S", AS_DIGIT(autoretract_enabled));
  }

#endif // FWRETRACT_AUTORETRACT


>>>>>>> mcu_ctrl
#endif // FWRETRACT
