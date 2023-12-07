
int in1 = 22; //make sure the pin is digital
int in2 = 21; //make sure the pin is digital
int Enable = 19; //make sure the pin is suitable for pwm


void setup() {
    pinMode(in1 ,OUTPUT);
    pinMode(in2 ,OUTPUT);
    pinMode(Enable ,OUTPUT);
}

void TurnMotorDir1(int num){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(Enable, num);
}

void TurnMotorDir2(int num){
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(Enable, num);
}

void TurnOFFA(){
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(Enable, 0);
}


void loop() {
    for(int i = 5; i <= 250; i++){ //teensy output values are [0-255]
        TurnMotorDir1(i);
        delay(10);
    }
    
    delay(3000);
    TurnOFFA();
    delay(2000);
    
    for(int i = 5; i <= 250; i++){ //teensy output values are [0-255]
        TurnMotorDir2(i);
        delay(10);
    }
    delay(3000);
    TurnOFFA();
    delay(2000);


    

}
