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
 * MKS SGEN-L pin assignments
 */

<<<<<<< HEAD
#ifndef MCU_LPC1768
  #error "Oops! Make sure you have the LPC1768 environment selected in your IDE."
#endif
=======
#include "env_validate.h"
>>>>>>> mcu_ctrl

#define BOARD_INFO_NAME   "MKS SGen-L"
#define BOARD_WEBSITE_URL "github.com/makerbase-mks/MKS-SGEN_L"

//
// Servos
//
<<<<<<< HEAD
#define SERVO0_PIN         P1_23   // SERVO P1.23
#define SERVO1_PIN         P2_00   // SERVO P2.0
=======
#define SERVO0_PIN                         P1_23  // SERVO P1.23
#define SERVO1_PIN                         P2_00  // SERVO P2.0

//
// Trinamic Stallguard pins
//
#define X_DIAG_PIN                         P1_29  // X-
#define Y_DIAG_PIN                         P1_27  // Y-
#define Z_DIAG_PIN                         P1_25  // Z-
#define E0_DIAG_PIN                        P1_28  // X+
#define E1_DIAG_PIN                        P1_26  // Y+
>>>>>>> mcu_ctrl

//
// Limit Switches
//
<<<<<<< HEAD
#define X_MIN_PIN          P1_29
#define X_MAX_PIN          P1_28
#define Y_MIN_PIN          P1_27
#define Y_MAX_PIN          P1_26
#define Z_MIN_PIN          P1_25
#define Z_MAX_PIN          P1_24
=======
#ifdef X_STALL_SENSITIVITY
  #define X_STOP_PIN                  X_DIAG_PIN
  #if X_HOME_TO_MIN
    #define X_MAX_PIN                      P1_28  // X+
  #else
    #define X_MIN_PIN                      P1_28  // X+
  #endif
#else
  #define X_MIN_PIN                        P1_29  // X-
  #define X_MAX_PIN                        P1_28  // X+
#endif

#ifdef Y_STALL_SENSITIVITY
  #define Y_STOP_PIN                  Y_DIAG_PIN
  #if Y_HOME_TO_MIN
    #define Y_MAX_PIN                      P1_26  // Y+
  #else
    #define Y_MIN_PIN                      P1_26  // Y+
  #endif
#else
  #define Y_MIN_PIN                        P1_27  // Y-
  #define Y_MAX_PIN                        P1_26  // Y+
#endif

#ifdef Z_STALL_SENSITIVITY
  #define Z_STOP_PIN                  Z_DIAG_PIN
  #if Z_HOME_TO_MIN
    #define Z_MAX_PIN                      P1_24  // Z+
  #else
    #define Z_MIN_PIN                      P1_24  // Z+
  #endif
#else
  #define Z_MIN_PIN                        P1_25  // Z-
  #define Z_MAX_PIN                        P1_24  // Z+
#endif
>>>>>>> mcu_ctrl

//
// Z Probe (when not Z_MIN_PIN)
//
#ifndef Z_MIN_PROBE_PIN
<<<<<<< HEAD
  #define Z_MIN_PROBE_PIN  P1_24
=======
  #define Z_MIN_PROBE_PIN                  P1_24
>>>>>>> mcu_ctrl
#endif

//
// Steppers
//
<<<<<<< HEAD
#define X_STEP_PIN         P2_02
#define X_DIR_PIN          P2_03
#define X_ENABLE_PIN       P2_01
#ifndef X_CS_PIN
  #define X_CS_PIN         P1_01
#endif

#define Y_STEP_PIN         P0_19
#define Y_DIR_PIN          P0_20
#define Y_ENABLE_PIN       P2_08
#ifndef Y_CS_PIN
  #define Y_CS_PIN         P1_08
#endif

#define Z_STEP_PIN         P0_22
#define Z_DIR_PIN          P2_11
#define Z_ENABLE_PIN       P0_21
#ifndef Z_CS_PIN
  #define Z_CS_PIN         P1_10
#endif

#define E0_STEP_PIN        P2_13
#define E0_DIR_PIN         P0_11
#define E0_ENABLE_PIN      P2_12
#ifndef E0_CS_PIN
  #define E0_CS_PIN        P1_15
#endif

#define E1_STEP_PIN        P0_01
#define E1_DIR_PIN         P0_00
#define E1_ENABLE_PIN      P0_10
#ifndef E1_CS_PIN
  #define E1_CS_PIN        P1_17
=======
#define X_STEP_PIN                         P2_02
#define X_DIR_PIN                          P2_03
#define X_ENABLE_PIN                       P2_01
#ifndef X_CS_PIN
  #define X_CS_PIN                         P1_01
#endif

#define Y_STEP_PIN                         P0_19
#define Y_DIR_PIN                          P0_20
#define Y_ENABLE_PIN                       P2_08
#ifndef Y_CS_PIN
  #define Y_CS_PIN                         P1_08
#endif

#define Z_STEP_PIN                         P0_22
#define Z_DIR_PIN                          P2_11
#define Z_ENABLE_PIN                       P0_21
#ifndef Z_CS_PIN
  #define Z_CS_PIN                         P1_10
#endif

#define E0_STEP_PIN                        P2_13
#define E0_DIR_PIN                         P0_11
#define E0_ENABLE_PIN                      P2_12
#ifndef E0_CS_PIN
  #define E0_CS_PIN                        P1_15
#endif

#define E1_STEP_PIN                        P0_01
#define E1_DIR_PIN                         P0_00
#define E1_ENABLE_PIN                      P0_10
#ifndef E1_CS_PIN
  #define E1_CS_PIN                        P1_17
>>>>>>> mcu_ctrl
#endif

//
// Software SPI pins for TMC2130 stepper drivers
//
#if ENABLED(TMC_USE_SW_SPI)
  #ifndef TMC_SW_MOSI
<<<<<<< HEAD
    #define TMC_SW_MOSI    P4_28
  #endif
  #ifndef TMC_SW_MISO
    #define TMC_SW_MISO    P0_05
  #endif
  #ifndef TMC_SW_SCK
    #define TMC_SW_SCK     P0_04
  #endif
#endif

#if HAS_TMC220x
=======
    #define TMC_SW_MOSI                    P4_28
  #endif
  #ifndef TMC_SW_MISO
    #define TMC_SW_MISO                    P0_05
  #endif
  #ifndef TMC_SW_SCK
    #define TMC_SW_SCK                     P0_04
  #endif
#endif

#if HAS_TMC_UART
>>>>>>> mcu_ctrl
  /**
   * TMC2208/TMC2209 stepper drivers
   *
   * Hardware serial communication ports.
   * If undefined software serial is used according to the pins below
   */
<<<<<<< HEAD
  //#define X_HARDWARE_SERIAL  Serial
=======
  //#define X_HARDWARE_SERIAL  Serial1
>>>>>>> mcu_ctrl
  //#define X2_HARDWARE_SERIAL Serial1
  //#define Y_HARDWARE_SERIAL  Serial1
  //#define Y2_HARDWARE_SERIAL Serial1
  //#define Z_HARDWARE_SERIAL  Serial1
  //#define Z2_HARDWARE_SERIAL Serial1
  //#define E0_HARDWARE_SERIAL Serial1
  //#define E1_HARDWARE_SERIAL Serial1
  //#define E2_HARDWARE_SERIAL Serial1
  //#define E3_HARDWARE_SERIAL Serial1
  //#define E4_HARDWARE_SERIAL Serial1

  //
  // Software serial
  //

<<<<<<< HEAD
  #define X_SERIAL_TX_PIN  P1_04
  #define X_SERIAL_RX_PIN  P1_01

  #define Y_SERIAL_TX_PIN  P1_09
  #define Y_SERIAL_RX_PIN  P1_08

  #define Z_SERIAL_TX_PIN  P1_14
  #define Z_SERIAL_RX_PIN  P1_10

  #define E0_SERIAL_TX_PIN P1_16
  #define E0_SERIAL_RX_PIN P1_15

  #define E1_SERIAL_TX_PIN P4_29
  #define E1_SERIAL_RX_PIN P1_17

  #define Z2_SERIAL_TX_PIN P4_29
  #define Z2_SERIAL_RX_PIN P1_17

  // Reduce baud rate to improve software serial reliability
  #define TMC_BAUD_RATE 19200
#endif // TMC2208 || TMC2209
=======
  #define X_SERIAL_TX_PIN                  P1_04
  #define X_SERIAL_RX_PIN                  P1_01

  #define Y_SERIAL_TX_PIN                  P1_09
  #define Y_SERIAL_RX_PIN                  P1_08

  #define Z_SERIAL_TX_PIN                  P1_14
  #define Z_SERIAL_RX_PIN                  P1_10

  #define E0_SERIAL_TX_PIN                 P1_16
  #define E0_SERIAL_RX_PIN                 P1_15

  #define E1_SERIAL_TX_PIN                 P4_29
  #define E1_SERIAL_RX_PIN                 P1_17

  #define Z2_SERIAL_TX_PIN                 P4_29
  #define Z2_SERIAL_RX_PIN                 P1_17

  // Reduce baud rate to improve software serial reliability
  #define TMC_BAUD_RATE                    19200
#endif // HAS_TMC_UART
>>>>>>> mcu_ctrl

//
// Temperature Sensors
// 3.3V max when defined as an analog input
//
<<<<<<< HEAD
#define TEMP_0_PIN         P0_23_A0   // Analog Input A0 (TH1)
#define TEMP_BED_PIN       P0_24_A1   // Analog Input A1 (TB)
#define TEMP_1_PIN         P0_25_A2   // Analog Input A2 (TH2)
=======
#define TEMP_0_PIN                      P0_23_A0  // Analog Input A0 (TH1)
#define TEMP_BED_PIN                    P0_24_A1  // Analog Input A1 (TB)
#define TEMP_1_PIN                      P0_25_A2  // Analog Input A2 (TH2)
>>>>>>> mcu_ctrl

//
// Heaters / Fans
//
<<<<<<< HEAD
#define HEATER_BED_PIN     P2_05
#define HEATER_0_PIN       P2_07
#define HEATER_1_PIN       P2_06
#ifndef FAN_PIN
  #define FAN_PIN          P2_04
=======
#define HEATER_BED_PIN                     P2_05
#define HEATER_0_PIN                       P2_07
#if HOTENDS == 1
  #ifndef FAN1_PIN
    #define FAN1_PIN                       P2_06
  #endif
#else
  #ifndef HEATER_1_PIN
    #define HEATER_1_PIN                   P2_06
  #endif
#endif
#ifndef FAN_PIN
  #define FAN_PIN                          P2_04
>>>>>>> mcu_ctrl
#endif

//
// Misc. Functions
//
<<<<<<< HEAD
#define LED_PIN            P1_18   // Used as a status indicator
#define LED2_PIN           P1_19
#define LED3_PIN           P1_20
#define LED4_PIN           P1_21
=======
#define LED_PIN                            P1_18  // Used as a status indicator
#define LED2_PIN                           P1_19
#define LED3_PIN                           P1_20
#define LED4_PIN                           P1_21
>>>>>>> mcu_ctrl

/**
 *                _____                                            _____
 * (BEEPER) 1.31 | · · | 1.30 (BTN_ENC)          (MISO)       0.8 | · · | 0.7  (SD_SCK)
 * (LCD_EN) 0.18 | · · | 0.16 (LCD_RS)           (BTN_EN1)   3.25 | · · | 0.28 (SD_CS2)
<<<<<<< HEAD
 * (LCD_D4) 0.15 | · · | 0.17 (LCD_D5)           (BTN_EN2)   3.26 | · · | 1.20 (SD_MOSI)
=======
 * (LCD_D4) 0.15 | · ·   0.17 (LCD_D5)           (BTN_EN2)   3.26 | · ·   0.9  (SD_MOSI)
>>>>>>> mcu_ctrl
 * (LCD_D6)  1.0 | · · | 1.22 (LCD_D7)           (SD_DETECT) 0.27 | · · | RST
 *           GND | · · | 5V                                   GND | · · | NC
 *                -----                                            -----
 *                EXP1                                             EXP2
 */
<<<<<<< HEAD
#if HAS_SPI_LCD
  #define BEEPER_PIN       P1_31
  #define BTN_ENC          P1_30

  #if ENABLED(CR10_STOCKDISPLAY)
    #define LCD_PINS_RS    P1_00

    #define BTN_EN1        P0_18
    #define BTN_EN2        P0_15

    #define LCD_PINS_ENABLE P1_22
    #define LCD_PINS_D4    P0_17

  #else
    #define LCD_PINS_RS    P0_16

    #define BTN_EN1        P3_25
    #define BTN_EN2        P3_26

    #define LCD_PINS_ENABLE P0_18
    #define LCD_PINS_D4    P0_15

    #define LCD_SDSS       P0_28
    #define SD_DETECT_PIN  P0_27

    #if ENABLED(FYSETC_MINI_12864)
      #define DOGLCD_CS    P0_18
      #define DOGLCD_A0    P0_16
      #define DOGLCD_SCK   P0_07
      #define DOGLCD_MOSI  P1_20

      #define LCD_BACKLIGHT_PIN -1

      #define FORCE_SOFT_SPI      // Use this if default of hardware SPI causes display problems
                                  //   results in LCD soft SPI mode 3, SD soft SPI mode 0

      #define LCD_RESET_PIN P0_15   // Must be high or open for LCD to operate normally.

      #if EITHER(FYSETC_MINI_12864_1_2, FYSETC_MINI_12864_2_0)
        #ifndef RGB_LED_R_PIN
          #define RGB_LED_R_PIN P0_17
        #endif
        #ifndef RGB_LED_G_PIN
          #define RGB_LED_G_PIN P1_00
        #endif
        #ifndef RGB_LED_B_PIN
          #define RGB_LED_B_PIN P1_22
        #endif
      #elif ENABLED(FYSETC_MINI_12864_2_1)
        #define NEOPIXEL_PIN    P0_17
      #endif

    #else // !FYSETC_MINI_12864

      #if ENABLED(MKS_MINI_12864)
        #define DOGLCD_CS  P0_17
        #define DOGLCD_A0  P1_00
      #endif

      #if ENABLED(ULTIPANEL)
        #define LCD_PINS_D5 P0_17
        #define LCD_PINS_D6 P1_00
        #define LCD_PINS_D7 P1_22
      #endif

    #endif // !FYSETC_MINI_12864

  #endif

#endif // HAS_SPI_LCD

#ifndef SDCARD_CONNECTION
  #define SDCARD_CONNECTION ONBOARD
#endif

#define ONBOARD_SD_CS_PIN  P0_06   // Chip select for "System" SD card

#if SD_CONNECTION_IS(LCD)
  #define SCK_PIN          P0_07
  #define MISO_PIN         P0_08
  #define MOSI_PIN         P0_09
  #define SS_PIN           P0_28
#elif SD_CONNECTION_IS(ONBOARD)
  #define SD_DETECT_PIN    P0_27
  #define SCK_PIN          P0_07
  #define MISO_PIN         P0_08
  #define MOSI_PIN         P0_09
  #define SS_PIN           ONBOARD_SD_CS_PIN
=======
#if HAS_WIRED_LCD

  #define BEEPER_PIN                       P1_31
  #define BTN_ENC                          P1_30

  #if ENABLED(CR10_STOCKDISPLAY)
    #define LCD_PINS_RS                    P1_00

    #define BTN_EN1                        P0_18
    #define BTN_EN2                        P0_15

    #define LCD_PINS_ENABLE                P1_22
    #define LCD_PINS_D4                    P0_17

  #elif HAS_SPI_TFT                               // Config for Classic UI (emulated DOGM) and Color UI
    #define TFT_CS_PIN                     P1_00
    #define TFT_A0_PIN                     P1_22
    #define TFT_DC_PIN                     P1_22
    #define TFT_MISO_PIN                   P0_08
    #define TFT_BACKLIGHT_PIN              P0_18
    #define TFT_RESET_PIN                  P0_16

    #define LCD_USE_DMA_SPI

    #define TOUCH_INT_PIN                  P0_17
    #define TOUCH_CS_PIN                   P0_15
    #define TOUCH_BUTTONS_HW_SPI
    #define TOUCH_BUTTONS_HW_SPI_DEVICE        2

    // Disable any LCD related PINs config
    #define LCD_PINS_ENABLE                -1
    #define LCD_PINS_RS                    -1

    #ifndef TFT_BUFFER_SIZE
      #define TFT_BUFFER_SIZE               1200
    #endif
    #ifndef TFT_QUEUE_SIZE
      #define TFT_QUEUE_SIZE                6144
    #endif

    #define BTN_EN1                        P3_25
    #define BTN_EN2                        P3_26

  #elif IS_TFTGLCD_PANEL

    #undef BEEPER_PIN
    #undef BTN_ENC

    #if ENABLED(TFTGLCD_PANEL_SPI)
      #define TFTGLCD_CS                   P3_25
    #endif

  #else

    #define BTN_EN1                        P3_25
    #define BTN_EN2                        P3_26

    #define LCD_SDSS                       P0_28

    #if ENABLED(MKS_12864OLED_SSD1306)

      #define LCD_PINS_DC                  P0_17
      #define DOGLCD_CS                    P0_16
      #define DOGLCD_A0              LCD_PINS_DC
      #define DOGLCD_SCK                   P0_15
      #define DOGLCD_MOSI                  P0_18

      #define LCD_PINS_RS                  P1_00
      #define LCD_PINS_D7                  P1_22
      #define KILL_PIN                     -1     // NC

    #else                                         // !MKS_12864OLED_SSD1306

      #define LCD_PINS_RS                  P0_16

      #define LCD_PINS_ENABLE              P0_18
      #define LCD_PINS_D4                  P0_15

      #if ENABLED(FYSETC_MINI_12864)

        #define DOGLCD_CS                  P0_18
        #define DOGLCD_A0                  P0_16
        #define DOGLCD_SCK                 P0_07
        #define DOGLCD_MOSI                P0_09

        #define LCD_BACKLIGHT_PIN          -1

        #define FORCE_SOFT_SPI                    // Use this if default of hardware SPI causes display problems
                                                  //   results in LCD soft SPI mode 3, SD soft SPI mode 0

        #define LCD_RESET_PIN              P0_15  // Must be high or open for LCD to operate normally.

        #if EITHER(FYSETC_MINI_12864_1_2, FYSETC_MINI_12864_2_0)
          #ifndef RGB_LED_R_PIN
            #define RGB_LED_R_PIN          P0_17
          #endif
          #ifndef RGB_LED_G_PIN
            #define RGB_LED_G_PIN          P1_00
          #endif
          #ifndef RGB_LED_B_PIN
            #define RGB_LED_B_PIN          P1_22
          #endif
        #elif ENABLED(FYSETC_MINI_12864_2_1)
          #define NEOPIXEL_PIN             P0_17
        #endif

      #else                                       // !FYSETC_MINI_12864

        #if ENABLED(MKS_MINI_12864)
          #define DOGLCD_CS                P0_17
          #define DOGLCD_A0                P1_00
        #endif

        #if IS_ULTIPANEL
          #define LCD_PINS_D5              P0_17
          #define LCD_PINS_D6              P1_00
          #define LCD_PINS_D7              P1_22

          #if ENABLED(REPRAP_DISCOUNT_FULL_GRAPHIC_SMART_CONTROLLER)
            #define BTN_ENC_EN       LCD_PINS_D7  // Detect the presence of the encoder
          #endif

        #endif

      #endif // !FYSETC_MINI_12864

    #endif // !MKS_12864OLED_SSD1306

  #endif // !CR10_STOCKDISPLAY

#endif // HAS_WIRED_LCD

#ifndef SDCARD_CONNECTION
  #define SDCARD_CONNECTION              ONBOARD
#endif

#define ONBOARD_SD_CS_PIN                  P0_06  // Chip select for "System" SD card

#if SD_CONNECTION_IS(LCD) || SD_CONNECTION_IS(ONBOARD)
  #define SD_DETECT_PIN                    P0_27
  #define SD_SCK_PIN                       P0_07
  #define SD_MISO_PIN                      P0_08
  #define SD_MOSI_PIN                      P0_09
  #if SD_CONNECTION_IS(ONBOARD)
    #define SD_SS_PIN          ONBOARD_SD_CS_PIN
  #else
    #define SD_SS_PIN                      P0_28
  #endif
>>>>>>> mcu_ctrl
#elif SD_CONNECTION_IS(CUSTOM_CABLE)
  #error "No custom SD drive cable defined for this board."
#endif

//
// Other Pins
//
<<<<<<< HEAD
//#define PIN_P0_02          P0_02   // AUX1 (Interrupt Capable/ADC/Serial Port 0)
//#define PIN_P0_03          P0_03   // AUX1 (Interrupt Capable/ADC/Serial Port 0)
//#define PS_ON_PIN          P1_23   // SERVO P1.23
=======
//#define PIN_P0_02                        P0_02  // AUX1 (Interrupt Capable/ADC/Serial Port 0)
//#define PIN_P0_03                        P0_03  // AUX1 (Interrupt Capable/ADC/Serial Port 0)
//#define PS_ON_PIN                        P1_23  // SERVO P1.23
>>>>>>> mcu_ctrl
