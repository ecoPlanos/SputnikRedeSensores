#include "SputnikCurrent.h"

analog_sensor acs770, acs712, pa3208, sct013;

void sputnikCurrentInit(void)
{
  acs770 = analog_sensor(ACS770_PIN);
  acs712 = analog_sensor(ACS712_PIN);
  pa3208 = analog_sensor(PA3208_PIN);
  sct013 = analog_sensor(SCT013_PIN);
  pinMode(ACS770_PIN,INPUT);
  pinMode(ACS712_PIN,INPUT);
  pinMode(PA3208_PIN,INPUT);
  pinMode(SCT013_PIN,INPUT);
}