#ifndef H_LED
#include "Led.h"
#define H_LED
#endif

Led_t * ledInit(byte pin_red,byte pin_green,byte pin_blue,boolean digital_)
{
  Led_t * new_led = (Led_t*)malloc(sizeof(Led_t));
  new_led->pin_RGB[0] = pin_red;
  new_led->pin_RGB[1] = pin_green;
  new_led->pin_RGB[2] = pin_blue;
  new_led->RGB[0] = 0;
  new_led->RGB[1] = 0;
  new_led->RGB[2] = 0;
  if(pin_red != 0)
    pinMode(pin_red,OUTPUT);
  if(pin_green != 0)
    pinMode(pin_green,OUTPUT);
  if(pin_blue != 0)
    pinMode(pin_blue,OUTPUT);
  new_led->digital = digital_;
  return new_led;
}

void ledSetColor(Led_t * target, byte red, byte green, byte blue)
{
  target->RGB[0] = red;
  target->RGB[1] = green;
  target->RGB[2] = blue;
}

void ledAct(Led_t * target)
{
  switch(target->digital)
  {
  case true:
      switch(target->pin_RGB[0])
      {
      case 0:
        break;
      default:
        if(target->RGB[0] > 127)
          digitalWrite(target->pin_RGB[0],HIGH);
        else
          digitalWrite(target->pin_RGB[0],LOW);
        break;
      }
      switch(target->pin_RGB[1])
      {
      case 0:
        break;
      default:
        if(target->RGB[1] > 127)
          digitalWrite(target->pin_RGB[1],HIGH);
        else
          digitalWrite(target->pin_RGB[1],LOW);
        break;
      }
      switch(target->pin_RGB[2])
      {
      case 0:
        break;
      default:
        if(target->RGB[2] > 127)
          digitalWrite(target->pin_RGB[2],HIGH);
        else
          digitalWrite(target->pin_RGB[2],LOW);
        break;
      }
    break;
  case false:
      switch(target->pin_RGB[0])
      {
      case 0:
        break;
      default:
        analogWrite(target->pin_RGB[0],target->RGB[0]);
        break;
      }
      switch(target->pin_RGB[1])
      {
      case 0:
        break;
      default:
        analogWrite(target->pin_RGB[1],target->RGB[1]);
        break;
      }
      switch(target->pin_RGB[2])
      {
      case 0:
        break;
      default:
        analogWrite(target->pin_RGB[2],target->RGB[2]);
        break;
      }
    break; 
  }
}
