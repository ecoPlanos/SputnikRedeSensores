// DHT Temperature & Humidity Sensor
// Unified Sensor Library Example
// Written by Tony DiCola for Adafruit Industries
// Released under an MIT license.

// Depends on the following Arduino libraries:
// - Adafruit Unified Sensor Library: https://github.com/adafruit/Adafruit_Sensor
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_SHT31.h>
#include <Sensirion.h>    //SHT75
#include <Adafruit_MLX90614.h>
//#include "SputinkRedeSensores.h"
#define INITIAL_DELAY 100
#define SENSORS_READ_INTERVAL 10000 //Sensors read minimum interval (ms)
#define DHT11_PIN            53         // Pin which is connected to the DHT sensor.
#define DHT22_PIN            52         // Pin which is connected to the DHT sensor.
#define SHT75_DATA           50         //
#define SHT75_SCK            51         //

// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

DHT_Unified dht11(DHT11_PIN, DHT11);
DHT_Unified dht22(DHT22_PIN, DHT22);
Adafruit_SHT31 sht31 = Adafruit_SHT31();
Sensirion sht75(SHT75_DATA, SHT75_SCK);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
uint32_t delayMS;

void setup() {
  Serial.begin(9600);
  delay(INITIAL_DELAY);
  // Initialize DHTs.
  dht11.begin();
  dht22.begin();
  sensor_t sensorDHT11, sensorDHT22;
  dht11.temperature().getSensor(&sensorDHT11);
  Serial.println("------------------------------------");
  Serial.println("");
  Serial.println("-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-");

  Serial.println();
  delay(500);
  //Initialize SHT31
  if (! sht31.begin(0x44)) {   // Set to 0x45 for alternate i2c addr
    Serial.println("Couldn't find SHT31");
    //while (1) delay(1);
  }

  // Set delay between sensor readings based on sensor details.
  delayMS = (uint32_t)(sensorDHT11.min_delay / 1000);
  delayMS = ((uint32_t)(sensorDHT22.min_delay / 1000) > delayMS)  ? ((uint32_t)(sensorDHT22.min_delay / 1000))  : delayMS;
  delayMS = (SENSORS_READ_INTERVAL > delayMS) ? SENSORS_READ_INTERVAL : delayMS;
}

void loop() {
  // Get temperature event and print its value.
  Serial.println("------------------------------------");
  Serial.println("----------------T&RH----------------");
  Serial.println("------------------------------------");

  sensors_event_t event11, event22;
  dht11.temperature().getEvent(&event11);
  if (isnan(event11.temperature)) {
    Serial.println("Error reading DHT11 temperature!");
  }
  else {
    Serial.print("DHT11 Temp: ");
    Serial.print(event11.temperature);
    Serial.println(" *C");
  }
  // Get humidity event and print its value.
  dht11.humidity().getEvent(&event11);
  if (isnan(event11.relative_humidity)) {
    Serial.println("Error reading DHT11 humidity!");
  }
  else {
    Serial.print("DHT11 RH: ");
    Serial.print(event11.relative_humidity);
    Serial.println("%");
  }
  dht22.temperature().getEvent(&event22);
  if (isnan(event22.temperature)) {
    Serial.println("Error reading DHT22 temperature!");
  }
  else {
    Serial.print("DHT22 Temp: ");
    Serial.print(event22.temperature);
    Serial.println(" *C");
  }
  // Get humidity event and print its value.
  dht22.humidity().getEvent(&event22);
  if (isnan(event22.relative_humidity)) {
    Serial.println("Error reading DHT22 humidity!");
  }
  else {
    Serial.print("DHT22 RH: ");
    Serial.print(event22.relative_humidity);
    Serial.println("%");
  }

  float t = sht31.readTemperature();
  float h = sht31.readHumidity();

  if (! isnan(t)) {  // check if 'is not a number'
    Serial.print("SHT31 Temp: ");
    Serial.print(t);
    Serial.println(" *C");

  } else {
    Serial.println("Error reading SHT31 temperature!");
  }

  if (! isnan(h)) {  // check if 'is not a number'
    Serial.print("SHT31 RH: ");
    Serial.print(h);
    Serial.println("%");
  } else {
    Serial.println("Error reading SHT31 humidity!");
  }
float sht75_temp, sht75_hr, sht75_dewpoint;
sht75.measure(&sht75_temp, &sht75_hr, &sht75_dewpoint);
if (! isnan(sht75_temp)) {  // check if 'is not a number'
    Serial.print("SHT75 Temp: ");
    Serial.print(sht75_temp);
    Serial.println(" *C");

  } else {
    Serial.println("Error reading SHT75 temperature!");
  }

  if (! isnan(sht75_hr)) {  // check if 'is not a number'
    Serial.print("SHT75 RH: ");
    Serial.print(sht75_hr);
    Serial.println("%");
  } else {
    Serial.println("Error reading SHT75 humidity!");
  }
  if (! isnan(h)) {  // check if 'is not a number'
    Serial.print("SHT75 Dewpoint: ");
    Serial.print(sht75_dewpoint);
    Serial.println("C");
  } else {
    Serial.println("Error reading SHT75 humidity!");
  }
  Serial.println("------------------------------------");
  Serial.println("----------------TEMP----------------");
  Serial.println("------------------------------------");
  float t_amb = mlx.readAmbientTempC();
  float t_obj = mlx.readObjectTempC();

  if (! isnan(t)) {  // check if 'is not a number'
    Serial.print("MLX90614 Ambient Temp: ");
    Serial.print(t_amb);
    Serial.println(" *C");
    Serial.print("MLX90614 Object Temp: ");
    Serial.print(t_obj);
    Serial.println(" *C");
  } else {
    Serial.println("Error reading MLX90614 temperature!");
  }
  // Delay between measurements.
  delay(delayMS);
}
