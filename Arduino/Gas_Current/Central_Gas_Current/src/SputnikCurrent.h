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

#define RMS_FACTOR 1.414213562

#define ACS770_AVG_335 2773
#define ACS770_CAL_MIN 0
#define ACS770_CAL_MAX 4095
#define ACS712_AVG_335 3208
#define ACS712_CAL_MIN 3
#define ACS712_CAL_MAX 4095
#define PA3208_AVG_335 2376
#define PA3208_CAL_MIN 0
#define PA3208_CAL_MAX 4095
#define SCT013_AVG_335 3448
#define SCT013_CAL_MIN 2078
#define SCT013_CAL_MAX 4095

#include <Arduino.h>
#include <AnalogSensors.h>

#define ACS770_PIN A0
#define ACS712_PIN A1
#define PA3208_PIN A2
#define SCT013_PIN A3

extern analog_sensor acs770, acs712, pa3208, sct013;
extern float_t acs770_current_rms, acs712_current_rms, pa3208_current_rms, sct013_current_rms;
void sputnikCurrentInit(void);

#endif
