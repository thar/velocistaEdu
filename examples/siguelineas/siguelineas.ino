#include <EnableInterrupt.h>
#include "velocistaEdu.h"

int error = 0;
int errorAnterior = 0;

/* Ajustar kp y kd para que el robot no oscile */
int kp = 30;
int kd = 5;

/* Aumentar pwmParteComun para que el robot vaya mas rapido */
int pwmParteComun = 25;
int pwmParteDiferencial = 0;

bool estoyEncendido = false;

VelocistaEdu robot = obtenerRobot();

void setup()
{
}

void loop()
{
  /* Aun no usamos la cuenta de los encoders */
  /*
  int encoderDerecho, encoderIzquierdo;
  robot.obtenerCuentaEncoders(encoderIzquierdo, encoderDerecho);
  */

  /* Comprobar boton de encendido */
  if (robot.botonLiberado())
  {
    estoyEncendido = !estoyEncendido;
  }

  /* Obtener el error para el PD */
  robot.actualizarSensoresLinea();
  error = robot.obtenerMedidaLinea();

  /* Ejecutar el algoritmo de PD */
  /*
   * El pwm puede tomar valores enteros entre -255 y 255
   * Teniendo en cuenta que el error absoluto maximo es de 30,
   * tendremos que dividir por lo menos entre 12 para tener una parte angular razonable
   * Ademas queremos tener algo de resolucion para las Ks
   * Vamos a poner una Kp en el orden de las centenas, con lo que tendremos que aumentar en *100 el divisor
   * Todo esto es un ejemplo. Hay que ajustar mejor estas operaciones
   */
  pwmParteDiferencial = (kp * error + kd * (error - errorAnterior))/12;
  errorAnterior = error;

  /* Establecer velocidad en los motores */
  if (estoyEncendido)
  {
    robot.establecerVelocidad(pwmParteComun - pwmParteDiferencial, pwmParteComun + pwmParteDiferencial);
  }
  /* Si tenemos que estar parados ponemos la velocidad a 0 */
  else
  {
    robot.establecerVelocidad(0, 0);
  }
}

