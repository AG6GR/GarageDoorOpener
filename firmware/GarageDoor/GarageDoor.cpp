#include "GarageDoor.hpp"

GarageDoor::GarageDoor(int sensorPin, int switchPin) : Service::GarageDoorOpener() {
  current = new Characteristic::CurrentDoorState(DOOR_CLOSED);
  target = new Characteristic::TargetDoorState(DOOR_CLOSED);

  this->sensorPin = sensorPin;
  this->switchPin = switchPin;

  pinMode(sensorPin, INPUT);
  pinMode(switchPin, OUTPUT);
  digitalWrite(this->switchPin, LOW);
  WEBLOG("Creating GarageDoor"); 
}

void GarageDoor::pressSwitch() {
  WEBLOG("Enabling switchPin");
  digitalWrite(this->switchPin, HIGH);
  delay(500);
  WEBLOG("Disabling switchPin");
  digitalWrite(this->switchPin, LOW);
}

boolean GarageDoor::update() {
  WEBLOG("update to %d", target->getNewVal());
  if (current->getVal() == target->getNewVal())
    return true;
  
  switch (target->getNewVal()) {
    case DOOR_OPEN:
      this->pressSwitch();
      break;
    
    case DOOR_CLOSED:
      this->pressSwitch();
      break;

    default:
      break;
  }
  return true;
}

void GarageDoor::loop() {
  if (current->timeVal() > 10000) {
    int readPos = digitalRead(this->sensorPin);
    bool stateChanged = false;
    if (readPos == LOW) {
      if (current->getVal() != DOOR_CLOSED) {
        WEBLOG("Detected door closed");
        current->setVal(DOOR_CLOSED);
        stateChanged = true;
      }
    } else {
      if (current->getVal() != DOOR_OPEN) {
        WEBLOG("Detected door open");
        current->setVal(DOOR_OPEN);
        stateChanged = true;
      }
    }

    if (stateChanged && target->timeVal() > 30000) {
      WEBLOG("No recent Homekit update of target state, set target = current");
      target->setVal(current->getVal());
    }
  }
}