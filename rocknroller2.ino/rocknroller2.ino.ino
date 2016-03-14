#include "TinyGPS++.h"
const int data_size = 80;
char data[data_size];

void setup() 
{
  Serial.begin(9600);
    delay(2000);
    Serial.print("Hello");
    Serial.println(F("GPS Activating"));
    Serial1.begin(9600);
}

void loop() 
{
  static int i = 0;
    if (Serial1.available()) {
      char ch = Serial1.read();
      if (ch != '\n' && i < data_size) {
        data[i] = ch;
          i++;
      }
      else {
          data[i] = '\0';
          i = 0;
          displayGPSFull();
//          displayGPSConverted();
      }
    }
}

void displayGPSFull() {
  char field[20];
  getField(field, 0);
  if (strcmp(field, "$GPRMC") == 0) {
    Serial1.print("LAT: ");
    getField(field, 3);    // Latitude: All degrees, two digits of minutes  .  decimals of minutes
    Serial1.print(field);
    Serial1.print(" ");
    getField(field, 4);     //Direction
    Serial1.println(field);
    
    Serial1.print("LONG: ");    
    getField(field, 5);     //Longitude
    Serial1.print(field);
    Serial1.print(" ");
    getField(field, 6);     //Direction
    Serial1.println(field);
    Serial1.println("");
  }
}

void displayGPSConverted() {
  char field[20];
  getField(field, 0);
  if (strcmp(field, "$GPRMC") == 0) {
    float converted = 0;

    Serial1.print("LAT: ");
    getField(field, 3);    // Latitude: All degrees, two digits of minutes  .  decimals of minutes
    converted = conv_coords(field);
    getField(field, 4);     //Direction
    if (strcmp(field, "S") == 0) {
      converted = 0 - converted;
    }
    Serial1.println(converted);
    
    Serial1.print("LONG: ");    
    getField(field, 5);     //Longitude
    converted  = conv_coords(field);
    getField(field, 6);     //Direction
    if (strcmp(field, "W") == 0) {
      converted = 0 - converted;
    }
    Serial1.println(converted);
    Serial1.println("");
  }
}

void getField(char* buffer, int index) {
  int data_pos = 0;
  int field_pos = 0;
  int comma = 0;
  while (data_pos < data_size) {
    if (data[data_pos] == ',') {
      comma ++;
      data_pos ++;
    }
    if (comma == index) {
      buffer[field_pos] = data[data_pos];
      field_pos ++;
    }
    data_pos ++;
  }
  buffer[field_pos] = '\0';
}

float conv_coords(char* in_coords){
  float f = (float)atof(in_coords);
  int firsttwodigits = ((int)f)/100; //This assumes that f < 10000.
  float nexttwodigits = f - (float)(firsttwodigits*100);
  float theFinalAnswer = (float)(firsttwodigits + nexttwodigits/60.0);
  return theFinalAnswer;
  }
