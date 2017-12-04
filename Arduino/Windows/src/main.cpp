// Copyright (c) 2017 by ecoPlanos. All Rights Reserved.
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
#include <SPI.h>
#include <math.h>
#include "Ultrasonic.h"
#include "SparkFunLIS3DH.h"
#include "I2Cdev.h"
#include "ITG3200.h"
#include "SparkFunLIS3DH.h"

// #define DEBUG
// #define DEBUG_MOTION

#define WINDOWS_START   0xFC
#define REMOTE_END      0xFF
#if defined (__arm__)
#define Serial_data     Serial1
#elif defined(__AVR_ATmega328P__)
#define Serial_data     Serial
#endif

#define ACQUISITION_T   500
#define SENSORS_READ_TIMEOUT   50

#if defined (__arm__)
#define ANALOG_READ_RESOLUTION 12
#define ANALOG_MAX             4095
#elif defined(__AVR_ATmega328P__)
#define ANALOG_READ_RESOLUTION 10
#define ANALOG_MAX             1023
#endif

#if defined (__arm__)

#elif defined(__AVR_ATmega328P__)
#define HCSRO4_TRIG_PIN  6
#define HCSRO4_ECHO_PIN  7
#define URM37_TRIG_PIN   8
#define URM37_ECHO_PIN   9
#define LV_EZ_AN_PIN    A0
#define LV_EZ_RX_PIN    11
#define LV_EZ_PWM_PIN   15
#define ITG3200_DREADY_PIN 9
#define REED_BLACK_PIN 2
#define REED_WHITE_PIN 3
#define REED_WHITE_SMALL_PIN 4
#endif

#define ITG3200_X_DETECT_THRESHOLD  128
#define ITG3200_Y_DETECT_THRESHOLD  64
#define ITG3200_Z_DETECT_THRESHOLD  16

#define LIS3DH_X_DETECT_THRESHOLD   0.4
#define LIS3DH_Y_DETECT_THRESHOLD   0.4
#define LIS3DH_Z_DETECT_THRESHOLD   0.4

#define ACTIVITY_LED_PIN 13

String serial_data_string;
uint32_t millis_start, millis_end, setup_time, acquisition_time, temp_millis, temp_delay, delay_ms;
uint8_t act_led_state = 0;
char serial_comand;

float hcsro4_dist_cm, urm37_dist_cm,lv_ez_dist_cm;
uint16_t lv_ez_analog;

ITG3200 itg3200;

int16_t itg3200_gx, itg3200_gy, itg3200_gz;
uint8_t itg3200_error, lis3dh_error;
volatile uint8_t itg3200_data_ready;
uint8_t itg3200_detected_x = false, itg3200_detected_y = false, itg3200_detected_z = false;

LIS3DH lis3dh;
int16_t lis3dh_ax_raw, lis3dh_ay_raw, lis3dh_az_raw;
float lis3dh_ax, lis3dh_ay, lis3dh_az;
uint8_t lis3dh_detected_x = false, lis3dh_detected_y = false, lis3dh_detected_z = false;
uint32_t itg3200_x_move_count = 0, itg3200_y_move_count = 0, itg3200_z_move_count = 0, lis3dh_x_move_count = 0, lis3dh_y_move_count = 0, lis3dh_z_move_count = 0;

uint8_t reed_black_detected, reed_white_detected, reed_white_small_detected;

void itg3200_dready(void);
void itg3200_update(void);
void itg3200_detect(void);
void lis3dh_detect(void);
void sensors_awake(void);
void sensors_sleep(void);
uint32_t ultrasound_timing(uint8_t trig, uint8_t echo);

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

    pinMode(HCSRO4_ECHO_PIN, INPUT);
    pinMode(HCSRO4_TRIG_PIN, OUTPUT);
    pinMode(URM37_ECHO_PIN, INPUT);
    pinMode(URM37_TRIG_PIN, OUTPUT);
    pinMode(LV_EZ_RX_PIN, OUTPUT);
    pinMode(LV_EZ_PWM_PIN, INPUT);
    pinMode(LV_EZ_AN_PIN, INPUT);
    pinMode(ITG3200_DREADY_PIN, INPUT);
    pinMode(REED_BLACK_PIN, INPUT);
    pinMode(REED_WHITE_PIN, INPUT);
    pinMode(REED_WHITE_SMALL_PIN, INPUT);
#if defined (__arm__)
    analogReadResolution(ANALOG_READ_RESOLUTION);
#endif

    sensors_awake();

    itg3200.setClockSource(ITG3200_CLOCK_INTERNAL);
    itg3200.setFullScaleRange(ITG3200_FULLSCALE_2000);
    itg3200.setDLPFBandwidth(ITG3200_DLPF_BW_256);
    itg3200.setInterruptMode(ITG3200_INTMODE_ACTIVEHIGH);
    itg3200.setInterruptDrive(ITG3200_INTDRV_PUSHPULL);
    itg3200.setInterruptLatch(ITG3200_INTLATCH_50USPULSE);
#ifdef INTERRUPTS_ACTIVE
    itg3200.setIntDataReadyEnabled(true);
    attachInterrupt(digitalPinToInterrupt(ITG3200_DREADY_PIN),itg3200_dready,RISING);
#else
    itg3200.setIntDataReadyEnabled(false);
#endif
    itg3200_error = !itg3200.testConnection();
    itg3200_data_ready = false;

#ifdef DEBUG
    Serial.println("Testing ITG-3200 connection...");
    Serial.println(itg3200_error ?  "ITG3200 connection failed" : "ITG3200 connection successful");
#endif

    lis3dh.settings.adcEnabled = false;
    lis3dh.settings.tempEnabled = true;
    lis3dh.settings.accelSampleRate = 10;
    lis3dh.settings.accelRange = 2;
    lis3dh.settings.xAccelEnabled = true;
    lis3dh.settings.yAccelEnabled = true;
    lis3dh.settings.zAccelEnabled = true;
    lis3dh.settings.fifoEnabled = false;
    lis3dh_error = lis3dh.begin();
    lis3dh_error = (lis3dh_error == IMU_SUCCESS) ?  false : true;

    delay_ms = ACQUISITION_T;

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

    delay(500);
}

void loop()
{
    millis_start = millis();
    String serial_data_string = "";
    sensors_awake();
    delay(50);

#ifdef DEBUG
    Serial.println("------------------------------------");
    Serial.println("--------------Distance--------------");
    Serial.println("------------------------------------");
#endif

    uint32_t pulse_duration = 0;

    hcsro4_dist_cm =((float)ultrasound_timing(HCSRO4_TRIG_PIN,HCSRO4_ECHO_PIN ))/58.0;

    digitalWrite(URM37_TRIG_PIN,LOW);
    delayMicroseconds(10);
    digitalWrite(URM37_TRIG_PIN,HIGH);
    // pulse_duration = pulseIn(URM37_ECHO_PIN, HIGH, SENSORS_READ_TIMEOUT);
    pulse_duration = pulseIn(URM37_ECHO_PIN, LOW);
#ifdef DEBUG
    Serial.print("URM37 pulse duration: ");
    Serial.println(pulse_duration);
#endif
    if(pulse_duration == 50000)
    {
#ifdef DEBUG
        Serial.println("Error reading URM37 sensor!");
#endif
    }
    else
    {
        urm37_dist_cm = ((float)pulse_duration)/50.0;
    }
    digitalWrite(LV_EZ_RX_PIN, HIGH);
    delayMicroseconds(30);
    digitalWrite(LV_EZ_RX_PIN, LOW);
    // pulse_duration = pulseIn(LV_EZ_PWM_PIN, HIGH, SENSORS_READ_TIMEOUT);
    pulse_duration = pulseIn(LV_EZ_PWM_PIN, HIGH);
    lv_ez_dist_cm =  ((float)pulse_duration)/58.0;
    lv_ez_analog = analogRead(LV_EZ_AN_PIN);
#ifdef DEBUG
    Serial.print("HC-SRO4 distance (cm): ");
    Serial.println(hcsro4_dist_cm);
    Serial.print("URM37 distance (cm): ");
    Serial.println(urm37_dist_cm);
    Serial.print("LV-EZ distance (cm): ");
    Serial.println(lv_ez_dist_cm);
    Serial.print("LV-EZ (mv): ");
    Serial.println((float)lv_ez_analog*3300/(float)ANALOG_MAX);
#endif

    serial_data_string+=String(hcsro4_dist_cm,2)+","+String(urm37_dist_cm,2)+","+String(lv_ez_dist_cm,2)+","+String((float)lv_ez_analog*3300/(float)ANALOG_MAX,2);

#ifdef DEBUG
    Serial.println("------------------------------------");
    Serial.println("---------------Motion---------------");
    Serial.println("------------------------------------");
#endif
    if(!itg3200_error)
    {
#ifdef INTERRUPTS_ACTIVE
        if(itg3200_data_ready)
        {
            itg3200.getRotation(&itg3200_gx, &itg3200_gy, &itg3200_gz);
            itg3200_data_ready = false;
        }
#else
        itg3200_detect();
#endif
#ifdef DEBUG
        Serial.print("ITG-3200 rotation (x, y, z): ");
        Serial.print(itg3200_gx); Serial.print(", ");
        Serial.print(itg3200_gy); Serial.print(", ");
        Serial.println(itg3200_gz);
#endif

        serial_data_string+=","+String(itg3200_gx)+","+String(itg3200_gy)+","+String(itg3200_gz)+","+String(itg3200_x_move_count)+","+String(itg3200_y_move_count)+","+String(itg3200_z_move_count)+","+String(uint8_t(itg3200_detected_x|itg3200_detected_y|itg3200_detected_z));
        itg3200_detected_x = false;
        itg3200_detected_y = false;
        itg3200_detected_z = false;
    }
    else
    {
        serial_data_string+=",,,,,,";
    }
    if(!lis3dh_error)
    {
        lis3dh_detect();

#ifdef DEBUG
        Serial.print("LIS3DH acceleration (x, y, z): ");
        Serial.print(lis3dh_ax,4); Serial.print(", ");
        Serial.print(lis3dh_ay,4); Serial.print(", ");
        Serial.println(lis3dh_az,4);
        Serial.print("LIS3DH acceleration RAW (x, y, z): ");
        Serial.print(lis3dh_ax_raw); Serial.print(", ");
        Serial.print(lis3dh_ay_raw); Serial.print(", ");
        Serial.println(lis3dh_az_raw);
#endif

        serial_data_string+=","+String(lis3dh_ax,4)+","+String(lis3dh_ay,4)+","+String(lis3dh_az,4)+","+String(lis3dh_x_move_count)+","+String(lis3dh_y_move_count)+","+String(lis3dh_z_move_count)+","+String(uint8_t(lis3dh_detected_x|lis3dh_detected_y|lis3dh_detected_z));
        lis3dh_detected_x = false;
        lis3dh_detected_y = false;
        lis3dh_detected_z = false;
    }
    else
    {
        serial_data_string+=",,,,,,";
    }

#ifdef DEBUG
    Serial.println("------------------------------------");
    Serial.println("----------------REED----------------");
    Serial.println("------------------------------------");
#endif
    reed_black_detected = digitalRead(REED_BLACK_PIN);
    reed_white_detected = digitalRead(REED_WHITE_PIN);
    reed_white_small_detected = digitalRead(REED_WHITE_SMALL_PIN);
#ifdef DEBUG
    Serial.print("Reed sensor 1 (black): ");
    Serial.println(reed_black_detected);
    Serial.print("Reed sensor 2 (white): ");
    Serial.println(reed_white_detected);
    Serial.print("Reed sensor 3 (white small): ");
    Serial.println(reed_white_small_detected);
#endif
    serial_data_string+=","+String(reed_black_detected)+","+String(reed_white_detected)+","+String(reed_white_small_detected);

    sensors_sleep();
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
    while((Serial_data.available()<=0)&&(temp_delay<(delay_ms-200)))
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
    while(Serial_data.available())
    {
        serial_comand = Serial_data.read();
        if(serial_comand == (char)WINDOWS_START)
        {
            Serial_data.write(WINDOWS_START);
            Serial_data.print(serial_data_string);
            Serial_data.write(REMOTE_END);
            itg3200_x_move_count = 0;
            itg3200_y_move_count = 0;
            itg3200_z_move_count = 0;
            lis3dh_x_move_count = 0;
            lis3dh_y_move_count = 0;
            lis3dh_z_move_count = 0;
        }
    }
    while(temp_delay<(delay_ms-50)) //check for accel/gyro movement detection
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
        itg3200_detect();
        lis3dh_detect();
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
    digitalWrite(ACTIVITY_LED_PIN,LOW);
    delay(temp_delay);

}

void sensors_awake(void)
{
    itg3200.setSleepEnabled(false);
}
void sensors_sleep(void)
{
    itg3200.setSleepEnabled(true);
}

uint32_t ultrasound_timing(uint8_t trig, uint8_t echo)
{
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    // return pulseIn(echo, HIGH, SENSORS_READ_TIMEOUT); // duration
    return pulseIn(echo, HIGH); // duration
}

void itg3200_dready(void)
{
    itg3200_data_ready = true;
}

void itg3200_update(void)
{
    if(itg3200_data_ready)
    {
        itg3200.getRotation(&itg3200_gx, &itg3200_gy, &itg3200_gz);
        itg3200_data_ready = false;
    }
}

void itg3200_detect(void)
{
    int16_t itg3200_gx_temp, itg3200_gy_temp, itg3200_gz_temp;
    itg3200.getRotation(&itg3200_gx_temp, &itg3200_gy_temp, &itg3200_gz_temp);
    if(!(itg3200_detected_x|itg3200_detected_y|itg3200_detected_z))
    {
        if((itg3200_gx_temp != 0) && (itg3200_gy_temp != 0) && (itg3200_gz_temp != 0))
        {
            itg3200_detected_x = (abs(abs(itg3200_gx_temp)-abs(itg3200_gx)) > ITG3200_X_DETECT_THRESHOLD);
            itg3200_detected_y = (abs(abs(itg3200_gy_temp)-abs(itg3200_gy)) > ITG3200_Y_DETECT_THRESHOLD);
            itg3200_detected_z = (abs(abs(itg3200_gz_temp)-abs(itg3200_gz)) > ITG3200_Z_DETECT_THRESHOLD);

            itg3200_gx = itg3200_gx_temp;
            itg3200_gy = itg3200_gy_temp;
            itg3200_gz = itg3200_gz_temp;

            itg3200_x_move_count += itg3200_detected_x;
            itg3200_y_move_count += itg3200_detected_y;
            itg3200_z_move_count += itg3200_detected_z;
        }
    }
#ifdef DEBUG_MOTION
    Serial.println(String(millis())+","+String(itg3200_gx)+","+String(itg3200_gy)+","+String(itg3200_gz)+","+String(itg3200_x_move_count)+","+String(itg3200_y_move_count)+","+String(itg3200_z_move_count)+","+String(uint8_t(itg3200_detected_x|itg3200_detected_y|itg3200_detected_z))+",,,,,,,");
#endif
}
void lis3dh_detect(void)
{
    int16_t lis3dh_ax_temp = lis3dh.readRawAccelX();
    int16_t lis3dh_ay_temp = lis3dh.readRawAccelY();
    int16_t lis3dh_az_temp = lis3dh.readRawAccelZ();
    if(!(lis3dh_detected_x|lis3dh_detected_y|lis3dh_detected_z))
    {
        if(!((lis3dh_ax_temp == 0) && (lis3dh_ay_temp == 0) && (lis3dh_az_temp == 0)))
        {
            lis3dh_detected_x = (abs(abs(lis3dh_ax_temp)-abs(lis3dh_ax)) > (float)LIS3DH_X_DETECT_THRESHOLD);
            lis3dh_detected_y = (abs(abs(lis3dh_ay_temp)-abs(lis3dh_ay)) > (float)LIS3DH_Y_DETECT_THRESHOLD);
            lis3dh_detected_z = (abs(abs(lis3dh_az_temp)-abs(lis3dh_az)) > (float)LIS3DH_Z_DETECT_THRESHOLD);

            lis3dh_ax = lis3dh.readFloatAccelX();
            lis3dh_ay = lis3dh.readFloatAccelY();
            lis3dh_az = lis3dh.readFloatAccelZ();
            lis3dh_ax_raw = lis3dh_ax_temp;
            lis3dh_ay_raw = lis3dh_ay_temp;
            lis3dh_az_raw = lis3dh_az_temp;

            lis3dh_x_move_count += lis3dh_detected_x;
            lis3dh_y_move_count += lis3dh_detected_y;
            lis3dh_z_move_count += lis3dh_detected_z;
        }
    }
#ifdef DEBUG_MOTION
    Serial.println(String(millis())+",,,,,,,,"+String(lis3dh_ax_raw)+","+String(lis3dh_ay_raw)+","+String(lis3dh_az_raw)+","+String(lis3dh_x_move_count)+","+String(lis3dh_y_move_count)+","+String (lis3dh_z_move_count)+","+String(uint8_t(lis3dh_detected_x|lis3dh_detected_y|lis3dh_detected_z)));
#endif
}
