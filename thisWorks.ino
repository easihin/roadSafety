#include "headers/global.h"

void setup(){
  Serial.begin(9600);
  
  startLCD();
  
  initAccel();
  
  beginGPS();

  connectWifi();
  connectServer();
}

void loop(){

  // push button
  checkPushed();
  
  // accelerometer stuff
  positioning();
  checkPositions();
  
  // is it hydroplaning? just letting this thing run and loop around
  riskHydroplaning();
  
  delay(100);

  // this might be stupid because idk if the other values can overwrite this. needs to loop around tho
  printLCD(0);
  
  // Reconnect
  checkConnection();
  clientLoop();
  
}