/*
 * El programa de test de movimiento de ruedas sirve
 * para comprobar que el driver de motores funciona
 * y para saber que las ruedas se mueven en el sentido
 * correcto.
 * Si alguna de las ruedas se mueve en el sentido
 * equivocado descomentar la(s) linea(s) que corresponda(n)
 */
//#define MOTOR_DERECHO_CAMBIAR_POLARIDAD
//#define MOTOR_IZQUIERDO_CAMBIAR_POLARIDAD

#include "velocistaEdu.h"

void setup()
{
  VelocistaEdu::inicializar();
}

void loop()
{
  /* Con led rojo encendido las ruedas se mueven hacia atras */
  VelocistaEdu::establecerVelocidad(-100,-100);
  VelocistaEdu::encenderLed(ROJO);
  VelocistaEdu::apagarLed(VERDE);
  delay(2000);
  /* Con leds apagados las ruedas no se mueven */
  VelocistaEdu::establecerVelocidad(0,0);
  VelocistaEdu::apagarLed(VERDE);
  VelocistaEdu::apagarLed(ROJO);
  delay(2000);
  /* Con led verde encendido las ruedas se mueven hacia delante */
  VelocistaEdu::establecerVelocidad(100,100);
  VelocistaEdu::encenderLed(VERDE);
  VelocistaEdu::apagarLed(ROJO);
  delay(2000);
  /* Con leds apagados las ruedas no se mueven */
  VelocistaEdu::establecerVelocidad(0,0);
  VelocistaEdu::apagarLed(VERDE);
  VelocistaEdu::apagarLed(ROJO);
  delay(2000);
}
