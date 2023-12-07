#define PWMH_PIN 8
#define DIR_PIN 9

void moveMotor(int value, bool dir){
    digitalWrite(DIR_PIN, dir);
    analogWrite(PWMH_PIN, value);
}

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(PWMH_PIN, OUTPUT);
    pinMode(DIR_PIN, OUTPUT);
}

void loop() {
    // put your main code here, to run repeatedly:
    Serial.println("Dir 1");
    moveMotor(255, true);
    delay(5000);
    Serial.println("Dir 2");
    moveMotor(100, false);
    delay(5000);
}
