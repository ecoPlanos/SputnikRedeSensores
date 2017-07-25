#include "SputnikTemp.h"

Adafruit_MLX90614 mlx;

SparkFunMAX31855k thermopar;

uint16_t ntc_temp=0;

void temp_init(void)
{
  mlx = Adafruit_MLX90614();
  mlx.begin();
  thermopar = SparkFunMAX31855k();
  thermopar.begin(THERMOPAR_CS, THERMOPAR_VCC);
}
