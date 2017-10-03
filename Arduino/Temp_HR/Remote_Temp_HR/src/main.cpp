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
#include "SputnikConfig.h"
#include "SputnikComm.h"
#include "SputnikTempRH.h"
#include "SputnikTemp.h"
////////////////////

uint32_t millis_start, millis_end, setup_time, acquisition_time;
uint8_t act_led_state;
char serial_comand;

void sensors_awake(void);
void sensors_sleep(void);

void setup() {
  millis_start = millis();
  Serial.begin(115200);

  Wire.begin();
  //disable i2c internal pullups to work with MLX and SHT31
  digitalWrite(SDA, 0);
  digitalWrite(SCL, 0);

  SPI.begin();

  #ifdef SERIAL_DEBUG
  Serial.println("-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-");
  Serial.println(".i.SputnikRedeSensores by ecoPlanos.i.");
  Serial.println("-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-");
  Serial.println();
  #endif

  // pinMode(9, OUTPUT);
  // act_led_state = 1;
  // digitalWrite(9, act_led_state);

  delay(SERIAL_DELAY);
  // Initialize temperature and RH sensors.
  temp_hr_init();
  //  Initialize temperature sensors
  temp_init();
  delay(INITIAL_DELAY);
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
  if(Serial.available()>0)
  {
    serial_comand = Serial.read();
    if((uint8_t)serial_comand == (uint8_t)REMOTE_START)
    {
      millis_start = millis();
      String serial_data_string = "";
      sensors_awake();
      // serial_data_string+=String(millis_start)+",";
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

      thermopar.readTempC();
      if (!isnan(thermopar.temperature_c)) {
        #ifdef SERIAL_DEBUG
        Serial.print("Thermopar temp: ");
        Serial.print(thermopar.temperature_c);
        Serial.println(" *C");
        #endif
        // sd_data_string+=String(thermopar.temperature_cjt)+","+String(thermopar.temperature_raw)+",";
        serial_data_string+=String(thermopar.temperature_raw);
      }
      else
      {
        serial_data_string+=",";
      }

      Serial.write(REMOTE_START);
      Serial.print(serial_data_string);
      Serial.write(REMOTE_END);

      #ifdef SERIAL_DEBUG
      Serial.println("Sent data: "+serial_data_string);
      Serial.print("Cheking sensors for errors: ");
      Serial.println(String(sht31_error)+","+String(mlx_error));
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
    }
    else
    {
      #ifdef SERIAL_DEBUG
      Serial.print("Received invalid serial comand: ");
      Serial.write(serial_comand);
      Serial.println();
      Serial.print("Expected data: ");
      Serial.write(REMOTE_START);
      Serial.println();
      #endif
    }
    // act_led_state = ~act_led_state;
    // digitalWrite(9,act_led_state);
  }
}

void sensors_awake(void){
}
void sensors_sleep(void){
}
