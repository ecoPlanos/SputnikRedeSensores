#include "SputnikGas.h"

uint16_t mg811_analog;
uint16_t mq135_analog;
CCS811 ccs811(CCS811_ADDR);
uint8_t ccs811_present = 0;

void sputnikGasInit(void)
{
  //  Initialize MG811 - CO2
  pinMode(MG811_PIN,INPUT);
  //  Initialize CCS811 - CO2
  pinMode(CCS811_NWAK,OUTPUT);
  pinMode(CCS811_NINT,INPUT);
  pinMode(CCS811_NRST,OUTPUT);    //reset pin (active High)
  digitalWrite(CCS811_NWAK,LOW);
  digitalWrite(CCS811_NRST,LOW);  //reset pin (active High)
  delayMicroseconds(50);          //Wait for turn on (min 20us)
  digitalWrite(CCS811_NRST,HIGH); //assert reset
  delayMicroseconds(20);          //Make sure awake pin can be asserted any time from now (min 20us)
  //Init sensor
  ccs811.begin();
  ccs811_present = 2;
}
void sputnikGasInit(Stream *Serial)
{
  //  Initialize MG811 - CO2
  pinMode(MG811_PIN,INPUT);
  //  Initialize CCS811 - CO2
  pinMode(CCS811_NWAK,OUTPUT);
  pinMode(CCS811_NINT,INPUT);
  pinMode(CCS811_NRST,OUTPUT);    //reset pin (active High)
  digitalWrite(CCS811_NWAK,LOW);
  digitalWrite(CCS811_NRST,LOW);  //reset pin (active High)
  delayMicroseconds(50);          //Wait for turn on (min 20us)
  digitalWrite(CCS811_NRST,HIGH); //assert reset
  delayMicroseconds(20);          //Make sure awake pin can be asserted any time from now (min 20us)
  //Init sensor
  if (ccs811.begin() != CCS811Core::SENSOR_SUCCESS)
  {
    #ifdef LOG_SERIAL
    Serial->println("Couldn't find CCS811");
    #endif
  }
  else
    ccs811_present = 1;
    Serial->println("CCS811 OK!!!");
}
