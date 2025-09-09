#include <Arduino.h>
#include <ModbusMaster.h>
#include <ArduinoJson.h>
#include "PinoutOutsealAtmega128.h"
#include "sensors.h"
#include "config.h"

ModbusMaster modbusNodes[6];  // For Modbus sensors (IDs 2-7)
unsigned long lastSendTime = 0;
const long sendInterval = 5000; // Kirim data setiap 5 detik

// Mapping for Modbus sensors (indices 0-5 in sensorConfig)
int modbusSensorMap[6] = {0, 1, 2, 3, 4, 5};

// Global buffer for storing latest sensor readings
StaticJsonDocument<512> sensorDataBuffer;

// --- Fungsi Modbus ---
void preTransmission() {
  digitalWrite(DM, HIGH);
}

void postTransmission() {
  digitalWrite(DM, LOW);
}

void initModbusSensors() {
  for (int i = 0; i < 6; i++) {
    int configIndex = modbusSensorMap[i];
    modbusNodes[i].begin(sensorConfig[configIndex].modbusId, Serial1);
    modbusNodes[i].preTransmission(preTransmission);
    modbusNodes[i].postTransmission(postTransmission);
  }
}

void initDigitalSensors() {
  // Digital sensors don't need special initialization
  // They use direct pin reading
}

void initSensors() {
  initModbusSensors();
  initDigitalSensors();
}

void readModbusSensorData(JsonArray& sensorNodes) {
  for (int i = 0; i < 6; i++) {
    int configIndex = modbusSensorMap[i];
    JsonObject nodeObj = sensorNodes.createNestedObject();
    nodeObj["id"] = sensorConfig[configIndex].nodeId;
    JsonObject readings = nodeObj.createNestedObject("read");

    if (String(sensorConfig[configIndex].type) == "npk") {
      uint8_t result;
      result = modbusNodes[i].readInputRegisters(0x0001, 1);
      readings["temp"] = (result == modbusNodes[i].ku8MBSuccess) ? modbusNodes[i].getResponseBuffer(0x00) / 10.0F : (float)NULL;
      result = modbusNodes[i].readInputRegisters(0x0003, 1);
      readings["ph"] = (result == modbusNodes[i].ku8MBSuccess) ? modbusNodes[i].getResponseBuffer(0x00) / 10.0F : (float)NULL;
      result = modbusNodes[i].readInputRegisters(0x0008, 1);
      readings["ec"] = (result == modbusNodes[i].ku8MBSuccess) ? modbusNodes[i].getResponseBuffer(0x00) / 10.0F : (float)NULL;
    } else if (String(sensorConfig[configIndex].type) == "cwt") {
      uint8_t result;
      result = modbusNodes[i].readInputRegisters(0x0000, 2);
      if (result == modbusNodes[i].ku8MBSuccess) {
        readings["temp"] = modbusNodes[i].getResponseBuffer(1) / 10.0F;
        readings["hum"] = modbusNodes[i].getResponseBuffer(0) / 10.0F;
      } else {
        readings["temp"] = (float)NULL;
        readings["hum"] = (float)NULL;
      }
    }
    delay(50);
  }
}

void readDigitalSensorData(JsonArray& sensorNodes) {
  for (int i = 6; i < 8; i++) {  // Digital sensors are at indices 6 and 7
    JsonObject nodeObj = sensorNodes.createNestedObject();
    nodeObj["id"] = sensorConfig[i].nodeId;
    JsonObject readings = nodeObj.createNestedObject("read");

    if (String(sensorConfig[i].nodeId) == "wl1") {
      readings["level"] = digitalRead(S1);
    } else if (String(sensorConfig[i].nodeId) == "wl2") {
      readings["level"] = digitalRead(S2);
    }
  }
}

void readSensorDataToBuffer() {
  // Clear previous data
  sensorDataBuffer.clear();

  // Create sensorNodes array in buffer
  JsonArray sensorNodes = sensorDataBuffer.createNestedArray("sensorNodes");

  // Read Modbus sensor data - only store valid readings
  for (int i = 0; i < 6; i++) {
    int configIndex = modbusSensorMap[i];
    JsonObject nodeObj = sensorNodes.createNestedObject();
    nodeObj["id"] = sensorConfig[configIndex].nodeId;
    JsonObject readings = nodeObj.createNestedObject("read");

    if (String(sensorConfig[configIndex].type) == "npk") {
      uint8_t result;
      result = modbusNodes[i].readInputRegisters(0x0001, 1);
      if (result == modbusNodes[i].ku8MBSuccess) {
        readings["temp"] = modbusNodes[i].getResponseBuffer(0x00) / 10.0F;
      }
      result = modbusNodes[i].readInputRegisters(0x0003, 1);
      if (result == modbusNodes[i].ku8MBSuccess) {
        readings["ph"] = modbusNodes[i].getResponseBuffer(0x00) / 10.0F;
      }
      result = modbusNodes[i].readInputRegisters(0x0008, 1);
      if (result == modbusNodes[i].ku8MBSuccess) {
        readings["ec"] = modbusNodes[i].getResponseBuffer(0x00) / 10.0F;
      }
    } else if (String(sensorConfig[configIndex].type) == "cwt") {
      uint8_t result = modbusNodes[i].readInputRegisters(0x0000, 2);
      if (result == modbusNodes[i].ku8MBSuccess) {
        readings["temp"] = modbusNodes[i].getResponseBuffer(1) / 10.0F;
        readings["hum"] = modbusNodes[i].getResponseBuffer(0) / 10.0F;
      }
    }
    delay(50);
  }

  // Read Digital sensor data - always include these
  for (int i = 6; i < 8; i++) {
    JsonObject nodeObj = sensorNodes.createNestedObject();
    nodeObj["id"] = sensorConfig[i].nodeId;
    JsonObject readings = nodeObj.createNestedObject("read");

    if (String(sensorConfig[i].nodeId) == "wl1") {
      readings["level"] = digitalRead(S1);
    } else if (String(sensorConfig[i].nodeId) == "wl2") {
      readings["level"] = digitalRead(S2);
    }
  }
}

void getSensorDataFromBuffer(JsonArray& sensorNodes) {
  // Copy data from buffer to the provided JsonArray
  if (sensorDataBuffer.containsKey("sensorNodes")) {
    JsonArray bufferArray = sensorDataBuffer["sensorNodes"];
    for (JsonVariant item : bufferArray) {
      sensorNodes.add(item);
    }
  }
}

void readSensorData(JsonArray& sensorNodes) {
  readSensorDataToBuffer();
  getSensorDataFromBuffer(sensorNodes);
}
