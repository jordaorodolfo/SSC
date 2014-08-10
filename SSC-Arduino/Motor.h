#ifndef H_ARDUINO
#include <Arduino.h>
#define H_ARDUINO
#endif

typedef struct Motor
{
  byte pin_rpm;
  byte pin_master_enable;
  long max_rpm;
  long min_rpm;
  long current_rpm;
  boolean master_enable;
} 
Motor_t;

Motor_t * motorInit(byte pin_rpm_, unsigned int pin_master_enable_ ,long max_rpm_, long min_rpm_);
void motorSetRpm(Motor_t *target, long rmp);
void motorAct(Motor_t *target);

