#include "headers/global.h"

TinyGPSPlus gps;

// (TX, RX)
SoftwareSerial gps_ss(2, 0);

float LAT, LONG;

using namespace std;

std::tuple<float, float> getLocation() {
  LAT = gps.location.lat();
  LONG = gps.location.lng();

  while (gps_ss.available() > 0) {   
      if (gps.encode(gps_ss.read())) {
        if (gps.location.isValid()) {
          Serial.print("LATITUDE =");         
          Serial.println(LAT);         
          Serial.print("LONGITUDE =");         
          Serial.println(LONG);        
        }      
      }   
    } 
  return {LAT, LONG};
}

int getSpeed() {
  if (gps.encode(gps_ss.read())){
    if (gps.speed.isValid()) {
      int SPEED = gps.speed.kmph();
      return SPEED;
    }
  }
}

void beginGPS() {
  gps_ss.begin(9600);
}

void isSafe() {
  int seconds = 0;
  bool toRun = true;
  int message = 3;
  while (toRun == true) {
      printLCD(message);
      delay(1000);
      
      seconds++;
      cout << seconds << " sec " << endl;
 
      if (seconds >= 10) {
        sendMessage(2);
        message = 4;
        Serial.println("not safe");
     } else if (checkPushed() == 1) {
        toRun = false;
        Serial.println("safe");
     }
   }
}
