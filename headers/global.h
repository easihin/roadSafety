#ifndef GLOBAL_H
#define GLOBAL_H

// arduino libraries
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ADXL345.h>
#include <I2Cdev.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

// cpp libraries
#include <utility>
#include <iostream>
#include <math.h>
#include <tuple>
#include <unistd.h>
#include <stdlib.h>


// header files
#include "connect.h"

// hydroplaning
void riskHydroplaning();

// positioning
void initAccel();
void positioning();
void checkPositions();

// button
extern int buttonVal;
int checkPushed();

// gps
std::tuple<float, float> getLocation();
void beginGPS();
int getSpeed();
int checkTime();
void isSafe();
// int getCurrentSecond();

// lcd
void startLCD();
void printLCD(int);
void safeDriving();

// water sensor
int getWaterValue();

#endif