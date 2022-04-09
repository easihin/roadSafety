#include "headers/global.h"

int tyrePressure, waterThreshold, isHydroplaning;
float speedThreshold;

void riskHydroplaning() {
    safeDriving();

    tyrePressure = 35; //psi
    waterThreshold = 120; //0.25 cm on the sensor 
    speedThreshold =  10.35 * sqrt(tyrePressure); // how many km/h
    
    isHydroplaning = 0;

    if (getWaterValue() > waterThreshold && getSpeed() > speedThreshold) {
        isHydroplaning = 1;
        printLCD(isHydroplaning);
        sendMessage(4);
    }

}
