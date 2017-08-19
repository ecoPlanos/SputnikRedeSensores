#include "SputnikTemp.h"

uint16_t ntc_temp, pt100_analog;
uint8_t ntc_error, mlx_error;

void temp_init(void)
{
  ntc_error=0;
  mlx_error=0;
  pinMode(NTC_PIN,INPUT);
  pinMode(PT100_PIN,INPUT);
}
void temp_sensors_check(void)
{
}
float pt100_resistance(void)
{
  return ((float)pt100_analog-PT100_B)/(PT100_M);
}
float pt100_temperature(void)
{
  return 0.00;  //TODO: implement lookup table
}
