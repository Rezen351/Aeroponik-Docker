#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <ArduinoJson.h>

void handleIncomingCommands();
void sendSensorDataImmediate();
void applyRelayStates();

#endif // COMMUNICATION_H
