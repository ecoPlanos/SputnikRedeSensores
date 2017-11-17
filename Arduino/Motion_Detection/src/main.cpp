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

#define DEBUG

#define REMOTE_START 0xFE
#define REMOTE_END 0xFF

#define SEN0192_INT_PIN 10
#define SE10_INT_PIN 11

#define ACTIVITY_LED_PIN 13

#define SEN0192_MIN_PULSE_WIDTH 5
#define SE10_MIN_PULSE_WIDTH 5
#define SEN0192_ID 0
#define SE10_ID 1

#define FIFO_WIDTH 128

class Motion {
    uint8_t _sensor_id;
    uint32_t _cntr;
    uint8_t _motion_detected[FIFO_WIDTH];
    // Time _t[FIFO_WIDTH];
    uint8_t _overflow;
  public:
    void init(uint8_t sensor_id);
    void record_motion(void);
    void append_string(String *str);
    void reset_count(void);
    uint32_t get_count(void) {return _cntr;}
};

void Motion::init(uint8_t sensor_id)
{
    uint32_t i = 0;
    _sensor_id = sensor_id;
    _cntr = 0;
    _overflow = 0;
    for(i = 0; i < FIFO_WIDTH; i++)
    {
        _motion_detected[i] = 0;
    }
}
void Motion::record_motion(void)
{
    // _motion_detected[_cntr] = 1;
    _cntr++;
}
void Motion::append_string(String *str)
{
    uint32_t i = 0, j = 0;
    for(i = 0; i < _cntr; i++)
    {
        // *str+=String(t[i].year)+"/"+String(t[i].mon)+"/"+String(t[i].date)+"/"+String(t[i].hour)+String(t[i].min)+String(t[i].sec);
        for(j = 0; j < _sensor_id+1; j++)
        {
            *str+=",";
        }
        *str+=String(_motion_detected[i])+",";
    }
    _cntr = 0;
}

void Motion::reset_count(void)
{
    _cntr = 0;
}

uint8_t total_sensors = 4;
Motion sen0192_motion, se10_motion;
String serial_data_string;
uint8_t act_led_state = 0;
volatile uint8_t sen0192_detected, se10_detected;

void sen0192_motion_detected(void);
void se10_motion_detected(void);

void setup()
{
    #ifdef DEBUG
    Serial.begin(115200);
    #endif
    Serial1.begin(9600); //XBee com port
    pinMode(SEN0192_INT_PIN, INPUT);
    pinMode(SE10_INT_PIN, INPUT);

    pinMode(ACTIVITY_LED_PIN, OUTPUT);
    sen0192_detected = 0;
    se10_detected = 0;
    sen0192_motion.init(SEN0192_ID);
    se10_motion.init(SE10_ID);
    attachInterrupt(digitalPinToInterrupt(SEN0192_INT_PIN),sen0192_motion_detected,FALLING);
    attachInterrupt(digitalPinToInterrupt(SE10_INT_PIN),se10_motion_detected,RISING);
}

void loop()
{
    //Check if motion was detected
    if(sen0192_detected)
    {
        sen0192_detected = 0;
        sen0192_motion.record_motion();
        #ifdef DEBUG
        Serial.println("SEN0192 Deteceted a rat!!!");
        #endif
        act_led_state = !act_led_state;
        digitalWrite(ACTIVITY_LED_PIN,act_led_state);
    }
    if(se10_detected)
    {
        se10_detected = 0;
        se10_motion.record_motion();
        #ifdef DEBUG
        Serial.println("SE-10 Deteceted a rat!!!");
        #endif
        act_led_state = !act_led_state;
        digitalWrite(ACTIVITY_LED_PIN,act_led_state);
    }

    //
    // //Send motion occurences
    // if(sen0192_motion.get_count()>0)
    // {
    //     #ifdef DEBUG
    //     sen0192_motion.append_string(&data);
    //     Serial1.println(data);
    //     #endif
    // }
    if(Serial1.available())
    {
        char start_char = Serial1.read();
        if(start_char == (char)REMOTE_START)
        {
            Serial1.write(REMOTE_START);
            Serial1.print(String(sen0192_motion.get_count())+","+String(se10_motion.get_count()));
            Serial1.write(REMOTE_END);
            sen0192_motion.reset_count();
            se10_motion.reset_count();
        }
    }
}

void sen0192_motion_detected(void)
{
        sen0192_detected = 1;
}
void se10_motion_detected(void)
{
        se10_detected = 1;
}
