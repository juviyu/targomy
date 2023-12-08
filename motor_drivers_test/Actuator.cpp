#include "Actuator.h"

Actuator::Actuator(int pin, unsigned long timeout) : pin(pin), timeout(timeout) {
 pinMode(pin, OUTPUT);
}

void Actuator::set_target(int target, unsigned long timeout) {
 this->target = target;
 this->timeout = timeout;
 startTime = millis();
}

ActuatorState Actuator::get_state() {
 if (_timeoutReached()) {
   return FAILURE;
 } else {
   return RUNNING;
 }
}

bool Actuator::_timeoutReached() {
 return (millis() - startTime) >= timeout;
}

