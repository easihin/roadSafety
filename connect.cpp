#include "headers/global.h"

WiFiClient espClient;
PubSubClient client(espClient);

char wifiName[10] = "My ASUS"; 
char wifiPass[20] = "12345667889";

void connectMQTT() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
    } 
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("try again in 5 seconds");
      delay(10000);
    }
  }
}

char msgmqtt[50];
void callback(char* topic, byte* payload, unsigned int length) {
  String MQTT_DATA = "";
  for (int i=0 ; i < length ; i++) {
    MQTT_DATA += (char)payload[i];
  }
}

void connectWifi() {
    WiFi.disconnect();
    Serial.println("Starting to connect WiFI...");
    WiFi.begin(wifiName, wifiPass);

    while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.println("re-Connecting . .. ... ");
    }
  
    Serial.println("Conected to WiFi");
    Serial.println("Your nodeMcu IP Address=");
    Serial.println((WiFi.localIP().toString()));
    Serial.println("Your Gateway IP=");
    Serial.println((WiFi.gatewayIP().toString().c_str()));
    
    Serial.println("Connecting to server (Broker) MQTT ... ");
    client.setServer("broker.mqttdashboard.com", 1883);
    client.setCallback(callback);
}

void connectServer() {
    Serial.println("Connecting to server (Broker) MQTT ... ");
    client.setServer("broker.mqttdashboard.com", 1883);
    client.setCallback(callback);
}

void checkConnection() {
    if (!client.connected()) {
      connectMQTT();
    }
}

void clientLoop() {
    client.loop();
}

void sendLocation() {
  // publish location
  auto [latitude, longitude] = getLocation();
  
  snprintf (msgmqtt, 50, "%f",latitude);
  client.publish("LATITUDE", msgmqtt);
  snprintf (msgmqtt, 50, "%f",longitude);  
  client.publish("LONGITUDE", msgmqtt);
}

void sendMessage(int val) {
  // val 1 -- flipped over
  // val 2 -- on the side
  // val 3 -- submerged
  // val 4 -- extreme deceleration
  
  sendLocation();

  if (val == 1) {
    // send some message to Tasia 
    // or send the value in some topic and all the if statements will on the app.
    // dk
  } else if (val == 2) {
    // send smth
  } else if (val == 3) {
    // send smth
  } else if (val == 4) {
    // send smth
  }
}

// kinda temporary because these values are rather useless to send
void publishtoServer(int val) {
    snprintf (msgmqtt, 50, "%d ", val);
    client.publish("isPushed", msgmqtt);
    
    // snprintf (msgmqtt, 50, "%d", watersensorValue);
    // client.publish("watersensorValue", msgmqtt);
    
    // snprintf (msgmqtt, 50, "%d", x_val);
    // client.publish("xVal",msgmqtt);
    
    // snprintf (msgmqtt, 50, "%d", y_val);
    // client.publish("yVal",msgmqtt);
    // 
    // snprintf (msgmqtt, 50, "%d", z_val);
    // client.publish("zVal",msgmqtt);
}