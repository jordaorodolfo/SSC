/** \file Led.h LED abstraction definitions.

  This files contains both the pseudo-class function definitions and the
  structure which acts kile the surmounted class.
 */

#ifndef H_ARDUINO
#include <Arduino.h>
#define H_ARDUINO
#endif

/** pseudo-class as a structure for LED abstraction.

  constitutes of \a pin_RGB vector, giving the pins designed to make the led
  act in the desired RGB color, \a RGB vector containing the so-called numbers
  and \a boolean digital; which is used within the function of acting to discern
  between digital and analog LEDs.
  */
typedef struct Led
{
  //! maps each pin for acting.
  byte pin_RGB[2];
  //! maps each RGB color of the desired color in the LED.
  byte RGB[2];
  //! used to discern digital or analog LEDs.
  boolean digital;
}
Led_t;

/** ledInit LED abstraction initialization.

  After giving the necessary pins and a flag to check if the LED is digital
  or analog; space for it is allocated internally and a Led_t type is returned
  to be used.

  @param[in] pin_red The pin for the red I/O.
  @param[in] pin_blue The pin for the blue I/O.
  @param[in] pin_green The pin for the green I/O.
  @param[in] digital_ Flag to be used internally for acting.
  */
Led_t * ledInit(byte pin_red,byte pin_green,byte pin_blue,boolean digital_);

/** Change the color settings of the target by giving new RGB.

  @param[in] target abstraction to me modified.
  @param[in] red new red value.
  @param[in] green new green value.
  @param[in] blue new blue value.
  */
void ledSetColor(Led_t *target, byte red, byte green, byte blue);

/** LED abstraction acting function.

  If the LED is digital, check if each of the RGB's in the target abstraction
  are greater than 127; if so, this color is set to HIGH. Else, just write
  each RGB color set directly into each color's analog pin.

  @param[in] target The LED abstraction to be acted.
  */
void ledAct(Led_t *target);
