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

#ifndef SPUTNIKGAS_H_
#define SPUTNIKGAS_H_

#include <Arduino.h>
#include <SparkFunCCS811.h>

#define MG811_PIN A0
#define MQ135_PIN A1
#define CCS811_NWAK 47
#define CCS811_NINT 48
#define CCS811_NRST 49
#define CCS811_ADDR 0x5B //Default I2C Address

extern uint16_t mg811_analog;
extern uint16_t mq135_analog;

extern CCS811 ccs811;
//
void sputnikGasInit(void);

#endif
