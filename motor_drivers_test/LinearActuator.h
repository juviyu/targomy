#ifndef LINEARACTUATOR_h
#define LINEARACTUATOR_h

#include "Actuator.h"
#include <Servo.h>

class LinearActuator : public Actuator {

  protected:
    const int servoToPotRange[2][2] = {{1050, 950}, {1950, 90}}; // maps to int : 0 - 100
    const int servoSetpointTreshold = 5;

  private:
    int potPin;
    int pin;
    int servoTargetPos;
    int potTarget;
    int currentServoPos;

    unsigned long maxTimeToReachPos;
    unsigned long timeForNextActuatorStep;
    int stepDuration;
    uint8_t servoStepSize;

    Servo servo;

  public:
    LinearActuator(int pin, int potPin);
    void setup() override;
    void update() override;
    bool servoReachedPos();
    int getServoPos();
    ActuatorState getState();
    void setTarget(int targetPos, int speed, unsigned long timout);
};

#endif
