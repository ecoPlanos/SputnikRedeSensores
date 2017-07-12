#include "SputnikTemp.h"

Adafruit_MLX90614 mlx;

void temp_init(void)
{
  mlx = Adafruit_MLX90614();
}
