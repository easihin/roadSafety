#include "headers/global.h"

// Water Sensor variables
int analogwaterPin = A0;
int water_value;

int getWaterValue() {
   water_value = analogRead(analogwaterPin);
   Serial.print("Water Sensor: ");
   Serial.println(water_value);
   
   // submerged
   if (water_value > 300) {
      sendMessage(3);
      isSafe(3);
   }
   return water_value;

}
