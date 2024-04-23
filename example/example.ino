#include <WiFi.h>
#include "wrapper.h"
#include <Wire.h>
#include "SSD1306Wire.h" 

/*
  CONFIG VARIABLES AND FUNCTION PROTOTYPES
*/
// Replace the next variables with your SSID/Password combination

const char* SSID = "IT4Project";
const char* PASSWORD = "IOT12345";

const char* mqtt_server = "192.168.10.2";  //Right IP as long as Laptop is connected to Router at School
const int port = 1883;
const char* client_name = "line1/thing19";  //Each client needs to be different for one broker

const uint8_t STATIC_IP[4] = {192, 168, 10, 119};
const uint8_t GATEWAY[4] = {192, 168, 10, 1};
const uint8_t SUBNET[4] = {255, 255, 255, 0}; 

void setupPins(); // sets up pins on ESP32
void setupWifi(); // sets up WiFi
void displayTopic(Topic& topic, int line); // writes topic to screen

#include "define.h" // includes all preprocess variables and setup functions

/*
  TOPIC + NAMESPACE INITIALIZATION
*/

// Initialize Main Topic
MqttClient client(mqtt_server, port, "line1/thing19"); // Topic to subscribe to

// other subtopics
Topic clientCount("count");
Topic clientInput("input");

void setup() {
  setupPins(); // defined in define.h
  Serial.begin(115200);
  setup_wifi();

  // add topics to subscribe to
  client.addTopic(&clientCount);
  client.addTopic(&clientInput);
  client.connect();

  display.setFont(ArialMT_Plain_10); // set fonts
  display.init();
}

int count = 0;
long lastMsg = 0;

void loop() {bool thing = true;
  long now = millis();
  clearDisplay();

  // if 1 second hasnt passed, return
  if (now - lastMsg <= 1000){
    return;
  }

  clientInput = (char*) readInput().c_str();
  clientCount = count;

  displayTopic(clientCount, 0);
  displayTopic(clientInput, 10);

  count++;
  client.publish();
  lastMsg = now;
}
