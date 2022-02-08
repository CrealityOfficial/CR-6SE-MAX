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
// Temperature Menu
//

<<<<<<< HEAD
#include "../../inc/MarlinConfigPre.h"

#if HAS_LCD_MENU

#include "menu.h"
#include "../../module/temperature.h"

#if FAN_COUNT > 1 || ENABLED(SINGLENOZZLE)
  #include "../../module/motion.h"
#endif

#if ENABLED(SINGLENOZZLE)
  #include "../../module/tool_change.h"
#endif

// Initialized by settings.load()
int16_t MarlinUI::preheat_hotend_temp[2], MarlinUI::preheat_bed_temp[2];
uint8_t MarlinUI::preheat_fan_speed[2];
=======
#include "../../inc/MarlinConfig.h"

#if HAS_LCD_MENU && HAS_TEMPERATURE

#include "menu_item.h"
#include "../../module/temperature.h"

#if HAS_FAN || ENABLED(SINGLENOZZLE)
  #include "../../module/motion.h"
#endif

#if EITHER(HAS_COOLER, LASER_COOLANT_FLOW_METER)
  #include "../../feature/cooler.h"
#endif

#if ENABLED(SINGLENOZZLE_STANDBY_TEMP)
  #include "../../module/tool_change.h"
#endif
>>>>>>> mcu_ctrl

//
// "Temperature" submenu items
//

<<<<<<< HEAD
void _lcd_preheat(const int16_t endnum, const int16_t temph, const int16_t tempb, const uint8_t fan) {
  #if HOTENDS
    if (temph > 0) thermalManager.setTargetHotend(_MIN(heater_maxtemp[endnum] - 15, temph), endnum);
  #endif
  #if HAS_HEATED_BED
    if (tempb >= 0) thermalManager.setTargetBed(tempb);
  #else
    UNUSED(tempb);
  #endif
  #if FAN_COUNT > 0
    #if FAN_COUNT > 1
      thermalManager.set_fan_speed(active_extruder < FAN_COUNT ? active_extruder : 0, fan);
    #else
      thermalManager.set_fan_speed(0, fan);
    #endif
  #else
    UNUSED(fan);
=======
void Temperature::lcd_preheat(const uint8_t e, const int8_t indh, const int8_t indb) {
  UNUSED(e); UNUSED(indh); UNUSED(indb);
  #if HAS_HOTEND
    if (indh >= 0 && ui.material_preset[indh].hotend_temp > 0)
      setTargetHotend(_MIN(thermalManager.hotend_max_target(e), ui.material_preset[indh].hotend_temp), e);
  #endif
  #if HAS_HEATED_BED
    if (indb >= 0 && ui.material_preset[indb].bed_temp > 0) setTargetBed(ui.material_preset[indb].bed_temp);
  #endif
  #if HAS_FAN
    if (indh >= 0)
      set_fan_speed(active_extruder < (FAN_COUNT) ? active_extruder : 0, ui.material_preset[indh].fan_speed);
>>>>>>> mcu_ctrl
  #endif
  ui.return_to_status();
}

<<<<<<< HEAD
#if HAS_TEMP_HOTEND
  inline void _preheat_end(const uint8_t m, const uint8_t e) {
    _lcd_preheat(e, ui.preheat_hotend_temp[m], -1, ui.preheat_fan_speed[m]);
  }
  #if HAS_HEATED_BED
    inline void _preheat_both(const uint8_t m, const uint8_t e) {
      _lcd_preheat(e, ui.preheat_hotend_temp[m], ui.preheat_bed_temp[m], ui.preheat_fan_speed[m]);
    }
  #endif
#endif
#if HAS_HEATED_BED
  inline void _preheat_bed(const uint8_t m) {
    _lcd_preheat(0, 0, ui.preheat_bed_temp[m], ui.preheat_fan_speed[m]);
  }
#endif

#if HAS_TEMP_HOTEND || HAS_HEATED_BED

  #define _PREHEAT_ITEMS(M,N) do{ \
    ACTION_ITEM_N(N, MSG_PREHEAT_##M##_H, []{ _preheat_both(M-1, MenuItemBase::itemIndex); }); \
    ACTION_ITEM_N(N, MSG_PREHEAT_##M##_END_E, []{ _preheat_end(M-1, MenuItemBase::itemIndex); }); \
  }while(0)
  #if HAS_HEATED_BED
    #define PREHEAT_ITEMS(M,N) _PREHEAT_ITEMS(M,N)
  #else
    #define PREHEAT_ITEMS(M,N) \
      ACTION_ITEM_N(N, MSG_PREHEAT_##M##_H, []{ _preheat_end(M-1, MenuItemBase::itemIndex); })
  #endif

  void menu_preheat_m1() {
    START_MENU();
    BACK_ITEM(MSG_TEMPERATURE);
    #if HOTENDS == 1
      #if HAS_HEATED_BED
        ACTION_ITEM(MSG_PREHEAT_1, []{ _preheat_both(0, 0); });
        ACTION_ITEM(MSG_PREHEAT_1_END, []{ _preheat_end(0, 0); });
      #else
        ACTION_ITEM(MSG_PREHEAT_1, []{ _preheat_end(0, 0); });
      #endif
    #elif HOTENDS > 1
      #if HAS_HEATED_BED
        _PREHEAT_ITEMS(1,0);
      #endif
      for (uint8_t n = 1; n < HOTENDS; n++) PREHEAT_ITEMS(1,n);
      ACTION_ITEM(MSG_PREHEAT_1_ALL, []() {
        #if HAS_HEATED_BED
          _preheat_bed(0);
        #endif
        HOTEND_LOOP() thermalManager.setTargetHotend(ui.preheat_hotend_temp[0], e);
      });
    #endif // HOTENDS > 1
    #if HAS_HEATED_BED
      ACTION_ITEM(MSG_PREHEAT_1_BEDONLY, []{ _preheat_bed(0); });
    #endif
    END_MENU();
  }

  void menu_preheat_m2() {
    START_MENU();
    BACK_ITEM(MSG_TEMPERATURE);
    #if HOTENDS == 1
      #if HAS_HEATED_BED
        ACTION_ITEM(MSG_PREHEAT_2, []{ _preheat_both(1, 0); });
        ACTION_ITEM(MSG_PREHEAT_2_END, []{ _preheat_end(1, 0); });
      #else
        ACTION_ITEM(MSG_PREHEAT_2, []{ _preheat_end(1, 0); });
      #endif
    #elif HOTENDS > 1
      #if HAS_HEATED_BED
        _PREHEAT_ITEMS(2,0);
      #endif
      for (uint8_t n = 1; n < HOTENDS; n++) PREHEAT_ITEMS(2,n);
      ACTION_ITEM(MSG_PREHEAT_2_ALL, []() {
        #if HAS_HEATED_BED
          _preheat_bed(1);
        #endif
        HOTEND_LOOP() thermalManager.setTargetHotend(ui.preheat_hotend_temp[1], e);
      });
    #endif // HOTENDS > 1
    #if HAS_HEATED_BED
      ACTION_ITEM(MSG_PREHEAT_2_BEDONLY, []{ _preheat_bed(1); });
    #endif
    END_MENU();
  }
=======
#if PREHEAT_COUNT

  #if HAS_TEMP_HOTEND
    inline void _preheat_end(const uint8_t m, const uint8_t e) { thermalManager.lcd_preheat(e, m, -1); }
    void do_preheat_end_m() { _preheat_end(editable.int8, 0); }
  #endif
  #if HAS_HEATED_BED
    inline void _preheat_bed(const uint8_t m) { thermalManager.lcd_preheat(0, -1, m); }
  #endif
  #if HAS_COOLER
    inline void _precool_laser(const uint8_t m, const uint8_t e) { thermalManager.lcd_preheat(e, m, -1); }
    void do_precool_laser_m() { _precool_laser(editable.int8, thermalManager.temp_cooler.target); }
  #endif

  #if HAS_TEMP_HOTEND && HAS_HEATED_BED
    inline void _preheat_both(const uint8_t m, const uint8_t e) { thermalManager.lcd_preheat(e, m, m); }

    // Indexed "Preheat ABC" and "Heat Bed" items
    #define PREHEAT_ITEMS(M,E) do{ \
      ACTION_ITEM_N_S(E, ui.get_preheat_label(M), MSG_PREHEAT_M_H, []{ _preheat_both(M, MenuItemBase::itemIndex); }); \
      ACTION_ITEM_N_S(E, ui.get_preheat_label(M), MSG_PREHEAT_M_END_E, []{ _preheat_end(M, MenuItemBase::itemIndex); }); \
    }while(0)

  #elif HAS_MULTI_HOTEND

    // No heated bed, so just indexed "Preheat ABC" items
    #define PREHEAT_ITEMS(M,E) ACTION_ITEM_N_S(E, ui.get_preheat_label(M), MSG_PREHEAT_M_H, []{ _preheat_end(M, MenuItemBase::itemIndex); })

  #endif

  #if HAS_MULTI_HOTEND || HAS_HEATED_BED

    // Set editable.int8 to the Material index before entering this menu
    // because MenuItemBase::itemIndex will be re-used by PREHEAT_ITEMS
    void menu_preheat_m() {
      const uint8_t m = editable.int8; // Don't re-use 'editable' in this menu

      START_MENU();
      BACK_ITEM(MSG_TEMPERATURE);

      #if HOTENDS == 1

        #if HAS_HEATED_BED
          ACTION_ITEM_S(ui.get_preheat_label(m), MSG_PREHEAT_M, []{ _preheat_both(editable.int8, 0); });
          ACTION_ITEM_S(ui.get_preheat_label(m), MSG_PREHEAT_M_END, do_preheat_end_m);
        #else
          ACTION_ITEM_S(ui.get_preheat_label(m), MSG_PREHEAT_M, do_preheat_end_m);
        #endif

      #elif HAS_MULTI_HOTEND

        HOTEND_LOOP() PREHEAT_ITEMS(editable.int8, e);
        ACTION_ITEM_S(ui.get_preheat_label(m), MSG_PREHEAT_M_ALL, []() {
          HOTEND_LOOP() thermalManager.setTargetHotend(ui.material_preset[editable.int8].hotend_temp, e);
          TERN(HAS_HEATED_BED, _preheat_bed(editable.int8), ui.return_to_status());
        });

      #endif

      #if HAS_HEATED_BED
        ACTION_ITEM_S(ui.get_preheat_label(m), MSG_PREHEAT_M_BEDONLY, []{ _preheat_bed(editable.int8); });
      #endif

      END_MENU();
    }

  #endif // HAS_MULTI_HOTEND || HAS_HEATED_BED

#endif // PREHEAT_COUNT

#if HAS_TEMP_HOTEND || HAS_HEATED_BED
>>>>>>> mcu_ctrl

  void lcd_cooldown() {
    thermalManager.zero_fan_speeds();
    thermalManager.disable_all_heaters();
    ui.return_to_status();
  }

#endif // HAS_TEMP_HOTEND || HAS_HEATED_BED

void menu_temperature() {
<<<<<<< HEAD
=======
  #if HAS_TEMP_HOTEND || HAS_HEATED_BED
    bool has_heat = false;
    #if HAS_TEMP_HOTEND
      HOTEND_LOOP() if (thermalManager.degTargetHotend(HOTEND_INDEX)) { has_heat = true; break; }
    #endif
  #endif

  #if HAS_COOLER
    if (thermalManager.temp_cooler.target == 0) thermalManager.temp_cooler.target = COOLER_DEFAULT_TEMP;
  #endif

>>>>>>> mcu_ctrl
  START_MENU();
  BACK_ITEM(MSG_MAIN);

  //
  // Nozzle:
  // Nozzle [1-5]:
  //
  #if HOTENDS == 1
<<<<<<< HEAD
    EDIT_ITEM_FAST(int3, MSG_NOZZLE, &thermalManager.temp_hotend[0].target, 0, HEATER_0_MAXTEMP - 15, []{ thermalManager.start_watching_hotend(0); });
  #elif HOTENDS > 1
    #define EDIT_TARGET(N) EDIT_ITEM_FAST_N(int3, N, MSG_NOZZLE_N, &thermalManager.temp_hotend[N].target, 0, heater_maxtemp[N] - 15, []{ thermalManager.start_watching_hotend(MenuItemBase::itemIndex); })
    HOTEND_LOOP() EDIT_TARGET(e);
  #endif

  #if ENABLED(SINGLENOZZLE)
    EDIT_ITEM_FAST(uint16_3, MSG_NOZZLE_STANDBY, &singlenozzle_temp[active_extruder ? 0 : 1], 0, HEATER_0_MAXTEMP - 15);
=======
    EDIT_ITEM_FAST(int3, MSG_NOZZLE, &thermalManager.temp_hotend[0].target, 0, thermalManager.hotend_max_target(0), []{ thermalManager.start_watching_hotend(0); });
  #elif HAS_MULTI_HOTEND
    HOTEND_LOOP()
      EDIT_ITEM_FAST_N(int3, e, MSG_NOZZLE_N, &thermalManager.temp_hotend[e].target, 0, thermalManager.hotend_max_target(e), []{ thermalManager.start_watching_hotend(MenuItemBase::itemIndex); });
  #endif

  #if ENABLED(SINGLENOZZLE_STANDBY_TEMP)
    LOOP_S_L_N(e, 1, EXTRUDERS)
      EDIT_ITEM_FAST_N(int3, e, MSG_NOZZLE_STANDBY, &thermalManager.singlenozzle_temp[e], 0, thermalManager.hotend_max_target(0));
>>>>>>> mcu_ctrl
  #endif

  //
  // Bed:
  //
  #if HAS_HEATED_BED
<<<<<<< HEAD
    EDIT_ITEM_FAST(int3, MSG_BED, &thermalManager.temp_bed.target, 0, BED_MAXTEMP - 10, thermalManager.start_watching_bed);
=======
    EDIT_ITEM_FAST(int3, MSG_BED, &thermalManager.temp_bed.target, 0, BED_MAX_TARGET, thermalManager.start_watching_bed);
>>>>>>> mcu_ctrl
  #endif

  //
  // Chamber:
  //
  #if HAS_HEATED_CHAMBER
<<<<<<< HEAD
    EDIT_ITEM_FAST(int3, MSG_CHAMBER, &thermalManager.temp_chamber.target, 0, CHAMBER_MAXTEMP - 5, thermalManager.start_watching_chamber);
=======
    EDIT_ITEM_FAST(int3, MSG_CHAMBER, &thermalManager.temp_chamber.target, 0, CHAMBER_MAX_TARGET, thermalManager.start_watching_chamber);
  #endif

  //
  // Cooler:
  //
  #if HAS_COOLER
    bool cstate = cooler.enabled;
    EDIT_ITEM(bool, MSG_COOLER_TOGGLE, &cstate, cooler.toggle);
    EDIT_ITEM_FAST(int3, MSG_COOLER, &thermalManager.temp_cooler.target, COOLER_MIN_TARGET, COOLER_MAX_TARGET, thermalManager.start_watching_cooler);
  #endif

  //
  // Flow Meter Safety Shutdown:
  //
  #if ENABLED(FLOWMETER_SAFETY)
    bool fstate = cooler.flowsafety_enabled;
    EDIT_ITEM(bool, MSG_FLOWMETER_SAFETY, &fstate, cooler.flowsafety_toggle);
>>>>>>> mcu_ctrl
  #endif

  //
  // Fan Speed:
  //
<<<<<<< HEAD
  #if FAN_COUNT > 0
    #if HAS_FAN0
      editable.uint8 = thermalManager.fan_speed[0];
      EDIT_ITEM_FAST_N(percent, 1, MSG_FIRST_FAN_SPEED, &editable.uint8, 0, 255, []{ thermalManager.set_fan_speed(0, editable.uint8); });
      #if ENABLED(EXTRA_FAN_SPEED)
        EDIT_ITEM_FAST_N(percent, 1, MSG_FIRST_EXTRA_FAN_SPEED, &thermalManager.new_fan_speed[0], 3, 255);
      #endif
    #endif
    #if HAS_FAN1
      editable.uint8 = thermalManager.fan_speed[1];
      EDIT_ITEM_FAST_N(percent, 2, MSG_FAN_SPEED_N, &editable.uint8, 0, 255, []{ thermalManager.set_fan_speed(1, editable.uint8); });
      #if ENABLED(EXTRA_FAN_SPEED)
        EDIT_ITEM_FAST_N(percent, 2, MSG_EXTRA_FAN_SPEED_N, &thermalManager.new_fan_speed[1], 3, 255);
      #endif
    #elif ENABLED(SINGLENOZZLE) && EXTRUDERS > 1
      editable.uint8 = thermalManager.fan_speed[1];
      EDIT_ITEM_FAST_N(percent, 2, MSG_STORED_FAN_N, &editable.uint8, 0, 255, []{ thermalManager.set_fan_speed(1, editable.uint8); });
    #endif
    #if HAS_FAN2
      editable.uint8 = thermalManager.fan_speed[2];
      EDIT_ITEM_FAST_N(percent, 3, MSG_FAN_SPEED_N, &editable.uint8, 0, 255, []{ thermalManager.set_fan_speed(2, editable.uint8); });
      #if ENABLED(EXTRA_FAN_SPEED)
        EDIT_ITEM_FAST_N(percent, 3, MSG_EXTRA_FAN_SPEED_N, &thermalManager.new_fan_speed[2], 3, 255);
      #endif
    #elif ENABLED(SINGLENOZZLE) && EXTRUDERS > 2
      editable.uint8 = thermalManager.fan_speed[2];
      EDIT_ITEM_FAST_N(percent, 3, MSG_STORED_FAN_N, &editable.uint8, 0, 255, []{ thermalManager.set_fan_speed(2, editable.uint8); });
    #endif
  #endif // FAN_COUNT > 0

  #if HAS_TEMP_HOTEND

    //
    // Preheat for Material 1 and 2
    //
    #if TEMP_SENSOR_1 != 0 || TEMP_SENSOR_2 != 0 || TEMP_SENSOR_3 != 0 || TEMP_SENSOR_4 != 0 || TEMP_SENSOR_5 != 0 || HAS_HEATED_BED
      SUBMENU(MSG_PREHEAT_1, menu_preheat_m1);
      SUBMENU(MSG_PREHEAT_2, menu_preheat_m2);
    #else
      ACTION_ITEM(MSG_PREHEAT_1, []{ _preheat_end(0, 0); });
      ACTION_ITEM(MSG_PREHEAT_2, []{ _preheat_end(1, 0); });
    #endif

    //
    // Cooldown
    //
    bool has_heat = false;
    HOTEND_LOOP() if (thermalManager.temp_hotend[HOTEND_INDEX].target) { has_heat = true; break; }
    #if HAS_TEMP_BED
      if (thermalManager.temp_bed.target) has_heat = true;
    #endif
    if (has_heat) ACTION_ITEM(MSG_COOLDOWN, lcd_cooldown);

  #endif // HAS_TEMP_HOTEND
=======
  #if HAS_FAN

    DEFINE_SINGLENOZZLE_ITEM();

    #if HAS_FAN0
      _FAN_EDIT_ITEMS(0,FIRST_FAN_SPEED);
    #endif
    #if HAS_FAN1
      FAN_EDIT_ITEMS(1);
    #elif SNFAN(1)
      singlenozzle_item(1);
    #endif
    #if HAS_FAN2
      FAN_EDIT_ITEMS(2);
    #elif SNFAN(2)
      singlenozzle_item(2);
    #endif
    #if HAS_FAN3
      FAN_EDIT_ITEMS(3);
    #elif SNFAN(3)
      singlenozzle_item(3);
    #endif
    #if HAS_FAN4
      FAN_EDIT_ITEMS(4);
    #elif SNFAN(4)
      singlenozzle_item(4);
    #endif
    #if HAS_FAN5
      FAN_EDIT_ITEMS(5);
    #elif SNFAN(5)
      singlenozzle_item(5);
    #endif
    #if HAS_FAN6
      FAN_EDIT_ITEMS(6);
    #elif SNFAN(6)
      singlenozzle_item(6);
    #endif
    #if HAS_FAN7
      FAN_EDIT_ITEMS(7);
    #elif SNFAN(7)
      singlenozzle_item(7);
    #endif

  #endif // HAS_FAN

  #if PREHEAT_COUNT
    //
    // Preheat for all Materials
    //
    LOOP_L_N(m, PREHEAT_COUNT) {
      editable.int8 = m;
      #if HOTENDS > 1 || HAS_HEATED_BED
        SUBMENU_S(ui.get_preheat_label(m), MSG_PREHEAT_M, menu_preheat_m);
      #elif HAS_HOTEND
        ACTION_ITEM_S(ui.get_preheat_label(m), MSG_PREHEAT_M, do_preheat_end_m);
      #endif
    }
  #endif

  #if HAS_TEMP_HOTEND || HAS_HEATED_BED
    //
    // Cooldown
    //
    if (TERN0(HAS_HEATED_BED, thermalManager.degTargetBed())) has_heat = true;
    if (has_heat) ACTION_ITEM(MSG_COOLDOWN, lcd_cooldown);
  #endif
>>>>>>> mcu_ctrl

  END_MENU();
}

<<<<<<< HEAD
#endif // HAS_LCD_MENU
=======
#if ENABLED(PREHEAT_SHORTCUT_MENU_ITEM)

  void menu_preheat_only() {
    START_MENU();
    BACK_ITEM(MSG_MAIN);

    LOOP_L_N(m, PREHEAT_COUNT) {
      editable.int8 = m;
      #if HOTENDS > 1 || HAS_HEATED_BED
        SUBMENU_S(ui.get_preheat_label(m), MSG_PREHEAT_M, menu_preheat_m);
      #else
        ACTION_ITEM_S(ui.get_preheat_label(m), MSG_PREHEAT_M, do_preheat_end_m);
      #endif
    }

    END_MENU();
  }

#endif

#endif // HAS_LCD_MENU && HAS_TEMPERATURE
>>>>>>> mcu_ctrl
