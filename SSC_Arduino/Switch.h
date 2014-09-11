/** \file Switch.h Switch abstraction header.

  This header file contains the switch abstraction and its
  corresponding functions; such as acting.

  To change the switch state, the boolean variable which represents it must
  be directly changed to the desired state.
  */
#ifndef H_ARDUINO
#include <Arduino.h>
#define H_ARDUINO
#endif

/** Switch pseudo-class abstraction.

  implements the usual pin abstraction along with the boolean reading. The
  pullup works as a flag which should only be given at the initialization and
  not changed later.
  */
typedef struct Switch
{
  //! varaible to represent Arduino PIN.
  byte pin;
  //! digital reading made by the arduino of the switch.
  bool reading;
  //! internal flag to control if the switch should be treated normally or as pullup.
  bool pullup;
} Switch_t;

/** Switch abstraction normal initialization.

  This allocates memory for the pseudo-class and sets its necessayr internal
  variables. along with the flags for further acting.
  */
Switch_t * switchInit(byte pin);

/** Switch abstraction pull-up initialization.

  This allocates memory for the pseudo-class and sets its necessary internal
  variables. along with the flags for further acting.
  */
Switch_t * switchInitPullUp(byte pin);

/** Switch acting function.

  Takes note of the structure internal variables and acts accordingly. The internal
  behaviour is different if the switch is initialized normally or as pull-up, but
  the end result is given as the same by the function.
  */
void switchAct(Switch_t * target);
