#include "LinearActuator.h"

LinearActuator::LinearActuator(int pin, int potPin) {
  this->pin = pin;
  this->potPin = potPin;
  this->servo = Servo();
}

void LinearActuator::setup() {
  servo.attach(pin);  // Attach the Servo object to the pin
  pinMode(potPin, INPUT);
}

void LinearActuator::onSetTarget() {
  servoOutputVal = getServoPosMicroSeconds();
  servoGoalMicroseconds = map(targetPos, 0, 100, SERVO_TO_POT_RANGE[0][0], SERVO_TO_POT_RANGE[0][1]);
  moveDirection = servoGoalMicroseconds > servoOutputVal ? 1 : -1;
}

// Update the actuator's state and position
void LinearActuator::onUpdate() {
  if (millis() >= timeForNextActuatorStep) {
    timeForNextActuatorStep = millis() + stepDuration;

    bool keepAdjustingOutput = moveDirection > 0 ? (servoOutputVal <= servoGoalMicroseconds) : (servoOutputVal >= servoGoalMicroseconds);
    if (keepAdjustingOutput)
      servoOutputVal += moveDirection * SERVO_STEP_SIZE;
  }

  if (servoReachedGoal())
    state = SUCCESS;
  else
    servo.writeMicroseconds(servoOutputVal);
}

void LinearActuator::onTimeoutReached() {
  servo.detach();
}


int LinearActuator::getServoPosMicroSeconds() {
  return map(analogRead(potPin),
             SERVO_TO_POT_RANGE[1][0], SERVO_TO_POT_RANGE[1][1],
             SERVO_TO_POT_RANGE[0][0], SERVO_TO_POT_RANGE[0][1]);
}

// Check if the servo has reached its goal position
bool LinearActuator::servoReachedGoal() {
  return abs(servoGoalMicroseconds - getServoPosMicroSeconds()) < SERVO_GOAL_THRSHLD_MICROS;
}
