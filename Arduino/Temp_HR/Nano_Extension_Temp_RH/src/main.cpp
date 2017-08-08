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
#include "../../../SputnikConfig.h"
#include "SputnikTempRH.h"
#include "SputnikTemp.h"
////////////////////

uint32_t millis_start, millis_end, setup_time, acquisition_time;
uint32_t delayMS;
uint8_t act_led_state;

uint8_t serial_on;

void serial_init(void);
void sensors_awake(void);
void sensors_sleep(void);

void setup() {
  millis_start = millis();
  Wire.begin();
  Serial.begin(115200);
  #ifdef SERIAL_DEBUG
  Serial.println("-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-");
  Serial.println(".i.SputnikRedeSensores by ecoPlanos.i.");
  Serial.println("-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-");
  Serial.println();
  #endif

  pinMode(ACTIVITY_LED, OUTPUT);
  act_led_state = 0;

  serial_on=false;
  serial_init();

  delay(SERIAL_DELAY);

  // delayMS = (SENSORS_READ_INTERVAL > delayMS) ? SENSORS_READ_INTERVAL : delayMS;
  delayMS = SENSORS_READ_INTERVAL;
  #ifdef SERIAL_DEBUG
    Serial.print("Logging interval: ");
    Serial.println(delayMS);
  #endif

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
  String serial_data_string = "";

  sensors_awake();
  #ifdef LOG_SERIAL
  if(!serial_on)
    serial_init();
  #endif
  serial_data_string+=String(millis_start)+",";
  #ifdef SERIAL_DEBUG
  Serial.println("------------------------------------");
  Serial.println("----------------T&RH----------------");
  Serial.println("------------------------------------");
  #endif

  float sht31_temp = sht31.readTemperature()-SHT31_OFFSET;
  float sht31_hr = sht31.readHumidity();

  if (! isnan(sht31_temp)) {  // check if 'is not a number'
    #ifdef SERIAL_DEBUG
    Serial.print("SHT31 Temp: ");
    Serial.print(sht31_temp);
    Serial.println(" *C");
    #endif
    serial_data_string+=String(sht31_temp)+",";
  } else {
    sht31_error=1;
    #ifdef SERIAL_DEBUG
    Serial.println("Error reading SHT31 temperature!");
    #endif
    serial_data_string+=",";
  }

  if (! isnan(sht31_hr)) {  // check if 'is not a number'
    #ifdef SERIAL_DEBUG
    Serial.print("SHT31 RH: ");
    Serial.print(sht31_hr);
    Serial.println("%");
    #endif
    serial_data_string+=String(sht31_hr)+",";
  } else {
    sht31_error = 1;
    #ifdef SERIAL_DEBUG
    Serial.println("Error reading SHT31 humidity!");
    #endif
    serial_data_string+=",";
  }

  #ifdef SERIAL_DEBUG
  Serial.println("------------------------------------");
  Serial.println("----------------TEMP----------------");
  Serial.println("------------------------------------");
  #endif
  float mlx_t_amb = mlx.readAmbientTempC();
  float mlx_t_obj = mlx.readObjectTempC();

  if ((!isnan(mlx_t_amb))&&(mlx_t_amb>-200.15)&&(mlx_t_obj>-200.15)) {  // check if 'is not a number'
    #ifdef SERIAL_DEBUG
    Serial.print("MLX90614 Ambient Temp: ");
    Serial.print(mlx_t_amb);
    Serial.println(" *C");
    Serial.print("MLX90614 Object Temp: ");
    Serial.print(mlx_t_obj);
    Serial.println(" *C");
    #endif
    serial_data_string+=String(mlx_t_amb)+",";
    serial_data_string+=String(mlx_t_obj)+",";
  } else {
    mlx_error = 1;
    #ifdef SERIAL_DEBUG
    Serial.println("Error reading MLX90614 temperature!");
    #endif
    serial_data_string+=",,";
  }

  #ifdef LOG_SERIAL
  // Log to serial output
  if(serial_on)
  {
    #ifdef SERIAL_DEBUG
    Serial.println("Logged data: "+serial_data_string);
    #endif
    Serial.println(serial_data_string);
  }
  #endif
  #ifdef SERIAL_DEBUG
  Serial.print("Cheking sensors for errors: ");
  Serial.println(String(sht31_error)+","+String(mlx_error));
  #endif
  temp_sensors_check();
  temp_hr_sensors_check();
  sensors_sleep();
  act_led_state = ~act_led_state;
  digitalWrite(ACTIVITY_LED,act_led_state);
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
  if(acquisition_time >= delayMS)
  {
    delayMS = ((uint8_t)(acquisition_time/1000))*1000+1000;
    #ifdef SERIAL_DEBUG
    Serial.print("Warning: Acquisition time forced to ");
    Serial.print(delayMS);
    Serial.println(" ms");
    #endif
  }
  // Delay between measurements.
  delay(delayMS-acquisition_time);
}

void serial_init(void)
{
  uint8_t serial_failures = 0;
  while(serial_failures < SERIAL_MAX_TRIES)
  {
    serial_failures++;
    //TODO: implement serial protocol!
  }
}

void sensors_awake(void){
}
void sensors_sleep(void){
}
