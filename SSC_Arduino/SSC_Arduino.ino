/** \file SSC_Arduino.ino Main code for the SSC Drill Arduino.
 *
 * All pseudo-classes inclusions occur in this file. The loop and setup standard
 * functions also call external functions defined as means of easy editing and control;
 * some preprocessor flags control if the stall detection algorithm should be used in
 * junction with the ESCON controller.
 */

//! checks if the motor type has already been included, and do it if not.
#ifndef H_MOTOR
#include "Motor.h"
#define H_MOTOR
#endif
//! checks if the led type has already been included, and do it if not.
#ifndef H_LED
#include "Led.h"
#define H_LED
#endif
//! checks if the sensor type has already been included, and do it if not.
#ifndef H_SENSOR
#include "Sensor.h"
#define H_SENSOR
#endif
/*
#ifndef H_UTILS
#include "utils.h"
#define H_UTILS
#endif
#ifndef H_LSR
#include "LSR.h"
#define H_LSR
#endif
*/
//! checks if the switch type has already been included, and do it if not.
#ifndef H_SWITCH
#include "Switch.h"
#define H_SWITCH
#endif

//! global variable representing the setup's only motor.
Motor_t * motor;
//! global variable to represent a LED indicating the motor activity.
Led_t * motor_enable_led;
//! global variable to represent the motor speed sensor abstraction.
Sensor_t * motor_speed_sensor;
//! global variable to represent the motor softPot into the system.
Sensor_t * height_sensor;
//! global variable to represent
Switch_t * motor_stall_current_switch;

/** A preprocessor flag defining if the stall detection should be used.

  if this flag is defined, then the functions defined for the stall error
  detection are compiled with the whole source code. if this flag is set,
  another global constant needs to be defined.

  @see errorDetection
  @see resetErrorAlgorithm
  @see C_ERROR_CHECK_TOLERANCE
  @see error_timer
  */
#define FLAG_CHECK_FOR_ERROR
#ifdef FLAG_CHECK_FOR_ERROR
/** maximum error tolerance for error algorithm.
  this flag defined the maximum error tolerated into the error algorithm.
  @see errorDetection
  */
#define C_ERROR_CHECK_TOLERANCE 150
/** global variable for error detection.
  This global variable is used in the error function as a timer replacement.
  @see errorDetection
  */
unsigned int error_timer;
#endif

#ifdef FLAG_CHECK_FOR_ERROR
/** function to detect stall, is used within the loop premises.

  If the FLAG_CHECK_FOR_ERROR is defined, this function is compiled and
  placed into the appropriate place within the loop premises; acting as a timer
  when the motor is stalling and inducing a disabled state when the timer
  pass beyond the tolerance.
  */
inline void errorDetection()
{
  switch(motor->master_enable)
  {
  case true:
    switch(motor_stall_current_switch->reading)
    {
    case true:
      error_timer++;
      break;
    case false:
      error_timer = 0;
      break;
    }
    switch(error_timer)
    {
    case C_ERROR_CHECK_TOLERANCE:
      motor->master_enable = false;
      break;
    }
    break;
  }
}

//! simple function to reset the global varaibles of the error detection.
inline void resetErrorAlgorithm()
{
  error_timer = 0;
}
#endif

/** function containing all the data serial data sending facilities.

  Sends to the serial the data concercning all the readings and settings of
  the arduino, such as the reference PWM input, the read speed and height sensor output and
  the stalling detection. When the motor is in its disabled state; the serial
  recieves only 0.

  The format of the dara is given by:
  enable; stall; ref RPM; read RPM; read Height;
  */
inline void sendData()
{
  switch(motor->master_enable)
  {
  case true:
    Serial.print("1;");
    switch(motor_stall_current_switch->reading)
    {
    case true:
      Serial.print("1");
      break;
    case false:
      Serial.print("0");
      break;
    }
    Serial.print(";");
    Serial.print(motor->current_rpm);
    Serial.print(';');
    Serial.print(sensorGetReading(motor_speed_sensor));
    Serial.print(';');
    Serial.print(sensorGetReading(height_sensor));
    Serial.print(';');
    break;
  case false:
    Serial.print('0');
    break;
  }
  Serial.write('\n');
  //-------------------------------------------------
}

/** standard initial procedure to give values for the global variables.
  @see motor
  @see motor_enable_led
  @see motor_speed_sensor
  @see height_sensor
  @see motor_stall_current_switch
  */
void setup(void)
{
  motor = motorInit(3,4,-9100/51,9100/51);
  motor_enable_led = ledInit(13,0,0,true);
  motor_speed_sensor = sensorInit(0,-9100.0/51.0,9100.0/51.0,0.180,3.820);
  height_sensor = sensorInit(3,10,90,0.5,4.50);
  motor_stall_current_switch = switchInitPullUp(7);
  //----------
  //check this drift experimentally to make the reading accurate
  //----------
  motor_speed_sensor->voltage_drift_linear = 0.0016849384;
  motor_speed_sensor->voltage_drift_const = -2.7551359119;
  //----------
#ifdef FLAG_CHECK_FOR_ERROR
  error_timer = 0;
#endif
  Serial.begin(9600);
}

/** standard looping procedure of micros and arduinos.

  If the motor state is disabled, the representing LDE is
  shutdown. All the variables are 'acted' in the abstraction that
  they do their respective hardware functions and store whatever
  results necessary in their own structure. The functions of
  error detection and serial sending are used here.

  @see errorDetection
  @see sendData
  */
void loop(void)
{
  switch(motor->master_enable)
  {
  case true:
    ledSetColor(motor_enable_led,255,0,0);
    break;
  case false:
    ledSetColor(motor_enable_led,0,0,0);
    break;
  }

  ledAct(motor_enable_led);
  sensorAct(motor_speed_sensor);
  sensorAct(height_sensor);
  switchAct(motor_stall_current_switch);
  motorAct(motor);

#ifdef FLAG_CHECK_FOR_ERROR
  errorDetection();
#endif

  sendData();
}

/** Function to read and interpret incoming serial data.

  This function is run in each loop and interprets (if any) serial
  incoming commands. These are chars in themselfs and are parsed according
  to a custom made for this project (This can be changed in the source code
  for this function).

  The commands accepted are:
  E: enable the motor.
  D: disable the motor.
  number: set this as reference RPM. Negative accepted for orientation purposes.

  Notice the capsulation of the letters: if a 'e' is sent to the arduino, it is
  ignored, for example. Also commands can be stacked to a certain degree; as the
  number parsing depends in the arduino internal function Serial.parseInt().
  */
void serialEvent()
{
  while(Serial.available() > 0)
  {
    switch(Serial.peek())
    {
    case 'E':
      motor->master_enable = true;
#ifdef FLAG_CHECK_FOR_ERROR
      resetErrorAlgorithm();
#endif
      Serial.read();
      break;
    case 'D':
      motor->master_enable = false;
      Serial.read();
      break;
    default:
      motor->current_rpm = Serial.parseInt();
#ifdef FLAG_CHECK_FOR_ERROR
      resetErrorAlgorithm();
#endif
      break;
    }
  }
}
