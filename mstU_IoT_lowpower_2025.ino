// based on Adafruit IO Publish Example
// modified by Martin Fierz

/************************** Configuration ***********************************/
#include "AdafruitIO_WiFi.h"
#include <Adafruit_Sensor.h>
#include "Adafruit_SHT4x.h"

#define IO_USERNAME   "your user name"
#define IO_KEY        "your Adafruit IO key"
#define WIFI_SSID     "your wifi hotspot"
#define WIFI_PASS     "your wifi password"

// io object for communication with Adafruit cloud
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// sht41 object for communication with RH/T sensor
Adafruit_SHT4x sht4 = Adafruit_SHT4x(); 

// set up the 'temperature' and 'humidity' feeds
AdafruitIO_Feed *temperature = io.feed("Temperature");
AdafruitIO_Feed *humidity = io.feed("Humidity");

#define DEEPSLEEP_DURATION 53e6  // sleep for 53 mio us = 53s because transmission takes about 7 seconds, so this is one data point every minute
#define uS_TO_S_FACTOR 1000000ULL /* Conversion factor for micro seconds to seconds */

void setup() {
  sensors_event_t SHThumidity, SHTtemp;

  setup_LED(); 

  setup_serialcommunication(); 
  
  // connect to RH_temp sensor
  connectSHT40();

  // connect to adafruit.IO
  connectAIO();

  // get data
  Serial.println();
  sht4.getEvent(&SHThumidity, &SHTtemp);        // populate temp and humidity objects with fresh data
  Serial.print("Temperature: "); 
  Serial.print(SHTtemp.temperature); 
  Serial.println(" degrees C");
  Serial.print("Humidity: "); 
  Serial.print(SHThumidity.relative_humidity); 
  Serial.println("% rH");

  // write to cloud
  temperature->save(SHTtemp.temperature);
  humidity->save(SHThumidity.relative_humidity); 
  delay(100); 

  // Deep sleep mode, the ESP8266 wakes up by itself when GPIO 16 is connected to the RESET pin
  Serial.println("sleeping...");
  ESP.deepSleep(DEEPSLEEP_DURATION); 
}


// loop is never excecuted here because we go to sleep.
// at next wakeup, setup is executed again
void loop() {
}

void setup_LED() {
  // set up LED
  pinMode(0, OUTPUT);  
}

void setup_serialcommunication() {
  // start the serial connection and wait for serial communication to start
  Serial.begin(115200);
  while(! Serial);
  Serial.println("Adafruit SHT4x test");
}

void connectAIO() {
  Serial.println("Connecting to Adafruit IO...");
  io.connect();

  // wait for a connection
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
}

void connectSHT40() {
  Serial.println("Connecting to SHT4x");
  while (! sht4.begin()) {
    Serial.println("Couldn't find SHT4x");
    delay(100);
  }
  Serial.println("Found SHT4x sensor");
  Serial.print("Serial number 0x");
  Serial.println(sht4.readSerial(), HEX);

  sht4.setPrecision(SHT4X_HIGH_PRECISION);
  sht4.setHeater(SHT4X_NO_HEATER);
}
