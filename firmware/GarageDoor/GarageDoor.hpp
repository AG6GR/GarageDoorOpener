#include "HomeSpan.h"
#pragma once

#define DOOR_OPEN 0
#define DOOR_CLOSED 1
#define DOOR_OPENING 2
#define DOOR_CLOSING 3
#define DOOR_STOPPED 4

struct GarageDoor : Service::GarageDoorOpener {
  SpanCharacteristic *current;
  SpanCharacteristic *target;
  int sensorPin;
  int switchPin;
  
  GarageDoor(int sensorPin, int switchPin);

  boolean update();
  void loop();
  void pressSwitch();
};
