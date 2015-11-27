#include <EnableInterrupt.h>
#include "velocistaEdu.h"

VelocistaEdu robot = obtenerRobot();

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  unsigned int s[4];
  robot.actualizarSensoresLinea();
  robot.obtenerSensoresLinea(s);
  char rawDataString[20];
  sprintf(rawDataString, "%d %d %d %d", s[0], s[1], s[2], s[3]);
  Serial.println(rawDataString);
  delay(100);
}
