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
  newSwitch->pullup = false;
  return newSwitch;
}

Switch_t * switchInitPullUp(byte pin_)
{
  Switch_t * newSwitch = (Switch_t*)malloc(sizeof(Switch_t));
  newSwitch->pin = pin_;
  newSwitch->pullup = true;
  pinMode(pin_,INPUT_PULLUP);
  return newSwitch;
}

void switchAct(Switch_t * target)
{
  switch(target->pullup)
  {
    case true:
      switch(digitalRead(target->pin))
      {
        case LOW:
          target->reading = true;
        break;
        case HIGH:
          target->reading = false;
        break;
      }
      break;
    case false:
      switch(digitalRead(target->pin))
      {
        case HIGH:
          target->reading = true;
        break;
        case LOW:
          target->reading = false;
        break;
      }
      break;
  }
}
