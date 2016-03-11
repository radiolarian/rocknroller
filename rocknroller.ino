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

char ssid[] = "Yipee! 2.0";      // your network SSID (name) 
char pass[] = "Catherineisthebest";   // your network password
int keyIndex = 0;                 // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

WiFiServer server(80);

// The serial connection to the GPS device
//SoftwareSerial ss(RXPin, TXPin);

// The TinyGPS++ object
TinyGPSPlus gps;

void setup()
{
 pinMode(13, OUTPUT);

  //Initialize serial and wait for port to open:
  Serial.begin(9600); 
 // while (!Serial) {
 //   ; // wait for serial port to connect. Needed for Leonardo only
 // }
  
//  // check for the presence of the shield:
//  if (WiFi.status() == WL_NO_SHIELD) {
//    Serial.println("WiFi shield not present"); 
//    // don't continue:
//    while(true);
//  } 
 
  // attempt to connect to Wifi network:
//  while (status != WL_CONNECTED) { 
//    Serial.print("Attempting to connect to SSID: ");
//    Serial.println(ssid);
//    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:    
//    status = WiFi.begin(ssid, pass);
//
//    // wait 10 seconds for connection:
//    delay(10000);
//  } 
//  server.begin();
// // you're connected now, so print out the status:
// printWifiStatus();


   //GPS
   Serial.begin(9600);
   Serial1.begin(9600);

   Serial.println("Getting lat/long with TinyGPS");
   Serial.println();
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

 // listen for incoming clients
 // WiFiClient client = server.available();
 // if (client) {
 //   Serial.println("new client");
 //   // an http request ends with a blank line
 //   boolean currentLineIsBlank = true;
 //   while (client.connected()) {
 //     if (client.available()) {
 //       char c = client.read();
 //       Serial.write(c);
 //       // if you've gotten to the end of the line (received a newline
 //       // character) and the line is blank, the http request has ended,
 //       // so you can send a reply
 //       if (c == '\n' && currentLineIsBlank) {
 //         // send a standard http response header
 //         client.println("HTTP/1.1 200 OK");
 //         client.println("Content-Type: text/html");
 //         client.println("Connection: close");  // the connection will be closed after completion of the response
 //         client.println("Refresh: 5");  // refresh the page automatically every 5 sec
 //         client.println();
 //         client.println("<!DOCTYPE HTML>");
 //         client.println("<html>");
         // output the value of the GPS longitude and latitude.

            //POTENTIALLY WHAT WE WANT
            // client.println(gps.location.lat(), 6);
            // client.print(",");
            // client.print(gps.location.lat(), 6);
 //         client.println("</html>");
 //          break;
 //       }

 //       if (c == '\n') {
 //         // you're starting a new line
 //         currentLineIsBlank = true;
 //       } 
 //       else if (c != '\r') {
 //         // you've gotten a character on the current line
 //         currentLineIsBlank = false;
 //       }
 //     }
 //   }
 //   // give the web browser time to receive the data
 //   delay(1);
   
 //   // close the connection:
 //   client.stop();
 //   Serial.println("client disonnected");
 // }

  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(4000);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
}

// void printWifiStatus() {
// // print the SSID of the network you're attached to:
// Serial.print("SSID: ");
// Serial.println(WiFi.SSID());
//
// // print your WiFi shield's IP address:
// IPAddress ip = WiFi.localIP();
// Serial.print("IP Address: ");
// Serial.println(ip);
//
// // print the received signal strength:
// long rssi = WiFi.RSSI();
// Serial.print("signal strength (RSSI):");
// Serial.print(rssi);
// Serial.println(" dBm");
// }


