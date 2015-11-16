#include "velocistaEdu.h"

void setup()
{
  VelocistaEdu::inicializar();
}

void loop()
{
  VelocistaEdu::encenderLed(LED1);
  VelocistaEdu::apagarLed(LED2);
  delay(500);
  VelocistaEdu::encenderLed(LED2);
  VelocistaEdu::apagarLed(LED1);
  delay(500);
}
