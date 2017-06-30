// DHT Temperature & Humidity Sensor
// Unified Sensor Library Example
// Written by Tony DiCola for Adafruit Industries
// Released under an MIT license.

// Depends on the following Arduino libraries:
// - Adafruit Unified Sensor Library: https://github.com/adafruit/Adafruit_Sensor
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include "Adafruit_SHT31.h"
#include "SputinkRedeSensores.h"

#define DHT11_PIN            53         // Pin which is connected to the DHT sensor.
#define DHT22_PIN            52         // Pin which is connected to the DHT sensor.

// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

DHT_Unified dht11(DHT11_PIN, DHT11);
DHT_Unified dht22(DHT22_PIN, DHT22);
Adafruit_SHT31 sht31 = Adafruit_SHT31();

uint32_t delayMS;

void setup() {
  Serial.begin(9600);
  // Initialize DHTs.
  dht11.begin();
  dht22.begin();
  sensor_t sensorDHT11, sensorDHT22;
  dht11.temperature().getSensor(&sensorDHT11);
  Serial.println("------------------------------------");
  Serial.println("Temperature DHT11");
  Serial.print  ("Sensor:       "); Serial.println(sensorDHT11.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensorDHT11.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensorDHT11.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensorDHT11.max_value); Serial.println(" *C");
  Serial.print  ("Min Value:    "); Serial.print(sensorDHT11.min_value); Serial.println(" *C");
  Serial.print  ("Resolution:   "); Serial.print(sensorDHT11.resolution); Serial.println(" *C");
  Serial.println("------------------------------------");
  dht11.humidity().getSensor(&sensorDHT11);
  Serial.println("------------------------------------");
  Serial.println("Humidity DHT11");
  Serial.print  ("Sensor:       "); Serial.println(sensorDHT11.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensorDHT11.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensorDHT11.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensorDHT11.max_value); Serial.println("%");
  Serial.print  ("Min Value:    "); Serial.print(sensorDHT11.min_value); Serial.println("%");
  Serial.print  ("Resolution:   "); Serial.print(sensorDHT11.resolution); Serial.println("%");
  Serial.println("------------------------------------");
  dht22.temperature().getSensor(&sensorDHT22);
  Serial.println("------------------------------------");
  Serial.println("Temperature DHT22");
  Serial.print  ("Sensor:       "); Serial.println(sensorDHT22.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensorDHT22.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensorDHT22.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensorDHT22.max_value); Serial.println(" *C");
  Serial.print  ("Min Value:    "); Serial.print(sensorDHT22.min_value); Serial.println(" *C");
  Serial.print  ("Resolution:   "); Serial.print(sensorDHT22.resolution); Serial.println(" *C");
  Serial.println("------------------------------------");
  dht11.humidity().getSensor(&sensorDHT11);
  Serial.println("------------------------------------");
  Serial.println("Humidity DHT22");
  Serial.print  ("Sensor:       "); Serial.println(sensorDHT22.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensorDHT22.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensorDHT22.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensorDHT22.max_value); Serial.println("%");
  Serial.print  ("Min Value:    "); Serial.print(sensorDHT22.min_value); Serial.println("%");
  Serial.print  ("Resolution:   "); Serial.print(sensorDHT22.resolution); Serial.println("%");
  Serial.println("------------------------------------");
  //Initialize SHT31
  if (! sht31.begin(0x44)) {   // Set to 0x45 for alternate i2c addr
    Serial.println("Couldn't find SHT31");
    //while (1) delay(1);
  }

  // Set delay between sensor readings based on sensor details.
  delayMS = sensorDHT11.min_delay / 1000;
  delayMS = (sensorDHT22.min_delay / 1000 > delayMS)  ? (sensorDHT22.min_delay / 1000)  : delayMS;
  delayMS = (SENSORS_READ_INTERVAL > delayMS) ? SENSORS_READ_INTERVAL : delayMS;
}

void loop() {
  // Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event11, event22;
  dht11.temperature().getEvent(&event11);
  if (isnan(event11.temperature)) {
    Serial.println("Error reading DHT11 temperature!");
  }
  else {
    Serial.print("Temperature DHT11: ");
    Serial.print(event11.temperature);
    Serial.println(" *C");
  }
  // Get humidity event and print its value.
  dht11.humidity().getEvent(&event11);
  if (isnan(event11.relative_humidity)) {
    Serial.println("Error reading DHT11 humidity!");
  }
  else {
    Serial.print("Humidity DHT11: ");
    Serial.print(event11.relative_humidity);
    Serial.println("%");
  }
  dht22.temperature().getEvent(&event22);
  if (isnan(event22.temperature)) {
    Serial.println("Error reading DHT22 temperature!");
  }
  else {
    Serial.print("Temperature DHT22: ");
    Serial.print(event22.temperature);
    Serial.println(" *C");
  }
  // Get humidity event and print its value.
  dht22.humidity().getEvent(&event22);
  if (isnan(event22.relative_humidity)) {
    Serial.println("Error reading DHT22 humidity!");
  }
  else {
    Serial.print("Humidity DHT22: ");
    Serial.print(event22.relative_humidity);
    Serial.println("%");
  }

  float t = sht31.readTemperature();
  float h = sht31.readHumidity();

  if (! isnan(t)) {  // check if 'is not a number'
    Serial.print("Temperature SHT31: ");
    Serial.print(t);
    Serial.println(" *C");

  } else {
    Serial.println("Error reading SHT31 temperature!");
  }

  if (! isnan(h)) {  // check if 'is not a number'
    Serial.print("Humidity SHT31: ");
    Serial.print(h);
    Serial.println("%");
  } else {
    Serial.println("Error reading SHT31 humidity!");
  }
  Serial.println("------------------------------------");
  delay(1000);
}
