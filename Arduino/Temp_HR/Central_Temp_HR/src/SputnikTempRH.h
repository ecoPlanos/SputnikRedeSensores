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

#ifndef SPUTNIKTEMPRH_H_
#define SPUTNIKTEMPRH_H_

#include <Wire.h>
////////////////
#include <DHT.h>
#include <Adafruit_SHT31.h>
#include <Sensirion.h>    //SHT75

#define DHT11_PIN            2         // Pin which is connected to the DHT sensor.
#define DHT22_PIN            3         // Pin which is connected to the DHT sensor.
#define SHT75_SCK            5         //
#define SHT75_DATA           6         //
#define THR_LED              25

#define SHT31_OFFSET  0.3

extern DHT dht11, dht22;
extern Adafruit_SHT31 sht31;
extern Sensirion sht75;

extern uint8_t dht11_error,dht22_error,sht31_error,sht75_error;

void temp_hr_init(void);
void temp_hr_sensors_check(void);

#endif // SPUTNIKTEMPRH_H_
