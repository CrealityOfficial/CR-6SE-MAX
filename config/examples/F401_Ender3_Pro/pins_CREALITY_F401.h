/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

// Source: 

/**
 * HOW TO COMPILE
 *
 * PlatformIO - Use the STM32F107VC environment (or the "Auto Build Marlin" extension).
 */

#pragma once

#if NOT_TARGET(STM32F4)
  #error "Oops! Select an STM32F1 board in 'Tools > Board.'"
#endif

#ifndef BOARD_INFO_NAME
  #define BOARD_INFO_NAME      "Creality 3D V6.0.2"
#endif

#ifndef DEFAULT_MACHINE_NAME
  #define DEFAULT_MACHINE_NAME "SERMOON V2"
#endif

//
// Limit Switches
//
#define X_MIN_PIN                             PE9//-1
#define Y_MIN_PIN                             PE10//-1

#ifdef BLTOUCH
  #define Z_MIN_PIN                           PD13  // BLTouch IN
#else
  #define Z_MIN_PIN                           PE12//PB0
#endif

#define X_MAX_PIN                             PE9
#define Y_MAX_PIN                             PE10
#define Z_MAX_PIN                             PE12//PE11
// #define Z2_MAX_PIN                            PE12
//
// Servos
//
#ifdef BLTOUCH
  #define SERVO0_PIN                          PD12   // BLTouch OUT
#endif

//
// Z Probe (when not Z_MIN_PIN)
//
//#ifndef Z_MIN_PROBE_PIN
//  #define Z_MIN_PROBE_PIN  Z_MIN_PIN
//#endif

//
// Filament runout
//
#ifndef FIL_RUNOUT_PIN
  #define FIL_RUNOUT_PIN                      PB2  // BED_THE
#endif

//
// Steppers
//
#define STEPPER_DRIVER_POWER_PIN                   PE13 // 电机驱动芯片电源控制

#define X_STEP_PIN                            PB9//PB6//
#define X_DIR_PIN                             PC13
#define X_ENABLE_PIN                          PD7

#define Y_STEP_PIN                            PB8
#define Y_DIR_PIN                             PE6
#define Y_ENABLE_PIN                          PD7

#define Z_STEP_PIN                            PB7
#define Z_DIR_PIN                             PE5
#define Z_ENABLE_PIN                          PD7

// #define Z1_STEP_PIN                           PB6
// #define Z1_DIR_PIN                            PE4
// #define Z1_ENABLE_PIN                         PD7

#define E0_STEP_PIN                           PB5
#define E0_DIR_PIN                            PE3
#define E0_ENABLE_PIN                         PD7

#define E1_STEP_PIN                           PB4
#define E1_DIR_PIN                            PE2
#define E1_ENABLE_PIN                         PD7


//
// Temperature Sensors
//
#ifndef TEMP_0_PIN
  #define TEMP_0_PIN                           PC1  // E1_THERMISTOR PA0 -> PT100
#endif
#define TEMP_1_PIN                             PC0  // E2_THERMISTOR
#define TEMP_2_PIN                             PC2  // 
#define TEMP_3_PIN                             PC3  // 
#define TEMP_BED_PIN                           PC4  // BED_THERMISTOR_1

//
// Heaters / Fans
//
#define HEATER_0_PIN                           PD14  // E1_HEAT_PWM
#define HEATER_1_PIN                           PD15  // E2_HEAT_PWM
#define HEATER_BED_PIN                         PA7  // BED_HEAT_1 FET

#define FAN_PIN                                PA2   // Part cooling fan FET
// #define FAN1_PIN                              PE11  // Extruder fan FET
// #define FAN2_PIN                              PE1   // Controller fan FET

#ifndef E0_AUTO_FAN_PIN
  #define E0_AUTO_FAN_PIN                     PA1  // FAN1_PIN
#endif

#ifdef HAS_MENU_RESET_WIFI
  #define RESET_WIFI_PIN                   PB13
#endif

#define LED_CONTROL_PIN                     PA5
#define BOX_FAN_PIN                         PA1

// SPI Flash
// #define HAS_SPI_FLASH                          1
#if HAS_SPI_FLASH
  #define SPI_FLASH_SIZE                0x1000000  // 16MB
#endif

// SPI 2
#define W25QXX_CS_PIN                       PB12
// 当前HAL/STM32的MOSI, MISO, SCK不由下面引脚定义，
// 需在buildroot\share\PlatformIO\variants\CREALITY_F107\variant.h中修改
#define W25QXX_MOSI_PIN                     PB15
#define W25QXX_MISO_PIN                     PB14
#define W25QXX_SCK_PIN                      PB13

// #define SPI_FLASH_EEPROM_EMULATION

#define IIC_BL24CXX_EEPROM                      // EEPROM on I2C-0 used only for display settings
#if ENABLED(IIC_BL24CXX_EEPROM)
  #define IIC_EEPROM_SDA                  PB3
  #define IIC_EEPROM_SCL                  PD3
  #define MARLIN_EEPROM_SIZE             0x800  // 2Kb (24C16)
#else
  #define SDCARD_EEPROM_EMULATION               // SD EEPROM until all EEPROM is BL24CXX
  #define MARLIN_EEPROM_SIZE             0x800  // 2Kb
#endif
//
// USB Disk support
//
#define HAS_OTG_USB_HOST_SUPPORT

//
// Misc functions
//
#define SDSS                                  -1  // SPI_CS
#define LED_PIN                               -1  // green LED   Heart beat
#define PS_ON_PIN                             -1
#define KILL_PIN                              -1
#define POWER_LOSS_PIN                        -1  // PWR_LOSS / nAC_FAULT

