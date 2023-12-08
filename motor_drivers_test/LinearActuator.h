#ifndef LINEARACTUATOR_h
#define LINEARACTUATOR_h

#include "Actuator.h"
#include <Servo.h>

class LinearActuator : public Actuator {

private:
  const int SERVO_TO_POT_RANGE[2][2] = { { 1050, 1950 }, { 90, 950 } };  // maps to int : 0 - 100
  const int SERVO_GOAL_THRSHLD_MICROS = 15;
  int SERVO_STEP_SIZE = 1;
  int moveDirection = 0;

  Servo servo;
  int potPin;
  int pin;
  int servoOutputVal;
  int servoGoalMicroseconds;

  unsigned long timeForNextActuatorStep;
  int stepDuration;

  bool servoReachedGoal();
  int getServoPosMicroSeconds();

  void onUpdate();
  void onSetTarget();
  void onTimeoutReached();

public:
  void setup();
  LinearActuator(int pin, int potPin);
};

#endif
