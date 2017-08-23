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
#include <Adafruit_SHT31.h>

#define SHT31_OFFSET  0

extern Adafruit_SHT31 sht31;

extern uint8_t sht31_error;

void temp_hr_init(void);
void temp_hr_sensors_check(void);

#endif // SPUTNIKTEMPRH_H_
