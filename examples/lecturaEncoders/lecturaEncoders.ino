#include "velocistaEdu.h"

void setup()
{
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  VelocistaEdu::inicializar();
}

void loop()
{
  int encoderDerecho, encoderIzquierdo;
  VelocistaEdu::actualizarEncoders();
  VelocistaEdu::obtenerCuentaEncoders(encoderIzquierdo, encoderDerecho);
  Serial.print(encoderIzquierdo);
  Serial.print(" ");
  Serial.println(encoderDerecho);
  delay(100);
}
