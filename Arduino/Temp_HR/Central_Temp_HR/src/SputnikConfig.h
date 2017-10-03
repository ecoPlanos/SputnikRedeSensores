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

#ifndef SPUTNIKCONFIG_H_
#define SPUTNIKCONFIG_H_

#include <Arduino.h>

#define SOFTWARE_VERSION      101
#define INITIAL_DELAY         100
#define SENSORS_READ_MIN_INTERVAL 2000     //Sensors read minimum interval (2s)
#define SENSORS_READ_MAX_INTERVAL 1800000  //Sensors read maximum interval (30min)

#define SD_CHIP_SEL           4

#define SD_CARD_DELAY         500
#define SD_MAX_TRIES          3
#define SERIAL_DELAY          500
#define SERIAL_MAX_TRIES      3

#define LOG_SD
#define SERIAL_DEBUG
#define REMOTE_ACTIVE

const String log_file_sufix="Data.csv";
const String config_file_name="SPUTNIK.CFG";

const char* ssid = "SSID";
const char* password = "PASS";

#endif // SPUTNIKCONFIG_H_
