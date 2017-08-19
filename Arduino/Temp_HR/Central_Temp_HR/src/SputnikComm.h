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

#ifndef SPUTNIKCOMM_H_
#define SPUTNIKCOMM_H_

#include <Arduino.h>

#define REMOTE_START 0xFE
#define REMOTE_END 0xFF

extern uint8_t remote_buff[32];
extern uint8_t serial_char;
extern uint8_t serial_error;
// extern String remote_buff;

#endif // SPUTNIKCOMM_H_
