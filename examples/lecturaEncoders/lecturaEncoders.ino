#include <EnableInterrupt.h>
#include "velocistaEdu.h"

VelocistaEdu robot = obtenerRobot();

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  unsigned int encoderDerecho, encoderIzquierdo;
  robot.obtenerCuentaEncoders(encoderIzquierdo, encoderDerecho);
  Serial.print(encoderIzquierdo);
  Serial.print(" ");
  Serial.println(encoderDerecho);
  delay(100);
}
