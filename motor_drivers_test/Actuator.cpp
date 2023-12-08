#include "Actuator.h"

//Actuator::Actuator(int pin) : pin(pin) {
// pinMode(pin, OUTPUT);
//}

void Actuator::setTarget(int target,int speed, unsigned long timeout) {
  this->target = target;
  this->timeout = timeout;
  startTime = millis();
}


bool Actuator::_timeoutReached() {
  return (millis() - startTime) >= timeout;
}
