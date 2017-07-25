/***************************************************
  This is a library for the MLX90614 Temp Sensor

  Designed specifically to work with the MLX90614 sensors in the
  adafruit shop
  ----> https://www.adafruit.com/products/1748
  ----> https://www.adafruit.com/products/1749

  These sensors use I2C to communicate, 2 pins are required to
  interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include "Adafruit_MLX90614.h"

#define KELVIN_CELSIUS 273.15

Adafruit_MLX90614::Adafruit_MLX90614(uint8_t i2caddr) {
  _addr = i2caddr;
}


boolean Adafruit_MLX90614::begin(void) {
  Wire.begin();

  /*
  for (uint8_t i=0; i<0x20; i++) {
    Serial.print(i); Serial.print(" = ");
    Serial.println(read16(i), HEX);
  }
  */
  return true;
}

//////////////////////////////////////////////////////

double Adafruit_MLX90614::readObjectTempC(void) {
  return (double)(readTemp(MLX90614_TOBJ1)-KELVIN_CELSIUS);
}


double Adafruit_MLX90614::readAmbientTempC(void) {
  return (double)(readTemp(MLX90614_TA)-KELVIN_CELSIUS);
}

double Adafruit_MLX90614::readObjectTempF(void) {
  return (((readTemp(MLX90614_TOBJ1)-KELVIN_CELSIUS) * 9 / 5) + 32);
}


double Adafruit_MLX90614::readAmbientTempF(void) {
  return (((readTemp(MLX90614_TA)-KELVIN_CELSIUS) * 9 / 5) + 32);
}

float Adafruit_MLX90614::readObjectTempK(void) {
  return readTemp(MLX90614_TOBJ1);
}


float Adafruit_MLX90614::readAmbientTempK(void) {
  return readTemp(MLX90614_TA);
}

float Adafruit_MLX90614::readTemp(uint8_t reg) {
  return (float)(read16(reg)*0.02);
}

uint8_t crc8(uint8_t *p, uint8_t len)
{
  uint16_t i;
  uint16_t crc = 0x0;

  while (len--) {
          i = (crc ^ *p++) & 0xFF;
          crc = (crc_table[i] ^ (crc << 8)) & 0xFF;
  }

  return crc & 0xFF;
}

/*********************************************************************/

uint16_t Adafruit_MLX90614::read16(uint8_t a) {
  uint16_t ret = 0x0000;
  uint8_t pec = 0;

#ifdef _VARIANT_ARDUINO_DUE_X_
  uint8_t n = Wire.requestFrom((uint8_t)_addr, (uint8_t)3, (uint32_t)a, (uint8_t)1, (uint8_t)1);// send data n-bytes read
#else
  Wire.beginTransmission(_addr); // start transmission to device
  Wire.write(a); // sends register address to read from
  Wire.endTransmission(false); // end transmission
  uint8_t n = Wire.requestFrom((uint8_t)_addr, (uint8_t)3);
#endif
  // delay(10);
  if(n == 3) {
    ret = Wire.read(); // receive DATA
    ret |= (Wire.read() << 8); // receive DATA
    pec = Wire.read();
  }

  return ret;
}
