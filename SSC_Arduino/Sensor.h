/** \file Sensor.h Sensor abstraction header.

  This header file contains the sensor abstraction and its
  corresponding functions; such as acting, initialization and
  reading calculation.

  A function is necessary for the reading interpretation as the arduino
  does not output the its reading directly, but rather the read voltage.
  */

#ifndef H_ARDUINO
#include <Arduino.h>
#define H_ARDUINO
#endif

/** Sensor pseudo-class abstraction.

  The implementation consists the usual \a pin to indicate the input
  of the arduino, \a reading internal variable for the voltage output,
  and some maximum and minimum settings for better value intepretation.

  There is also \a voltage_drift_const and \a voltage_drift_linear for
  fine tune of the readings; but experience showed that the arduino is
  not relaible even with these in the best way tuned.
  */
typedef struct Sensor
{
  //! variable to indicate the output PIN for the sensor.
  byte pin;
  //! internal variable to calculate corret measurements.
  double max_value;
  //! internal variable to calculate corret measurements.
  double min_value;
  //! internal variable to calculate corret measurements.
  double max_voltage;
  //! internal variable to calculate corret measurements.
  double min_voltage;
  //! internal variable to fine tune sensor readings.
  double voltage_drift_linear;
  //! internal variable to fine tune sensor readings.
  double voltage_drift_const;
  //! internal variable to store the pure arduino reading, for later processing.
  double reading;
}
Sensor_t;

/** Sensor abstraction initialization.

  The arguments required for the abstraction allocation are essential
  for the true reading calculation. Note that the fine tune paramenters
  are set by direct acces; not given in one pseudo-class initialization.

  @param[in] pin_ Arduino sensor PIN.
  @param[in] min_value_ minimum value the readings can assume.
  @param[in] max_value_ maximum value the readings can assume.
  @param[in] min_voltage_ the voltage read by the Arduino when the value is at the minimum.
  @param[in] max_voltage_ the voltage read by the Arduino when the value is at the maximum.
  */
Sensor_t * sensorInit(byte pin_, double min_value_, double max_value_,double min_voltage_, double max_voltage_);

/** interpretable reading fucntion.

  based upon the structure's internal variables of maximu mand variables,
  return the expected (in ideal situations) reading of the sensor. This
  is the preferred way of getting information from the sensors, rather
  than directly acessing the reading internal variable and converting
  it to some value; this is a particular case of what this function
  does.
  */
double sensorGetReading(Sensor_t *target);

//! The standard acting function for sensor, more of a general placeholder.
void sensorAct(Sensor_t *target);
