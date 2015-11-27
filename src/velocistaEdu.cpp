#include "velocistaEdu.h"

const uint8_t VelocistaEdu::BOTON = 0;
const uint8_t VelocistaEdu::M_IZQ_PWM_PIN = 3;
const uint8_t VelocistaEdu::M_IZQ_DIR_PIN = 4;
const uint8_t VelocistaEdu::M_DER_DIR_PIN = 5;
const uint8_t VelocistaEdu::M_DER_PWM_PIN = 6;
const uint8_t VelocistaEdu::ENC_IZQ_PIN = 7;
const uint8_t VelocistaEdu::ENC_DER_PIN = 8;
const uint8_t VelocistaEdu::BUZZ = 12;
const uint8_t VelocistaEdu::PULSOS_POR_REVOLUCION = 60;

volatile unsigned int cuentaEncoderIzquierdo = 0; //!< Guarda la cuenta del encoder izquierdo
volatile unsigned int cuentaEncoderDerecho = 0; //!< Guarda la cuenta del encoder derecho

/**
  * Funcion que aumenta la cuenta del encoder izquierdo
  * @see obtenerCuentaEncoders()
  * @see resetearCuentaEncoders()
  * @see aumentarCuentaDerecha()
  */
void aumentarCuentaIzquierda()
{
  cuentaEncoderIzquierdo++;
}

/**
  * Funcion que aumenta la cuenta del encoder derecho
  * @see obtenerCuentaEncoders()
  * @see resetearCuentaEncoders()
  * @see aumentarCuentaIzquierda()
  */
void aumentarCuentaDerecha()
{
  cuentaEncoderDerecho++;
}

VelocistaEdu::VelocistaEdu(const boolean cambiarPolaridadMotorIzquierdo, const boolean cambiarPolaridadMotorDerecho) :
esperandoSoltarBoton_(0), s_({0,0,0,0}),
motorIzquierdoAvanza_(cambiarPolaridadMotorIzquierdo ? LOW : HIGH), motorDerechoAvanza_(cambiarPolaridadMotorDerecho ? HIGH : LOW)
{
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

  enableInterrupt(VelocistaEdu::ENC_DER_PIN, aumentarCuentaDerecha, CHANGE);
  enableInterrupt(VelocistaEdu::ENC_IZQ_PIN, aumentarCuentaIzquierda, CHANGE);
}

void VelocistaEdu::establecerVelocidad(int velocidadIzquierda, int velocidadDerecha) const {
  if (velocidadIzquierda >= 0) {
    digitalWrite(VelocistaEdu::M_IZQ_DIR_PIN, motorIzquierdoAvanza_);
  } else {
    digitalWrite(VelocistaEdu::M_IZQ_DIR_PIN, !motorIzquierdoAvanza_);
  }
  //Ajuste de la velocidad maxima y minima para el motor izquierdo
  if (velocidadIzquierda > 255) {
    velocidadIzquierda = 255;
  } else if (velocidadIzquierda < -255) {
    velocidadIzquierda = -255;
  }
  analogWrite(VelocistaEdu::M_IZQ_PWM_PIN, abs(velocidadIzquierda));

  if (velocidadDerecha >= 0) {
    digitalWrite(VelocistaEdu::M_DER_DIR_PIN, motorDerechoAvanza_);
  } else {
    digitalWrite(VelocistaEdu::M_DER_DIR_PIN, !motorDerechoAvanza_);
  }
  //Ajuste de la velocidad maxima y minima para el motor derecho
  if (velocidadDerecha > 255) {
    velocidadDerecha = 255;
  } else if (velocidadDerecha < -255) {
    velocidadDerecha = -255;
  }
  analogWrite(VelocistaEdu::M_DER_PWM_PIN, abs(velocidadDerecha));
}


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
    esperandoSoltarBoton_ = true;
    return false;
  } else if(esperandoSoltarBoton_) {
    esperandoSoltarBoton_ = false;
    return true;
  }
}

void VelocistaEdu::actualizarSensoresLinea()
{
  s_[0] = analogRead(A0); //posicion -3
  s_[1] = analogRead(A1); //posicion -1
  s_[2] = analogRead(A2); //posicion 1
  s_[3] = analogRead(A3); //posicion 3
}

int VelocistaEdu::obtenerMedidaLinea() const
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
  if (s_[0] > 200)
    numeroSensoresDetectando++;
  if (s_[1] > 200)
    numeroSensoresDetectando+=2;
  if (s_[2] > 200)
    numeroSensoresDetectando+=2;
  if (s_[3] > 200)
    numeroSensoresDetectando++;
  if (numeroSensoresDetectando > 1)
  {
    posicion = (-3 * s_[0]) + (-1 * s_[1]) + (1 * s_[2]) + (3 * s_[3]);
    posicionAnterior = posicion;
  }
  else
  {
    posicion = posicionAnterior * 11 / 10; //Esto sirve para dar un valor un poco mayor al extremo cuando perdemos la linea
  }
  //NOTA: Aqui divido por 100 para tener valores entre -30 y 30, siendo esto una resolucion de unos 0.6mm, pero es posible que otro valor sea mejor
  return posicion/100;
}

void VelocistaEdu::obtenerCuentaEncoders(int &encoderIzquierdo, int &encoderDerecho) const
{
  encoderIzquierdo = cuentaEncoderIzquierdo;
  encoderDerecho = cuentaEncoderDerecho;
}

void VelocistaEdu::resetearCuentaEncoders() const
{
  cuentaEncoderDerecho = 0;
  cuentaEncoderIzquierdo = 0;
}

unsigned int VelocistaEdu::obtenerTensionBateria() const
{
  unsigned int bateria = analogRead(A6);
  bateria = bateria * 41 / 5;
  return bateria;
}

VelocistaEdu & obtenerRobot(const boolean cambiarPolaridadMotorIzquierdo, const boolean cambiarPolaridadMotorDerecho)
{
  static VelocistaEdu robot(cambiarPolaridadMotorIzquierdo, cambiarPolaridadMotorDerecho);
  return robot;
}

