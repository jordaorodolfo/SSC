#ifndef H_ARDUINO
#include <Arduino.h>
#define H_ARDUINO
#endif

typedef struct Switch
{
  byte pin;
  bool reading;
  bool pullup;
} Switch_t;

Switch_t * switchInit(byte pin);
void switchAct(Switch_t * target);
