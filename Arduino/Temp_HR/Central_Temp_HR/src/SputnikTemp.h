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

#ifndef SPUTNIKTEMP_H_
#define SPUTNIKTEMP_H_

#include <Arduino.h>

#define NTC_PIN A1
#define PT100_PIN A8
#define PT100_ANALOG_VALUE_1124 420  //Measured for a 112.4 homs resistor (1.38V)
#define PT100_ANALOG_VALUE_0    76   //Measured for 0ºC
#define PT100_RESISTANCE_0    100
#define NTC_SERIAL_RESISTOR 9980

const float VCC_TRUE = 3.28;
const float VCC = 3.3;
const float PT100_RESISTANCE_1124 = 112.4;
const float PT100_M = 27.742;
const float PT100_B = -2698.2;

extern uint16_t ntc_analog, pt100_analog;

extern uint8_t ntc_error, mlx_error;

void temp_init(void);
void temp_sensors_check(void);
float pt100_resistance(void);
float pt100_temperature(void);
float ntc_resistance(void);

#endif // SPUTNIKTEMP_H_
