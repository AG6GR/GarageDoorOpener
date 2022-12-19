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
  WEBLOG("update %d", target->getNewVal());
  if (current->getVal() == target->getNewVal())
    return true;
  
  switch (target->getNewVal()) {
    case DOOR_OPEN:
      WEBLOG("update to DOOR_OPEN");
      this->pressSwitch();
      current->setVal(DOOR_OPEN);
      break;
    
    case DOOR_CLOSED:
      WEBLOG("update to DOOR_CLOSED");
      this->pressSwitch();
      current->setVal(DOOR_CLOSED);
      break;

    default:
      break;
  }
  return true;
}

void GarageDoor::loop() {
  if (current->timeVal() > 1000) {
    int readPos = digitalRead(this->sensorPin);
    if (readPos == LOW) {
      if (current->getVal() != DOOR_CLOSED) {
        WEBLOG("Detected door closed");
        current->setVal(DOOR_CLOSED);
      }
    } else {
      if (current->getVal() != DOOR_OPEN) {
        WEBLOG("Detected door open");
        current->setVal(DOOR_OPEN);
      }
    }
  }
}