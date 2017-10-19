#include "SputnikTempRH.h"

Adafruit_SHT31 sht31;

uint8_t sht31_error;

void temp_hr_init(void)
{
  sht31_error=0;
  sht31 = Adafruit_SHT31();
  if (sht31.begin(0x44)) // Set to 0x45 for alternate i2c addr
  {
      sht31_error = 0;
  }
  else
  {
      #ifdef LOG_SERIAL
      Serial.println("Couldn't find SHT31");
      #endif
  }
}

void temp_hr_sensors_check(void)
{
  if(sht31_error)
  {
    sht31 = Adafruit_SHT31();
    if (sht31.begin(0x44))    // Set to 0x45 for alternate i2c addr
    {
        sht31_error = 0;
    }
    else
    {
        #ifdef LOG_SERIAL
        Serial.println("Couldn't find SHT31");
        #endif
    }
  }
}
