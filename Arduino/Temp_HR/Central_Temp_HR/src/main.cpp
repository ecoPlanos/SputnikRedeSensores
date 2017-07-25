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
#include <DS1302.h>
// #include <ESP8266wifi.h>
// #include <WiFiClient.h>
// #include <ESP8266WebServer.h>
// #include <ESP8266FtpServer.h>
////////////////////
#include "SputnikTempRH.h"
#include "SputnikTemp.h"
////////////////////
//#include "SputinkRedeSensores.h"
#define INITIAL_DELAY 100
// #define SENSORS_READ_INTERVAL 10000 //Sensors read minimum interval (ms)
#define SENSORS_READ_INTERVAL 1000 //Sensors read minimum interval (ms)

#define SD_CHIP_SEL          4//10
#define SD2_CHIP_SEL          10

#define SD_CARD_DELAY 500
#define SD_MAX_TRIES 3

#define LOG_SD
#define LOG_SERIAL

const String log_file_sufix="Data.csv";
const String config_file_name="SPUTNIK.CFG";

const char* ssid = "SSID";
const char* password = "PASS";

uint32_t millis_start, millis_end, setup_time, acquisition_time;
uint32_t delayMS;
uint8_t thr_led_state;

uint8_t sd_present;
String log_file_name, report_file_name;

void sd_card_init(void);
void sensors_awake(void);
void sensors_sleep(void);

Sd2Card card;
SdVolume volume;
SdFile root;
File log_file, config_file, report_file, test_file;

DS1302 rtc(52, 50, 48);
Time t;

void setup() {
  millis_start = millis();

  Serial.begin(115200);
  #ifdef LOG_SERIAL
  Serial.println("-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-");
  Serial.println(".i.SputnikRedeSensores by ecoPlanos.i.");
  Serial.println("-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-");
  Serial.println();
  #endif

  pinMode(THR_LED, OUTPUT);
  thr_led_state = 0;

  // Set the clock to run-mode, and disable the write protection
  rtc.halt(false);
  rtc.writeProtect(false);
  //Adjust RTC Date And Time
  // rtc.setDOW(MONDAY);        // Set Day-of-Week to FRIDAY
  // rtc.setTime(15, 10, 00);     // Set the time to 12:00:00 (24hr format)
  // rtc.setDate(17, 07, 2017);   // Set the date to August 6th, 2010
  t = rtc.getTime();

  report_file_name ="REPORT.LOG";
  log_file_name = String(t.year)+"/"+String(t.mon)+"/"+String(t.date)+"/"+String(t.hour)+"H"+String(t.min)+"M"+String(t.sec)+".CSV";

  sd_card_init();
  delay(SD_CARD_DELAY);
  if(sd_present)
  {
    SD.mkdir(String(t.year)+"/"+String(t.mon)+"/"+String(t.date));
  }

  if(sd_present)
  {
    report_file = SD.open(report_file_name, FILE_WRITE);

    if (report_file) {
      report_file.println("-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^");
      report_file.println(">>SputnikRedeSensores by ecoPlanos<<");
      report_file.println("-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^");
      report_file.println();
      report_file.println(String(t.year)+"/"+String(t.mon)+"/"+String(t.date)+"/"+String(t.hour)+"H"+String(t.min)+"M"+String(t.sec));
      report_file.println("Starting new acquisition");
      report_file.close();
    }
    else
    {
      #ifdef LOG_SERIAL
      Serial.println("Error: can't open system log file!!!");
      #endif
    }
    test_file = SD2.open("test.txt",FILE_WRITE);
    if(test_file)
    {
      test_file.println("YEI!");
      test_file.close();
    }
    else
      Serial.print("ERROR: Can't open file test.txt!!!");
  }
  // Read configuration from SD card
  if(sd_present)
  {
    config_file = SD.open(config_file_name, FILE_READ);
    if (config_file) {
      #ifdef LOG_SERIAL
      Serial.println("Config file successfuly open");
      #endif
      String delayMSstr = "";
      while (config_file.available()) {
        delayMSstr+=config_file.read();
      }
      // delayMS = delayMSstr.toInt();
      // Serial.println(delayMSstr);
      //  Set delay between sensor readings based on sensor details.
    }
    else
    {
      #ifdef LOG_SERIAL
      Serial.println("Error: can't open configuration file!!!");
      #endif
    }
  }
  // delayMS = (SENSORS_READ_INTERVAL > delayMS) ? SENSORS_READ_INTERVAL : delayMS;
  delayMS = SENSORS_READ_INTERVAL;
  #ifdef LOG_SERIAL
    Serial.print("Logging interval: ");
    Serial.println(delayMS);
  #endif
  if(sd_present)
  {
    report_file = SD.open(report_file_name, FILE_WRITE);
    if (report_file) {
      report_file.print("Logging interval: ");
      report_file.println(delayMS);
      report_file.close();
    }
    else
    {
      #ifdef LOG_SERIAL
      Serial.println("Error: can't open system log file!!!");
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
  millis_end = millis();
  #ifdef LOG_SERIAL
  Serial.print("millis_start: ");
  Serial.println(millis_start);
  Serial.print("millis_end: ");
  Serial.println(millis_end);
  #endif
  if(millis_end > millis_start)
  {
    setup_time = millis_end-millis_start;
  }
  else
  {
    setup_time = 0XFFFFFFFF-millis_start+millis_end;
  }
  #ifdef LOG_SERIAL
  Serial.print("Setup time: ");
  if(setup_time >= 60000)
  {
    Serial.print((uint8_t) (setup_time/60000));
    Serial.println("m");
  }
  else if(setup_time >= 1000)
  {
    Serial.print((uint8_t) (setup_time/1000));
    Serial.println("s");
  }
  else
  {
    Serial.print(setup_time);
    Serial.println("ms");
  }
  #endif
}

void loop() {
  millis_start = millis();
  String sd_data_string = "";

  sensors_awake();
  #ifdef LOG_SD
  if(!sd_present)
    sd_card_init();
  #endif
  sd_data_string+=String(millis_start)+",";
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
  thermopar.readCJT();
  if (!isnan(thermopar.temperature_cjt)) {
    #ifdef LOG_SERIAL
    Serial.print("Thermopar CJT temp: ");
    Serial.print(thermopar.temperature_cjt);
    Serial.println(" *C");
    #endif
  }
  else
  {
    sd_data_string+=",";
  }
  thermopar.readTempC();
  if (!isnan(thermopar.temperature_c)) {
    #ifdef LOG_SERIAL
    Serial.print("Thermopar temp: ");
    Serial.print(thermopar.temperature_c);
    Serial.println(" *C");
    #endif
  }
  else
  {
    sd_data_string+=",";
  }
  sd_data_string+=String(thermopar.temperature_cjt)+","+String(thermopar.temperature_raw)+",";

  ntc_temp=analogRead(NTC_PIN);
  #ifdef LOG_SERIAL
  Serial.print("NTC Temp: ");
  Serial.print(ntc_temp);
  Serial.println(" Analog value");
  #endif
  sd_data_string+=String(ntc_temp)+",";

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
  thr_led_state = ~thr_led_state;
  digitalWrite(THR_LED,thr_led_state);
  millis_end = millis();
  #ifdef LOG_SERIAL
  Serial.print("millis_start: ");
  Serial.println(millis_start);
  Serial.print("millis_end: ");
  Serial.println(millis_end);
  #endif
  if(millis_end > millis_start)
 {
   acquisition_time = millis_end-millis_start;
 }
 else
 {
   acquisition_time = 0XFFFFFFFF-millis_start+millis_end;
 }
  #ifdef LOG_SERIAL
  Serial.print("Acquisition time: ");
  if(acquisition_time >= 60000)
  {
    Serial.print((uint8_t) (acquisition_time/60000));
    Serial.println("m");
  }
  else if(acquisition_time >= 1000)
  {
    Serial.print((uint8_t) (acquisition_time/1000));
    Serial.println("s");
  }
  else
  {
    Serial.print(acquisition_time);
    Serial.println("ms");
  }
  #endif
  if(acquisition_time >= delayMS)
  {
    delayMS = ((uint8_t)(acquisition_time/1000))*1000+1000;
    #ifdef LOG_SERIAL
    Serial.print("Warning: Acquisition time forced to ");
    Serial.print(delayMS);
    Serial.println(" ms");
    #endif
    if(sd_present)
    {
      report_file = SD.open(report_file_name, FILE_WRITE);
      if (report_file) {
        report_file.print("Forced Logging interval: ");
        report_file.println(delayMS);
        report_file.close();
      }
      else
      {
        #ifdef LOG_SERIAL
        Serial.println("Error: can't open system log file!!!");
        #endif
      }
    }
  }
  delay(delayMS-acquisition_time);
}

void sd_card_init(void)
{
  //SD2.begin(SD2_CHIP_SEL);
  uint8_t sd_card_failures = 0;
  while(sd_card_failures < SD_MAX_TRIES)
  {
    sd_card_failures++;
    if (!SD.begin(SD_CHIP_SEL))
     {
       #ifdef LOG_SERIAL
       Serial.print("Card failed, or not present -> try ");
       Serial.println(sd_card_failures);
       #endif
       sd_present=false;
       delay(500);
     }
     else
     {
       #ifdef LOG_SERIAL
       Serial.println("SD card initialized.");
       #endif
       sd_present=true;
       break;
     }
  }
  sd_card_failures = 0;
  while(sd_card_failures < SD_MAX_TRIES)
  {
    sd_card_failures++;
    if (!SD2.begin(SD2_CHIP_SEL))
     {
       #ifdef LOG_SERIAL
       Serial.print("Card 2 failed, or not present -> try ");
       Serial.println(sd_card_failures);
       #endif
       sd_present=false;
       delay(500);
     }
     else
     {
       #ifdef LOG_SERIAL
       Serial.println("SD card 2 initialized.");
       #endif
       sd_present=true;
       break;
     }
  }
}

void sensors_awake(void){
}
void sensors_sleep(void){
}
