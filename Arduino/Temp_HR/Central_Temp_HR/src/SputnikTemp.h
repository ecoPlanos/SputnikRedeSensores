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

#define NTC_PIN 7
#define PT100_PIN 8

extern uint16_t ntc_temp, pt100_temp;

extern uint8_t ntc_error, mlx_error;

void temp_init(void);
void temp_sensors_check(void);

#endif // SPUTNIKTEMP_H_
