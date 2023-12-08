
/* PINS SETUP */

//communications
//byte mac[] = {0x04, 0xE9, 0xE5, 0x14, 0x34, 0xB4}; //TODO: Check valid MAC (Depending on teensy) 80
//IPAddress ip(100, 22, 13, 59);
//ConnectionPort = 1234;

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
