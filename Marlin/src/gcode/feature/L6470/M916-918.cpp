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

#include "../../../inc/MarlinConfig.h"

#if HAS_DRIVER(L6470)
=======
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

//
// NOTE: All tests assume each axis uses matching driver chips.
//

#include "../../../inc/MarlinConfig.h"

#if HAS_L64XX
>>>>>>> mcu_ctrl

#include "../../gcode.h"
#include "../../../module/stepper/indirection.h"
#include "../../../module/planner.h"
<<<<<<< HEAD
#include "../../../libs/L6470/L6470_Marlin.h"
=======
#include "../../../libs/L64XX/L64XX_Marlin.h"
>>>>>>> mcu_ctrl

#define DEBUG_OUT ENABLED(L6470_CHITCHAT)
#include "../../../core/debug_out.h"

<<<<<<< HEAD
static void jiggle_axis(const char axis_char, const float &min, const float &max, const feedRate_t &fr_mm_m) {
  char gcode_string[30], str1[11], str2[11];

  // Turn the motor(s) both directions
  sprintf_P(gcode_string, PSTR("G0 %c%s F%s"), axis_char, dtostrf(min, 1, 3, str1), dtostrf(fr_mm_m, 1, 3, str2));
  gcode.process_subcommands_now(gcode_string);

  sprintf_P(gcode_string, PSTR("G0 %c%s F%s"), axis_char, dtostrf(max, 1, 3, str1), str2);
  gcode.process_subcommands_now(gcode_string);

  planner.synchronize();
}

/**
 *
 * M916: Increase KVAL_HOLD until thermal warning
 *
=======
/**
 * M916: increase KVAL_HOLD until get thermal warning
 *       NOTE - on L6474 it is TVAL that is used
>>>>>>> mcu_ctrl
 *
 * J - select which driver(s) to monitor on multi-driver axis
 *     0 - (default) monitor all drivers on the axis or E0
 *     1 - monitor only X, Y, Z, E1
 *     2 - monitor only X2, Y2, Z2, E2
 *     3 - monitor only Z3, E3
<<<<<<< HEAD
=======
 *     4 - monitor only Z4, E4
>>>>>>> mcu_ctrl
 *
 * Xxxx, Yxxx, Zxxx, Exxx - axis to be monitored with displacement
 *     xxx (1-255) is distance moved on either side of current position
 *
 * F - feedrate
 *     optional - will use default max feedrate from configuration.h if not specified
 *
<<<<<<< HEAD
 * K - starting value for KVAL_HOLD (0 - 255)
 *     optional - will use & report current value from driver if not specified
 *
=======
 * T - current (mA) setting for TVAL (0 - 4A in 31.25mA increments, rounds down) - L6474 only
 *     optional - will report current value from driver if not specified
 *
 * K - value for KVAL_HOLD (0 - 255) (ignored for L6474)
 *     optional - will report current value from driver if not specified
 *
 * D - time (in seconds) to run each setting of KVAL_HOLD/TVAL
 *     optional - defaults to zero (runs each setting once)
>>>>>>> mcu_ctrl
 */

/**
 * This routine is also useful for determining the approximate KVAL_HOLD
 * where the stepper stops losing steps. The sound will get noticeably quieter
 * as it stops losing steps.
 */

void GcodeSuite::M916() {

  DEBUG_ECHOLNPGM("M916");

<<<<<<< HEAD
  // Variables used by L6470_get_user_input function - some may not be used
  char axis_mon[3][3] = { "  ", "  ", "  " };  // list of Axes to be monitored
  uint8_t axis_index[3];
=======
  L64xxManager.pause_monitor(true); // Keep monitor_driver() from stealing status

  // Variables used by L64xxManager.get_user_input function - some may not be used
  char axis_mon[3][3] = { {"  "}, {"  "}, {"  "} };   // list of Axes to be monitored
  L64XX_axis_t axis_index[3];
>>>>>>> mcu_ctrl
  uint16_t axis_status[3];
  uint8_t driver_count = 1;
  float position_max;
  float position_min;
<<<<<<< HEAD
  feedRate_t final_fr_mm_m;
  uint8_t kval_hold;
  uint8_t ocd_th_val = 0;
  uint8_t stall_th_val = 0;
  uint16_t over_current_threshold;
  constexpr bool over_current_flag = false;  // M916 doesn't play with the overcurrent thresholds

  uint8_t j;   // general purpose counter

  if (L6470.get_user_input(driver_count, axis_index, axis_mon, position_max, position_min, final_fr_mm_m, kval_hold, over_current_flag, ocd_th_val, stall_th_val, over_current_threshold))
    return;  // quit if invalid user input

  DEBUG_ECHOLNPAIR("feedrate = ", final_fr_mm_m);

  planner.synchronize();                  // Wait for moves to finish

  for (j = 0; j < driver_count; j++)
    L6470.get_status(axis_index[j]);      // Clear out error flags

  uint16_t status_composite = 0;

=======
  float final_feedrate;
  uint8_t kval_hold;
  uint8_t OCD_TH_val = 0;
  uint8_t STALL_TH_val = 0;
  uint16_t over_current_threshold;
  constexpr uint8_t over_current_flag = false;  // M916 doesn't play with the overcurrent thresholds

  #define DRIVER_TYPE_L6474(Q) AXIS_DRIVER_TYPE_##Q(L6474)

  uint8_t j;   // general purpose counter

  if (L64xxManager.get_user_input(driver_count, axis_index, axis_mon, position_max, position_min, final_feedrate, kval_hold, over_current_flag, OCD_TH_val, STALL_TH_val, over_current_threshold))
    return;  // quit if invalid user input

  DEBUG_ECHOLNPAIR("feedrate = ", final_feedrate);

  planner.synchronize();                             // wait for all current movement commands to complete

  const L64XX_Marlin::L64XX_shadow_t &sh = L64xxManager.shadow;
  for (j = 0; j < driver_count; j++)
    L64xxManager.get_status(axis_index[j]);  // clear out any pre-existing error flags

  char temp_axis_string[] = " ";
  temp_axis_string[0] = axis_mon[0][0];  // need to have a string for use within sprintf format section
  char gcode_string[80];
  uint16_t status_composite = 0;

  uint16_t M91x_counter = kval_hold;
  uint16_t M91x_counter_max;
  if (sh.STATUS_AXIS_LAYOUT == L6474_STATUS_LAYOUT) {
    M91x_counter_max = 128;  // TVAL is 7 bits
    LIMIT(M91x_counter, 0U, 127U);
  }
  else
    M91x_counter_max = 256;  // KVAL_HOLD is 8 bits

  uint8_t M91x_delay_s = parser.byteval('D');   // get delay in seconds
  millis_t M91x_delay_ms = SEC_TO_MS(M91x_delay_s * 60);
  millis_t M91x_delay_end;

>>>>>>> mcu_ctrl
  DEBUG_ECHOLNPGM(".\n.");

  do {

<<<<<<< HEAD
    DEBUG_ECHOLNPAIR("kval_hold = ", kval_hold);   // set & report KVAL_HOLD for this run

    for (j = 0; j < driver_count; j++)
      L6470.set_param(axis_index[j], L6470_KVAL_HOLD, kval_hold);

    // Turn the motor(s) both directions
    jiggle_axis(axis_mon[0][0], position_min, position_max, final_fr_mm_m);

    status_composite = 0;    // clear out the old bits

    for (j = 0; j < driver_count; j++) {
      axis_status[j] = (~L6470.get_status(axis_index[j])) & L6470_ERROR_MASK;    // bits of interest are all active low
      status_composite |= axis_status[j] ;
    }

    if (status_composite && (status_composite & STATUS_UVLO)) {
      DEBUG_ECHOLNPGM("Test aborted (Undervoltage lockout active)");
      for (j = 0; j < driver_count; j++) {
        DEBUG_ECHOPGM("...");
        L6470.error_status_decode(axis_status[j], axis_index[j]);
      }
      return;
    }

    // increment KVAL_HOLD if not yet at thermal warning/shutdown
    if (!(status_composite & (STATUS_TH_WRN | STATUS_TH_SD)))
      kval_hold++;

  } while (!(status_composite & (STATUS_TH_WRN | STATUS_TH_SD)) && kval_hold);  // exit when kval_hold == 0 (rolls over)

  DEBUG_ECHOPGM(".\n.\nThermal warning/shutdown ");
  if ((status_composite & (STATUS_TH_WRN | STATUS_TH_SD))) {
    DEBUG_ECHOLNPGM("has occurred");
    for (j = 0; j < driver_count; j++) {
      DEBUG_ECHOPGM("...");
      L6470.error_status_decode(axis_status[j], axis_index[j]);
    }
  }
  else
    DEBUG_ECHOLNPGM("(Unable to get)");

  DEBUG_ECHOLNPGM(".");
}

/**
 *
=======
    if (sh.STATUS_AXIS_LAYOUT == L6474_STATUS_LAYOUT)
      DEBUG_ECHOLNPAIR("TVAL current (mA) = ", (M91x_counter + 1) * sh.AXIS_STALL_CURRENT_CONSTANT_INV);        // report TVAL current for this run
    else
      DEBUG_ECHOLNPAIR("kval_hold = ", M91x_counter);                                   // report KVAL_HOLD for this run

    for (j = 0; j < driver_count; j++)
      L64xxManager.set_param(axis_index[j], L6470_KVAL_HOLD, M91x_counter);  //set KVAL_HOLD or TVAL (same register address)

    M91x_delay_end = millis() + M91x_delay_ms;
    do {
      // turn the motor(s) both directions
      sprintf_P(gcode_string, PSTR("G0 %s%03d F%03d"), temp_axis_string, uint16_t(position_min), uint16_t(final_feedrate));
      gcode.process_subcommands_now_P(gcode_string);

      sprintf_P(gcode_string, PSTR("G0 %s%03d F%03d"), temp_axis_string, uint16_t(position_max), uint16_t(final_feedrate));
      gcode.process_subcommands_now_P(gcode_string);

      // get the status after the motors have stopped
      planner.synchronize();

      status_composite = 0;    // clear out the old bits

      for (j = 0; j < driver_count; j++) {
        axis_status[j] = (~L64xxManager.get_status(axis_index[j])) & sh.L6470_ERROR_MASK;    // bits of interest are all active low
        status_composite |= axis_status[j] ;
      }

      if (status_composite) break;
    } while (millis() < M91x_delay_end);

    if (status_composite) break;

    M91x_counter++;

  } while (!(status_composite & (sh.STATUS_AXIS_TH_WRN | sh.STATUS_AXIS_TH_SD)) && (M91x_counter < M91x_counter_max));

  DEBUG_ECHOLNPGM(".");

  #if ENABLED(L6470_CHITCHAT)
    if (status_composite) {
      L64xxManager.error_status_decode(status_composite, axis_index[0],
        sh.STATUS_AXIS_TH_SD, sh.STATUS_AXIS_TH_WRN,
        sh.STATUS_AXIS_STEP_LOSS_A, sh.STATUS_AXIS_STEP_LOSS_B,
        sh.STATUS_AXIS_OCD, sh.STATUS_AXIS_LAYOUT);
      DEBUG_ECHOLNPGM(".");
    }
  #endif

  if ((status_composite & (sh.STATUS_AXIS_TH_WRN | sh.STATUS_AXIS_TH_SD)))
    DEBUG_ECHOLNPGM(".\n.\nTest completed normally - Thermal warning/shutdown has occurred");
  else if (status_composite)
    DEBUG_ECHOLNPGM(".\n.\nTest completed abnormally - non-thermal error has occured");
  else
    DEBUG_ECHOLNPGM(".\n.\nTest completed normally - Unable to get to thermal warning/shutdown");

  L64xxManager.pause_monitor(false);
}

/**
>>>>>>> mcu_ctrl
 * M917: Find minimum current thresholds
 *
 *   Decrease OCD current until overcurrent error
 *   Increase OCD until overcurrent error goes away
<<<<<<< HEAD
 *   Decrease stall threshold until stall
 *   Increase stall until stall error goes away
=======
 *   Decrease stall threshold until stall (not done on L6474)
 *   Increase stall until stall error goes away (not done on L6474)
>>>>>>> mcu_ctrl
 *
 * J - select which driver(s) to monitor on multi-driver axis
 *     0 - (default) monitor all drivers on the axis or E0
 *     1 - monitor only X, Y, Z, E1
 *     2 - monitor only X2, Y2, Z2, E2
 * Xxxx, Yxxx, Zxxx, Exxx - axis to be monitored with displacement
 *     xxx (1-255) is distance moved on either side of current position
 *
 * F - feedrate
 *     optional - will use default max feedrate from Configuration.h if not specified
 *
 * I - starting over-current threshold
 *     optional - will report current value from driver if not specified
 *     if there are multiple drivers on the axis then all will be set the same
 *
<<<<<<< HEAD
 * K - value for KVAL_HOLD (0 - 255)
 *     optional - will report current value from driver if not specified
 *
=======
 * T - current (mA) setting for TVAL (0 - 4A in 31.25mA increments, rounds down) - L6474 only
 *     optional - will report current value from driver if not specified
 *
 * K - value for KVAL_HOLD (0 - 255) (ignored for L6474)
 *     optional - will report current value from driver if not specified
>>>>>>> mcu_ctrl
 */
void GcodeSuite::M917() {

  DEBUG_ECHOLNPGM("M917");

<<<<<<< HEAD
  char axis_mon[3][3] = { "  ", "  ", "  " };  // list of axes to be monitored
  uint8_t axis_index[3];
=======
  L64xxManager.pause_monitor(true); // Keep monitor_driver() from stealing status

  char axis_mon[3][3] = { {"  "}, {"  "}, {"  "} };   // list of Axes to be monitored
  L64XX_axis_t axis_index[3];
>>>>>>> mcu_ctrl
  uint16_t axis_status[3];
  uint8_t driver_count = 1;
  float position_max;
  float position_min;
<<<<<<< HEAD
  feedRate_t final_fr_mm_m;
  uint8_t kval_hold;
  uint8_t ocd_th_val = 0;
  uint8_t stall_th_val = 0;
  uint16_t over_current_threshold;
  constexpr bool over_current_flag = true;

  uint8_t j;   // general purpose counter

  if (L6470.get_user_input(driver_count, axis_index, axis_mon, position_max, position_min, final_fr_mm_m, kval_hold, over_current_flag, ocd_th_val, stall_th_val, over_current_threshold))
    return;  // quit if invalid user input

  DEBUG_ECHOLNPAIR("feedrate = ", final_fr_mm_m);

  planner.synchronize();                // Wait for moves to finish
  for (j = 0; j < driver_count; j++)
    L6470.get_status(axis_index[j]);    // Clear out error flags
  uint16_t status_composite = 0;
  uint8_t test_phase = 0;
        // 0 - decreasing OCD - exit when OCD warning occurs (ignore STALL)
        // 1 - increasing OCD - exit when OCD warning stops (ignore STALL) -
        // 2 - OCD finalized - decreasing STALL - exit when STALL warning happens
        // 3 - OCD finalized - increasing STALL - exit when STALL warning stop
        // 4 - all testing completed
  DEBUG_ECHOPAIR(".\n.\n.\nover_current threshold : ", (ocd_th_val + 1) * 375);   // first status display
  DEBUG_ECHOPAIR("  (OCD_TH:  : ", ocd_th_val);
  DEBUG_ECHOPAIR(")   Stall threshold: ", (stall_th_val + 1) * 31.25);
  DEBUG_ECHOPAIR("  (STALL_TH: ", stall_th_val);
=======
  float final_feedrate;
  uint8_t kval_hold;
  uint8_t OCD_TH_val = 0;
  uint8_t STALL_TH_val = 0;
  uint16_t over_current_threshold;
  constexpr uint8_t over_current_flag = true;

  uint8_t j;   // general purpose counter

  if (L64xxManager.get_user_input(driver_count, axis_index, axis_mon, position_max, position_min, final_feedrate, kval_hold, over_current_flag, OCD_TH_val, STALL_TH_val, over_current_threshold))
    return;  // quit if invalid user input

  DEBUG_ECHOLNPAIR("feedrate = ", final_feedrate);

  planner.synchronize();                             // wait for all current movement commands to complete

  const L64XX_Marlin::L64XX_shadow_t &sh = L64xxManager.shadow;
  for (j = 0; j < driver_count; j++)
    L64xxManager.get_status(axis_index[j]);  // clear error flags
  char temp_axis_string[] = " ";
  temp_axis_string[0] = axis_mon[0][0];   // need a sprintf format string
  char gcode_string[80];
  uint16_t status_composite = 0;
  uint8_t test_phase = 0;                 // 0 - decreasing OCD - exit when OCD warning occurs (ignore STALL)
                                          // 1 - increasing OCD - exit when OCD warning stops (ignore STALL)
                                          // 2 - OCD finalized - decreasing STALL - exit when STALL warning happens
                                          // 3 - OCD finalized - increasing STALL - exit when STALL warning stop
                                          // 4 - all testing completed
  DEBUG_ECHOPAIR(".\n.\n.\nover_current threshold : ", (OCD_TH_val + 1) * 375);   // first status display
  DEBUG_ECHOPAIR("  (OCD_TH:  : ", OCD_TH_val);
  if (sh.STATUS_AXIS_LAYOUT != L6474_STATUS_LAYOUT) {
    DEBUG_ECHOPAIR(")   Stall threshold: ", (STALL_TH_val + 1) * 31.25);
    DEBUG_ECHOPAIR("  (STALL_TH: ", STALL_TH_val);
  }
>>>>>>> mcu_ctrl
  DEBUG_ECHOLNPGM(")");

  do {

<<<<<<< HEAD
    DEBUG_ECHOPAIR("STALL threshold : ", (stall_th_val + 1) * 31.25);
    DEBUG_ECHOLNPAIR("   OCD threshold : ", (ocd_th_val + 1) * 375);

    jiggle_axis(axis_mon[0][0], position_min, position_max, final_fr_mm_m);
=======
    if (sh.STATUS_AXIS_LAYOUT != L6474_STATUS_LAYOUT) DEBUG_ECHOPAIR("STALL threshold : ", (STALL_TH_val + 1) * 31.25);
    DEBUG_ECHOLNPAIR("   OCD threshold : ", (OCD_TH_val + 1) * 375);

    sprintf_P(gcode_string, PSTR("G0 %s%03d F%03d"), temp_axis_string, uint16_t(position_min), uint16_t(final_feedrate));
    gcode.process_subcommands_now_P(gcode_string);

    sprintf_P(gcode_string, PSTR("G0 %s%03d F%03d"), temp_axis_string, uint16_t(position_max), uint16_t(final_feedrate));
    gcode.process_subcommands_now_P(gcode_string);

    planner.synchronize();
>>>>>>> mcu_ctrl

    status_composite = 0;    // clear out the old bits

    for (j = 0; j < driver_count; j++) {
<<<<<<< HEAD
      axis_status[j] = (~L6470.get_status(axis_index[j])) & L6470_ERROR_MASK;    // bits of interest are all active low
      status_composite |= axis_status[j];
    }

    if (status_composite && (status_composite & STATUS_UVLO)) {
      DEBUG_ECHOLNPGM("Test aborted (Undervoltage lockout active)");
      for (j = 0; j < driver_count; j++) {
        DEBUG_ECHOPGM("...");
        L6470.error_status_decode(axis_status[j], axis_index[j]);
      }
      return;
    }

    if (status_composite & (STATUS_TH_WRN | STATUS_TH_SD)) {
=======
      axis_status[j] = (~L64xxManager.get_status(axis_index[j])) & sh.L6470_ERROR_MASK;    // bits of interest are all active low
      status_composite |= axis_status[j];
    }

    if (status_composite && (status_composite & sh.STATUS_AXIS_UVLO)) {
      DEBUG_ECHOLNPGM("Test aborted (Undervoltage lockout active)");
      #if ENABLED(L6470_CHITCHAT)
        for (j = 0; j < driver_count; j++) {
          if (j) DEBUG_ECHOPGM("...");
          L64xxManager.error_status_decode(axis_status[j], axis_index[j],
            sh.STATUS_AXIS_TH_SD, sh.STATUS_AXIS_TH_WRN,
            sh.STATUS_AXIS_STEP_LOSS_A, sh.STATUS_AXIS_STEP_LOSS_B,
            sh.STATUS_AXIS_OCD, sh.STATUS_AXIS_LAYOUT);
        }
      #endif
      return;
    }

    if (status_composite & (sh.STATUS_AXIS_TH_WRN | sh.STATUS_AXIS_TH_SD)) {
>>>>>>> mcu_ctrl
      DEBUG_ECHOLNPGM("thermal problem - waiting for chip(s) to cool down ");
      uint16_t status_composite_temp = 0;
      uint8_t k = 0;
      do {
        k++;
        if (!(k % 4)) {
          kval_hold *= 0.95;
<<<<<<< HEAD
          L6470_EOL();
          DEBUG_ECHOLNPAIR("Lowering KVAL_HOLD by about 5% to ", kval_hold);
          for (j = 0; j < driver_count; j++)
            L6470.set_param(axis_index[j], L6470_KVAL_HOLD, kval_hold);
        }
        DEBUG_ECHOLNPGM(".");
        reset_stepper_timeout(); // reset_stepper_timeout to keep steppers powered
=======
          DEBUG_EOL();
          DEBUG_ECHOLNPAIR("Lowering KVAL_HOLD by about 5% to ", kval_hold);
          for (j = 0; j < driver_count; j++)
            L64xxManager.set_param(axis_index[j], L6470_KVAL_HOLD, kval_hold);
        }
        DEBUG_ECHOLNPGM(".");
        gcode.reset_stepper_timeout(); // keep steppers powered
>>>>>>> mcu_ctrl
        watchdog_refresh();
        safe_delay(5000);
        status_composite_temp = 0;
        for (j = 0; j < driver_count; j++) {
<<<<<<< HEAD
          axis_status[j] = (~L6470.get_status(axis_index[j])) & L6470_ERROR_MASK;    // bits of interest are all active low
          status_composite_temp |= axis_status[j];
        }
      }
      while (status_composite_temp & (STATUS_TH_WRN | STATUS_TH_SD));
      L6470_EOL();
    }
    if (status_composite & (STATUS_STEP_LOSS_A | STATUS_STEP_LOSS_B | STATUS_OCD)) {
      switch (test_phase) {

        case 0: {
          if (status_composite & STATUS_OCD) {
            // phase 0 with OCD warning - time to go to next phase
            if (ocd_th_val >=15) {
              ocd_th_val = 15;           // limit to max
              test_phase = 2;            // at highest value so skip phase 1
              DEBUG_ECHOLNPGM("LOGIC E0A OCD at highest - skip to 2");
            }
            else {
              ocd_th_val++;              // normal exit to next phase
              test_phase = 1;            // setup for first pass of phase 1
              DEBUG_ECHOLNPGM("LOGIC E0B - inc OCD  & go to 1");
            }
          }
          else {  // phase 0 without OCD warning - keep on decrementing if can
            if (ocd_th_val) {
              ocd_th_val--;              // try lower value
              DEBUG_ECHOLNPGM("LOGIC E0C - dec OCD");
            }
            else {
              test_phase = 2;            // at lowest value without warning so skip phase 1
              DEBUG_ECHOLNPGM("LOGIC E0D - OCD at latest - go to 2");
=======
          axis_status[j] = (~L64xxManager.get_status(axis_index[j])) & sh.L6470_ERROR_MASK;    // bits of interest are all active low
          status_composite_temp |= axis_status[j];
        }
      }
      while (status_composite_temp & (sh.STATUS_AXIS_TH_WRN | sh.STATUS_AXIS_TH_SD));
      DEBUG_EOL();
    }
    if (status_composite & (sh.STATUS_AXIS_STEP_LOSS_A | sh.STATUS_AXIS_STEP_LOSS_B | sh.STATUS_AXIS_OCD)) {
      switch (test_phase) {

        case 0: {
          if (status_composite & sh.STATUS_AXIS_OCD) {
            // phase 0 with OCD warning - time to go to next phase
            if (OCD_TH_val >= sh.AXIS_OCD_TH_MAX) {
              OCD_TH_val = sh.AXIS_OCD_TH_MAX;           // limit to max
              test_phase = 2;            // at highest value so skip phase 1
              //DEBUG_ECHOLNPGM("LOGIC E0A OCD at highest - skip to 2");
              DEBUG_ECHOLNPGM("OCD at highest - OCD finalized");
            }
            else {
              OCD_TH_val++;              // normal exit to next phase
              test_phase = 1;            // setup for first pass of phase 1
              //DEBUG_ECHOLNPGM("LOGIC E0B - inc OCD  & go to 1");
              DEBUG_ECHOLNPGM("inc OCD");
            }
          }
          else {  // phase 0 without OCD warning - keep on decrementing if can
            if (OCD_TH_val) {
              OCD_TH_val--;              // try lower value
              //DEBUG_ECHOLNPGM("LOGIC E0C - dec OCD");
              DEBUG_ECHOLNPGM("dec OCD");
            }
            else {
              test_phase = 2;            // at lowest value without warning so skip phase 1
              //DEBUG_ECHOLNPGM("LOGIC E0D - OCD at latest - go to 2");
              DEBUG_ECHOLNPGM("OCD finalized");
>>>>>>> mcu_ctrl
            }
          }
        } break;

        case 1: {
<<<<<<< HEAD
          if (status_composite & STATUS_OCD) {
            // phase 1 with OCD warning - increment if can
            if (ocd_th_val >= 15) {
              ocd_th_val = 15;           // limit to max
              test_phase = 2;            // at highest value so go to next phase
              DEBUG_ECHOLNPGM("LOGIC E1A - OCD at max - go to 2");
            }
            else {
              ocd_th_val++;              // try a higher value
              DEBUG_ECHOLNPGM("LOGIC E1B - inc OCD");
=======
          if (status_composite & sh.STATUS_AXIS_OCD) {
            // phase 1 with OCD warning - increment if can
            if (OCD_TH_val >= sh.AXIS_OCD_TH_MAX) {
              OCD_TH_val = sh.AXIS_OCD_TH_MAX;           // limit to max
              test_phase = 2;            // at highest value so go to next phase
              //DEBUG_ECHOLNPGM("LOGIC E1A - OCD at max - go to 2");
              DEBUG_ECHOLNPGM("OCD finalized");
            }
            else {
              OCD_TH_val++;              // try a higher value
              //DEBUG_ECHOLNPGM("LOGIC E1B - inc OCD");
              DEBUG_ECHOLNPGM("inc OCD");
>>>>>>> mcu_ctrl
            }
          }
          else { // phase 1 without OCD warning - normal exit to phase 2
            test_phase = 2;
<<<<<<< HEAD
            DEBUG_ECHOLNPGM("LOGIC E1C - no OCD warning - go to 1");
=======
            //DEBUG_ECHOLNPGM("LOGIC E1C - no OCD warning - go to 1");
            DEBUG_ECHOLNPGM("OCD finalized");
>>>>>>> mcu_ctrl
          }
        } break;

        case 2: {
<<<<<<< HEAD
          if (status_composite & (STATUS_STEP_LOSS_A | STATUS_STEP_LOSS_B)) {
            // phase 2 with stall warning - time to go to next phase
            if (stall_th_val >= 127) {
              stall_th_val = 127;  // limit to max
              DEBUG_ECHOLNPGM("LOGIC E2A - STALL warning, STALL at max, quit");
=======
          if (sh.STATUS_AXIS_LAYOUT == L6474_STATUS_LAYOUT) {  // skip all STALL_TH steps if L6474
            test_phase = 4;
            break;
          }
          if (status_composite & (sh.STATUS_AXIS_STEP_LOSS_A | sh.STATUS_AXIS_STEP_LOSS_B)) {
            // phase 2 with stall warning - time to go to next phase
            if (STALL_TH_val >= 127) {
              STALL_TH_val = 127;  // limit to max
              //DEBUG_ECHOLNPGM("LOGIC E2A - STALL warning, STALL at max, quit");
>>>>>>> mcu_ctrl
              DEBUG_ECHOLNPGM("finished - STALL at maximum value but still have stall warning");
              test_phase = 4;
            }
            else {
              test_phase = 3;              // normal exit to next phase (found failing value of STALL)
<<<<<<< HEAD
              stall_th_val++;              // setup for first pass of phase 3
              DEBUG_ECHOLNPGM("LOGIC E2B - INC - STALL warning, inc Stall, go to 3");
            }
          }
          else {  // phase 2 without stall warning - decrement if can
            if (stall_th_val) {
              stall_th_val--;              // try a lower value
              DEBUG_ECHOLNPGM("LOGIC E2C - no STALL, dec STALL");
=======
              STALL_TH_val++;              // setup for first pass of phase 3
              //DEBUG_ECHOLNPGM("LOGIC E2B - INC - STALL warning, inc Stall, go to 3");
              DEBUG_ECHOLNPGM("inc Stall");
            }
          }
          else {  // phase 2 without stall warning - decrement if can
            if (STALL_TH_val) {
              STALL_TH_val--;              // try a lower value
              //DEBUG_ECHOLNPGM("LOGIC E2C - no STALL, dec STALL");
              DEBUG_ECHOLNPGM("dec STALL");
>>>>>>> mcu_ctrl
            }
            else {
              DEBUG_ECHOLNPGM("finished - STALL at lowest value but still do NOT have stall warning");
              test_phase = 4;
<<<<<<< HEAD
              DEBUG_ECHOLNPGM("LOGIC E2D - no STALL, at lowest so quit");
=======
              //DEBUG_ECHOLNPGM("LOGIC E2D - no STALL, at lowest so quit");
>>>>>>> mcu_ctrl
            }
          }
        } break;

        case 3: {
<<<<<<< HEAD
          if (status_composite & (STATUS_STEP_LOSS_A | STATUS_STEP_LOSS_B)) {
            // phase 3 with stall warning - increment if can
            if (stall_th_val >= 127) {
              stall_th_val = 127; // limit to max
              DEBUG_ECHOLNPGM("finished - STALL at maximum value but still have stall warning");
              test_phase = 4;
              DEBUG_ECHOLNPGM("LOGIC E3A - STALL, at max so quit");
            }
            else {
              stall_th_val++;              // still looking for passing value
              DEBUG_ECHOLNPGM("LOGIC E3B - STALL, inc stall");
=======
          if (sh.STATUS_AXIS_LAYOUT == L6474_STATUS_LAYOUT) {  // skip all STALL_TH steps if L6474
            test_phase = 4;
            break;
          }
          if (status_composite & (sh.STATUS_AXIS_STEP_LOSS_A | sh.STATUS_AXIS_STEP_LOSS_B)) {
            // phase 3 with stall warning - increment if can
            if (STALL_TH_val >= 127) {
              STALL_TH_val = 127; // limit to max
              DEBUG_ECHOLNPGM("finished - STALL at maximum value but still have stall warning");
              test_phase = 4;
              //DEBUG_ECHOLNPGM("LOGIC E3A - STALL, at max so quit");
            }
            else {
              STALL_TH_val++;              // still looking for passing value
              //DEBUG_ECHOLNPGM("LOGIC E3B - STALL, inc stall");
              DEBUG_ECHOLNPGM("inc stall");
>>>>>>> mcu_ctrl
            }
          }
          else {  //phase 3 without stall warning  but have OCD warning
            DEBUG_ECHOLNPGM("Hardware problem - OCD warning without STALL warning");
            test_phase = 4;
<<<<<<< HEAD
            DEBUG_ECHOLNPGM("LOGIC E3C - not STALLED, hardware problem (quit)");
=======
            //DEBUG_ECHOLNPGM("LOGIC E3C - not STALLED, hardware problem (quit)");
>>>>>>> mcu_ctrl
          }
        } break;

      }

    }
    else {
      switch (test_phase) {
        case 0: { // phase 0 without OCD warning - keep on decrementing if can
<<<<<<< HEAD
          if (ocd_th_val) {
            ocd_th_val--;             // try lower value
            DEBUG_ECHOLNPGM("LOGIC N0A - DEC OCD");
          }
          else {
            test_phase = 2;           // at lowest value without warning so skip phase 1
            DEBUG_ECHOLNPGM("LOGIC N0B - OCD at lowest (go to phase 2)");
          }
        } break;

        case 1: DEBUG_ECHOLNPGM("LOGIC N1 (go directly to 2)"); // phase 1 without OCD warning - drop directly to phase 2

        case 2: { // phase 2 without stall warning - keep on decrementing if can
          if (stall_th_val) {
            stall_th_val--;              // try a lower value (stay in phase 2)
            DEBUG_ECHOLNPGM("LOGIC N2B - dec STALL");
=======
          if (OCD_TH_val) {
            OCD_TH_val--;             // try lower value
            //DEBUG_ECHOLNPGM("LOGIC N0A - DEC OCD");
            DEBUG_ECHOLNPGM("DEC OCD");
          }
          else {
            test_phase = 2;           // at lowest value without warning so skip phase 1
            //DEBUG_ECHOLNPGM("LOGIC N0B - OCD at lowest (go to phase 2)");
            DEBUG_ECHOLNPGM("OCD finalized");
          }
        } break;

        case 1: //DEBUG_ECHOLNPGM("LOGIC N1 (go directly to 2)"); // phase 1 without OCD warning - drop directly to phase 2
                DEBUG_ECHOLNPGM("OCD finalized");

        case 2: { // phase 2 without stall warning - keep on decrementing if can
          if (sh.STATUS_AXIS_LAYOUT == L6474_STATUS_LAYOUT) {  // skip all STALL_TH steps if L6474
            test_phase = 4;
            break;
          }
          if (STALL_TH_val) {
            STALL_TH_val--;              // try a lower value (stay in phase 2)
            //DEBUG_ECHOLNPGM("LOGIC N2B - dec STALL");
            DEBUG_ECHOLNPGM("dec STALL");
>>>>>>> mcu_ctrl
          }
          else {
            DEBUG_ECHOLNPGM("finished - STALL at lowest value but still no stall warning");
            test_phase = 4;
<<<<<<< HEAD
            DEBUG_ECHOLNPGM("LOGIC N2C - STALL at lowest (quit)");
          }
        } break;

        case 3: { test_phase = 4;
           DEBUG_ECHOLNPGM("LOGIC N3 - finished!");
=======
            //DEBUG_ECHOLNPGM("LOGIC N2C - STALL at lowest (quit)");
          }
        } break;

        case 3: {
          if (sh.STATUS_AXIS_LAYOUT == L6474_STATUS_LAYOUT) {  // skip all STALL_TH steps if L6474
            test_phase = 4;
            break;
          }
          test_phase = 4;
           //DEBUG_ECHOLNPGM("LOGIC N3 - finished!");
           DEBUG_ECHOLNPGM("finished!");
>>>>>>> mcu_ctrl
        } break;  // phase 3 without any warnings - desired exit
      }  //
    }  // end of status checks

    if (test_phase != 4) {
      for (j = 0; j < driver_count; j++) {                       // update threshold(s)
<<<<<<< HEAD
        L6470.set_param(axis_index[j], L6470_OCD_TH, ocd_th_val);
        L6470.set_param(axis_index[j], L6470_STALL_TH, stall_th_val);
        if (L6470.get_param(axis_index[j], L6470_OCD_TH) != ocd_th_val) DEBUG_ECHOLNPGM("OCD mismatch");
        if (L6470.get_param(axis_index[j], L6470_STALL_TH) != stall_th_val) DEBUG_ECHOLNPGM("STALL mismatch");
=======
        L64xxManager.set_param(axis_index[j], L6470_OCD_TH, OCD_TH_val);
        if (sh.STATUS_AXIS_LAYOUT != L6474_STATUS_LAYOUT) L64xxManager.set_param(axis_index[j], L6470_STALL_TH, STALL_TH_val);
        if (L64xxManager.get_param(axis_index[j], L6470_OCD_TH) != OCD_TH_val) DEBUG_ECHOLNPGM("OCD mismatch");
        if ((L64xxManager.get_param(axis_index[j], L6470_STALL_TH) != STALL_TH_val) && (sh.STATUS_AXIS_LAYOUT != L6474_STATUS_LAYOUT)) DEBUG_ECHOLNPGM("STALL mismatch");
>>>>>>> mcu_ctrl
      }
    }

  } while (test_phase != 4);

<<<<<<< HEAD
  if (status_composite) {
    DEBUG_ECHOLNPGM("Completed with errors");
    for (j = 0; j < driver_count; j++) {
      DEBUG_ECHOPGM("...");
      L6470.error_status_decode(axis_status[j], axis_index[j]);
    }
  }
  else
    DEBUG_ECHOLNPGM("Completed with no errors");

} // M917

/**
 *
=======
  DEBUG_ECHOLNPGM(".");
  if (status_composite) {
    #if ENABLED(L6470_CHITCHAT)
      for (j = 0; j < driver_count; j++) {
        if (j) DEBUG_ECHOPGM("...");
        L64xxManager.error_status_decode(axis_status[j], axis_index[j],
          sh.STATUS_AXIS_TH_SD, sh.STATUS_AXIS_TH_WRN,
          sh.STATUS_AXIS_STEP_LOSS_A, sh.STATUS_AXIS_STEP_LOSS_B,
          sh.STATUS_AXIS_OCD, sh.STATUS_AXIS_LAYOUT);
      }
      DEBUG_ECHOLNPGM(".");
    #endif
    DEBUG_ECHOLNPGM("Completed with errors");
  }
  else
    DEBUG_ECHOLNPGM("Completed with no errors");
  DEBUG_ECHOLNPGM(".");

  L64xxManager.pause_monitor(false);
}

/**
>>>>>>> mcu_ctrl
 * M918: increase speed until error or max feedrate achieved (as shown in configuration.h))
 *
 * J - select which driver(s) to monitor on multi-driver axis
 *     0 - (default) monitor all drivers on the axis or E0
 *     1 - monitor only X, Y, Z, E1
 *     2 - monitor only X2, Y2, Z2, E2
 * Xxxx, Yxxx, Zxxx, Exxx - axis to be monitored with displacement
 *     xxx (1-255) is distance moved on either side of current position
 *
 * I - over current threshold
 *     optional - will report current value from driver if not specified
 *
<<<<<<< HEAD
 * K - value for KVAL_HOLD (0 - 255) (optional)
 *     optional - will report current value from driver if not specified
 *
=======
 * T - current (mA) setting for TVAL (0 - 4A in 31.25mA increments, rounds down) - L6474 only
 *     optional - will report current value from driver if not specified
 *
 * K - value for KVAL_HOLD (0 - 255) (ignored for L6474)
 *     optional - will report current value from driver if not specified
 *
 * M - value for microsteps (1 - 128) (optional)
 *     optional - will report current value from driver if not specified
>>>>>>> mcu_ctrl
 */
void GcodeSuite::M918() {

  DEBUG_ECHOLNPGM("M918");

<<<<<<< HEAD
  char axis_mon[3][3] = { "  ", "  ", "  " };  // List of axes to monitor
  uint8_t axis_index[3];
  uint16_t axis_status[3];
  uint8_t driver_count = 1;
  float position_max, position_min;
  feedRate_t final_fr_mm_m;
  uint8_t kval_hold;
  uint8_t ocd_th_val = 0;
  uint8_t stall_th_val = 0;
  uint16_t over_current_threshold;
  constexpr bool over_current_flag = true;

  uint8_t j;   // general purpose counter

  if (L6470.get_user_input(driver_count, axis_index, axis_mon, position_max, position_min, final_fr_mm_m, kval_hold, over_current_flag, ocd_th_val, stall_th_val, over_current_threshold))
    return;  // quit if invalid user input

  uint8_t m_steps = parser.byteval('M');
  LIMIT(m_steps, 0, 128);
  DEBUG_ECHOLNPAIR("M = ", m_steps);

  int8_t m_bits = -1;
       if (m_steps > 85) m_bits = 7;  // 128 (no synch output)
  else if (m_steps > 42) m_bits = 6;  //  64 (no synch output)
  else if (m_steps > 22) m_bits = 5;  //  32 (no synch output)
  else if (m_steps > 12) m_bits = 4;  //  16 (no synch output)
  else if (m_steps >  5) m_bits = 3;  //   8 (no synch output)
  else if (m_steps >  2) m_bits = 2;  //   4 (no synch output)
  else if (m_steps == 2) m_bits = 1;  //   2 (no synch output)
  else if (m_steps == 1) m_bits = 0;  //   1 (no synch output)
  else if (m_steps == 0) m_bits = 7;  // 128 (no synch output)

  if (m_bits >= 0) {
    const int micros = _BV(m_bits);
    if (micros < 100) { DEBUG_CHAR(' '); if (micros < 10) DEBUG_CHAR(' '); }
    DEBUG_ECHO(micros);
    DEBUG_ECHOPGM(" uSTEPS");
  }

  for (j = 0; j < driver_count; j++)
    L6470.set_param(axis_index[j], L6470_STEP_MODE, m_bits);   // set microsteps

  DEBUG_ECHOLNPAIR("target (maximum) feedrate = ", final_fr_mm_m);

  planner.synchronize();                  // Wait for moves to finish

  for (j = 0; j < driver_count; j++)
    L6470.get_status(axis_index[j]);      // Clear all error flags

  uint16_t status_composite = 0;
  DEBUG_ECHOLNPGM(".\n.\n.");             // Make the feedrate prints easier to see

  constexpr uint8_t iterations = 10;
  for (uint8_t i = 1; i <= iterations; i++) {
    const feedRate_t fr_mm_m = i * final_fr_mm_m / iterations;
    DEBUG_ECHOLNPAIR("...feedrate = ", fr_mm_m);

    jiggle_axis(axis_mon[0][0], position_min, position_max, fr_mm_m);

    for (j = 0; j < driver_count; j++) {
      axis_status[j] = (~L6470.get_status(axis_index[j])) & 0x0800;    // bits of interest are all active low
      status_composite |= axis_status[j];
    }
    if (status_composite) break;       // quit if any errors flags are raised
  }

  DEBUG_ECHOPGM("Completed with errors");
  if (status_composite) {
    DEBUG_ECHOLNPGM("errors");
    for (j = 0; j < driver_count; j++) {
      DEBUG_ECHOPGM("...");
      L6470.error_status_decode(axis_status[j], axis_index[j]);
    }
=======
  L64xxManager.pause_monitor(true); // Keep monitor_driver() from stealing status

  char axis_mon[3][3] = { {"  "}, {"  "}, {"  "} };   // list of Axes to be monitored
  L64XX_axis_t axis_index[3];
  uint16_t axis_status[3];
  uint8_t driver_count = 1;
  float position_max, position_min;
  float final_feedrate;
  uint8_t kval_hold;
  uint8_t OCD_TH_val = 0;
  uint8_t STALL_TH_val = 0;
  uint16_t over_current_threshold;
  constexpr uint8_t over_current_flag = true;

  const L64XX_Marlin::L64XX_shadow_t &sh = L64xxManager.shadow;

  uint8_t j;   // general purpose counter

  if (L64xxManager.get_user_input(driver_count, axis_index, axis_mon, position_max, position_min, final_feedrate, kval_hold, over_current_flag, OCD_TH_val, STALL_TH_val, over_current_threshold))
    return;  // quit if invalid user input

  L64xxManager.get_status(axis_index[0]); // populate shadow array

  uint8_t m_steps = parser.byteval('M');

  if (m_steps != 0) {
    LIMIT(m_steps, 1, sh.STATUS_AXIS_LAYOUT == L6474_STATUS_LAYOUT ? 16 : 128);  // L6474

    uint8_t stepVal;
    for (stepVal = 0; stepVal < 8; stepVal++) {  // convert to L64xx register value
      if (m_steps == 1) break;
      m_steps >>= 1;
    }

    if (sh.STATUS_AXIS_LAYOUT == L6474_STATUS_LAYOUT)
      stepVal |= 0x98;  // NO SYNC
    else
      stepVal |= (!SYNC_EN) | SYNC_SEL_1 | stepVal;

    for (j = 0; j < driver_count; j++) {
      L64xxManager.set_param(axis_index[j], dSPIN_HARD_HIZ, 0);          // can't write STEP register if stepper being powered
                                                                         //   results in an extra NOOP being sent (data 00)
      L64xxManager.set_param(axis_index[j], L6470_STEP_MODE, stepVal);   // set microsteps
    }
  }
  m_steps = L64xxManager.get_param(axis_index[0], L6470_STEP_MODE) & 0x07;   // get microsteps

  DEBUG_ECHOLNPAIR("Microsteps = ", _BV(m_steps));
  DEBUG_ECHOLNPAIR("target (maximum) feedrate = ", final_feedrate);

  const float feedrate_inc = final_feedrate / 10,   // Start at 1/10 of max & go up by 1/10 per step
              fr_limit = final_feedrate * 0.99f;    // Rounding-safe comparison value
  float current_feedrate = 0;

  planner.synchronize();                            // Wait for moves to complete

  for (j = 0; j < driver_count; j++)
    L64xxManager.get_status(axis_index[j]);         // Clear error flags

  char temp_axis_string[2] = " ";
  temp_axis_string[0] = axis_mon[0][0];             // Need a sprintf format string
  //temp_axis_string[1] = '\n';

  char gcode_string[80];
  uint16_t status_composite = 0;
  DEBUG_ECHOLNPGM(".\n.\n.");                       // Make feedrate outputs easier to read

  do {
    current_feedrate += feedrate_inc;
    DEBUG_ECHOLNPAIR("...feedrate = ", current_feedrate);

    sprintf_P(gcode_string, PSTR("G0 %s%03d F%03d"), temp_axis_string, uint16_t(position_min), uint16_t(current_feedrate));
    gcode.process_subcommands_now_P(gcode_string);

    sprintf_P(gcode_string, PSTR("G0 %s%03d F%03d"), temp_axis_string, uint16_t(position_max), uint16_t(current_feedrate));
    gcode.process_subcommands_now_P(gcode_string);

    planner.synchronize();

    for (j = 0; j < driver_count; j++) {
      axis_status[j] = (~L64xxManager.get_status(axis_index[j])) & 0x0800;  // Bits of interest are all active LOW
      status_composite |= axis_status[j];
    }
    if (status_composite) break;              // Break on any error
  } while (current_feedrate < fr_limit);

  DEBUG_ECHOPGM("Completed with ");
  if (status_composite) {
    DEBUG_ECHOLNPGM("errors");
    #if ENABLED(L6470_CHITCHAT)
      for (j = 0; j < driver_count; j++) {
        if (j) DEBUG_ECHOPGM("...");
        L64xxManager.error_status_decode(axis_status[j], axis_index[j],
          sh.STATUS_AXIS_TH_SD, sh.STATUS_AXIS_TH_WRN,
          sh.STATUS_AXIS_STEP_LOSS_A, sh.STATUS_AXIS_STEP_LOSS_B,
          sh.STATUS_AXIS_OCD, sh.STATUS_AXIS_LAYOUT);
      }
    #endif
>>>>>>> mcu_ctrl
  }
  else
    DEBUG_ECHOLNPGM("no errors");

<<<<<<< HEAD
} // M918

#endif // HAS_DRIVER(L6470)
=======
  L64xxManager.pause_monitor(false);
}

#endif // HAS_L64XX
>>>>>>> mcu_ctrl
