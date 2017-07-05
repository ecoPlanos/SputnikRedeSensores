// DHT Temperature & Humidity Sensor
// Unified Sensor Library Example
// Written by Tony DiCola for Adafruit Industries
// Released under an MIT license.

// Depends on the following Arduino libraries:
// - Adafruit Unified Sensor Library: https://github.com/adafruit/Adafruit_Sensor
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library

#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_SHT31.h>
#include <Sensirion.h>    //SHT75
#include <Adafruit_MLX90614.h>
//#include "SputinkRedeSensores.h"
#define INITIAL_DELAY 100
// #define SENSORS_READ_INTERVAL 10000 //Sensors read minimum interval (ms)
#define SENSORS_READ_INTERVAL 1000 //Sensors read minimum interval (ms)

#define DHT11_PIN            53         // Pin which is connected to the DHT sensor.
#define DHT22_PIN            52         // Pin which is connected to the DHT sensor.
#define SHT75_DATA           50         //
#define SHT75_SCK            51         //

#define SD_CHIP_SEL          4//10

#define LOG_SD
#define LOG_SERIAL

const String log_file_name="datalog.csv";
// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

uint32_t sys_time, sys_time_last, setup_time, acquisition_time;

uint8_t sd_present=false;

Sd2Card card;
SdVolume volume;
SdFile root;
File log_file;

DHT_Unified dht11(DHT11_PIN, DHT11);
DHT_Unified dht22(DHT22_PIN, DHT22);
Adafruit_SHT31 sht31 = Adafruit_SHT31();
Sensirion sht75(SHT75_DATA, SHT75_SCK);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
uint32_t delayMS;

void setup() {
  sys_time = millis();
  sys_time_last = sys_time;
  #ifdef LOG_SERIAL
  Serial.begin(9600);
  #endif
  #ifdef LOG_SD
   if (!SD.begin(SD_CHIP_SEL))
   {
     #ifdef LOG_SERIAL
     Serial.println("Card failed, or not present");
     #endif
     sd_present=false;
   }
   else
   {
     #ifdef LOG_SERIAL
     Serial.println("SD card initialized.");
     #endif
     sd_present=true;
   }
  #endif  //ifdef LOG_SD
  delay(INITIAL_DELAY);
  // Initialize DHTs.
  dht11.begin();
  dht22.begin();
  sensor_t sensorDHT11, sensorDHT22;
  dht11.temperature().getSensor(&sensorDHT11);
  #ifdef LOG_SERIAL
  Serial.println("-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-");
  Serial.println(".i.SputnikRedeSensores by ecoPlanos.i.");
  Serial.println("-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-");
  Serial.println();
  #endif
  //Initialize SHT31
  if (! sht31.begin(0x44)) {   // Set to 0x45 for alternate i2c addr
    #ifdef LOG_SERIAL
    Serial.println("Couldn't find SHT31");
    #endif
  }

  // Set delay between sensor readings based on sensor details.
  delayMS = (uint32_t)(sensorDHT11.min_delay / 1000);
  delayMS = ((uint32_t)(sensorDHT22.min_delay / 1000) > delayMS)  ? ((uint32_t)(sensorDHT22.min_delay / 1000))  : delayMS;
  delayMS = (SENSORS_READ_INTERVAL > delayMS) ? SENSORS_READ_INTERVAL : delayMS;
  sys_time = micros();
  setup_time = sys_time-sys_time_last;
  sys_time_last = sys_time;
}

void loop() {
  sys_time = micros();
  acquisition_time = sys_time-sys_time_last;
  sys_time_last = sys_time;
  String sd_data_string = "";
  // Get temperature event and print its value.

  #ifdef LOG_SERIAL
  Serial.println("------------------------------------");
  Serial.println("----------------T&RH----------------");
  Serial.println("------------------------------------");
  #endif

  sensors_event_t dht11_data, dht22_data;
  dht11.temperature().getEvent(&dht11_data);

  if (isnan(dht11_data.temperature)) {
    #ifdef LOG_SERIAL
    Serial.println("Error reading DHT11 temperature!");
    #endif
    sd_data_string+=",";
  }
  else {
    #ifdef LOG_SERIAL
    Serial.print("DHT11 Temp: ");
    Serial.print(dht11_data.temperature);
    Serial.println(" *C");
    #endif
    sd_data_string+=String(dht11_data.temperature)+",";
  }
  // Get humidity event and print its value.
  dht11.humidity().getEvent(&dht11_data);
  if (isnan(dht11_data.relative_humidity)) {
    #ifdef LOG_SERIAL
    Serial.println("Error reading DHT11 humidity!");
    #endif
    sd_data_string+=String(",");
  }
  else {
    #ifdef LOG_SERIAL
    Serial.print("DHT11 RH: ");
    Serial.print(dht11_data.relative_humidity);
    Serial.println("%");
    #endif
    sd_data_string+=String(dht11_data.relative_humidity)+",";
  }
  dht22.temperature().getEvent(&dht22_data);
  if (isnan(dht22_data.temperature)) {
    #ifdef LOG_SERIAL
    Serial.println("Error reading DHT22 temperature!");
    #endif
    sd_data_string+=",";
  }
  else {
    #ifdef LOG_SERIAL
    Serial.print("DHT22 Temp: ");
    Serial.print(dht22_data.temperature);
    Serial.println(" *C");
    #endif
    sd_data_string+=String(dht22_data.temperature)+",";
  }
  // Get humidity event and print its value.
  dht22.humidity().getEvent(&dht22_data);
  if (isnan(dht22_data.relative_humidity)) {
    #ifdef LOG_SERIAL
    Serial.println("Error reading DHT22 humidity!");
    #endif
    sd_data_string+=",";
  }
  else {
    #ifdef LOG_SERIAL
    Serial.print("DHT22 RH: ");
    Serial.print(dht22_data.relative_humidity);
    Serial.println("%");
    #endif
    sd_data_string+=String(dht22_data.relative_humidity)+",";
  }

  float sht31_temp = sht31.readTemperature();
  float sht31_hr = sht31.readHumidity();

  if (! isnan(sht31_temp)) {  // check if 'is not a number'
    #ifdef LOG_SERIAL
    Serial.print("SHT31 Temp: ");
    Serial.print(sht31_temp);
    Serial.println(" *C");
    #endif
    sd_data_string+=String(sht31_temp)+",";
  } else {
    #ifdef LOG_SERIAL
    Serial.println("Error reading SHT31 temperature!");
    #endif
    sd_data_string+=",";
  }

  if (! isnan(sht31_hr)) {  // check if 'is not a number'
    #ifdef LOG_SERIAL
    Serial.print("SHT31 RH: ");
    Serial.print(sht31_hr);
    Serial.println("%");
    #endif
    sd_data_string+=String(sht31_hr)+",";
  } else {
    #ifdef LOG_SERIAL
    Serial.println("Error reading SHT31 humidity!");
    #endif
    sd_data_string+=",";
  }

  float sht75_temp, sht75_hr, sht75_dewpoint;
  sht75.measure(&sht75_temp, &sht75_hr, &sht75_dewpoint);

  if (! isnan(sht75_temp)) {  // check if 'is not a number'
    #ifdef LOG_SERIAL
    Serial.print("SHT75 Temp: ");
    Serial.print(sht75_temp);
    Serial.println(" *C");
    #endif
    sd_data_string+=String(sht75_temp)+",";
  } else {
    #ifdef LOG_SERIAL
    Serial.println("Error reading SHT75 temperature!");
    #endif
    sd_data_string+=",";
  }

  if (! isnan(sht75_hr)) {  // check if 'is not a number'
    #ifdef LOG_SERIAL
    Serial.print("SHT75 RH: ");
    Serial.print(sht75_hr);
    Serial.println("%");
    #endif
    sd_data_string+=String(sht75_hr)+",";
  } else {
    #ifdef LOG_SERIAL
    Serial.println("Error reading SHT75 humidity!");
    #endif
    sd_data_string+=",";
  }
  if (! isnan(sht75_dewpoint)) {  // check if 'is not a number'
    #ifdef LOG_SERIAL
    Serial.print("SHT75 Dewpoint: ");
    Serial.print(sht75_dewpoint);
    Serial.println("C");
    #endif
  } else {
    #ifdef LOG_SERIAL
    Serial.println("Error reading SHT75 humidity!");
    #endif
  }
  #ifdef LOG_SERIAL
  Serial.println("------------------------------------");
  Serial.println("----------------TEMP----------------");
  Serial.println("------------------------------------");
  #endif
  float mlx_t_amb = mlx.readAmbientTempC();
  float mlx_t_obj = mlx.readObjectTempC();

  if (! isnan(mlx_t_amb)) {  // check if 'is not a number'
    #ifdef LOG_SERIAL
    Serial.print("MLX90614 Ambient Temp: ");
    Serial.print(mlx_t_amb);
    Serial.println(" *C");
    Serial.print("MLX90614 Object Temp: ");
    Serial.print(mlx_t_obj);
    Serial.println(" *C");
    #endif
    sd_data_string+=String(mlx_t_amb)+",";
    sd_data_string+=String(mlx_t_obj);
  } else {
    #ifdef LOG_SERIAL
    Serial.println("Error reading MLX90614 temperature!");
    #endif
    sd_data_string+=",";
  }
  // Log to SD card
  if(sd_present)
  {
    log_file = SD.open(log_file_name, FILE_WRITE);
    if (log_file) {
      log_file.println(sd_data_string);
      log_file.close();
      // print to the serial port too:
      #ifdef LOG_SERIAL
      Serial.println("Logged data: "+sd_data_string);
      #endif
    }
    // if the file isn't open, pop up an error:
    else {
      #ifdef LOG_SERIAL
      Serial.println("error opening "+log_file_name);
      #endif
    }
  }
  // Delay between measurements.
  delay(delayMS);
}
