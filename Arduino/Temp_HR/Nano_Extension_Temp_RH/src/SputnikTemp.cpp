#include "SputnikTemp.h"

Adafruit_MLX90614 mlx;
// SparkFunMAX31855k thermopar;

uint8_t mlx_error, thermopar_error;

void temp_init(void)
{
  mlx_error=0;
  mlx = Adafruit_MLX90614();
  mlx.begin();

  // thermopar = SparkFunMAX31855k();
  // thermopar.begin(THERMOPAR_CS, THERMOPAR_VCC);
}
void temp_sensors_check(void)
{
  if(mlx_error)
  {
    mlx.begin();
  }
}
