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

#ifndef ANALOGSENSORS_h
#define ANALOGSENSORS_h

#include <Arduino.h>
#include <stdlib.h>

#define DEFAULT_PERIOD 20000
#define DEFAULT_SAMP_NR 200
#define RMS_FACTOR 1,414213562

// #define FILTER_MANHOSO_ENABLE

// #define SERIAL_DEBUG

class analog_sensor
{
    public:
        analog_sensor(uint8_t pin, uint32_t sig_period, uint16_t samp_nr);
        analog_sensor(uint8_t pin, uint16_t samp_nr);
        analog_sensor(uint8_t pin);
        analog_sensor();
        void sample_triger(void);
        void set_samp_nr(uint16_t samp_nr);
        void get_last_sampling(uint16_t *samples);
        uint16_t get_adc_max(void);
        uint16_t get_analog_min(void);
    private:
        uint8_t _pin;
        uint16_t *_samples;
        uint16_t _samp_nr;
        uint32_t _sig_period;
        uint32_t _delay_us;
        uint16_t _adc_max;
        uint16_t _analog_min;
};

#endif
