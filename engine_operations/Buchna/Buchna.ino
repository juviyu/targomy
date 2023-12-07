#include <Servo.h>
/*********
 * How to use Actuaor:
    L12-I Micro Linear Actuator 
    Pinout:
    Green - Current Input Signal (4-20mA)
    Blue - Voltage Input Signal (0-5V)
    Purple - Position Feedback Signal (Proportional 0-3.3V - Read values are in reverse)
    White - RC Input Signal (Servo Compatible)
    Red - Power (6V or 12V)
    Black - Ground
*********/
Servo buchna;
int ana_val;

#define MIN_PWM_VAL 1000
#define MAX_PWM_VAL 2000

#define PWM_OUTPUT_PIN 4
#define PWM_INPUT_PIN A7 //(20)
//(20) A6 - (21) A7
#define FULLY_OUT_PWM 1950
#define FULLY_IN_PWM 1050

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    buchna.attach(PWM_OUTPUT_PIN);
    pinMode(PWM_INPUT_PIN,INPUT);
}

void loop() {
    // Note that Actuaor real accepted values
    // are in between (1050-1950)

    // Fully out
    buchna.writeMicroseconds(FULLY_OUT_PWM);    
    delay(10000); // Note that movement is significatly slow
    ana_val = analogRead(PWM_INPUT_PIN);
    ana_val = map(ana_val, 0, 1023, MAX_PWM_VAL, MIN_PWM_VAL);
    Serial.print("Analog Value: ");
    Serial.println(ana_val);
    Serial.println("Done 1950");
    
    // Fully in
    buchna.writeMicroseconds(FULLY_IN_PWM);
    delay(10000); // Note that movement is significatly slow
    ana_val = analogRead(PWM_INPUT_PIN);
    ana_val = map(ana_val, 0, 1023, MAX_PWM_VAL, MIN_PWM_VAL);
    Serial.print("Analog Value: ");
    Serial.println(ana_val);
    Serial.println("Done 1050");
}
