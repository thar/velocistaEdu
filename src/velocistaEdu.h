#define LIBCALL_ENABLEINTERRUPT
#ifndef velocistaEdu_h
#define velocistaEdu_h

#include <stdint.h>
#include "Arduino.h"

#define EI_ARDUINO_INTERRUPTED_PIN
#include "EnableInterrupt.h"

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
  * El objeto de control solo se puede obtener mediante una llamada a la funcion obtenerRobot
  * Esto implementa un patron singleton para asegurar que solo hay un objeto de tipo
  * VelocistaEdu en el programa
  */
class VelocistaEdu
{
  public:
    friend VelocistaEdu & obtenerRobot(const boolean cambiarPolaridadMotorIzquierdo, const boolean cambiarPolaridadMotorDerecho);

/**
  * Funcion que establece pone un pwm en los motores
  * @param[in] velocidadIzquierda PWM para el motor izquierdo
  * @param[in] velocidadDerecha PWM para el motor derecho
  */
    void establecerVelocidad(int velocidadIzquierda, int velocidadDerecha) const;

/**
  * Funcion que comprueba las pulsaciones en el boton del robot
  * @return true cuando se suelta el boton, false en el resto de condiciones
  */
    boolean botonLiberado();

/**
  * Funcion que actualiza las variables internas que guardan los valores de los sensores infrarrojos
  * @see obtenerMedidaLinea()
  * @see obtenerSensoresLinea()
  */
    void actualizarSensoresLinea();

/**
  * funcion que devuelve la posicion de la linea detectada
  * Cuando la linea se deja de detectar devuelve el ultimo valor bueno conocido
  * Es necesario haber llamado a la funcion actualizarSensoresLinea() para usar los valores de los sensores mas actuales
  * @see actualizarSensoresLinea()
  * @see obtenerSensoresLinea()
  * @return La posicion de la linea entre -30 y 30 (aproximadamente)
  */
    int obtenerMedidaLinea() const;

/**
  * Funcion que guarda en un array los ultimos valores conocidos de los sensores inrarojos
  * Es necesario haber llamado a la funcion actualizarSensoresLinea() para usar los valores de los sensores mas actuales
  * @see actualizarSensoresLinea()
  * @see obtenerMedidaLinea()
  * @param[out] s array donde se guardaran los valores de los sensores
  */
    void obtenerSensoresLinea(unsigned int s[4]) const;

/**
  * Funcion que permite obtener la cuenta interna de los encoders
  * @see resetearCuentaEncoders()
  * @param[out] encoderIzquierdo variable donde se guardara la cuenta para el encoder de la rueda izquierda
  * @param[out] encoderDerecho variable donde se guardara la cuenta para el encoder de la rueda derecha
  */
    void obtenerCuentaEncoders(unsigned int &encoderIzquierdo, unsigned int &encoderDerecho) const;

/**
  * Funcion que pone la cuenta de los encoder a 0
  * @see obtenerCuentaEncoders()
  */
    void resetearCuentaEncoders() const;

/**
  * funcion que devuelve la tension de la bateria
  * @return La tension de la bateria en mV
  */
    unsigned int obtenerTensionBateria() const;

/**
  * Funcion que enciende un LED
  * @param[in] led el led que se quiere encender
  */
    void encenderLed(const LEDS led) const;

/**
  * Funcion que apaga un LED
  * @param[in] led el led que se quiere apagar
  */
    void apagarLed(const LEDS led) const;

/**
  * Funcion que apaga un LED
  * @param[in] led el led que se quiere apagar
  */
    void reproducirNota(unsigned int nota, unsigned int duracion) const;
   
  protected:
/**
  * Constructor que inicializa los pines usados por el kit
  * Es privado, con lo que solo se pueden crear objetos de la clase VelocistaEdu haciendo uso de la
  * funcion amiga obtenerRobot
  * @see obtenerRobot()
  * @param[in] cambiarPolaridadMotorIzquierdo, cambia la polaridad del motor izquierdo
  * @param[in] cambiarPolaridadMotorDerecho, cambia la polaridad del motor derecho
  */
    VelocistaEdu(const boolean cambiarPolaridadMotorIzquierdo=false, const boolean cambiarPolaridadMotorDerecho=false);

    boolean esperandoSoltarBoton_; //!< Permite controlar el momento en el que se libera el boton
    unsigned int s_[4]; //!< Guarda el valor de los sensores infrarrojos
    const bool motorIzquierdoAvanza_; //!< Valor que se le debe poner al pin de direccion izquierdo para que el motor izquierdo avance
    const bool motorDerechoAvanza_; //!< Valor que se le debe poner al pin de direccion derecho para que el motor derecho avance

  private:
    static const uint8_t BOTON, M_IZQ_PWM_PIN, M_IZQ_DIR_PIN, M_DER_DIR_PIN, M_DER_PWM_PIN, ENC_IZQ_PIN, ENC_DER_PIN, BUZZ, PULSOS_POR_REVOLUCION;

};

/**
  * Funcion amiga de la clase VelocistaEdu. Esto permite que pueda acceder a los miembros y metodos privados
  * De esta forma esta funcion es capaz de crear un objeto de tipo VelocistaEdu, pues el constructor es privado
  * @param[in] cambiarPolaridadMotorIzquierdo, cambia la polaridad del motor izquierdo. Solo funiona la primera vez que es llada la funcion
  * @param[in] cambiarPolaridadMotorDerecho, cambia la polaridad del motor derecho. Solo funiona la primera vez que es llada la funcion
  */
VelocistaEdu & obtenerRobot(const boolean cambiarPolaridadMotorIzquierdo = false, const boolean cambiarPolaridadMotorDerecho = false);

inline void VelocistaEdu::obtenerSensoresLinea(unsigned int s[4]) const
{
  memcpy(s, VelocistaEdu::s_, 4 * sizeof(unsigned int));
}

inline void VelocistaEdu::encenderLed(const LEDS led) const
{
  digitalWrite(led, HIGH);
}

inline void VelocistaEdu::apagarLed(const LEDS led) const
{
  digitalWrite(led, LOW);
}

inline void VelocistaEdu::reproducirNota(unsigned int nota, unsigned int duracion) const
{
  tone(VelocistaEdu::BUZZ, nota, duracion);
  delay(duracion + 2);
}

#endif //velocistaEdu_h
