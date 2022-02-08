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

<<<<<<< HEAD
#if HAS_DIGIPOTSS || HAS_MOTOR_CURRENT_PWM || EITHER(DIGIPOT_I2C, DAC_STEPPER_CURRENT)

#include "../../gcode.h"

#if HAS_DIGIPOTSS || HAS_MOTOR_CURRENT_PWM
  #include "../../../module/stepper.h"
#endif

#if ENABLED(DIGIPOT_I2C)
  #include "../../../feature/digipot/digipot.h"
#endif

#if ENABLED(DAC_STEPPER_CURRENT)
=======
#if ANY(HAS_MOTOR_CURRENT_SPI, HAS_MOTOR_CURRENT_PWM, HAS_MOTOR_CURRENT_I2C, HAS_MOTOR_CURRENT_DAC)

#include "../../gcode.h"

#if HAS_MOTOR_CURRENT_SPI || HAS_MOTOR_CURRENT_PWM
  #include "../../../module/stepper.h"
#endif

#if HAS_MOTOR_CURRENT_I2C
  #include "../../../feature/digipot/digipot.h"
#endif

#if ENABLED(HAS_MOTOR_CURRENT_DAC)
>>>>>>> mcu_ctrl
  #include "../../../feature/dac/stepper_dac.h"
#endif

/**
 * M907: Set digital trimpot motor current using axis codes X, Y, Z, E, B, S
 */
void GcodeSuite::M907() {
<<<<<<< HEAD
  #if HAS_DIGIPOTSS

    LOOP_XYZE(i) if (parser.seenval(axis_codes[i])) stepper.digipot_current(i, parser.value_int());
    if (parser.seenval('B')) stepper.digipot_current(4, parser.value_int());
    if (parser.seenval('S')) for (uint8_t i = 0; i <= 4; i++) stepper.digipot_current(i, parser.value_int());
=======
  #if HAS_MOTOR_CURRENT_SPI

    LOOP_LOGICAL_AXES(i) if (parser.seenval(axis_codes[i])) stepper.set_digipot_current(i, parser.value_int());
    if (parser.seenval('B')) stepper.set_digipot_current(4, parser.value_int());
    if (parser.seenval('S')) LOOP_LE_N(i, 4) stepper.set_digipot_current(i, parser.value_int());
>>>>>>> mcu_ctrl

  #elif HAS_MOTOR_CURRENT_PWM

    #if ANY_PIN(MOTOR_CURRENT_PWM_X, MOTOR_CURRENT_PWM_Y, MOTOR_CURRENT_PWM_XY)
<<<<<<< HEAD
      if (parser.seenval('X') || parser.seenval('Y')) stepper.digipot_current(0, parser.value_int());
    #endif
    #if PIN_EXISTS(MOTOR_CURRENT_PWM_Z)
      if (parser.seenval('Z')) stepper.digipot_current(1, parser.value_int());
    #endif
    #if PIN_EXISTS(MOTOR_CURRENT_PWM_E)
      if (parser.seenval('E')) stepper.digipot_current(2, parser.value_int());
=======
      if (parser.seenval('X') || parser.seenval('Y')) stepper.set_digipot_current(0, parser.value_int());
    #endif
    #if PIN_EXISTS(MOTOR_CURRENT_PWM_Z)
      if (parser.seenval('Z')) stepper.set_digipot_current(1, parser.value_int());
    #endif
    #if PIN_EXISTS(MOTOR_CURRENT_PWM_E)
      if (parser.seenval('E')) stepper.set_digipot_current(2, parser.value_int());
>>>>>>> mcu_ctrl
    #endif

  #endif

<<<<<<< HEAD
  #if ENABLED(DIGIPOT_I2C)
    // this one uses actual amps in floating point
    LOOP_XYZE(i) if (parser.seenval(axis_codes[i])) digipot_i2c_set_current(i, parser.value_float());
    // Additional extruders use B,C,D for channels 4,5,6.
    // TODO: Change these parameters because 'E' is used. B<index>?
    for (uint8_t i = E_AXIS + 1; i < DIGIPOT_I2C_NUM_CHANNELS; i++)
      if (parser.seenval('B' + i - (E_AXIS + 1))) digipot_i2c_set_current(i, parser.value_float());
  #endif

  #if ENABLED(DAC_STEPPER_CURRENT)
    if (parser.seenval('S')) {
      const float dac_percent = parser.value_float();
      for (uint8_t i = 0; i <= 4; i++) dac_current_percent(i, dac_percent);
    }
    LOOP_XYZE(i) if (parser.seenval(axis_codes[i])) dac_current_percent(i, parser.value_float());
  #endif
}

#if HAS_DIGIPOTSS || ENABLED(DAC_STEPPER_CURRENT)
=======
  #if HAS_MOTOR_CURRENT_I2C
    // this one uses actual amps in floating point
    LOOP_LOGICAL_AXES(i) if (parser.seenval(axis_codes[i])) digipot_i2c.set_current(i, parser.value_float());
    // Additional extruders use B,C,D for channels 4,5,6.
    // TODO: Change these parameters because 'E' is used. B<index>?
    for (uint8_t i = E_AXIS + 1; i < DIGIPOT_I2C_NUM_CHANNELS; i++)
      if (parser.seenval('B' + i - (E_AXIS + 1))) digipot_i2c.set_current(i, parser.value_float());
  #endif

  #if ENABLED(HAS_MOTOR_CURRENT_DAC)
    if (parser.seenval('S')) {
      const float dac_percent = parser.value_float();
      LOOP_LE_N(i, 4) stepper_dac.set_current_percent(i, dac_percent);
    }
    LOOP_LOGICAL_AXES(i) if (parser.seenval(axis_codes[i])) stepper_dac.set_current_percent(i, parser.value_float());
  #endif
}

#if EITHER(HAS_MOTOR_CURRENT_SPI, HAS_MOTOR_CURRENT_DAC)
>>>>>>> mcu_ctrl

  /**
   * M908: Control digital trimpot directly (M908 P<pin> S<current>)
   */
  void GcodeSuite::M908() {
<<<<<<< HEAD
    #if HAS_DIGIPOTSS
      stepper.digitalPotWrite(parser.intval('P'), parser.intval('S'));
    #endif
    #if ENABLED(DAC_STEPPER_CURRENT)
      dac_current_raw(parser.byteval('P', -1), parser.ushortval('S', 0));
    #endif
  }

#endif // HAS_DIGIPOTSS || DAC_STEPPER_CURRENT

#if ENABLED(DAC_STEPPER_CURRENT)

  void GcodeSuite::M909() { dac_print_values(); }
  void GcodeSuite::M910() { dac_commit_eeprom(); }

#endif // DAC_STEPPER_CURRENT

#endif // HAS_DIGIPOTSS || DAC_STEPPER_CURRENT || HAS_MOTOR_CURRENT_PWM || DIGIPOT_I2C
=======
    TERN_(HAS_MOTOR_CURRENT_SPI, stepper.set_digipot_value_spi(parser.intval('P'), parser.intval('S')));
    TERN_(HAS_MOTOR_CURRENT_DAC, stepper_dac.set_current_value(parser.byteval('P', -1), parser.ushortval('S', 0)));
  }

  #if ENABLED(HAS_MOTOR_CURRENT_DAC)

    void GcodeSuite::M909() { stepper_dac.print_values(); }
    void GcodeSuite::M910() { stepper_dac.commit_eeprom(); }

  #endif // HAS_MOTOR_CURRENT_DAC

#endif // HAS_MOTOR_CURRENT_SPI || HAS_MOTOR_CURRENT_DAC

#endif // HAS_MOTOR_CURRENT_SPI || HAS_MOTOR_CURRENT_PWM || HAS_MOTOR_CURRENT_I2C || HAS_MOTOR_CURRENT_DAC
>>>>>>> mcu_ctrl
