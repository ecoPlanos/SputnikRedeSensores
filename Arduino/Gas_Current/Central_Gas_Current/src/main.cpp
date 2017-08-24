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
////////////////////
#include "SputnikGas.h"
////////////////////
#define INITIAL_DELAY 100
#define SENSORS_READ_INTERVAL 1000 //Sensors read minimum interval (ms)

#define SD_CHIP_SEL          4//10

#define LOG_SD
#define LOG_SERIAL

const String log_file_sufix="Data.csv";
const String config_file_name="SPUTNIK.CFG";

const char* ssid = "SSID";
const char* password = "PASS";

uint32_t millis_start, millis_end, setup_time, acquisition_time;
uint32_t delayMS;
uint8_t thr_led_state;

String log_file_name, report_file_name;

void sd_card_init(void);
void sensors_awake(void);
void sensors_sleep(void);

Sd2Card card;
SdVolume volume;
SdFile root;
File log_file, config_file;

DS1302 rtc(24, 23, 22);
Time t;

void setup() {
  sys_time = millis();
  sys_time_last = sys_time;

  analogReadResolution(12);
  pinMode(THR_LED, OUTPUT);

  // Set the clock to run-mode, and disable the write protection
  rtc.halt(false);
  rtc.writeProtect(false);
  //Adjust RTC Date And Time
  rtc.setDOW(MONDAY);        // Set Day-of-Week to FRIDAY
  rtc.setTime(13, 45, 30);     // Set the time to 12:00:00 (24hr format)
  rtc.setDate(17, 07, 2017);   // Set the date to August 6th, 2010
  Serial.begin(115200);
  #ifdef LOG_SERIAL
  Serial.println("-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-");
  Serial.println(".i.SputnikRedeSensores by ecoPlanos.i.");
  Serial.println("-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-");
  Serial.println();
  #endif

  t = rtc.getTime();

  log_file_name = String(t.year)+"/"+String(t.mon)+"/"+String(t.date)+"/"+String(t.hour)+"H"+String(t.min)+"M"+String(t.sec)+".CSV";

  Serial.println(log_file_name);
  sd_card_init();
  SD.mkdir(String(t.year)+"/"+String(t.mon)+"/"+String(t.date));
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
  //  Initialize Gas Sensors

  sputnikGasInit();

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
  #ifdef LOG_SERIAL
  Serial.println("------------------------------------");
  Serial.println("----------------GAS-----------------");
  Serial.println("------------------------------------");
  #endif
  sct013_analog=analogRead(SCT013_PIN);
  #ifdef LOG_SERIAL
  Serial.print("SCT013-000 Analogic: ");
  Serial.println(sct013_analog);
  #endif
  sd_data_string+=String(sct013_analog)+",";
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
