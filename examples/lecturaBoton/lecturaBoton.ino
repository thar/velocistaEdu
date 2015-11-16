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
  if (VelocistaEdu::botonLiberado())
  {
    Serial.println("boton liberado");
  }
}
