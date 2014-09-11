/** \file Motor.h Motor abstraction header

  This header file contains the motor abstraction and its
  corresponding functions; such as acting, switching and initialization.
  Since the abstraction is a data structure, there is no need for private
  access methods; these changes are made by directly acessing the structure
  variables.
  */

#ifndef H_ARDUINO
#include <Arduino.h>
#define H_ARDUINO
#endif

/** pseudo-class abstraction for motors.

  The implementation consists the usual \a pin_rpm to indicate the PWM output
  of the arduino, another pin to control the enable/disable state and RPM control
  variables.

  The \a max_rpm and \a min_rpm variables are necessary to make the arduino
  corretly process and act on the desired RPM, \a current_rpm. Note that the
  last variable is NOT the speed reading, but the reference speed. These variables
  and set in the initialization and can be changed by direct acess if needed later.
  */
typedef struct Motor
{
  //! Arduino pin for the PMW output.
  byte pin_rpm;
  //! Arduino pin for the enable/disable control.
  byte pin_master_enable;
  //! a variable representing the max RPM the motor can achieve.
  long max_rpm;
  //! a variable representing the min RPM the motor can achieve. This can be negative for orientation.
  long min_rpm;
  //! a varaible representing the desired speed for the motor.
  long current_rpm;
  //! internal variable controlling the enabled and disabled state.
  boolean master_enable;
}
Motor_t;

/** Motor abstraction initialization.

  For initialization, control and internal calculations; along the necessary pins
  the maximum and minimum achievable RPMs should be supplied.

  For example, in the SSC prototype; the motor could achieve 178 rpm CCW, hence
  being positive and 178 rpm CW, being then negative. This setup initialization
  would be the pin rpms with \a min_rpm_=-178 and \a max_rpm_=178.

  @param[in] pin_rpm_ Arduino PIN for the PWM output.
  @param[in] pin_master_enable_ Arduino PIN for the enable/disable control.
  @param[in] max_rpm_ Maximum RPM achievable.
  @param[in] min_rpm_ Minimum RPM achievable.
  */
Motor_t * motorInit(byte pin_rpm_, byte pin_master_enable_ ,long max_rpm_, long min_rpm_);

//! \deprecated The motor is not a class anymore. Direct change can be made and this code can be safely removed.
void motorSetRpm(Motor_t *target, long rmp);

/** Motor abstraction standard acting

  Takes care of the enable/disable state control and automatically sets the
  correct voltage PWM based upon the \a min_rpm and \a max_rpm pseudo-class
  variables.

  However an important assumption is made: the minimum RPM occurs at 10% of the
  admissable voltage apply while the maximum occurs at 90%. If that is not the
  case, the internal implementation needs to be changed. This is true for
  the ESCON 50/5 controller.
  */
void motorAct(Motor_t *target);
