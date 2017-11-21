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

#include <Arduino.h>
#include <Wire.h>
#include "SparkFunTSL2561.h"
#include "SparkFunISL29125.h"
#include "Adafruit_SI1145.h"

#define DEBUG

#define LIGHT_START     0xFD
#define REMOTE_END      0xFF
#if defined (__arm__)
#define Serial_data     Serial1
#elif defined(__AVR_ATmega328P__)
#define Serial_data     Serial
#endif

#define ACQUISITION_T   500

#ifdef INTERRUPT_ACTIVE
#define TSL2561_INT_PIN
#define ISL29125_INT_PIN
#define SI1145_INT_PIN
#endif

#define TSL2561_I2C_ADDR    TSL2561_ADDR_0
#define ISL29125_I2C_ADDR   ISL_I2C_ADDR
#if defined (__arm__)
#define ISL29125_TRIG_PIN   12
#elif defined(__AVR_ATmega328P__)
#define ISL29125_TRIG_PIN   2
#endif
#define SI1145_I2C_ADDR     SI1145_ADDR

#define ACTIVITY_LED_PIN 13

String serial_data_string;
uint32_t millis_start, millis_end, setup_time, acquisition_time, temp_millis, temp_delay, delay_ms;
uint8_t act_led_state = 0;
char serial_comand;
uint8_t loop_started = 0;

SFE_TSL2561 tsl2561;
uint8_t tsl2561_gain;
unsigned int tsl2561_ms;
SFE_ISL29125 isl29125;
Adafruit_SI1145 si1145;
uint8_t tsl256_error, isl29125_error, si1145_error;

void tsl2561_printError(byte error);
void sensors_awake(void);
void sensors_sleep(void);


#ifdef INTERRUPT_ACTIVE
volatile uint8_t tsl2561_detected, isl29125_detected,si1145_detected;

void tsl2561_threshold_detected(void);
void isl29125_threshold_detected(void);
void si1145_threshold_detected(void);
#endif


void setup()
{
    millis_start = millis();
    #if defined(__AVR_ATmega328P__)
    Serial_data.begin(9600); //XBee com port
    #else
    #ifdef DEBUG
    Serial.begin(115200);
    #endif
    Serial_data.begin(9600); //XBee com port
    #endif
    Wire.begin();
    #if defined(__AVR_ATmega328P__)
    //disable i2c internal pullups to work with MLX and SHT31
    digitalWrite(SDA, 0);
    digitalWrite(SCL, 0);
    #endif
    #ifdef DEBUG
    Serial.println("-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-");
    Serial.println(".i.SputnikRedeSensores by ecoPlanos.i.");
    Serial.println("-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-");
    Serial.println();
    #endif
    tsl2561 = SFE_TSL2561();
    tsl2561.begin(TSL2561_I2C_ADDR);

    #ifdef DEBUG
    uint8_t ID;

    if (tsl2561.getID(ID))
    {
        Serial.print("Got factory ID: 0X");
        Serial.print(ID,HEX);
        Serial.println(", should be 0X5X");
    }
    // Most library commands will return true if communications was successful,
    // and false if there was a problem. You can ignore this returned value,
    // or check whether a command worked correctly and retrieve an error code:
    else
    {
        tsl2561_printError(tsl2561.getError());
    }
    #endif

    // The light sensor has a default integration time of 402ms,
    // and a default tsl2561_gain of low (1X).

    // If you would like to change either of these, you can
    // do so using the setTiming() command.

    // If tsl2561_gain = false (0), device is set to low tsl2561_gain (1X)
    // If tsl2561_gain = high (1), device is set to high tsl2561_gain (16X)

    tsl2561_gain = 0;

    // If tsl2561_ = 0, integration will be 13.7ms
    // If tsl2561_ = 1, integration will be 101ms
    // If tsl2561_ = 2, integration will be 402ms
    // If tsl2561_ = 3, use manual start / stop to perform your own integration

    uint8_t tsl2561_time = 2;

    // setTiming() will set the third parameter (ms) to the
    // requested integration time in ms (this will be useful later):
    #ifdef DEBUG
    Serial.println("Set timing for TSL2561...");
    Serial.print("TSL2561 gain setings: ");
    Serial.println(tsl2561_gain);
    Serial.print("TSL2561 time setings: ");
    Serial.println(tsl2561_time);
    Serial.print("TSL2561 integration period: ");
    Serial.println(tsl2561_ms);
    #endif
    tsl2561.setTiming(tsl2561_gain,tsl2561_time,tsl2561_ms);
    // tsl2561.setTiming(tsl2561_gain,tsl2561_time);


    isl29125 = SFE_ISL29125(ISL29125_I2C_ADDR);
    if(!isl29125.init())
    {
        #ifdef DEBUG
        Serial.println("Error: Didn't find ISL9125");
        #endif
        isl29125_error = 1;
    }
    else
    {
        pinMode(ISL29125_TRIG_PIN, OUTPUT);
        digitalWrite(ISL29125_TRIG_PIN, HIGH);
        if(!isl29125.config(  CFG1_MODE_RGB|CFG1_10KLUX|CFG1_16BIT|CFG1_ADC_SYNC_TO_INT,
                            CFG2_IR_OFFSET_OFF|CFG2_IR_ADJUST_MID,
                            CFG3_NO_INT|CFG3_RGB_CONV_TO_INT_DISABLE))
        {
            #ifdef DEBUG
            Serial.println("Error: ISL2925 configuration error!");
            #endif
        }
        isl29125_error = 0;
    }

    si1145 = Adafruit_SI1145();
    if (! si1145.begin())
    {
        #ifdef DEBUG
        Serial.println("Error: Didn't find Si1145");
        #endif
        si1145_error = 1;
    }
    else
        si1145_error = 0;

    delay_ms = ACQUISITION_T;

    loop_started = 0;
    sensors_awake();

    #ifdef INTERRUPT_ACTIVE
    pinMode(TSL2561_INT_PIN, INPUT);
    pinMode(ISL29125_INT_PIN, INPUT);
    pinMode(SI1145_INT_PIN, INPUT);
    pinMode(ACTIVITY_LED_PIN, OUTPUT);
    tsl2561_detected = 0;
    tsl2561.setInterruptControl(1,0);
    isl29125_detected = 0;
    si1145_detected = 0;
    attachInterrupt(digitalPinToInterrupt(TSL2561_INT_PIN),tsl2561_threshold_detected,RISING);
    attachInterrupt(digitalPinToInterrupt(ISL29125_INT_PIN),isl29125_threshold_detected,RISING);
    attachInterrupt(digitalPinToInterrupt(SI1145_INT_PIN),si1145_threshold_detected,RISING);
    #endif
    millis_end = millis();
    #ifdef DEBUG
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
    #ifdef DEBUG
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

void loop()
{
    millis_start = millis();
    String serial_data_string = "";

    digitalWrite(ISL29125_TRIG_PIN, LOW);

    digitalWrite(ACTIVITY_LED_PIN,HIGH);

    if(!loop_started)
    {
        delay(delay_ms);
    }

    #ifdef DEBUG
    Serial.println("------------------------------------");
    Serial.println("----------------LIGHT---------------");
    Serial.println("------------------------------------");
    #endif
    // tsl2561.setPowerDown();
    unsigned int data0, data1;
    if (tsl2561.getData(data0,data1))
    {
      // getData() returned true, communication was successful

      double lux;    // Resulting lux value
      boolean good;  // True if neither sensor is saturated

      // Perform lux calculation:
      good = tsl2561.getLux(tsl2561_gain,delay_ms,data0,data1,lux);

      #ifdef DEBUG
      Serial.print("tsl2561 data0: ");
      Serial.println(data0);
      Serial.print("tsl2561 data1: ");
      Serial.println(data1);
      Serial.print("tsl2561 lux: ");
      Serial.println(lux);
      Serial.print("Saturated? ");
      if (good) Serial.println("no"); else Serial.println("yes");
      #endif

      serial_data_string+=String(data0)+","+String(data1)+","+String(lux)+","+String(good);
    }
    else
    {
      // getData() returned false because of an I2C error, inform the user.
      #ifdef DEBUG
      tsl2561_printError(tsl2561.getError());
      #endif

      serial_data_string += ",,,";
    }

    uint16_t si1145_visible = si1145.readVisible(), si1145_ir = si1145.readIR();
    float si1145_uv_index = si1145.readUV()/100.0;
    #ifdef DEBUG
    Serial.print("SI1145 visible: "); Serial.println(si1145_visible);
    Serial.print("SI1145 IR: "); Serial.println(si1145_ir);
    Serial.print("SI1145 UV: ");  Serial.println(si1145_uv_index);
    // Uncomment if you have an IR LED attached to LED pin!
    //Serial.print("SI1145 Prox: "); Serial.println(si1145.readProx());
    #endif
    serial_data_string+=","+String(si1145_visible)+","+String(si1145_ir)+","+String(si1145_uv_index);

    if(!isl29125_error)
    {
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

        // Wait for sensor data to be ready
        uint8_t isl29125_ready = isl29125.checkDataReady();

        while(!isl29125_ready&&(temp_delay<(delay_ms-200)))
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
            isl29125_ready = isl29125.checkDataReady();
        }

        if(isl29125_ready)
        {
            uint16_t isl29125_red = isl29125.readRed();
            uint16_t isl29125_green = isl29125.readGreen();
            uint16_t isl29125_blue = isl29125.readBlue();
            #ifdef DEBUG
            Serial.print("ISL29125 Red: "); Serial.println(isl29125_red,HEX);
            Serial.print("ISL29125 Green: "); Serial.println(isl29125_green,HEX);
            Serial.print("ISL29125 Blue: "); Serial.println(isl29125_blue,HEX);
            #endif
            serial_data_string += "," + String(isl29125_red) + "," + String(isl29125_green) + "," + String(isl29125_blue);
        }
        else
        {
            #ifdef DEBUG
            Serial.println("Warning: timeout waiting for ISL29125 data!");
            #endif
            serial_data_string += ",,,";
        }
        digitalWrite(ISL29125_TRIG_PIN, HIGH);
    }

    //Check if threshold was detected
    #ifdef INTERRUPT_ACTIVE
    if(tsl2561_detected)
    {
        tsl2561_detected = 0;
        #ifdef DEBUG
        Serial.println("TSL2561");
        #endif
        act_led_state = !act_led_state;
        digitalWrite(ACTIVITY_LED_PIN,act_led_state);
    }
    if(isl29125_detected)
    {
        isl29125_detected = 0;
        #ifdef DEBUG
        Serial.println("ISL29125");
        #endif
        act_led_state = !act_led_state;
        digitalWrite(ACTIVITY_LED_PIN,act_led_state);
    }
    if(si1145_detected)
    {
        si1145_detected = 0;
        si1145_threshold.record_threshold();
        #ifdef DEBUG
        Serial.println("SI1145");
        #endif
        act_led_state = !act_led_state;
        digitalWrite(ACTIVITY_LED_PIN,act_led_state);
    }
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

    if(!loop_started)
    {
        loop_started = 1;
    }
    else
    {
        // Wait for data on serial bus
        while((Serial_data.available()<=0)&&(temp_delay<(delay_ms-100)))
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
        if(Serial_data.available())
        {
            serial_comand = Serial_data.read();
            if(serial_comand == (char)LIGHT_START)
            {
                Serial_data.write(LIGHT_START);
                Serial_data.print(serial_data_string);
                Serial_data.write(REMOTE_END);
            }
        }
        else
        {
            #ifdef DEBUG
            Serial.print("Timeout: ");
            Serial.print(temp_delay);
            Serial.println(" ms passed while waiting for serial response...");
            #endif
        }
    }
    millis_end = millis();
    #ifdef DEBUG
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
    #ifdef DEBUG
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
    if(acquisition_time >= delay_ms)
    {
        delay_ms = acquisition_time;
        #ifdef DEBUG
        Serial.print("Warning: Acquisition time forced to ");
        Serial.print(delay_ms);
        Serial.println(" ms");
        #endif
    }
    else{
        if(acquisition_time > ACQUISITION_T)
        {
            delay_ms = acquisition_time;
        }
        else
        {
            delay_ms = ACQUISITION_T;
        }
    }
    temp_delay = (delay_ms-acquisition_time)/2;
    #ifdef SERIAL_DEBUG
    Serial.print("temp_delay:");
    Serial.println(temp_delay);
    #endif
    // Delay between measurements.
    delay(temp_delay);
    digitalWrite(ACTIVITY_LED_PIN,0);
    delay(temp_delay);

}

void tsl2561_printError(byte error)
  // If there's an I2C error, this function will
  // print out an explanation.
{
    Serial.print("I2C error: ");
    Serial.print(error,DEC);
    Serial.print(", ");

    switch(error)
    {
    case 0:
        Serial.println("success");
        break;
    case 1:
        Serial.println("data too long for transmit buffer");
        break;
    case 2:
        Serial.println("received NACK on address (disconnected?)");
        break;
    case 3:
        Serial.println("received NACK on data");
        break;
    case 4:
        Serial.println("other error");
        break;
    default:
        Serial.println("unknown error");
        break;
    }
}

void sensors_awake(void){
    tsl2561.setPowerUp();
}
void sensors_sleep(void){
    tsl2561.setPowerDown();
}

#ifdef INTERRUPT_ACTIVE
void tsl2561_threshold_detected(void)
{
        tsl2561_detected = 1;
}
void isl29125_threshold_detected(void)
{
        isl29125_detected = 1;
}
void si1145_threshold_detected(void)
{
        si1145_detected = 1;
}
#endif
