#include "GarageDoor.hpp"

GarageDoor::GarageDoor(int sensorPin, int switchPin) : Service::GarageDoorOpener() {
  current = new Characteristic::CurrentDoorState(DOOR_CLOSED);
  target = new Characteristic::TargetDoorState(DOOR_CLOSED);

  this->sensorPin = sensorPin;
  this->switchPin = switchPin;

  pinMode(sensorPin, INPUT);
  pinMode(switchPin, OUTPUT);
  digitalWrite(this->switchPin, LOW);
  Serial.println("Creating GarageDoor"); 
}

void GarageDoor::pressSwitch() {
  Serial.println("Enabling switchpin");
  digitalWrite(this->switchPin, HIGH);
  delay(1000);
  Serial.println("Disabling switchpin");
  digitalWrite(this->switchPin, LOW);
}

boolean GarageDoor::update() {
  Serial.print("update ");
  Serial.println(target->getNewVal());
  if (current->getVal() == target->getNewVal())
    return true;
  
  switch (target->getNewVal()) {
    case DOOR_OPEN:
      Serial.println("update to DOOR_OPEN");
      this->pressSwitch();
      current->setVal(DOOR_OPEN);
      break;
    
    case DOOR_CLOSED:
      Serial.println("update to DOOR_CLOSED");
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
        Serial.println("Detected door closed");
        current->setVal(DOOR_CLOSED);
      }
    } else {
      if (current->getVal() != DOOR_OPEN) {
        Serial.println("Detected door open");
        current->setVal(DOOR_OPEN);
      }
    }
  }
}