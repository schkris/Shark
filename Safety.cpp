#include "Safety.h"
#include <Arduino.h>

// Safety-related pin definitions
#define HEATER_BED_PIN 12
#define HEATER_0_PIN  13
#define FAN_PIN       4

void initializeSafety() 
{
  pinMode(HEATER_BED_PIN, OUTPUT);
  pinMode(HEATER_0_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  maintainSafety();
}

void maintainSafety() {
  digitalWrite(HEATER_BED_PIN, LOW);
  digitalWrite(HEATER_0_PIN, LOW);
  digitalWrite(FAN_PIN, LOW);
}
