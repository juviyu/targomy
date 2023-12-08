#ifndef LINEARACTUATOR_h
#define LINEARACTUATOR_h

#include "Actuator.h"

class LinearActuator : public Actuator {
 private:
  int potPin;

 public:
  LinearActuator(int pin, int potPin, unsigned long timeout);
  void setup() override;
  void update() override;
};

#endif
