/*
 * A simple wrapper library for Khoi Hoang's ESP32 AsyncMQTT library
 */

#pragma once

#ifndef ASYNC_MQTT_ESP32_WRAPPER
#define ASYNC_MQTT_ESP32_WRAPPER

#include <AsyncMQTT_ESP32.h>
#include <unordered_map>
#include <string>

// Topic Class
class Topic{
    std::string topicName;
    char* value;
    public:
      Topic(){}
      Topic(const char* topic){
        topicName = std::string(topic);
      }
      ~Topic(){
        delete value;
      }
      void setVal(char* val) {
        value = val;
      }
      const char* getName() const {
        return topicName.c_str();
      }
      char* getVal() const{
        return value;
      }
      bool operator==(const char* cmp){
        if (value == nullptr) return false;
        return (*cmp == *value);
      }
      bool operator!=(const char* cmp){
        if (value == nullptr) return true;
        return (*cmp != *value);
      } 
};

class MqttClient{
  static inline std::unordered_map<std::string, Topic*> cache;
  static inline std::string mainTopic;


  static void onMqttMessage(char *topic, char* payload, const AsyncMqttClientMessageProperties& properties,
                     const size_t& len, const size_t& index, const size_t& total)
  {
    // store message in cache
    std::string topicName(topic);
    if (cache.count(topicName))
    	cache[topicName]->setVal(payload);
  }

  static void onMqttConnect(bool sessionPresent){
    client.subscribe((mainTopic + "/#").c_str(), 2);
    client.publish(mainTopic.c_str(), 0, true, "ESP32 Test");
  }
public:
  static inline AsyncMqttClient client;

  MqttClient(){}
  MqttClient(const char* MQTTClientIP, int Port, const char* newTopic){
    client.setServer(MQTTClientIP, Port);
    mainTopic = std::string(newTopic);

    client.onMessage(onMqttMessage);
    client.onConnect(onMqttConnect);
  }
  ~MqttClient(){};

  void addTopic(Topic* topic){
    cache.emplace(mainTopic + "/" + std::string(topic->getName()), topic);
  } 
  void connect(){
    Serial.print("connecting to mqtt");
    client.connect();
  }

  const char* getValue(const char* topic) const {
    std::string topicName(topic);
    if (cache.count(topicName)) return cache.at(topicName)->getName(); 
    return NULL;
  }
};
#endif
