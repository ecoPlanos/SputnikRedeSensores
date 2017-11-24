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

#include <Wire.h>
////////////////////
#include <SPI.h>
#include <SD.h>
#include <DS1302.h>
////////////////////
#include "SputnikGas.h"
#include "SputnikCurrent.h"
////////////////////
#define SOFTWARE_VERSION      100
#define INITIAL_DELAY         100
#define SENSORS_READ_MIN_INTERVAL 500     //Sensors read minimum interval (2s)
#define SENSORS_READ_MAX_INTERVAL 1800000  //Sensors read maximum interval (30min)
#define ACTIVITY_LED_PIN A7

#define SD_CHIP_SEL           4//10
#define SD_CARD_DELAY         500
#define SD_MAX_TRIES          3
#define SERIAL_DELAY          500
#define SERIAL_MAX_TRIES      3

#define RTC_CE      52
#define RTC_SCK     50
#define RTC_IO      48

#define LOG_SD
// #define SERIAL_DEBUG

#define MOTION_START 0xFE
#define LIGHT_START 0xFD
#define REMOTE_END 0xFF

const String log_file_sufix="Data.csv";
const String config_file_name="SPUTNIK.CFG";

const char* ssid = "SSID";
const char* password = "PASS";

uint32_t millis_start, millis_end, setup_time, acquisition_time;
uint32_t delayMs, delayMsRequested, temp_delay;

uint8_t serial_error;

uint8_t sd_present, log_file_opened, config_file_opened, report_file_opened;
String log_file_name, report_file_name;

uint8_t remote_data_received = 0;

Sd2Card card;
SdVolume volume;
SdFile root;
File log_file, config_file, report_file;

DS1302 rtc(RTC_CE, RTC_IO, RTC_SCK);
Time t_start, t;

#ifdef SERIAL_DEBUG
uint16_t acs770_adc_max_map, acs712_adc_max_map, pa3208_adc_max_map, sct013_adc_max_map;
#endif

void sd_card_init(void);
void sensors_awake(void);
void sensors_sleep(void);

void setup() {
  millis_start = millis();
  analogReadResolution(12);
  SPI.begin();
  Serial.begin(115200);
  Serial1.begin(9600);

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
  // rtc.setDOW(THURSDAY);      // Set Day-of-Week to FRIDAY
  // rtc.setTime(22, 10, 00);   // Set the time
  // rtc.setDate(9, 11, 2017);  // Set the date
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

  if(sd_present)
  {
      #ifdef LOG_SD
      log_file = SD.open(log_file_name, FILE_WRITE);
      if (log_file) {
          #ifdef SERIAL_DEBUG
          log_file.println("year,month,day,time,MG811 (ADC-12Bit),MQ135 (ADC-12Bit),CCS188 (CO2),CCS188 (TVOC),ACS770 (Current RMS (A)),ACS770 (ADC map),ACS770 (ADC RAW),ACS712 (Current RMS (A)),ACS712 (ADC map),ACS712 (ADC RAW),PA3208 (Current RMS (A)),PA3208 (ADC map),PA3208 (ADC RAW),SCT0-13 (Current RMS (A)),SCT0-13 (ADC map),SCT0-13 (ADC RAW),SEN0192 (nr),SE-10 (nr),ZRE200GE (nr),EKMB1101111 (nr),TSL2561 data0,TSL2561 data1,TSL2561 lux,SI1145 visible,SI1145 IR,SI1145 UV,ISL29125 Red,ISL29125 Green,ISL29125 Blue");
          #else
          log_file.println("year,month,day,time,MG811 (ADC-12Bit),MQ135 (ADC-12Bit),CCS188 (CO2),CCS188 (TVOC),ACS770 (Current RMS (A)),ACS712 (Current RMS (A)),PA3208 (Current RMS (A)),SCT0-13 (Current RMS (A)),SEN0192 (nr),SE-10 (nr),ZRE200GE (nr),EKMB1101111 (nr),TSL2561 data0,TSL2561 data1,TSL2561 lux,SI1145 visible,SI1145 IR,SI1145 UV,ISL29125 Red,ISL29125 Green,ISL29125 Blue");
          #endif
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
  //  Initialize Gas Sensors

  sputnikGasInit();
  sputnikCurrentInit();

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
              #ifdef SERIAL_DEBUG
              log_file.println("year,month,day,time,MG811 (ADC-12Bit),MQ135 (ADC-12Bit),CCS188 (CO2),CCS188 (TVOC),ACS770 (Current RMS (A)),ACS770 (ADC map),ACS770 (ADC RAW),ACS712 (Current RMS (A)),ACS712 (ADC map),ACS712 (ADC RAW),PA3208 (Current RMS (A)),PA3208 (ADC map),PA3208 (ADC RAW),SCT0-13 (Current RMS (A)),SCT0-13 (ADC map),SCT0-13 (ADC RAW),SEN0192 (nr),SE-10 (nr),ZRE200GE (nr),EKMB1101111 (nr),TSL2561 data0,TSL2561 data1,TSL2561 lux,SI1145 visible,SI1145 IR,SI1145 UV,ISL29125 Red,ISL29125 Green,ISL29125 Blue");
              #else
              log_file.println("year,month,day,time,MG811 (ADC-12Bit),MQ135 (ADC-12Bit),CCS188 (CO2),CCS188 (TVOC),ACS770 (Current RMS (A)),ACS712 (Current RMS (A)),PA3208 (Current RMS (A)),SCT0-13 (Current RMS (A)),SEN0192 (nr),SE-10 (nr),ZRE200GE (nr),EKMB1101111 (nr),TSL2561 data0,TSL2561 data1,TSL2561 lux,SI1145 visible,SI1145 IR,SI1145 UV,ISL29125 Red,ISL29125 Green,ISL29125 Blue");
              #endif
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
  }

  digitalWrite(ACTIVITY_LED_PIN,1);

  Serial1.write(MOTION_START);
  Serial1.write(LIGHT_START);

  String sd_data_string = "";
  String motion_data_string = "", light_data_string = "";

  sensors_awake();
  #ifdef LOG_SD
  if(!sd_present)
    sd_card_init();
  #endif
  sd_data_string+=String(String(t.year)+","+String(t.mon)+","+String(t.date)+","+String(t.hour)+":"+String(t.min)+":"+String(t.sec))+",";
  #ifdef SERIAL_DEBUG
  Serial.println("------------------------------------");
  Serial.println("----------------GAS-----------------");
  Serial.println("------------------------------------");
  #endif
  mg811_analog=analogRead(MG811_PIN);
  #ifdef SERIAL_DEBUG
  Serial.print("MG811 ADC-12Bit: ");
  Serial.println(mg811_analog);
  #endif
  sd_data_string+=String(mg811_analog)+",";

  mq135_analog=map(analogRead(MQ135_PIN),0,3917,0,4096);       //Max output voltage: 3.146
  #ifdef SERIAL_DEBUG
  Serial.print("MQ135 ADC-12Bit: ");
  Serial.println(mq135_analog);
  #endif
  sd_data_string+=String(mq135_analog)+",";

  if(ccs811.dataAvailable())
  {
    ccs811.readAlgorithmResults();
    #ifdef SERIAL_DEBUG
    Serial.print("CCS188 CO2: ");
    Serial.println(ccs811.getCO2());
    Serial.print("CCS188 TVOC: ");
    Serial.println(ccs811.getTVOC());
    #endif
    sd_data_string+=String(ccs811.getCO2())+","+String(ccs811.getTVOC())+",";
  }
  else
  {
    #ifdef SERIAL_DEBUG
    Serial.println("ERROR: CCS188 didn't respond!");
    #endif
    sd_data_string+=",,";
  }
  #ifdef SERIAL_DEBUG
  Serial.println("------------------------------------");
  Serial.println("--------------CURRENT---------------");
  Serial.println("------------------------------------");
  #endif
  acs770.sample_triger();
  acs712.sample_triger();
  pa3208.sample_triger();
  sct013.sample_triger();
  acs770_current_rms = (float_t)(acs770.get_adc_max()-ACS770_CAL_MIN)*(float_t)(3.35/(ACS770_AVG_335-ACS770_CAL_MIN));
  acs712_current_rms = (float_t)(acs712.get_adc_max()-ACS712_CAL_MIN)*(float_t)(3.35/(ACS712_AVG_335-ACS712_CAL_MIN));
  pa3208_current_rms = (float_t)(pa3208.get_adc_max()-PA3208_CAL_MIN)*(float_t)(3.35/(PA3208_AVG_335-PA3208_CAL_MIN));
  sct013_current_rms = (float_t)(sct013.get_adc_max()-SCT013_CAL_MIN)*(float_t)(3.35/(SCT013_AVG_335-SCT013_CAL_MIN));
  #ifdef SERIAL_DEBUG
  acs770_adc_max_map = abs(map(acs770.get_adc_max(),ACS770_CAL_MIN,ACS770_CAL_MAX,0,4095));
  acs712_adc_max_map = abs(map(acs712.get_adc_max(),ACS712_CAL_MIN,ACS712_CAL_MAX,0,4095));
  pa3208_adc_max_map = abs(map(pa3208.get_adc_max(),PA3208_CAL_MIN,PA3208_CAL_MAX,0,4095));
  sct013_adc_max_map = abs(map(sct013.get_adc_max(),SCT013_CAL_MIN,SCT013_CAL_MAX,0,4095));
  Serial.print("ACS770 Current RMS: ");
  Serial.println(acs770_current_rms);
  Serial.print("ACS712 Current RMS: ");
  Serial.println(acs712_current_rms);
  Serial.print("PA3208 Current RMS: ");
  Serial.println(pa3208_current_rms);
  Serial.print("SCT0-13 Current RMS: ");
  Serial.println(sct013_current_rms);
  Serial.print("ACS770 ADC Max Map: ");
  Serial.println(acs770_adc_max_map);
  Serial.print("ACS712 ADC Max Map: ");
  Serial.println(acs712_adc_max_map);
  Serial.print("PA3208 ADC Max Map: ");
  Serial.println(pa3208_adc_max_map);
  Serial.print("SCT0-13 ADC Max Map: ");
  Serial.println(sct013_adc_max_map);
  Serial.print("ACS770 ADC Max RAW: ");
  Serial.println(acs770.get_adc_max());
  Serial.print("ACS712 ADC Max RAW: ");
  Serial.println(acs712.get_adc_max());
  Serial.print("PA3208 ADC Max RAW: ");
  Serial.println(pa3208.get_adc_max());
  Serial.print("SCT0-13 ADC Max RAW: ");
  Serial.println(sct013.get_adc_max());
  sd_data_string+=String(acs770_current_rms)+","+String(acs770_adc_max_map)+","+String(acs770.get_adc_max())+","+String(acs712_current_rms)+","+String(acs712_adc_max_map)+","+String(acs712.get_adc_max())+","+String(pa3208_current_rms)+","+String(pa3208_adc_max_map)+","+String(pa3208.get_adc_max())+","+String(sct013_current_rms)+","+String(sct013_adc_max_map)+","+String(sct013.get_adc_max())+",";
  #else
  sd_data_string+=String(acs770_current_rms)+","+String(acs712_current_rms)+","+String(pa3208_current_rms)+","+String(sct013_current_rms)+",";
  #endif

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
    while(temp_delay<(delayMs-100))
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
        while(Serial1.available())
        {
            char start_char = Serial1.read();
            switch (start_char) {
                case (char)MOTION_START:
                    motion_data_string = Serial1.readStringUntil((char)REMOTE_END);
                    remote_data_received |= 0x01;
                    serial_error = 0;
                break;
                case (char)LIGHT_START:
                    light_data_string = Serial1.readStringUntil((char)REMOTE_END);
                    remote_data_received |= 0x02;
                    serial_error = 0;
                break;
                default:
                    serial_error = 1;
                break;
            }
        }
    }
    switch(remote_data_received)
    {
        case 0x01:
            sd_data_string  += motion_data_string
                            + ",,,,,,,,,";
        break;
        case 0x02:
            sd_data_string  += ",,,,"
                            + light_data_string;
        break;
        case 0x03:
            sd_data_string  += motion_data_string + ","
                            + light_data_string;
        break;
        default:
            #ifdef SERIAL_DEBUG
            Serial.println("Warning: Timeout wainting for remote sensors!");
            #endif
            sd_data_string  += ",,,,,,,,,,,,,";
            serial_error = 1;
        break;
    }

    remote_data_received = 0;

    #ifdef SERIAL_DEBUG
    Serial.print("Received data string: ");
    Serial.println(final_remote_str);
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
      digitalWrite(ACTIVITY_LED_PIN,0);
      sd_present = false;
      #ifdef SERIAL_DEBUG
      Serial.println("Error opening "+log_file_name);
      #endif
    }
  }
  #endif
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
  temp_delay = (delayMs-acquisition_time)/2;
  #ifdef SERIAL_DEBUG
  Serial.print("temp_delay:");
  Serial.println(temp_delay);
  #endif
  // Delay between measurements.
  delay(temp_delay);
  digitalWrite(ACTIVITY_LED_PIN,0);
  delay(temp_delay);
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
  digitalWrite(CCS811_NWAK, LOW);
}
void sensors_sleep(void){
  digitalWrite(CCS811_NWAK, HIGH);
}
