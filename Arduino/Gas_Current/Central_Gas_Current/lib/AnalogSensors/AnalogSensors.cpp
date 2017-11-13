#include "AnalogSensors.h"

analog_sensor::analog_sensor(uint8_t pin, uint32_t sig_period, uint16_t samp_nr)
{
    uint16_t *_samples_temp = NULL;
    _pin = pin;
    _samp_nr = samp_nr;
    _sig_period = sig_period;
    _delay_us = _sig_period%_samp_nr > 0 ? (_sig_period/_samp_nr + 1) : (_sig_period/_samp_nr);
    _samples_temp = (uint16_t*) malloc (_samp_nr * sizeof(uint16_t));
    if(_samples_temp != NULL)
    {
        _samples = _samples_temp;
        _samples_temp = NULL;
    }
}

analog_sensor::analog_sensor(uint8_t pin, uint16_t samp_nr)
{
    uint16_t *_samples_temp = NULL;
    _pin = pin;
    _samp_nr = samp_nr;
    _sig_period = (uint32_t)DEFAULT_PERIOD;
    _delay_us = _sig_period%_samp_nr > 0 ? (_sig_period/_samp_nr + 1) : (_sig_period/_samp_nr);
    _samples_temp = (uint16_t*) malloc (_samp_nr * sizeof(uint16_t));
  if(_samples_temp != NULL)
  {
      _samples = _samples_temp;
      _samples_temp = NULL;
  }
}

analog_sensor::analog_sensor(uint8_t pin)
{
    uint16_t *_samples_temp = NULL;
    _pin = pin;
    _samp_nr = (uint16_t) DEFAULT_SAMP_NR;
    _sig_period = (uint32_t)DEFAULT_PERIOD;
    _delay_us = _sig_period%_samp_nr > 0 ? (_sig_period/_samp_nr + 1) : (_sig_period/_samp_nr);
    _samples_temp = (uint16_t*) malloc (_samp_nr * sizeof(uint16_t));
    if(_samples_temp != NULL)
    {
     _samples = _samples_temp;
     _samples_temp = NULL;
    }
}

analog_sensor::analog_sensor()
{
    uint16_t *_samples_temp = NULL;
    _pin = A0;
    _samp_nr = (uint16_t) DEFAULT_SAMP_NR;
    _sig_period = (uint32_t)DEFAULT_PERIOD;
    _delay_us = _sig_period%_samp_nr > 0 ? (_sig_period/_samp_nr + 1) : (_sig_period/_samp_nr);
    _samples_temp = (uint16_t*) malloc (_samp_nr * sizeof(uint16_t));
    if(_samples_temp != NULL)
    {
     _samples = _samples_temp;
     _samples_temp = NULL;
    }
}

void analog_sensor::sample_triger(void)
{
    uint16_t i;
    #ifdef FILTER_MANHOSO_ENABLE
    uint8_t filter_cntr = 0;
    uint16_t analog_buff = 0;
    #endif

    _adc_max = 0;
    for(i = 0; i<_samp_nr; i++)
    {
        _samples[i] = analogRead(_pin);
        #ifdef FILTER_MANHOSO_ENABLE
        if(i > 0)
            filter_cntr = (analog_buff == _samples[i])  ;
        if(filter_cntr)
            _adc_max = _adc_max < _samples[i] ? _samples[i] : _adc_max;
        analog_buff = _samples[i];
        #else
        _adc_max = _adc_max < _samples[i] ? _samples[i] : _adc_max;
        #endif
        delayMicroseconds(_delay_us);
        #ifdef SERIAL_DEBUG
        Serial.print("_adc_max: ");
        Serial.println(_adc_max);
        Serial.print("Analog sample[");
        Serial.print(i);
        Serial.print("]: ");
        Serial.println( _samples[i]);
        #endif
    }
    #ifdef SERIAL_DEBUG
    Serial.print("Analog max: ");
    Serial.println( _adc_max);
    #endif
}

void analog_sensor::set_samp_nr(uint16_t samp_nr)
{
    _samp_nr = samp_nr;
}
void analog_sensor::get_last_sampling(uint16_t *samples)
{
    samples = _samples;
}

uint16_t analog_sensor::get_adc_max(void)
{
    return _adc_max;
}
