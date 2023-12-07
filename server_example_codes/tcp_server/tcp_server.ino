#include <QNEthernet.h>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <vector>

// --------------------------------------------------------------------------
//  Configuration
// --------------------------------------------------------------------------

// NOTE: Not all the code here is needed

// The DHCP timeout, in milliseconds. Set to zero to not wait and
// instead rely on the listener to inform us of an address assignment.
constexpr uint32_t kDHCPTimeout = 15'000;  // 15 seconds

// The link timeout, in milliseconds. Set to zero to not wait and
// instead rely on the listener to inform us of a link.
constexpr uint32_t kLinkTimeout = 5'000;  // 5 seconds

constexpr uint16_t kServerPort = 80;

// Timeout for waiting for input from the client.
constexpr uint32_t kClientTimeout = 5'000;  // 5 seconds

// Timeout for waiting for a close from the client after a
// half close.
constexpr uint32_t kShutdownTimeout = 30'000;  // 30 seconds

// Set the static IP to something other than INADDR_NONE (all zeros)
// to not use DHCP. The values here are just examples.
IPAddress staticIP{192, 168, 1, 201};//{192, 168, 1, 101};
IPAddress subnetMask{255, 255, 255, 0};
IPAddress gateway{192, 168, 1, 1};
EthernetServer server{kServerPort};


void setup() {
    Serial.begin(115200);
    while (!Serial && millis() < 4000) {
    // Wait for Serial
    }
    Serial.println("Starting...\r\n");
    
    // Unlike the Arduino API (which you can still use), QNEthernet uses
    // the Teensy's internal MAC address by default, so we can retrieve
    // it here
    uint8_t mac[6];
    Ethernet.macAddress(mac);  // This is informative; it retrieves, not sets
    
    
    // Add listeners
    // It's important to add these before doing anything with Ethernet
    // so no events are missed.
    
    // Listen for link changes
    Ethernet.onLinkState([](bool state) {
    Serial.print("Ethernet Link");
    Serial.println(state);

    
    // Listen for address changes
    Ethernet.onAddressChanged([]() {
    IPAddress ip = Ethernet.localIP();
    bool hasIP = (ip != INADDR_NONE);
    if (hasIP) {
      Serial.println("[Ethernet] Address changed:\r\n");
    
      //printf("    Local IP = %u.%u.%u.%u\r\n", ip[0], ip[1], ip[2], ip[3]);
      ip = Ethernet.subnetMask();
      //printf("    Subnet   = %u.%u.%u.%u\r\n", ip[0], ip[1], ip[2], ip[3]);
      ip = Ethernet.gatewayIP();
      //printf("    Gateway  = %u.%u.%u.%u\r\n", ip[0], ip[1], ip[2], ip[3]);
      ip = Ethernet.dnsServerIP();
      if (ip != INADDR_NONE) {  // May happen with static IP
        //printf("    DNS      = %u.%u.%u.%u\r\n", ip[0], ip[1], ip[2], ip[3]);
      }
    } else {
      //printf("[Ethernet] Address changed: No IP address\r\n");
    }
    });
    
    if (initEthernet()) {
    // Start the server
    //printf("Starting server on port %u...", kServerPort);
        server.begin();
    //printf("%s\r\n", (server) ? "Done." : "FAILED!");
    }
}

bool initEthernet() {
  // DHCP
  if (staticIP == INADDR_NONE) {
    Serial.println("Starting Ethernet with DHCP...\r\n");
    if (!Ethernet.begin()) {
      Serial.println("Failed to start Ethernet\r\n");
      return false;
    }

    // We can choose not to wait and rely on the listener to tell us
    // when an address has been assigned
    if (kDHCPTimeout > 0) {
      Serial.println("Waiting for IP address...\r\n");
      if (!Ethernet.waitForLocalIP(kDHCPTimeout)) {
        Serial.println("No IP address yet\r\n");
        // We may still get an address later, after the timeout,
        // so continue instead of returning
      }
    }
  } else {
    // Static IP
    Serial.println("Starting Ethernet with static IP...");
    if (!Ethernet.begin(staticIP, subnetMask, gateway)) {
      Serial.println("Failed to start Ethernet");
      return false;
    }

    // When setting a static IP, the address is changed immediately,
    // but the link may not be up; optionally wait for the link here
    if (kLinkTimeout > 0) {
     Serial.println("Waiting for link...");
      if (!Ethernet.waitForLink(kLinkTimeout)) {
        Serial.println("No link yet");
        // We may still see a link later, after the timeout, so
        // continue instead of returning
      }
    }
  }

  return true;
}



void loop() {
    EthernetClient client = server.accept();
    if (client) {
        // We got a connection!
        IPAddress ip = client.remoteIP();
        Serial.print("Client connected: ")
        Serial.print(ip[0]);
        Serial.print(ip[1]);
        Serial.print(ip[2]);
        Serial.println(ip[3]);
    }
    
    // Process data from each client
    while (true) {
        int avail = client.available();
        if (avail <= 0) {
          return;
        }
        int c = client.read();
        Serial.print(c);
        if (c == '\n') {
          if (state.emptyLine) {
            break;
          }
          // Start a new empty line
          state.emptyLine = true;
        } 
    }
    
    IPAddress ip = client.remoteIP();
    Serial.print("Sending to client: ");
    Serial.print(ip[0]);
    Serial.print(ip[1]);
    Serial.print(ip[2]);
    Serial.println(ip[3]);
    client.writeFully("HTTP/1.1 200 OK\r\n"
                          "Connection: close\r\n"
                          "Content-Type: text/plain\r\n"
                          "\r\n"
                          "Hello, Client!\r\n");
}
