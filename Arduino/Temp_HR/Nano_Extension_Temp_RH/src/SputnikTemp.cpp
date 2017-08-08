#include "SputnikTemp.h"

Adafruit_MLX90614 mlx;

uint8_t mlx_error;

void temp_init(void)
{
  mlx_error=0;
  mlx = Adafruit_MLX90614();
  mlx.begin();
}
void temp_sensors_check(void)
{
  if(mlx_error)
  {
    mlx.begin();
  }
}
