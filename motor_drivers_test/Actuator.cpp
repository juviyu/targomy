#include "Actuator.h"

void Actuator::setTarget(int targetPos, int speed, unsigned long timeout)
{
  this->targetPos = targetPos;
  stepDuration = 1000 / speed; // for when speed is in steps per seconds. can be multiplied by ticks per rotation to get rot/second

  timeoutTime = millis() + timeout;
  onSetTarget();
  state = RUNNING;
}

void Actuator::update()
{
  if (millis() >= timeoutTime)
  {
    state = TIMEOUT;
    onTimeoutReached();
  }
  else
  {
    onUpdate();
  }
}

ActuatorState Actuator::getState(){
  return state;
}