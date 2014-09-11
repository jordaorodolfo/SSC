#ifndef H_MOTOR
#include "Motor.h"
#define H_MOTOR
#endif

Motor_t * motorInit(byte pin_rpm_, byte pin_master_enable_ ,long min_rpm_, long max_rpm_)
{
  Motor_t * new_motor = (Motor_t*)malloc(sizeof(Motor_t));
  new_motor->pin_rpm = pin_rpm_;
  new_motor->pin_master_enable = pin_master_enable_;
  new_motor->max_rpm = max_rpm_;
  new_motor->min_rpm = min_rpm_;
  new_motor->current_rpm = 0;
  new_motor->master_enable = false;
  pinMode(pin_rpm_,OUTPUT);
  pinMode(pin_master_enable_,OUTPUT);
  return new_motor;
}

void motorSetRpm(Motor_t * target, long rpm)
{
  target->current_rpm = constrain(rpm,target->min_rpm,target->max_rpm);
}

void motorAct(Motor_t *target)
{
  switch(target->master_enable)
  {
  case true:
    digitalWrite(target->pin_master_enable,HIGH);
    analogWrite(target->pin_rpm,map(target->current_rpm,target->min_rpm,target->max_rpm,25,230));
    break;
  case false:
    digitalWrite(target->pin_master_enable,LOW);
    analogWrite(target->pin_rpm,map(0,target->min_rpm,target->max_rpm,25,230));
    break;
  }
}
