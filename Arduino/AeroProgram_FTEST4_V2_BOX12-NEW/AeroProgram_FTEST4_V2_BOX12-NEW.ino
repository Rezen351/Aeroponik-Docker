#include <ModbusMaster.h>
#include <ArduinoJson.h>
#include <TaskScheduler.h>

#include "PinoutOutsealAtmega128.h"
#include "config.h"
#include "sensors.h"
#include "communication.h"
#include "control.h"
#include "utils.h"

Scheduler runner;

// Task for handling incoming commands
void handleIncomingCommandsTask() {
  handleIncomingCommands();
}

// Task for reading sensor data and storing in buffer
void readSensorDataTask() {
  readSensorDataToBuffer();
}

// Task for sending sensor data (removed - now only sends on serial input)

Task t1(10, TASK_FOREVER, &handleIncomingCommandsTask);
Task t2(5000, TASK_FOREVER, &readSensorDataTask); // Read sensors every 5 seconds

// --- Fungsi Setup ---
void setup() {
  pinMode(DM, OUTPUT);
  digitalWrite(DM, LOW);
  // pinMode(30, OUTPUT);
  // digitalWrite(30, LOW);

  Serial.begin(9600);
  Serial1.begin(9600);

  initSensors();
  initControls();

  runner.init();
  runner.addTask(t1);
  runner.addTask(t2);
  t1.enable();
  t2.enable();
}

// --- Loop Utama ---
void loop() {
  runner.execute();
}
