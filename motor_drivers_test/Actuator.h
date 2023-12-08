#ifndef ACTUATOR_h
#define ACTUATOR_h

#include <Arduino.h>

enum ActuatorState {
  RUNNING,
  SUCCESS,
  FAILURE,
  TIMEOUT
};

class Actuator {
  protected:
    int pin;
    unsigned long startTime;
    unsigned long timeout;
    int target;
    ActuatorState state;


  public:
    //   Actuator(int pin);
    virtual void setup() = 0; // Pure virtual function
    void setTarget(int target, int speed, unsigned long timeout);
    ActuatorState getState();
    virtual void update() = 0; // Pure virtual function
    bool _timeoutReached();
};

#endif
