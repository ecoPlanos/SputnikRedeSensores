#include "SputnikTempRH.h"

void temp_hr_init(void)
{
  dht11.begin(DHT11_PIN, DHT11);
  dht22.begin(DHT22_PIN, DHT22);
  sht31 = Adafruit_SHT31();
  sht75.begin(SHT75_DATA, SHT75_SCK);
}
