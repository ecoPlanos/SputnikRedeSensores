// Copyright (c) 2017 by ecoPlanos. All Rights Reserved.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// #include <Wire.h>
////////////////////
#include <SPI.h>
#include <SD.h>
#include <ESP8266wifi.h>
// #include <WiFiClient.h>
// #include <ESP8266WebServer.h>
// #include <ESP8266FtpServer.h>
////////////////////
#include "SputnikTempRH.h"
#include "SputnikTemp.h"
#include "SputnikGas.h"
////////////////////
//#include "SputinkRedeSensores.h"
#define INITIAL_DELAY 100
// #define SENSORS_READ_INTERVAL 10000 //Sensors read minimum interval (ms)
#define SENSORS_READ_INTERVAL 1000 //Sensors read minimum interval (ms)

#define SD_CHIP_SEL          4//10

#define LOG_SD
#define LOG_SERIAL

const String log_file_name="datalog.csv";
const String config_file_name="Sputnik.conf";

const char* ssid = "SSID";
const char* password = "PASS";
// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

uint32_t sys_time, sys_time_last, setup_time, acquisition_time;
uint32_t delayMS;

uint8_t sd_present=false;

void sd_card_init(void);
void sensors_awake(void);
void sensors_sleep(void);

Sd2Card card;
SdVolume volume;
SdFile root;
File log_file, config_file;

void setup() {
  sys_time = millis();
  sys_time_last = sys_time;
  #ifdef LOG_SERIAL
  Serial.begin(115200);
  Serial.println("-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-");
  Serial.println(".i.SputnikRedeSensores by ecoPlanos.i.");
  Serial.println("-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-");
  Serial.println();
  #endif

  sd_card_init();
  // Read configuration from SD card
  if(sd_present)
  {
    config_file = SD.open(config_file_name, FILE_READ);
    if (config_file) {
      #ifdef LOG_SERIAL
      Serial.println("Config file successfuly open");
      #endif
      Serial.write(config_file.read());
      //  Set delay between sensor readings based on sensor details.
      delayMS = (SENSORS_READ_INTERVAL > delayMS) ? SENSORS_READ_INTERVAL : delayMS;
    }
    else
    {
      #ifdef LOG_SERIAL
      Serial.println("Error: can't open configuration file!!!");
      #endif
    }
  }
  delay(INITIAL_DELAY);
  // Initialize DHTs.
  temp_hr_init();
  //  Initialize SHT31
  if (! sht31.begin(0x44)) {   // Set to 0x45 for alternate i2c addr
    #ifdef LOG_SERIAL
    Serial.println("Couldn't find SHT31");
    #endif
  }
  //  Initialize Temperature Sensors
  temp_init();

  sputnikGasInit();

  sys_time = micros();
  setup_time = sys_time-sys_time_last;
  sys_time_last = sys_time;
}

void loop() {
  sys_time = micros();
  acquisition_time = sys_time-sys_time_last;
  sys_time_last = sys_time;
  String sd_data_string = "";

  sensors_awake();
  #ifdef LOG_SD
  if(!sd_present)
    sd_card_init();
  #endif

  #ifdef LOG_SERIAL
  Serial.println("------------------------------------");
  Serial.println("----------------T&RH----------------");
  Serial.println("------------------------------------");
  #endif

  if (isnan(dht11.readTemperature(false,true))) {
    #ifdef LOG_SERIAL
    Serial.println("Error reading DHT11 temperature!");
    #endif
    sd_data_string+=",";
  }
  else {
    #ifdef LOG_SERIAL
    Serial.print("DHT11 Temp: ");
    Serial.print(dht11.getTemperature());
    Serial.println(" *C");
    #endif
    sd_data_string+=String(dht11.getTemperature())+",";
  }
  // Get humidity event and print its value.
  if (isnan(dht11.readHumidity(true))) {
    #ifdef LOG_SERIAL
    Serial.println("Error reading DHT11 humidity!");
    #endif
    sd_data_string+=",";
  }
  else {
    #ifdef LOG_SERIAL
    Serial.print("DHT11 RH: ");
    Serial.print(dht11.getHumidity());
    Serial.println("%");
    #endif
    sd_data_string+=String(dht11.getHumidity())+",";
  }

  if (isnan(dht22.readTemperature(false,true))) {
    #ifdef LOG_SERIAL
    Serial.println("Error reading DHT22 temperature!");
    #endif
    sd_data_string+=",";
  }
  else {
    #ifdef LOG_SERIAL
    Serial.print("DHT22 Temp: ");
    Serial.print(dht11.getTemperature());
    Serial.println(" *C");
    #endif
    sd_data_string+=String(dht22.getTemperature())+",";
  }
  // Get humidity event and print its value.
  if (isnan(dht22.readHumidity(true))) {
    #ifdef LOG_SERIAL
    Serial.println("Error reading DHT22 humidity!");
    #endif
    sd_data_string+=",";
  }
  else {
    #ifdef LOG_SERIAL
    Serial.print("DHT22 RH: ");
    Serial.print(dht22.getHumidity());
    Serial.println("%");
    #endif
    sd_data_string+=String(dht11.getHumidity())+",";
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
    sd_data_string+=String(mlx_t_obj)+",";
  } else {
    #ifdef LOG_SERIAL
    Serial.println("Error reading MLX90614 temperature!");
    #endif
    sd_data_string+=",,";
  }
  #ifdef LOG_SERIAL
  Serial.println("------------------------------------");
  Serial.println("----------------GAS-----------------");
  Serial.println("------------------------------------");
  #endif
  mg811_analog=analogRead(MG811_PIN);
  #ifdef LOG_SERIAL
  Serial.print("MG811 Analogic: ");
  Serial.println(mg811_analog);
  #endif
  sd_data_string+=String(mg811_analog)+",";
  mq135_analog=analogRead(MQ135_PIN);
  #ifdef LOG_SERIAL
  Serial.print("MQ135 Analogic: ");
  Serial.println(mq135_analog);
  #endif
  sd_data_string+=String(mq135_analog)+",";

  if(ccs811.dataAvailable())
  {
    ccs811.readAlgorithmResults();
    #ifdef LOG_SERIAL
    Serial.print("CCS188 CO2: ");
    Serial.println(ccs811.getCO2());
    Serial.print("CCS188 TVOC: ");
    Serial.println(ccs811.getTVOC());
    #endif
    sd_data_string+=String(ccs811.getCO2())+","+String(ccs811.getTVOC())+",";
  }
  else
  {
    #ifdef LOG_SERIAL
    Serial.println("ERROR: CCS188 didn't respond!");
    #endif
    sd_data_string+=",,";
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
      sd_card_init();
    }
  }
  // Delay between measurements.
  sensors_sleep();
  delay(delayMS);
}

void sd_card_init(void)
{
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
}

void sensors_awake(void){
  digitalWrite(CCS811_NWAK, LOW);
}
void sensors_sleep(void){
  digitalWrite(CCS811_NWAK, HIGH);
}
