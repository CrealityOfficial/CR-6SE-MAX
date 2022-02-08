/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _VARIANT_ARDUINO_STM32_
#define _VARIANT_ARDUINO_STM32_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef ARDUINO_CREALITY

//                  | DIGITAL | ANALOG | USART     | TWI      | SPI                    | SPECIAL   |
//                  |---------|--------|-----------|----------|------------------------|-----------|
#define PA0  0  // | 0       | A0     |           |          |                        |           |
#define PA1  1  // | 1       | A1     |           |          |                        |           |
#define PA2  2  // | 2       | A2     | USART2_TX |          |                        |           |
#define PA3  3  // | 3       | A3     | USART2_RX |          |                        |           |
#define PA4  3  // | 4       | A4     |           |          | SPI1_SS, (SPI3_SS)     |           |
#define PA5  5  // | 5       | A5     |           |          | SPI1_SCK               |           |
#define PA6  6  // | 6       | A6     |           |          | SPI1_MISO              |           |
#define PA7  7  // | 7       | A7     |           |          | SPI1_MOSI              |           |
#define PA8  8   // | 8       |        |           | TWI3_SCL |                        |           |
#define PA9  9   // | 9       |        | USART1_TX |          |                        |           |
#define PA10 10  // | 10      |        | USART1_RX |          |                        |           |
#define PA11 11  // | 11      |        | USART6_TX |          |                        |           |
#define PA12 12  // | 12      |        | USART6_RX |          |                        |           |
#define PA13 13  // | 13      |        |           |          |                        | SWD_SWDIO |
#define PA14 14  // | 14      |        |           |          |                        | SWD_SWCLK |
#define PA15 15  // | 15      |        |           |          | SPI3_SS, (SPI1_SS)     |           |
//                  |---------|--------|-----------|----------|------------------------|-----------|
#define PB0  16  // | 16      | A8     |           |          |                        |           |
#define PB1  17  // | 17      | A9     |           |          |                        |           |
#define PB2  18  // | 18      |        |           |          |                        | BOOT1     |
#define PB3  19  // | 19      |        |           | TWI2_SDA | SPI3_SCK,  (SPI1_SCK)  |           |
#define PB4  20  // | 20      |        |           | TWI3_SDA | SPI3_MISO, (SPI1_MISO) |           |
#define PB5  21  // | 21      |        |           |          | SPI3_MOSI, (SPI1_MOSI) |           |
#define PB6  22  // | 22      |        | USART1_TX | TWI1_SCL |                        |           |
#define PB7  23  // | 23      |        | USART1_RX | TWI1_SDA |                        |           |
#define PB8  24  // | 24      |        |           | TWI1_SCL |                        |           |
#define PB9  25  // | 25      |        |           | TWI1_SDA | SPI2_SS                |           |
#define PB10 26  // | 26      |        |           | TWI2_SCL | SPI2_SCK               |           |
#define PB12 27  // | 27      |        |           |          | SPI2_SS                |           |
#define PB13 28  // | 28      |        |           |          | SPI2_SCK               |           |
#define PB14 29  // | 29      |        |           |          | SPI2_MISO              |           |
#define PB15 30  // | 30      |        |           |          | SPI2_MOSI              |           |
//                  |---------|--------|-----------|----------|------------------------|-----------|
#define PC0  31 // | 31      | A10    |           |          |                        |           |
#define PC1  32 // | 32      | A11    |           |          |                        |           |
#define PC2  33 // | 33      | A12    |           |          | SPI2_MISO              |           |
#define PC3  34 // | 34      | A13    |           |          | SPI2_MOSI              |           |
#define PC4  35 // | 35      | A14    |           |          |                        |           |
#define PC5  36 // | 36      | A15    |           |          |                        |           |
#define PC6  37  // | 37      |        | USART6_TX |          |                        |           |
#define PC7  38  // | 38      |        | USART6_RX |          |                        |           |
#define PC8  39  // | 39      |        |           |          |                        |           |
#define PC9  40  // | 40      |        |           | TWI3_SDA |                        |           |
#define PC10 41  // | 41      |        |           |          | SPI3_SCK               |           |
#define PC11 42  // | 42      |        |           |          | SPI3_MISO              |           |
#define PC12 43  // | 43      |        |           |          | SPI3_MOSI              |           |
#define PC13 44  // | 44      |        |           |          |                        |           |
#define PC14 45  // | 45      |        |           |          |                        | OSC32_IN  |
#define PC15 46  // | 46      |        |           |          |                        | OSC32_OUT |
//                  |---------|--------|-----------|----------|------------------------|-----------|
#define PD0  47   // Digital pin 47
#define PD1  48   // Digital pin 48
#define PD2  49   // Digital pin 49
#define PD3  50   // Digital pin 50
#define PD4  51   // Digital pin 51
#define PD5  52   // Digital pin 52
#define PD6  53   // Digital pin 53
#define PD7  54   // Digital pin 54
#define PD8  55   // Digital pin 55
#define PD9  56   // Digital pin 56
#define PD10 57   // Digital pin 57
#define PD11 58   // Digital pin 58
#define PD12 59   // Digital pin 59
#define PD13 60   // Digital pin 60
#define PD14 61   // Digital pin 61
#define PD15 62   // Digital pin 62

#define PE0  63  // Digital pin 63
#define PE1  64  // Digital pin 64
#define PE2  65  // Digital pin 65
#define PE3  66  // Digital pin 66
#define PE4  67  // Digital pin 67
#define PE5  68  // Digital pin 68
#define PE6  69  // Digital pin 69
#define PE7  70  // Digital pin 70
#define PE8  71  // Digital pin 71
#define PE9  72  // Digital pin 72
#define PE10 73  // Digital pin 73
#define PE11 74  // Digital pin 74
#define PE12 75  // Digital pin 75
#define PE13 76  // Digital pin 76
#define PE14 77  // Digital pin 77
#define PE15 78  // Digital pin 78

//                  |---------|--------|-----------|----------|------------------------|-----------|
#define PH0  79  // | 48      |        |           |          |                        | OSC_IN    |
#define PH1  80  // | 49      |        |           |          |                        | OSC_OUT   |
//                  |---------|--------|-----------|----------|------------------------|-----------|

// This must be a literal
#define NUM_DIGITAL_PINS        80
#define NUM_ANALOG_INPUTS       16

// On-board LED pin number
#ifdef ARDUINO_CoreBoard_F401RC
#define LED_BUILTIN             PB10
#endif
// #ifndef LED_BUILTIN
// #define LED_BUILTIN             PA5
// #endif
// #define LED_GREEN               LED_BUILTIN

// On-board user button
#if !defined(USER_BTN) && !defined(ARDUINO_CoreBoard_F401RC)
#define USER_BTN                PC13
#endif

// SPI definitions
// #define PIN_SPI_SS              PA4
// #define PIN_SPI_SS1             PA4
// #define PIN_SPI_SS2             PB12
// #define PIN_SPI_SS3             PA15
// #define PIN_SPI_MOSI            PA7
// #define PIN_SPI_MISO            PA6
// #define PIN_SPI_SCK             PA5

// I2C definitions
// #define PIN_WIRE_SDA            PB9
// #define PIN_WIRE_SCL            PB8

// Timer Definitions
#define TIMER_TONE              TIM10
#define TIMER_SERVO             TIM11

// UART Definitions
#define SERIAL_UART_INSTANCE    1

// Default pin used for 'Serial' instance
// Mandatory for Firmata
#define PIN_SERIAL_RX           PA10
#define PIN_SERIAL_TX           PA9

#ifdef ARDUINO_CoreBoard_F401RC
// USB, pull this pin low to enable the USB attach pullup
// It is documented here, but not actually used, since there are also
// internal pullups which are automatically used and using both would
// violate the USB specification for pullup strength.
//#define USBD_ATTACH_PIN         PD2
//#define USBD_ATTACH_LEVEL       LOW
#endif

#define USB_OTG_HS USB_OTG_FS
#define OTG_HS_WKUP_IRQn 76
#define OTG_HS_IRQn 77
#define PinMap_USB_OTG_HS PinMap_USB_OTG_FS
#define __HAL_RCC_USB_OTG_HS_CLK_ENABLE()

#endif

#ifdef __cplusplus
} // extern "C"
#endif
/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus
  // These serial port names are intended to allow libraries and architecture-neutral
  // sketches to automatically default to the correct port name for a particular type
  // of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
  // the first hardware serial port whose RX/TX pins are not dedicated to another use.
  //
  // SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
  //
  // SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
  //
  // SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
  //
  // SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
  //
  // SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
  //                            pins are NOT connected to anything by default.
  #define SERIAL_PORT_MONITOR     Serial
  #define SERIAL_PORT_HARDWARE    Serial
#endif

#endif /* _VARIANT_ARDUINO_STM32_ */
