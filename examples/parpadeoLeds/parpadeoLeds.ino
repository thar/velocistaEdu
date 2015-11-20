#include "velocistaEdu.h"

void setup()
{
  VelocistaEdu::inicializar();
}

void loop()
{
  VelocistaEdu::encenderLed(ROJO);
  VelocistaEdu::apagarLed(VERDE);
  delay(500);
  VelocistaEdu::encenderLed(VERDE);
  VelocistaEdu::apagarLed(ROJO);
  delay(500);
}
