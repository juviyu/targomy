#include <NativeEthernet.h>
#include <Servo.h>
/************* Server Configuration Set up **********/
byte mac[] = {0x04,0xE9,0xE5,0x14,0x34,0x08};
IPAddress ip(192, 168, 1, 5);
EthernetServer server(1234);
/************* Server Configuration Set up **********/

Servo myservo;
int pos = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial && millis() < 2000) {;}
  Ethernet.begin(mac, ip);
  delay(10);
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("ethernet phy not working");
    while (true) {delay(1);}
  }
  delay(10);
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }
  delay(10);
  server.begin();
  delay(10);
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  delay(10);
  myservo.attach(20);
  delay(10);
}



void loop() {
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    while (client.connected()) { 
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        Serial.print("\n");
        if(c == '1'){
            if(pos < 350){
                pos += 10;
                myservo.write(pos);
                String response = "Sent to servo:";
                client.println(response);
                client.println(pos);
                Serial.println(pos);
            }
        }
        if(c == '0'){
            if(pos > 0){
                pos -= 10;
                myservo.write(pos);
                String response = "Sent to servo:";
                client.println(response);
                client.println(pos);
                Serial.println(pos);
            }
        }
      }
    }
    delay(1);
    client.stop();
    Serial.println("client disconnected");
  }
  delay(10);
}
