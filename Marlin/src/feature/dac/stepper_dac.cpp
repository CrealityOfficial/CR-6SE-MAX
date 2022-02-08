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
 * stepper_dac.cpp - To set stepper current via DAC
 */

#include "../../inc/MarlinConfig.h"

<<<<<<< HEAD
#if ENABLED(DAC_STEPPER_CURRENT)

#include "stepper_dac.h"

bool dac_present = false;
constexpr xyze_uint8_t dac_order = DAC_STEPPER_ORDER;
xyze_uint8_t dac_channel_pct = DAC_MOTOR_CURRENT_DEFAULT;

int dac_init() {
=======
#if ENABLED(HAS_MOTOR_CURRENT_DAC)

#include "stepper_dac.h"
#include "../../MarlinCore.h" // for SP_X_LBL...

bool dac_present = false;
constexpr xyze_uint8_t dac_order = DAC_STEPPER_ORDER;
xyze_uint_t dac_channel_pct = DAC_MOTOR_CURRENT_DEFAULT;

StepperDAC stepper_dac;

int StepperDAC::init() {
>>>>>>> mcu_ctrl
  #if PIN_EXISTS(DAC_DISABLE)
    OUT_WRITE(DAC_DISABLE_PIN, LOW);  // set pin low to enable DAC
  #endif

<<<<<<< HEAD
  mcp4728_init();

  if (mcp4728_simpleCommand(RESET)) return -1;

  dac_present = true;

  mcp4728_setVref_all(DAC_STEPPER_VREF);
  mcp4728_setGain_all(DAC_STEPPER_GAIN);

  if (mcp4728_getDrvPct(0) < 1 || mcp4728_getDrvPct(1) < 1 || mcp4728_getDrvPct(2) < 1 || mcp4728_getDrvPct(3) < 1 ) {
    mcp4728_setDrvPct(dac_channel_pct);
    mcp4728_eepromWrite();
=======
  mcp4728.init();

  if (mcp4728.simpleCommand(RESET)) return -1;

  dac_present = true;

  mcp4728.setVref_all(DAC_STEPPER_VREF);
  mcp4728.setGain_all(DAC_STEPPER_GAIN);

  if (mcp4728.getDrvPct(0) < 1 || mcp4728.getDrvPct(1) < 1 || mcp4728.getDrvPct(2) < 1 || mcp4728.getDrvPct(3) < 1) {
    mcp4728.setDrvPct(dac_channel_pct);
    mcp4728.eepromWrite();
>>>>>>> mcu_ctrl
  }

  return 0;
}

<<<<<<< HEAD
void dac_current_percent(uint8_t channel, float val) {
  if (!dac_present) return;

  NOMORE(val, 100);

  mcp4728_analogWrite(dac_order[channel], val * 0.01 * (DAC_STEPPER_MAX));
  mcp4728_simpleCommand(UPDATE);
}

void dac_current_raw(uint8_t channel, uint16_t val) {
  if (!dac_present) return;

  NOMORE(val, DAC_STEPPER_MAX);

  mcp4728_analogWrite(dac_order[channel], val);
  mcp4728_simpleCommand(UPDATE);
}

static float dac_perc(int8_t n) { return 100.0 * mcp4728_getValue(dac_order[n]) * RECIPROCAL(DAC_STEPPER_MAX); }
static float dac_amps(int8_t n) { return mcp4728_getDrvPct(dac_order[n]) * (DAC_STEPPER_MAX) * 0.125 * RECIPROCAL(DAC_STEPPER_SENSE); }

uint8_t dac_current_get_percent(const AxisEnum axis) { return mcp4728_getDrvPct(dac_order[axis]); }
void dac_current_set_percents(xyze_uint8_t &pct) {
  LOOP_XYZE(i) dac_channel_pct[i] = pct[dac_order[i]];
  mcp4728_setDrvPct(dac_channel_pct);
}

void dac_print_values() {
  if (!dac_present) return;

  SERIAL_ECHO_MSG("Stepper current values in % (Amps):");
  SERIAL_ECHO_START();
  SERIAL_ECHOLNPAIR(
    " X:", dac_perc(X_AXIS), " (", dac_amps(X_AXIS), ")"
    " Y:", dac_perc(Y_AXIS), " (", dac_amps(Y_AXIS), ")"
    " Z:", dac_perc(Z_AXIS), " (", dac_amps(Z_AXIS), ")"
    " E:", dac_perc(E_AXIS), " (", dac_amps(E_AXIS), ")"
  );
}

void dac_commit_eeprom() {
  if (!dac_present) return;
  mcp4728_eepromWrite();
}

#endif // DAC_STEPPER_CURRENT
=======
void StepperDAC::set_current_value(const uint8_t channel, uint16_t val) {
  if (!dac_present) return;

  NOMORE(val, uint16_t(DAC_STEPPER_MAX));

  mcp4728.analogWrite(dac_order[channel], val);
  mcp4728.simpleCommand(UPDATE);
}

void StepperDAC::set_current_percent(const uint8_t channel, float val) {
  set_current_value(channel, _MIN(val, 100.0f) * (DAC_STEPPER_MAX) / 100.0f);
}

static float dac_perc(int8_t n) { return mcp4728.getDrvPct(dac_order[n]); }
static float dac_amps(int8_t n) { return mcp4728.getValue(dac_order[n]) * 0.125 * RECIPROCAL(DAC_STEPPER_SENSE * 1000); }

uint8_t StepperDAC::get_current_percent(const AxisEnum axis) { return mcp4728.getDrvPct(dac_order[axis]); }
void StepperDAC::set_current_percents(xyze_uint8_t &pct) {
  LOOP_LOGICAL_AXES(i) dac_channel_pct[i] = pct[dac_order[i]];
  mcp4728.setDrvPct(dac_channel_pct);
}

void StepperDAC::print_values() {
  if (!dac_present) return;
  SERIAL_ECHO_MSG("Stepper current values in % (Amps):");
  SERIAL_ECHO_START();
  SERIAL_ECHOPAIR_P(  SP_X_LBL, dac_perc(X_AXIS), PSTR(" ("), dac_amps(X_AXIS), PSTR(")"));
  SERIAL_ECHOPAIR_P(  SP_Y_LBL, dac_perc(Y_AXIS), PSTR(" ("), dac_amps(Y_AXIS), PSTR(")"));
  SERIAL_ECHOPAIR_P(  SP_Z_LBL, dac_perc(Z_AXIS), PSTR(" ("), dac_amps(Z_AXIS), PSTR(")"));
  SERIAL_ECHOLNPAIR_P(SP_E_LBL, dac_perc(E_AXIS), PSTR(" ("), dac_amps(E_AXIS), PSTR(")"));
}

void StepperDAC::commit_eeprom() {
  if (!dac_present) return;
  mcp4728.eepromWrite();
}

#endif // HAS_MOTOR_CURRENT_DAC
>>>>>>> mcu_ctrl
