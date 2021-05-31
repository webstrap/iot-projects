#include "config.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SHT31.h>

//#define Sprintln(a) (Serial.println(a))
#define Sprintln(a)
char payload[50] = "{}";
WiFiClient client;


void setup() {
  Serial.begin(74880);
  Sprintln(F("MQTT Temperature/Humidity Sensor"));
  delay(10);
  setupWiFi();
  delay(10);

  setupSensor();
  Sprintln(payload);
  delay(10);
  setupMQTT();
  delay(10);
  ESP.deepSleep(DEEP_SLEEP);

}

void loop() {
}

void setupWiFi(){
  Sprintln(F("WiFi Start"));
  Sprintln(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Sprintln(F("."));
  }
  Sprintln(F("IP: ")); 
  Sprintln(WiFi.localIP());
  
}

void setupSensor(){
  Sprintln(F("Sensor Start"));
  Adafruit_SHT31 sht31 = Adafruit_SHT31();
  // Set to 0x45 for alternate i2c addr
  if (! sht31.begin(0x44)) {   
    Sprintln(F("Error with SHT31"));
  }
  float t = sht31.readTemperature();
  char tempString[7];
  dtostrf(t,4,2,tempString);

  float h = sht31.readHumidity();
  char humString[7];
  dtostrf(h,4,2,humString);
  
  char chipId[ 5 ];
  sprintf(chipId,"%lu", system_get_chip_id());

  strcpy(payload, "{\"temperature\":");
  strcat(payload,tempString);
  strcat(payload,",\"humidity\":");
  strcat(payload,humString);
  strcat(payload,",\"device\":\"sht31-");
  strcat(payload, chipId);
  strcat(payload, "\"}");

  Sprintln(payload);
  Sprintln(F("Sensor Done"));
}

void setupMQTT(){
  Sprintln(F("MQTT Start"));
  Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_SERVERPORT);
  Adafruit_MQTT_Publish mqttPub = Adafruit_MQTT_Publish(&mqtt, MQTT_TOPIC);
  Sprintln(F("MQTT Connect"));
  if (mqtt.connect() != 0) {
    Sprintln(F("MQTT Error"));
  }
  mqttPub.publish(payload);
  Sprintln(F("MQTT Success"));
}
