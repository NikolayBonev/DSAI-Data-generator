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
dht DHT; // Create a DHT object
TinyGPSPlus gps; // Create a TinyGPS++ object
// Uncomment only for UNO controller
//SoftwareSerial ss(GPS_RX, GPS_TX); // The serial connection to the GPS device
//SoftwareSerial esp_ss(ESP_RX, ESP_TX); // The serial connection to the ESP8266 device

// variables will change:
String incomming_string="";
String buf;
String ecu_code="P0000";
int val0 = 0; // potentiometer value
int val1 = 0;
int val2 = 0;
int buttonState2 = 0; // button state
int buttonState3 = 0;
int buttonState4 = 0;
int buttonState5 = 0;
float t, h; // DHT sensor
float gps_lat, gps_lng; // GPS
int Vo; // thermistor
float logR2, R2, T, Tc, Tf; // thermistor
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07; // thermistor
unsigned long previousMillis = 0; // will store last updated time

/**
 * Generator entry-point: Set up before the program loop
 *  - Start the serial port
 *  - Print startup messages and diagnostics
 *  - Get EEPROM or default settings
 *  - Initialize managers for:
 *	  • sensors
 *    • status LEDs
 */
void setup(){
  Serial.begin(BAUDRATE);
  Serial1.begin(ESP_BAUDRATE);
  Serial2.begin(GPS_BAUDRATE);

  //Set car pins
  pinMode(HEADLIGHTS, OUTPUT);
  digitalWrite(HEADLIGHTS, LOW);
  // Uncomment only for UNO controller
  //ss.begin(GPS_BAUDRATE);
  //esp_ss.begin(ESP_BAUDRATE);

  // use Arduino pins 
  //pinMode(VCC_PIN, OUTPUT); digitalWrite(VCC_PIN, HIGH);
  //pinMode(GND_PIN, OUTPUT); digitalWrite(GND_PIN, LOW);

  SERIAL_ECHOLN(BOARD_NAME);

  // wait for MAX chip to stabilize
  delay(TERMOCOUPLE_SLEEP);
}

void control_sensors(){
  //Potentiometers and buttons test
  val0 = analogRead(POT_PIN0); // read the value from the potentiometer
  val1 = analogRead(POT_PIN1);
  val2 = analogRead(POT_PIN2);

  buttonState2 = digitalRead(BUTTON_PIN2); // read the value from the button
  buttonState3 = digitalRead(BUTTON_PIN3);
  buttonState4 = digitalRead(BUTTON_PIN4);
  buttonState5 = digitalRead(BUTTON_PIN5);
  
  if (buttonState3 == 1){
    ecu_code = "P0001";
  }
  else{
    ecu_code = "P0000";
  }
}

void dht_termocouple(){
  int readData = DHT.read22(DHT22_PIN); // Reads the data from the sensor
  t = DHT.temperature; // Gets the values of the temperature
  h = DHT.humidity; // Gets the values of the humidity
  
  // Termocouple  
  // basic readout test, just print the current temp from termocouple  
  //SERIAL_ECHO("C = "); 
  //SERIAL_ECHOLN(thermocouple.readCelsius());
  //SERIAL_ECHO("F = ");
  //SERIAL_ECHOLN(thermocouple.readFahrenheit());
 
  //delay(DHT22_SLEEP); // Delays 2 secods, as the DHT22 sampling rate is 0.5Hz
}

void thermistor(){
  Vo = analogRead(THERMISTORPIN);
  R2 = THERMISTORNOMINAL * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  Tc = T - 273.15;
  //Tf = (Tc * 9.0)/ 5.0 + 32.0; 
}

void serial_print() {
  buf = F("\"speed\":"); buf += int(val1/SPEED_CONST);
  buf += F(";\"rpm\":"); buf += int(val0/RPM_CONST);
  buf += F(";\"engine_temp\":"); buf += Tc;
  buf += F(";\"engine_warning\":"); buf += ecu_code;
  buf += F(";\"fog_lamp\":"); buf += buttonState5;
  buf += F(";\"hazard_lamp\":"); buf += buttonState2;
  buf += F(";\"gps_latitude\":"); buf += gps_lat;
  buf += F(";\"gps_longitude\":"); buf += gps_lng;
  buf += F(";\"air_temp\":"); buf += t;
  buf += F(";\"air_humidity\":"); buf += h;
  buf += F(";\"handbrake\":"); buf += buttonState4;
  buf += F(";\"fuel\":"); buf += int(val2/FUEL_CONST); buf += F(";");
  /*sprintf(message_buf,"\"speed\":%d;\"rpm\":%d;\"engine_temp\":%f;\
\"engine_warning\":\"%s\";\"fog_lamp\":%s;\"hazard_lamp\":%s;\
\"gps_latitude\":%f;\"gps_longitude\":%f;\"air_temp\":%f;\
\"air_humidity\":%f;\"handbrake\":%s;\"fuel\":%d;",int(val1/4.2625),\
int(val0/0.1364),float(Tc),int(buttonState3),int(buttonState5),int(buttonState2),float(gps_lat),\
float(gps_lng),float(t),float(h),int(buttonState4),int(val2/10.23));*/
  SERIAL_ECHOLN(buf);
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
  /**
   *Read sensors data without using the delay() function. 
   *This means that other code can run at the
   *same time without being interrupted by the delay().
   */
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= SENSORS_READ){
    // save the last time
    previousMillis = currentMillis;

    // DHT22 and termocouple test
    dht_termocouple();

    // Potentiometers and buttons test
    control_sensors();

    // Thermistor test
    thermistor();

    // Send data to serial port
    serial_print();
  }
  //else if (currentMillis - previousMillis >= SENSORS_READ){
    // Potentiometers and buttons test
  //  control_sensors();
  //}

  // GPS test
  while (Serial2.available() > 0 ){
    gps.encode(Serial2.read());
    if (gps.location.isUpdated()){
      gps_lat = gps.location.lat();
      gps_lng = gps.location.lng();
      //SERIAL_ECHO("Latitude= "); 
      //Serial.println(gps_lat, 6);
      //SERIAL_ECHO("Longitude= "); 
      //Serial.println(gps_lng, 6);
    }
  }

  // ESP test
  while ( Serial1.available() > 0 ){
    incomming_string=Serial1.readString();
    if (incomming_string.indexOf("FUNCTION1ON") > 0){
      digitalWrite(HEADLIGHTS, HIGH);
    }
    else if (incomming_string.indexOf("FUNCTION1OFF") > 0){
      digitalWrite(HEADLIGHTS, LOW);
    }
  }
}
