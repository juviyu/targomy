#include "LinearActuator.h"

LinearActuator::LinearActuator(int pin, int potPin) : pin(pin), potPin(potPin) {
}

void LinearActuator::setup() {
 pinMode(pin, OUTPUT);
 pinMode(potPin, INPUT);
}

void LinearActuator::update() {
 int potValue = analogRead(potPin);
 int target = map(potValue, 0, 1023, 0, 100);
 set_target(target, timeout);

 if (target > 50) {
   digitalWrite(pin, HIGH);
 } else {
   digitalWrite(pin, LOW);
 }
}
