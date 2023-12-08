#ifndef ACTUATOR_h
#define ACTUATOR_h

#include <Arduino.h>

enum ActuatorState {
 RUNNING,
 SUCCESS,
 FAILURE
};

class Actuator {
 protected:
   int pin;
   unsigned long startTime;
   unsigned long timeout;

 public:
   Actuator(int pin, unsigned long timeout);
   virtual void setup() = 0; // Pure virtual function
   void set_target(int target, unsigned long timeout);
   ActuatorState get_state();
   virtual void update() = 0; // Pure virtual function
   bool _timeoutReached();
};

#endif
