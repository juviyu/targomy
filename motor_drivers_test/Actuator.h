#ifndef ACTUATOR_h
#define ACTUATOR_h

#include <Arduino.h>

enum ActuatorState
{
  RUNNING,
  SUCCESS,
  FAILURE,
  TIMEOUT
};

class Actuator
{
protected:
  ActuatorState state;
  virtual void onUpdate() = 0;
  virtual void onTimeoutReached() = 0;
  virtual void onSetTarget() = 0;
  int targetPos;
  int stepDuration;
  unsigned long timeoutTime;

public:
  void setup(); // Pure virtual function
  void setTarget(int target, int speed, unsigned long timeout);
  ActuatorState getState();
  void update(); // Pure virtual function
};

#endif
