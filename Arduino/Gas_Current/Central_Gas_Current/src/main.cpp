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
#define SENSORS_READ_MIN_INTERVAL 750
#define CO2_READ_MIN_INTERVAL 500
#define CURRENT_READ_MIN_INTERVAL 250
#define MOTION_READ_MIN_INTERVAL 750
#define LIGHT_READ_MIN_INTERVAL 750
#define WINDOWS_READ_MIN_INTERVAL 750
#define SENSORS_READ_MAX_INTERVAL 1800000
#define SENSOR_MODULES_TOTAL 5

#define ACTIVITY_LED_PIN 61

#define SD_CHIP_SEL           4
#define SD_CARD_DELAY         500
#define SD_MAX_TRIES          3
#define SERIAL_DELAY          500
#define SERIAL_MAX_TRIES      3

#define RTC_CE      52
#define RTC_SCK     50
#define RTC_IO      48

#define LOG_SD
// #define SERIAL_DEBUG

#define MOTION_START    0xFE
#define LIGHT_START     0xFD
#define WINDOWS_START   0xFC
#define REMOTE_END      0xFF

const String config_file_name="SPUTNIK.CFG";

uint32_t millis_start, millis_end, setup_time, acquisition_time;
uint32_t co2_delay_req, current_delay_req, motion_delay_req, light_delay_req, windows_delay_req;
uint32_t co2_millis_start, current_millis_start, motion_millis_start, light_millis_start, windows_millis_start;

uint8_t sd_present, log_file_opened, config_file_opened, report_file_opened;
String co2_log_file_name, current_log_file_name, motion_log_file_name, light_log_file_name, windows_log_file_name, report_file_name;
String co2_sd_data_string, current_sd_data_string, motion_sd_data_string, light_sd_data_string, windows_sd_data_string;

uint8_t remote_data_received;

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
void log_files_create();
void log_sd(String file_name, String data);
void check_t(void);
void co2_sensors_awake(void);
void co2_sensors_sleep(void);

uint32_t calc_elapsed_time(uint32_t start_time, uint32_t end_time);

void setup() {
    millis_start = millis();
    analogReadResolution(12);
    SPI.begin();
    Serial.begin(115200);
    Serial1.begin(9600);
    remote_data_received = 0;

    co2_delay_req = (uint32_t)CO2_READ_MIN_INTERVAL;
    current_delay_req = (uint32_t)CURRENT_READ_MIN_INTERVAL;
    motion_delay_req = (uint32_t)MOTION_READ_MIN_INTERVAL;
    light_delay_req = (uint32_t)LIGHT_READ_MIN_INTERVAL;
    windows_delay_req = (uint32_t)WINDOWS_READ_MIN_INTERVAL;

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
    sd_present=false;
#ifdef LOG_SD
    sd_card_init();
    delay(SD_CARD_DELAY);
    log_files_create();
#endif

    if(sd_present)
    {
        uint8_t tmp_cntr = 0;
        config_file = SD.open(config_file_name, FILE_READ);
        if (config_file)
        {
#ifdef SERIAL_DEBUG
            Serial.println("Config file successfuly open");
#endif
            while(config_file.available())
            {
                tmp_cntr ++;
                String delayMSstr = "";
                delayMSstr=config_file.readString();
                switch(tmp_cntr)
                {
                    case 1:
                        if((((uint32_t)delayMSstr.toInt())>=((uint32_t)CO2_READ_MIN_INTERVAL))
                        && (((uint32_t)delayMSstr.toInt())<=((uint32_t)SENSORS_READ_MAX_INTERVAL)))
                        {
                            co2_delay_req = delayMSstr.toInt();
#ifdef SERIAL_DEBUG
                            Serial.print("CO2 period (ms): ");
                            Serial.println(co2_delay_req);
#endif
                        }
                        else
                        {
#ifdef SERIAL_DEBUG
                            Serial.print("Waring: Invalid CO2 period found at SD card: ");
                            Serial.println(delayMSstr);
#endif
                        }
                    break;
                    case 2:
                        if((((uint32_t)delayMSstr.toInt())>=((uint32_t)CURRENT_READ_MIN_INTERVAL))
                        && (((uint32_t)delayMSstr.toInt())<=((uint32_t)SENSORS_READ_MAX_INTERVAL)))
                        {
                            current_delay_req = delayMSstr.toInt();
#ifdef SERIAL_DEBUG
                            Serial.print("Current period (ms): ");
                            Serial.println(current_delay_req);
#endif
                        }
                        else
                        {
#ifdef SERIAL_DEBUG
                            Serial.print("Waring: Invalid current period found at SD card: ");
                            Serial.println(delayMSstr);
#endif
                        }
                    break;
                    case 3:
                        if((((uint32_t)delayMSstr.toInt())>=((uint32_t)MOTION_READ_MIN_INTERVAL))
                        && (((uint32_t)delayMSstr.toInt())<=((uint32_t)SENSORS_READ_MAX_INTERVAL)))
                        {
                            motion_delay_req = delayMSstr.toInt();
#ifdef SERIAL_DEBUG
                            Serial.print("Motion period (ms): ");
                            Serial.println(motion_delay_req);
#endif
                        }
                        else
                        {
#ifdef SERIAL_DEBUG
                            Serial.print("Waring: Invalid motion period found at SD card: ");
                            Serial.println(delayMSstr);
#endif
                        }
                    break;
                    case 4:
                        if((((uint32_t)delayMSstr.toInt())>=((uint32_t)LIGHT_READ_MIN_INTERVAL))
                        && (((uint32_t)delayMSstr.toInt())<=((uint32_t)SENSORS_READ_MAX_INTERVAL)))
                        {
                            light_delay_req = delayMSstr.toInt();
#ifdef SERIAL_DEBUG
                            Serial.print("Motion period (ms): ");
                            Serial.println(light_delay_req);
#endif
                        }
                        else
                        {
#ifdef SERIAL_DEBUG
                            Serial.print("Waring: Invalid light period found at SD card: ");
                            Serial.println(delayMSstr);
#endif
                        }
                    break;
                    case 5:
                        if((((uint32_t)delayMSstr.toInt())>=((uint32_t)WINDOWS_READ_MIN_INTERVAL))
                        && (((uint32_t)delayMSstr.toInt())<=((uint32_t)SENSORS_READ_MAX_INTERVAL)))
                        {
                            windows_delay_req = delayMSstr.toInt();
#ifdef SERIAL_DEBUG
                            Serial.print("Motion period (ms): ");
                            Serial.println(light_delay_req);
#endif
                        }
                        else
                        {
#ifdef SERIAL_DEBUG
                            Serial.print("Waring: Invalid windows period found at SD card: ");
                            Serial.println(delayMSstr);
#endif
                        }
                    break;
                    case 6:
                    #ifdef SERIAL_DEBUG
                                                Serial.println("Reached end of file!");
                    #endif
                    break;
                    default:
#ifdef SERIAL_DEBUG
                        Serial.println("Warning: Reached an acquisition period configuration that wasn't supose.");
                        Serial.print("configuration cntr: ");
                        Serial.println(tmp_cntr);
#endif

                    break;
                }
                if(tmp_cntr == ((uint8_t)SENSOR_MODULES_TOTAL + 1))
                {
#ifdef SERIAL_DEBUG
                    Serial.println("Warning: File had more values to read, but sensors total was reached!");
#endif
                    break;
                }
            }
            if(tmp_cntr < (uint8_t)SENSOR_MODULES_TOTAL)
            {
#ifdef SERIAL_DEBUG
                Serial.print("Warning: missing some modules period configuration! (");
                Serial.print(tmp_cntr);
                Serial.print("/");
                Serial.print(SENSOR_MODULES_TOTAL);
                Serial.println(")");
                Serial.println("");
                Serial.println("Applyed periods:");
                Serial.println(co2_delay_req);
                Serial.println(current_delay_req);
                Serial.println(motion_delay_req);
                Serial.println(light_delay_req);
                Serial.println(windows_delay_req);
                Serial.println("");
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
              config_file.println((uint32_t)CO2_READ_MIN_INTERVAL);
              config_file.println((uint32_t)CURRENT_READ_MIN_INTERVAL);
              config_file.println((uint32_t)MOTION_READ_MIN_INTERVAL);
              config_file.println((uint32_t)LIGHT_READ_MIN_INTERVAL);
              config_file.println((uint32_t)WINDOWS_READ_MIN_INTERVAL);
              config_file.close();
            }
            else
            {
#ifdef SERIAL_DEBUG
                Serial.println("Error creating config file!");
#endif
                config_file_opened=false;
            }
            config_file_opened=true;
            config_file.close();
        }
    }
  delay(INITIAL_DELAY);

  sputnikGasInit();
  sputnikCurrentInit();

  millis_end = millis();
#ifdef SERIAL_DEBUG
  Serial.print("millis_start: ");
  Serial.println(millis_start);
  Serial.print("millis_end: ");
  Serial.println(millis_end);
#endif
    setup_time = calc_elapsed_time(millis_start, millis_end);
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
co2_millis_start = current_millis_start = motion_millis_start = light_millis_start = windows_millis_start = 0;
}

void loop() {
    millis_start = millis();

    digitalWrite(ACTIVITY_LED_PIN,1);
    uint32_t millis_temp = millis();

    if(calc_elapsed_time(motion_millis_start,millis_temp) >= motion_delay_req)
    {
        Serial1.write(MOTION_START);
        motion_millis_start = millis_temp;
    }
    if(calc_elapsed_time(light_millis_start,millis_temp) >= light_delay_req)
    {
        Serial1.write(LIGHT_START);
        light_millis_start = millis_temp;
    }
    if(calc_elapsed_time(windows_millis_start,millis_temp) >= windows_delay_req)
    {
        Serial1.write(WINDOWS_START);
        windows_millis_start = millis_temp;
    }

    if(calc_elapsed_time(co2_millis_start,millis_temp) >= co2_delay_req)
    {
        co2_millis_start = millis();
        co2_sensors_awake();
        t = rtc.getTime();
        check_t();
        co2_sd_data_string = String(String(t.year)+","+String(t.mon)+","+String(t.date)+","+String(t.hour)+":"+String(t.min)+":"+String(t.sec));

#ifdef LOG_SD
        if(!sd_present)
        sd_card_init();
#endif
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
        co2_sd_data_string+=","+String(mg811_analog);

        mq135_analog=map(analogRead(MQ135_PIN),0,3917,0,4096);       //Max output voltage: 3.146
#ifdef SERIAL_DEBUG
        Serial.print("MQ135 ADC-12Bit: ");
        Serial.println(mq135_analog);
#endif
        co2_sd_data_string+=","+String(mq135_analog);

        if(ccs811.dataAvailable())
        {
            ccs811.readAlgorithmResults();
#ifdef SERIAL_DEBUG
            Serial.print("CCS188 CO2: ");
            Serial.println(ccs811.getCO2());
            Serial.print("CCS188 TVOC: ");
            Serial.println(ccs811.getTVOC());
#endif
            co2_sd_data_string+=","+String(ccs811.getCO2())+","+String(ccs811.getTVOC());
        }
        else
        {
#ifdef SERIAL_DEBUG
            Serial.println("ERROR: CCS188 didn't respond!");
#endif
            co2_sd_data_string+=",,";
        }
#ifdef LOG_SD
        log_sd(co2_log_file_name, co2_sd_data_string);
#endif
        co2_sensors_sleep();
    }

    if(calc_elapsed_time(current_millis_start,millis_temp) >= current_delay_req)
    {
        current_millis_start = millis();
        t = rtc.getTime();
        check_t();
        current_sd_data_string = String(String(t.year)+","+String(t.mon)+","+String(t.date)+","+String(t.hour)+":"+String(t.min)+":"+String(t.sec));

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
        current_sd_data_string+=","+String(acs770_current_rms)+","+String(acs770_adc_max_map)+","+String(acs770.get_adc_max())+","+String(acs712_current_rms)+","+String(acs712_adc_max_map)+","+String(acs712.get_adc_max())+","+String(pa3208_current_rms)+","+String(pa3208_adc_max_map)+","+String(pa3208.get_adc_max())+","+String(sct013_current_rms)+","+String(sct013_adc_max_map)+","+String(sct013.get_adc_max());
#else
        current_sd_data_string+=","+String(acs770_current_rms)+","+String(acs712_current_rms)+","+String(pa3208_current_rms)+","+String(sct013_current_rms);
#endif
#ifdef LOG_SD
        log_sd(current_log_file_name, current_sd_data_string);
#endif
    }

    // Get everything from serial port
    while(Serial1.available())
    {
        char start_char = Serial1.read();
        switch (start_char) {
            case (char)MOTION_START:
                t = rtc.getTime();
                check_t();
                motion_sd_data_string = String(String(t.year)+","+String(t.mon)+","+String(t.date)+","+String(t.hour)+":"+String(t.min)+":"+String(t.sec));
                motion_sd_data_string  +=  ","+Serial1.readStringUntil((char)REMOTE_END);
#ifdef LOG_SD
                log_sd(motion_log_file_name, motion_sd_data_string);
#endif
                remote_data_received |= 0x01;
            break;
            case (char)LIGHT_START:
                t = rtc.getTime();
                check_t();
                light_sd_data_string = String(String(t.year)+","+String(t.mon)+","+String(t.date)+","+String(t.hour)+":"+String(t.min)+":"+String(t.sec));
                light_sd_data_string += ","+Serial1.readStringUntil((char)REMOTE_END);
#ifdef LOG_SD
                log_sd(light_log_file_name, light_sd_data_string);
#endif
                remote_data_received |= 0x02;
            break;
            case (char)WINDOWS_START:
                t = rtc.getTime();
                check_t();
                windows_sd_data_string = String(String(t.year)+","+String(t.mon)+","+String(t.date)+","+String(t.hour)+":"+String(t.min)+":"+String(t.sec));
                windows_sd_data_string += ","+Serial1.readStringUntil((char)REMOTE_END);
#ifdef LOG_SD
                log_sd(windows_log_file_name, windows_sd_data_string);
#endif
                remote_data_received |= 0x04;
            break;
            default:
            break;
        }
    }

#ifdef SERIAL_DEBUG
    switch(remote_data_received)
    {
        case 0x01:
            Serial.println("------------------------------------");
            Serial.println("---------------REMOTE---------------");
            Serial.println("------------------------------------");
            Serial.print("Motion: ");
            Serial.println(motion_sd_data_string);
        break;
        case 0x02:
            Serial.println("------------------------------------");
            Serial.println("---------------REMOTE---------------");
            Serial.println("------------------------------------");
            Serial.print("Light: ");
            Serial.println(light_sd_data_string);
        break;
        case 0x03:
            Serial.println("------------------------------------");
            Serial.println("---------------REMOTE---------------");
            Serial.println("------------------------------------");
            Serial.print("Motion: ");
            Serial.println(motion_sd_data_string);
            Serial.print("Light: ");
            Serial.println(light_sd_data_string);
        break;
        case 0x04:
            Serial.println("------------------------------------");
            Serial.println("---------------REMOTE---------------");
            Serial.println("------------------------------------");
            Serial.print("Windows: ");
            Serial.println(windows_sd_data_string);
        break;
        case 0x07:
            Serial.println("------------------------------------");
            Serial.println("---------------REMOTE---------------");
            Serial.println("------------------------------------");
            Serial.print("Motion: ");
            Serial.println(motion_sd_data_string);
            Serial.print("Light: ");
            Serial.println(light_sd_data_string);
            Serial.print("Windows: ");
            Serial.println(windows_sd_data_string);
        break;
        default:
        break;
    }
#endif
remote_data_received = 0;

#ifdef SERIAL_DEBUG
    // millis_end = millis();
    // Serial.print("millis_start: ");
    // Serial.println(millis_start);
    // Serial.print("millis_end: ");
    // Serial.println(millis_end);
    //
    // acquisition_time = calc_elapsed_time(millis_start,millis_end);
    //
    // Serial.print("Acquisition time: ");
    // if(acquisition_time >= 60000)
    // {
    //     Serial.print((uint8_t) (acquisition_time/60000));
    //     Serial.println("m");
    // }
    // else if(acquisition_time >= 1000)
    // {
    //     Serial.print((uint8_t) (acquisition_time/1000));
    //     Serial.println("s");
    // }
    // else
    // {
    //   Serial.print(acquisition_time);
    //     Serial.println("ms");
    // }
#endif
}

void sd_card_init(void)
{
    uint8_t sd_card_failures = 0;

    pinMode(SD_CHIP_SEL, OUTPUT);
    digitalWrite(SD_CHIP_SEL, HIGH);

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

void log_files_create()
{
    if(sd_present)
    {
        String generic_log_path = String(t_start.year)+"/"+String(t_start.mon)+"/"+String(t_start.date);
        SD.mkdir("CO2/"+generic_log_path);
        SD.mkdir("CURRENT/"+generic_log_path);
        SD.mkdir("MOTION/"+generic_log_path);
        SD.mkdir("LIGHT/"+generic_log_path);
        SD.mkdir("WINOWS/"+generic_log_path);

        String generic_log_file_name = String(t_start.year)+"/"+String(t_start.mon)+"/"+String(t_start.date)+"/"+String(t_start.hour)+String(t_start.min)+String(t_start.sec)+".CSV";
        co2_log_file_name = "CO2/"+generic_log_file_name;
        current_log_file_name = "CURRENT/"+generic_log_file_name;
        motion_log_file_name = "MOTION/"+generic_log_file_name;
        light_log_file_name = "LIGHT/"+generic_log_file_name;
        windows_log_file_name = "WINDOWS/"+generic_log_file_name;

        log_file = SD.open(co2_log_file_name, FILE_WRITE);
        if (log_file) {
#ifdef SERIAL_DEBUG
            Serial.println("year,month,day,time,MG811 (ADC-12Bit),MQ135 (ADC-12Bit),CCS188 (CO2),CCS188 (TVOC)");
#endif
            log_file.println("year,month,day,time,MG811 (ADC-12Bit),MQ135 (ADC-12Bit),CCS188 (CO2),CCS188 (TVOC)");
            log_file.close();
        }
        else
        {
#ifdef SERIAL_DEBUG
            Serial.println("Error: Opening file "+co2_log_file_name+" for writing");
#endif
        }
        log_file = SD.open(current_log_file_name, FILE_WRITE);
        if (log_file) {
#ifdef SERIAL_DEBUG
            Serial.println("year,month,day,time,ACS770 (Current RMS (A)),ACS712 (Current RMS (A)),PA3208 (Current RMS (A)),SCT0-13 (Current RMS (A))");
#endif
            log_file.println("year,month,day,time,ACS770 (Current RMS (A)),ACS712 (Current RMS (A)),PA3208 (Current RMS (A)),SCT0-13 (Current RMS (A))");
            log_file.close();
        }
        else
        {
#ifdef SERIAL_DEBUG
            Serial.println("Error: Opening file "+current_log_file_name+" for writing");
#endif
        }
            log_file = SD.open(motion_log_file_name, FILE_WRITE);
        if (log_file) {
#ifdef SERIAL_DEBUG
            Serial.println("year,month,day,time,SEN0192 (nr),SE-10 (nr),ZRE200GE (nr),EKMB1101111 (nr)");
#endif
            log_file.println("year,month,day,time,SEN0192 (nr),SE-10 (nr),ZRE200GE (nr),EKMB1101111 (nr)");
            log_file.close();
        }
        else
        {
#ifdef SERIAL_DEBUG
            Serial.println("Error: Opening file "+motion_log_file_name+" for writing");
#endif
        }
        log_file = SD.open(light_log_file_name, FILE_WRITE);
        if (log_file) {
#ifdef SERIAL_DEBUG
            Serial.println("year,month,day,time,TSL2561 data0,TSL2561 data1,TSL2561 lux,SI1145 visible,SI1145 IR,SI1145 UV,ISL29125 Red,ISL29125 Green,ISL29125 Blue");
#endif
            log_file.println("year,month,day,time,TSL2561 data0,TSL2561 data1,TSL2561 lux,SI1145 visible,SI1145 IR,SI1145 UV,ISL29125 Red,ISL29125 Green,ISL29125 Blue");
            log_file.close();
        }
        else
        {
#ifdef SERIAL_DEBUG
        Serial.println("Error: Opening file "+light_log_file_name+" for writing");
#endif
        }
        log_file = SD.open(windows_log_file_name, FILE_WRITE);
        if (log_file) {
#ifdef SERIAL_DEBUG
            Serial.println("year,month,day,time,HC-SRO4 (cm),URM37 (cm),LV-EZ (cm),LV-EZ (mv),itg3200_gx,itg3200_gy,itg3200_gz,itg3200_x_move_count,itg3200_y_move_count,itg3200_z_move_count,itg3200_detected,lis3dh_ax,lis3dh_ay,lis3dh_az,lis3dh_x_move_count,lis3dh_y_move_count,lis3dh_z_move_count,lis3dh_detected");
#endif
            log_file.println("year,month,day,time,HC-SRO4 (cm),URM37 (cm),LV-EZ (cm),LV-EZ (mv),itg3200_gx,itg3200_gy,itg3200_gz,itg3200_x_move_count,itg3200_y_move_count,itg3200_z_move_count,itg3200_detected,lis3dh_ax,lis3dh_ay,lis3dh_az,lis3dh_x_move_count,lis3dh_y_move_count,lis3dh_z_move_count,lis3dh_detected");
            log_file.close();
        }
        else
        {
#ifdef SERIAL_DEBUG
            Serial.println("Error: Opening file "+windows_log_file_name+" for writing");
#endif
        }
    }
}

void log_sd(String file_name, String data)
{
    if(sd_present)
    {
        log_file = SD.open(file_name, FILE_WRITE);
        if (log_file) {
            log_file.println(data);
            log_file.close();
#ifdef SERIAL_DEBUG
            Serial.println(data);
#endif
        }
        else {
            digitalWrite(ACTIVITY_LED_PIN,0);
            sd_present = false;
#ifdef SERIAL_DEBUG
            Serial.println("Error opening "+file_name);
#endif
        }
    }
}

void check_t(void)
{
    if(t.date > t_start.date)
    {
        t_start = t;
        if(sd_present)
        {
            log_files_create();
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
}

void co2_sensors_awake(void){
    digitalWrite(CCS811_NWAK, LOW);
}
void co2_sensors_sleep(void){
    digitalWrite(CCS811_NWAK, HIGH);
}

uint32_t calc_elapsed_time(uint32_t start_time, uint32_t end_time)
{
    uint32_t elapsed_time;
    if(end_time >= start_time)
    {
        elapsed_time = end_time-start_time;
    }
    else
    {
        elapsed_time = 0XFFFFFFFF-start_time+end_time;
    }
    return elapsed_time;
}
