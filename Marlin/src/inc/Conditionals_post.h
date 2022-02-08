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
 * Conditionals_post.h
 * Defines that depend on configuration but are not editable.
 */

<<<<<<< HEAD
#define AVR_ATmega2560_FAMILY_PLUS_70 ( \
     MB(BQ_ZUM_MEGA_3D)                 \
  || MB(MIGHTYBOARD_REVE)               \
  || MB(MINIRAMBO)                      \
  || MB(SCOOVO_X9H)                     \
)
=======
#ifdef GITHUB_ACTIONS
  // Extras for CI testing
#endif

// ADC
#ifdef BOARD_ADC_VREF
  #define ADC_VREF BOARD_ADC_VREF
#else
  #define ADC_VREF HAL_ADC_VREF
#endif

// Linear advance uses Jerk since E is an isolated axis
#if BOTH(HAS_JUNCTION_DEVIATION, LIN_ADVANCE)
  #define HAS_LINEAR_E_JERK 1
#endif

// Determine which type of 'EEPROM' is in use
#if ENABLED(EEPROM_SETTINGS)
  // EEPROM type may be defined by compile flags, configs, HALs, or pins
  // Set additional flags to let HALs choose in their Conditionals_post.h
  #if ANY(FLASH_EEPROM_EMULATION, SRAM_EEPROM_EMULATION, SDCARD_EEPROM_EMULATION, QSPI_EEPROM)
    #define USE_EMULATED_EEPROM 1
  #elif ANY(I2C_EEPROM, SPI_EEPROM)
    #define USE_WIRED_EEPROM    1
  #elif ENABLED(IIC_BL24CXX_EEPROM)
    // nothing
  #else
    #define USE_FALLBACK_EEPROM 1
  #endif
#else
  #undef I2C_EEPROM
  #undef SPI_EEPROM
  #undef QSPI_EEPROM
  #undef SDCARD_EEPROM_EMULATION
  #undef SRAM_EEPROM_EMULATION
  #undef FLASH_EEPROM_EMULATION
  #undef IIC_BL24CXX_EEPROM
#endif
>>>>>>> mcu_ctrl

#ifdef TEENSYDUINO
  #undef max
  #define max(a,b) ((a)>(b)?(a):(b))
  #undef min
  #define min(a,b) ((a)<(b)?(a):(b))

  #undef NOT_A_PIN    // Override Teensyduino legacy CapSense define work-around
  #define NOT_A_PIN 0 // For PINS_DEBUGGING
#endif

<<<<<<< HEAD
#define HAS_CLASSIC_JERK (ENABLED(CLASSIC_JERK) || IS_KINEMATIC)
#define HAS_CLASSIC_E_JERK (ENABLED(CLASSIC_JERK) || DISABLED(LIN_ADVANCE))

=======
>>>>>>> mcu_ctrl
/**
 * Axis lengths and center
 */
#define X_MAX_LENGTH (X_MAX_POS - (X_MIN_POS))
#define Y_MAX_LENGTH (Y_MAX_POS - (Y_MIN_POS))
#define Z_MAX_LENGTH (Z_MAX_POS - (Z_MIN_POS))

// Defined only if the sanity-check is bypassed
#ifndef X_BED_SIZE
  #define X_BED_SIZE X_MAX_LENGTH
#endif
#ifndef Y_BED_SIZE
  #define Y_BED_SIZE Y_MAX_LENGTH
#endif

// Require 0,0 bed center for Delta and SCARA
#if IS_KINEMATIC
  #define BED_CENTER_AT_0_0
#endif

// Define center values for future use
#define _X_HALF_BED ((X_BED_SIZE) / 2)
#define _Y_HALF_BED ((Y_BED_SIZE) / 2)
<<<<<<< HEAD
#if ENABLED(BED_CENTER_AT_0_0)
  #define X_CENTER 0
  #define Y_CENTER 0
#else
  #define X_CENTER _X_HALF_BED
  #define Y_CENTER _Y_HALF_BED
#endif
=======
#define X_CENTER TERN(BED_CENTER_AT_0_0, 0, _X_HALF_BED)
#define Y_CENTER TERN(BED_CENTER_AT_0_0, 0, _Y_HALF_BED)
#define XY_CENTER { X_CENTER, Y_CENTER }
>>>>>>> mcu_ctrl

// Get the linear boundaries of the bed
#define X_MIN_BED (X_CENTER - _X_HALF_BED)
#define X_MAX_BED (X_MIN_BED + X_BED_SIZE)
#define Y_MIN_BED (Y_CENTER - _Y_HALF_BED)
#define Y_MAX_BED (Y_MIN_BED + Y_BED_SIZE)

/**
 * Dual X Carriage
 */
#if ENABLED(DUAL_X_CARRIAGE)
  #ifndef X1_MIN_POS
    #define X1_MIN_POS X_MIN_POS
  #endif
  #ifndef X1_MAX_POS
    #define X1_MAX_POS X_BED_SIZE
  #endif
#endif

<<<<<<< HEAD
/**
 * CoreXY, CoreXZ, and CoreYZ - and their reverse
 */
#define CORE_IS_XY EITHER(COREXY, COREYX)
#define CORE_IS_XZ EITHER(COREXZ, COREZX)
#define CORE_IS_YZ EITHER(COREYZ, COREZY)
#define IS_CORE (CORE_IS_XY || CORE_IS_XZ || CORE_IS_YZ)
#if IS_CORE
  #if CORE_IS_XY
    #define CORE_AXIS_1 A_AXIS
    #define CORE_AXIS_2 B_AXIS
    #define NORMAL_AXIS Z_AXIS
  #elif CORE_IS_XZ
    #define CORE_AXIS_1 A_AXIS
    #define NORMAL_AXIS Y_AXIS
    #define CORE_AXIS_2 C_AXIS
  #elif CORE_IS_YZ
    #define NORMAL_AXIS X_AXIS
    #define CORE_AXIS_1 B_AXIS
    #define CORE_AXIS_2 C_AXIS
  #endif
  #if ANY(COREYX, COREZX, COREZY)
    #define CORESIGN(n) (-(n))
  #else
    #define CORESIGN(n) (n)
  #endif
#endif
=======
// Calibration codes only for non-core axes
#if EITHER(BACKLASH_GCODE, CALIBRATION_GCODE)
  #if EITHER(IS_CORE, MARKFORGED_XY)
    #define CAN_CALIBRATE(A,B) (_AXIS(A) == B)
  #else
    #define CAN_CALIBRATE(A,B) true
  #endif
#endif
#define AXIS_CAN_CALIBRATE(A) CAN_CALIBRATE(A,NORMAL_AXIS)
>>>>>>> mcu_ctrl

/**
 * No adjustable bed on non-cartesians
 */
#if IS_KINEMATIC
  #undef LEVEL_BED_CORNERS
#endif

/**
 * SCARA cannot use SLOWDOWN and requires QUICKHOME
 * Printable radius assumes joints can fully extend
 */
#if IS_SCARA
  #undef SLOWDOWN
<<<<<<< HEAD
  #define QUICK_HOME
=======
  #if DISABLED(AXEL_TPARA)
    #define QUICK_HOME
  #endif
>>>>>>> mcu_ctrl
  #define SCARA_PRINTABLE_RADIUS (SCARA_LINKAGE_1 + SCARA_LINKAGE_2)
#endif

/**
 * Set the home position based on settings or manual overrides
 */
#ifdef MANUAL_X_HOME_POS
  #define X_HOME_POS MANUAL_X_HOME_POS
<<<<<<< HEAD
#elif ENABLED(BED_CENTER_AT_0_0)
  #if ENABLED(DELTA)
    #define X_HOME_POS 0
  #else
    #define X_HOME_POS (X_HOME_DIR < 0 ? X_MIN_POS : X_MAX_POS)
  #endif
#else
  #if ENABLED(DELTA)
    #define X_HOME_POS (X_MIN_POS + (X_BED_SIZE) * 0.5)
  #else
    #define X_HOME_POS (X_HOME_DIR < 0 ? X_MIN_POS : X_MAX_POS)
=======
#else
  #define X_END_POS TERN(X_HOME_TO_MIN, X_MIN_POS, X_MAX_POS)
  #if ENABLED(BED_CENTER_AT_0_0)
    #define X_HOME_POS TERN(DELTA, 0, X_END_POS)
  #else
    #define X_HOME_POS TERN(DELTA, X_MIN_POS + (X_BED_SIZE) * 0.5, X_END_POS)
>>>>>>> mcu_ctrl
  #endif
#endif

#ifdef MANUAL_Y_HOME_POS
  #define Y_HOME_POS MANUAL_Y_HOME_POS
<<<<<<< HEAD
#elif ENABLED(BED_CENTER_AT_0_0)
  #if ENABLED(DELTA)
    #define Y_HOME_POS 0
  #else
    #define Y_HOME_POS (Y_HOME_DIR < 0 ? Y_MIN_POS : Y_MAX_POS)
  #endif
#else
  #if ENABLED(DELTA)
    #define Y_HOME_POS (Y_MIN_POS + (Y_BED_SIZE) * 0.5)
  #else
    #define Y_HOME_POS (Y_HOME_DIR < 0 ? Y_MIN_POS : Y_MAX_POS)
=======
#else
  #define Y_END_POS TERN(Y_HOME_TO_MIN, Y_MIN_POS, Y_MAX_POS)
  #if ENABLED(BED_CENTER_AT_0_0)
    #define Y_HOME_POS TERN(DELTA, 0, Y_END_POS)
  #else
    #define Y_HOME_POS TERN(DELTA, Y_MIN_POS + (Y_BED_SIZE) * 0.5, Y_END_POS)
>>>>>>> mcu_ctrl
  #endif
#endif

#ifdef MANUAL_Z_HOME_POS
  #define Z_HOME_POS MANUAL_Z_HOME_POS
#else
<<<<<<< HEAD
  #define Z_HOME_POS (Z_HOME_DIR < 0 ? Z_MIN_POS : Z_MAX_POS)
=======
  #define Z_HOME_POS TERN(Z_HOME_TO_MIN, Z_MIN_POS, Z_MAX_POS)
>>>>>>> mcu_ctrl
#endif

/**
 * If DELTA_HEIGHT isn't defined use the old setting
 */
#if ENABLED(DELTA) && !defined(DELTA_HEIGHT)
  #define DELTA_HEIGHT Z_HOME_POS
#endif

/**
 * Z Sled Probe requires Z_SAFE_HOMING
 */
#if ENABLED(Z_PROBE_SLED)
  #define Z_SAFE_HOMING
#endif

/**
 * DELTA should ignore Z_SAFE_HOMING and SLOWDOWN
 */
#if ENABLED(DELTA)
  #undef Z_SAFE_HOMING
  #undef SLOWDOWN
#endif

#ifndef MESH_INSET
  #define MESH_INSET 0
#endif

/**
 * Safe Homing Options
 */
#if ENABLED(Z_SAFE_HOMING)
  #if ENABLED(AUTO_BED_LEVELING_UBL)
    // Home close to center so grid points have z heights very close to 0
    #define _SAFE_POINT(A) (((GRID_MAX_POINTS_##A) / 2) * (A##_BED_SIZE - 2 * (MESH_INSET)) / (GRID_MAX_POINTS_##A - 1) + MESH_INSET)
  #else
    #define _SAFE_POINT(A) A##_CENTER
  #endif
  #ifndef Z_SAFE_HOMING_X_POINT
    #define Z_SAFE_HOMING_X_POINT _SAFE_POINT(X)
  #endif
  #ifndef Z_SAFE_HOMING_Y_POINT
    #define Z_SAFE_HOMING_Y_POINT _SAFE_POINT(Y)
  #endif
#endif

<<<<<<< HEAD
=======
#ifdef GRID_MAX_POINTS_X
  #define GRID_MAX_CELLS_X (GRID_MAX_POINTS_X - 1)
  #define GRID_MAX_CELLS_Y (GRID_MAX_POINTS_Y - 1)
#endif

>>>>>>> mcu_ctrl
/**
 * Host keep alive
 */
#ifndef DEFAULT_KEEPALIVE_INTERVAL
  #define DEFAULT_KEEPALIVE_INTERVAL 2
#endif

/**
 * Provide a MAX_AUTORETRACT for older configs
 */
#if ENABLED(FWRETRACT) && !defined(MAX_AUTORETRACT)
  #define MAX_AUTORETRACT 99
#endif

/**
<<<<<<< HEAD
=======
 * Provide a DEFAULT_VOLUMETRIC_EXTRUDER_LIMIT in case NO_VOLUMETRICS is enabled
 */
#ifndef DEFAULT_VOLUMETRIC_EXTRUDER_LIMIT
  #define DEFAULT_VOLUMETRIC_EXTRUDER_LIMIT 0.00
#endif

/**
>>>>>>> mcu_ctrl
 * LCD Contrast for Graphical Displays
 */
#if ENABLED(CARTESIO_UI)
  #define _LCD_CONTRAST_MIN   60
  #define _LCD_CONTRAST_INIT  90
  #define _LCD_CONTRAST_MAX  140
#elif ENABLED(miniVIKI)
  #define _LCD_CONTRAST_MIN   75
  #define _LCD_CONTRAST_INIT  95
  #define _LCD_CONTRAST_MAX  115
#elif ENABLED(VIKI2)
  #define _LCD_CONTRAST_INIT 140
#elif ENABLED(ELB_FULL_GRAPHIC_CONTROLLER)
  #define _LCD_CONTRAST_MIN   90
  #define _LCD_CONTRAST_INIT 110
  #define _LCD_CONTRAST_MAX  130
#elif ENABLED(AZSMZ_12864)
  #define _LCD_CONTRAST_MIN  120
  #define _LCD_CONTRAST_INIT 190
<<<<<<< HEAD
#elif ENABLED(MKS_MINI_12864)
  #define _LCD_CONTRAST_MIN  120
  #define _LCD_CONTRAST_INIT 195
#elif ANY(FYSETC_MINI_12864_X_X, FYSETC_MINI_12864_1_2, FYSETC_MINI_12864_2_0, FYSETC_MINI_12864_2_1)
=======
#elif EITHER(MKS_LCD12864A, MKS_LCD12864B)
  #define _LCD_CONTRAST_MIN  120
  #define _LCD_CONTRAST_INIT 205
#elif EITHER(MKS_MINI_12864, ENDER2_STOCKDISPLAY)
  #define _LCD_CONTRAST_MIN  120
  #define _LCD_CONTRAST_INIT 195
#elif ENABLED(FYSETC_MINI_12864)
>>>>>>> mcu_ctrl
  #define _LCD_CONTRAST_INIT 220
#elif ENABLED(ULTI_CONTROLLER)
  #define _LCD_CONTRAST_INIT 127
  #define _LCD_CONTRAST_MAX  254
<<<<<<< HEAD
#elif EITHER(MAKRPANEL, MINIPANEL)
  #define _LCD_CONTRAST_INIT  17
#endif

#define HAS_LCD_CONTRAST defined(_LCD_CONTRAST_INIT)
=======
#elif ENABLED(MAKRPANEL)
  #define _LCD_CONTRAST_INIT  17
#elif ENABLED(MINIPANEL)
  #define _LCD_CONTRAST_INIT 150
#elif ENABLED(ZONESTAR_12864OLED)
  #define _LCD_CONTRAST_MIN   64
  #define _LCD_CONTRAST_INIT 128
  #define _LCD_CONTRAST_MAX  255
#elif IS_TFTGLCD_PANEL
  #define _LCD_CONTRAST_MIN    0
  #define _LCD_CONTRAST_INIT 250
  #define _LCD_CONTRAST_MAX  255
#endif

#ifdef _LCD_CONTRAST_INIT
  #define HAS_LCD_CONTRAST 1
#endif

>>>>>>> mcu_ctrl
#if HAS_LCD_CONTRAST
  #ifndef LCD_CONTRAST_MIN
    #ifdef _LCD_CONTRAST_MIN
      #define LCD_CONTRAST_MIN _LCD_CONTRAST_MIN
    #else
      #define LCD_CONTRAST_MIN 0
    #endif
  #endif
  #ifndef LCD_CONTRAST_INIT
    #define LCD_CONTRAST_INIT _LCD_CONTRAST_INIT
  #endif
  #ifndef LCD_CONTRAST_MAX
    #ifdef _LCD_CONTRAST_MAX
      #define LCD_CONTRAST_MAX _LCD_CONTRAST_MAX
    #elif _LCD_CONTRAST_INIT > 63
      #define LCD_CONTRAST_MAX 255
    #else
      #define LCD_CONTRAST_MAX 63   // ST7567 6-bits contrast
    #endif
  #endif
  #ifndef DEFAULT_LCD_CONTRAST
    #define DEFAULT_LCD_CONTRAST LCD_CONTRAST_INIT
  #endif
#endif

/**
<<<<<<< HEAD
 * Override here because this is set in Configuration_adv.h
 */
#if HAS_LCD_MENU && DISABLED(ELB_FULL_GRAPHIC_CONTROLLER)
  #undef SD_DETECT_INVERTED
=======
 * Override the SD_DETECT_STATE set in Configuration_adv.h
 * and enable sharing of onboard SD host drives (all platforms but AGCM4)
 */
#if ENABLED(SDSUPPORT)

  #if HAS_SD_HOST_DRIVE && SD_CONNECTION_IS(ONBOARD)
    //
    // The external SD card is not used. Hardware SPI is used to access the card.
    // When sharing the SD card with a PC we want the menu options to
    // mount/unmount the card and refresh it. So we disable card detect.
    //
    #undef SD_DETECT_PIN
    #define HAS_SHARED_MEDIA 1
  #endif

  // Set SD_DETECT_STATE based on hardware if not overridden
  #if PIN_EXISTS(SD_DETECT) && !defined(SD_DETECT_STATE)
    #if BOTH(HAS_LCD_MENU, ELB_FULL_GRAPHIC_CONTROLLER) && (SD_CONNECTION_IS(LCD) || !defined(SDCARD_CONNECTION))
      #define SD_DETECT_STATE HIGH
    #else
      #define SD_DETECT_STATE LOW
    #endif
  #endif

  // Extender cable doesn't support SD_DETECT_PIN
  #if ENABLED(NO_SD_DETECT)
    #undef SD_DETECT_PIN
  #endif

  #if DISABLED(USB_FLASH_DRIVE_SUPPORT) || BOTH(MULTI_VOLUME, VOLUME_SD_ONBOARD)
    #if ENABLED(SDIO_SUPPORT)
      #define NEED_SD2CARD_SDIO 1
    #else
      #define NEED_SD2CARD_SPI 1
    #endif
  #endif

#endif

#if ANY(HAS_GRAPHICAL_TFT, LCD_USE_DMA_FSMC, HAS_FSMC_GRAPHICAL_TFT, HAS_SPI_GRAPHICAL_TFT) || !PIN_EXISTS(SD_DETECT)
  #define NO_LCD_REINIT 1  // Suppress LCD re-initialization
>>>>>>> mcu_ctrl
#endif

/**
 * Set defaults for missing (newer) options
 */
#ifndef DISABLE_INACTIVE_X
  #define DISABLE_INACTIVE_X DISABLE_X
#endif
#ifndef DISABLE_INACTIVE_Y
  #define DISABLE_INACTIVE_Y DISABLE_Y
#endif
#ifndef DISABLE_INACTIVE_Z
  #define DISABLE_INACTIVE_Z DISABLE_Z
#endif
#ifndef DISABLE_INACTIVE_E
  #define DISABLE_INACTIVE_E DISABLE_E
#endif

/**
 * Power Supply
 */
#ifndef PSU_NAME
  #if DISABLED(PSU_CONTROL)
    #define PSU_NAME "Generic"  // No control
<<<<<<< HEAD
  #elif PSU_ACTIVE_HIGH
=======
  #elif PSU_ACTIVE_STATE
>>>>>>> mcu_ctrl
    #define PSU_NAME "XBox"     // X-Box 360 (203W)
  #else
    #define PSU_NAME "ATX"      // ATX style
  #endif
#endif

<<<<<<< HEAD
#if !defined(PSU_POWERUP_DELAY) && ENABLED(PSU_CONTROL) && DISABLED(AUTO_POWER_CONTROL)
  #define PSU_POWERUP_DELAY 100
=======
#if ENABLED(PSU_CONTROL)
  #ifndef PSU_POWERUP_DELAY
    #define PSU_POWERUP_DELAY 250
  #endif
  #ifndef POWER_OFF_DELAY
    #define POWER_OFF_DELAY   0
  #endif
>>>>>>> mcu_ctrl
#endif

/**
 * Temp Sensor defines
 */

<<<<<<< HEAD
#define ANY_TEMP_SENSOR_IS(n) (TEMP_SENSOR_0 == (n) || TEMP_SENSOR_1 == (n) || TEMP_SENSOR_2 == (n) || TEMP_SENSOR_3 == (n) || TEMP_SENSOR_4 == (n) || TEMP_SENSOR_5 == (n) || TEMP_SENSOR_BED == (n) || TEMP_SENSOR_CHAMBER == (n))

#define HAS_USER_THERMISTORS ANY_TEMP_SENSOR_IS(1000)

#if TEMP_SENSOR_0 == -5 || TEMP_SENSOR_0 == -3 || TEMP_SENSOR_0 == -2
  #define HEATER_0_USES_MAX6675
  #if TEMP_SENSOR_0 == -3
    #define HEATER_0_MAX6675_TMIN -270
    #define HEATER_0_MAX6675_TMAX 1800
  #else
    #define HEATER_0_MAX6675_TMIN    0
    #define HEATER_0_MAX6675_TMAX 1024
  #endif
  #if TEMP_SENSOR_0 == -5
    #define MAX6675_IS_MAX31865
  #elif TEMP_SENSOR_0 == -3
    #define MAX6675_IS_MAX31855
  #endif
#elif TEMP_SENSOR_0 == -4
  #define HEATER_0_USES_AD8495
#elif TEMP_SENSOR_0 == -1
  #define HEATER_0_USES_AD595
#elif TEMP_SENSOR_0 > 0
  #define THERMISTOR_HEATER_0 TEMP_SENSOR_0
  #define HEATER_0_USES_THERMISTOR
  #if TEMP_SENSOR_0 == 1000
    #define HEATER_0_USER_THERMISTOR
=======
#define ANY_TEMP_SENSOR_IS(n) (TEMP_SENSOR_0 == (n) || TEMP_SENSOR_1 == (n) || TEMP_SENSOR_2 == (n) || TEMP_SENSOR_3 == (n) || TEMP_SENSOR_4 == (n) || TEMP_SENSOR_5 == (n) || TEMP_SENSOR_6 == (n) || TEMP_SENSOR_7 == (n) || TEMP_SENSOR_BED == (n) || TEMP_SENSOR_PROBE == (n) || TEMP_SENSOR_CHAMBER == (n) || TEMP_SENSOR_COOLER == (n))

#if ANY_TEMP_SENSOR_IS(1000)
  #define HAS_USER_THERMISTORS 1
#endif

#if TEMP_SENSOR_0 == -5 || TEMP_SENSOR_0 == -3 || TEMP_SENSOR_0 == -2
  #define TEMP_SENSOR_0_IS_MAX_TC 1
  #define HAS_MAX_TC 1
  #if TEMP_SENSOR_0 == -3
    #define TEMP_SENSOR_0_MAX_TC_TMIN -270
    #define TEMP_SENSOR_0_MAX_TC_TMAX 1800
  #else
    #define TEMP_SENSOR_0_MAX_TC_TMIN    0
    #define TEMP_SENSOR_0_MAX_TC_TMAX 1024
  #endif
  #if TEMP_SENSOR_0 == -5
    #define TEMP_SENSOR_0_IS_MAX31865 1
  #elif TEMP_SENSOR_0 == -3
    #define TEMP_SENSOR_0_IS_MAX31855 1
  #elif TEMP_SENSOR_0 == -2
    #define TEMP_SENSOR_0_IS_MAX6675 1
  #endif
#elif TEMP_SENSOR_0 == -4
  #define TEMP_SENSOR_0_IS_AD8495 1
#elif TEMP_SENSOR_0 == -1
  #define TEMP_SENSOR_0_IS_AD595 1
#elif TEMP_SENSOR_0 > 0
  #define TEMP_SENSOR_0_THERMISTOR_ID TEMP_SENSOR_0
  #define TEMP_SENSOR_0_IS_THERMISTOR 1
  #if TEMP_SENSOR_0 == 1000
    #define TEMP_SENSOR_0_IS_CUSTOM 1
  #elif TEMP_SENSOR_0 == 998 || TEMP_SENSOR_0 == 999
    #define TEMP_SENSOR_0_IS_DUMMY 1
>>>>>>> mcu_ctrl
  #endif
#else
  #undef HEATER_0_MINTEMP
  #undef HEATER_0_MAXTEMP
#endif

#if TEMP_SENSOR_1 == -5 || TEMP_SENSOR_1 == -3 || TEMP_SENSOR_1 == -2
<<<<<<< HEAD
  #define HEATER_1_USES_MAX6675
  #if TEMP_SENSOR_1 == -3
    #define HEATER_1_MAX6675_TMIN -270
    #define HEATER_1_MAX6675_TMAX 1800
  #else
    #define HEATER_1_MAX6675_TMIN    0
    #define HEATER_1_MAX6675_TMAX 1024
=======
  #define TEMP_SENSOR_1_IS_MAX_TC 1
  #define HAS_MAX_TC 1
  #if TEMP_SENSOR_1 == -3
    #define TEMP_SENSOR_1_MAX_TC_TMIN -270
    #define TEMP_SENSOR_1_MAX_TC_TMAX 1800
  #else
    #define TEMP_SENSOR_1_MAX_TC_TMIN    0
    #define TEMP_SENSOR_1_MAX_TC_TMAX 1024
  #endif
  #if TEMP_SENSOR_1 == -5
    #define TEMP_SENSOR_1_IS_MAX31865 1
  #elif TEMP_SENSOR_1 == -3
    #define TEMP_SENSOR_1_IS_MAX31855 1
  #elif TEMP_SENSOR_1 == -2
    #define TEMP_SENSOR_1_IS_MAX6675 1
>>>>>>> mcu_ctrl
  #endif
  #if TEMP_SENSOR_1 != TEMP_SENSOR_0
    #if   TEMP_SENSOR_1 == -5
      #error "If MAX31865 Thermocouple (-5) is used for TEMP_SENSOR_1 then TEMP_SENSOR_0 must match."
    #elif TEMP_SENSOR_1 == -3
      #error "If MAX31855 Thermocouple (-3) is used for TEMP_SENSOR_1 then TEMP_SENSOR_0 must match."
    #elif TEMP_SENSOR_1 == -2
      #error "If MAX6675 Thermocouple (-2) is used for TEMP_SENSOR_1 then TEMP_SENSOR_0 must match."
    #endif
  #endif
#elif TEMP_SENSOR_1 == -4
<<<<<<< HEAD
  #define HEATER_1_USES_AD8495
#elif TEMP_SENSOR_1 == -1
  #define HEATER_1_USES_AD595
#elif TEMP_SENSOR_1 > 0
  #define THERMISTOR_HEATER_1 TEMP_SENSOR_1
  #define HEATER_1_USES_THERMISTOR
  #if TEMP_SENSOR_1 == 1000
    #define HEATER_1_USER_THERMISTOR
=======
  #define TEMP_SENSOR_1_IS_AD8495 1
#elif TEMP_SENSOR_1 == -1
  #define TEMP_SENSOR_1_IS_AD595 1
#elif TEMP_SENSOR_1 > 0
  #define TEMP_SENSOR_1_THERMISTOR_ID TEMP_SENSOR_1
  #define TEMP_SENSOR_1_IS_THERMISTOR 1
  #if TEMP_SENSOR_1 == 1000
    #define TEMP_SENSOR_1_IS_CUSTOM 1
  #elif TEMP_SENSOR_1 == 998 || TEMP_SENSOR_1 == 999
    #define TEMP_SENSOR_1_IS_DUMMY 1
>>>>>>> mcu_ctrl
  #endif
#else
  #undef HEATER_1_MINTEMP
  #undef HEATER_1_MAXTEMP
#endif

<<<<<<< HEAD
#if TEMP_SENSOR_2 == -4
  #define HEATER_2_USES_AD8495
=======
#if TEMP_SENSOR_0_IS_MAX31855 || TEMP_SENSOR_1_IS_MAX31855
  #define HAS_MAX31855 1
#endif
#if TEMP_SENSOR_0_IS_MAX31865 || TEMP_SENSOR_1_IS_MAX31865
  #define HAS_MAX31865 1
#endif
#if TEMP_SENSOR_0_IS_MAX6675 || TEMP_SENSOR_1_IS_MAX6675
  #define HAS_MAX6675 1
#endif

//
// Compatibility layer for MAX (SPI) temp boards
//
#if PIN_EXISTS(MAX6675_SS)
  #if TEMP_SENSOR_0_IS_MAX31855
    #define MAX31855_CS_PIN MAX6675_SS_PIN
  #elif TEMP_SENSOR_0_IS_MAX31865
    #define MAX31865_CS_PIN MAX6675_SS_PIN
  #elif TEMP_SENSOR_0_IS_MAX6675
    #define MAX6675_CS_PIN MAX6675_SS_PIN
  #endif
#endif

#if PIN_EXISTS(MAX6675_SS2)
  #if TEMP_SENSOR_1_IS_MAX31855
    #define MAX31855_CS2_PIN MAX6675_SS2_PIN
  #elif TEMP_SENSOR_1_IS_MAX31865
    #define MAX31865_CS2_PIN MAX6675_SS2_PIN
  #elif TEMP_SENSOR_1_IS_MAX6675
    #define MAX6675_CS2_PIN MAX6675_SS2_PIN
  #endif
#endif

#if PIN_EXISTS(MAX6675_DO)
  #if HAS_MAX31855
    #define MAX31855_MISO_PIN MAX6675_DO_PIN
  #elif HAS_MAX31865
    #define MAX31865_MISO_PIN MAX6675_DO_PIN
  #elif HAS_MAX6675
    #define MAX6675_MISO_PIN MAX6675_DO_PIN
  #endif
#endif

#if PIN_EXISTS(MAX6675_SCK)
  #if HAS_MAX31855
    #define MAX31855_SCK_PIN MAX6675_SCK_PIN
  #elif HAS_MAX31865
    #define MAX31865_SCK_PIN MAX6675_SCK_PIN
  #endif
#endif

// Compatibility Layer for use when HAL manipulates PINS for MAX31855 and MAX6675
#if PIN_EXISTS(MAX31855_CS) && !PIN_EXISTS(MAX6675_SS)
  #define MAX6675_SS_PIN MAX31855_CS_PIN
#endif
#if PIN_EXISTS(MAX31855_CS2) && !PIN_EXISTS(MAX6675_SS2)
  #define MAX6675_SS2_PIN MAX31855_CS2_PIN
#endif
#if PIN_EXISTS(MAX6675_CS) && !PIN_EXISTS(MAX6675_SS)
  #define MAX6675_SS_PIN MAX6675_CS_PIN
#endif
#if PIN_EXISTS(MAX6675_CS2) && !PIN_EXISTS(MAX6675_SS2)
  #define MAX6675_SS2_PIN MAX6675_CS2_PIN
#endif
#if PIN_EXISTS(MAX31855_MISO) && !PIN_EXISTS(MAX6675_DO)
  #define MAX6675_DO_PIN MAX31855_MISO_PIN
#endif
#if PIN_EXISTS(MAX6675_MISO) && !PIN_EXISTS(MAX6675_DO)
  #define MAX6675_DO_PIN MAX6675_MISO_PIN
#endif
#if PIN_EXISTS(MAX31855_SCK) && !PIN_EXISTS(MAX6675_SCK)
  #define MAX6675_SCK_PIN MAX31855_SCK_PIN
#endif

//
// User-defined thermocouple libraries
//
// Add LIB_MAX6675 / LIB_MAX31855 / LIB_MAX31865 to the build_flags
// to select a USER library for MAX6675, MAX31855, MAX31865
//
#if BOTH(HAS_MAX6675, LIB_MAX6675)
  #define LIB_USR_MAX6675 1
#endif
#if BOTH(HAS_MAX31855, LIB_MAX31855)
  #define LIB_USR_MAX31855 1
#endif
#if HAS_MAX31865
  #if ENABLED(LIB_MAX31865)
    #define LIB_USR_MAX31865 1
  #else
    #define LIB_ADAFRUIT_MAX31865 1
  #endif
#endif

#if TEMP_SENSOR_2 == -4
  #define TEMP_SENSOR_2_IS_AD8495 1
>>>>>>> mcu_ctrl
#elif TEMP_SENSOR_2 == -3
  #error "MAX31855 Thermocouples (-3) not supported for TEMP_SENSOR_2."
#elif TEMP_SENSOR_2 == -2
  #error "MAX6675 Thermocouples (-2) not supported for TEMP_SENSOR_2."
#elif TEMP_SENSOR_2 == -1
<<<<<<< HEAD
  #define HEATER_2_USES_AD595
#elif TEMP_SENSOR_2 > 0
  #define THERMISTOR_HEATER_2 TEMP_SENSOR_2
  #define HEATER_2_USES_THERMISTOR
  #if TEMP_SENSOR_2 == 1000
    #define HEATER_2_USER_THERMISTOR
=======
  #define TEMP_SENSOR_2_IS_AD595 1
#elif TEMP_SENSOR_2 > 0
  #define TEMP_SENSOR_2_THERMISTOR_ID TEMP_SENSOR_2
  #define TEMP_SENSOR_2_IS_THERMISTOR 1
  #if TEMP_SENSOR_2 == 1000
    #define TEMP_SENSOR_2_IS_CUSTOM 1
  #elif TEMP_SENSOR_2 == 998 || TEMP_SENSOR_2 == 999
    #define TEMP_SENSOR_2_IS_DUMMY 1
>>>>>>> mcu_ctrl
  #endif
#else
  #undef HEATER_2_MINTEMP
  #undef HEATER_2_MAXTEMP
#endif

#if TEMP_SENSOR_3 == -4
<<<<<<< HEAD
  #define HEATER_3_USES_AD8495
=======
  #define TEMP_SENSOR_3_IS_AD8495 1
>>>>>>> mcu_ctrl
#elif TEMP_SENSOR_3 == -3
  #error "MAX31855 Thermocouples (-3) not supported for TEMP_SENSOR_3."
#elif TEMP_SENSOR_3 == -2
  #error "MAX6675 Thermocouples (-2) not supported for TEMP_SENSOR_3."
#elif TEMP_SENSOR_3 == -1
<<<<<<< HEAD
  #define HEATER_3_USES_AD595
#elif TEMP_SENSOR_3 > 0
  #define THERMISTOR_HEATER_3 TEMP_SENSOR_3
  #define HEATER_3_USES_THERMISTOR
  #if TEMP_SENSOR_3 == 1000
    #define HEATER_3_USER_THERMISTOR
=======
  #define TEMP_SENSOR_3_IS_AD595 1
#elif TEMP_SENSOR_3 > 0
  #define TEMP_SENSOR_3_THERMISTOR_ID TEMP_SENSOR_3
  #define TEMP_SENSOR_3_IS_THERMISTOR 1
  #if TEMP_SENSOR_3 == 1000
    #define TEMP_SENSOR_3_IS_CUSTOM 1
  #elif TEMP_SENSOR_3 == 998 || TEMP_SENSOR_3 == 999
    #define TEMP_SENSOR_3_IS_DUMMY 1
>>>>>>> mcu_ctrl
  #endif
#else
  #undef HEATER_3_MINTEMP
  #undef HEATER_3_MAXTEMP
#endif

#if TEMP_SENSOR_4 == -4
<<<<<<< HEAD
  #define HEATER_4_USES_AD8495
=======
  #define TEMP_SENSOR_4_IS_AD8495 1
>>>>>>> mcu_ctrl
#elif TEMP_SENSOR_4 == -3
  #error "MAX31855 Thermocouples (-3) not supported for TEMP_SENSOR_4."
#elif TEMP_SENSOR_4 == -2
  #error "MAX6675 Thermocouples (-2) not supported for TEMP_SENSOR_4."
#elif TEMP_SENSOR_4 == -1
<<<<<<< HEAD
  #define HEATER_4_USES_AD595
#elif TEMP_SENSOR_4 > 0
  #define THERMISTOR_HEATER_4 TEMP_SENSOR_4
  #define HEATER_4_USES_THERMISTOR
  #if TEMP_SENSOR_4 == 1000
    #define HEATER_4_USER_THERMISTOR
=======
  #define TEMP_SENSOR_4_IS_AD595 1
#elif TEMP_SENSOR_4 > 0
  #define TEMP_SENSOR_4_THERMISTOR_ID TEMP_SENSOR_4
  #define TEMP_SENSOR_4_IS_THERMISTOR 1
  #if TEMP_SENSOR_4 == 1000
    #define TEMP_SENSOR_4_IS_CUSTOM 1
  #elif TEMP_SENSOR_4 == 998 || TEMP_SENSOR_4 == 999
    #define TEMP_SENSOR_4_IS_DUMMY 1
>>>>>>> mcu_ctrl
  #endif
#else
  #undef HEATER_4_MINTEMP
  #undef HEATER_4_MAXTEMP
#endif

#if TEMP_SENSOR_5 == -4
<<<<<<< HEAD
  #define HEATER_5_USES_AD8495
=======
  #define TEMP_SENSOR_5_IS_AD8495 1
>>>>>>> mcu_ctrl
#elif TEMP_SENSOR_5 == -3
  #error "MAX31855 Thermocouples (-3) not supported for TEMP_SENSOR_5."
#elif TEMP_SENSOR_5 == -2
  #error "MAX6675 Thermocouples (-2) not supported for TEMP_SENSOR_5."
#elif TEMP_SENSOR_5 == -1
<<<<<<< HEAD
  #define HEATER_5_USES_AD595
#elif TEMP_SENSOR_5 > 0
  #define THERMISTOR_HEATER_5 TEMP_SENSOR_5
  #define HEATER_5_USES_THERMISTOR
  #if TEMP_SENSOR_5 == 1000
    #define HEATER_5_USER_THERMISTOR
=======
  #define TEMP_SENSOR_5_IS_AD595 1
#elif TEMP_SENSOR_5 > 0
  #define TEMP_SENSOR_5_THERMISTOR_ID TEMP_SENSOR_5
  #define TEMP_SENSOR_5_IS_THERMISTOR 1
  #if TEMP_SENSOR_5 == 1000
    #define TEMP_SENSOR_5_IS_CUSTOM 1
  #elif TEMP_SENSOR_5 == 998 || TEMP_SENSOR_5 == 999
    #define TEMP_SENSOR_5_IS_DUMMY 1
>>>>>>> mcu_ctrl
  #endif
#else
  #undef HEATER_5_MINTEMP
  #undef HEATER_5_MAXTEMP
#endif

<<<<<<< HEAD
#if TEMP_SENSOR_BED == -4
  #define HEATER_BED_USES_AD8495
=======
#if TEMP_SENSOR_6 == -4
  #define TEMP_SENSOR_6_IS_AD8495 1
#elif TEMP_SENSOR_6 == -3
  #error "MAX31855 Thermocouples (-3) not supported for TEMP_SENSOR_6."
#elif TEMP_SENSOR_6 == -2
  #error "MAX6675 Thermocouples (-2) not supported for TEMP_SENSOR_6."
#elif TEMP_SENSOR_6 == -1
  #define TEMP_SENSOR_6_IS_AD595 1
#elif TEMP_SENSOR_6 > 0
  #define TEMP_SENSOR_6_THERMISTOR_ID TEMP_SENSOR_6
  #define TEMP_SENSOR_6_IS_THERMISTOR 1
  #if TEMP_SENSOR_6 == 1000
    #define TEMP_SENSOR_6_IS_CUSTOM 1
  #elif TEMP_SENSOR_6 == 998 || TEMP_SENSOR_6 == 999
    #define TEMP_SENSOR_6_IS_DUMMY 1
  #endif
#else
  #undef HEATER_6_MINTEMP
  #undef HEATER_6_MAXTEMP
#endif

#if TEMP_SENSOR_7 == -4
  #define TEMP_SENSOR_7_IS_AD8495 1
#elif TEMP_SENSOR_7 == -3
  #error "MAX31855 Thermocouples (-3) not supported for TEMP_SENSOR_7."
#elif TEMP_SENSOR_7 == -2
  #error "MAX7775 Thermocouples (-2) not supported for TEMP_SENSOR_7."
#elif TEMP_SENSOR_7 == -1
  #define TEMP_SENSOR_7_IS_AD595 1
#elif TEMP_SENSOR_7 > 0
  #define TEMP_SENSOR_7_THERMISTOR_ID TEMP_SENSOR_7
  #define TEMP_SENSOR_7_IS_THERMISTOR 1
  #if TEMP_SENSOR_7 == 1000
    #define TEMP_SENSOR_7_IS_CUSTOM 1
  #elif TEMP_SENSOR_7 == 998 || TEMP_SENSOR_7 == 999
    #define TEMP_SENSOR_7_IS_DUMMY 1
  #endif
#else
  #undef HEATER_7_MINTEMP
  #undef HEATER_7_MAXTEMP
#endif

#if TEMP_SENSOR_BED == -4
  #define TEMP_SENSOR_BED_IS_AD8495 1
>>>>>>> mcu_ctrl
#elif TEMP_SENSOR_BED == -3
  #error "MAX31855 Thermocouples (-3) not supported for TEMP_SENSOR_BED."
#elif TEMP_SENSOR_BED == -2
  #error "MAX6675 Thermocouples (-2) not supported for TEMP_SENSOR_BED."
#elif TEMP_SENSOR_BED == -1
<<<<<<< HEAD
  #define HEATER_BED_USES_AD595
#elif TEMP_SENSOR_BED > 0
  #define THERMISTORBED TEMP_SENSOR_BED
  #define HEATER_BED_USES_THERMISTOR
  #if TEMP_SENSOR_BED == 1000
    #define HEATER_BED_USER_THERMISTOR
=======
  #define TEMP_SENSOR_BED_IS_AD595 1
#elif TEMP_SENSOR_BED > 0
  #define TEMP_SENSOR_BED_THERMISTOR_ID TEMP_SENSOR_BED
  #define TEMP_SENSOR_BED_IS_THERMISTOR 1
  #if TEMP_SENSOR_BED == 1000
    #define TEMP_SENSOR_BED_IS_CUSTOM 1
  #elif TEMP_SENSOR_BED == 998 || TEMP_SENSOR_BED == 999
    #define TEMP_SENSOR_BED_IS_DUMMY 1
>>>>>>> mcu_ctrl
  #endif
#else
  #undef BED_MINTEMP
  #undef BED_MAXTEMP
#endif

#if TEMP_SENSOR_CHAMBER == -4
<<<<<<< HEAD
  #define HEATER_CHAMBER_USES_AD8495
=======
  #define TEMP_SENSOR_CHAMBER_IS_AD8495 1
>>>>>>> mcu_ctrl
#elif TEMP_SENSOR_CHAMBER == -3
  #error "MAX31855 Thermocouples (-3) not supported for TEMP_SENSOR_CHAMBER."
#elif TEMP_SENSOR_CHAMBER == -2
  #error "MAX6675 Thermocouples (-2) not supported for TEMP_SENSOR_CHAMBER."
#elif TEMP_SENSOR_CHAMBER == -1
<<<<<<< HEAD
  #define HEATER_CHAMBER_USES_AD595
#elif TEMP_SENSOR_CHAMBER > 0
  #define THERMISTORCHAMBER TEMP_SENSOR_CHAMBER
  #define HEATER_CHAMBER_USES_THERMISTOR
  #if TEMP_SENSOR_CHAMBER == 1000
    #define HEATER_CHAMBER_USER_THERMISTOR
=======
  #define TEMP_SENSOR_CHAMBER_IS_AD595 1
#elif TEMP_SENSOR_CHAMBER > 0
  #define TEMP_SENSOR_CHAMBER_THERMISTOR_ID TEMP_SENSOR_CHAMBER
  #define TEMP_SENSOR_CHAMBER_IS_THERMISTOR 1
  #if TEMP_SENSOR_CHAMBER == 1000
    #define TEMP_SENSOR_CHAMBER_IS_CUSTOM 1
  #elif TEMP_SENSOR_CHAMBER == 998 || TEMP_SENSOR_CHAMBER == 999
    #define TEMP_SENSOR_CHAMBER_IS_DUMMY 1
>>>>>>> mcu_ctrl
  #endif
#else
  #undef CHAMBER_MINTEMP
  #undef CHAMBER_MAXTEMP
#endif

<<<<<<< HEAD
#define HOTEND_USES_THERMISTOR ANY(HEATER_0_USES_THERMISTOR, HEATER_1_USES_THERMISTOR, HEATER_2_USES_THERMISTOR, HEATER_3_USES_THERMISTOR, HEATER_4_USES_THERMISTOR)

/**
 * Default hotend offsets, if not defined
 */
#if HAS_HOTEND_OFFSET
  #ifndef HOTEND_OFFSET_X
    #define HOTEND_OFFSET_X { 0 } // X offsets for each extruder
  #endif
  #ifndef HOTEND_OFFSET_Y
    #define HOTEND_OFFSET_Y { 0 } // Y offsets for each extruder
  #endif
  #ifndef HOTEND_OFFSET_Z
    #define HOTEND_OFFSET_Z { 0 } // Z offsets for each extruder
  #endif
#endif

/**
 * ARRAY_BY_EXTRUDERS based on EXTRUDERS
 */
#define ARRAY_BY_EXTRUDERS(V...) ARRAY_N(EXTRUDERS, V)
#define ARRAY_BY_EXTRUDERS1(v1) ARRAY_BY_EXTRUDERS(v1, v1, v1, v1, v1, v1)

/**
 * ARRAY_BY_HOTENDS based on HOTENDS
 */
#define ARRAY_BY_HOTENDS(V...) ARRAY_N(HOTENDS, V)
#define ARRAY_BY_HOTENDS1(v1) ARRAY_BY_HOTENDS(v1, v1, v1, v1, v1, v1)

/**
 * Driver Timings
 * NOTE: Driver timing order is longest-to-shortest duration.
 *       Preserve this ordering when adding new drivers.
 */

#define TRINAMICS (HAS_TRINAMIC || HAS_DRIVER(TMC2130_STANDALONE) || HAS_DRIVER(TMC2208_STANDALONE) || HAS_DRIVER(TMC2209_STANDALONE) || HAS_DRIVER(TMC26X_STANDALONE) || HAS_DRIVER(TMC2660_STANDALONE) || HAS_DRIVER(TMC5130_STANDALONE) || HAS_DRIVER(TMC5160_STANDALONE) || HAS_DRIVER(TMC2160_STANDALONE))

#ifndef MINIMUM_STEPPER_POST_DIR_DELAY
  #if HAS_DRIVER(TB6560)
    #define MINIMUM_STEPPER_POST_DIR_DELAY 15000
  #elif HAS_DRIVER(TB6600)
    #define MINIMUM_STEPPER_POST_DIR_DELAY 1500
  #elif HAS_DRIVER(DRV8825)
    #define MINIMUM_STEPPER_POST_DIR_DELAY 650
  #elif HAS_DRIVER(LV8729)
    #define MINIMUM_STEPPER_POST_DIR_DELAY 500
  #elif HAS_DRIVER(A5984)
    #define MINIMUM_STEPPER_POST_DIR_DELAY 400
  #elif HAS_DRIVER(A4988)
    #define MINIMUM_STEPPER_POST_DIR_DELAY 200
  #elif TRINAMICS
    #define MINIMUM_STEPPER_POST_DIR_DELAY 20
  #else
    #define MINIMUM_STEPPER_POST_DIR_DELAY 0   // Expect at least 10µS since one Stepper ISR must transpire
  #endif
#endif

#ifndef MINIMUM_STEPPER_PRE_DIR_DELAY
  #define MINIMUM_STEPPER_PRE_DIR_DELAY MINIMUM_STEPPER_POST_DIR_DELAY
#endif

#ifndef MINIMUM_STEPPER_PULSE
  #if HAS_DRIVER(TB6560)
    #define MINIMUM_STEPPER_PULSE 30
  #elif HAS_DRIVER(TB6600)
    #define MINIMUM_STEPPER_PULSE 3
  #elif HAS_DRIVER(DRV8825)
    #define MINIMUM_STEPPER_PULSE 2
  #elif HAS_DRIVER(A4988) || HAS_DRIVER(A5984)
    #define MINIMUM_STEPPER_PULSE 1
  #elif TRINAMICS
    #if ENABLED(LIN_ADVANCE) && (HAS_TMC_STANDALONE_E_DRIVER || (HAS_TMC_E_DRIVER && DISABLED(SQUARE_WAVE_STEPPING)))
      #define MINIMUM_STEPPER_PULSE 1
    #else
      #define MINIMUM_STEPPER_PULSE 0
    #endif
  #elif HAS_DRIVER(LV8729)
    #define MINIMUM_STEPPER_PULSE 0
  #else
    #define MINIMUM_STEPPER_PULSE 2
  #endif
#endif

#ifndef MAXIMUM_STEPPER_RATE
  #if HAS_DRIVER(TB6560)
    #define MAXIMUM_STEPPER_RATE 15000
  #elif HAS_DRIVER(TB6600)
    #define MAXIMUM_STEPPER_RATE 150000
  #elif HAS_DRIVER(LV8729)
    #define MAXIMUM_STEPPER_RATE 200000
  #elif HAS_DRIVER(DRV8825)
    #define MAXIMUM_STEPPER_RATE 250000
  #elif TRINAMICS
    #define MAXIMUM_STEPPER_RATE 400000
  #elif HAS_DRIVER(A4988)
    #define MAXIMUM_STEPPER_RATE 500000
  #else
    #define MAXIMUM_STEPPER_RATE 250000
=======
#if TEMP_SENSOR_COOLER == -4
  #define COOLER_USES_AD8495 1
#elif TEMP_SENSOR_COOLER == -3
  #error "MAX31855 Thermocouples (-3) not supported for TEMP_SENSOR_COOLER."
#elif TEMP_SENSOR_COOLER == -2
  #error "MAX6675 Thermocouples (-2) not supported for TEMP_SENSOR_COOLER."
#elif TEMP_SENSOR_COOLER == -1
  #define COOLER_USES_AD595 1
#elif TEMP_SENSOR_COOLER > 0
  #define TEMP_SENSOR_COOLER_THERMISTOR_ID TEMP_SENSOR_COOLER
  #define TEMP_SENSOR_COOLER_IS_THERMISTOR 1
  #if TEMP_SENSOR_COOLER == 1000
    #define COOLER_USER_THERMISTOR 1
  #elif TEMP_SENSOR_COOLER == 998 || TEMP_SENSOR_COOLER == 999
    #define COOLER_DUMMY_THERMISTOR 1
  #endif
#else
  #undef COOLER_MINTEMP
  #undef COOLER_MAXTEMP
#endif

#if TEMP_SENSOR_PROBE == -4
  #define TEMP_SENSOR_PROBE_IS_AD8495 1
#elif TEMP_SENSOR_PROBE == -3
  #error "MAX31855 Thermocouples (-3) not supported for TEMP_SENSOR_PROBE."
#elif TEMP_SENSOR_PROBE == -2
  #error "MAX6675 Thermocouples (-2) not supported for TEMP_SENSOR_PROBE."
#elif TEMP_SENSOR_PROBE == -1
  #define TEMP_SENSOR_PROBE_IS_AD595 1
#elif TEMP_SENSOR_PROBE > 0
  #define TEMP_SENSOR_PROBE_THERMISTOR_ID TEMP_SENSOR_PROBE
  #define TEMP_SENSOR_PROBE_IS_THERMISTOR 1
  #if TEMP_SENSOR_PROBE == 1000
    #define TEMP_SENSOR_PROBE_IS_CUSTOM 1
  #elif TEMP_SENSOR_PROBE == 998 || TEMP_SENSOR_PROBE == 999
    #define TEMP_SENSOR_PROBE_IS_DUMMY 1
>>>>>>> mcu_ctrl
  #endif
#endif

/**
 * X_DUAL_ENDSTOPS endstop reassignment
 */
#if ENABLED(X_DUAL_ENDSTOPS)
<<<<<<< HEAD
  #if X_HOME_DIR > 0
    #if X2_USE_ENDSTOP == _XMIN_
      #define X2_MAX_ENDSTOP_INVERTING X_MIN_ENDSTOP_INVERTING
      #define X2_MAX_PIN X_MIN_PIN
    #elif X2_USE_ENDSTOP == _XMAX_
      #define X2_MAX_ENDSTOP_INVERTING X_MAX_ENDSTOP_INVERTING
      #define X2_MAX_PIN X_MAX_PIN
    #elif X2_USE_ENDSTOP == _YMIN_
      #define X2_MAX_ENDSTOP_INVERTING Y_MIN_ENDSTOP_INVERTING
      #define X2_MAX_PIN Y_MIN_PIN
    #elif X2_USE_ENDSTOP == _YMAX_
      #define X2_MAX_ENDSTOP_INVERTING Y_MAX_ENDSTOP_INVERTING
      #define X2_MAX_PIN Y_MAX_PIN
    #elif X2_USE_ENDSTOP == _ZMIN_
      #define X2_MAX_ENDSTOP_INVERTING Z_MIN_ENDSTOP_INVERTING
      #define X2_MAX_PIN Z_MIN_PIN
    #elif X2_USE_ENDSTOP == _ZMAX_
      #define X2_MAX_ENDSTOP_INVERTING Z_MAX_ENDSTOP_INVERTING
      #define X2_MAX_PIN Z_MAX_PIN
    #else
      #define X2_MAX_ENDSTOP_INVERTING false
    #endif
    #define X2_MIN_ENDSTOP_INVERTING false
  #else
    #if X2_USE_ENDSTOP == _XMIN_
      #define X2_MIN_ENDSTOP_INVERTING X_MIN_ENDSTOP_INVERTING
      #define X2_MIN_PIN X_MIN_PIN
    #elif X2_USE_ENDSTOP == _XMAX_
      #define X2_MIN_ENDSTOP_INVERTING X_MAX_ENDSTOP_INVERTING
      #define X2_MIN_PIN X_MAX_PIN
    #elif X2_USE_ENDSTOP == _YMIN_
      #define X2_MIN_ENDSTOP_INVERTING Y_MIN_ENDSTOP_INVERTING
      #define X2_MIN_PIN Y_MIN_PIN
    #elif X2_USE_ENDSTOP == _YMAX_
      #define X2_MIN_ENDSTOP_INVERTING Y_MAX_ENDSTOP_INVERTING
      #define X2_MIN_PIN Y_MAX_PIN
    #elif X2_USE_ENDSTOP == _ZMIN_
      #define X2_MIN_ENDSTOP_INVERTING Z_MIN_ENDSTOP_INVERTING
      #define X2_MIN_PIN Z_MIN_PIN
    #elif X2_USE_ENDSTOP == _ZMAX_
      #define X2_MIN_ENDSTOP_INVERTING Z_MAX_ENDSTOP_INVERTING
      #define X2_MIN_PIN Z_MAX_PIN
    #else
      #define X2_MIN_ENDSTOP_INVERTING false
    #endif
    #define X2_MAX_ENDSTOP_INVERTING false
  #endif
#endif

// Is an endstop plug used for the X2 endstop?
#define IS_X2_ENDSTOP(A,M) (ENABLED(X_DUAL_ENDSTOPS) && X2_USE_ENDSTOP == _##A##M##_)

=======
  #if X_HOME_TO_MAX
    #ifndef X2_MAX_ENDSTOP_INVERTING
      #if X2_USE_ENDSTOP == _XMIN_
        #define X2_MAX_ENDSTOP_INVERTING X_MIN_ENDSTOP_INVERTING
      #elif X2_USE_ENDSTOP == _XMAX_
        #define X2_MAX_ENDSTOP_INVERTING X_MAX_ENDSTOP_INVERTING
      #elif X2_USE_ENDSTOP == _YMIN_
        #define X2_MAX_ENDSTOP_INVERTING Y_MIN_ENDSTOP_INVERTING
      #elif X2_USE_ENDSTOP == _YMAX_
        #define X2_MAX_ENDSTOP_INVERTING Y_MAX_ENDSTOP_INVERTING
      #elif X2_USE_ENDSTOP == _ZMIN_
        #define X2_MAX_ENDSTOP_INVERTING Z_MIN_ENDSTOP_INVERTING
      #elif X2_USE_ENDSTOP == _ZMAX_
        #define X2_MAX_ENDSTOP_INVERTING Z_MAX_ENDSTOP_INVERTING
      #else
        #define X2_MAX_ENDSTOP_INVERTING false
      #endif
    #endif
    #ifndef X2_MAX_PIN
      #if X2_USE_ENDSTOP == _XMIN_
        #define X2_MAX_PIN X_MIN_PIN
      #elif X2_USE_ENDSTOP == _XMAX_
        #define X2_MAX_PIN X_MAX_PIN
      #elif X2_USE_ENDSTOP == _YMIN_
        #define X2_MAX_PIN Y_MIN_PIN
      #elif X2_USE_ENDSTOP == _YMAX_
        #define X2_MAX_PIN Y_MAX_PIN
      #elif X2_USE_ENDSTOP == _ZMIN_
        #define X2_MAX_PIN Z_MIN_PIN
      #elif X2_USE_ENDSTOP == _ZMAX_
        #define X2_MAX_PIN Z_MAX_PIN
      #elif X2_USE_ENDSTOP == _XDIAG_
        #define X2_MAX_PIN X_DIAG_PIN
      #elif X2_USE_ENDSTOP == _YDIAG_
        #define X2_MAX_PIN Y_DIAG_PIN
      #elif X2_USE_ENDSTOP == _ZDIAG_
        #define X2_MAX_PIN Z_DIAG_PIN
      #elif X2_USE_ENDSTOP == _E0DIAG_
        #define X2_MAX_PIN E0_DIAG_PIN
      #elif X2_USE_ENDSTOP == _E1DIAG_
        #define X2_MAX_PIN E1_DIAG_PIN
      #elif X2_USE_ENDSTOP == _E2DIAG_
        #define X2_MAX_PIN E2_DIAG_PIN
      #elif X2_USE_ENDSTOP == _E3DIAG_
        #define X2_MAX_PIN E3_DIAG_PIN
      #elif X2_USE_ENDSTOP == _E4DIAG_
        #define X2_MAX_PIN E4_DIAG_PIN
      #elif X2_USE_ENDSTOP == _E5DIAG_
        #define X2_MAX_PIN E5_DIAG_PIN
      #elif X2_USE_ENDSTOP == _E6DIAG_
        #define X2_MAX_PIN E6_DIAG_PIN
      #elif X2_USE_ENDSTOP == _E7DIAG_
        #define X2_MAX_PIN E7_DIAG_PIN
      #endif
    #endif
    #ifndef X2_MIN_ENDSTOP_INVERTING
      #define X2_MIN_ENDSTOP_INVERTING false
    #endif
  #else
    #ifndef X2_MIN_ENDSTOP_INVERTING
      #if X2_USE_ENDSTOP == _XMIN_
        #define X2_MIN_ENDSTOP_INVERTING X_MIN_ENDSTOP_INVERTING
      #elif X2_USE_ENDSTOP == _XMAX_
        #define X2_MIN_ENDSTOP_INVERTING X_MAX_ENDSTOP_INVERTING
      #elif X2_USE_ENDSTOP == _YMIN_
        #define X2_MIN_ENDSTOP_INVERTING Y_MIN_ENDSTOP_INVERTING
      #elif X2_USE_ENDSTOP == _YMAX_
        #define X2_MIN_ENDSTOP_INVERTING Y_MAX_ENDSTOP_INVERTING
      #elif X2_USE_ENDSTOP == _ZMIN_
        #define X2_MIN_ENDSTOP_INVERTING Z_MIN_ENDSTOP_INVERTING
      #elif X2_USE_ENDSTOP == _ZMAX_
        #define X2_MIN_ENDSTOP_INVERTING Z_MAX_ENDSTOP_INVERTING
      #else
        #define X2_MIN_ENDSTOP_INVERTING false
      #endif
    #endif
    #ifndef X2_MIN_PIN
      #if X2_USE_ENDSTOP == _XMIN_
        #define X2_MIN_PIN X_MIN_PIN
      #elif X2_USE_ENDSTOP == _XMAX_
        #define X2_MIN_PIN X_MAX_PIN
      #elif X2_USE_ENDSTOP == _YMIN_
        #define X2_MIN_PIN Y_MIN_PIN
      #elif X2_USE_ENDSTOP == _YMAX_
        #define X2_MIN_PIN Y_MAX_PIN
      #elif X2_USE_ENDSTOP == _ZMIN_
        #define X2_MIN_PIN Z_MIN_PIN
      #elif X2_USE_ENDSTOP == _ZMAX_
        #define X2_MIN_PIN Z_MAX_PIN
      #elif X2_USE_ENDSTOP == _XDIAG_
        #define X2_MIN_PIN X_DIAG_PIN
      #elif X2_USE_ENDSTOP == _YDIAG_
        #define X2_MIN_PIN Y_DIAG_PIN
      #elif X2_USE_ENDSTOP == _ZDIAG_
        #define X2_MIN_PIN Z_DIAG_PIN
      #elif X2_USE_ENDSTOP == _E0DIAG_
        #define X2_MIN_PIN E0_DIAG_PIN
      #elif X2_USE_ENDSTOP == _E1DIAG_
        #define X2_MIN_PIN E1_DIAG_PIN
      #elif X2_USE_ENDSTOP == _E2DIAG_
        #define X2_MIN_PIN E2_DIAG_PIN
      #elif X2_USE_ENDSTOP == _E3DIAG_
        #define X2_MIN_PIN E3_DIAG_PIN
      #elif X2_USE_ENDSTOP == _E4DIAG_
        #define X2_MIN_PIN E4_DIAG_PIN
      #elif X2_USE_ENDSTOP == _E5DIAG_
        #define X2_MIN_PIN E5_DIAG_PIN
      #elif X2_USE_ENDSTOP == _E6DIAG_
        #define X2_MIN_PIN E6_DIAG_PIN
      #elif X2_USE_ENDSTOP == _E7DIAG_
        #define X2_MIN_PIN E7_DIAG_PIN
      #endif
    #endif
    #ifndef X2_MAX_ENDSTOP_INVERTING
      #define X2_MAX_ENDSTOP_INVERTING false
    #endif
  #endif
#endif

>>>>>>> mcu_ctrl
/**
 * Y_DUAL_ENDSTOPS endstop reassignment
 */
#if ENABLED(Y_DUAL_ENDSTOPS)
<<<<<<< HEAD
  #if Y_HOME_DIR > 0
    #if Y2_USE_ENDSTOP == _XMIN_
      #define Y2_MAX_ENDSTOP_INVERTING X_MIN_ENDSTOP_INVERTING
      #define Y2_MAX_PIN X_MIN_PIN
    #elif Y2_USE_ENDSTOP == _XMAX_
      #define Y2_MAX_ENDSTOP_INVERTING X_MAX_ENDSTOP_INVERTING
      #define Y2_MAX_PIN X_MAX_PIN
    #elif Y2_USE_ENDSTOP == _YMIN_
      #define Y2_MAX_ENDSTOP_INVERTING Y_MIN_ENDSTOP_INVERTING
      #define Y2_MAX_PIN Y_MIN_PIN
    #elif Y2_USE_ENDSTOP == _YMAX_
      #define Y2_MAX_ENDSTOP_INVERTING Y_MAX_ENDSTOP_INVERTING
      #define Y2_MAX_PIN Y_MAX_PIN
    #elif Y2_USE_ENDSTOP == _ZMIN_
      #define Y2_MAX_ENDSTOP_INVERTING Z_MIN_ENDSTOP_INVERTING
      #define Y2_MAX_PIN Z_MIN_PIN
    #elif Y2_USE_ENDSTOP == _ZMAX_
      #define Y2_MAX_ENDSTOP_INVERTING Z_MAX_ENDSTOP_INVERTING
      #define Y2_MAX_PIN Z_MAX_PIN
    #else
      #define Y2_MAX_ENDSTOP_INVERTING false
    #endif
    #define Y2_MIN_ENDSTOP_INVERTING false
  #else
    #if Y2_USE_ENDSTOP == _XMIN_
      #define Y2_MIN_ENDSTOP_INVERTING X_MIN_ENDSTOP_INVERTING
      #define Y2_MIN_PIN X_MIN_PIN
    #elif Y2_USE_ENDSTOP == _XMAX_
      #define Y2_MIN_ENDSTOP_INVERTING X_MAX_ENDSTOP_INVERTING
      #define Y2_MIN_PIN X_MAX_PIN
    #elif Y2_USE_ENDSTOP == _YMIN_
      #define Y2_MIN_ENDSTOP_INVERTING Y_MIN_ENDSTOP_INVERTING
      #define Y2_MIN_PIN Y_MIN_PIN
    #elif Y2_USE_ENDSTOP == _YMAX_
      #define Y2_MIN_ENDSTOP_INVERTING Y_MAX_ENDSTOP_INVERTING
      #define Y2_MIN_PIN Y_MAX_PIN
    #elif Y2_USE_ENDSTOP == _ZMIN_
      #define Y2_MIN_ENDSTOP_INVERTING Z_MIN_ENDSTOP_INVERTING
      #define Y2_MIN_PIN Z_MIN_PIN
    #elif Y2_USE_ENDSTOP == _ZMAX_
      #define Y2_MIN_ENDSTOP_INVERTING Z_MAX_ENDSTOP_INVERTING
      #define Y2_MIN_PIN Z_MAX_PIN
    #else
      #define Y2_MIN_ENDSTOP_INVERTING false
    #endif
    #define Y2_MAX_ENDSTOP_INVERTING false
  #endif
#endif

// Is an endstop plug used for the Y2 endstop or the bed probe?
#define IS_Y2_ENDSTOP(A,M) (ENABLED(Y_DUAL_ENDSTOPS) && Y2_USE_ENDSTOP == _##A##M##_)

/**
 * Z_DUAL_ENDSTOPS endstop reassignment
 */
#if Z_MULTI_ENDSTOPS
  #if Z_HOME_DIR > 0
    #if Z2_USE_ENDSTOP == _XMIN_
      #define Z2_MAX_ENDSTOP_INVERTING X_MIN_ENDSTOP_INVERTING
      #define Z2_MAX_PIN X_MIN_PIN
    #elif Z2_USE_ENDSTOP == _XMAX_
      #define Z2_MAX_ENDSTOP_INVERTING X_MAX_ENDSTOP_INVERTING
      #define Z2_MAX_PIN X_MAX_PIN
    #elif Z2_USE_ENDSTOP == _YMIN_
      #define Z2_MAX_ENDSTOP_INVERTING Y_MIN_ENDSTOP_INVERTING
      #define Z2_MAX_PIN Y_MIN_PIN
    #elif Z2_USE_ENDSTOP == _YMAX_
      #define Z2_MAX_ENDSTOP_INVERTING Y_MAX_ENDSTOP_INVERTING
      #define Z2_MAX_PIN Y_MAX_PIN
    #elif Z2_USE_ENDSTOP == _ZMIN_
      #define Z2_MAX_ENDSTOP_INVERTING Z_MIN_ENDSTOP_INVERTING
      #define Z2_MAX_PIN Z_MIN_PIN
    #elif Z2_USE_ENDSTOP == _ZMAX_
      #define Z2_MAX_ENDSTOP_INVERTING Z_MAX_ENDSTOP_INVERTING
      #define Z2_MAX_PIN Z_MAX_PIN
    #else
      #define Z2_MAX_ENDSTOP_INVERTING false
    #endif
    #define Z2_MIN_ENDSTOP_INVERTING false
  #else
    #if Z2_USE_ENDSTOP == _XMIN_
      #define Z2_MIN_ENDSTOP_INVERTING X_MIN_ENDSTOP_INVERTING
      #define Z2_MIN_PIN X_MIN_PIN
    #elif Z2_USE_ENDSTOP == _XMAX_
      #define Z2_MIN_ENDSTOP_INVERTING X_MAX_ENDSTOP_INVERTING
      #define Z2_MIN_PIN X_MAX_PIN
    #elif Z2_USE_ENDSTOP == _YMIN_
      #define Z2_MIN_ENDSTOP_INVERTING Y_MIN_ENDSTOP_INVERTING
      #define Z2_MIN_PIN Y_MIN_PIN
    #elif Z2_USE_ENDSTOP == _YMAX_
      #define Z2_MIN_ENDSTOP_INVERTING Y_MAX_ENDSTOP_INVERTING
      #define Z2_MIN_PIN Y_MAX_PIN
    #elif Z2_USE_ENDSTOP == _ZMIN_
      #define Z2_MIN_ENDSTOP_INVERTING Z_MIN_ENDSTOP_INVERTING
      #define Z2_MIN_PIN Z_MIN_PIN
    #elif Z2_USE_ENDSTOP == _ZMAX_
      #define Z2_MIN_ENDSTOP_INVERTING Z_MAX_ENDSTOP_INVERTING
      #define Z2_MIN_PIN Z_MAX_PIN
    #else
      #define Z2_MIN_ENDSTOP_INVERTING false
    #endif
    #define Z2_MAX_ENDSTOP_INVERTING false
  #endif
#endif

#if ENABLED(Z_TRIPLE_ENDSTOPS)
  #if Z_HOME_DIR > 0
    #if Z3_USE_ENDSTOP == _XMIN_
      #define Z3_MAX_ENDSTOP_INVERTING X_MIN_ENDSTOP_INVERTING
      #define Z3_MAX_PIN X_MIN_PIN
    #elif Z3_USE_ENDSTOP == _XMAX_
      #define Z3_MAX_ENDSTOP_INVERTING X_MAX_ENDSTOP_INVERTING
      #define Z3_MAX_PIN X_MAX_PIN
    #elif Z3_USE_ENDSTOP == _YMIN_
      #define Z3_MAX_ENDSTOP_INVERTING Y_MIN_ENDSTOP_INVERTING
      #define Z3_MAX_PIN Y_MIN_PIN
    #elif Z3_USE_ENDSTOP == _YMAX_
      #define Z3_MAX_ENDSTOP_INVERTING Y_MAX_ENDSTOP_INVERTING
      #define Z3_MAX_PIN Y_MAX_PIN
    #elif Z3_USE_ENDSTOP == _ZMIN_
      #define Z3_MAX_ENDSTOP_INVERTING Z_MIN_ENDSTOP_INVERTING
      #define Z3_MAX_PIN Z_MIN_PIN
    #elif Z3_USE_ENDSTOP == _ZMAX_
      #define Z3_MAX_ENDSTOP_INVERTING Z_MAX_ENDSTOP_INVERTING
      #define Z3_MAX_PIN Z_MAX_PIN
    #else
      #define Z3_MAX_ENDSTOP_INVERTING false
    #endif
    #define Z3_MIN_ENDSTOP_INVERTING false
  #else
    #if Z3_USE_ENDSTOP == _XMIN_
      #define Z3_MIN_ENDSTOP_INVERTING X_MIN_ENDSTOP_INVERTING
      #define Z3_MIN_PIN X_MIN_PIN
    #elif Z3_USE_ENDSTOP == _XMAX_
      #define Z3_MIN_ENDSTOP_INVERTING X_MAX_ENDSTOP_INVERTING
      #define Z3_MIN_PIN X_MAX_PIN
    #elif Z3_USE_ENDSTOP == _YMIN_
      #define Z3_MIN_ENDSTOP_INVERTING Y_MIN_ENDSTOP_INVERTING
      #define Z3_MIN_PIN Y_MIN_PIN
    #elif Z3_USE_ENDSTOP == _YMAX_
      #define Z3_MIN_ENDSTOP_INVERTING Y_MAX_ENDSTOP_INVERTING
      #define Z3_MIN_PIN Y_MAX_PIN
    #elif Z3_USE_ENDSTOP == _ZMIN_
      #define Z3_MIN_ENDSTOP_INVERTING Z_MIN_ENDSTOP_INVERTING
      #define Z3_MIN_PIN Z_MIN_PIN
    #elif Z3_USE_ENDSTOP == _ZMAX_
      #define Z3_MIN_ENDSTOP_INVERTING Z_MAX_ENDSTOP_INVERTING
      #define Z3_MIN_PIN Z_MAX_PIN
    #else
      #define Z3_MIN_ENDSTOP_INVERTING false
    #endif
    #define Z3_MAX_ENDSTOP_INVERTING false
  #endif
#endif

// Is an endstop plug used for the Z2 endstop or the bed probe?
#define IS_Z2_OR_PROBE(A,M) ( \
     (Z_MULTI_ENDSTOPS && Z2_USE_ENDSTOP == _##A##M##_) \
  || (HAS_CUSTOM_PROBE_PIN && Z_MIN_PROBE_PIN == A##_##M##_PIN ) )

// Is an endstop plug used for the Z3 endstop or the bed probe?
#define IS_Z3_OR_PROBE(A,M) ( \
     (ENABLED(Z_TRIPLE_ENDSTOPS) && Z3_USE_ENDSTOP == _##A##M##_) \
  || (HAS_CUSTOM_PROBE_PIN && Z_MIN_PROBE_PIN == A##_##M##_PIN ) )
=======
  #if Y_HOME_TO_MAX
    #ifndef Y2_MAX_ENDSTOP_INVERTING
      #if Y2_USE_ENDSTOP == _XMIN_
        #define Y2_MAX_ENDSTOP_INVERTING X_MIN_ENDSTOP_INVERTING
      #elif Y2_USE_ENDSTOP == _XMAX_
        #define Y2_MAX_ENDSTOP_INVERTING X_MAX_ENDSTOP_INVERTING
      #elif Y2_USE_ENDSTOP == _YMIN_
        #define Y2_MAX_ENDSTOP_INVERTING Y_MIN_ENDSTOP_INVERTING
      #elif Y2_USE_ENDSTOP == _YMAX_
        #define Y2_MAX_ENDSTOP_INVERTING Y_MAX_ENDSTOP_INVERTING
      #elif Y2_USE_ENDSTOP == _ZMIN_
        #define Y2_MAX_ENDSTOP_INVERTING Z_MIN_ENDSTOP_INVERTING
      #elif Y2_USE_ENDSTOP == _ZMAX_
        #define Y2_MAX_ENDSTOP_INVERTING Z_MAX_ENDSTOP_INVERTING
      #else
        #define Y2_MAX_ENDSTOP_INVERTING false
      #endif
    #endif
    #ifndef Y2_MAX_PIN
      #if Y2_USE_ENDSTOP == _XMIN_
        #define Y2_MAX_PIN X_MIN_PIN
      #elif Y2_USE_ENDSTOP == _XMAX_
        #define Y2_MAX_PIN X_MAX_PIN
      #elif Y2_USE_ENDSTOP == _YMIN_
        #define Y2_MAX_PIN Y_MIN_PIN
      #elif Y2_USE_ENDSTOP == _YMAX_
        #define Y2_MAX_PIN Y_MAX_PIN
      #elif Y2_USE_ENDSTOP == _ZMIN_
        #define Y2_MAX_PIN Z_MIN_PIN
      #elif Y2_USE_ENDSTOP == _ZMAX_
        #define Y2_MAX_PIN Z_MAX_PIN
      #elif Y2_USE_ENDSTOP == _XDIAG_
        #define Y2_MAX_PIN X_DIAG_PIN
      #elif Y2_USE_ENDSTOP == _YDIAG_
        #define Y2_MAX_PIN Y_DIAG_PIN
      #elif Y2_USE_ENDSTOP == _ZDIAG_
        #define Y2_MAX_PIN Z_DIAG_PIN
      #elif Y2_USE_ENDSTOP == _E0DIAG_
        #define Y2_MAX_PIN E0_DIAG_PIN
      #elif Y2_USE_ENDSTOP == _E1DIAG_
        #define Y2_MAX_PIN E1_DIAG_PIN
      #elif Y2_USE_ENDSTOP == _E2DIAG_
        #define Y2_MAX_PIN E2_DIAG_PIN
      #elif Y2_USE_ENDSTOP == _E3DIAG_
        #define Y2_MAX_PIN E3_DIAG_PIN
      #elif Y2_USE_ENDSTOP == _E4DIAG_
        #define Y2_MAX_PIN E4_DIAG_PIN
      #elif Y2_USE_ENDSTOP == _E5DIAG_
        #define Y2_MAX_PIN E5_DIAG_PIN
      #elif Y2_USE_ENDSTOP == _E6DIAG_
        #define Y2_MAX_PIN E6_DIAG_PIN
      #elif Y2_USE_ENDSTOP == _E7DIAG_
        #define Y2_MAX_PIN E7_DIAG_PIN
      #endif
    #endif
    #ifndef Y2_MIN_ENDSTOP_INVERTING
      #define Y2_MIN_ENDSTOP_INVERTING false
    #endif
  #else
    #ifndef Y2_MIN_ENDSTOP_INVERTING
      #if Y2_USE_ENDSTOP == _XMIN_
        #define Y2_MIN_ENDSTOP_INVERTING X_MIN_ENDSTOP_INVERTING
      #elif Y2_USE_ENDSTOP == _XMAX_
        #define Y2_MIN_ENDSTOP_INVERTING X_MAX_ENDSTOP_INVERTING
      #elif Y2_USE_ENDSTOP == _YMIN_
        #define Y2_MIN_ENDSTOP_INVERTING Y_MIN_ENDSTOP_INVERTING
      #elif Y2_USE_ENDSTOP == _YMAX_
        #define Y2_MIN_ENDSTOP_INVERTING Y_MAX_ENDSTOP_INVERTING
      #elif Y2_USE_ENDSTOP == _ZMIN_
        #define Y2_MIN_ENDSTOP_INVERTING Z_MIN_ENDSTOP_INVERTING
      #elif Y2_USE_ENDSTOP == _ZMAX_
        #define Y2_MIN_ENDSTOP_INVERTING Z_MAX_ENDSTOP_INVERTING
      #else
        #define Y2_MIN_ENDSTOP_INVERTING false
      #endif
    #endif
    #ifndef Y2_MIN_PIN
      #if Y2_USE_ENDSTOP == _XMIN_
        #define Y2_MIN_PIN X_MIN_PIN
      #elif Y2_USE_ENDSTOP == _XMAX_
        #define Y2_MIN_PIN X_MAX_PIN
      #elif Y2_USE_ENDSTOP == _YMIN_
        #define Y2_MIN_PIN Y_MIN_PIN
      #elif Y2_USE_ENDSTOP == _YMAX_
        #define Y2_MIN_PIN Y_MAX_PIN
      #elif Y2_USE_ENDSTOP == _ZMIN_
        #define Y2_MIN_PIN Z_MIN_PIN
      #elif Y2_USE_ENDSTOP == _ZMAX_
        #define Y2_MIN_PIN Z_MAX_PIN
      #elif Y2_USE_ENDSTOP == _XDIAG_
        #define Y2_MIN_PIN X_DIAG_PIN
      #elif Y2_USE_ENDSTOP == _YDIAG_
        #define Y2_MIN_PIN Y_DIAG_PIN
      #elif Y2_USE_ENDSTOP == _ZDIAG_
        #define Y2_MIN_PIN Z_DIAG_PIN
      #elif Y2_USE_ENDSTOP == _E0DIAG_
        #define Y2_MIN_PIN E0_DIAG_PIN
      #elif Y2_USE_ENDSTOP == _E1DIAG_
        #define Y2_MIN_PIN E1_DIAG_PIN
      #elif Y2_USE_ENDSTOP == _E2DIAG_
        #define Y2_MIN_PIN E2_DIAG_PIN
      #elif Y2_USE_ENDSTOP == _E3DIAG_
        #define Y2_MIN_PIN E3_DIAG_PIN
      #elif Y2_USE_ENDSTOP == _E4DIAG_
        #define Y2_MIN_PIN E4_DIAG_PIN
      #elif Y2_USE_ENDSTOP == _E5DIAG_
        #define Y2_MIN_PIN E5_DIAG_PIN
      #elif Y2_USE_ENDSTOP == _E6DIAG_
        #define Y2_MIN_PIN E6_DIAG_PIN
      #elif Y2_USE_ENDSTOP == _E7DIAG_
        #define Y2_MIN_PIN E7_DIAG_PIN
      #endif
    #endif
    #ifndef Y2_MAX_ENDSTOP_INVERTING
      #define Y2_MAX_ENDSTOP_INVERTING false
    #endif
  #endif
#endif

/**
 * Z_MULTI_ENDSTOPS endstop reassignment
 */
#if ENABLED(Z_MULTI_ENDSTOPS)

  #if Z_HOME_TO_MAX
    #ifndef Z2_MAX_ENDSTOP_INVERTING
      #if Z2_USE_ENDSTOP == _XMIN_
        #define Z2_MAX_ENDSTOP_INVERTING X_MIN_ENDSTOP_INVERTING
      #elif Z2_USE_ENDSTOP == _XMAX_
        #define Z2_MAX_ENDSTOP_INVERTING X_MAX_ENDSTOP_INVERTING
      #elif Z2_USE_ENDSTOP == _YMIN_
        #define Z2_MAX_ENDSTOP_INVERTING Y_MIN_ENDSTOP_INVERTING
      #elif Z2_USE_ENDSTOP == _YMAX_
        #define Z2_MAX_ENDSTOP_INVERTING Y_MAX_ENDSTOP_INVERTING
      #elif Z2_USE_ENDSTOP == _ZMIN_
        #define Z2_MAX_ENDSTOP_INVERTING Z_MIN_ENDSTOP_INVERTING
      #elif Z2_USE_ENDSTOP == _ZMAX_
        #define Z2_MAX_ENDSTOP_INVERTING Z_MAX_ENDSTOP_INVERTING
      #else
        #define Z2_MAX_ENDSTOP_INVERTING false
      #endif
    #endif
    #ifndef Z2_MAX_PIN
      #if Z2_USE_ENDSTOP == _XMIN_
        #define Z2_MAX_PIN X_MIN_PIN
      #elif Z2_USE_ENDSTOP == _XMAX_
        #define Z2_MAX_PIN X_MAX_PIN
      #elif Z2_USE_ENDSTOP == _YMIN_
        #define Z2_MAX_PIN Y_MIN_PIN
      #elif Z2_USE_ENDSTOP == _YMAX_
        #define Z2_MAX_PIN Y_MAX_PIN
      #elif Z2_USE_ENDSTOP == _ZMIN_
        #define Z2_MAX_PIN Z_MIN_PIN
      #elif Z2_USE_ENDSTOP == _ZMAX_
        #define Z2_MAX_PIN Z_MAX_PIN
      #elif Z2_USE_ENDSTOP == _XDIAG_
        #define Z2_MAX_PIN X_DIAG_PIN
      #elif Z2_USE_ENDSTOP == _YDIAG_
        #define Z2_MAX_PIN Y_DIAG_PIN
      #elif Z2_USE_ENDSTOP == _ZDIAG_
        #define Z2_MAX_PIN Z_DIAG_PIN
      #elif Z2_USE_ENDSTOP == _E0DIAG_
        #define Z2_MAX_PIN E0_DIAG_PIN
      #elif Z2_USE_ENDSTOP == _E1DIAG_
        #define Z2_MAX_PIN E1_DIAG_PIN
      #elif Z2_USE_ENDSTOP == _E2DIAG_
        #define Z2_MAX_PIN E2_DIAG_PIN
      #elif Z2_USE_ENDSTOP == _E3DIAG_
        #define Z2_MAX_PIN E3_DIAG_PIN
      #elif Z2_USE_ENDSTOP == _E4DIAG_
        #define Z2_MAX_PIN E4_DIAG_PIN
      #elif Z2_USE_ENDSTOP == _E5DIAG_
        #define Z2_MAX_PIN E5_DIAG_PIN
      #elif Z2_USE_ENDSTOP == _E6DIAG_
        #define Z2_MAX_PIN E6_DIAG_PIN
      #elif Z2_USE_ENDSTOP == _E7DIAG_
        #define Z2_MAX_PIN E7_DIAG_PIN
      #endif
    #endif
    #ifndef Z2_MIN_ENDSTOP_INVERTING
      #define Z2_MIN_ENDSTOP_INVERTING false
    #endif
  #else
    #ifndef Z2_MIN_ENDSTOP_INVERTING
      #if Z2_USE_ENDSTOP == _XMIN_
        #define Z2_MIN_ENDSTOP_INVERTING X_MIN_ENDSTOP_INVERTING
      #elif Z2_USE_ENDSTOP == _XMAX_
        #define Z2_MIN_ENDSTOP_INVERTING X_MAX_ENDSTOP_INVERTING
      #elif Z2_USE_ENDSTOP == _YMIN_
        #define Z2_MIN_ENDSTOP_INVERTING Y_MIN_ENDSTOP_INVERTING
      #elif Z2_USE_ENDSTOP == _YMAX_
        #define Z2_MIN_ENDSTOP_INVERTING Y_MAX_ENDSTOP_INVERTING
      #elif Z2_USE_ENDSTOP == _ZMIN_
        #define Z2_MIN_ENDSTOP_INVERTING Z_MIN_ENDSTOP_INVERTING
      #elif Z2_USE_ENDSTOP == _ZMAX_
        #define Z2_MIN_ENDSTOP_INVERTING Z_MAX_ENDSTOP_INVERTING
      #else
        #define Z2_MIN_ENDSTOP_INVERTING false
      #endif
    #endif
    #ifndef Z2_MIN_PIN
      #if Z2_USE_ENDSTOP == _XMIN_
        #define Z2_MIN_PIN X_MIN_PIN
      #elif Z2_USE_ENDSTOP == _XMAX_
        #define Z2_MIN_PIN X_MAX_PIN
      #elif Z2_USE_ENDSTOP == _YMIN_
        #define Z2_MIN_PIN Y_MIN_PIN
      #elif Z2_USE_ENDSTOP == _YMAX_
        #define Z2_MIN_PIN Y_MAX_PIN
      #elif Z2_USE_ENDSTOP == _ZMIN_
        #define Z2_MIN_PIN Z_MIN_PIN
      #elif Z2_USE_ENDSTOP == _ZMAX_
        #define Z2_MIN_PIN Z_MAX_PIN
      #elif Z2_USE_ENDSTOP == _XDIAG_
        #define Z2_MIN_PIN X_DIAG_PIN
      #elif Z2_USE_ENDSTOP == _YDIAG_
        #define Z2_MIN_PIN Y_DIAG_PIN
      #elif Z2_USE_ENDSTOP == _ZDIAG_
        #define Z2_MIN_PIN Z_DIAG_PIN
      #elif Z2_USE_ENDSTOP == _E0DIAG_
        #define Z2_MIN_PIN E0_DIAG_PIN
      #elif Z2_USE_ENDSTOP == _E1DIAG_
        #define Z2_MIN_PIN E1_DIAG_PIN
      #elif Z2_USE_ENDSTOP == _E2DIAG_
        #define Z2_MIN_PIN E2_DIAG_PIN
      #elif Z2_USE_ENDSTOP == _E3DIAG_
        #define Z2_MIN_PIN E3_DIAG_PIN
      #elif Z2_USE_ENDSTOP == _E4DIAG_
        #define Z2_MIN_PIN E4_DIAG_PIN
      #elif Z2_USE_ENDSTOP == _E5DIAG_
        #define Z2_MIN_PIN E5_DIAG_PIN
      #elif Z2_USE_ENDSTOP == _E6DIAG_
        #define Z2_MIN_PIN E6_DIAG_PIN
      #elif Z2_USE_ENDSTOP == _E7DIAG_
        #define Z2_MIN_PIN E7_DIAG_PIN
      #endif
    #endif
    #ifndef Z2_MAX_ENDSTOP_INVERTING
      #define Z2_MAX_ENDSTOP_INVERTING false
    #endif
  #endif

  #if NUM_Z_STEPPER_DRIVERS >= 3
    #if Z_HOME_TO_MAX
      #ifndef Z3_MAX_ENDSTOP_INVERTING
        #if Z3_USE_ENDSTOP == _XMIN_
          #define Z3_MAX_ENDSTOP_INVERTING X_MIN_ENDSTOP_INVERTING
        #elif Z3_USE_ENDSTOP == _XMAX_
          #define Z3_MAX_ENDSTOP_INVERTING X_MAX_ENDSTOP_INVERTING
        #elif Z3_USE_ENDSTOP == _YMIN_
          #define Z3_MAX_ENDSTOP_INVERTING Y_MIN_ENDSTOP_INVERTING
        #elif Z3_USE_ENDSTOP == _YMAX_
          #define Z3_MAX_ENDSTOP_INVERTING Y_MAX_ENDSTOP_INVERTING
        #elif Z3_USE_ENDSTOP == _ZMIN_
          #define Z3_MAX_ENDSTOP_INVERTING Z_MIN_ENDSTOP_INVERTING
        #elif Z3_USE_ENDSTOP == _ZMAX_
          #define Z3_MAX_ENDSTOP_INVERTING Z_MAX_ENDSTOP_INVERTING
        #else
          #define Z3_MAX_ENDSTOP_INVERTING false
        #endif
      #endif
      #ifndef Z3_MAX_PIN
        #if Z3_USE_ENDSTOP == _XMIN_
          #define Z3_MAX_PIN X_MIN_PIN
        #elif Z3_USE_ENDSTOP == _XMAX_
          #define Z3_MAX_PIN X_MAX_PIN
        #elif Z3_USE_ENDSTOP == _YMIN_
          #define Z3_MAX_PIN Y_MIN_PIN
        #elif Z3_USE_ENDSTOP == _YMAX_
          #define Z3_MAX_PIN Y_MAX_PIN
        #elif Z3_USE_ENDSTOP == _ZMIN_
          #define Z3_MAX_PIN Z_MIN_PIN
        #elif Z3_USE_ENDSTOP == _ZMAX_
          #define Z3_MAX_PIN Z_MAX_PIN
        #elif Z3_USE_ENDSTOP == _XDIAG_
          #define Z3_MAX_PIN X_DIAG_PIN
        #elif Z3_USE_ENDSTOP == _YDIAG_
          #define Z3_MAX_PIN Y_DIAG_PIN
        #elif Z3_USE_ENDSTOP == _ZDIAG_
          #define Z3_MAX_PIN Z_DIAG_PIN
        #elif Z3_USE_ENDSTOP == _E0DIAG_
          #define Z3_MAX_PIN E0_DIAG_PIN
        #elif Z3_USE_ENDSTOP == _E1DIAG_
          #define Z3_MAX_PIN E1_DIAG_PIN
        #elif Z3_USE_ENDSTOP == _E2DIAG_
          #define Z3_MAX_PIN E2_DIAG_PIN
        #elif Z3_USE_ENDSTOP == _E3DIAG_
          #define Z3_MAX_PIN E3_DIAG_PIN
        #elif Z3_USE_ENDSTOP == _E4DIAG_
          #define Z3_MAX_PIN E4_DIAG_PIN
        #elif Z3_USE_ENDSTOP == _E5DIAG_
          #define Z3_MAX_PIN E5_DIAG_PIN
        #elif Z3_USE_ENDSTOP == _E6DIAG_
          #define Z3_MAX_PIN E6_DIAG_PIN
        #elif Z3_USE_ENDSTOP == _E7DIAG_
          #define Z3_MAX_PIN E7_DIAG_PIN
        #endif
      #endif
      #ifndef Z3_MIN_ENDSTOP_INVERTING
        #define Z3_MIN_ENDSTOP_INVERTING false
      #endif
    #else
      #ifndef Z3_MIN_ENDSTOP_INVERTING
        #if Z3_USE_ENDSTOP == _XMIN_
          #define Z3_MIN_ENDSTOP_INVERTING X_MIN_ENDSTOP_INVERTING
        #elif Z3_USE_ENDSTOP == _XMAX_
          #define Z3_MIN_ENDSTOP_INVERTING X_MAX_ENDSTOP_INVERTING
        #elif Z3_USE_ENDSTOP == _YMIN_
          #define Z3_MIN_ENDSTOP_INVERTING Y_MIN_ENDSTOP_INVERTING
        #elif Z3_USE_ENDSTOP == _YMAX_
          #define Z3_MIN_ENDSTOP_INVERTING Y_MAX_ENDSTOP_INVERTING
        #elif Z3_USE_ENDSTOP == _ZMIN_
          #define Z3_MIN_ENDSTOP_INVERTING Z_MIN_ENDSTOP_INVERTING
        #elif Z3_USE_ENDSTOP == _ZMAX_
          #define Z3_MIN_ENDSTOP_INVERTING Z_MAX_ENDSTOP_INVERTING
        #else
          #define Z3_MIN_ENDSTOP_INVERTING false
        #endif
      #endif
      #ifndef Z3_MIN_PIN
        #if Z3_USE_ENDSTOP == _XMIN_
          #define Z3_MIN_PIN X_MIN_PIN
        #elif Z3_USE_ENDSTOP == _XMAX_
          #define Z3_MIN_PIN X_MAX_PIN
        #elif Z3_USE_ENDSTOP == _YMIN_
          #define Z3_MIN_PIN Y_MIN_PIN
        #elif Z3_USE_ENDSTOP == _YMAX_
          #define Z3_MIN_PIN Y_MAX_PIN
        #elif Z3_USE_ENDSTOP == _ZMIN_
          #define Z3_MIN_PIN Z_MIN_PIN
        #elif Z3_USE_ENDSTOP == _ZMAX_
          #define Z3_MIN_PIN Z_MAX_PIN
        #elif Z3_USE_ENDSTOP == _XDIAG_
          #define Z3_MIN_PIN X_DIAG_PIN
        #elif Z3_USE_ENDSTOP == _YDIAG_
          #define Z3_MIN_PIN Y_DIAG_PIN
        #elif Z3_USE_ENDSTOP == _ZDIAG_
          #define Z3_MIN_PIN Z_DIAG_PIN
        #elif Z3_USE_ENDSTOP == _E0DIAG_
          #define Z3_MIN_PIN E0_DIAG_PIN
        #elif Z3_USE_ENDSTOP == _E1DIAG_
          #define Z3_MIN_PIN E1_DIAG_PIN
        #elif Z3_USE_ENDSTOP == _E2DIAG_
          #define Z3_MIN_PIN E2_DIAG_PIN
        #elif Z3_USE_ENDSTOP == _E3DIAG_
          #define Z3_MIN_PIN E3_DIAG_PIN
        #elif Z3_USE_ENDSTOP == _E4DIAG_
          #define Z3_MIN_PIN E4_DIAG_PIN
        #elif Z3_USE_ENDSTOP == _E5DIAG_
          #define Z3_MIN_PIN E5_DIAG_PIN
        #elif Z3_USE_ENDSTOP == _E6DIAG_
          #define Z3_MIN_PIN E6_DIAG_PIN
        #elif Z3_USE_ENDSTOP == _E7DIAG_
          #define Z3_MIN_PIN E7_DIAG_PIN
        #endif
      #endif
      #ifndef Z3_MAX_ENDSTOP_INVERTING
        #define Z3_MAX_ENDSTOP_INVERTING false
      #endif
    #endif
  #endif

  #if NUM_Z_STEPPER_DRIVERS >= 4
    #if Z_HOME_TO_MAX
      #ifndef Z4_MAX_ENDSTOP_INVERTING
        #if Z4_USE_ENDSTOP == _XMIN_
          #define Z4_MAX_ENDSTOP_INVERTING X_MIN_ENDSTOP_INVERTING
        #elif Z4_USE_ENDSTOP == _XMAX_
          #define Z4_MAX_ENDSTOP_INVERTING X_MAX_ENDSTOP_INVERTING
        #elif Z4_USE_ENDSTOP == _YMIN_
          #define Z4_MAX_ENDSTOP_INVERTING Y_MIN_ENDSTOP_INVERTING
        #elif Z4_USE_ENDSTOP == _YMAX_
          #define Z4_MAX_ENDSTOP_INVERTING Y_MAX_ENDSTOP_INVERTING
        #elif Z4_USE_ENDSTOP == _ZMIN_
          #define Z4_MAX_ENDSTOP_INVERTING Z_MIN_ENDSTOP_INVERTING
        #elif Z4_USE_ENDSTOP == _ZMAX_
          #define Z4_MAX_ENDSTOP_INVERTING Z_MAX_ENDSTOP_INVERTING
        #else
          #define Z4_MAX_ENDSTOP_INVERTING false
        #endif
      #endif
      #ifndef Z4_MAX_PIN
        #if Z4_USE_ENDSTOP == _XMIN_
          #define Z4_MAX_PIN X_MIN_PIN
        #elif Z4_USE_ENDSTOP == _XMAX_
          #define Z4_MAX_PIN X_MAX_PIN
        #elif Z4_USE_ENDSTOP == _YMIN_
          #define Z4_MAX_PIN Y_MIN_PIN
        #elif Z4_USE_ENDSTOP == _YMAX_
          #define Z4_MAX_PIN Y_MAX_PIN
        #elif Z4_USE_ENDSTOP == _ZMIN_
          #define Z4_MAX_PIN Z_MIN_PIN
        #elif Z4_USE_ENDSTOP == _ZMAX_
          #define Z4_MAX_PIN Z_MAX_PIN
        #elif Z4_USE_ENDSTOP == _XDIAG_
          #define Z4_MAX_PIN X_DIAG_PIN
        #elif Z4_USE_ENDSTOP == _YDIAG_
          #define Z4_MAX_PIN Y_DIAG_PIN
        #elif Z4_USE_ENDSTOP == _ZDIAG_
          #define Z4_MAX_PIN Z_DIAG_PIN
        #elif Z4_USE_ENDSTOP == _E0DIAG_
          #define Z4_MAX_PIN E0_DIAG_PIN
        #elif Z4_USE_ENDSTOP == _E1DIAG_
          #define Z4_MAX_PIN E1_DIAG_PIN
        #elif Z4_USE_ENDSTOP == _E2DIAG_
          #define Z4_MAX_PIN E2_DIAG_PIN
        #elif Z4_USE_ENDSTOP == _E3DIAG_
          #define Z4_MAX_PIN E3_DIAG_PIN
        #elif Z4_USE_ENDSTOP == _E4DIAG_
          #define Z4_MAX_PIN E4_DIAG_PIN
        #elif Z4_USE_ENDSTOP == _E5DIAG_
          #define Z4_MAX_PIN E5_DIAG_PIN
        #elif Z4_USE_ENDSTOP == _E6DIAG_
          #define Z4_MAX_PIN E6_DIAG_PIN
        #elif Z4_USE_ENDSTOP == _E7DIAG_
          #define Z4_MAX_PIN E7_DIAG_PIN
        #endif
      #endif
      #ifndef Z4_MIN_ENDSTOP_INVERTING
        #define Z4_MIN_ENDSTOP_INVERTING false
      #endif
    #else
      #ifndef Z4_MIN_ENDSTOP_INVERTING
        #if Z4_USE_ENDSTOP == _XMIN_
          #define Z4_MIN_ENDSTOP_INVERTING X_MIN_ENDSTOP_INVERTING
        #elif Z4_USE_ENDSTOP == _XMAX_
          #define Z4_MIN_ENDSTOP_INVERTING X_MAX_ENDSTOP_INVERTING
        #elif Z4_USE_ENDSTOP == _YMIN_
          #define Z4_MIN_ENDSTOP_INVERTING Y_MIN_ENDSTOP_INVERTING
        #elif Z4_USE_ENDSTOP == _YMAX_
          #define Z4_MIN_ENDSTOP_INVERTING Y_MAX_ENDSTOP_INVERTING
        #elif Z4_USE_ENDSTOP == _ZMIN_
          #define Z4_MIN_ENDSTOP_INVERTING Z_MIN_ENDSTOP_INVERTING
        #elif Z4_USE_ENDSTOP == _ZMAX_
          #define Z4_MIN_ENDSTOP_INVERTING Z_MAX_ENDSTOP_INVERTING
        #else
          #define Z4_MIN_ENDSTOP_INVERTING false
        #endif
      #endif
      #ifndef Z4_MIN_PIN
        #if Z4_USE_ENDSTOP == _XMIN_
          #define Z4_MIN_PIN X_MIN_PIN
        #elif Z4_USE_ENDSTOP == _XMAX_
          #define Z4_MIN_PIN X_MAX_PIN
        #elif Z4_USE_ENDSTOP == _YMIN_
          #define Z4_MIN_PIN Y_MIN_PIN
        #elif Z4_USE_ENDSTOP == _YMAX_
          #define Z4_MIN_PIN Y_MAX_PIN
        #elif Z4_USE_ENDSTOP == _ZMIN_
          #define Z4_MIN_PIN Z_MIN_PIN
        #elif Z4_USE_ENDSTOP == _ZMAX_
          #define Z4_MIN_PIN Z_MAX_PIN
        #elif Z4_USE_ENDSTOP == _XDIAG_
          #define Z4_MIN_PIN X_DIAG_PIN
        #elif Z4_USE_ENDSTOP == _YDIAG_
          #define Z4_MIN_PIN Y_DIAG_PIN
        #elif Z4_USE_ENDSTOP == _ZDIAG_
          #define Z4_MIN_PIN Z_DIAG_PIN
        #elif Z4_USE_ENDSTOP == _E0DIAG_
          #define Z4_MIN_PIN E0_DIAG_PIN
        #elif Z4_USE_ENDSTOP == _E1DIAG_
          #define Z4_MIN_PIN E1_DIAG_PIN
        #elif Z4_USE_ENDSTOP == _E2DIAG_
          #define Z4_MIN_PIN E2_DIAG_PIN
        #elif Z4_USE_ENDSTOP == _E3DIAG_
          #define Z4_MIN_PIN E3_DIAG_PIN
        #elif Z4_USE_ENDSTOP == _E4DIAG_
          #define Z4_MIN_PIN E4_DIAG_PIN
        #elif Z4_USE_ENDSTOP == _E5DIAG_
          #define Z4_MIN_PIN E5_DIAG_PIN
        #elif Z4_USE_ENDSTOP == _E6DIAG_
          #define Z4_MIN_PIN E6_DIAG_PIN
        #elif Z4_USE_ENDSTOP == _E7DIAG_
          #define Z4_MIN_PIN E7_DIAG_PIN
        #endif
      #endif
      #ifndef Z4_MAX_ENDSTOP_INVERTING
        #define Z4_MAX_ENDSTOP_INVERTING false
      #endif
    #endif
  #endif

#endif // Z_MULTI_ENDSTOPS
>>>>>>> mcu_ctrl

/**
 * Set ENDSTOPPULLUPS for active endstop switches
 */
#if ENABLED(ENDSTOPPULLUPS)
  #if ENABLED(USE_XMAX_PLUG)
    #define ENDSTOPPULLUP_XMAX
  #endif
  #if ENABLED(USE_YMAX_PLUG)
    #define ENDSTOPPULLUP_YMAX
  #endif
  #if ENABLED(USE_ZMAX_PLUG)
    #define ENDSTOPPULLUP_ZMAX
  #endif
  #if ENABLED(USE_XMIN_PLUG)
    #define ENDSTOPPULLUP_XMIN
  #endif
  #if ENABLED(USE_YMIN_PLUG)
    #define ENDSTOPPULLUP_YMIN
  #endif
  #if ENABLED(USE_ZMIN_PLUG)
    #define ENDSTOPPULLUP_ZMIN
  #endif
#endif

/**
 * Set ENDSTOPPULLDOWNS for active endstop switches
 */
#if ENABLED(ENDSTOPPULLDOWNS)
  #if ENABLED(USE_XMAX_PLUG)
    #define ENDSTOPPULLDOWN_XMAX
  #endif
<<<<<<< HEAD
  #if ENABLED(USE_YMAX_PLUG)
    #define ENDSTOPPULLDOWN_YMAX
  #endif
  #if ENABLED(USE_ZMAX_PLUG)
    #define ENDSTOPPULLDOWN_ZMAX
  #endif
  #if ENABLED(USE_XMIN_PLUG)
    #define ENDSTOPPULLDOWN_XMIN
  #endif
  #if ENABLED(USE_YMIN_PLUG)
    #define ENDSTOPPULLDOWN_YMIN
  #endif
  #if ENABLED(USE_ZMIN_PLUG)
    #define ENDSTOPPULLDOWN_ZMIN
  #endif
#endif

/**
 * Shorthand for pin tests, used wherever needed
 */

// Steppers
#define HAS_X_ENABLE      (PIN_EXISTS(X_ENABLE) || (ENABLED(SOFTWARE_DRIVER_ENABLE) && AXIS_IS_TMC(X)))
#define HAS_X_DIR         (PIN_EXISTS(X_DIR))
#define HAS_X_STEP        (PIN_EXISTS(X_STEP))
#define HAS_X_MICROSTEPS  (PIN_EXISTS(X_MS1))

#define HAS_X2_ENABLE     (PIN_EXISTS(X2_ENABLE) || (ENABLED(SOFTWARE_DRIVER_ENABLE) && AXIS_IS_TMC(X2)))
#define HAS_X2_DIR        (PIN_EXISTS(X2_DIR))
#define HAS_X2_STEP       (PIN_EXISTS(X2_STEP))
#define HAS_X2_MICROSTEPS (PIN_EXISTS(X2_MS1))

#define HAS_Y_ENABLE      (PIN_EXISTS(Y_ENABLE) || (ENABLED(SOFTWARE_DRIVER_ENABLE) && AXIS_IS_TMC(Y)))
#define HAS_Y_DIR         (PIN_EXISTS(Y_DIR))
#define HAS_Y_STEP        (PIN_EXISTS(Y_STEP))
#define HAS_Y_MICROSTEPS  (PIN_EXISTS(Y_MS1))

#define HAS_Y2_ENABLE     (PIN_EXISTS(Y2_ENABLE) || (ENABLED(SOFTWARE_DRIVER_ENABLE) && AXIS_IS_TMC(Y2)))
#define HAS_Y2_DIR        (PIN_EXISTS(Y2_DIR))
#define HAS_Y2_STEP       (PIN_EXISTS(Y2_STEP))
#define HAS_Y2_MICROSTEPS (PIN_EXISTS(Y2_MS1))

#define HAS_Z_ENABLE      (PIN_EXISTS(Z_ENABLE) || (ENABLED(SOFTWARE_DRIVER_ENABLE) && AXIS_IS_TMC(Z)))
#define HAS_Z_DIR         (PIN_EXISTS(Z_DIR))
#define HAS_Z_STEP        (PIN_EXISTS(Z_STEP))
#define HAS_Z_MICROSTEPS  (PIN_EXISTS(Z_MS1))

#define HAS_Z2_ENABLE     (PIN_EXISTS(Z2_ENABLE) || (ENABLED(SOFTWARE_DRIVER_ENABLE) && AXIS_IS_TMC(Z2)))
#define HAS_Z2_DIR        (PIN_EXISTS(Z2_DIR))
#define HAS_Z2_STEP       (PIN_EXISTS(Z2_STEP))
#define HAS_Z2_MICROSTEPS (PIN_EXISTS(Z2_MS1))

#define HAS_Z3_ENABLE     (PIN_EXISTS(Z3_ENABLE) || (ENABLED(SOFTWARE_DRIVER_ENABLE) && AXIS_IS_TMC(Z3)))
#define HAS_Z3_DIR        (PIN_EXISTS(Z3_DIR))
#define HAS_Z3_STEP       (PIN_EXISTS(Z3_STEP))
#define HAS_Z3_MICROSTEPS (PIN_EXISTS(Z3_MS1))

// Extruder steppers and solenoids
#define HAS_E0_ENABLE     (PIN_EXISTS(E0_ENABLE) || (ENABLED(SOFTWARE_DRIVER_ENABLE) && AXIS_IS_TMC(E0)))
#define HAS_E0_DIR        (PIN_EXISTS(E0_DIR))
#define HAS_E0_STEP       (PIN_EXISTS(E0_STEP))
#define HAS_E0_MICROSTEPS (PIN_EXISTS(E0_MS1))
#define HAS_SOLENOID_0    (PIN_EXISTS(SOL0))

#define HAS_E1_ENABLE     (PIN_EXISTS(E1_ENABLE) || (ENABLED(SOFTWARE_DRIVER_ENABLE) && AXIS_IS_TMC(E1)))
#define HAS_E1_DIR        (PIN_EXISTS(E1_DIR))
#define HAS_E1_STEP       (PIN_EXISTS(E1_STEP))
#define HAS_E1_MICROSTEPS (PIN_EXISTS(E1_MS1))
#define HAS_SOLENOID_1    (PIN_EXISTS(SOL1))

#define HAS_E2_ENABLE     (PIN_EXISTS(E2_ENABLE) || (ENABLED(SOFTWARE_DRIVER_ENABLE) && AXIS_IS_TMC(E2)))
#define HAS_E2_DIR        (PIN_EXISTS(E2_DIR))
#define HAS_E2_STEP       (PIN_EXISTS(E2_STEP))
#define HAS_E2_MICROSTEPS (PIN_EXISTS(E2_MS1))
#define HAS_SOLENOID_2    (PIN_EXISTS(SOL2))

#define HAS_E3_ENABLE     (PIN_EXISTS(E3_ENABLE) || (ENABLED(SOFTWARE_DRIVER_ENABLE) && AXIS_IS_TMC(E3)))
#define HAS_E3_DIR        (PIN_EXISTS(E3_DIR))
#define HAS_E3_STEP       (PIN_EXISTS(E3_STEP))
#define HAS_E3_MICROSTEPS (PIN_EXISTS(E3_MS1))
#define HAS_SOLENOID_3    (PIN_EXISTS(SOL3))

#define HAS_E4_ENABLE     (PIN_EXISTS(E4_ENABLE) || (ENABLED(SOFTWARE_DRIVER_ENABLE) && AXIS_IS_TMC(E4)))
#define HAS_E4_DIR        (PIN_EXISTS(E4_DIR))
#define HAS_E4_STEP       (PIN_EXISTS(E4_STEP))
#define HAS_E4_MICROSTEPS (PIN_EXISTS(E4_MS1))
#define HAS_SOLENOID_4    (PIN_EXISTS(SOL4))

#define HAS_E5_ENABLE     (PIN_EXISTS(E5_ENABLE) || (ENABLED(SOFTWARE_DRIVER_ENABLE) && AXIS_IS_TMC(E5)))
#define HAS_E5_DIR        (PIN_EXISTS(E5_DIR))
#define HAS_E5_STEP       (PIN_EXISTS(E5_STEP))
#define HAS_E5_MICROSTEPS (PIN_EXISTS(E5_MS1))
#define HAS_SOLENOID_5    (PIN_EXISTS(SOL5))

// Trinamic Stepper Drivers
#if HAS_TRINAMIC
  #define HAS_TMCX1X0       (HAS_DRIVER(TMC2130) || HAS_DRIVER(TMC2160) || HAS_DRIVER(TMC5130) || HAS_DRIVER(TMC5160))
  #define TMC_HAS_SPI       (HAS_TMCX1X0 || HAS_DRIVER(TMC2660))
  #define HAS_STALLGUARD    (HAS_TMCX1X0 || HAS_DRIVER(TMC2209) || HAS_DRIVER(TMC2660))
  #define HAS_STEALTHCHOP   (HAS_TMCX1X0 || HAS_TMC220x)

  #define STEALTHCHOP_ENABLED ANY(STEALTHCHOP_XY, STEALTHCHOP_Z, STEALTHCHOP_E)
  #define USE_SENSORLESS EITHER(SENSORLESS_HOMING, SENSORLESS_PROBING)
  // Disable Z axis sensorless homing if a probe is used to home the Z axis
  #if HOMING_Z_WITH_PROBE
    #undef Z_STALL_SENSITIVITY
  #endif
  #define X_SENSORLESS  (AXIS_HAS_STALLGUARD(X)  && defined(X_STALL_SENSITIVITY))
  #define X2_SENSORLESS (AXIS_HAS_STALLGUARD(X2) && defined(X2_STALL_SENSITIVITY))
  #define Y_SENSORLESS  (AXIS_HAS_STALLGUARD(Y)  && defined(Y_STALL_SENSITIVITY))
  #define Y2_SENSORLESS (AXIS_HAS_STALLGUARD(Y2) && defined(Y2_STALL_SENSITIVITY))
  #define Z_SENSORLESS  (AXIS_HAS_STALLGUARD(Z)  && defined(Z_STALL_SENSITIVITY))
  #define Z2_SENSORLESS (AXIS_HAS_STALLGUARD(Z2) && defined(Z2_STALL_SENSITIVITY))
  #define Z3_SENSORLESS (AXIS_HAS_STALLGUARD(Z3) && defined(Z3_STALL_SENSITIVITY))
  #if ENABLED(SPI_ENDSTOPS)
    #define X_SPI_SENSORLESS X_SENSORLESS
    #define Y_SPI_SENSORLESS Y_SENSORLESS
    #define Z_SPI_SENSORLESS Z_SENSORLESS
  #endif
#endif

#define HAS_E_STEPPER_ENABLE (HAS_E_DRIVER(TMC2660) \
  || ( E0_ENABLE_PIN != X_ENABLE_PIN && E1_ENABLE_PIN != X_ENABLE_PIN   \
    && E0_ENABLE_PIN != Y_ENABLE_PIN && E1_ENABLE_PIN != Y_ENABLE_PIN ) \
)

// Endstops and bed probe
#define _HAS_STOP(A,M) (PIN_EXISTS(A##_##M) && !IS_X2_ENDSTOP(A,M) && !IS_Y2_ENDSTOP(A,M) && !IS_Z2_OR_PROBE(A,M))
#define HAS_X_MIN _HAS_STOP(X,MIN)
#define HAS_X_MAX _HAS_STOP(X,MAX)
#define HAS_Y_MIN _HAS_STOP(Y,MIN)
#define HAS_Y_MAX _HAS_STOP(Y,MAX)
#define HAS_Z_MIN _HAS_STOP(Z,MIN)
#define HAS_Z_MAX _HAS_STOP(Z,MAX)
#define HAS_X2_MIN (PIN_EXISTS(X2_MIN))
#define HAS_X2_MAX (PIN_EXISTS(X2_MAX))
#define HAS_Y2_MIN (PIN_EXISTS(Y2_MIN))
#define HAS_Y2_MAX (PIN_EXISTS(Y2_MAX))
#define HAS_Z2_MIN (PIN_EXISTS(Z2_MIN))
#define HAS_Z2_MAX (PIN_EXISTS(Z2_MAX))
#define HAS_Z3_MIN (PIN_EXISTS(Z3_MIN))
#define HAS_Z3_MAX (PIN_EXISTS(Z3_MAX))
#define HAS_Z_MIN_PROBE_PIN (HAS_CUSTOM_PROBE_PIN && PIN_EXISTS(Z_MIN_PROBE))
#define HAS_CALIBRATION_PIN (PIN_EXISTS(CALIBRATION))

// ADC Temp Sensors (Thermistor or Thermocouple with amplifier ADC interface)
#define HAS_ADC_TEST(P) (PIN_EXISTS(TEMP_##P) && TEMP_SENSOR_##P != 0 && DISABLED(HEATER_##P##_USES_MAX6675))
#define HAS_TEMP_ADC_0 HAS_ADC_TEST(0)
#define HAS_TEMP_ADC_1 HAS_ADC_TEST(1)
#define HAS_TEMP_ADC_2 HAS_ADC_TEST(2)
#define HAS_TEMP_ADC_3 HAS_ADC_TEST(3)
#define HAS_TEMP_ADC_4 HAS_ADC_TEST(4)
#define HAS_TEMP_ADC_5 HAS_ADC_TEST(5)
#define HAS_TEMP_ADC_BED HAS_ADC_TEST(BED)
#define HAS_TEMP_ADC_CHAMBER HAS_ADC_TEST(CHAMBER)

#define HAS_TEMP_HOTEND (HOTENDS > 0 && (HAS_TEMP_ADC_0 || ENABLED(HEATER_0_USES_MAX6675)))
#define HAS_TEMP_BED HAS_TEMP_ADC_BED
#define HAS_TEMP_CHAMBER HAS_TEMP_ADC_CHAMBER
#define HAS_HEATED_CHAMBER (HAS_TEMP_CHAMBER && PIN_EXISTS(HEATER_CHAMBER))

#if ENABLED(JOYSTICK)
  #define HAS_JOY_ADC_X  PIN_EXISTS(JOY_X)
  #define HAS_JOY_ADC_Y  PIN_EXISTS(JOY_Y)
  #define HAS_JOY_ADC_Z  PIN_EXISTS(JOY_Z)
  #define HAS_JOY_ADC_EN PIN_EXISTS(JOY_EN)
#endif

// Heaters
#define HAS_HEATER_0 (PIN_EXISTS(HEATER_0))
#define HAS_HEATER_1 (PIN_EXISTS(HEATER_1))
#define HAS_HEATER_2 (PIN_EXISTS(HEATER_2))
#define HAS_HEATER_3 (PIN_EXISTS(HEATER_3))
#define HAS_HEATER_4 (PIN_EXISTS(HEATER_4))
#define HAS_HEATER_5 (PIN_EXISTS(HEATER_5))
#define HAS_HEATER_BED (PIN_EXISTS(HEATER_BED))

// Shorthand for common combinations
#define HAS_HEATED_BED (HAS_TEMP_BED && HAS_HEATER_BED)
#define BED_OR_CHAMBER (HAS_HEATED_BED || HAS_TEMP_CHAMBER)
#define HAS_TEMP_SENSOR (HAS_TEMP_HOTEND || BED_OR_CHAMBER)

#if !HAS_TEMP_SENSOR
  #undef AUTO_REPORT_TEMPERATURES
#endif

// PID heating
#if !HAS_HEATED_BED
  #undef PIDTEMPBED
#endif
#define HAS_PID_HEATING EITHER(PIDTEMP, PIDTEMPBED)
#define HAS_PID_FOR_BOTH BOTH(PIDTEMP, PIDTEMPBED)

// Thermal protection
#define HAS_THERMALLY_PROTECTED_BED (HAS_HEATED_BED && ENABLED(THERMAL_PROTECTION_BED))
#define WATCH_HOTENDS (ENABLED(THERMAL_PROTECTION_HOTENDS) && WATCH_TEMP_PERIOD > 0)
#define WATCH_BED (HAS_THERMALLY_PROTECTED_BED && WATCH_BED_TEMP_PERIOD > 0)
#define WATCH_CHAMBER (HAS_HEATED_CHAMBER && ENABLED(THERMAL_PROTECTION_CHAMBER) && WATCH_CHAMBER_TEMP_PERIOD > 0)

// Auto fans
#define HAS_AUTO_FAN_0 (HOTENDS > 0 && PIN_EXISTS(E0_AUTO_FAN))
#define HAS_AUTO_FAN_1 (HOTENDS > 1 && PIN_EXISTS(E1_AUTO_FAN))
#define HAS_AUTO_FAN_2 (HOTENDS > 2 && PIN_EXISTS(E2_AUTO_FAN))
#define HAS_AUTO_FAN_3 (HOTENDS > 3 && PIN_EXISTS(E3_AUTO_FAN))
#define HAS_AUTO_FAN_4 (HOTENDS > 4 && PIN_EXISTS(E4_AUTO_FAN))
#define HAS_AUTO_FAN_5 (HOTENDS > 5 && PIN_EXISTS(E5_AUTO_FAN))
#define HAS_AUTO_CHAMBER_FAN (HAS_TEMP_CHAMBER && PIN_EXISTS(CHAMBER_AUTO_FAN))

#define HAS_AUTO_FAN (HAS_AUTO_FAN_0 || HAS_AUTO_FAN_1 || HAS_AUTO_FAN_2 || HAS_AUTO_FAN_3 || HAS_AUTO_FAN_4 || HAS_AUTO_FAN_5 || HAS_AUTO_CHAMBER_FAN)
#define _FANOVERLAP(A,B) (A##_AUTO_FAN_PIN == E##B##_AUTO_FAN_PIN)
#if HAS_AUTO_FAN
  #define AUTO_CHAMBER_IS_E (_FANOVERLAP(CHAMBER,0) || _FANOVERLAP(CHAMBER,1) || _FANOVERLAP(CHAMBER,2) || _FANOVERLAP(CHAMBER,3) || _FANOVERLAP(CHAMBER,4) || _FANOVERLAP(CHAMBER,5))
=======
  #if ENABLED(USE_YMAX_PLUG)
    #define ENDSTOPPULLDOWN_YMAX
  #endif
  #if ENABLED(USE_ZMAX_PLUG)
    #define ENDSTOPPULLDOWN_ZMAX
  #endif
  #if ENABLED(USE_XMIN_PLUG)
    #define ENDSTOPPULLDOWN_XMIN
  #endif
  #if ENABLED(USE_YMIN_PLUG)
    #define ENDSTOPPULLDOWN_YMIN
  #endif
  #if ENABLED(USE_ZMIN_PLUG)
    #define ENDSTOPPULLDOWN_ZMIN
  #endif
#endif

/**
 * Shorthand for pin tests, used wherever needed
 */

// Steppers
#if PIN_EXISTS(X_ENABLE) || (ENABLED(SOFTWARE_DRIVER_ENABLE) && AXIS_IS_TMC(X))
  #define HAS_X_ENABLE 1
#endif
#if PIN_EXISTS(X_DIR)
  #define HAS_X_DIR 1
#endif
#if PIN_EXISTS(X_STEP)
  #define HAS_X_STEP 1
#endif
#if PIN_EXISTS(X_MS1)
  #define HAS_X_MS_PINS 1
#endif

#if PIN_EXISTS(X2_ENABLE) || (ENABLED(SOFTWARE_DRIVER_ENABLE) && AXIS_IS_TMC(X2))
  #define HAS_X2_ENABLE 1
#endif
#if PIN_EXISTS(X2_DIR)
  #define HAS_X2_DIR 1
#endif
#if PIN_EXISTS(X2_STEP)
  #define HAS_X2_STEP 1
#endif
#if PIN_EXISTS(X2_MS1)
  #define HAS_X2_MS_PINS 1
#endif

#if PIN_EXISTS(Y_ENABLE) || (ENABLED(SOFTWARE_DRIVER_ENABLE) && AXIS_IS_TMC(Y))
  #define HAS_Y_ENABLE 1
#endif
#if PIN_EXISTS(Y_DIR)
  #define HAS_Y_DIR 1
#endif
#if PIN_EXISTS(Y_STEP)
  #define HAS_Y_STEP 1
#endif
#if PIN_EXISTS(Y_MS1)
  #define HAS_Y_MS_PINS 1
#endif

#if PIN_EXISTS(Y2_ENABLE) || (ENABLED(SOFTWARE_DRIVER_ENABLE) && AXIS_IS_TMC(Y2))
  #define HAS_Y2_ENABLE 1
#endif
#if PIN_EXISTS(Y2_DIR)
  #define HAS_Y2_DIR 1
#endif
#if PIN_EXISTS(Y2_STEP)
  #define HAS_Y2_STEP 1
#endif
#if PIN_EXISTS(Y2_MS1)
  #define HAS_Y2_MS_PINS 1
#endif

#if PIN_EXISTS(Z_ENABLE) || (ENABLED(SOFTWARE_DRIVER_ENABLE) && AXIS_IS_TMC(Z))
  #define HAS_Z_ENABLE 1
#endif
#if PIN_EXISTS(Z_DIR)
  #define HAS_Z_DIR 1
#endif
#if PIN_EXISTS(Z_STEP)
  #define HAS_Z_STEP 1
#endif
#if PIN_EXISTS(Z_MS1)
  #define HAS_Z_MS_PINS 1
#endif

#if PIN_EXISTS(Z2_ENABLE) || (ENABLED(SOFTWARE_DRIVER_ENABLE) && AXIS_IS_TMC(Z2))
  #define HAS_Z2_ENABLE 1
#endif
#if PIN_EXISTS(Z2_DIR)
  #define HAS_Z2_DIR 1
#endif
#if PIN_EXISTS(Z2_STEP)
  #define HAS_Z2_STEP 1
#endif
#if PIN_EXISTS(Z2_MS1)
  #define HAS_Z2_MS_PINS 1
#endif

#if PIN_EXISTS(Z3_ENABLE) || (ENABLED(SOFTWARE_DRIVER_ENABLE) && AXIS_IS_TMC(Z3))
  #define HAS_Z3_ENABLE 1
#endif
#if PIN_EXISTS(Z3_DIR)
  #define HAS_Z3_DIR 1
#endif
#if PIN_EXISTS(Z3_STEP)
  #define HAS_Z3_STEP 1
#endif
#if PIN_EXISTS(Z3_MS1)
  #define HAS_Z3_MS_PINS 1
#endif

#if PIN_EXISTS(Z4_ENABLE) || (ENABLED(SOFTWARE_DRIVER_ENABLE) && AXIS_IS_TMC(Z4))
  #define HAS_Z4_ENABLE 1
#endif
#if PIN_EXISTS(Z4_DIR)
  #define HAS_Z4_DIR 1
#endif
#if PIN_EXISTS(Z4_STEP)
  #define HAS_Z4_STEP 1
#endif
#if PIN_EXISTS(Z4_MS1)
  #define HAS_Z4_MS_PINS 1
#endif

// Extruder steppers and solenoids
#if PIN_EXISTS(E0_ENABLE) || (ENABLED(SOFTWARE_DRIVER_ENABLE) && AXIS_IS_TMC(E0))
  #define HAS_E0_ENABLE 1
#endif
#if PIN_EXISTS(E0_DIR)
  #define HAS_E0_DIR 1
#endif
#if PIN_EXISTS(E0_STEP)
  #define HAS_E0_STEP 1
#endif
#if PIN_EXISTS(E0_MS1)
  #define HAS_E0_MS_PINS 1
#endif
#if PIN_EXISTS(SOL0)
  #define HAS_SOLENOID_0 1
#endif

#if PIN_EXISTS(E1_ENABLE) || (ENABLED(SOFTWARE_DRIVER_ENABLE) && AXIS_IS_TMC(E1))
  #define HAS_E1_ENABLE 1
#endif
#if PIN_EXISTS(E1_DIR)
  #define HAS_E1_DIR 1
#endif
#if PIN_EXISTS(E1_STEP)
  #define HAS_E1_STEP 1
#endif
#if PIN_EXISTS(E1_MS1)
  #define HAS_E1_MS_PINS 1
#endif
#if PIN_EXISTS(SOL1)
  #define HAS_SOLENOID_1 1
#endif

#if PIN_EXISTS(E2_ENABLE) || (ENABLED(SOFTWARE_DRIVER_ENABLE) && AXIS_IS_TMC(E2))
  #define HAS_E2_ENABLE 1
#endif
#if PIN_EXISTS(E2_DIR)
  #define HAS_E2_DIR 1
#endif
#if PIN_EXISTS(E2_STEP)
  #define HAS_E2_STEP 1
#endif
#if PIN_EXISTS(E2_MS1)
  #define HAS_E2_MS_PINS 1
#endif
#if PIN_EXISTS(SOL2)
  #define HAS_SOLENOID_2 1
#endif

#if PIN_EXISTS(E3_ENABLE) || (ENABLED(SOFTWARE_DRIVER_ENABLE) && AXIS_IS_TMC(E3))
  #define HAS_E3_ENABLE 1
#endif
#if PIN_EXISTS(E3_DIR)
  #define HAS_E3_DIR 1
#endif
#if PIN_EXISTS(E3_STEP)
  #define HAS_E3_STEP 1
#endif
#if PIN_EXISTS(E3_MS1)
  #define HAS_E3_MS_PINS 1
#endif
#if PIN_EXISTS(SOL3)
  #define HAS_SOLENOID_3 1
#endif

#if PIN_EXISTS(E4_ENABLE) || (ENABLED(SOFTWARE_DRIVER_ENABLE) && AXIS_IS_TMC(E4))
  #define HAS_E4_ENABLE 1
#endif
#if PIN_EXISTS(E4_DIR)
  #define HAS_E4_DIR 1
#endif
#if PIN_EXISTS(E4_STEP)
  #define HAS_E4_STEP 1
#endif
#if PIN_EXISTS(E4_MS1)
  #define HAS_E4_MS_PINS 1
#endif
#if PIN_EXISTS(SOL4)
  #define HAS_SOLENOID_4 1
#endif

#if PIN_EXISTS(E5_ENABLE) || (ENABLED(SOFTWARE_DRIVER_ENABLE) && AXIS_IS_TMC(E5))
  #define HAS_E5_ENABLE 1
#endif
#if PIN_EXISTS(E5_DIR)
  #define HAS_E5_DIR 1
#endif
#if PIN_EXISTS(E5_STEP)
  #define HAS_E5_STEP 1
#endif
#if PIN_EXISTS(E5_MS1)
  #define HAS_E5_MS_PINS 1
#endif
#if PIN_EXISTS(SOL5)
  #define HAS_SOLENOID_5 1
#endif

#if PIN_EXISTS(E6_ENABLE) || (ENABLED(SOFTWARE_DRIVER_ENABLE) && AXIS_IS_TMC(E6))
  #define HAS_E6_ENABLE 1
#endif
#if PIN_EXISTS(E6_DIR)
  #define HAS_E6_DIR 1
#endif
#if PIN_EXISTS(E6_STEP)
  #define HAS_E6_STEP 1
#endif
#if PIN_EXISTS(E6_MS1)
  #define HAS_E6_MS_PINS 1
#endif
#if PIN_EXISTS(SOL6)
  #define HAS_SOLENOID_6 1
#endif

#if PIN_EXISTS(E7_ENABLE) || (ENABLED(SOFTWARE_DRIVER_ENABLE) && AXIS_IS_TMC(E7))
  #define HAS_E7_ENABLE 1
#endif
#if PIN_EXISTS(E7_DIR)
  #define HAS_E7_DIR 1
#endif
#if PIN_EXISTS(E7_STEP)
  #define HAS_E7_STEP 1
#endif
#if PIN_EXISTS(E7_MS1)
  #define HAS_E7_MS_PINS 1
#endif
#if PIN_EXISTS(SOL7)
  #define HAS_SOLENOID_7 1
#endif

//
// Trinamic Stepper Drivers
//

#if HAS_TRINAMIC_CONFIG
  #if ANY(STEALTHCHOP_XY, STEALTHCHOP_Z, STEALTHCHOP_E)
    #define STEALTHCHOP_ENABLED 1
  #endif
  #if EITHER(SENSORLESS_HOMING, SENSORLESS_PROBING)
    #define USE_SENSORLESS 1
  #endif
  // Disable Z axis sensorless homing if a probe is used to home the Z axis
  #if HOMING_Z_WITH_PROBE
    #undef Z_STALL_SENSITIVITY
    #undef Z2_STALL_SENSITIVITY
    #undef Z3_STALL_SENSITIVITY
    #undef Z4_STALL_SENSITIVITY
  #endif
  #if defined(X_STALL_SENSITIVITY)  && AXIS_HAS_STALLGUARD(X)
    #define X_SENSORLESS 1
  #endif
  #if defined(X2_STALL_SENSITIVITY) && AXIS_HAS_STALLGUARD(X2)
    #define X2_SENSORLESS 1
  #endif
  #if defined(Y_STALL_SENSITIVITY)  && AXIS_HAS_STALLGUARD(Y)
    #define Y_SENSORLESS 1
  #endif
  #if defined(Y2_STALL_SENSITIVITY) && AXIS_HAS_STALLGUARD(Y2)
    #define Y2_SENSORLESS 1
  #endif
  #if defined(Z_STALL_SENSITIVITY)  && AXIS_HAS_STALLGUARD(Z)
    #define Z_SENSORLESS 1
  #endif
  #if defined(Z2_STALL_SENSITIVITY) && AXIS_HAS_STALLGUARD(Z2)
    #define Z2_SENSORLESS 1
  #endif
  #if defined(Z3_STALL_SENSITIVITY) && AXIS_HAS_STALLGUARD(Z3)
    #define Z3_SENSORLESS 1
  #endif
  #if defined(Z4_STALL_SENSITIVITY) && AXIS_HAS_STALLGUARD(Z4)
    #define Z4_SENSORLESS 1
  #endif
  #if ENABLED(SPI_ENDSTOPS)
    #define X_SPI_SENSORLESS X_SENSORLESS
    #define Y_SPI_SENSORLESS Y_SENSORLESS
    #define Z_SPI_SENSORLESS Z_SENSORLESS
  #endif
  #ifndef X_INTERPOLATE
    #define X_INTERPOLATE INTERPOLATE
  #endif
  #ifndef X2_INTERPOLATE
    #define X2_INTERPOLATE INTERPOLATE
  #endif
  #ifndef Y_INTERPOLATE
    #define Y_INTERPOLATE INTERPOLATE
  #endif
  #ifndef Y2_INTERPOLATE
    #define Y2_INTERPOLATE INTERPOLATE
  #endif
  #ifndef Z_INTERPOLATE
    #define Z_INTERPOLATE INTERPOLATE
  #endif
  #ifndef Z2_INTERPOLATE
    #define Z2_INTERPOLATE INTERPOLATE
  #endif
  #ifndef Z3_INTERPOLATE
    #define Z3_INTERPOLATE INTERPOLATE
  #endif
  #ifndef Z4_INTERPOLATE
    #define Z4_INTERPOLATE INTERPOLATE
  #endif
  #ifndef E0_INTERPOLATE
    #define E0_INTERPOLATE INTERPOLATE
  #endif
  #ifndef E1_INTERPOLATE
    #define E1_INTERPOLATE INTERPOLATE
  #endif
  #ifndef E2_INTERPOLATE
    #define E2_INTERPOLATE INTERPOLATE
  #endif
  #ifndef E3_INTERPOLATE
    #define E3_INTERPOLATE INTERPOLATE
  #endif
  #ifndef E4_INTERPOLATE
    #define E4_INTERPOLATE INTERPOLATE
  #endif
  #ifndef E5_INTERPOLATE
    #define E5_INTERPOLATE INTERPOLATE
  #endif
  #ifndef E6_INTERPOLATE
    #define E6_INTERPOLATE INTERPOLATE
  #endif
  #ifndef E7_INTERPOLATE
    #define E7_INTERPOLATE INTERPOLATE
  #endif
  #ifndef X_SLAVE_ADDRESS
    #define X_SLAVE_ADDRESS  0
  #endif
  #ifndef Y_SLAVE_ADDRESS
    #define Y_SLAVE_ADDRESS  0
  #endif
  #ifndef Z_SLAVE_ADDRESS
    #define Z_SLAVE_ADDRESS  0
  #endif
  #ifndef X2_SLAVE_ADDRESS
    #define X2_SLAVE_ADDRESS 0
  #endif
  #ifndef Y2_SLAVE_ADDRESS
    #define Y2_SLAVE_ADDRESS 0
  #endif
  #ifndef Z2_SLAVE_ADDRESS
    #define Z2_SLAVE_ADDRESS 0
  #endif
  #ifndef Z3_SLAVE_ADDRESS
    #define Z3_SLAVE_ADDRESS 0
  #endif
  #ifndef Z4_SLAVE_ADDRESS
    #define Z4_SLAVE_ADDRESS 0
  #endif
  #ifndef E0_SLAVE_ADDRESS
    #define E0_SLAVE_ADDRESS 0
  #endif
  #ifndef E1_SLAVE_ADDRESS
    #define E1_SLAVE_ADDRESS 0
  #endif
  #ifndef E2_SLAVE_ADDRESS
    #define E2_SLAVE_ADDRESS 0
  #endif
  #ifndef E3_SLAVE_ADDRESS
    #define E3_SLAVE_ADDRESS 0
  #endif
  #ifndef E4_SLAVE_ADDRESS
    #define E4_SLAVE_ADDRESS 0
  #endif
  #ifndef E5_SLAVE_ADDRESS
    #define E5_SLAVE_ADDRESS 0
  #endif
  #ifndef E6_SLAVE_ADDRESS
    #define E6_SLAVE_ADDRESS 0
  #endif
  #ifndef E7_SLAVE_ADDRESS
    #define E7_SLAVE_ADDRESS 0
  #endif
#endif

#if (HAS_E_DRIVER(TMC2660) \
  || ( E0_ENABLE_PIN != X_ENABLE_PIN && E1_ENABLE_PIN != X_ENABLE_PIN   \
    && E0_ENABLE_PIN != Y_ENABLE_PIN && E1_ENABLE_PIN != Y_ENABLE_PIN ) )
  #define HAS_E_STEPPER_ENABLE 1
#endif

#if ANY_AXIS_HAS(HW_SERIAL)
  #define HAS_TMC_HW_SERIAL 1
#endif
#if ANY_AXIS_HAS(SW_SERIAL)
  #define HAS_TMC_SW_SERIAL 1
#endif

//
// Set USING_HW_SERIALn flags for used Serial Ports
//

// Flag the indexed hardware serial ports in use
#define CONF_SERIAL_IS(N) (  (defined(SERIAL_PORT)      && SERIAL_PORT == N) \
                          || (defined(SERIAL_PORT_2)    && SERIAL_PORT_2 == N) \
                          || (defined(SERIAL_PORT_3)    && SERIAL_PORT_3 == N) \
                          || (defined(MMU2_SERIAL_PORT) && MMU2_SERIAL_PORT == N) \
                          || (defined(LCD_SERIAL_PORT)  && LCD_SERIAL_PORT == N) )

// Flag the named hardware serial ports in use
#define TMC_UART_IS(A,N) (defined(A##_HARDWARE_SERIAL) && (CAT(HW_,A##_HARDWARE_SERIAL) == HW_Serial##N || CAT(HW_,A##_HARDWARE_SERIAL) == HW_MSerial##N))
#define ANY_SERIAL_IS(N) (  CONF_SERIAL_IS(N) \
                         || TMC_UART_IS(X,  N) || TMC_UART_IS(Y , N) || TMC_UART_IS(Z , N) \
                         || TMC_UART_IS(X2, N) || TMC_UART_IS(Y2, N) || TMC_UART_IS(Z2, N) || TMC_UART_IS(Z3, N) || TMC_UART_IS(Z4, N) \
                         || TMC_UART_IS(E0, N) || TMC_UART_IS(E1, N) || TMC_UART_IS(E2, N) || TMC_UART_IS(E3, N) || TMC_UART_IS(E4, N) )

#define HW_Serial    501
#define HW_Serial0   502
#define HW_Serial1   503
#define HW_Serial2   504
#define HW_Serial3   505
#define HW_Serial4   506
#define HW_Serial5   507
#define HW_Serial6   508
#define HW_MSerial0  509
#define HW_MSerial1  510
#define HW_MSerial2  511
#define HW_MSerial3  512
#define HW_MSerial4  513
#define HW_MSerial5  514
#define HW_MSerial6  515
#define HW_MSerial7  516
#define HW_MSerial8  517
#define HW_MSerial9  518
#define HW_MSerial10 519

#if CONF_SERIAL_IS(-1)
  #define USING_HW_SERIALUSB 1
#endif
#if ANY_SERIAL_IS(0)
  #define USING_HW_SERIAL0 1
#endif
#if ANY_SERIAL_IS(1)
  #define USING_HW_SERIAL1 1
#endif
#if ANY_SERIAL_IS(2)
  #define USING_HW_SERIAL2 1
#endif
#if ANY_SERIAL_IS(3)
  #define USING_HW_SERIAL3 1
#endif
#if ANY_SERIAL_IS(4)
  #define USING_HW_SERIAL4 1
#endif
#if ANY_SERIAL_IS(5)
  #define USING_HW_SERIAL5 1
#endif
#if ANY_SERIAL_IS(6)
  #define USING_HW_SERIAL6 1
#endif
#if ANY_SERIAL_IS(7)
  #define USING_HW_SERIAL7 1
#endif
#if ANY_SERIAL_IS(8)
  #define USING_HW_SERIAL8 1
#endif
#if ANY_SERIAL_IS(9)
  #define USING_HW_SERIAL9 1
#endif
#if ANY_SERIAL_IS(10)
  #define USING_HW_SERIAL10 1
#endif

#undef HW_Serial
#undef HW_Serial0
#undef HW_Serial1
#undef HW_Serial2
#undef HW_Serial3
#undef HW_Serial4
#undef HW_Serial5
#undef HW_Serial6
#undef HW_MSerial0
#undef HW_MSerial1
#undef HW_MSerial2
#undef HW_MSerial3
#undef HW_MSerial4
#undef HW_MSerial5
#undef HW_MSerial6
#undef HW_MSerial7
#undef HW_MSerial8
#undef HW_MSerial9
#undef HW_MSerial10

#undef _SERIAL_ID
#undef _TMC_UART_IS
#undef TMC_UART_IS
#undef ANY_SERIAL_IS

//
// Endstops and bed probe
//

// Is an endstop plug used for extra Z endstops or the probe?
#define IS_PROBE_PIN(A,M) (HAS_CUSTOM_PROBE_PIN && Z_MIN_PROBE_PIN == A##_##M##_PIN)
#define IS_X2_ENDSTOP(A,M) (ENABLED(X_DUAL_ENDSTOPS) && X2_USE_ENDSTOP == _##A##M##_)
#define IS_Y2_ENDSTOP(A,M) (ENABLED(Y_DUAL_ENDSTOPS) && Y2_USE_ENDSTOP == _##A##M##_)
#define IS_Z2_ENDSTOP(A,M) (ENABLED(Z_MULTI_ENDSTOPS) && Z2_USE_ENDSTOP == _##A##M##_)
#define IS_Z3_ENDSTOP(A,M) (ENABLED(Z_MULTI_ENDSTOPS) && NUM_Z_STEPPER_DRIVERS >= 3 && Z3_USE_ENDSTOP == _##A##M##_)
#define IS_Z4_ENDSTOP(A,M) (ENABLED(Z_MULTI_ENDSTOPS) && NUM_Z_STEPPER_DRIVERS >= 4 && Z4_USE_ENDSTOP == _##A##M##_)

#define _HAS_STOP(A,M) (PIN_EXISTS(A##_##M) && !IS_PROBE_PIN(A,M) && !IS_X2_ENDSTOP(A,M) && !IS_Y2_ENDSTOP(A,M) && !IS_Z2_ENDSTOP(A,M) && !IS_Z3_ENDSTOP(A,M) && !IS_Z4_ENDSTOP(A,M))
#if _HAS_STOP(X,MIN)
  #define HAS_X_MIN 1
#endif
#if _HAS_STOP(X,MAX)
  #define HAS_X_MAX 1
#endif
#if _HAS_STOP(Y,MIN)
  #define HAS_Y_MIN 1
#endif
#if _HAS_STOP(Y,MAX)
  #define HAS_Y_MAX 1
#endif
#if _HAS_STOP(Z,MIN)
  #define HAS_Z_MIN 1
#endif
#if _HAS_STOP(Z,MAX)
  #define HAS_Z_MAX 1
#endif
#if PIN_EXISTS(X2_MIN)
  #define HAS_X2_MIN 1
#endif
#if PIN_EXISTS(X2_MAX)
  #define HAS_X2_MAX 1
#endif
#if PIN_EXISTS(Y2_MIN)
  #define HAS_Y2_MIN 1
#endif
#if PIN_EXISTS(Y2_MAX)
  #define HAS_Y2_MAX 1
#endif
#if PIN_EXISTS(Z2_MIN)
  #define HAS_Z2_MIN 1
#endif
#if PIN_EXISTS(Z2_MAX)
  #define HAS_Z2_MAX 1
#endif
#if PIN_EXISTS(Z3_MIN)
  #define HAS_Z3_MIN 1
#endif
#if PIN_EXISTS(Z3_MAX)
  #define HAS_Z3_MAX 1
#endif
#if PIN_EXISTS(Z4_MIN)
  #define HAS_Z4_MIN 1
#endif
#if PIN_EXISTS(Z4_MAX)
  #define HAS_Z4_MAX 1
#endif
#if BOTH(HAS_BED_PROBE, HAS_CUSTOM_PROBE_PIN) && PIN_EXISTS(Z_MIN_PROBE)
  #define HAS_Z_MIN_PROBE_PIN 1
#endif

#undef IS_PROBE_PIN
#undef IS_X2_ENDSTOP
#undef IS_Y2_ENDSTOP
#undef IS_Z2_ENDSTOP
#undef IS_Z3_ENDSTOP
#undef IS_Z4_ENDSTOP

//
// ADC Temp Sensors (Thermistor or Thermocouple with amplifier ADC interface)
//
#define HAS_ADC_TEST(P) (PIN_EXISTS(TEMP_##P) && TEMP_SENSOR_##P != 0 && NONE(TEMP_SENSOR_##P##_IS_MAX_TC, TEMP_SENSOR_##P##_IS_DUMMY))
#if HAS_ADC_TEST(0)
  #define HAS_TEMP_ADC_0 1
#endif
#if HAS_ADC_TEST(1)
  #define HAS_TEMP_ADC_1 1
#endif
#if HAS_ADC_TEST(2)
  #define HAS_TEMP_ADC_2 1
#endif
#if HAS_ADC_TEST(3)
  #define HAS_TEMP_ADC_3 1
#endif
#if HAS_ADC_TEST(4)
  #define HAS_TEMP_ADC_4 1
#endif
#if HAS_ADC_TEST(5)
  #define HAS_TEMP_ADC_5 1
#endif
#if HAS_ADC_TEST(6)
  #define HAS_TEMP_ADC_6 1
#endif
#if HAS_ADC_TEST(7)
  #define HAS_TEMP_ADC_7 1
#endif
#if HAS_ADC_TEST(BED)
  #define HAS_TEMP_ADC_BED 1
#endif
#if HAS_ADC_TEST(PROBE)
  #define HAS_TEMP_ADC_PROBE 1
#endif
#if HAS_ADC_TEST(CHAMBER)
  #define HAS_TEMP_ADC_CHAMBER 1
#endif
#if HAS_ADC_TEST(COOLER)
  #define HAS_TEMP_ADC_COOLER 1
#endif

#define HAS_TEMP(N) ANY(HAS_TEMP_ADC_##N, TEMP_SENSOR_##N##_IS_MAX_TC, TEMP_SENSOR_##N##_IS_DUMMY)
#if HAS_HOTEND && HAS_TEMP(0)
  #define HAS_TEMP_HOTEND 1
#endif
#if HAS_TEMP(BED)
  #define HAS_TEMP_BED 1
#endif
#if HAS_TEMP(PROBE)
  #define HAS_TEMP_PROBE 1
#endif
#if HAS_TEMP(CHAMBER)
  #define HAS_TEMP_CHAMBER 1
#endif
#if HAS_TEMP(COOLER)
  #define HAS_TEMP_COOLER 1
#endif

#if ENABLED(JOYSTICK)
  #if PIN_EXISTS(JOY_X)
    #define HAS_JOY_ADC_X 1
  #endif
  #if PIN_EXISTS(JOY_Y)
    #define HAS_JOY_ADC_Y 1
  #endif
  #if PIN_EXISTS(JOY_Z)
    #define HAS_JOY_ADC_Z 1
  #endif
  #if PIN_EXISTS(JOY_EN)
    #define HAS_JOY_ADC_EN 1
  #endif
#endif

// Heaters
#if PIN_EXISTS(HEATER_0)
  #define HAS_HEATER_0 1
#endif
#if PIN_EXISTS(HEATER_1)
  #define HAS_HEATER_1 1
#endif
#if PIN_EXISTS(HEATER_2)
  #define HAS_HEATER_2 1
#endif
#if PIN_EXISTS(HEATER_3)
  #define HAS_HEATER_3 1
#endif
#if PIN_EXISTS(HEATER_4)
  #define HAS_HEATER_4 1
#endif
#if PIN_EXISTS(HEATER_5)
  #define HAS_HEATER_5 1
#endif
#if PIN_EXISTS(HEATER_6)
  #define HAS_HEATER_6 1
#endif
#if PIN_EXISTS(HEATER_7)
  #define HAS_HEATER_7 1
#endif
#if PIN_EXISTS(HEATER_BED)
  #define HAS_HEATER_BED 1
#endif

// Shorthand for common combinations
#if HAS_TEMP_BED && HAS_HEATER_BED
  #define HAS_HEATED_BED 1
  #ifndef BED_OVERSHOOT
    #define BED_OVERSHOOT 10
  #endif
  #define BED_MAX_TARGET (BED_MAXTEMP - (BED_OVERSHOOT))
#else
  #undef PIDTEMPBED
#endif

#if HAS_TEMP_COOLER && PIN_EXISTS(COOLER)
  #define HAS_COOLER 1
  #ifndef COOLER_OVERSHOOT
    #define COOLER_OVERSHOOT 2
  #endif
  #define COOLER_MIN_TARGET (COOLER_MINTEMP + (COOLER_OVERSHOOT))
  #define COOLER_MAX_TARGET (COOLER_MAXTEMP - (COOLER_OVERSHOOT))
#endif

#if HAS_HEATED_BED || HAS_TEMP_CHAMBER
  #define BED_OR_CHAMBER 1
#endif
#if HAS_TEMP_HOTEND || BED_OR_CHAMBER || HAS_TEMP_PROBE || HAS_TEMP_COOLER
  #define HAS_TEMP_SENSOR 1
#endif

#if HAS_TEMP_CHAMBER && PIN_EXISTS(HEATER_CHAMBER)
  #define HAS_HEATED_CHAMBER 1
  #ifndef CHAMBER_OVERSHOOT
    #define CHAMBER_OVERSHOOT 10
  #endif
  #define CHAMBER_MAX_TARGET (CHAMBER_MAXTEMP - (CHAMBER_OVERSHOOT))
#else
  #undef PIDTEMPCHAMBER
#endif

// PID heating
#if ANY(PIDTEMP, PIDTEMPBED, PIDTEMPCHAMBER)
  #define HAS_PID_HEATING 1
#endif

// Thermal protection
#if BOTH(HAS_HEATED_BED, THERMAL_PROTECTION_BED)
  #define HAS_THERMALLY_PROTECTED_BED 1
#endif
#if ENABLED(THERMAL_PROTECTION_HOTENDS) && WATCH_TEMP_PERIOD > 0
  #define WATCH_HOTENDS 1
#endif
#if HAS_THERMALLY_PROTECTED_BED && WATCH_BED_TEMP_PERIOD > 0
  #define WATCH_BED 1
#endif
#if BOTH(HAS_HEATED_CHAMBER, THERMAL_PROTECTION_CHAMBER) && WATCH_CHAMBER_TEMP_PERIOD > 0
  #define WATCH_CHAMBER 1
#endif
#if BOTH(HAS_COOLER, THERMAL_PROTECTION_COOLER) && WATCH_COOLER_TEMP_PERIOD > 0
  #define WATCH_COOLER 1
#endif
#if  (ENABLED(THERMAL_PROTECTION_HOTENDS) || !EXTRUDERS) \
  && (ENABLED(THERMAL_PROTECTION_BED)     || !HAS_HEATED_BED) \
  && (ENABLED(THERMAL_PROTECTION_CHAMBER) || !HAS_HEATED_CHAMBER) \
  && (ENABLED(THERMAL_PROTECTION_COOLER) || !HAS_COOLER)
  #define THERMALLY_SAFE 1
#endif

// Auto fans
#if HAS_HOTEND && PIN_EXISTS(E0_AUTO_FAN)
  #define HAS_AUTO_FAN_0 1
#endif
#if HAS_MULTI_HOTEND && PIN_EXISTS(E1_AUTO_FAN)
  #define HAS_AUTO_FAN_1 1
#endif
#if HOTENDS > 2 && PIN_EXISTS(E2_AUTO_FAN)
  #define HAS_AUTO_FAN_2 1
#endif
#if HOTENDS > 3 && PIN_EXISTS(E3_AUTO_FAN)
  #define HAS_AUTO_FAN_3 1
#endif
#if HOTENDS > 4 && PIN_EXISTS(E4_AUTO_FAN)
  #define HAS_AUTO_FAN_4 1
#endif
#if HOTENDS > 5 && PIN_EXISTS(E5_AUTO_FAN)
  #define HAS_AUTO_FAN_5 1
#endif
#if HOTENDS > 6 && PIN_EXISTS(E6_AUTO_FAN)
  #define HAS_AUTO_FAN_6 1
#endif
#if HOTENDS > 7 && PIN_EXISTS(E7_AUTO_FAN)
  #define HAS_AUTO_FAN_7 1
#endif
#if HAS_TEMP_CHAMBER && PIN_EXISTS(CHAMBER_AUTO_FAN)
  #define HAS_AUTO_CHAMBER_FAN 1
#endif
#if HAS_TEMP_COOLER && PIN_EXISTS(COOLER_AUTO_FAN)
  #define HAS_AUTO_COOLER_FAN 1
#endif

#if ANY(HAS_AUTO_FAN_0, HAS_AUTO_FAN_1, HAS_AUTO_FAN_2, HAS_AUTO_FAN_3, HAS_AUTO_FAN_4, HAS_AUTO_FAN_5, HAS_AUTO_FAN_6, HAS_AUTO_FAN_7, HAS_AUTO_CHAMBER_FAN, HAS_AUTO_COOLER_FAN)
  #define HAS_AUTO_FAN 1
#endif
#define _FANOVERLAP(A,B) (A##_AUTO_FAN_PIN == E##B##_AUTO_FAN_PIN)
#if HAS_AUTO_FAN && (_FANOVERLAP(CHAMBER,0) || _FANOVERLAP(CHAMBER,1) || _FANOVERLAP(CHAMBER,2) || _FANOVERLAP(CHAMBER,3) || _FANOVERLAP(CHAMBER,4) || _FANOVERLAP(CHAMBER,5) || _FANOVERLAP(CHAMBER,6) || _FANOVERLAP(CHAMBER,7))
  #define AUTO_CHAMBER_IS_E 1
#endif

#if !HAS_TEMP_SENSOR
  #undef AUTO_REPORT_TEMPERATURES
#endif
#if ANY(AUTO_REPORT_TEMPERATURES, AUTO_REPORT_SD_STATUS, AUTO_REPORT_POSITION)
  #define HAS_AUTO_REPORTING 1
>>>>>>> mcu_ctrl
#endif

#if !HAS_AUTO_CHAMBER_FAN || AUTO_CHAMBER_IS_E
  #undef AUTO_POWER_CHAMBER_FAN
#endif

<<<<<<< HEAD
// Other fans
#define HAS_FAN0 (PIN_EXISTS(FAN))
#define HAS_FAN1 (PIN_EXISTS(FAN1) && CONTROLLER_FAN_PIN != FAN1_PIN && E0_AUTO_FAN_PIN != FAN1_PIN && E1_AUTO_FAN_PIN != FAN1_PIN && E2_AUTO_FAN_PIN != FAN1_PIN && E3_AUTO_FAN_PIN != FAN1_PIN && E4_AUTO_FAN_PIN != FAN1_PIN && E5_AUTO_FAN_PIN != FAN1_PIN)
#define HAS_FAN2 (PIN_EXISTS(FAN2) && CONTROLLER_FAN_PIN != FAN2_PIN && E0_AUTO_FAN_PIN != FAN2_PIN && E1_AUTO_FAN_PIN != FAN2_PIN && E2_AUTO_FAN_PIN != FAN2_PIN && E3_AUTO_FAN_PIN != FAN2_PIN && E4_AUTO_FAN_PIN != FAN2_PIN && E5_AUTO_FAN_PIN != FAN2_PIN)
#define HAS_CONTROLLER_FAN (PIN_EXISTS(CONTROLLER_FAN))

// Servos
#define HAS_SERVO_0 (PIN_EXISTS(SERVO0) && NUM_SERVOS > 0)
#define HAS_SERVO_1 (PIN_EXISTS(SERVO1) && NUM_SERVOS > 1)
#define HAS_SERVO_2 (PIN_EXISTS(SERVO2) && NUM_SERVOS > 2)
#define HAS_SERVO_3 (PIN_EXISTS(SERVO3) && NUM_SERVOS > 3)
#define HAS_SERVOS  (NUM_SERVOS > 0)

#if HAS_SERVOS && !defined(Z_PROBE_SERVO_NR)
  #define Z_PROBE_SERVO_NR -1
#endif

#define HAS_SERVO_ANGLES (EITHER(SWITCHING_EXTRUDER, SWITCHING_NOZZLE) || (HAS_Z_SERVO_PROBE && defined(Z_PROBE_SERVO_NR)))

#if !HAS_SERVO_ANGLES || ENABLED(BLTOUCH)
  #undef EDITABLE_SERVO_ANGLES
#endif

// Sensors
#define HAS_FILAMENT_WIDTH_SENSOR (PIN_EXISTS(FILWIDTH))

// User Interface
#define HAS_HOME        (PIN_EXISTS(HOME))
#define HAS_KILL        (PIN_EXISTS(KILL))
#define HAS_SUICIDE     (PIN_EXISTS(SUICIDE))
#define HAS_PHOTOGRAPH  (PIN_EXISTS(PHOTOGRAPH))
#define HAS_BUZZER      (PIN_EXISTS(BEEPER) || EITHER(LCD_USE_I2C_BUZZER, PCA9632_BUZZER))
#define USE_BEEPER      (HAS_BUZZER && DISABLED(LCD_USE_I2C_BUZZER, PCA9632_BUZZER))
#define HAS_CASE_LIGHT  (PIN_EXISTS(CASE_LIGHT) && ENABLED(CASE_LIGHT_ENABLE))

// Digital control
#define HAS_STEPPER_RESET     (PIN_EXISTS(STEPPER_RESET))
#define HAS_DIGIPOTSS         (PIN_EXISTS(DIGIPOTSS))
#define HAS_MOTOR_CURRENT_PWM ANY_PIN(MOTOR_CURRENT_PWM_X, MOTOR_CURRENT_PWM_Y, MOTOR_CURRENT_PWM_XY, MOTOR_CURRENT_PWM_Z, MOTOR_CURRENT_PWM_E)

#define HAS_MICROSTEPS (HAS_X_MICROSTEPS || HAS_X2_MICROSTEPS || HAS_Y_MICROSTEPS || HAS_Y2_MICROSTEPS || HAS_Z_MICROSTEPS || HAS_Z2_MICROSTEPS || HAS_Z3_MICROSTEPS || HAS_E0_MICROSTEPS || HAS_E1_MICROSTEPS || HAS_E2_MICROSTEPS || HAS_E3_MICROSTEPS || HAS_E4_MICROSTEPS || HAS_E5_MICROSTEPS)
=======
// Print Cooling fans (limit)
#ifdef NUM_M106_FANS
  #define MAX_FANS NUM_M106_FANS
#else
  #define MAX_FANS 8  // Max supported fans
#endif

#define _NOT_E_AUTO(N,F) (E##N##_AUTO_FAN_PIN != FAN##F##_PIN)
#define _HAS_FAN(F) (PIN_EXISTS(FAN##F) \
                     && CONTROLLER_FAN_PIN != FAN##F##_PIN \
                     && _NOT_E_AUTO(0,F) \
                     && _NOT_E_AUTO(1,F) \
                     && _NOT_E_AUTO(2,F) \
                     && _NOT_E_AUTO(3,F) \
                     && _NOT_E_AUTO(4,F) \
                     && _NOT_E_AUTO(5,F) \
                     && _NOT_E_AUTO(6,F) \
                     && _NOT_E_AUTO(7,F) \
                     && F < MAX_FANS)
#if PIN_EXISTS(FAN)
  #define HAS_FAN0 1
#endif
#if _HAS_FAN(1)
  #define HAS_FAN1 1
#endif
#if _HAS_FAN(2)
  #define HAS_FAN2 1
#endif
#if _HAS_FAN(3)
  #define HAS_FAN3 1
#endif
#if _HAS_FAN(4)
  #define HAS_FAN4 1
#endif
#if _HAS_FAN(5)
  #define HAS_FAN5 1
#endif
#if _HAS_FAN(6)
  #define HAS_FAN6 1
#endif
#if _HAS_FAN(7)
  #define HAS_FAN7 1
#endif
#undef _NOT_E_AUTO
#undef _HAS_FAN
#if PIN_EXISTS(CONTROLLER_FAN)
  #define HAS_CONTROLLER_FAN 1
#endif

#if BED_OR_CHAMBER || HAS_FAN0
  #define BED_OR_CHAMBER_OR_FAN 1
#endif

// Servos
#if PIN_EXISTS(SERVO0) && NUM_SERVOS > 0
  #define HAS_SERVO_0 1
#endif
#if PIN_EXISTS(SERVO1) && NUM_SERVOS > 1
  #define HAS_SERVO_1 1
#endif
#if PIN_EXISTS(SERVO2) && NUM_SERVOS > 2
  #define HAS_SERVO_2 1
#endif
#if PIN_EXISTS(SERVO3) && NUM_SERVOS > 3
  #define HAS_SERVO_3 1
#endif
#if NUM_SERVOS > 0
  #define HAS_SERVOS 1
#endif
#if HAS_SERVOS && defined(PAUSE_SERVO_OUTPUT) && defined(RESUME_SERVO_OUTPUT)
  #define HAS_PAUSE_SERVO_OUTPUT 1
#endif

// Sensors
#if PIN_EXISTS(FILWIDTH)
  #define HAS_FILAMENT_WIDTH_SENSOR 1
#endif

// User Interface
#if ENABLED(FREEZE_FEATURE)
  #if !PIN_EXISTS(FREEZE) && PIN_EXISTS(KILL)
    #define FREEZE_PIN KILL_PIN
  #endif
  #if PIN_EXISTS(FREEZE)
    #define HAS_FREEZE_PIN 1
  #endif
#else
  #undef FREEZE_PIN
#endif
#if PIN_EXISTS(KILL) && TERN1(FREEZE_FEATURE, KILL_PIN != FREEZE_PIN)
  #define HAS_KILL 1
#endif
#if PIN_EXISTS(HOME)
  #define HAS_HOME 1
#endif
#if PIN_EXISTS(SUICIDE)
  #define HAS_SUICIDE 1
#endif
#if PIN_EXISTS(PHOTOGRAPH)
  #define HAS_PHOTOGRAPH 1
#endif

// Digital control
#if PIN_EXISTS(STEPPER_RESET)
  #define HAS_STEPPER_RESET 1
#endif
#if PIN_EXISTS(DIGIPOTSS)
  #define HAS_MOTOR_CURRENT_SPI 1
#endif
#if ANY_PIN(MOTOR_CURRENT_PWM_X, MOTOR_CURRENT_PWM_Y, MOTOR_CURRENT_PWM_XY, MOTOR_CURRENT_PWM_Z, MOTOR_CURRENT_PWM_E)
  #define HAS_MOTOR_CURRENT_PWM 1
#endif

#if ANY(HAS_Z_MS_PINS, HAS_Z2_MS_PINS, HAS_Z3_MS_PINS, HAS_Z4_MS_PINS)
  #define HAS_SOME_Z_MS_PINS 1
#endif
#if ANY(HAS_E0_MS_PINS, HAS_E1_MS_PINS, HAS_E2_MS_PINS, HAS_E3_MS_PINS, HAS_E4_MS_PINS, HAS_E5_MS_PINS, HAS_E6_MS_PINS, HAS_E7_MS_PINS)
  #define HAS_SOME_E_MS_PINS 1
#endif
#if ANY(HAS_X_MS_PINS, HAS_X2_MS_PINS, HAS_Y_MS_PINS, HAS_Y2_MS_PINS, HAS_SOME_Z_MS_PINS, HAS_SOME_E_MS_PINS)
  #define HAS_MICROSTEPS 1
#endif
>>>>>>> mcu_ctrl

#if HAS_MICROSTEPS

  // MS1 MS2 MS3 Stepper Driver Microstepping mode table
  #ifndef MICROSTEP1
    #define MICROSTEP1 LOW,LOW,LOW
  #endif
  #if ENABLED(HEROIC_STEPPER_DRIVERS)
    #ifndef MICROSTEP128
      #define MICROSTEP128 LOW,HIGH,LOW
    #endif
  #else
    #ifndef MICROSTEP2
      #define MICROSTEP2 HIGH,LOW,LOW
    #endif
    #ifndef MICROSTEP4
      #define MICROSTEP4 LOW,HIGH,LOW
    #endif
  #endif
  #ifndef MICROSTEP8
    #define MICROSTEP8 HIGH,HIGH,LOW
  #endif
  #ifdef __SAM3X8E__
    #if MB(ALLIGATOR)
      #ifndef MICROSTEP16
        #define MICROSTEP16 LOW,LOW,LOW
      #endif
      #ifndef MICROSTEP32
        #define MICROSTEP32 HIGH,HIGH,LOW
      #endif
    #else
      #ifndef MICROSTEP16
        #define MICROSTEP16 HIGH,HIGH,LOW
      #endif
    #endif
  #else
    #ifndef MICROSTEP16
      #define MICROSTEP16 HIGH,HIGH,LOW
    #endif
  #endif

<<<<<<< HEAD
  #define HAS_MICROSTEP1 defined(MICROSTEP1)
  #define HAS_MICROSTEP2 defined(MICROSTEP2)
  #define HAS_MICROSTEP4 defined(MICROSTEP4)
  #define HAS_MICROSTEP8 defined(MICROSTEP8)
  #define HAS_MICROSTEP16 defined(MICROSTEP16)
  #define HAS_MICROSTEP32 defined(MICROSTEP32)
  #define HAS_MICROSTEP64 defined(MICROSTEP64)
  #define HAS_MICROSTEP128 defined(MICROSTEP128)

#endif // HAS_MICROSTEPS

#if !HAS_TEMP_SENSOR
  #undef AUTO_REPORT_TEMPERATURES
#endif

#define HAS_AUTO_REPORTING EITHER(AUTO_REPORT_TEMPERATURES, AUTO_REPORT_SD_STATUS)

/**
 * This setting is also used by M109 when trying to calculate
 * a ballpark safe margin to prevent wait-forever situation.
 */
#ifndef EXTRUDE_MINTEMP
  #define EXTRUDE_MINTEMP 170
#endif

=======
  #ifdef MICROSTEP1
    #define HAS_MICROSTEP1 1
  #endif
  #ifdef MICROSTEP2
    #define HAS_MICROSTEP2 1
  #endif
  #ifdef MICROSTEP4
    #define HAS_MICROSTEP4 1
  #endif
  #ifdef MICROSTEP8
    #define HAS_MICROSTEP8 1
  #endif
  #ifdef MICROSTEP16
    #define HAS_MICROSTEP16 1
  #endif
  #ifdef MICROSTEP32
    #define HAS_MICROSTEP32 1
  #endif
  #ifdef MICROSTEP64
    #define HAS_MICROSTEP64 1
  #endif
  #ifdef MICROSTEP128
    #define HAS_MICROSTEP128 1
  #endif

#endif // HAS_MICROSTEPS

>>>>>>> mcu_ctrl
/**
 * Heater signal inversion defaults
 */

#if HAS_HEATER_0 && !defined(HEATER_0_INVERTING)
  #define HEATER_0_INVERTING false
#endif
<<<<<<< HEAD

#if HAS_HEATER_1 && !defined(HEATER_1_INVERTING)
  #define HEATER_1_INVERTING false
#endif

#if HAS_HEATER_2 && !defined(HEATER_2_INVERTING)
  #define HEATER_2_INVERTING false
#endif

#if HAS_HEATER_3 && !defined(HEATER_3_INVERTING)
  #define HEATER_3_INVERTING false
#endif

#if HAS_HEATER_4 && !defined(HEATER_4_INVERTING)
  #define HEATER_4_INVERTING false
#endif

#if HAS_HEATER_5 && !defined(HEATER_5_INVERTING)
  #define HEATER_5_INVERTING false
#endif
=======
#if HAS_HEATER_1 && !defined(HEATER_1_INVERTING)
  #define HEATER_1_INVERTING false
#endif
#if HAS_HEATER_2 && !defined(HEATER_2_INVERTING)
  #define HEATER_2_INVERTING false
#endif
#if HAS_HEATER_3 && !defined(HEATER_3_INVERTING)
  #define HEATER_3_INVERTING false
#endif
#if HAS_HEATER_4 && !defined(HEATER_4_INVERTING)
  #define HEATER_4_INVERTING false
#endif
#if HAS_HEATER_5 && !defined(HEATER_5_INVERTING)
  #define HEATER_5_INVERTING false
#endif
#if HAS_HEATER_6 && !defined(HEATER_6_INVERTING)
  #define HEATER_6_INVERTING false
#endif
#if HAS_HEATER_7 && !defined(HEATER_7_INVERTING)
  #define HEATER_7_INVERTING false
#endif
>>>>>>> mcu_ctrl

/**
 * Helper Macros for heaters and extruder fan
 */

#define WRITE_HEATER_0P(v) WRITE(HEATER_0_PIN, (v) ^ HEATER_0_INVERTING)
<<<<<<< HEAD
#if HOTENDS > 1 || ENABLED(HEATERS_PARALLEL)
=======
#if EITHER(HAS_MULTI_HOTEND, HEATERS_PARALLEL)
>>>>>>> mcu_ctrl
  #define WRITE_HEATER_1(v) WRITE(HEATER_1_PIN, (v) ^ HEATER_1_INVERTING)
  #if HOTENDS > 2
    #define WRITE_HEATER_2(v) WRITE(HEATER_2_PIN, (v) ^ HEATER_2_INVERTING)
    #if HOTENDS > 3
      #define WRITE_HEATER_3(v) WRITE(HEATER_3_PIN, (v) ^ HEATER_3_INVERTING)
      #if HOTENDS > 4
        #define WRITE_HEATER_4(v) WRITE(HEATER_4_PIN, (v) ^ HEATER_4_INVERTING)
        #if HOTENDS > 5
          #define WRITE_HEATER_5(v) WRITE(HEATER_5_PIN, (v) ^ HEATER_5_INVERTING)
<<<<<<< HEAD
=======
          #if HOTENDS > 6
            #define WRITE_HEATER_6(v) WRITE(HEATER_6_PIN, (v) ^ HEATER_6_INVERTING)
            #if HOTENDS > 7
              #define WRITE_HEATER_7(v) WRITE(HEATER_7_PIN, (v) ^ HEATER_7_INVERTING)
            #endif // HOTENDS > 7
          #endif // HOTENDS > 6
>>>>>>> mcu_ctrl
        #endif // HOTENDS > 5
      #endif // HOTENDS > 4
    #endif // HOTENDS > 3
  #endif // HOTENDS > 2
<<<<<<< HEAD
#endif // HOTENDS > 1
=======
#endif // HAS_MULTI_HOTEND || HEATERS_PARALLEL
>>>>>>> mcu_ctrl
#if ENABLED(HEATERS_PARALLEL)
  #define WRITE_HEATER_0(v) { WRITE_HEATER_0P(v); WRITE_HEATER_1(v); }
#else
  #define WRITE_HEATER_0(v) WRITE_HEATER_0P(v)
#endif

#ifndef MIN_POWER
  #define MIN_POWER 0
#endif

/**
 * Heated bed requires settings
 */
#if HAS_HEATED_BED
  #ifndef MIN_BED_POWER
    #define MIN_BED_POWER 0
  #endif
  #ifndef MAX_BED_POWER
    #define MAX_BED_POWER 255
  #endif
  #ifndef HEATER_BED_INVERTING
    #define HEATER_BED_INVERTING false
  #endif
  #define WRITE_HEATER_BED(v) WRITE(HEATER_BED_PIN, (v) ^ HEATER_BED_INVERTING)
#endif

/**
 * Heated chamber requires settings
 */
#if HAS_HEATED_CHAMBER
<<<<<<< HEAD
=======
  #ifndef MIN_CHAMBER_POWER
    #define MIN_CHAMBER_POWER 0
  #endif
>>>>>>> mcu_ctrl
  #ifndef MAX_CHAMBER_POWER
    #define MAX_CHAMBER_POWER 255
  #endif
  #ifndef HEATER_CHAMBER_INVERTING
    #define HEATER_CHAMBER_INVERTING false
  #endif
  #define WRITE_HEATER_CHAMBER(v) WRITE(HEATER_CHAMBER_PIN, (v) ^ HEATER_CHAMBER_INVERTING)
#endif

/**
<<<<<<< HEAD
=======
 * Laser Cooling requires settings
 */
#if HAS_COOLER
  #ifndef MAX_COOLER_POWER
    #define MAX_COOLER_POWER 255
  #endif
  #ifndef COOLER_INVERTING
    #define COOLER_INVERTING true
  #endif
  #define WRITE_HEATER_COOLER(v) WRITE(COOLER_PIN, (v) ^ COOLER_INVERTING)
#endif

#if HAS_HOTEND || HAS_HEATED_BED || HAS_HEATED_CHAMBER || HAS_COOLER
  #define HAS_TEMPERATURE 1
#endif

#if HAS_TEMPERATURE && EITHER(HAS_LCD_MENU, DWIN_CREALITY_LCD)
  #ifdef PREHEAT_6_LABEL
    #define PREHEAT_COUNT 6
  #elif defined(PREHEAT_5_LABEL)
    #define PREHEAT_COUNT 5
  #elif defined(PREHEAT_4_LABEL)
    #define PREHEAT_COUNT 4
  #elif defined(PREHEAT_3_LABEL)
    #define PREHEAT_COUNT 3
  #elif defined(PREHEAT_2_LABEL)
    #define PREHEAT_COUNT 2
  #elif defined(PREHEAT_1_LABEL)
    #define PREHEAT_COUNT 1
  #endif
#endif

#if !PREHEAT_COUNT
  #undef PREHEAT_SHORTCUT_MENU_ITEM
#endif

/**
>>>>>>> mcu_ctrl
 * Up to 3 PWM fans
 */
#ifndef FAN_INVERTING
  #define FAN_INVERTING false
#endif

<<<<<<< HEAD
#if HAS_FAN2
=======
#if HAS_FAN7
  #define FAN_COUNT 8
#elif HAS_FAN6
  #define FAN_COUNT 7
#elif HAS_FAN5
  #define FAN_COUNT 6
#elif HAS_FAN4
  #define FAN_COUNT 5
#elif HAS_FAN3
  #define FAN_COUNT 4
#elif HAS_FAN2
>>>>>>> mcu_ctrl
  #define FAN_COUNT 3
#elif HAS_FAN1
  #define FAN_COUNT 2
#elif HAS_FAN0
  #define FAN_COUNT 1
#else
  #define FAN_COUNT 0
#endif

#if FAN_COUNT > 0
<<<<<<< HEAD
  #define WRITE_FAN(n, v) WRITE(FAN##n##_PIN, (v) ^ FAN_INVERTING)
=======
  #define HAS_FAN 1
>>>>>>> mcu_ctrl
#endif

/**
 * Part Cooling fan multipliexer
 */
<<<<<<< HEAD
#define HAS_FANMUX PIN_EXISTS(FANMUX0)
=======
#if PIN_EXISTS(FANMUX0)
  #define HAS_FANMUX 1
#endif
>>>>>>> mcu_ctrl

/**
 * MIN/MAX fan PWM scaling
 */
#ifndef FAN_OFF_PWM
  #define FAN_OFF_PWM 0
#endif
#ifndef FAN_MIN_PWM
  #if FAN_OFF_PWM > 0
    #define FAN_MIN_PWM (FAN_OFF_PWM + 1)
  #else
    #define FAN_MIN_PWM 0
  #endif
#endif
#ifndef FAN_MAX_PWM
  #define FAN_MAX_PWM 255
#endif
#if FAN_MIN_PWM < 0 || FAN_MIN_PWM > 255
  #error "FAN_MIN_PWM must be a value from 0 to 255."
#elif FAN_MAX_PWM < 0 || FAN_MAX_PWM > 255
  #error "FAN_MAX_PWM must be a value from 0 to 255."
#elif FAN_MIN_PWM > FAN_MAX_PWM
  #error "FAN_MIN_PWM must be less than or equal to FAN_MAX_PWM."
#elif FAN_OFF_PWM > FAN_MIN_PWM
  #error "FAN_OFF_PWM must be less than or equal to FAN_MIN_PWM."
#endif

/**
 * FAST PWM FAN Settings
 */
#if ENABLED(FAST_PWM_FAN) && !defined(FAST_PWM_FAN_FREQUENCY)
  #define FAST_PWM_FAN_FREQUENCY ((F_CPU) / (2 * 255 * 1)) // Fan frequency default
#endif

/**
 * MIN/MAX case light PWM scaling
 */
<<<<<<< HEAD
#if HAS_CASE_LIGHT
=======
#if ENABLED(CASE_LIGHT_ENABLE)
>>>>>>> mcu_ctrl
  #ifndef CASE_LIGHT_MAX_PWM
    #define CASE_LIGHT_MAX_PWM 255
  #elif !WITHIN(CASE_LIGHT_MAX_PWM, 1, 255)
    #error "CASE_LIGHT_MAX_PWM must be a value from 1 to 255."
  #endif
#endif

/**
 * Bed Probe dependencies
 */
#if HAS_BED_PROBE
<<<<<<< HEAD
  #if ENABLED(ENDSTOPPULLUPS) && HAS_Z_MIN_PROBE_PIN
=======
  #if BOTH(ENDSTOPPULLUPS, HAS_Z_MIN_PROBE_PIN)
>>>>>>> mcu_ctrl
    #define ENDSTOPPULLUP_ZMIN_PROBE
  #endif
  #ifndef Z_PROBE_OFFSET_RANGE_MIN
    #define Z_PROBE_OFFSET_RANGE_MIN -20
  #endif
  #ifndef Z_PROBE_OFFSET_RANGE_MAX
    #define Z_PROBE_OFFSET_RANGE_MAX 20
  #endif
<<<<<<< HEAD
  #ifndef XY_PROBE_SPEED
    #ifdef HOMING_FEEDRATE_XY
      #define XY_PROBE_SPEED HOMING_FEEDRATE_XY
    #else
      #define XY_PROBE_SPEED 4000
    #endif
=======
  #ifndef XY_PROBE_FEEDRATE
    #define XY_PROBE_FEEDRATE ((homing_feedrate_mm_m.x + homing_feedrate_mm_m.y) / 2)
>>>>>>> mcu_ctrl
  #endif
  #ifndef NOZZLE_TO_PROBE_OFFSET
    #define NOZZLE_TO_PROBE_OFFSET { 0, 0, 0 }
  #endif
#else
  #undef NOZZLE_TO_PROBE_OFFSET
#endif

/**
 * XYZ Bed Skew Correction
 */
#if ENABLED(SKEW_CORRECTION)
  #define SKEW_FACTOR_MIN -1
  #define SKEW_FACTOR_MAX 1

  #define _GET_SIDE(a,b,c) (SQRT(2*sq(a)+2*sq(b)-4*sq(c))*0.5)
  #define _SKEW_SIDE(a,b,c) tan(M_PI*0.5-acos((sq(a)-sq(b)-sq(c))/(2*c*b)))
  #define _SKEW_FACTOR(a,b,c) _SKEW_SIDE(float(a),_GET_SIDE(float(a),float(b),float(c)),float(c))

  #ifndef XY_SKEW_FACTOR
    #if defined(XY_DIAG_AC) && defined(XY_DIAG_BD) && defined(XY_SIDE_AD)
      #define XY_SKEW_FACTOR _SKEW_FACTOR(XY_DIAG_AC, XY_DIAG_BD, XY_SIDE_AD)
    #else
      #define XY_SKEW_FACTOR 0.0
    #endif
  #endif
  #ifndef XZ_SKEW_FACTOR
    #if defined(XY_SIDE_AD) && !defined(XZ_SIDE_AD)
      #define XZ_SIDE_AD XY_SIDE_AD
    #endif
    #if defined(XZ_DIAG_AC) && defined(XZ_DIAG_BD) && defined(XZ_SIDE_AD)
      #define XZ_SKEW_FACTOR _SKEW_FACTOR(XZ_DIAG_AC, XZ_DIAG_BD, XZ_SIDE_AD)
    #else
      #define XZ_SKEW_FACTOR 0.0
    #endif
  #endif
  #ifndef YZ_SKEW_FACTOR
    #if defined(YZ_DIAG_AC) && defined(YZ_DIAG_BD) && defined(YZ_SIDE_AD)
      #define YZ_SKEW_FACTOR _SKEW_FACTOR(YZ_DIAG_AC, YZ_DIAG_BD, YZ_SIDE_AD)
    #else
      #define YZ_SKEW_FACTOR 0.0
    #endif
  #endif
#endif // SKEW_CORRECTION

/**
<<<<<<< HEAD
 * Set granular options based on the specific type of leveling
 */
#define UBL_SEGMENTED   BOTH(AUTO_BED_LEVELING_UBL, DELTA)
#define ABL_PLANAR      EITHER(AUTO_BED_LEVELING_LINEAR, AUTO_BED_LEVELING_3POINT)
#define ABL_GRID        EITHER(AUTO_BED_LEVELING_LINEAR, AUTO_BED_LEVELING_BILINEAR)
#define HAS_ABL_NOT_UBL (ABL_PLANAR || ABL_GRID)
#define HAS_ABL_OR_UBL  (HAS_ABL_NOT_UBL || ENABLED(AUTO_BED_LEVELING_UBL))
#define HAS_LEVELING    (HAS_ABL_OR_UBL || ENABLED(MESH_BED_LEVELING))
#define HAS_AUTOLEVEL   (HAS_ABL_OR_UBL && DISABLED(PROBE_MANUALLY))
#define HAS_MESH        ANY(AUTO_BED_LEVELING_BILINEAR, AUTO_BED_LEVELING_UBL, MESH_BED_LEVELING)
#define PLANNER_LEVELING      (HAS_LEVELING && DISABLED(AUTO_BED_LEVELING_UBL))
#define HAS_PROBING_PROCEDURE (HAS_ABL_OR_UBL || ENABLED(Z_MIN_PROBE_REPEATABILITY_TEST))
#define HAS_POSITION_MODIFIERS (ENABLED(FWRETRACT) || HAS_LEVELING || ENABLED(SKEW_CORRECTION))
#define NEEDS_THREE_PROBE_POINTS EITHER(AUTO_BED_LEVELING_UBL, AUTO_BED_LEVELING_3POINT)

#if ENABLED(AUTO_BED_LEVELING_UBL)
  #undef LCD_BED_LEVELING
#endif

/**
=======
>>>>>>> mcu_ctrl
 * Heater, Fan, and Probe interactions
 */
#if FAN_COUNT == 0
  #undef PROBING_FANS_OFF
  #undef ADAPTIVE_FAN_SLOWING
  #undef NO_FAN_SLOWING_IN_PID_TUNING
#endif

<<<<<<< HEAD
#define QUIET_PROBING (HAS_BED_PROBE && (EITHER(PROBING_HEATERS_OFF, PROBING_FANS_OFF) || DELAY_BEFORE_PROBING > 0))
#define HEATER_IDLE_HANDLER EITHER(ADVANCED_PAUSE_FEATURE, PROBING_HEATERS_OFF)

#if ENABLED(ADVANCED_PAUSE_FEATURE) && !defined(FILAMENT_CHANGE_SLOW_LOAD_LENGTH)
  #define FILAMENT_CHANGE_SLOW_LOAD_LENGTH 0
#endif

#if EXTRUDERS > 1 && !defined(TOOLCHANGE_FIL_EXTRA_PRIME)
  #define TOOLCHANGE_FIL_EXTRA_PRIME 0
=======
#if HAS_BED_PROBE && (EITHER(PROBING_HEATERS_OFF, PROBING_FANS_OFF) || DELAY_BEFORE_PROBING > 0)
  #define HAS_QUIET_PROBING 1
#endif
#if EITHER(ADVANCED_PAUSE_FEATURE, PROBING_HEATERS_OFF)
  #define HEATER_IDLE_HANDLER 1
#endif

/**
 * Advanced Pause - Filament Change
 */
#if ENABLED(ADVANCED_PAUSE_FEATURE)
  #if HAS_LCD_MENU || BOTH(EMERGENCY_PARSER, HOST_PROMPT_SUPPORT)
    #define M600_PURGE_MORE_RESUMABLE 1
  #endif
  #ifndef FILAMENT_CHANGE_SLOW_LOAD_LENGTH
    #define FILAMENT_CHANGE_SLOW_LOAD_LENGTH 0
  #endif
#endif

#if HAS_MULTI_EXTRUDER && !defined(TOOLCHANGE_FS_EXTRA_PRIME)
  #define TOOLCHANGE_FS_EXTRA_PRIME 0
>>>>>>> mcu_ctrl
#endif

/**
 * Only constrain Z on DELTA / SCARA machines
 */
#if IS_KINEMATIC
  #undef MIN_SOFTWARE_ENDSTOP_X
  #undef MIN_SOFTWARE_ENDSTOP_Y
  #undef MAX_SOFTWARE_ENDSTOP_X
  #undef MAX_SOFTWARE_ENDSTOP_Y
#endif

/**
 * Bed Probing bounds
 */

<<<<<<< HEAD
#ifndef MIN_PROBE_EDGE
  #define MIN_PROBE_EDGE 0
#endif

#if IS_KINEMATIC
  #undef MIN_PROBE_EDGE_LEFT
  #undef MIN_PROBE_EDGE_RIGHT
  #undef MIN_PROBE_EDGE_FRONT
  #undef MIN_PROBE_EDGE_BACK
#else
  #ifndef MIN_PROBE_EDGE_LEFT
    #define MIN_PROBE_EDGE_LEFT MIN_PROBE_EDGE
  #endif
  #ifndef MIN_PROBE_EDGE_RIGHT
    #define MIN_PROBE_EDGE_RIGHT MIN_PROBE_EDGE
  #endif
  #ifndef MIN_PROBE_EDGE_FRONT
    #define MIN_PROBE_EDGE_FRONT MIN_PROBE_EDGE
  #endif
  #ifndef MIN_PROBE_EDGE_BACK
    #define MIN_PROBE_EDGE_BACK MIN_PROBE_EDGE
=======
#ifndef PROBING_MARGIN
  #define PROBING_MARGIN 0
#endif

#if IS_KINEMATIC
  #undef PROBING_MARGIN_LEFT
  #undef PROBING_MARGIN_RIGHT
  #undef PROBING_MARGIN_FRONT
  #undef PROBING_MARGIN_BACK
  #define PROBING_MARGIN_LEFT 0
  #define PROBING_MARGIN_RIGHT 0
  #define PROBING_MARGIN_FRONT 0
  #define PROBING_MARGIN_BACK 0
#else
  #ifndef PROBING_MARGIN_LEFT
    #define PROBING_MARGIN_LEFT PROBING_MARGIN
  #endif
  #ifndef PROBING_MARGIN_RIGHT
    #define PROBING_MARGIN_RIGHT PROBING_MARGIN
  #endif
  #ifndef PROBING_MARGIN_FRONT
    #define PROBING_MARGIN_FRONT PROBING_MARGIN
  #endif
  #ifndef PROBING_MARGIN_BACK
    #define PROBING_MARGIN_BACK PROBING_MARGIN
>>>>>>> mcu_ctrl
  #endif
#endif

#if ENABLED(DELTA)
  /**
   * Delta radius/rod trimmers/angle trimmers
   */
  #ifndef DELTA_ENDSTOP_ADJ
    #define DELTA_ENDSTOP_ADJ { 0, 0, 0 }
  #endif
  #ifndef DELTA_TOWER_ANGLE_TRIM
    #define DELTA_TOWER_ANGLE_TRIM { 0, 0, 0 }
  #endif
  #ifndef DELTA_RADIUS_TRIM_TOWER
    #define DELTA_RADIUS_TRIM_TOWER { 0, 0, 0 }
  #endif
  #ifndef DELTA_DIAGONAL_ROD_TRIM_TOWER
    #define DELTA_DIAGONAL_ROD_TRIM_TOWER { 0, 0, 0 }
  #endif
#endif

<<<<<<< HEAD
=======
#ifndef DEFAULT_LEVELING_FADE_HEIGHT
  #define DEFAULT_LEVELING_FADE_HEIGHT 0.0
#endif

>>>>>>> mcu_ctrl
#if ENABLED(SEGMENT_LEVELED_MOVES) && !defined(LEVELED_SEGMENT_LENGTH)
  #define LEVELED_SEGMENT_LENGTH 5
#endif

/**
 * Default mesh area is an area with an inset margin on the print area.
 */
#if EITHER(MESH_BED_LEVELING, AUTO_BED_LEVELING_UBL)
  #if IS_KINEMATIC
    // Probing points may be verified at compile time within the radius
    // using static_assert(HYPOT2(X2-X1,Y2-Y1)<=sq(DELTA_PRINTABLE_RADIUS),"bad probe point!")
    // so that may be added to SanityCheck.h in the future.
    #define _MESH_MIN_X (X_MIN_BED + MESH_INSET)
    #define _MESH_MIN_Y (Y_MIN_BED + MESH_INSET)
    #define _MESH_MAX_X (X_MAX_BED - (MESH_INSET))
    #define _MESH_MAX_Y (Y_MAX_BED - (MESH_INSET))
  #else
    // Boundaries for Cartesian probing based on set limits
    #define _MESH_MIN_X (_MAX(X_MIN_BED + MESH_INSET, X_MIN_POS))  // UBL is careful not to probe off the bed.  It does not
    #define _MESH_MIN_Y (_MAX(Y_MIN_BED + MESH_INSET, Y_MIN_POS))  // need NOZZLE_TO_PROBE_OFFSET in the mesh dimensions
    #define _MESH_MAX_X (_MIN(X_MAX_BED - (MESH_INSET), X_MAX_POS))
    #define _MESH_MAX_Y (_MIN(Y_MAX_BED - (MESH_INSET), Y_MAX_POS))
  #endif

  // These may be overridden in Configuration.h if a smaller area is desired
  #ifndef MESH_MIN_X
    #define MESH_MIN_X _MESH_MIN_X
  #endif
  #ifndef MESH_MIN_Y
    #define MESH_MIN_Y _MESH_MIN_Y
  #endif
  #ifndef MESH_MAX_X
    #define MESH_MAX_X _MESH_MAX_X
  #endif
  #ifndef MESH_MAX_Y
    #define MESH_MAX_Y _MESH_MAX_Y
  #endif
#else
  #undef MESH_MIN_X
  #undef MESH_MIN_Y
  #undef MESH_MAX_X
  #undef MESH_MAX_Y
#endif

<<<<<<< HEAD
#if (defined(PROBE_PT_1_X) && defined(PROBE_PT_2_X) && defined(PROBE_PT_3_X) && defined(PROBE_PT_1_Y) && defined(PROBE_PT_2_Y) && defined(PROBE_PT_3_Y))
  #define HAS_FIXED_3POINT
#endif

=======
#define _POINT_COUNT (defined(PROBE_PT_1_X) + defined(PROBE_PT_2_X) + defined(PROBE_PT_3_X) + defined(PROBE_PT_1_Y) + defined(PROBE_PT_2_Y) + defined(PROBE_PT_3_Y))
#if _POINT_COUNT == 6
  #define HAS_FIXED_3POINT 1
#elif _POINT_COUNT > 0
  #error "For 3-Point Leveling all XY points must be defined (or none for the defaults)."
#endif
#undef _POINT_COUNT
>>>>>>> mcu_ctrl

/**
 * Buzzer/Speaker
 */
<<<<<<< HEAD
=======
#if PIN_EXISTS(BEEPER)
  #define USE_BEEPER 1
#endif
#if USE_BEEPER || ANY(LCD_USE_I2C_BUZZER, PCA9632_BUZZER)
  #define HAS_BUZZER 1
#endif

>>>>>>> mcu_ctrl
#if ENABLED(LCD_USE_I2C_BUZZER)
  #ifndef LCD_FEEDBACK_FREQUENCY_HZ
    #define LCD_FEEDBACK_FREQUENCY_HZ 1000
  #endif
  #ifndef LCD_FEEDBACK_FREQUENCY_DURATION_MS
    #define LCD_FEEDBACK_FREQUENCY_DURATION_MS 100
  #endif
#elif HAS_BUZZER
  #ifndef LCD_FEEDBACK_FREQUENCY_HZ
    #define LCD_FEEDBACK_FREQUENCY_HZ 5000
  #endif
  #ifndef LCD_FEEDBACK_FREQUENCY_DURATION_MS
    #define LCD_FEEDBACK_FREQUENCY_DURATION_MS 2
  #endif
#endif

<<<<<<< HEAD
/**
 * Make sure DOGLCD_SCK and DOGLCD_MOSI are defined.
 */
#if HAS_GRAPHICAL_LCD
  #ifndef DOGLCD_SCK
    #define DOGLCD_SCK  SCK_PIN
  #endif
  #ifndef DOGLCD_MOSI
    #define DOGLCD_MOSI MOSI_PIN
=======
#if HAS_BUZZER
  #if LCD_FEEDBACK_FREQUENCY_DURATION_MS && LCD_FEEDBACK_FREQUENCY_HZ
    #define HAS_CHIRP 1
  #endif
#else
  #undef SOUND_MENU_ITEM   // No buzzer menu item without a buzzer
#endif

/**
 * Make sure DOGLCD_SCK and DOGLCD_MOSI are defined.
 */
#if HAS_MARLINUI_U8GLIB
  #ifndef DOGLCD_SCK
    #define DOGLCD_SCK  SD_SCK_PIN
  #endif
  #ifndef DOGLCD_MOSI
    #define DOGLCD_MOSI SD_MOSI_PIN
>>>>>>> mcu_ctrl
  #endif
#endif

/**
 * Z_HOMING_HEIGHT / Z_CLEARANCE_BETWEEN_PROBES
 */
#ifndef Z_HOMING_HEIGHT
<<<<<<< HEAD
  #ifndef Z_CLEARANCE_BETWEEN_PROBES
    #define Z_HOMING_HEIGHT 0
  #else
    #define Z_HOMING_HEIGHT Z_CLEARANCE_BETWEEN_PROBES
=======
  #ifdef Z_CLEARANCE_BETWEEN_PROBES
    #define Z_HOMING_HEIGHT Z_CLEARANCE_BETWEEN_PROBES
  #else
    #define Z_HOMING_HEIGHT 0
>>>>>>> mcu_ctrl
  #endif
#endif

#if PROBE_SELECTED
  #ifndef Z_CLEARANCE_BETWEEN_PROBES
    #define Z_CLEARANCE_BETWEEN_PROBES Z_HOMING_HEIGHT
  #endif
  #if Z_CLEARANCE_BETWEEN_PROBES > Z_HOMING_HEIGHT
<<<<<<< HEAD
    #define MANUAL_PROBE_HEIGHT Z_CLEARANCE_BETWEEN_PROBES
  #else
    #define MANUAL_PROBE_HEIGHT Z_HOMING_HEIGHT
=======
    #define Z_CLEARANCE_BETWEEN_MANUAL_PROBES Z_CLEARANCE_BETWEEN_PROBES
  #else
    #define Z_CLEARANCE_BETWEEN_MANUAL_PROBES Z_HOMING_HEIGHT
>>>>>>> mcu_ctrl
  #endif
  #ifndef Z_CLEARANCE_MULTI_PROBE
    #define Z_CLEARANCE_MULTI_PROBE Z_CLEARANCE_BETWEEN_PROBES
  #endif
  #if ENABLED(BLTOUCH) && !defined(BLTOUCH_DELAY)
    #define BLTOUCH_DELAY 500
  #endif
#endif

<<<<<<< HEAD
=======
// Define a starting height for measuring manual probe points
#ifndef MANUAL_PROBE_START_Z
  #if EITHER(MESH_BED_LEVELING, PROBE_MANUALLY)
    // Leave MANUAL_PROBE_START_Z undefined so the prior Z height will be used.
    // Note: If Z_CLEARANCE_BETWEEN_MANUAL_PROBES is 0 there will be no raise between points
  #elif ENABLED(AUTO_BED_LEVELING_UBL) && defined(Z_CLEARANCE_BETWEEN_PROBES)
    #define MANUAL_PROBE_START_Z Z_CLEARANCE_BETWEEN_PROBES
  #endif
#endif

>>>>>>> mcu_ctrl
#ifndef __SAM3X8E__ //todo: hal: broken hal encapsulation
  #undef UI_VOLTAGE_LEVEL
  #undef RADDS_DISPLAY
  #undef MOTOR_CURRENT
#endif

// Updated G92 behavior shifts the workspace
<<<<<<< HEAD
#define HAS_POSITION_SHIFT DISABLED(NO_WORKSPACE_OFFSETS)
// The home offset also shifts the coordinate space
#define HAS_HOME_OFFSET (DISABLED(NO_WORKSPACE_OFFSETS) && IS_CARTESIAN)
// The SCARA home offset applies only on G28
#define HAS_SCARA_OFFSET (DISABLED(NO_WORKSPACE_OFFSETS) && IS_SCARA)
// Cumulative offset to workspace to save some calculation
#define HAS_WORKSPACE_OFFSET (HAS_POSITION_SHIFT && HAS_HOME_OFFSET)
// M206 sets the home offset for Cartesian machines
#define HAS_M206_COMMAND (HAS_HOME_OFFSET && !IS_SCARA)
=======
#if DISABLED(NO_WORKSPACE_OFFSETS)
  #define HAS_POSITION_SHIFT 1
  #if IS_CARTESIAN
    #define HAS_HOME_OFFSET 1       // The home offset also shifts the coordinate space
    #define HAS_WORKSPACE_OFFSET 1  // Cumulative offset to workspace to save some calculation
    #define HAS_M206_COMMAND 1      // M206 sets the home offset for Cartesian machines
  #elif IS_SCARA
    #define HAS_SCARA_OFFSET 1      // The SCARA home offset applies only on G28
  #endif
#endif
>>>>>>> mcu_ctrl

// LCD timeout to status screen default is 15s
#ifndef LCD_TIMEOUT_TO_STATUS
  #define LCD_TIMEOUT_TO_STATUS 15000
#endif

// Add commands that need sub-codes to this list
<<<<<<< HEAD
#define USE_GCODE_SUBCODES ANY(G38_PROBE_TARGET, CNC_COORDINATE_SYSTEMS, POWER_LOSS_RECOVERY)
=======
#if ANY(G38_PROBE_TARGET, CNC_COORDINATE_SYSTEMS, POWER_LOSS_RECOVERY)
  #define USE_GCODE_SUBCODES 1
#endif
>>>>>>> mcu_ctrl

// Parking Extruder
#if ENABLED(PARKING_EXTRUDER)
  #ifndef PARKING_EXTRUDER_GRAB_DISTANCE
    #define PARKING_EXTRUDER_GRAB_DISTANCE 0
  #endif
  #ifndef PARKING_EXTRUDER_SOLENOIDS_PINS_ACTIVE
    #define PARKING_EXTRUDER_SOLENOIDS_PINS_ACTIVE HIGH
  #endif
#endif

// Number of VFAT entries used. Each entry has 13 UTF-16 characters
<<<<<<< HEAD
#if ENABLED(SCROLL_LONG_FILENAMES)
  #define MAX_VFAT_ENTRIES (5)
#else
  #define MAX_VFAT_ENTRIES (5)
#endif

// Set defaults for unspecified LED user colors
#if ENABLED(LED_CONTROL_MENU)
  #ifndef LED_USER_PRESET_RED
    #define LED_USER_PRESET_RED       255
  #endif
  #ifndef LED_USER_PRESET_GREEN
    #define LED_USER_PRESET_GREEN     255
  #endif
  #ifndef LED_USER_PRESET_BLUE
    #define LED_USER_PRESET_BLUE      255
  #endif
  #ifndef LED_USER_PRESET_WHITE
    #define LED_USER_PRESET_WHITE     0
  #endif
  #ifndef LED_USER_PRESET_BRIGHTNESS
    #ifdef NEOPIXEL_BRIGHTNESS
      #define LED_USER_PRESET_BRIGHTNESS NEOPIXEL_BRIGHTNESS
    #else
      #define LED_USER_PRESET_BRIGHTNESS 255
    #endif
  #endif
=======
#if EITHER(SCROLL_LONG_FILENAMES, DWIN_CREALITY_LCD)
  #define MAX_VFAT_ENTRIES (5)
#else
  #define MAX_VFAT_ENTRIES (2)
>>>>>>> mcu_ctrl
#endif

// Nozzle park for Delta
#if BOTH(NOZZLE_PARK_FEATURE, DELTA)
  #undef NOZZLE_PARK_Z_FEEDRATE
  #define NOZZLE_PARK_Z_FEEDRATE NOZZLE_PARK_XY_FEEDRATE
#endif

// Force SDCARD_SORT_ALPHA to be enabled for Graphical LCD on LPC1768
// on boards where SD card and LCD display share the same SPI bus
// because of a bug in the shared SPI implementation. (See #8122)
<<<<<<< HEAD
#if defined(TARGET_LPC1768) && ENABLED(REPRAP_DISCOUNT_FULL_GRAPHIC_SMART_CONTROLLER) && (SCK_PIN == LCD_PINS_D4)
  #define SDCARD_SORT_ALPHA         // Keeps one directory level in RAM. Changing
                                    // directory levels still glitches the screen,
                                    // but the following LCD update cleans it up.
=======
#if defined(TARGET_LPC1768) && IS_RRD_FG_SC && (SD_SCK_PIN == LCD_PINS_D4)
  #define SDCARD_SORT_ALPHA         // Keep one directory level in RAM. Changing directory levels
                                    // may still glitch the screen, but LCD updates clean it up.
>>>>>>> mcu_ctrl
  #undef SDSORT_LIMIT
  #undef SDSORT_USES_RAM
  #undef SDSORT_USES_STACK
  #undef SDSORT_CACHE_NAMES
  #define SDSORT_LIMIT       64
  #define SDSORT_USES_RAM    true
  #define SDSORT_USES_STACK  false
  #define SDSORT_CACHE_NAMES true
  #ifndef FOLDER_SORTING
    #define FOLDER_SORTING     -1
  #endif
  #ifndef SDSORT_GCODE
    #define SDSORT_GCODE       false
  #endif
  #ifndef SDSORT_DYNAMIC_RAM
    #define SDSORT_DYNAMIC_RAM false
  #endif
  #ifndef SDSORT_CACHE_VFATS
    #define SDSORT_CACHE_VFATS 2
  #endif
#endif

<<<<<<< HEAD
// Defined here to catch the above defines
#if ENABLED(SDCARD_SORT_ALPHA)
  #define HAS_FOLDER_SORTING (FOLDER_SORTING || ENABLED(SDSORT_GCODE))
#endif

// If platform requires early initialization of watchdog to properly boot
#define EARLY_WATCHDOG (ENABLED(USE_WATCHDOG) && defined(ARDUINO_ARCH_SAM))

#if ENABLED(Z_TRIPLE_STEPPER_DRIVERS)
  #define Z_STEPPER_COUNT 3
#elif ENABLED(Z_DUAL_STEPPER_DRIVERS)
  #define Z_STEPPER_COUNT 2
#else
  #define Z_STEPPER_COUNT 1
#endif

#if HAS_SPI_LCD
  // Get LCD character width/height, which may be overridden by pins, configs, etc.
  #ifndef LCD_WIDTH
    #if HAS_GRAPHICAL_LCD
      #define LCD_WIDTH 21
    #elif ENABLED(ULTIPANEL)
      #define LCD_WIDTH 20
    #else
      #define LCD_WIDTH 16
    #endif
  #endif
  #ifndef LCD_HEIGHT
    #if HAS_GRAPHICAL_LCD
      #define LCD_HEIGHT 5
    #elif ENABLED(ULTIPANEL)
      #define LCD_HEIGHT 4
    #else
      #define LCD_HEIGHT 2
=======
// Fallback SPI Speed for SD
#if ENABLED(SDSUPPORT) && !defined(SD_SPI_SPEED)
  #define SD_SPI_SPEED SPI_FULL_SPEED
#endif

// Defined here to catch the above defines
#if ENABLED(SDCARD_SORT_ALPHA) && (FOLDER_SORTING || ENABLED(SDSORT_GCODE))
  #define HAS_FOLDER_SORTING 1
#endif

#if HAS_WIRED_LCD
  // Get LCD character width/height, which may be overridden by pins, configs, etc.
  #ifndef LCD_WIDTH
    #if HAS_MARLINUI_U8GLIB
      #define LCD_WIDTH 21
    #else
      #define LCD_WIDTH TERN(IS_ULTIPANEL, 20, 16)
    #endif
  #endif
  #ifndef LCD_HEIGHT
    #if HAS_MARLINUI_U8GLIB
      #define LCD_HEIGHT 5
    #else
      #define LCD_HEIGHT TERN(IS_ULTIPANEL, 4, 2)
>>>>>>> mcu_ctrl
    #endif
  #endif
#endif

<<<<<<< HEAD
#if ENABLED(SDSUPPORT)
  #if SD_CONNECTION_IS(ONBOARD) && DISABLED(NO_SD_HOST_DRIVE)
    //
    // The external SD card is not used. Hardware SPI is used to access the card.
    // When sharing the SD card with a PC we want the menu options to
    // mount/unmount the card and refresh it. So we disable card detect.
    //
    #undef SD_DETECT_PIN
    #define SHARED_SD_CARD
  #endif
  #if DISABLED(SHARED_SD_CARD)
    #define INIT_SDCARD_ON_BOOT
  #endif
#endif

#if !NUM_SERIAL
  #undef BAUD_RATE_GCODE
#endif

#if ENABLED(Z_STEPPER_ALIGN_KNOWN_STEPPER_POSITIONS)
  #undef Z_STEPPER_ALIGN_AMP
#endif
#ifndef Z_STEPPER_ALIGN_AMP
  #define Z_STEPPER_ALIGN_AMP 1.0
=======
#if BUTTONS_EXIST(EN1, EN2, ENC)
  #define HAS_ROTARY_ENCODER 1
#endif

#if PIN_EXISTS(SAFE_POWER) && DISABLED(DISABLE_DRIVER_SAFE_POWER_PROTECT)
  #define HAS_DRIVER_SAFE_POWER_PROTECT 1
>>>>>>> mcu_ctrl
#endif
