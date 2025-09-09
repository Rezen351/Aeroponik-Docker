#include <Arduino.h>
#include <ArduinoJson.h>
#include "PinoutOutsealAtmega128.h"
#include "communication.h"
#include "sensors.h"
#include "config.h"
#include "utils.h"
// Global relay states
bool relayStateR1 = false;
bool relayStateR2 = false;
bool relayStateR3 = false;
bool relayStateR4 = false;
bool relayStateR5 = false;
bool relayStateR6 = false;

void handleIncomingCommands() {
  static String inputBuffer = "";

  while (Serial.available() > 0) {
    char c = (char)Serial.read();
    if (c == '\n') {
      if (inputBuffer.length() > 0) {
        StaticJsonDocument<256> doc;
        DeserializationError error = deserializeJson(doc, inputBuffer);

        if (!error) {
          if (doc.containsKey("R1")) relayStateR1 = doc["R1"];
          if (doc.containsKey("R2")) relayStateR2 = doc["R2"];
          if (doc.containsKey("R3")) relayStateR3 = doc["R3"];
          if (doc.containsKey("R4")) relayStateR4 = doc["R4"];
          if (doc.containsKey("R5")) relayStateR5 = doc["R5"];
          if (doc.containsKey("R6")) relayStateR6 = doc["R6"];
        } else {
          Serial.println("JSON Error: " + String(error.c_str()));
        }
      }
      sendSensorDataImmediate();
      delay(100);
      inputBuffer = "";
    } else {
      inputBuffer += c;
    }
  applyRelayStates();
  }
}

void applyRelayStates() {
  digitalWrite(R1, relayStateR1);
  digitalWrite(R2, relayStateR2);
  digitalWrite(R3, relayStateR3);
  digitalWrite(R4, relayStateR4);
  digitalWrite(R5, relayStateR5);
  digitalWrite(R6, relayStateR6);
}




void sendSensorDataImmediate() {
  StaticJsonDocument<512> doc;
  doc["d"] = DEVICE_ID;
  JsonArray data = doc.createNestedArray("s");

  // Get buffered sensor data
  if (sensorDataBuffer.containsKey("sensorNodes")) {
    JsonArray bufferArray = sensorDataBuffer["sensorNodes"];
    for (JsonVariant item : bufferArray) {
      JsonObject sensor = data.createNestedObject();
      sensor["i"] = item["id"];
      JsonObject readings = sensor.createNestedObject("r");

      // Only add non-null values to save space
      if (item["read"]["temp"] != nullptr) readings["t"] = item["read"]["temp"];
      if (item["read"]["hum"] != nullptr) readings["h"] = item["read"]["hum"];
      if (item["read"]["ph"] != nullptr) readings["p"] = item["read"]["ph"];
      if (item["read"]["ec"] != nullptr) readings["e"] = item["read"]["ec"];
      if (item["read"]["level"] != nullptr) readings["l"] = item["read"]["level"];
    }
  }

  serializeJson(doc, Serial);
  Serial.println();
}
