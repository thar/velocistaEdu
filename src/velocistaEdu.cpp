#include "velocistaEdu.h"

const uint8_t VelocistaEdu::BOTON = 0;
const uint8_t VelocistaEdu::M_IZQ_PWM_PIN = 3;
const uint8_t VelocistaEdu::M_IZQ_DIR_PIN = 4;
const uint8_t VelocistaEdu::M_DER_DIR_PIN = 5;
const uint8_t VelocistaEdu::M_DER_PWM_PIN = 6;
const uint8_t VelocistaEdu::ENC_IZQ_PIN = 7;
const uint8_t VelocistaEdu::ENC_DER_PIN = 8;
const uint8_t VelocistaEdu::BUZZ = 12;

boolean VelocistaEdu::estadoEncoderDerecho = 0;
boolean VelocistaEdu::estadoEncoderIzquierdo = 0;
unsigned int VelocistaEdu::cuentaEncoderDerecho = 0;
unsigned int VelocistaEdu::cuentaEncoderIzquierdo = 0;
boolean VelocistaEdu::esperandoSoltarBoton = 0;
unsigned int VelocistaEdu::s[4] = {0, 0, 0, 0};

//lectura de pulsador para arrancar/parar
/*
 * Este codigo controla el estado de encendido/apagado del robot
 * El objetivo es que cuando se suelte el boton se cambie el estado del robot
 * El boton cuando esta suelto responde con un 1 (o un true)
 * Cuando esta pulsado responde con un 0 (o con un false)
 * El if comprueba si el boton responde con 0. En ese caso pone la variable esperaUno a 1
 * Esto nos sirve para saber que hemos pulsado el boton y que ahora hay que comprobar si se va a soltar
 * Esa comprobacion se hace en el else.
 * Es un else if porque queremos entrar en esa condicion solo una vez en el momento exacto en el que soltamos el boton
 * Eso se hace gracias a la variable esperaUno, que como hemos visto la activamos solo cuando el boton se mantiene pulsado
 * Al soltar el boton esa variable tiene el valor uno y entramos en el else if
 * Al entrar lo primero que hacemos es desactivar la variable esperaUno para no volver a entrar en el else if
 * Y tambien cambiamos el valor de onoff, que es el que controla si el robot esta en marcha (cuando vale 1)
 * o parado (cuando vale 0)
 */
boolean VelocistaEdu::botonLiberado()
{
  if(digitalRead(VelocistaEdu::BOTON)==0) {
    VelocistaEdu::esperandoSoltarBoton = true;
    return false;
  } else if(VelocistaEdu::esperandoSoltarBoton) {
    VelocistaEdu::esperandoSoltarBoton = false;
    return true;
  }
}

//Cuenta del encoder
/*
 * Este codigo comprueba si el pin asociado al encoder ha cambiado de valor.
 * Cada vez que cambia se aumenta la cuenta del encoder en uno.
 * Esa cuenta se guarda en las variables cuentaEncoderDerecho y cuentaEncoderIzquierdo
 */
#ifndef USE_INTERRUPT
void VelocistaEdu::actualizarEncoders()
{
  int estadoEnc = digitalRead(VelocistaEdu::ENC_DER_PIN);
  if (estadoEnc != VelocistaEdu::estadoEncoderDerecho) {
    VelocistaEdu::estadoEncoderDerecho = estadoEnc;
    VelocistaEdu::cuentaEncoderDerecho++;
  }
  estadoEnc = digitalRead(VelocistaEdu::ENC_IZQ_PIN);
  if (estadoEnc != VelocistaEdu::estadoEncoderIzquierdo) {
    VelocistaEdu::estadoEncoderIzquierdo = estadoEnc;
    VelocistaEdu::cuentaEncoderIzquierdo++;
  }
}
#else
void VelocistaEdu::aumentarCuentaDerecha()
{
  VelocistaEdu::cuentaEncoderDerecho++;
}

void VelocistaEdu::aumentarCuentaIzquierda()
{
  VelocistaEdu::cuentaEncoderIzquierdo++;
}
#endif

void VelocistaEdu::obtenerCuentaEncoders(int &encoderIzquierdo, int &encoderDerecho)
{
  encoderIzquierdo = VelocistaEdu::cuentaEncoderIzquierdo;
  encoderDerecho = VelocistaEdu::cuentaEncoderDerecho;
}

void VelocistaEdu::resetearCuentaEncoders()
{
  VelocistaEdu::cuentaEncoderDerecho = 0;
  VelocistaEdu::cuentaEncoderIzquierdo = 0;
}

unsigned int VelocistaEdu::obtenerTensionBateria()
{
  unsigned int bateria = analogRead(A6);
  bateria = bateria * 41 / 5;
  return bateria;
}

void VelocistaEdu::establecerVelocidad(int velocidadIzquierda, int velocidadDerecha) {
  //Control de direccion para el motor derecho. Si el motor va al reves de lo esperado cambiar el LOW por HIGH y HIGH por LOW
  if (velocidadDerecha >= 0) {
    digitalWrite(VelocistaEdu::M_DER_DIR_PIN, LOW);
  } else {
    digitalWrite(VelocistaEdu::M_DER_DIR_PIN, HIGH);
  }
  //Ajuste de la velocidad maxima y minima para el motor derecho
  if (velocidadDerecha > 255) {
    velocidadDerecha = 255;
  } else if (velocidadDerecha < -255) {
    velocidadDerecha = -255;
  }
  analogWrite(VelocistaEdu::M_DER_PWM_PIN, abs(velocidadDerecha));
  
  //Control de direccion para el motor izquierdo. Si el motor va al reves de lo esperado cambiar el LOW por HIGH y HIGH por LOW
  if (velocidadIzquierda >= 0) {
    digitalWrite(VelocistaEdu::M_IZQ_DIR_PIN, LOW);
  } else {
    digitalWrite(VelocistaEdu::M_IZQ_DIR_PIN, HIGH);
  }
  //Ajuste de la velocidad maxima y minima para el motor izquierdo
  if (velocidadIzquierda > 255) {
    velocidadIzquierda = 255;
  } else if (velocidadIzquierda < -255) {
    velocidadIzquierda = -255;
  }
  analogWrite(VelocistaEdu::M_IZQ_PWM_PIN, abs(velocidadIzquierda));
}

void VelocistaEdu::actualizarSensoresLinea()
{
  VelocistaEdu::s[0] = analogRead(A0); //posicion -3
  VelocistaEdu::s[1] = analogRead(A1); //posicion -1
  VelocistaEdu::s[2] = analogRead(A2); //posicion 1
  VelocistaEdu::s[3] = analogRead(A3); //posicion 3
}

int VelocistaEdu::obtenerMedidaLinea()
{
  /*
   * Esta variable guarda la posicion de la linea calculada
   */
  int posicion = 0;

  /*
   * Esta variable sirve para trackear la ultima posicion de linea buena antes de que se perdiera
   */
  static int posicionAnterior = 0;

  /* 
   *  En el siguiente codigo vamos a calcular la posicion de la linea
   *  Los sensores miden entre 0 y 1023
   *  Esto nos da un valor de linea teorico minimo de -3*1023 y uno maximo de 3*1023
   */
  int numeroSensoresDetectando = 0;
  if (VelocistaEdu::s[0] > 200)
    numeroSensoresDetectando++;
  if (VelocistaEdu::s[1] > 200)
    numeroSensoresDetectando+=2;
  if (VelocistaEdu::s[2] > 200)
    numeroSensoresDetectando+=2;
  if (VelocistaEdu::s[3] > 200)
    numeroSensoresDetectando++;
  if (numeroSensoresDetectando > 1)
  {
    posicion = (-3 * VelocistaEdu::s[0]) + (-1 * VelocistaEdu::s[1]) + (1 * VelocistaEdu::s[2]) + (3 * VelocistaEdu::s[3]);
    posicionAnterior = posicion;
    //VelocistaEdu::apagarLed(ROJO); //Descomentar para que se apague el ROJO cuando se encuentra la linea
  }
  else
  {
    posicion = posicionAnterior * 11 / 10; //Esto sirve para dar un valor un poco mayor al extremo cuando perdemos la linea
    //VelocistaEdu::encenderLed(ROJO); //Descomentar para que se encienda el ROJO si se pierde la linea
  }
  //NOTA: Aqui divido por 100 para tener valores entre -30 y 30, siendo esto una resolucion de unos 0.6mm, pero es posible que otro valor sea mejor
  return posicion/100;
}

/*
 * TODO: IR
 */
void VelocistaEdu::inicializar() {
  /*
   * Ponemos los pines del motor como salida
   */
  pinMode(VelocistaEdu::M_DER_DIR_PIN, OUTPUT);
  pinMode(VelocistaEdu::M_DER_PWM_PIN, OUTPUT);
  pinMode(VelocistaEdu::M_IZQ_DIR_PIN, OUTPUT);
  pinMode(VelocistaEdu::M_IZQ_PWM_PIN, OUTPUT);

  /*
   * Ponemos los pines de encoder como entrada
   * Hay que activar las resistencias de pull-up internas
   */
  pinMode(VelocistaEdu::ENC_DER_PIN, INPUT_PULLUP);
  pinMode(VelocistaEdu::ENC_IZQ_PIN, INPUT_PULLUP);

  /*
   * Los pines de los leds como salida
   */
  pinMode(ROJO, OUTPUT);
  pinMode(VERDE, OUTPUT);

  /*
   * El pin del buzzer como salida
   */
  pinMode(VelocistaEdu::BUZZ, OUTPUT);

  /*
   * El pin del boton como entrada
   * Necesita tambien el pull-up activo
   */
  pinMode(VelocistaEdu::BOTON, INPUT_PULLUP);

#ifdef USE_INTERRUPT
  enableInterrupt(VelocistaEdu::ENC_DER_PIN, VelocistaEdu::aumentarCuentaDerecha, CHANGE);
  enableInterrupt(VelocistaEdu::ENC_IZQ_PIN, VelocistaEdu::aumentarCuentaIzquierda, CHANGE);
#endif
}

