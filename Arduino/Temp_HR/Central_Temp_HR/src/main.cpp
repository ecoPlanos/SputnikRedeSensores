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

////////////////////
#include <SPI.h>
#include <SD.h>
#include <DS1302.h>
// #include <ESP8266wifi.h>
// #include <WiFiClient.h>
// #include <ESP8266WebServer.h>
// #include <ESP8266FtpServer.h>
////////////////////
#include "SputnikConfig.h"
#include "SputnikComm.h"
#include "SputnikTempRH.h"
#include "SputnikTemp.h"
////////////////////

#define  ACTIVITY_LED_PIN 8

uint32_t millis_start, millis_end, setup_time, acquisition_time;
uint32_t delayMs, delayMsRequested;

uint8_t i = 0;

uint8_t sd_present, log_file_opened, config_file_opened, report_file_opened, readme_file_opened;
String log_file_name, report_file_name, readme_file_name;

void sd_card_init(void);
void sensors_awake(void);
void sensors_sleep(void);
void sys_restart(void);
void(* reset_arduino)(void) = 0;

Sd2Card card;
SdVolume volume;
SdFile root;
File log_file, config_file, report_file, readme_file;

DS1302 rtc(52, 50, 48);
Time t_start, t;

void setup() {
  millis_start = millis();
  // analogReadResolution(12);
  SPI.begin();
  Serial.begin(115200);
  #ifdef WIFI_ACTIVE
  Serial1.begin(115200);  // Start ESP wifi communication interface
  #endif
  #ifdef REMOTE_ACTIVE
  Serial2.begin(115200);  // Start communication interface with remote sensors
  delay(100);
  Serial2.write(REMOTE_START);  // Prompt remote sensors for data
  #endif
  delayMs = (uint32_t)SENSORS_READ_MIN_INTERVAL;
  #ifdef SERIAL_DEBUG
  Serial.println("-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-");
  Serial.println(".i.SputnikRedeSensores by ecoPlanos.i.");
  Serial.println("-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-");
  Serial.println();
  #endif

  pinMode(ACTIVITY_LED_PIN, OUTPUT);

  // Set the clock to run-mode, and disable the write protection
  rtc.halt(false);
  rtc.writeProtect(false);
  //Adjust RTC Date And Time
  // rtc.setDOW(MONDAY);        // Set Day-of-Week to FRIDAY
  // rtc.setTime(19, 52, 00);     // Set the time to 12:00:00 (24hr format)
  // rtc.setDate(18, 8, 2017);   // Set the date to August 6th, 2010
  t_start = rtc.getTime();
  #ifdef SERIAL_DEBUG
  Serial.println("RTC date and time: "+String(t_start.year)+"/"+String(t_start.mon)+"/"+String(t_start.date)+"/"+String(t_start.hour)+"H"+String(t_start.min)+"M"+String(t_start.sec)+"S");
  #endif
  report_file_name ="REPORT.LOG";
  log_file_name = String(t_start.year)+"/"+String(t_start.mon)+"/"+String(t_start.date)+"/"+String(t_start.hour)+String(t_start.min)+String(t_start.sec)+".CSV";
  sd_present=false;
  #ifdef LOG_SD
  #ifdef SERIAL_DEBUG
  Serial.println("Log file will be saved to: "+log_file_name);
  #endif
  sd_card_init();
  #endif
  delay(SD_CARD_DELAY);

  #ifdef LOG_SD
  if(sd_present)
  {
    SD.mkdir(String(t_start.year)+"/"+String(t_start.mon)+"/"+String(t_start.date));
  }
  #endif

  if(sd_present)
  {
    report_file = SD.open(report_file_name, FILE_WRITE);

    if (report_file) {
      report_file.println(String(t_start.year)+"/"+String(t_start.mon)+"/"+String(t_start.date)+"/"+String(t_start.hour)+"H"+String(t_start.min)+"M"+String(t_start.sec)+"S");
      report_file.println("Starting new acquisition");
      report_file.close();
      report_file_opened=true;
      #ifdef SERIAL_DEBUG
      Serial.println("Report file successfuly opened");
      #endif
    }
    else
    {
      #ifdef SERIAL_DEBUG
      Serial.println("Error: can't open system log file!!!");
      #endif
      report_file_opened=false;
    }
  }

  readme_file_name ="README.TXT";
  if(sd_present)
  {
    readme_file = SD.open(readme_file_name, FILE_READ);
    if (!readme_file) {
      readme_file = SD.open(readme_file_name, FILE_WRITE);
      if (readme_file) {
        readme_file.println("Sensors data on the SD card is saved in a file structure as follows: YYYY/MM/DD/hhmmss.CSV");
        readme_file.println("Each sensor information is separated by \",\" respecting the folowing order:");
        readme_file.println("year,month,day,time,DHT11 temp (C),DHT11 RH (%),DHT22 temp (C),DHT22 RH (%),SHT75 temp (C),SHT75 RH (%),SHT75 dewp (C),PT100 (Ohm),NTC (Ohm),SHT31 temp (C),SHT31 RH (%),MLX ambient temp (C),MLX object temp (C),Thermopar temp (RAW) ");
        readme_file.println();
        readme_file.println("To configure the accquisition time, write a file called \"SPUTNIK.CFG\" at the root directory of the SD card and write a line with the time between measurements in milliseconds.");
        readme_file.close();
        readme_file_opened=true;
      }
      else
      {
        #ifdef SERIAL_DEBUG
        Serial.println("Error: can't open system log file!!!");
        #endif
        readme_file_opened=false;
      }
    }
  }
  // Read configuration from SD card
  if(sd_present)
  {
    #ifdef LOG_SD
    log_file = SD.open(log_file_name, FILE_WRITE);
    if (log_file) {
        log_file.println("year,month,day,time,DHT11 temp (C),DHT11 RH (%),DHT22 temp (C),DHT22 RH (%),SHT75 temp (C),SHT75 RH (%),SHT75 dewp (C),PT100 (Ohm),NTC (Ohm),SHT31 temp (C),SHT31 RH (%),MLX ambient temp (C),MLX object temp (C),Thermopar temp (RAW) ");
        log_file.close();
    }
    else
    {
        #ifdef SERIAL_DEBUG
        Serial.println("Error: Opening file "+log_file_name+" for writing");
        #endif
    }
    #endif
    config_file = SD.open(config_file_name, FILE_READ);
    if (config_file)
    {
      #ifdef SERIAL_DEBUG
      Serial.println("Config file successfuly open");
      #endif
      String delayMSstr = "";
      delayMSstr=config_file.readString();
      #ifdef SERIAL_DEBUG
      Serial.print("Config file content string: ");
      Serial.println(delayMSstr);
      #endif
      if((((uint32_t)delayMSstr.toInt())>=((uint32_t)SENSORS_READ_MIN_INTERVAL))
      && (((uint32_t)delayMSstr.toInt())<=((uint32_t)SENSORS_READ_MAX_INTERVAL)))
      {
        delayMsRequested = delayMSstr.toInt();
        delayMs = delayMsRequested;
        #ifdef SERIAL_DEBUG
        Serial.print("Valid delay found at SD card: ");
        Serial.print(delayMs);
        Serial.println("ms");
        #endif
      }
      else
      {
       delayMsRequested = (uint32_t)SENSORS_READ_MIN_INTERVAL;
       delayMs = delayMsRequested;
       #ifdef SERIAL_DEBUG
       Serial.print("Waring: Invalid delay found at SD card: ");
       Serial.print(delayMSstr);
       Serial.println("ms");
       #endif
      }
      config_file_opened=true;
      config_file.close();
    }
    else
    {
      config_file = SD.open(config_file_name, FILE_WRITE);
      if (config_file)
      {
        config_file.print((uint16_t)SENSORS_READ_MIN_INTERVAL);
        config_file.close();
      }
      else
      {
        #ifdef SERIAL_DEBUG
        Serial.println("Error creating config file!");
        #endif
      }
      #ifdef SERIAL_DEBUG
      Serial.println("Error: can't open configuration file!!!");
      #endif
      config_file_opened=false;
    }
  }
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
      report_file.close();
    }
  }
  delay(INITIAL_DELAY);
  // Initialize temperature and RH sensors.
  temp_hr_init();
  // Initialize temperature sensors
  temp_init();
  millis_end = millis();
  #ifdef SERIAL_DEBUG
  Serial.print("millis_start: ");
  Serial.println(millis_start);
  Serial.print("millis_end: ");
  Serial.println(millis_end);
  #endif
  if(millis_end >= millis_start)
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
  serial_error = 0;
}

void loop() {
  millis_start = millis();
  t = rtc.getTime();
  #ifdef SERIAL_DEBUG
  Serial.println("RTC date and time: "+String(t.year)+"/"+String(t.mon)+"/"+String(t.date)+"/"+String(t.hour)+"H"+String(t.min)+"M"+String(t.sec)+"S");
  #endif
  if(t.date > t_start.date)
  {
      t_start = t;
      log_file_name = String(t.year)+"/"+String(t.mon)+"/"+String(t.date)+"/"+String(t.hour)+String(t.min)+String(t.sec)+".CSV";
      if(sd_present)
      {
          #ifdef LOG_SD
          SD.mkdir(String(t.year)+"/"+String(t.mon)+"/"+String(t.date));
          log_file = SD.open(log_file_name, FILE_WRITE);
          if (log_file) {
              log_file.println("year,month,day,time,DHT11 temp (C),DHT11 RH (%),DHT22 temp (C),DHT22 RH (%),SHT75 temp (C),SHT75 RH (%),SHT75 dewp (C),PT100 (Ohm),NTC (Ohm),SHT31 temp (C),SHT31 RH (%),MLX ambient temp (C),MLX object temp (C),Thermopar temp (RAW) ");
              log_file.close();
          }
          else
          {
              #ifdef SERIAL_DEBUG
              Serial.println("Error: Opening file "+log_file_name+" for writing");
              #endif
          }
          #endif
        report_file = SD.open(report_file_name, FILE_WRITE);

        if (report_file) {
          report_file.println(String(t_start.year)+"/"+String(t_start.mon)+"/"+String(t_start.date)+"/"+String(t_start.hour)+"H"+String(t_start.min)+"M"+String(t_start.sec)+"S");
          report_file.println("Starting new acquisition");
          report_file.close();
          report_file_opened=true;
          #ifdef SERIAL_DEBUG
          Serial.println("Report file successfuly opened");
          #endif
        }
        else
        {
          #ifdef SERIAL_DEBUG
          Serial.println("Error: can't open system log file!!!");
          #endif
          report_file_opened=false;
        }
      }
    //   sys_restart();
  }

  digitalWrite(ACTIVITY_LED_PIN,1);

  #ifdef REMOTE_ACTIVE
  Serial2.write(REMOTE_START);  // Prompt remote sensors for data
  #endif
  String sd_data_string = "";
  String sd_data_string_tmp = "";

  sensors_awake();
  #ifdef LOG_SD
  if(!sd_present)
    sd_card_init();
  #endif
  sd_data_string+=String(String(t.year)+","+String(t.mon)+","+String(t.date)+","+String(t.hour)+":"+String(t.min)+":"+String(t.sec))+",";
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
    sd_data_string+=String(sht75_temp)+",";
    sd_data_string+=String(sht75_hr)+",";
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

  pt100_analog=analogRead(PT100_PIN);
  #ifdef SERIAL_DEBUG
  Serial.print("PT100 Analog: ");
  Serial.print(pt100_analog);
  Serial.println(" Analog value");
  Serial.print("PT100 Resistance: ");
  Serial.print(pt100_resistance());
  Serial.println(" Ohm");
  #endif
  sd_data_string+=String(pt100_resistance())+",";

  ntc_analog=analogRead(NTC_PIN);
  #ifdef SERIAL_DEBUG
  Serial.print("NTC Analog: ");
  Serial.print(ntc_analog);
  Serial.println(" Analog value");
  Serial.print("NTC Resistance: ");
  Serial.print(ntc_resistance());
  Serial.println(" Ohm");
  #endif
  sd_data_string+=String(ntc_resistance())+",";
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

  // Wait for data on serial bus
  while((Serial2.available()<=0)&&(temp_delay<(delayMs-100)))
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
  #ifdef SERIAL_DEBUG
  Serial.print("Warning: ");
  Serial.print(temp_delay);
  Serial.println(" ms passed while waiting for serial response...");
  #endif
  if(Serial2.available())
  {
    char start_char = Serial2.read();
    if(start_char == (char)REMOTE_START)
    {
      sd_data_string_tmp = Serial2.readStringUntil((char)REMOTE_END);
      #ifdef SERIAL_DEBUG
      Serial.print("Received remote sensors data: ");
      Serial.println(sd_data_string_tmp);
      #endif
      sd_data_string += sd_data_string_tmp;
      serial_error = 0;
    }
    else
    {
      #ifdef SERIAL_DEBUG
      Serial.println("Error: Received wrong start character "+String(start_char)+" !");
      #endif
      serial_error = 1;
    }
  }
  else
  {
    #ifdef SERIAL_DEBUG
    Serial.println("Warning: Timeout wainting for remote sensors!");
    #endif
    sd_data_string+=",,,,,";
    serial_error = 1;
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
      digitalWrite(ACTIVITY_LED_PIN,0);
    }
    // if the file isn't open, pop up an error:
    else {
      digitalWrite(ACTIVITY_LED_PIN,1);
      sd_present = false;
      #ifdef SERIAL_DEBUG
      Serial.println("Error opening "+log_file_name);
      #endif
    }
  }
  #endif
  #ifdef SERIAL_DEBUG
  Serial.print("Checking sensors for errors: ");
  Serial.println(String(dht11_error)+","+String(dht22_error)+","+String(sht31_error)+","+String(sht75_error)+","+String(serial_error));
  #endif
  #ifdef LOG_SD
  //TODO: log sensor errors to SD card.
  #endif
  temp_sensors_check();
  temp_hr_sensors_check();
  sensors_sleep();

  millis_end = millis();
  #ifdef SERIAL_DEBUG
  Serial.print("millis_start: ");
  Serial.println(millis_start);
  Serial.print("millis_end: ");
  Serial.println(millis_end);
  #endif
  if(millis_end >= millis_start)
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
  else{
      if(acquisition_time > delayMsRequested)
      {
          delayMs = acquisition_time;
      }
      else
      {
          delayMs = delayMsRequested;
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

void sys_restart(void){
    if (log_file)
      log_file.close();
    if (report_file)
      report_file.close();

    reset_arduino();
}
