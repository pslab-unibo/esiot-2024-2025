#ifndef __SERVO_MOTOR_IMPL__
#define __SERVO_MOTOR_IMPL__

#include "servo_motor.h"
#include <arduino.h>
#include "ServoTimer2.h"

class ServoMotorImpl: public ServoMotor {

public:
  ServoMotorImpl(int pin);

  void on();
  bool isOn();
  void setPosition(int angle);
  void off();
    
private:
  int pin; 
  bool _on;
  ServoTimer2 motor; 
};

#endif
