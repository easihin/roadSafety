#ifndef SENSORS_H
#define SENSORS_H

// button
extern int buttonVal;
int checkPushed();

// gps
std::tuple<float, float> getLocation();
void beginGPS();
int getSpeed();

// lcd
void startLCD();
void printLCD(int);

// water sensor
int getWaterValue();

#endif
