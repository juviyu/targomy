#include "LinearActuator.h"
#include "configuration.hpp"
// Create an instance of LinearActuator
LinearActuator myactuator(BOCHNA1_HASAMA_CONTROL_PIN, BOCHNA1_HASAMA_SENSOR_PIN);

void setup() {
  // Call the setup method on the actuator instance
  Serial.begin(9600);
  myactuator.setup();
  myactuator.setTarget(100, 0, 10000);
  Serial.printf("starting\n");
}

int nextpos = 0;
void loop() {
  // Call the update method on the actuator instance
  if (Serial.available()) {
    nextpos = Serial.readStringUntil('\n').toInt();
    Serial.printf("next pos:  %d\n", nextpos);
    delay(100);
    myactuator.setTarget(nextpos, 0, 10000);
  }

  myactuator.update();
  delay(10);
}
