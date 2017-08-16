#include "SputnikTempRH.h"

DHT dht11, dht22;
Sensirion sht75;

uint8_t dht11_error,dht22_error,sht31_error,sht75_error;

void temp_hr_init(void)
{
  dht11_error=0;
  dht22_error=0;
  sht31_error=0;
  sht75_error=0;
  dht11.begin(DHT11_PIN, DHT11);
  dht22.begin(DHT22_PIN, DHT22);
  sht75.begin(SHT75_DATA, SHT75_SCK);
}

void temp_hr_sensors_check(void)
{
  if(dht11_error)
  {
    dht11.begin(DHT11_PIN, DHT11);
    dht11_error = 0;
  }
  if(dht22_error)
  {
    dht22.begin(DHT22_PIN, DHT22);
    dht22_error = 0;
  }
  if(sht75_error)
  {
    sht75.begin(SHT75_DATA, SHT75_SCK);
    sht75_error = 0;
  }
}
