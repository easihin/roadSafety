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

// header files
#include "connect.h"
#include "positioning.h"
#include "sensors.h"
#include "hydroplaning.h"

#endif