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
  
  // accelerometer
  positioning();
  checkPositions();
  
  // constantly check hydroplaning
  riskHydroplaning();
  
  delay(100);
  
  // Reconnect
  checkConnection();
  clientLoop();
}