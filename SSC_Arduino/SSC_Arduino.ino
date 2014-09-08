//------------------------------------------------------------
// arduino control software designed for the tests on the drill project, SSC, Surrey.
// The Key idea is to adopt an object approach and abstract as much
// as possible without constraining performance of the controller or the system
// overall.
//
// Rodolfo Jordao, 2014.
//------------------------------------------------------------

//------------------------------------------------------------
// Classes inclusions
//------------------------------------------------------------
#ifndef H_MOTOR
#include "Motor.h"
#define H_MOTOR
#endif
#ifndef H_LED
#include "Led.h"
#define H_LED
#endif
#ifndef H_SENSOR
#include "Sensor.h"
#define H_SENSOR
#endif
#ifndef H_UTILS
#include "utils.h"
#define H_UTILS
#endif
#ifndef H_LSR
#include "LSR.h"
#define H_LSR
#endif
#ifndef H_SWITCH
#include "Switch.h"
#define H_SWITCH
#endif
//------------------------------------------------------------

//------------------------------------------------------------
//global variables
//------------------------------------------------------------
Motor_t * motor;
Led_t * motor_enable_led;
Sensor_t * motor_speed_sensor;
Sensor_t * motor_current_sensor;
Sensor_t * height_sensor;
Switch_t * motor_above_current_switch;
Switch_t * motor_stall_current_switch;
//------------------------------------------------------------
// error detection algorithm
//------------------------------------------------------------
#define FLAG_CHECK_FOR_ERROR
#ifdef FLAG_CHECK_FOR_ERROR
#define C_ERROR_CHECK_TOLERANCE 500
unsigned int error_timer;
#endif
//------------------------------------------------------------
//------------------------------------------------------------

#ifdef FLAG_CHECK_FOR_ERROR
inline void errorDetection()
{
  switch(motor->master_enable)
  {
  case true:
    switch(motor_stall_current_switch->reading)
    {
    case true:
      motor->master_enable = false;
      break;
    case false:
      switch(motor_above_current_switch->reading)
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
    }
    break;
  }
}

inline void resetErrorAlgorithm()
{
  error_timer = 0;
}
#endif

inline void sendData()
{
  //-------------------------------------------------
  //write on Serial
  //-------------------------------------------------
  switch(motor->master_enable)
  {
  case true:
    Serial.print("1;");
    switch(motor_above_current_switch->reading)
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
    Serial.print(sensorGetReading(motor_current_sensor));
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

void setup(void)
{
  motor = motorInit(3,4,-9100/51,9100/51);
  motor_enable_led = ledInit(13,0,0,true);
  motor_speed_sensor = sensorInit(0,-9100.0/51.0,9100.0/51.0,0.180,3.820);
  motor_current_sensor = sensorInit(1,-2.6659,2.6659,0.180,3.820);
  height_sensor = sensorInit(3,8,2000,0.0,5.0);
  motor_above_current_switch = switchInit(8);
  motor_stall_current_switch = switchInit(7);
  //----------
  //check this drift experimentally to make the reading accurate
  //----------
  motor_speed_sensor->voltage_drift_linear = 0.0016849384;
  motor_speed_sensor->voltage_drift_const = -2.7551359119;
  //motor_current_sensor->voltage_drift_const = 8;
  //motor_current_sensor->voltage_drift_linear = 8/1023;
  //----------
#ifdef FLAG_CHECK_FOR_ERROR
  error_timer = 0;
#endif
  Serial.begin(9600);
}

void loop(void)
{
  //-------------------------------------------------
  //leds
  //-------------------------------------------------
  switch(motor->master_enable)
  {
  case true:
    ledSetColor(motor_enable_led,255,0,0);
    break;
  case false:
    ledSetColor(motor_enable_led,0,0,0);
    break;
  }
  //-------------------------------------------------

  //-------------------------------------------------
  //act
  //-------------------------------------------------
  ledAct(motor_enable_led);
  sensorAct(motor_speed_sensor);
  sensorAct(motor_current_sensor);
  switchAct(motor_above_current_switch);
  switchAct(motor_stall_current_switch);
  motorAct(motor);
  //-------------------------------------------------

  //-------------------------------------------------
  //error algorithm
  //-------------------------------------------------
#ifdef FLAG_CHECK_FOR_ERROR
  errorDetection();
#endif
  //-------------------------------------------------
  sendData();
}

void serialEvent()
{
  //-------------------------------------------------
  //read from Serial
  //-------------------------------------------------
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
  //-------------------------------------------------
}

