#include <Arduino.h>
#include "PinoutOutsealAtmega128.h"
#include "control.h"

void initControls() {
  pinMode(R1, OUTPUT); // Pompa 1 (Nutrisi A)
  pinMode(R2, OUTPUT); // Pompa 2 (Nutrisi B)
  pinMode(R3, OUTPUT); // Pompa 3 (Sirkulasi A)
  pinMode(R4, OUTPUT);
  pinMode(R5, OUTPUT);
  pinMode(R6, OUTPUT);

  pinMode(S1, INPUT);  // Level Switch 1
  pinMode(S2, INPUT);  // Level Switch 2
  
  // Set kondisi awal semua output ke mati
  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
  digitalWrite(R3, LOW);
  digitalWrite(R4, LOW);
  digitalWrite(R5, LOW);
  digitalWrite(R6, LOW);
}
