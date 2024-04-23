# AsyncMQTT Wrapper
This library is a simple header only library for Khoi Hoang's MQTT Library: https://github.com/CCC-Industry4/AsyncMQTTWrapper for ESP32's.

### Dependencies
- Khoi Hoang's AsyncMQTT Library: https://github.com/CCC-Industry4/AsyncMQTTWrapper

## Documentation
#### MQTTClient Class
**Constructors**
```cpp
  // Default Constructor, do not use
  MQTTClient();
  // Creates an MQTTClient Object that connects to the MQTT broker's IP and port.
  // Subscribes to all topics under the namespace of NewTopic.
  MQTTClient(const char* MQTTClientIP, int Port, const char* NewTopic);
```
**Member Functions**
```cpp
   void addTopic(Topic* topic);
   void connect();
   void publish() const;
   const char* getValue(const char* topic) const;
```
#### Topic Class
**Constructors**
```cpp
   Topic();
   Topic(const char* topic);
```
**Member Functions**
```cpp
   const char* getName() const;
   const char* getVal() const;
   bool operator==(const char* cmp);
   bool operator!=(const char* cmp);
   Topic& operator=(char* newVal);
   Topic& operator=(int newVal);
   bool published();
   bool subscribed();
   void setVal(char* val);
   void setPublished(bool val);
   void setSubscribe(bool val);
```
