#ifndef H_ARDUINO
#include <Arduino.h>
#define H_ARDUINO
#endif
#ifndef H_SENSOR
#include "Sensor.h"
#define H_SENSOR
#endif
#ifndef H_UTILS
#include "utils.h"
#define H_UTILS
#endif

Sensor_t * sensorInit(byte pin_, double min_value_, double max_value_,double min_voltage_, double max_voltage_)
{
  Sensor_t * new_sensor = (Sensor_t*)malloc(sizeof(Sensor_t));
  new_sensor->pin = pin_;
  new_sensor->max_value = max_value_;
  new_sensor->max_voltage = max_voltage_*1023.0/5.0;
  new_sensor->min_value = min_value_;
  new_sensor->min_voltage = min_voltage_*1023.0/5.0;
  new_sensor->voltage_drift_linear = 0.0;
  new_sensor->voltage_drift_const = 0.0;
  pinMode(pin_,INPUT);
  return new_sensor;
}

Sensor_t * sensorInitPullUp(byte pin_, double min_value_, double max_value_,double min_voltage_, double max_voltage_)
{
  Sensor_t * new_sensor = (Sensor_t*)malloc(sizeof(Sensor_t));
  new_sensor->pin = pin_;
  new_sensor->max_value = max_value_;
  new_sensor->max_voltage = max_voltage_*1023.0/5.0;
  new_sensor->min_value = min_value_;
  new_sensor->min_voltage = min_voltage_*1023.0/5.0;
  new_sensor->voltage_drift_linear = 0.0;
  new_sensor->voltage_drift_const = 0.0;
  pinMode(pin_,INPUT_PULLUP);
  return new_sensor;
}

double sensorGetReading(Sensor_t * target)
{
  return doubleMap(target->reading*(1+target->voltage_drift_linear)+target->voltage_drift_const,
  target->min_voltage,target->max_voltage,target->min_value,target->max_value);
}

void sensorAct(Sensor_t *target)
{
  target->reading = analogRead(target->pin);
}
