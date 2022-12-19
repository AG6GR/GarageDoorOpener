#include "GarageDoor.hpp"

#define PIN_STATUS_LED 3
#define PIN_DOOR_POSITION 6
#define PIN_DOOR_SWITCH 7

void setup() {
  Serial.begin(115200);

  // HomeSpan setup
  homeSpan.setStatusPin(PIN_STATUS_LED);
  homeSpan.enableOTA();
  homeSpan.enableWebLog(10,"pool.ntp.org","America/Los_Angeles","myLog");
  homeSpan.begin(Category::GarageDoorOpeners,"Garage Door");
  new SpanAccessory();

  // Accessory Information Service
  new Service::AccessoryInformation();
  new Characteristic::Identify();
  new Characteristic::Model("ESP32 Dev Board");
  new Characteristic::FirmwareRevision("0.1"); 
  
  new GarageDoor(PIN_DOOR_POSITION, PIN_DOOR_SWITCH);
}

void loop() {
  // put your main code here, to run repeatedly:
  homeSpan.poll();
}
