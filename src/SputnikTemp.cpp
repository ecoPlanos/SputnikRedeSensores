#include "SputnikTemp.h"

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void temp_init(void)
{
  mlx = Adafruit_MLX90614();
}
