#include "LinearActuator.h"

#define MIN_PWM_VAL 1000
#define MAX_PWM_VAL 2000

#define PWM_OUTPUT_PIN 4
#define PWM_INPUT_PIN A7 //(20)
//(20) A6 - (21) A7
#define FULLY_OUT_PWM 1950
#define FULLY_IN_PWM 1050


LinearActuator::LinearActuator(int pin, int potPin) {
  this->pin = pin;
  this->potPin = potPin;
  this->servo = Servo(); // Initialize the Servo object
}

void LinearActuator::setup() {
  this->servo.attach(pin); // Attach the Servo object to the pin
  pinMode(potPin, INPUT);
}

//pos (0 - 100)
//speed (0 - 100)
//speed : how much delay between steps
void LinearActuator::setTarget(int targetPos, int speed, unsigned long timout) {
  this->maxTimeToReachPos = millis() + timout;
  this->stepDuration = speed;
  this->servoStepSize = 1; // in us
  this->currentServoPos = this->getServoPos();

  this->potTarget = map(targetPos, 0, 100, servoToPotRange[0][1], servoToPotRange[1][1]);
  this->servoTargetPos = map(targetPos, 0, 100, servoToPotRange[0][0], servoToPotRange[1][0]);
  this->state = RUNNING;
}

bool isInRange(int x, int y, int range) {
  return abs(x - y) < range;
}

int LinearActuator::getServoPos()// in us
{
 return map(analogRead(potPin), servoToPotRange[0][1], servoToPotRange[1][1], servoToPotRange[0][1], servoToPotRange[1][1]);
}

bool LinearActuator::servoReachedPos() {
  int servoTargetPosInPotValues = map(this->currentServoPos, servoToPotRange[0][0], servoToPotRange[1][0], servoToPotRange[0][1], servoToPotRange[1][1]);
  Serial.printf("dist from %d to %d\n",servoTargetPosInPotValues,analogRead(potPin));
  return isInRange(servoTargetPosInPotValues, analogRead(potPin), servoSetpointTreshold);
}


void LinearActuator::update() {
  if (millis() >= maxTimeToReachPos)
    this->state = TIMEOUT;
    
  if (millis() >= timeForNextActuatorStep) //time for another step
  {
    this->timeForNextActuatorStep = millis() + stepDuration;
    int stepToAdd = currentServoPos > servoTargetPos ? servoStepSize : -servoStepSize ;
    if (this->servoReachedPos())
        this->currentServoPos += stepToAdd;
    currentServoPos = constrain(currentServoPos, servoToPotRange[0][0], servoToPotRange[1][0]);
    Serial.printf("moving to %d\n", this->currentServoPos);
  }

//  if (isInRange(currentServoPos, servoTargetPos, servoSetpointTreshold))// reached goal
//  {
//    Serial.printf("success\n");
//    this->state = SUCCESS;
//  }
//  else
//  {
    this->servo.writeMicroseconds(this->currentServoPos);
//  }
}

ActuatorState LinearActuator::getState() {
  return this->state;
}
