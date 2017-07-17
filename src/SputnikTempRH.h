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

#define DHT11_PIN            53         // Pin which is connected to the DHT sensor.
#define DHT22_PIN            52         // Pin which is connected to the DHT sensor.
#define SHT75_DATA           50         //
#define SHT75_SCK            51         //
#define THR_LED              25

extern DHT dht11, dht22;
extern Adafruit_SHT31 sht31;
extern Sensirion sht75;

void temp_hr_init(void);

#endif // SPUTNIKTEMPRH_H_
