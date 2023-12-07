#include <NativeEthernet.h>

/************* Server Configuration Set up **********/
byte mac[] = {0x04,0xE9,0xE5,0x14,0x34,0xB4};
IPAddress ip(100, 22, 13, 59);
EthernetServer server(1234);
/************* Server Configuration Set up **********/


void setup() {
  Serial.begin(9600);
  while (!Serial) {;}
  Ethernet.begin(mac, ip);
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("ethernet physical not working");
    while (true) {delay(1);}
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}



void loop() {
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.println(c);
        String response = "Hello, from teensy!";
        int num = 1234;
        server.println(response);
        server.println(num);
      }
    }
    delay(1);
    client.stop();
    Serial.println("client disconnected");
  }
}
