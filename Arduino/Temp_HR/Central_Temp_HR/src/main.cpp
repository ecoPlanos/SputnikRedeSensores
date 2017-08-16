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
#include "../../../SputnikConfig.h"
#include "SputnikComm.h"
#include "SputnikTempRH.h"
#include "SputnikTemp.h"
////////////////////

uint32_t millis_start, millis_end, setup_time, acquisition_time;
uint32_t delayMs;
uint8_t thr_led_state;

uint8_t i = 0;

uint8_t sd_present, log_file_opened, config_file_opened, report_file_opened;
String log_file_name, report_file_name;

void sd_card_init(void);
void sensors_awake(void);
void sensors_sleep(void);

Sd2Card card;
SdVolume volume;
SdFile root;
File log_file, config_file, report_file;

DS1302 rtc(52, 50, 48);
Time t;

void setup() {
  millis_start = millis();
  Wire.begin();
  Wire1.begin();
  SPI.begin();
  Serial.begin(115200);
  Serial1.begin(115200);  // Start ESP wifi communication interface
  #ifdef REMOTE_ACTIVE
  Serial2.begin(115200);  // Start communication interface with remote sensors
  #endif
  #ifdef SERIAL_DEBUG
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
  sd_present=false;
  #ifdef LOG_SD
  sd_card_init();
  #endif
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
      report_file_opened=true;
    }
    else
    {
      #ifdef SERIAL_DEBUG
      Serial.println("Error: can't open system log file!!!");
      #endif
      report_file_opened=false;
    }
  }
  // Read configuration from SD card
  if(sd_present)
  {
    config_file = SD.open(config_file_name, FILE_READ);
    if (config_file) {
      #ifdef SERIAL_DEBUG
      Serial.println("Config file successfuly open");
      #endif
      String delayMSstr = "";
      while (config_file.available()) {
        delayMSstr+=config_file.read();
      }
      #ifdef SERIAL_DEBUG
      Serial.print("Config file content string: ");
      Serial.println(delayMSstr);
      #endif
      // delayMs = delayMSstr.toInt();
      // Serial.println(delayMSstr);
      //  Set delay between sensor readings based on sensor details.
      config_file_opened=true;
    }
    else
    {
      #ifdef SERIAL_DEBUG
      Serial.println("Error: can't open configuration file!!!");
      #endif
      config_file_opened=false;
    }
  }
  // delayMs = (SENSORS_READ_INTERVAL > delayMs) ? SENSORS_READ_INTERVAL : delayMs;
  delayMs = (uint32_t)SENSORS_READ_INTERVAL;
  #ifdef SERIAL_DEBUG
    Serial.print("Logging interval: ");
    Serial.println(delayMs);
  #endif

  if(sd_present)
  {
    report_file = SD.open(report_file_name, FILE_WRITE);
    if (report_file) {
      report_file.print("Logging interval: ");
      report_file.println(delayMs);
      report_file.close();
      report_file_opened=true;
    }
    else
    {
      #ifdef SERIAL_DEBUG
      Serial.println("Error: can't open system log file!!!");
      #endif
      report_file_opened=false;
    }
  }
  delay(INITIAL_DELAY);
  // Initialize temperature and RH sensors.
  temp_hr_init();
  //  Initialize temperature sensors
  temp_init();
  millis_end = millis();
  #ifdef SERIAL_DEBUG
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
  #ifdef SERIAL_DEBUG
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
  #ifdef REMOTE_ACTIVE
  Serial2.write(REMOTE_START);  // Prompt remote sensors for data
  #endif
  Serial2.write('\r');
  Serial2.write('\n');  // Prompt remote sensors for data
  String sd_data_string = "";
  String sd_data_string_tmp = "";

  sensors_awake();
  #ifdef LOG_SD
  if(!sd_present)
    sd_card_init();
  #endif
  sd_data_string+=String(millis_start)+",";
  #ifdef SERIAL_DEBUG
  Serial.println("------------------------------------");
  Serial.println("----------------T&RH----------------");
  Serial.println("------------------------------------");
  #endif

  if (isnan(dht11.readTemperature(false,true))) {
    dht11_error = 1;
    #ifdef SERIAL_DEBUG
    Serial.println("Error reading DHT11 temperature!");
    #endif
    sd_data_string+=",";
  }
  else {
    #ifdef SERIAL_DEBUG
    Serial.print("DHT11 Temp: ");
    Serial.print(dht11.getTemperature());
    Serial.println(" *C");
    #endif
    sd_data_string+=String(dht11.getTemperature())+",";
  }
  // Get humidity event and print its value.
  if (isnan(dht11.readHumidity(true))) {
    dht11_error = 1;
    #ifdef SERIAL_DEBUG
    Serial.println("Error reading DHT11 humidity!");
    #endif
    sd_data_string+=",";
  }
  else {
    #ifdef SERIAL_DEBUG
    Serial.print("DHT11 RH: ");
    Serial.print(dht11.getHumidity());
    Serial.println("%");
    #endif
    sd_data_string+=String(dht11.getHumidity())+",";
  }

  if (isnan(dht22.readTemperature(false,true))) {
    dht22_error = 1;
    #ifdef SERIAL_DEBUG
    Serial.println("Error reading DHT22 temperature!");
    #endif
    sd_data_string+=",";
  }
  else {
    #ifdef SERIAL_DEBUG
    Serial.print("DHT22 Temp: ");
    Serial.print(dht22.getTemperature());
    Serial.println(" *C");
    #endif
    sd_data_string+=String(dht22.getTemperature())+",";
  }
  // Get humidity event and print its value.
  if (isnan(dht22.readHumidity(true))) {
    dht22_error = 1;
    #ifdef SERIAL_DEBUG
    Serial.println("Error reading DHT22 humidity!");
    #endif
    sd_data_string+=",";
  }
  else {
    #ifdef SERIAL_DEBUG
    Serial.print("DHT22 RH: ");
    Serial.print(dht22.getHumidity());
    Serial.println("%");
    #endif
    sd_data_string+=String(dht22.getHumidity())+",";
  }

  float sht75_temp, sht75_hr, sht75_dewpoint;
  sht75.measure(&sht75_temp, &sht75_hr, &sht75_dewpoint);

  if(!isnan(sht75_hr)&&((sht75_hr!=0.0)&&(sht75_temp!=0.0)))
  {
    #ifdef SERIAL_DEBUG
    Serial.print("SHT75 Temp: ");
    Serial.print(sht75_temp);
    Serial.println(" *C");
    Serial.print("SHT75 RH: ");
    Serial.print(sht75_hr);
    Serial.println("%");
    #endif
    sd_data_string+=String(sht75_hr)+",";
    sd_data_string+=String(sht75_temp)+",";
    sd_data_string+=String(sht75_dewpoint)+",";
  }
  else
  {
    #ifdef SERIAL_DEBUG
    Serial.println("Error reading SHT75 data!");
    #endif
    sd_data_string+=",";
    sht75_error = 1;
  }

  if (! isnan(sht75_dewpoint)) {  // check if 'is not a number'
    #ifdef SERIAL_DEBUG
    Serial.print("SHT75 Dewpoint: ");
    Serial.print(sht75_dewpoint);
    Serial.println("C");
    #endif
  } else {
    #ifdef SERIAL_DEBUG
    Serial.println("Error reading SHT75 humidity!");
    #endif
  }
  #ifdef SERIAL_DEBUG
  Serial.println("------------------------------------");
  Serial.println("----------------TEMP----------------");
  Serial.println("------------------------------------");
  #endif
  //
  // thermopar.readCJT();
  // if (!isnan(thermopar.temperature_cjt)) {
  //   #ifdef SERIAL_DEBUG
  //   Serial.print("Thermopar CJT temp: ");
  //   Serial.print(thermopar.temperature_cjt);
  //   Serial.println(" *C");
  //   #endif
  // }
  // else
  // {
  //   sd_data_string+=",";
  // }

  pt100_temp=analogRead(PT100_PIN);
  #ifdef SERIAL_DEBUG
  Serial.print("PT100 Temp: ");
  Serial.print(pt100_temp);
  Serial.println(" Analog value");
  #endif
  sd_data_string+=String(pt100_temp)+",";

  ntc_temp=analogRead(NTC_PIN);
  #ifdef SERIAL_DEBUG
  Serial.print("NTC Temp: ");
  Serial.print(ntc_temp);
  Serial.println(" Analog value");
  #endif
  sd_data_string+=String(ntc_temp)+",";
  #ifdef REMOTE_ACTIVE
  #ifdef SERIAL_DEBUG
  Serial.println("------------------------------------");
  Serial.println("---------------REMOTE---------------");
  Serial.println("------------------------------------");
  #endif
  uint32_t temp_millis = millis();
  uint32_t temp_delay;
  if(temp_millis > millis_start)
  {
    temp_delay = temp_millis-millis_start;
  }
  else
  {
    temp_delay = 0XFFFFFFFF-millis_start+temp_millis;
  }

  //Wait for data on serial bus
  while((Serial2.available()<=0)&&(temp_delay<(delayMs-1000)))
  {
    temp_millis = millis();
    if(temp_millis > millis_start)
    {
      temp_delay = temp_millis-millis_start;
    }
    else
    {
      temp_delay = 0XFFFFFFFF-millis_start+temp_millis;
    }
  }

  if(Serial2.available()>0)
  {
    while(Serial2.available()>0)
    {
      serial_char = Serial2.read();
      if((char)serial_char == (char)REMOTE_START)
      {
        i++;
      }
      else if((char)serial_char != (char)REMOTE_END)
      {
        if(i>0)
        {
          sd_data_string_tmp+=String(serial_char);
        }
        else
        {
          #ifdef SERIAL_DEBUG
          Serial.print("Warning, received wrong start! ");
          Serial.println(String(serial_char));
          #endif
          Serial2.flush();
        }
      }
      else
      {
        if(i>0)
        {
          #ifdef SERIAL_DEBUG
          Serial.print("Message received from remote base: ");
          Serial.println(sd_data_string_tmp);
          #endif
        }
        else
        {
          #ifdef SERIAL_DEBUG
          Serial.println("Error, received termination character out of order.");
          #endif
          Serial2.flush();
          i=0;
        }
      }
    }
  }
  else
  {
    if(i==0)
    {
      #ifdef SERIAL_DEBUG
      Serial.println("Warning: Timeout wainting for remote sensors!");
      #endif
      sd_data_string+=",,,,";
    }
    else
    {
      sd_data_string += sd_data_string_tmp;
      #ifdef SERIAL_DEBUG
      Serial.print("Final data string: ");
      Serial.println(sd_data_string);
      #endif
      i=0;
    }
  }
  #endif
  #ifdef LOG_SD
  // Log to SD card
  if(sd_present)
  {
    log_file = SD.open(log_file_name, FILE_WRITE);
    if (log_file) {
      log_file.println(sd_data_string);
      log_file.close();
      // print to the serial port too:
      #ifdef SERIAL_DEBUG
      Serial.println("Logged data: "+sd_data_string);
      #endif
    }
    // if the file isn't open, pop up an error:
    else {
      #ifdef SERIAL_DEBUG
      Serial.println("error opening "+log_file_name);
      #endif
    }
  }
  #endif
  #ifdef SERIAL_DEBUG
  Serial.print("Checking sensors for errors: ");
  Serial.println(String(dht11_error)+","+String(dht22_error)+","+String(sht31_error)+","+String(sht75_error)+","+String(mlx_error));
  #endif
  #ifdef LOG_SD
  //TODO: log sensor errors to SD card.
  #endif
  temp_sensors_check();
  temp_hr_sensors_check();
  sensors_sleep();
  thr_led_state = ~thr_led_state;
  digitalWrite(THR_LED,thr_led_state);
  millis_end = millis();
  #ifdef SERIAL_DEBUG
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
  #ifdef SERIAL_DEBUG
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
  if(acquisition_time >= delayMs)
  {
    // delayMs = ((uint8_t)(acquisition_time/1000))*1000+1000;
    delayMs = acquisition_time;
    #ifdef SERIAL_DEBUG
    Serial.print("Warning: Acquisition time forced to ");
    Serial.print(delayMs);
    Serial.println(" ms");
    #endif
    if(sd_present)
    {
      report_file = SD.open(report_file_name, FILE_WRITE);
      if (report_file) {
        report_file.print("Forced Logging interval: ");
        report_file.println(delayMs);
        report_file.close();
      }
      else
      {
        #ifdef SERIAL_DEBUG
        Serial.println("Error: can't open system log file!!!");
        #endif
      }
    }
  }
  // Delay between measurements.
  delay(delayMs-acquisition_time);
}

void sd_card_init(void)
{
  uint8_t sd_card_failures = 0;
  while(sd_card_failures < SD_MAX_TRIES)
  {
    sd_card_failures++;
    if (!SD.begin(SD_CHIP_SEL))
     {
       #ifdef SERIAL_DEBUG
       Serial.print("Card failed, or not present -> try ");
       Serial.println(sd_card_failures);
       #endif
       sd_present=false;
       delay(500);
     }
     else
     {
       #ifdef SERIAL_DEBUG
       Serial.println("SD card initialized.");
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
