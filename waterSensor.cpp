#include "headers/global.h"

// Water Sensor variables
int analogwaterPin = A0;
int water_value;

int getWaterValue() {
   water_value = analogRead(analogwaterPin);
   Serial.print("sensor = ");
   Serial.println(water_value);
   return water_value;

   if (water_value > 300) {
      sendLocation();
      sendMessage(3);
   }
}
