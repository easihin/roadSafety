#include "headers/global.h"

// might send a message, don't know yet
void riskHydroplaning(){
    int tyrePressure = 35; //psi
    int waterThreshold = 0; //0.3 cm on the sensor is some value idk yet
    float speedThreshold =  10.35 * sqrt(tyrePressure); // how many km/h
    int isHydroplaning;
    
    if (getWaterValue() > waterThreshold && getSpeed() > speedThreshold) {
        isHydroplaning = 1;
        printLCD(isHydroplaning);
    }
    isHydroplaning = 0;
}