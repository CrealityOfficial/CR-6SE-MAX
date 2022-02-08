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
 * mcp4728.cpp - Arduino library for MicroChip MCP4728 I2C D/A converter
 *
 * For implementation details, please take a look at the datasheet:
<<<<<<< HEAD
 * http://ww1.microchip.com/downloads/en/DeviceDoc/22187a.pdf
 *
 * For discussion and feedback, please go to:
 * http://arduino.cc/forum/index.php/topic,51842.0.html
=======
 * https://ww1.microchip.com/downloads/en/DeviceDoc/22187a.pdf
 *
 * For discussion and feedback, please go to:
 * https://forum.arduino.cc/index.php/topic,51842.0.html
>>>>>>> mcu_ctrl
 */

#include "../../inc/MarlinConfig.h"

<<<<<<< HEAD
#if ENABLED(DAC_STEPPER_CURRENT)

#include "dac_mcp4728.h"

xyze_uint_t mcp4728_values;
=======
#if ENABLED(HAS_MOTOR_CURRENT_DAC)

#include "dac_mcp4728.h"

MCP4728 mcp4728;

xyze_uint_t dac_values;
>>>>>>> mcu_ctrl

/**
 * Begin I2C, get current values (input register and eeprom) of mcp4728
 */
<<<<<<< HEAD
void mcp4728_init() {
  Wire.begin();
  Wire.requestFrom(int(DAC_DEV_ADDRESS), 24);
=======
void MCP4728::init() {
  Wire.begin();
  Wire.requestFrom(I2C_ADDRESS(DAC_DEV_ADDRESS), uint8_t(24));
>>>>>>> mcu_ctrl
  while (Wire.available()) {
    char deviceID = Wire.read(),
         hiByte = Wire.read(),
         loByte = Wire.read();

    if (!(deviceID & 0x08))
<<<<<<< HEAD
      mcp4728_values[(deviceID & 0x30) >> 4] = word((hiByte & 0x0F), loByte);
=======
      dac_values[(deviceID & 0x30) >> 4] = word((hiByte & 0x0F), loByte);
>>>>>>> mcu_ctrl
  }
}

/**
 * Write input resister value to specified channel using fastwrite method.
 * Channel : 0-3, Values : 0-4095
 */
<<<<<<< HEAD
uint8_t mcp4728_analogWrite(const uint8_t channel, const uint16_t value) {
  mcp4728_values[channel] = value;
  return mcp4728_fastWrite();
}

/**
 * Write all input resistor values to EEPROM using SequencialWrite method.
 * This will update both input register and EEPROM value
 * This will also write current Vref, PowerDown, Gain settings to EEPROM
 */
uint8_t mcp4728_eepromWrite() {
  Wire.beginTransmission(I2C_ADDRESS(DAC_DEV_ADDRESS));
  Wire.write(SEQWRITE);
  LOOP_XYZE(i) {
    Wire.write(DAC_STEPPER_VREF << 7 | DAC_STEPPER_GAIN << 4 | highByte(mcp4728_values[i]));
    Wire.write(lowByte(mcp4728_values[i]));
=======
uint8_t MCP4728::analogWrite(const uint8_t channel, const uint16_t value) {
  dac_values[channel] = value;
  return fastWrite();
}

/**
 * Write all input resistor values to EEPROM using SequentialWrite method.
 * This will update both input register and EEPROM value
 * This will also write current Vref, PowerDown, Gain settings to EEPROM
 */
uint8_t MCP4728::eepromWrite() {
  Wire.beginTransmission(I2C_ADDRESS(DAC_DEV_ADDRESS));
  Wire.write(SEQWRITE);
  LOOP_LOGICAL_AXES(i) {
    Wire.write(DAC_STEPPER_VREF << 7 | DAC_STEPPER_GAIN << 4 | highByte(dac_values[i]));
    Wire.write(lowByte(dac_values[i]));
>>>>>>> mcu_ctrl
  }
  return Wire.endTransmission();
}

/**
 * Write Voltage reference setting to all input regiters
 */
<<<<<<< HEAD
uint8_t mcp4728_setVref_all(const uint8_t value) {
=======
uint8_t MCP4728::setVref_all(const uint8_t value) {
>>>>>>> mcu_ctrl
  Wire.beginTransmission(I2C_ADDRESS(DAC_DEV_ADDRESS));
  Wire.write(VREFWRITE | (value ? 0x0F : 0x00));
  return Wire.endTransmission();
}
/**
 * Write Gain setting to all input regiters
 */
<<<<<<< HEAD
uint8_t mcp4728_setGain_all(const uint8_t value) {
=======
uint8_t MCP4728::setGain_all(const uint8_t value) {
>>>>>>> mcu_ctrl
  Wire.beginTransmission(I2C_ADDRESS(DAC_DEV_ADDRESS));
  Wire.write(GAINWRITE | (value ? 0x0F : 0x00));
  return Wire.endTransmission();
}

/**
 * Return Input Register value
 */
<<<<<<< HEAD
uint16_t mcp4728_getValue(const uint8_t channel) { return mcp4728_values[channel]; }
=======
uint16_t MCP4728::getValue(const uint8_t channel) { return dac_values[channel]; }
>>>>>>> mcu_ctrl

#if 0
/**
 * Steph: Might be useful in the future
 * Return Vout
 */
<<<<<<< HEAD
uint16_t mcp4728_getVout(const uint8_t channel) {
  const uint32_t vref = 2048,
                 vOut = (vref * mcp4728_values[channel] * (_DAC_STEPPER_GAIN + 1)) / 4096;
=======
uint16_t MCP4728::getVout(const uint8_t channel) {
  const uint32_t vref = 2048,
                 vOut = (vref * dac_values[channel] * (_DAC_STEPPER_GAIN + 1)) / 4096;
>>>>>>> mcu_ctrl
  return _MIN(vOut, defaultVDD);
}
#endif

/**
 * Returns DAC values as a 0-100 percentage of drive strength
 */
<<<<<<< HEAD
uint8_t mcp4728_getDrvPct(const uint8_t channel) { return uint8_t(100.0 * mcp4728_values[channel] / (DAC_STEPPER_MAX) + 0.5); }
=======
uint8_t MCP4728::getDrvPct(const uint8_t channel) { return uint8_t(100.0 * dac_values[channel] / (DAC_STEPPER_MAX) + 0.5); }
>>>>>>> mcu_ctrl

/**
 * Receives all Drive strengths as 0-100 percent values, updates
 * DAC Values array and calls fastwrite to update the DAC.
 */
<<<<<<< HEAD
void mcp4728_setDrvPct(xyze_uint8_t &pct) {
  mcp4728_values *= 0.01 * pct * (DAC_STEPPER_MAX);
  mcp4728_fastWrite();
=======
void MCP4728::setDrvPct(xyze_uint_t &pct) {
  dac_values = pct * (DAC_STEPPER_MAX) * 0.01f;
  fastWrite();
>>>>>>> mcu_ctrl
}

/**
 * FastWrite input register values - All DAC ouput update. refer to DATASHEET 5.6.1
 * DAC Input and PowerDown bits update.
 * No EEPROM update
 */
<<<<<<< HEAD
uint8_t mcp4728_fastWrite() {
  Wire.beginTransmission(I2C_ADDRESS(DAC_DEV_ADDRESS));
  LOOP_XYZE(i) {
    Wire.write(highByte(mcp4728_values[i]));
    Wire.write(lowByte(mcp4728_values[i]));
=======
uint8_t MCP4728::fastWrite() {
  Wire.beginTransmission(I2C_ADDRESS(DAC_DEV_ADDRESS));
  LOOP_LOGICAL_AXES(i) {
    Wire.write(highByte(dac_values[i]));
    Wire.write(lowByte(dac_values[i]));
>>>>>>> mcu_ctrl
  }
  return Wire.endTransmission();
}

/**
 * Common function for simple general commands
 */
<<<<<<< HEAD
uint8_t mcp4728_simpleCommand(const byte simpleCommand) {
=======
uint8_t MCP4728::simpleCommand(const byte simpleCommand) {
>>>>>>> mcu_ctrl
  Wire.beginTransmission(I2C_ADDRESS(GENERALCALL));
  Wire.write(simpleCommand);
  return Wire.endTransmission();
}

<<<<<<< HEAD
#endif // DAC_STEPPER_CURRENT
=======
#endif // HAS_MOTOR_CURRENT_DAC
>>>>>>> mcu_ctrl
