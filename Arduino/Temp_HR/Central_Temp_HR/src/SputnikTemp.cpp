#include "SputnikTemp.h"

Adafruit_MLX90614 mlx;
SparkFunMAX31855k thermopar;

uint16_t ntc_temp, pt100_temp;
uint8_t ntc_error, mlx_error, thermopar_error;

void temp_init(void)
{
  ntc_error=0;
  mlx_error=0;
  mlx = Adafruit_MLX90614();
  mlx.begin();
  pinMode(NTC_PIN,INPUT);
  pinMode(PT100_PIN,INPUT);
  thermopar = SparkFunMAX31855k();
  thermopar.begin(THERMOPAR_CS, THERMOPAR_VCC);
}
void temp_sensors_check(void)
{
  if(mlx_error)
  {
    mlx.begin();
  }
}
