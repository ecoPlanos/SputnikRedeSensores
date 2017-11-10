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

#ifndef SPUTNIKCURRENT_H_
#define SPUTNIKCURRENT_H_

#include <Arduino.h>
#include <AnalogSensors.h>

#define ACS770_PIN A0
#define ACS712_PIN A1
#define PA3208_PIN A2
#define SCT013_PIN A3

extern analog_sensor acs770, acs712, pa3208, sct013;
void sputnikCurrentInit(void);

#endif
