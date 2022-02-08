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

//
// Spindle / Laser Menu
//

#include "../../inc/MarlinConfig.h"

#if HAS_LCD_MENU && HAS_CUTTER

<<<<<<< HEAD
  #include "menu.h"
=======
  #include "menu_item.h"
>>>>>>> mcu_ctrl

  #include "../../feature/spindle_laser.h"

  void menu_spindle_laser() {
<<<<<<< HEAD

    START_MENU();
    BACK_ITEM(MSG_MAIN);
    if (cutter.enabled()) {
      #if ENABLED(SPINDLE_LASER_PWM)
        EDIT_ITEM(CUTTER_MENU_TYPE, MSG_CUTTER(POWER), &cutter.power, SPEED_POWER_MIN, SPEED_POWER_MAX);
      #endif
      ACTION_ITEM(MSG_CUTTER(OFF), cutter.disable);
    }
    else {
      ACTION_ITEM(MSG_CUTTER(ON), cutter.enable_forward);
      #if ENABLED(SPINDLE_CHANGE_DIR)
        ACTION_ITEM(MSG_SPINDLE_REVERSE, cutter.enable_reverse);
      #endif
    }
=======
    bool is_enabled = cutter.enabled() && cutter.isReady;
    #if ENABLED(SPINDLE_CHANGE_DIR)
      bool is_rev = cutter.is_reverse();
    #endif

    START_MENU();
    BACK_ITEM(MSG_MAIN);

    #if ENABLED(SPINDLE_LASER_PWM)
      // Change the cutter's "current power" value without turning the cutter on or off
      // Power is displayed and set in units and range according to CUTTER_POWER_UNIT
      EDIT_ITEM_FAST(CUTTER_MENU_POWER_TYPE, MSG_CUTTER(POWER), &cutter.menuPower,
        cutter.mpower_min(), cutter.mpower_max(), cutter.update_from_mpower);
    #endif

    editable.state = is_enabled;
    EDIT_ITEM(bool, MSG_CUTTER(TOGGLE), &is_enabled, []{ if (editable.state) cutter.disable(); else cutter.enable_same_dir(); });

    #if ENABLED(AIR_EVACUATION)
      bool evac_state = cutter.air_evac_state();
      EDIT_ITEM(bool, MSG_CUTTER(EVAC_TOGGLE), &evac_state, cutter.air_evac_toggle);
    #endif

    #if ENABLED(AIR_ASSIST)
      bool air_assist_state = cutter.air_assist_state();
      EDIT_ITEM(bool, MSG_CUTTER(ASSIST_TOGGLE), &air_assist_state, cutter.air_assist_toggle);
    #endif

    #if ENABLED(SPINDLE_CHANGE_DIR)
      if (!is_enabled) {
        editable.state = is_rev;
        ACTION_ITEM_P(is_rev ? GET_TEXT(MSG_CUTTER(REVERSE)) : GET_TEXT(MSG_CUTTER(FORWARD)), []{ cutter.set_reverse(!editable.state); });
      }
    #endif

    #if ENABLED(LASER_FEATURE)
      // Setup and fire a test pulse using the current PWM power level for for a duration of test_pulse_min to test_pulse_max ms.
      EDIT_ITEM_FAST(CUTTER_MENU_PULSE_TYPE, MSG_LASER_PULSE_MS, &cutter.testPulse, LASER_TEST_PULSE_MIN, LASER_TEST_PULSE_MAX);
      ACTION_ITEM(MSG_LASER_FIRE_PULSE, cutter.test_fire_pulse);
    #endif

    #if BOTH(MARLIN_DEV_MODE, HAL_CAN_SET_PWM_FREQ) && defined(SPINDLE_LASER_FREQUENCY)
      EDIT_ITEM_FAST(CUTTER_MENU_FREQUENCY_TYPE, MSG_CUTTER_FREQUENCY, &cutter.frequency, 2000, 80000, cutter.refresh_frequency);
    #endif

>>>>>>> mcu_ctrl
    END_MENU();
  }

#endif // HAS_LCD_MENU && HAS_CUTTER
