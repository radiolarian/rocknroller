#include "TinyGPS++"

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
      		displayGPS();
    	}
  	}
}

void displayGPS() {
  char field[20];
  getField(field, 0);
  if (strcmp(field, "$GPRMC") == 0) {

    Serial1.print("LAT: ");
    getField(field, 3);    // number
    Serial1.print(field);
    getField(field, 4);
    Serial1.print(" ");
    Serial1.print(field);
    Serial1.print("LONG: ");
    getField(field, 5);
    Serial1.print(field);
    getField(field, 6);
    Serial1.println(field);
    Serial1.print("SPEED: ");
    getField(field, 7);
    Serial1.println(field);
    Serial1.print("DATESTAMP: ");
    getField(field, 9);
    Serial1.println(field);
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