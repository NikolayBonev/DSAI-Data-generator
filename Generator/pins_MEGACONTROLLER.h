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
 * MEGA controller pin assignments
 */

#define BOARD_NAME "MEGA Controller"

//
// Thermocouple pins
//
#define THERMO_DO			5
#define THERMO_CS 			4
#define THERMO_CLK 			3

#define DHT22_PIN			2
//#define VCC_PIN 			9
//#define GND_PIN 			10
#define GPS_RX				17
#define GPS_TX				16
#define ESP_RX				18
#define	ESP_TX				19

//
// Potentiometers and buttons
//
#define POT_PIN0			 0
#define POT_PIN1 			 1
#define POT_PIN2 			 2

#define BUTTON_PIN2 		 50
#define BUTTON_PIN3 		 51
#define BUTTON_PIN4 		 52
#define BUTTON_PIN5 		 53

//
// Car lights and other electronics
//
#define HEADLIGHTS 			 49

//
// Thermistor
//
#define THERMISTORPIN A3 // which analog pin to connect     
#define THERMISTORNOMINAL 10000 // resistance at 25 degrees C      

//
// Delay times
//
#define TERMOCOUPLE_SLEEP	500
#define SENSORS_READ		1000
//#define	DHT22_SLEEP			5000