#ifndef SENSORS_H
#define SENSORS_H

#include <ModbusMaster.h>
#include <ArduinoJson.h>
#include "config.h"

extern ModbusMaster modbusNodes[6];
extern unsigned long lastSendTime;
extern const long sendInterval;

// Global buffer for storing latest sensor readings
extern StaticJsonDocument<512> sensorDataBuffer;

// --- Fungsi Modbus ---
void preTransmission();
void postTransmission();
void initSensors();
void readSensorDataToBuffer();
void getSensorDataFromBuffer(JsonArray& sensorNodes);

#endif // SENSORS_H
