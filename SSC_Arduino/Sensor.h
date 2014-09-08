#ifndef H_ARDUINO
#include <Arduino.h>
#define H_ARDUINO
#endif

typedef struct Sensor
{
  byte pin;
  double max_value;
  double min_value;
  double max_voltage;
  double min_voltage;
  double voltage_drift_linear;
  double voltage_drift_const;
  double reading;
}
Sensor_t;

Sensor_t * sensorInit(byte pin_, double min_value_, double max_value_,double min_voltage_, double max_voltage_);
Sensor_t * sensorInitPullUp(byte pin_, double min_value_, double max_value_,double min_voltage_, double max_voltage_);
double sensorGetReading(Sensor_t *target);
void sensorAct(Sensor_t *target);
