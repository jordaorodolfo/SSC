#ifndef H_ARDUINO
#include <Arduino.h>
#define H_ARDUINO
#endif
#ifndef H_SWITCH
#include "Switch.h"
#define H_SWITCH
#endif

Switch_t * switchInit(byte pin_)
{
  Switch_t * newSwitch = (Switch_t*)malloc(sizeof(Switch_t));
  newSwitch->pin = pin_;
  pinMode(pin_,INPUT);
  return newSwitch;
}

void switchAct(Switch_t * target)
{
  switch(digitalRead(target->pin))
  {
    case HIGH:
      target->reading = true;
    break;
    case LOW:
      target->reading = false;
    break;
  }
}
