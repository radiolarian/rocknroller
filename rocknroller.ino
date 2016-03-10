#include <SoftwareSerial.h> 
#include "TinyGPS++.h"
#define RXPin 2
#define TXPin 3
#define GPSBaud 4800
#define ConsoleBaud 115200

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

// The TinyGPS++ object
TinyGPSPlus gps;

void setup()
{
  Serial.begin(ConsoleBaud);
  ss.begin(GPSBaud);

  Serial.println("Getting lat/long with TinyGPS");
  Serial.println();
}

void loop()
{
  // If any characters have arrived from the GPS,
  // send them to the TinyGPS++ object
  while (ss.available() > 0)
    gps.encode(ss.read());

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
}