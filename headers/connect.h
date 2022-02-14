#ifndef CONNECT_H
#define CONNECT_H

#include "Arduino.h"

extern char msgmqtt[50];

void callback(char* topic, byte* payload, unsigned int length);
void connectMQTT();
void connectWifi();
void connectServer();
void checkConnection();
void clientLoop();
void sendLocation();
void sendMessage(int);

void publishtoServer(int a);

#endif