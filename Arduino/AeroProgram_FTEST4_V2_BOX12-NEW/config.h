#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// --- Konfigurasi Perangkat ---
extern const char* DEVICE_ID;

// Definisikan struktur untuk informasi sensor
struct SensorNodeInfo {
  int modbusId;
  const char* nodeId;
  const char* type; // "cwt", "npk", or "digital"
};

extern SensorNodeInfo sensorConfig[8];

#endif // CONFIG_H
