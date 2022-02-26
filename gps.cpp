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
