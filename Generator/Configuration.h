/**
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/**
 * Configuration.h
 *
 * Basic settings such as:
 *
 * - Type of electronics
 * - Type of sensors
 *
 */
#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#define CONFIGURATION_H_VERSION 150519

//===========================================================================
//============================= Getting Started =============================
//===========================================================================

// User-specified version info of this build to display in terminal window during
// startup. 
#define STRING_CONFIG_H_AUTHOR "(none, default config)" // Who made the changes.
#define SHOW_BOOTSCREEN
#define STRING_SPLASH_LINE1 SHORT_BUILD_VERSION // will be shown during bootup in line 1
#define STRING_SPLASH_LINE2 WEBSITE_URL         // will be shown during bootup in line 2

/**
 * Select which serial port on the board will be used for communication with the host.
 * This allows the connection of wireless adapters (for instance) to non-default port pins.
 * Serial port 0 is always used by the Arduino bootloader regardless of this setting.
 *
 * :[0, 1, 2, 3, 4, 5, 6, 7]
 */
#define SERIAL_PORT 0

/**
 * This setting determines the communication speed of the controller.
 *
 * :[2400, 9600, 19200, 38400, 57600, 115200, 250000, 500000, 1000000]
 */
#define BAUDRATE 9600

/**
 * If your GPS module uses a different default baud rate,
 * you should also modify that. You need to change that to 9600,
 * if you’re using the NEO-6M GPS module.
*/
#define GPS_BAUDRATE 9600

/**
 * This setting determines the communication speed of the EXP8266 module.
*/
#define ESP_BAUDRATE 9600

/**
 * Constants
 */
#define SPEED_CONST 4.2625
#define RPM_CONST 0.1364
#define FUEL_CONST 10.23

// The following define selects which electronics board you have.
// Please choose the name that matches your setup
// Available boards: BOARD_UNOCONTROLLER, BOARD_MEGACONTROLLER
#ifndef MOTHERBOARD
  #define MOTHERBOARD BOARD_MEGACONTROLLER
#endif

#endif // CONFIGURATION_H