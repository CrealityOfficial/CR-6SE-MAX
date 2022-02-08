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
 * feature/spindle_laser.cpp
 */

#include "../inc/MarlinConfig.h"

#if HAS_CUTTER

#include "spindle_laser.h"

<<<<<<< HEAD
SpindleLaser cutter;

cutter_power_t SpindleLaser::power; // = 0

#define SPINDLE_LASER_PWM_OFF ((SPINDLE_LASER_PWM_INVERT) ? 255 : 0)

void SpindleLaser::init() {
  OUT_WRITE(SPINDLE_LASER_ENA_PIN, !SPINDLE_LASER_ACTIVE_HIGH); // Init spindle to off
  #if ENABLED(SPINDLE_CHANGE_DIR)
    OUT_WRITE(SPINDLE_DIR_PIN, SPINDLE_INVERT_DIR ? 255 : 0);   // Init rotation to clockwise (M3)
  #endif
  #if ENABLED(SPINDLE_LASER_PWM)
    SET_PWM(SPINDLE_LASER_PWM_PIN);
    analogWrite(pin_t(SPINDLE_LASER_PWM_PIN), SPINDLE_LASER_PWM_OFF);  // set to lowest speed
=======
#if ENABLED(SPINDLE_SERVO)
  #include "../module/servo.h"
#endif

SpindleLaser cutter;
uint8_t SpindleLaser::power;
#if ENABLED(LASER_FEATURE)
  cutter_test_pulse_t SpindleLaser::testPulse = 50;                   // Test fire Pulse time ms value.
#endif
bool SpindleLaser::isReady;                                           // Ready to apply power setting from the UI to OCR
cutter_power_t SpindleLaser::menuPower,                               // Power set via LCD menu in PWM, PERCENT, or RPM
               SpindleLaser::unitPower;                               // LCD status power in PWM, PERCENT, or RPM

#if ENABLED(MARLIN_DEV_MODE)
  cutter_frequency_t SpindleLaser::frequency;                         // PWM frequency setting; range: 2K - 50K
#endif
#define SPINDLE_LASER_PWM_OFF TERN(SPINDLE_LASER_PWM_INVERT, 255, 0)

//
// Init the cutter to a safe OFF state
//
void SpindleLaser::init() {
  #if ENABLED(SPINDLE_SERVO)
    MOVE_SERVO(SPINDLE_SERVO_NR, SPINDLE_SERVO_MIN);
  #else
    OUT_WRITE(SPINDLE_LASER_ENA_PIN, !SPINDLE_LASER_ACTIVE_STATE);    // Init spindle to off
  #endif
  #if ENABLED(SPINDLE_CHANGE_DIR)
    OUT_WRITE(SPINDLE_DIR_PIN, SPINDLE_INVERT_DIR ? 255 : 0);         // Init rotation to clockwise (M3)
  #endif
  #if ENABLED(SPINDLE_LASER_PWM)
    SET_PWM(SPINDLE_LASER_PWM_PIN);
    analogWrite(pin_t(SPINDLE_LASER_PWM_PIN), SPINDLE_LASER_PWM_OFF); // Set to lowest speed
  #endif
  #if ENABLED(HAL_CAN_SET_PWM_FREQ) && defined(SPINDLE_LASER_FREQUENCY)
    set_pwm_frequency(pin_t(SPINDLE_LASER_PWM_PIN), SPINDLE_LASER_FREQUENCY);
    TERN_(MARLIN_DEV_MODE, frequency = SPINDLE_LASER_FREQUENCY);
  #endif
  #if ENABLED(AIR_EVACUATION)
    OUT_WRITE(AIR_EVACUATION_PIN, !AIR_EVACUATION_ACTIVE);            // Init Vacuum/Blower OFF
  #endif
  #if ENABLED(AIR_ASSIST)
    OUT_WRITE(AIR_ASSIST_PIN, !AIR_ASSIST_ACTIVE);                    // Init Air Assist OFF
>>>>>>> mcu_ctrl
  #endif
}

#if ENABLED(SPINDLE_LASER_PWM)
<<<<<<< HEAD

  /**
   * ocr_val_mode() is used for debugging and to get the points needed to compute the RPM vs ocr_val line
   *
   * it accepts inputs of 0-255
   */
  void SpindleLaser::set_ocr(const uint8_t ocr) {
    WRITE(SPINDLE_LASER_ENA_PIN, SPINDLE_LASER_ACTIVE_HIGH); // turn spindle on (active low)
    analogWrite(pin_t(SPINDLE_LASER_PWM_PIN), ocr ^ SPINDLE_LASER_PWM_OFF);
  }

#endif

void SpindleLaser::apply_power(const cutter_power_t inpow) {
  static cutter_power_t last_power_applied = 0;
  if (inpow == last_power_applied) return;
  last_power_applied = inpow;
  #if ENABLED(SPINDLE_LASER_PWM)
    if (enabled()) {
      #define _scaled(F) ((F - (SPEED_POWER_INTERCEPT)) * inv_slope)
      constexpr float inv_slope = RECIPROCAL(SPEED_POWER_SLOPE),
                      min_ocr = _scaled(SPEED_POWER_MIN),
                      max_ocr = _scaled(SPEED_POWER_MAX);
      int16_t ocr_val;
           if (inpow <= SPEED_POWER_MIN) ocr_val = min_ocr;       // Use minimum if set below
      else if (inpow >= SPEED_POWER_MAX) ocr_val = max_ocr;       // Use maximum if set above
      else ocr_val = _scaled(inpow);                              // Use calculated OCR value
      set_ocr(ocr_val & 0xFF);                                    // ...limited to Atmel PWM max
    }
    else {
      WRITE(SPINDLE_LASER_ENA_PIN, !SPINDLE_LASER_ACTIVE_HIGH);   // Turn spindle off (active low)
      analogWrite(pin_t(SPINDLE_LASER_PWM_PIN), SPINDLE_LASER_PWM_OFF);  // Only write low byte
    }
  #else
    WRITE(SPINDLE_LASER_ENA_PIN, (SPINDLE_LASER_ACTIVE_HIGH) ? enabled() : !enabled());
=======
  /**
   * Set the cutter PWM directly to the given ocr value
   */
  void SpindleLaser::_set_ocr(const uint8_t ocr) {
    #if NEEDS_HARDWARE_PWM && SPINDLE_LASER_FREQUENCY
      set_pwm_frequency(pin_t(SPINDLE_LASER_PWM_PIN), TERN(MARLIN_DEV_MODE, frequency, SPINDLE_LASER_FREQUENCY));
      set_pwm_duty(pin_t(SPINDLE_LASER_PWM_PIN), ocr ^ SPINDLE_LASER_PWM_OFF);
    #else
      analogWrite(pin_t(SPINDLE_LASER_PWM_PIN), ocr ^ SPINDLE_LASER_PWM_OFF);
    #endif
  }

  void SpindleLaser::set_ocr(const uint8_t ocr) {
    WRITE(SPINDLE_LASER_ENA_PIN,  SPINDLE_LASER_ACTIVE_STATE); // Cutter ON
    _set_ocr(ocr);
  }

  void SpindleLaser::ocr_off() {
    WRITE(SPINDLE_LASER_ENA_PIN, !SPINDLE_LASER_ACTIVE_STATE); // Cutter OFF
    _set_ocr(0);
  }
#endif

//
// Set cutter ON/OFF state (and PWM) to the given cutter power value
//
void SpindleLaser::apply_power(const uint8_t opwr) {
  static uint8_t last_power_applied = 0;
  if (opwr == last_power_applied) return;
  last_power_applied = opwr;
  power = opwr;
  #if ENABLED(SPINDLE_LASER_PWM)
    if (cutter.unitPower == 0 && CUTTER_UNIT_IS(RPM)) {
      ocr_off();
      isReady = false;
    }
    else if (ENABLED(CUTTER_POWER_RELATIVE) || enabled()) {
      set_ocr(power);
      isReady = true;
    }
    else {
      ocr_off();
      isReady = false;
    }
  #elif ENABLED(SPINDLE_SERVO)
    MOVE_SERVO(SPINDLE_SERVO_NR, power);
  #else
    WRITE(SPINDLE_LASER_ENA_PIN, enabled() ? SPINDLE_LASER_ACTIVE_STATE : !SPINDLE_LASER_ACTIVE_STATE);
    isReady = true;
>>>>>>> mcu_ctrl
  #endif
}

#if ENABLED(SPINDLE_CHANGE_DIR)
<<<<<<< HEAD

  void SpindleLaser::set_direction(const bool reverse) {
    const bool dir_state = (reverse == SPINDLE_INVERT_DIR); // Forward (M3) HIGH when not inverted
    #if ENABLED(SPINDLE_STOP_ON_DIR_CHANGE)
      if (enabled() && READ(SPINDLE_DIR_PIN) != dir_state) disable();
    #endif
    WRITE(SPINDLE_DIR_PIN, dir_state);
  }

#endif

=======
  //
  // Set the spindle direction and apply immediately
  // Stop on direction change if SPINDLE_STOP_ON_DIR_CHANGE is enabled
  //
  void SpindleLaser::set_reverse(const bool reverse) {
    const bool dir_state = (reverse == SPINDLE_INVERT_DIR); // Forward (M3) HIGH when not inverted
    if (TERN0(SPINDLE_STOP_ON_DIR_CHANGE, enabled()) && READ(SPINDLE_DIR_PIN) != dir_state) disable();
    WRITE(SPINDLE_DIR_PIN, dir_state);
  }
#endif

#if ENABLED(AIR_EVACUATION)

  // Enable / disable Cutter Vacuum or Laser Blower motor
  void SpindleLaser::air_evac_enable()  { WRITE(AIR_EVACUATION_PIN,  AIR_EVACUATION_ACTIVE); } // Turn ON

  void SpindleLaser::air_evac_disable() { WRITE(AIR_EVACUATION_PIN, !AIR_EVACUATION_ACTIVE); } // Turn OFF

  void SpindleLaser::air_evac_toggle()  { TOGGLE(AIR_EVACUATION_PIN); } // Toggle state

#endif // AIR_EVACUATION

#if ENABLED(AIR_ASSIST)

  // Enable / disable air assist
  void SpindleLaser::air_assist_enable()  { WRITE(AIR_ASSIST_PIN,  AIR_ASSIST_PIN); } // Turn ON

  void SpindleLaser::air_assist_disable() { WRITE(AIR_ASSIST_PIN, !AIR_ASSIST_PIN); } // Turn OFF

  void SpindleLaser::air_assist_toggle()  { TOGGLE(AIR_ASSIST_PIN); } // Toggle state

#endif // AIR_ASSIST

>>>>>>> mcu_ctrl
#endif // HAS_CUTTER
