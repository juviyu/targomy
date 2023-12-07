#include <Servo.h> 
//#include <pthread.h>
#include <NativeEthernet.h>

/*MultiThreading Definitions*/
//pthread_mutex_t com_lock;
//pthread_t sender_thread;
/***************************/

//Targonel
Servo bochna1_targonel;
Servo bochna2_targonel; 
Servo servo_targonel; // safety for buchnot 

//Hasama
Servo bochna1_hasama;
Servo bochna2_hasama; 
Servo motor_grifa;
Servo servo_maglesha;
Servo servo_neitza;

//communications
byte mac[] = {0x04, 0xE9, 0xE5, 0x14, 0x34, 0xB4}; //TODO: Check valid MAC (Depending on teensy) 80
IPAddress ip(100, 22, 13, 59);
EthernetServer server(1234);


/* PINS SETUP */
//Targonel
#define BOCHNA1_TARGONEL_CONTROL_PIN 2
#define BOCHNA1_TARGONEL_SENSOR_PIN A16 //pin 40

#define BOCHNA2_TARGONEL_CONTROL_PIN 28
#define BOCHNA2_TARGONEL_SENSOR_PIN A15 //pin 39

#define SERVO_TARGONEL_CONTROL_PIN 3

//Hasama
#define BOCHNA1_HASAMA_CONTROL_PIN 4
#define BOCHNA1_HASAMA_SENSOR_PIN A7 //pin 21

#define BOCHNA2_HASAMA_CONTROL_PIN 5
#define BOCHNA2_HASAMA_SENSOR_PIN A6 //pin 20

//Grifa - DC brushed motor
#define GRIFA_DIR1_CONTROL_PIN 19
#define GRIFA_DIR2_CONTROL_PIN 20
#define GRIFA_SPEED_CONTROL_PIN 8

#define SERVO_MAGLESHA_CONTROL_PIN 37

#define SERVO_NEITZA_CONTROL_PIN 36

#define SWITCH1_SENSOR_PIN A13
#define SWITCH2_SENSOR_PIN A12

/*Constant Definitions*/
#define TEENSY_MAX_INPUT_VAL 1023
#define TEENSY_MIN_INPUT_VAL 0
#define MAX_PWM_VAL 2000
#define MIN_PWM_VAL 1000
const int grifa_speed = 5;
/**********************/
/*Application Functions*/

/*Send function*/
// In here we set a function that will send the values
// of global variables. This will allow us to quentify the
// number o bytes our client will recieve and manage 
// the communication more easily.

int bochna1_targonel_analog_input = 0;
int bochna2_targonel_analog_input = 0;
int bochna1_hasama_analog_input = 0;
int bochna2_hasama_analog_input = 0;
int switch1_val = 0;
int switch2_val = 0;


void send_status_to_client(EthernetClient client){ // sample and send
//        pthread_mutex_lock(&com_lock);
    client.print(bochna1_targonel_analog_input);
    client.print(" ");
    client.print(bochna2_targonel_analog_input);
    client.print(" ");

    client.print(bochna1_hasama_analog_input);
    client.print(" ");
    client.print(bochna2_hasama_analog_input);
    client.print(" ");
    
    client.print(switch1_val);
    client.print(" ");
    client.print(switch2_val);
    client.println(" ");
//        pthread_mutex_unlock(&com_lock);
    delay(500); // TODO: check if delay main program too 
}



//a function that recieves a bochna analog read and converts the 
int ReadBochna(int bochna_analog_pin){
    int ana_val = analogRead(bochna_analog_pin);
    return map(ana_val, TEENSY_MIN_INPUT_VAL, TEENSY_MAX_INPUT_VAL, MAX_PWM_VAL, MIN_PWM_VAL);
}

void TurnMotor(int dir1_pin, int dir2_pin, int speed_pin){
    digitalWrite(dir1_pin, HIGH);
    digitalWrite(dir2_pin, LOW);
    analogWrite(speed_pin, grifa_speed); //speed val [0,255]
}

//turns motor off
void TurnOFF(int dir1_pin, int dir2_pin, int speed_pin){
    digitalWrite(dir1_pin, LOW);
    digitalWrite(dir2_pin, LOW);
    analogWrite(speed_pin, 0);
}

//grifa function- forward and backward control
void Grifa(EthernetClient client, int control){
    bool stop_ = false;
    while(!stop_){
        if(control){ //forward
            TurnMotor(GRIFA_DIR1_CONTROL_PIN, GRIFA_DIR2_CONTROL_PIN, GRIFA_SPEED_CONTROL_PIN);
        }
        else { //backward
            TurnMotor(GRIFA_DIR2_CONTROL_PIN, GRIFA_DIR1_CONTROL_PIN, GRIFA_SPEED_CONTROL_PIN);
        } 
        stop_ = (bool) digitalRead(SWITCH1_SENSOR_PIN); //TODO: check digitalRead is the right way
//        send_status_to_client();
    } 
}
// a function that recieves a msg(0/1)and a bochna and moves it
void MoveBochnot(EthernetClient client, Servo bochna1, Servo bochna2, int bochna1_analog_pin,
                 int bochna2_analog_pin, int control, int UPPER_BOUND, int LOWER_BOUND){
    bool stop_ = false;
    int bochna1_analog_val, bochna2_analog_val;
    int next_location = (control) ? (LOWER_BOUND + 25): (UPPER_BOUND - 25); // 1 meaning going out - 0 going in 
    while(!stop_){
        
        while(true){ // set actuators to same position
//            pthread_mutex_lock(&com_lock);
            bochna1_analog_val = ReadBochna(bochna1_analog_pin);
            bochna2_analog_val = ReadBochna(bochna2_analog_pin);
            Serial.print("bochna1_analog_val :");
            Serial.print(bochna1_analog_val);
            Serial.print("bochna2_analog_val :");
            Serial.println(bochna2_analog_val);
//            send_status_to_client(); // TODO: preferbly put in a thread
//            pthread_mutex_unlock(&com_lock);
            int diff = bochna1_analog_val - bochna2_analog_val;
            if(diff > 25){
                //move bochna2 and hold1
                bochna2.writeMicroseconds(bochna1_analog_val);
                delay(50);
            }
            else if(diff < -25){
                //move bochna1 and hold2
                bochna1.writeMicroseconds(bochna2_analog_val);
                delay(50);
            }
            else{
                break;
            }
        }
        bochna1.writeMicroseconds(next_location);
        bochna2.writeMicroseconds(next_location);
        delay(10);
        next_location = (control) ? (next_location + 1) : (next_location - 1);
        stop_ = (control && (next_location == 1975)) || (!control && (next_location == 1025));
    }
}

/**********************/



void setup() {
    //Targonel
    bochna1_targonel.attach(BOCHNA1_TARGONEL_CONTROL_PIN);
    pinMode(BOCHNA1_TARGONEL_SENSOR_PIN, INPUT); 
    
    bochna2_targonel.attach(BOCHNA2_TARGONEL_CONTROL_PIN); 
    pinMode(BOCHNA2_TARGONEL_SENSOR_PIN, INPUT); 
    
    servo_targonel.attach(SERVO_TARGONEL_CONTROL_PIN);
    
    //Hasama
    bochna1_hasama.attach(BOCHNA1_HASAMA_CONTROL_PIN);
    pinMode(BOCHNA1_HASAMA_SENSOR_PIN, INPUT);  
    
    bochna2_hasama.attach(BOCHNA2_HASAMA_CONTROL_PIN); 
    pinMode(BOCHNA2_HASAMA_SENSOR_PIN, INPUT);
    
    //Grifa - DC brushed
//    pinMode(GRIFA_DIR1_CONTROL_PIN ,OUTPUT);
//    pinMode(GRIFA_DIR2_CONTROL_PIN ,OUTPUT);
//    pinMode(GRIFA_SPEED_CONTROL_PIN ,INPUT);
    
    //Maglesha
    servo_maglesha.attach(SERVO_MAGLESHA_CONTROL_PIN);
    //Neitza
    servo_neitza.attach(SERVO_NEITZA_CONTROL_PIN);
    
    pinMode(SWITCH1_SENSOR_PIN, INPUT);
    pinMode(SWITCH2_SENSOR_PIN, INPUT);
  

    //Communication
    Ethernet.begin(mac, ip);
    while(true){
        if(Ethernet.hardwareStatus() == EthernetNoHardware){
            Serial.println("Ethernet phy not working");
            delay(1000); //Wait for a second and try again
        }
        else{
            break;
        }
    }
    while(true){
        if(Ethernet.linkStatus() == LinkOFF){
            Serial.println("Ethernet cable is not connected");
            delay(1000); //Wait for a second and try again
        }
        else{
            break;
        }
    }    
    server.begin();
    Serial.print("server is at ");
    Serial.println(Ethernet.localIP());
    
    /*
    if(pthread_mutex_init(&com_lock, NULL) != 0 ){
        Serial.println("Mutex init failed");
    }
    if(pthread_create(&sender_thread, NULL, &send_to_client,NULL) != 0){
        Serial.println("Thread can't be created :(");
    }
    */
}


void loop() {
    //read messeges from Ethernet 
    //send indications
    EthernetClient client = server.accept();
    if (client){
        while (client.connected()){
            send_status_to_client(client); // TODO: preferbly put in a thread
            if (client.available()){
                //messeges from GUI
                char com = client.read(); //TODO: consider changing to int
                Serial.println(com);
                int command_;
                switch(com){
                    case '0'...'1':
                        command_ = com - '0';
                        Grifa(client, command_);
                        break;
                    case '2'...'3': //bochna1 targonel
                        command_ = (com - '0') - 2;
                        Serial.println(command_);
                        MoveBochnot(client, bochna1_hasama, bochna2_hasama,
                                    BOCHNA1_HASAMA_SENSOR_PIN, BOCHNA2_HASAMA_SENSOR_PIN,
                                    command_, 1950, 1050);
                        break;
                    default:
                        break;
                        
                }
            }
        }
        Serial.println("Client Disconnected");
    }
}
