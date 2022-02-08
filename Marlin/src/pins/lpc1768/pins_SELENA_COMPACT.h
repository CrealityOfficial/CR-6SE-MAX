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
 * Selena Compact pin assignments
 */

<<<<<<< HEAD
#ifndef MCU_LPC1768
  #error "Oops! Make sure you have the LPC1768 environment selected in your IDE."
#endif
=======
#include "env_validate.h"
>>>>>>> mcu_ctrl

#define BOARD_INFO_NAME   "Selena Compact"
#define BOARD_WEBSITE_URL "github.com/Ales2-k/Selena"

//
// Servos
//
<<<<<<< HEAD
#define SERVO0_PIN        P1_23
=======
#define SERVO0_PIN                         P1_23
>>>>>>> mcu_ctrl

//
// Limit Switches
//
<<<<<<< HEAD
#define X_MIN_PIN          P1_28
#define X_MAX_PIN          P1_25
#define Y_MIN_PIN          P2_11
#define Y_MAX_PIN          -1
#define Z_MIN_PIN          P1_27
#define Z_MAX_PIN          -1
#define Z_PROBE            P1_22
=======
#define X_MIN_PIN                          P1_28
#define X_MAX_PIN                          P1_25
#define Y_MIN_PIN                          P2_11
#define Y_MAX_PIN                          -1
#define Z_MIN_PIN                          P1_27
#define Z_MAX_PIN                          -1
#ifndef Z_MIN_PROBE_PIN
  #define Z_MIN_PROBE_PIN                  P1_22
#endif
>>>>>>> mcu_ctrl

//
// Steppers
//
<<<<<<< HEAD
#define X_STEP_PIN         P2_00
#define X_DIR_PIN          P0_05
#define X_ENABLE_PIN       P0_04

#define Y_STEP_PIN         P2_01
#define Y_DIR_PIN          P0_11
#define Y_ENABLE_PIN       P0_10

#define Z_STEP_PIN         P2_02
#define Z_DIR_PIN          P0_20
#define Z_ENABLE_PIN       P0_19

#define E0_STEP_PIN        P2_03
#define E0_DIR_PIN         P0_22
#define E0_ENABLE_PIN      P0_21

#define E1_STEP_PIN        P2_08
#define E1_DIR_PIN         P2_13
#define E1_ENABLE_PIN      P4_29
=======
#define X_STEP_PIN                         P2_00
#define X_DIR_PIN                          P0_05
#define X_ENABLE_PIN                       P0_04

#define Y_STEP_PIN                         P2_01
#define Y_DIR_PIN                          P0_11
#define Y_ENABLE_PIN                       P0_10

#define Z_STEP_PIN                         P2_02
#define Z_DIR_PIN                          P0_20
#define Z_ENABLE_PIN                       P0_19

#define E0_STEP_PIN                        P2_03
#define E0_DIR_PIN                         P0_22
#define E0_ENABLE_PIN                      P0_21

#define E1_STEP_PIN                        P2_08
#define E1_DIR_PIN                         P2_13
#define E1_ENABLE_PIN                      P4_29
>>>>>>> mcu_ctrl

//
// Temperature Sensors
// 3.3V max when defined as an analog input
//
<<<<<<< HEAD
#define TEMP_BED_PIN        P0_23_A0   // A0 (TH1)
#define TEMP_0_PIN          P0_24_A1   // A1 (TH2)
#define TEMP_1_PIN          P0_25_A2   // A2 (TH3)

=======
#define TEMP_BED_PIN                    P0_23_A0  // A0 (TH1)
#define TEMP_0_PIN                      P0_24_A1  // A1 (TH2)
#define TEMP_1_PIN                      P0_25_A2  // A2 (TH3)
>>>>>>> mcu_ctrl

//
// Heaters / Fans
//

<<<<<<< HEAD
#define HEATER_BED_PIN     P2_05
#define HEATER_BED2_PIN    P2_04
#define HEATER_0_PIN       P2_07
#define HEATER_1_PIN       P2_06
#ifndef FAN_PIN
  #define FAN_PIN          P1_24
#endif
#define FAN1_PIN           P1_26
=======
#define HEATER_BED_PIN                     P2_05
#define HEATER_BED2_PIN                    P2_04
#define HEATER_0_PIN                       P2_07
#define HEATER_1_PIN                       P2_06
#ifndef FAN_PIN
  #define FAN_PIN                          P1_24
#endif
#define FAN1_PIN                           P1_26
>>>>>>> mcu_ctrl

//
// Display
//

<<<<<<< HEAD
#if ENABLED(REPRAP_DISCOUNT_FULL_GRAPHIC_SMART_CONTROLLER)
    #define LCD_PINS_RS         P0_16
    #define LCD_PINS_ENABLE     P0_18
    #define LCD_PINS_D4         P0_15
    #define LCD_PINS_D5         P1_00
    #define LCD_PINS_D6         P1_01
    #define LCD_PINS_D7         P1_04
    #define BEEPER_PIN          P1_31

    #define BTN_EN1             P3_25
    #define BTN_EN2             P3_26
    #define BTN_ENC             P1_30

    #define SD_DETECT_PIN       -1
#endif // REPRAP_DISCOUNT_FULL_GRAPHIC_SMART_CONTROLLER
=======
#if IS_RRD_FG_SC
  #define LCD_PINS_RS                      P0_16
  #define LCD_PINS_ENABLE                  P0_18
  #define LCD_PINS_D4                      P0_15
  #define LCD_PINS_D5                      P1_00
  #define LCD_PINS_D6                      P1_01
  #define LCD_PINS_D7                      P1_04
  #define BEEPER_PIN                       P1_31

  #define BTN_EN1                          P3_25
  #define BTN_EN2                          P3_26
  #define BTN_ENC                          P1_30

  #define SD_DETECT_PIN                    -1

  #if ENABLED(REPRAP_DISCOUNT_FULL_GRAPHIC_SMART_CONTROLLER)
    #define BTN_ENC_EN               LCD_PINS_D7  // Detect the presence of the encoder
  #endif

#endif // IS_RRD_FG_SC
>>>>>>> mcu_ctrl
