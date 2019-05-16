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
 * About Generator
 *
 * Data generator part of collaborative project for the course
 * Development of software for the automotive industry.
 */

#include "Generator.h"

MAX6675 thermocouple(THERMO_CLK, THERMO_CS, THERMO_DO);

/**
 * Generator entry-point: Set up before the program loop
 *  - Start the serial port
 *  - Print startup messages and diagnostics
 *  - Get EEPROM or default settings
 *  - Initialize managers for:
 *	  • sensors
 *    • status LEDs
 */
void setup() {
  Serial.begin(BAUDRATE);
  // use Arduino pins 
  pinMode(VCC_PIN, OUTPUT); digitalWrite(VCC_PIN, HIGH);
  pinMode(GND_PIN, OUTPUT); digitalWrite(GND_PIN, LOW);
  
  //Serial.println("MAX6675 test123");
  //Serial.println(BOARD_NAME);
  
  SERIAL_ECHOLN("MAX6675 test123");
  SERIAL_ECHOLN(BOARD_NAME);

  // wait for MAX chip to stabilize
  delay(TERMO_SETUP_SLEEP);
}

/**
 * The main Generator program loop
 *
 *  - Get speed in kmph
 *	- Get outside temperature
 *	- Get engine temperature
 *	- Get engine rpm
 *	- Get engine oil level
 *  - Process available commands (if not saving)
 */
void loop() {
  // basic readout test, just print the current temp
  
   SERIAL_ECHO("C = "); 
   SERIAL_ECHOLN(thermocouple.readCelsius());
   SERIAL_ECHO("F = ");
   SERIAL_ECHOLN(thermocouple.readFahrenheit());
 
   delay(1000);
}