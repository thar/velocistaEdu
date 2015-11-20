#ifndef velocistaEdu_h
#define velocistaEdu_h

#include "Arduino.h"
#ifdef USE_INTERRUPT
#include "EnableInterrupt.h"
#endif

/** 
  * enum para definir los pines de los LEDs
  * Cada LED tiene asociando un pin de la placa Arduino
  * Se puede extender con mas leds, como el disponible en la Arduino Nano
  */
enum LEDS {
   ROJO = 9,
   VERDE = 10,
   NANO = 13
};

/**
  * Clase de control del velocistaEdu
  * Tiene las funciones basicas para empezar a usar el kit de velocista
  * No tiene constructor ni destructor porque todos sus miembros son estaticos
  */
class VelocistaEdu
{
  public:
/**
  * Funcion estatica de inicializacion de los pines usados por el kit
  */
    static void inicializar();

/**
  * Funcion estatica que establece pone un pwm en los motores
  * @param[in] velocidadIzquierda PWM para el motor izquierdo
  * @param[in] velocidadDerecha PWM para el motor derecho
  */
    static void establecerVelocidad(int velocidadIzquierda, int velocidadDerecha);

/**
  * Funcion estatica que comprueba las pulsaciones en el boton del robot
  * @return true cuando se suelta el boton, false en el resto de condiciones
  */
    static boolean botonLiberado();

/**
  * Funcion estatica que actualiza las variables internas que guardan los valores de los sensores infrarrojos
  * @see obtenerMedidaLinea()
  * @see obtenerSensoresLinea()
  */
    static void actualizarSensoresLinea();

/**
  * funcion estatica que devuelve la posicion de la linea detectada
  * Cuando la linea se deja de detectar devuelve el ultimo valor bueno conocido
  * Es necesario haber llamado a la funcion actualizarSensoresLinea() para usar los valores de los sensores mas actuales
  * @see actualizarSensoresLinea()
  * @see obtenerSensoresLinea()
  * @return La posicion de la linea entre -30 y 30 (aproximadamente)
  */
    static int obtenerMedidaLinea();

/**
  * Funcion estatica que guarda en un array los ultimos valores conocidos de los sensores inrarojos
  * Es necesario haber llamado a la funcion actualizarSensoresLinea() para usar los valores de los sensores mas actuales
  * @see actualizarSensoresLinea()
  * @see obtenerMedidaLinea()
  * @param[out] s array donde se guardaran los valores de los sensores
  */
    static void obtenerSensoresLinea(unsigned int s[4]);

#ifdef USE_INTERRUPT
/**
  * Funcion estatica que aumenta la cuenta del encoder derecho
  * Se usa en el modo de cuenta de encoders por interrupcion
  * @see obtenerCuentaEncoders()
  * @see resetearCuentaEncoders()
  * @see aumentarCuentaIzquierda()
  */
    static void aumentarCuentaDerecha();

/**
  * Funcion estatica que aumenta la cuenta del encoder izquierdo
  * Se usa en el modo de cuenta de encoders por interrupcion
  * @see obtenerCuentaEncoders()
  * @see resetearCuentaEncoders()
  * @see aumentarCuentaDerecha()
  */
    static void aumentarCuentaIzquierda();

#else
/**
  * Funcion estatica que comprueba si las ruedas se han movido y actualiza el valor de la cuenta de los encoder
  * Esta funcion se tiene que llamar de forma periodica y con la mayor frecuencia posible para estar seguros de que contamos todos los pulsos
  * @see obtenerCuentaEncoders()
  * @see resetearCuentaEncoders()
  */
    static void actualizarEncoders();
#endif

/**
  * Funcion estatica que permite obtener la cuenta interna de los encoders
  * @see actualizarEncoders()
  * @see resetearCuentaEncoders()
  * @param[out] encoderIzquierdo variable donde se guardara la cuenta para el encoder de la rueda izquierda
  * @param[out] encoderDerecho variable donde se guardara la cuenta para el encoder de la rueda derecha
  */
    static void obtenerCuentaEncoders(int &encoderIzquierdo, int &encoderDerecho);

/**
  * Funcion estatica que pone la cuenta de los encoder a 0
  * @see actualizarEncoders()
  * @see obtenerCuentaEncoders()
  */
    static void resetearCuentaEncoders();

/**
  * funcion estatica que devuelve la tension de la bateria
  * @return La tension de la bateria en mV
  */
    static unsigned int obtenerTensionBateria();

/**
  * Funcion estatica que enciende un LED
  * @param[in] led el led que se quiere encender
  */
    static void encenderLed(LEDS led);

/**
  * Funcion estatica que apaga un LED
  * @param[in] led el led que se quiere apagar
  */
    static void apagarLed(LEDS led);


  protected:
#ifndef USE_INTERRUPT
    static boolean estadoEncoderDerecho; //!< Guarda el ultimo estado conocido del pin del encoder derecho
    static boolean estadoEncoderIzquierdo; //!< Guarda el ultimo estado conocido del pin del encoder izquierdo
#endif
    static unsigned int cuentaEncoderDerecho; //!< Guarda la cuenta del encoder derecho
    static unsigned int cuentaEncoderIzquierdo; //!< Guarda la cuenta del encoder izquierdo
    static boolean esperandoSoltarBoton; //!< Permite controlar el momento en el que se libera el boton
    static unsigned int s[4]; //!< Guarda el valor de los sensores infrarrojos

  private:
    static const uint8_t BOTON, M_IZQ_PWM_PIN, M_IZQ_DIR_PIN, M_DER_DIR_PIN, M_DER_PWM_PIN, ENC_IZQ_PIN, ENC_DER_PIN, BUZZ;
};

inline void VelocistaEdu::encenderLed(LEDS led)
{
  digitalWrite(led, HIGH);
}

inline void VelocistaEdu::apagarLed(LEDS led)
{
  digitalWrite(led, LOW);
}

inline void VelocistaEdu::obtenerSensoresLinea(unsigned int s[4])
{
  memcpy(s, VelocistaEdu::s, 4 * sizeof(unsigned int));
}


#endif
