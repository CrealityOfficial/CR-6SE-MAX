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
 * Finnish
 *
 * LCD Menu Messages
<<<<<<< HEAD
 * See also http://marlinfw.org/docs/development/lcd_language.html
 *
=======
 * See also https://marlinfw.org/docs/development/lcd_language.html
>>>>>>> mcu_ctrl
 */

#define DISPLAY_CHARSET_ISO10646_1

namespace Language_fi {
  using namespace Language_en; // Inherit undefined strings from English

  constexpr uint8_t    CHARSIZE                            = 2;
  PROGMEM Language_Str LANGUAGE                            = _UxGT("Finnish");

  PROGMEM Language_Str WELCOME_MSG                         = MACHINE_NAME _UxGT(" valmis.");
  PROGMEM Language_Str MSG_MEDIA_INSERTED                  = _UxGT("Kortti asetettu");
  PROGMEM Language_Str MSG_MEDIA_REMOVED                   = _UxGT("Kortti poistettu");
  PROGMEM Language_Str MSG_MAIN                            = _UxGT("Palaa");
<<<<<<< HEAD
  PROGMEM Language_Str MSG_AUTOSTART                       = _UxGT("Automaatti");
  PROGMEM Language_Str MSG_DISABLE_STEPPERS                = _UxGT("Vapauta moottorit");
  PROGMEM Language_Str MSG_AUTO_HOME                       = _UxGT("Aja referenssiin");
  PROGMEM Language_Str MSG_SET_ORIGIN                      = _UxGT("Aseta origo");
  PROGMEM Language_Str MSG_PREHEAT_1                       = _UxGT("Esil??mmit?? ") PREHEAT_1_LABEL;
  PROGMEM Language_Str MSG_PREHEAT_1_H                     = _UxGT("Esil??mmit?? ") PREHEAT_1_LABEL " ~";
  PROGMEM Language_Str MSG_PREHEAT_1_END                   = _UxGT("Esil??. ") PREHEAT_1_LABEL _UxGT("Suutin");
  PROGMEM Language_Str MSG_PREHEAT_1_END_E                 = _UxGT("Esil??. ") PREHEAT_1_LABEL _UxGT("Suutin ~");
  PROGMEM Language_Str MSG_PREHEAT_1_ALL                   = _UxGT("Esil??. ") PREHEAT_1_LABEL _UxGT(" Kaikki");
  PROGMEM Language_Str MSG_PREHEAT_1_BEDONLY               = _UxGT("Esil??. ") PREHEAT_1_LABEL _UxGT(" Alusta");
  PROGMEM Language_Str MSG_PREHEAT_1_SETTINGS              = _UxGT("Esil??mm. ") PREHEAT_1_LABEL _UxGT(" konf");
  PROGMEM Language_Str MSG_PREHEAT_2                       = _UxGT("Esil??mmit?? ") PREHEAT_2_LABEL;
  PROGMEM Language_Str MSG_PREHEAT_2_H                     = _UxGT("Esil??mmit?? ") PREHEAT_2_LABEL " ~";
  PROGMEM Language_Str MSG_PREHEAT_2_END                   = _UxGT("Esil??. ") PREHEAT_2_LABEL _UxGT("Suutin");
  PROGMEM Language_Str MSG_PREHEAT_2_END_E                 = _UxGT("Esil??. ") PREHEAT_2_LABEL _UxGT("Suutin ~");
  PROGMEM Language_Str MSG_PREHEAT_2_ALL                   = _UxGT("Esil??. ") PREHEAT_2_LABEL _UxGT(" Kaikki");
  PROGMEM Language_Str MSG_PREHEAT_2_BEDONLY               = _UxGT("Esil??. ") PREHEAT_2_LABEL _UxGT(" Alusta");
  PROGMEM Language_Str MSG_PREHEAT_2_SETTINGS              = _UxGT("Esil??mm. ") PREHEAT_2_LABEL _UxGT(" konf");
=======
  PROGMEM Language_Str MSG_RUN_AUTO_FILES                  = _UxGT("Automaatti");
  PROGMEM Language_Str MSG_DISABLE_STEPPERS                = _UxGT("Vapauta moottorit");
  PROGMEM Language_Str MSG_AUTO_HOME                       = _UxGT("Aja referenssiin");
  PROGMEM Language_Str MSG_SET_ORIGIN                      = _UxGT("Aseta origo");
  #if PREHEAT_COUNT
    PROGMEM Language_Str MSG_PREHEAT_1                     = _UxGT("Esil??mmit?? ") PREHEAT_1_LABEL;
    PROGMEM Language_Str MSG_PREHEAT_1_H                   = _UxGT("Esil??mmit?? ") PREHEAT_1_LABEL " ~";
    PROGMEM Language_Str MSG_PREHEAT_1_END                 = _UxGT("Esil??. ") PREHEAT_1_LABEL _UxGT("Suutin");
    PROGMEM Language_Str MSG_PREHEAT_1_END_E               = _UxGT("Esil??. ") PREHEAT_1_LABEL _UxGT("Suutin ~");
    PROGMEM Language_Str MSG_PREHEAT_1_ALL                 = _UxGT("Esil??. ") PREHEAT_1_LABEL _UxGT(" Kaikki");
    PROGMEM Language_Str MSG_PREHEAT_1_BEDONLY             = _UxGT("Esil??. ") PREHEAT_1_LABEL _UxGT(" Alusta");
    PROGMEM Language_Str MSG_PREHEAT_1_SETTINGS            = _UxGT("Esil??mm. ") PREHEAT_1_LABEL _UxGT(" konf");

    PROGMEM Language_Str MSG_PREHEAT_M                     = _UxGT("Esil??mmit?? $");
    PROGMEM Language_Str MSG_PREHEAT_M_H                   = _UxGT("Esil??mmit?? $ ~");
    PROGMEM Language_Str MSG_PREHEAT_M_END                 = _UxGT("Esil??. $Suutin");
    PROGMEM Language_Str MSG_PREHEAT_M_END_E               = _UxGT("Esil??. $Suutin ~");
    PROGMEM Language_Str MSG_PREHEAT_M_ALL                 = _UxGT("Esil??. $ Kaikki");
    PROGMEM Language_Str MSG_PREHEAT_M_BEDONLY             = _UxGT("Esil??. $ Alusta");
    PROGMEM Language_Str MSG_PREHEAT_M_SETTINGS            = _UxGT("Esil??mm. $ konf");
  #endif
>>>>>>> mcu_ctrl
  PROGMEM Language_Str MSG_COOLDOWN                        = _UxGT("J????hdyt??");
  PROGMEM Language_Str MSG_SWITCH_PS_ON                    = _UxGT("Virta p????lle");
  PROGMEM Language_Str MSG_SWITCH_PS_OFF                   = _UxGT("Virta pois");
  PROGMEM Language_Str MSG_EXTRUDE                         = _UxGT("Pursota");
  PROGMEM Language_Str MSG_RETRACT                         = _UxGT("Ved?? takaisin");
  PROGMEM Language_Str MSG_MOVE_AXIS                       = _UxGT("Liikuta akseleita");
  PROGMEM Language_Str MSG_MOVE_X                          = _UxGT("Liikuta X");
  PROGMEM Language_Str MSG_MOVE_Y                          = _UxGT("Liikuta Y");
  PROGMEM Language_Str MSG_MOVE_Z                          = _UxGT("Liikuta Z");
  PROGMEM Language_Str MSG_MOVE_E                          = _UxGT("Extruder");
  PROGMEM Language_Str MSG_MOVE_EN                         = _UxGT("Extruder *");
<<<<<<< HEAD
  PROGMEM Language_Str MSG_MOVE_Z_DIST                     = _UxGT("Liikuta %smm");
=======
  PROGMEM Language_Str MSG_MOVE_N_MM                       = _UxGT("Liikuta %smm");
>>>>>>> mcu_ctrl
  PROGMEM Language_Str MSG_MOVE_01MM                       = _UxGT("Liikuta 0.1mm");
  PROGMEM Language_Str MSG_MOVE_1MM                        = _UxGT("Liikuta 1mm");
  PROGMEM Language_Str MSG_MOVE_10MM                       = _UxGT("Liikuta 10mm");
  PROGMEM Language_Str MSG_SPEED                           = _UxGT("Nopeus");
  PROGMEM Language_Str MSG_NOZZLE                          = _UxGT("Suutin");
  PROGMEM Language_Str MSG_NOZZLE_N                        = _UxGT("Suutin ~");
  PROGMEM Language_Str MSG_BED                             = _UxGT("Alusta");
  PROGMEM Language_Str MSG_FAN_SPEED                       = _UxGT("Tuul. nopeus");
<<<<<<< HEAD
  PROGMEM Language_Str MSG_FAN_SPEED_N                     = _UxGT("Tuul. nopeus =");
=======
  PROGMEM Language_Str MSG_FAN_SPEED_N                     = _UxGT("Tuul. nopeus ~");
>>>>>>> mcu_ctrl
  PROGMEM Language_Str MSG_FLOW                            = _UxGT("Virtaus");
  PROGMEM Language_Str MSG_FLOW_N                          = _UxGT("Virtaus ~");
  PROGMEM Language_Str MSG_CONTROL                         = _UxGT("Kontrolli");
  PROGMEM Language_Str MSG_MIN                             = " " LCD_STR_THERMOMETER _UxGT(" Min");
  PROGMEM Language_Str MSG_MAX                             = " " LCD_STR_THERMOMETER _UxGT(" Max");
  PROGMEM Language_Str MSG_FACTOR                          = " " LCD_STR_THERMOMETER _UxGT(" Kerr");
  PROGMEM Language_Str MSG_AUTOTEMP                        = _UxGT("Autotemp");
  PROGMEM Language_Str MSG_ACC                             = _UxGT("Kiihtyv");
  PROGMEM Language_Str MSG_VTRAV_MIN                       = _UxGT("VLiike min");
  PROGMEM Language_Str MSG_A_RETRACT                       = _UxGT("A-peruuta");
  PROGMEM Language_Str MSG_TEMPERATURE                     = _UxGT("L??mp??tila");
  PROGMEM Language_Str MSG_MOTION                          = _UxGT("Liike");
  PROGMEM Language_Str MSG_FILAMENT                        = _UxGT("Filament");
<<<<<<< HEAD
  PROGMEM Language_Str MSG_VOLUMETRIC_ENABLED              = _UxGT("E in mm??");
  PROGMEM Language_Str MSG_CONTRAST                        = _UxGT("LCD kontrasti");
  PROGMEM Language_Str MSG_STORE_EEPROM                    = _UxGT("Tallenna muistiin");
  PROGMEM Language_Str MSG_LOAD_EEPROM                     = _UxGT("Lataa muistista");
  PROGMEM Language_Str MSG_RESTORE_FAILSAFE                = _UxGT("Palauta oletus");
  PROGMEM Language_Str MSG_REFRESH                         = LCD_STR_REFRESH  _UxGT("P??ivit??");
  PROGMEM Language_Str MSG_WATCH                           = _UxGT("Seuraa");
=======
  PROGMEM Language_Str MSG_VOLUMETRIC_ENABLED              = _UxGT("E in mm") SUPERSCRIPT_THREE;
  PROGMEM Language_Str MSG_CONTRAST                        = _UxGT("LCD kontrasti");
  PROGMEM Language_Str MSG_STORE_EEPROM                    = _UxGT("Tallenna muistiin");
  PROGMEM Language_Str MSG_LOAD_EEPROM                     = _UxGT("Lataa muistista");
  PROGMEM Language_Str MSG_RESTORE_DEFAULTS                = _UxGT("Palauta oletus");
  PROGMEM Language_Str MSG_REFRESH                         = LCD_STR_REFRESH  _UxGT("P??ivit??");
  PROGMEM Language_Str MSG_INFO_SCREEN                     = _UxGT("Seuraa");
>>>>>>> mcu_ctrl
  PROGMEM Language_Str MSG_PREPARE                         = _UxGT("Valmistele");
  PROGMEM Language_Str MSG_TUNE                            = _UxGT("S????d??");
  PROGMEM Language_Str MSG_PAUSE_PRINT                     = _UxGT("Keskeyt?? tulostus");
  PROGMEM Language_Str MSG_RESUME_PRINT                    = _UxGT("Jatka tulostusta");
  PROGMEM Language_Str MSG_STOP_PRINT                      = _UxGT("Pys??yt?? tulostus");
  PROGMEM Language_Str MSG_MEDIA_MENU                      = _UxGT("Korttivalikko");
  PROGMEM Language_Str MSG_NO_MEDIA                        = _UxGT("Ei korttia");
  PROGMEM Language_Str MSG_DWELL                           = _UxGT("Nukkumassa...");
  PROGMEM Language_Str MSG_USERWAIT                        = _UxGT("Odotet. valintaa");
  PROGMEM Language_Str MSG_NO_MOVE                         = _UxGT("Ei liiketta.");
  PROGMEM Language_Str MSG_CONTROL_RETRACT                 = _UxGT("Ved?? mm");
  PROGMEM Language_Str MSG_CONTROL_RETRACT_SWAP            = _UxGT("Va. Ved?? mm");
  PROGMEM Language_Str MSG_CONTROL_RETRACTF                = _UxGT("Ved?? V");
  PROGMEM Language_Str MSG_CONTROL_RETRACT_ZHOP            = _UxGT("Z mm");
<<<<<<< HEAD
  PROGMEM Language_Str MSG_CONTROL_RETRACT_RECOVER         = _UxGT("UnRet mm");
  PROGMEM Language_Str MSG_CONTROL_RETRACT_RECOVER_SWAP    = _UxGT("Va. UnRet mm");
  PROGMEM Language_Str MSG_CONTROL_RETRACT_RECOVERF        = _UxGT("UnRet  V");
=======
  PROGMEM Language_Str MSG_CONTROL_RETRACT_RECOVER         = _UxGT("Unretr. mm");
  PROGMEM Language_Str MSG_CONTROL_RETRACT_RECOVER_SWAP    = _UxGT("Va. Unretr. mm");
  PROGMEM Language_Str MSG_CONTROL_RETRACT_RECOVERF        = _UxGT("Unretract V");
>>>>>>> mcu_ctrl
  PROGMEM Language_Str MSG_AUTORETRACT                     = _UxGT("AutoVeto.");
  PROGMEM Language_Str MSG_DELTA_CALIBRATE                 = _UxGT("Delta Kalibrointi");
  PROGMEM Language_Str MSG_DELTA_CALIBRATE_X               = _UxGT("Kalibroi X");
  PROGMEM Language_Str MSG_DELTA_CALIBRATE_Y               = _UxGT("Kalibroi Y");
  PROGMEM Language_Str MSG_DELTA_CALIBRATE_Z               = _UxGT("Kalibroi Z");
  PROGMEM Language_Str MSG_DELTA_CALIBRATE_CENTER          = _UxGT("Kalibroi Center");

<<<<<<< HEAD
  PROGMEM Language_Str MSG_EXPECTED_PRINTER                = _UxGT("V????r?? tulostin");
=======
  PROGMEM Language_Str MSG_KILL_EXPECTED_PRINTER           = _UxGT("V????r?? tulostin");
>>>>>>> mcu_ctrl
}
