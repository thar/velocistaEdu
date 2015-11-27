#include <EnableInterrupt.h>
#include "velocistaEdu.h"

VelocistaEdu robot = obtenerRobot();

void setup()
{
}

void loop()
{
  robot.encenderLed(ROJO);
  robot.apagarLed(VERDE);
  delay(500);
  robot.encenderLed(VERDE);
  robot.apagarLed(ROJO);
  delay(500);
}
