#include <EnableInterrupt.h>
#include "velocistaEdu.h"

/*
 * El programa de test de movimiento de ruedas sirve
 * para comprobar que el driver de motores funciona
 * y para saber que las ruedas se mueven en el sentido
 * correcto.
 * Si alguna de las ruedas se mueve en el sentido
 * equivocado hay que indicarle al constructor de robot
 * la(s) rueda(s) que gira(n) en sentido contrario
 *
 * Si la rueda izquierda gira en sentido contrario:
 * VelocistaEdu robot = obtenerRobot(true, false);
 *
 * Si la rueda derecha gira en sentido contrario:
 * VelocistaEdu robot = obtenerRobot(false, true);
 *
 * Si ambas ruedas giran en sentido contrario:
 * VelocistaEdu robot = obtenerRobot(true, true);
 */
VelocistaEdu robot = obtenerRobot();

void setup()
{
}

void loop()
{
  /* Con led rojo encendido las ruedas se mueven hacia atras */
  robot.establecerVelocidad(-100,-100);
  robot.encenderLed(ROJO);
  robot.apagarLed(VERDE);
  delay(2000);
  /* Con leds apagados las ruedas no se mueven */
  robot.establecerVelocidad(0,0);
  robot.apagarLed(VERDE);
  robot.apagarLed(ROJO);
  delay(2000);
  /* Con led verde encendido las ruedas se mueven hacia delante */
  robot.establecerVelocidad(100,100);
  robot.encenderLed(VERDE);
  robot.apagarLed(ROJO);
  delay(2000);
  /* Con leds apagados las ruedas no se mueven */
  robot.establecerVelocidad(0,0);
  robot.apagarLed(VERDE);
  robot.apagarLed(ROJO);
  delay(2000);
}
