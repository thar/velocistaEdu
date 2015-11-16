#ifndef velocistaEdu_h
#define velocistaEdu_h

#include "Arduino.h"

enum LEDS {
   LED1 = 9,
   LED2 = 10
};

class VelocistaEdu
{
  public:
    static void inicializar();
    static void establecerVelocidad(int velocidadIzquierda, int velocidadDerecha);
    static boolean botonLiberado();
    static void actualizarSensoresLinea();
    static int obtenerMedidaLinea();
    static void obtenerSensoresLinea(unsigned int s[4]);
    static void obtenerCuentaEncoders(int &encoderIzquierdo, int &encoderDerecho);
    static void resetearCuentaEncoders();
    static void actualizarEncoders();
    static int obtenerTensionBateria();
    static void encenderLed(LEDS led);
    static void apagarLed(LEDS led);

  protected:
    static boolean estadoEncoderDerecho;
    static boolean estadoEncoderIzquierdo;
    static unsigned int cuentaEncoderDerecho;
    static unsigned int cuentaEncoderIzquierdo;
    static boolean esperandoSoltarBoton;
    static unsigned int s[4];

  private:
    static const uint8_t BOTON, M_IZQ_PWM_PIN, M_IZQ_DIR_PIN, M_DER_DIR_PIN, M_DER_PWM_PIN, ENC_IZQ_PIN, ENC_DER_PIN;
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
