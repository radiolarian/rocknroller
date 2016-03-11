//Serial1 Code inspiration from: https://forums.adafruit.com/viewtopic.php?f=25&t=85437
//Used Wifi Code from: https://www.arduino.cc/en/Tutorial/WiFiWebServer
//Other Wifi Code Could be: https://www.arduino.cc/en/Tutorial/WiFiSendReceiveUDPString


#include "TinyGPS++.h"
//#define RXPin 13
//#define TXPin 12
//#define GPSBaud 4800
//#define ConsoleBaud 115200
#include <SPI.h>
#include <WiFi.h>
#include <WiFiUdp.h>

int status = WL_IDLE_STATUS;
char ssid[] = "Yipee! 2.0";      // your network SSID (name) 
char pass[] = "Catherineisthebest";   // your network password
int keyIndex = 0;                 // your network key Index number (needed only for WEP)

unsigned int localPort = 2390;      // local port to listen on

char packetBuffer[255]; //buffer to hold incoming packet
char  ReplyBuffer[] = ""; // a string to send back

// The serial connection to the GPS device
//SoftwareSerial ss(RXPin, TXPin);

WiFiUDP Udp;

// The TinyGPS++ object
TinyGPSPlus gps;

void setup()
{
  //pinMode(13, OUTPUT); TRYING TO TEST WHAT MADE MY BOARD TURN OFF

  //GPS
   Serial.begin(9600);
   Serial1.begin(9600);

   Serial.println("Getting lat/long with TinyGPS");
   Serial.println();

  //Initialize serial and wait for port to open:
  Serial.begin(9600); 
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv != "1.1.0") {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid);

    // wait 10 seconds for connection:
    delay(10000);
  }

  Serial.println("Connected to wifi");
  printWifiStatus();

  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  Udp.begin(localPort);

   
}

void loop()
{
  // If any characters have arrived from the GPS,
  // send them to the TinyGPS++ object
  while (Serial1.available() > 0)
    gps.encode(Serial1.read());

  // Let's display the new location and altitude
  // whenever either of them have been updated.
  if (gps.location.isUpdated() || gps.altitude.isUpdated())
  {
    Serial.print("Location: "); 
    Serial.print(gps.location.lat(), 6);
    Serial.print(",");
    Serial.print(gps.location.lng(), 6);
    //now save lat/long to SD card
  }

  //---------DON'T KNOW IF THIS PART IF NECESSARY----------
 
  // // if there's data available, read a packet
  // int packetSize = Udp.parsePacket();
  // if (packetSize) {
  //   Serial.print("Received packet of size ");
  //   Serial.println(packetSize);
  //   Serial.print("From ");
  //   IPAddress remoteIp = Udp.remoteIP();
  //   Serial.print(remoteIp);
  //   Serial.print(", port ");
  //   Serial.println(Udp.remotePort());

  //   // read the packet into packetBufffer
  //   int len = Udp.read(packetBuffer, 255);
  //   if (len > 0) {
  //     packetBuffer[len] = 0;
  //   }
  //   Serial.println("Contents:");
  //   Serial.println(packetBuffer);
  
  //-----------THINK WE CAN JUST USE LINES AFTER THIS-------------


    // send a reply, to the IP address and port that sent us the packet we received
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write("%f, %f", gps.location.lat(), gps.location.lng());
    Udp.endPacket();
  }

  //TRYING TO TEST WHAT MADE MY BOARD TURN OFF
  // digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  // delay(4000);              // wait for a second
  // digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  // delay(1000);              // wait for a second
}

void printWifiStatus() {
// print the SSID of the network you're attached to:
Serial.print("SSID: ");
Serial.println(WiFi.SSID());

// print your WiFi shield's IP address:
IPAddress ip = WiFi.localIP();
Serial.print("IP Address: ");
Serial.println(ip);

// print the received signal strength:
long rssi = WiFi.RSSI();
Serial.print("signal strength (RSSI):");
Serial.print(rssi);
Serial.println(" dBm");
}


