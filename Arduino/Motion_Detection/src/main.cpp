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

// #define DEBUG

#define MOTION_START 0xFE
#define REMOTE_END 0xFF

#define SEN0192_INT_PIN A2
#define SE10_INT_PIN A0
#define ZRE200GE_AN_PIN A7
#define EKMB_INT_PIN 6
#define SEN0192_MIN_PULSE_WIDTH 5
#define SE10_MIN_PULSE_WIDTH 5
#define SEN0192_ID 0
#define SE10_ID 1
#define ZRE200GE_ID 2
#define EKMB_ID 3
#define ZRE200GE_DC_OFFSET 2308
#define ZRE200GE_DETECT_T 500
#define ZRE200GE_THRESHOLD 120

#define ACTIVITY_LED_PIN 13


class Motion {
    uint8_t _sensor_id;
    uint32_t _cntr;
    uint8_t _overflow;
  public:
    void init(uint8_t sensor_id);
    void record_motion(void);
    void reset_count(void);
    uint32_t get_count(void) {return _cntr;}
};

void Motion::init(uint8_t sensor_id)
{
    uint32_t i = 0;
    _sensor_id = sensor_id;
    _cntr = 0;
    _overflow = 0;
}
void Motion::record_motion(void)
{
    _cntr++;
}

void Motion::reset_count(void)
{
    _cntr = 0;
}

uint8_t total_sensors = 4;
Motion sen0192_motion, se10_motion, zre200ge_motion, ekmb_motion;
String serial_data_string;
uint8_t act_led_state = 0;

uint32_t zre200ge_detect_millis = 0;

volatile uint8_t sen0192_detected, se10_detected,zre200ge_detected,ekmb_detected;

void sen0192_motion_detected(void);
void se10_motion_detected(void);
void ekmb_motion_detected(void);

void setup()
{
    #ifdef DEBUG
    Serial.begin(115200);
    #endif
    Serial1.begin(9600); //XBee com port
    analogReadResolution(12);
    pinMode(SEN0192_INT_PIN, INPUT);
    pinMode(SE10_INT_PIN, INPUT);
    pinMode(EKMB_INT_PIN, INPUT);
    pinMode(ZRE200GE_AN_PIN, INPUT);
    pinMode(ACTIVITY_LED_PIN, OUTPUT);
    sen0192_detected = 0;
    se10_detected = 0;
    sen0192_motion.init(SEN0192_ID);
    se10_motion.init(SE10_ID);
    zre200ge_motion.init(ZRE200GE_ID);
    ekmb_motion.init(EKMB_ID);
    attachInterrupt(digitalPinToInterrupt(SEN0192_INT_PIN),sen0192_motion_detected,FALLING);
    attachInterrupt(digitalPinToInterrupt(SE10_INT_PIN),se10_motion_detected,RISING);
    attachInterrupt(digitalPinToInterrupt(EKMB_INT_PIN),ekmb_motion_detected,RISING);
}

void loop()
{
    //Check if motion was detected
    uint16_t zre200ge_an_tmp = analogRead(ZRE200GE_AN_PIN);
    if((zre200ge_an_tmp > (ZRE200GE_DC_OFFSET + ZRE200GE_THRESHOLD)) || (zre200ge_an_tmp < (ZRE200GE_DC_OFFSET - ZRE200GE_THRESHOLD)))
    {
        if(millis()-zre200ge_detect_millis >= ZRE200GE_DETECT_T)
        {
            zre200ge_detect_millis = millis();
            zre200ge_detected = 1;
        }
    }
    // #ifdef DEBUG
    // Serial.println(zre200ge_an_tmp);
    // #endif
    // delay(1000);
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
    if(zre200ge_detected)
    {
        zre200ge_detected = 0;
        zre200ge_motion.record_motion();
        #ifdef DEBUG
        Serial.println("ZRE200GE Deteceted a rat!!!");
        #endif
        act_led_state = !act_led_state;
        digitalWrite(ACTIVITY_LED_PIN,act_led_state);
    }
    if(ekmb_detected)
    {
        ekmb_detected = 0;
        ekmb_motion.record_motion();
        #ifdef DEBUG
        Serial.println("EKMB1101111 Deteceted a rat!!!");
        #endif
        act_led_state = !act_led_state;
        digitalWrite(ACTIVITY_LED_PIN,act_led_state);
    }

    while(Serial1.available())
    {
        char start_char = Serial1.read();
        if(start_char == (char)MOTION_START)
        {
            Serial1.write(MOTION_START);
            Serial1.print(String(sen0192_motion.get_count())+","+String(se10_motion.get_count())+","+String(zre200ge_motion.get_count())+","+String(ekmb_motion.get_count()));
            Serial1.write(REMOTE_END);
            sen0192_motion.reset_count();
            se10_motion.reset_count();
            zre200ge_motion.reset_count();
            ekmb_motion.reset_count();
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
void ekmb_motion_detected(void)
{
        ekmb_detected = 1;
}
