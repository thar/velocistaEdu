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
  unsigned int s[4];
  VelocistaEdu::actualizarSensoresLinea();
  VelocistaEdu::obtenerSensoresLinea(s);
  Serial.print(s[0]);
  Serial.print(" ");
  Serial.print(s[1]);
  Serial.print(" ");
  Serial.print(s[2]);
  Serial.print(" ");
  Serial.println(s[3]);
  delay(100);
}
