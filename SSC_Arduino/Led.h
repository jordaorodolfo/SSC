#ifndef H_ARDUINO
#include <Arduino.h>
#define H_ARDUINO
#endif

typedef struct Led
{
  byte pin_RGB[2];
  byte RGB[2];
  boolean digital;
}
Led_t;

Led_t * ledInit(byte pin_red,byte pin_green,byte pin_blue,boolean digital_);
void ledSetColor(Led_t *target, byte red, byte green, byte blue);
void ledAct(Led_t *target);
 
